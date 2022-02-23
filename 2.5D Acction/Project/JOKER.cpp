#include "JOKER.h"



JOKER::JOKER()
{
}


JOKER::~JOKER()
{
}

void JOKER::TGInitialize() {
	m_TrickGunFirstCount = m_TrickGunAmount * m_TrickGunSetAmount;
	m_TrickGun2Count = m_TrickGunFirstCount * m_TrickGun2DivisionAmount;
	m_TrickGun3Count = m_TrickGun2Count * m_TrickGun3DivisionAmount;
	m_TrickGunLastCount = m_TrickGun3Count * m_TrickGunLastDivisionAmount;
	m_pTrickGunFirst = new CTrickGun[m_TrickGunFirstCount];
	m_pTrickGun2 = new CTrickGun[m_TrickGun2Count];
	m_pTrickGun3 = new CTrickGun[m_TrickGun3Count];
	m_pTrickGunLast = new CTrickGun[m_TrickGunLastCount];

	for (int i = 0; i < m_TrickGunFirstCount; ++i)
	{
		m_pTrickGunFirst[i].Initialize(m_PlayerNo, 0);
	}
	for (int i = 0; i < m_TrickGun2Count; ++i)
	{
		m_pTrickGun2[i].Initialize(m_PlayerNo, 1);
	}
	for (int i = 0; i < m_TrickGun3Count; ++i)
	{
		m_pTrickGun3[i].Initialize(m_PlayerNo, 2);
	}
	for (int i = 0; i < m_TrickGunLastCount; ++i)
	{
		m_pTrickGunLast[i].Initialize(m_PlayerNo, 3);
	}
	m_TrickGunFirstNo = 0;
	m_TrickGun2No = 0;
	m_TrickGun3No = 0;
	m_TrickGunLastNo = 0;
	m_TrickGunFirstRemSetGap = 0;
	m_TrickGunFirstRemGap = 0;
	m_TrickGunFirstSetNo = 0;
}

void JOKER::TGFGeneration(CCircle enemy) {
	int pno = CControlManager::GetInstance().GetNo(m_PlayerNo);
	if (m_TrickGunFirstRemSetGap > 0)
	{
		return;
	}
	if (m_TrickGunFirstRemGap > 0)
	{
		return;
	}
	if (CInputManager::GetInstance().GetHold(pno, 0))
	{
		m_TrickGunFirstRemGap = m_TrickGunFirstGap;
		if (m_pTrickGunFirst[m_TrickGunFirstNo].GetDrow()) { return; }
		m_pTrickGunFirst[m_TrickGunFirstNo].Generation(GetCircle(), enemy);
		m_TrickGunFirstNo = (m_TrickGunFirstNo < m_TrickGunFirstCount - 1) ? m_TrickGunFirstNo + 1 : 0;
		if (m_TrickGunFirstSetNo < m_TrickGunAmount - 1)
			m_TrickGunFirstSetNo++;
		else
		{
			m_TrickGunFirstSetNo = 0;
			m_TrickGunFirstRemSetGap = m_TrickGunFirstSetGap;
		}
	}
}

void JOKER::TGGeneration() {
	for (int i = 0; i < m_DoubtRingCount; ++i)
	{
		if (!m_pDoubtRing[i].GetDrow()) { continue; }
		for (int j = 0; j < m_TrickGunFirstCount; ++j)
		{
			if (!m_pTrickGunFirst[j].GetDrow()) { continue; }
			TGDivision(0, m_pTrickGunFirst[j].GetCircle(), m_pDoubtRing[i].GetCircle(), j, i);
		}
	}
	for (int i = 0; i < m_DoubtRingCount; ++i)
	{
		if (!m_pDoubtRing[i].GetDrow()) { continue; }
		for (int j = 0; j < m_TrickGun2Count; ++j)
		{
			if (!m_pTrickGun2[j].GetDrow()) { continue; }
			TGDivision(1, m_pTrickGun2[j].GetCircle(), m_pDoubtRing[i].GetCircle(), j, i);
		}
	}
	for (int i = 0; i < m_DoubtRingCount; ++i)
	{
		if (!m_pDoubtRing[i].GetDrow()) { continue; }
		for (int j = 0; j < m_TrickGun3Count; ++j)
		{
			if (!m_pTrickGun3[j].GetDrow()) { continue; }
			TGDivision(2, m_pTrickGun3[j].GetCircle(), m_pDoubtRing[i].GetCircle(), j, i);
		}
	}
}

void JOKER::TGDivision(int p, CCircle cir1, CCircle cir2, int cn1, int cn2) {
	if (cir1.CollisionCircle(cir2))
	{
		if (p == 0)
		{
			m_pTrickGunFirst[cn1].EndDrow();
			for (int i = 0; i < 4; ++i)
			{
				m_pTrickGun2[m_TrickGun2No + i].DivisionGeneration(cir2, i);
				m_pTrickGun2[m_TrickGun2No + i].SetRingNo(1, cn2, cn2);
			}
			if (m_TrickGun2No < m_TrickGun2Count - 5)
				m_TrickGun2No += 4;
			else
				m_TrickGun2No = 0;
			CSoundManager::GetInstance().GetSE(16).Play();
		}
		else if (p == 1)
		{
			if (m_pTrickGun2[cn1].GetRingNo1() == cn2) { return; }
			m_pTrickGun2[cn1].EndDrow();
			for (int i = 0; i < 4; ++i)
			{
				m_pTrickGun3[m_TrickGun3No + i].DivisionGeneration(cir2, i);
				m_pTrickGun3[m_TrickGun3No + i].SetRingNo(2, m_pTrickGun2[cn1].GetRingNo1(), cn2);
			}
			if (m_TrickGun3No < m_TrickGun3Count - 5)
				m_TrickGun3No += 4;
			else
				m_TrickGun3No = 0;
			CSoundManager::GetInstance().GetSE(16).Play();
		}
		else if (p == 2)
		{
			if (m_pTrickGun3[cn1].GetRingNo1() == cn2 || m_pTrickGun3[cn1].GetRingNo2() == cn2) { return; }
			m_pTrickGun3[cn1].EndDrow();
			for (int i = 0; i < 8; ++i)
			{
				m_pTrickGunLast[m_TrickGunLastNo + i].DivisionGeneration(cir2, i);
				m_pTrickGunLast[m_TrickGunLastNo + i].SetRingNo(2, m_pTrickGun3[cn1].GetRingNo1(), cn2);
			}
			if (m_TrickGunLastNo < m_TrickGunLastCount - 9)
				m_TrickGunLastNo += 8;
			else
				m_TrickGunLastNo = 0;
			CSoundManager::GetInstance().GetSE(17).Play();
		}
	}
}

void JOKER::DoubtRingInitialize() {
	m_pDoubtRing = new CDoubtRing[m_DoubtRingCount];
	for (int i = 0; i < m_DoubtRingCount; ++i)
	{
		m_pDoubtRing[i].Initialize(m_PlayerNo, 0);
	}
	m_DoubtRingNo = 0;
	m_DoubtRingRemGap = 0;
}

void JOKER::DoubtRingGeneration(CCircle enemy) {
	int pno = CControlManager::GetInstance().GetNo(m_PlayerNo);
	if (m_DoubtRingRemGap > 0)
	{
		return;
	}
	if (CInputManager::GetInstance().GetPush(pno, 1))
	{
		for (int i = 0; i < m_DoubtRingCount; i++)
		{
			if (m_pDoubtRing[i].GetDrow()) { continue; }
			m_DoubtRingRemGap = m_DoubtRingGap;
			m_pDoubtRing[i].Generation(GetCircle(), enemy);
			return;
		}
	}
}

void JOKER::Heal() {
	int pno = CControlManager::GetInstance().GetNo(m_PlayerNo);
	if (m_RemHealGap > 0)
	{
		return;
	}
	if (m_Skill < JOKER_SKILL / 3 || m_Life == JOKER_LIFE) { return; }
	if (CInputManager::GetInstance().GetPush(pno, 2))
	{
		m_Skill -= JOKER_SKILL / 6;
		if (m_Life > JOKER_LIFE / 7 * 6)
			m_Life = JOKER_LIFE;
		else
			m_Life += JOKER_LIFE / 7;
		m_RemHealGap = m_HealGap;
		CSoundManager::GetInstance().GetSE(9).Play();
	}
}

void JOKER::Inversion() {
	int pno = CControlManager::GetInstance().GetNo(m_PlayerNo);
	//*m_EInv = 1;
	if (m_RemInvGap > 0)
	{
		return;
	}
	if (m_Skill < JOKER_SKILL / 3 * 2) { return; }
	if (CInputManager::GetInstance().GetPush(pno, 3))
	{
		m_Skill -= JOKER_SKILL / 3;
		m_RemInvGap = m_InvGap;
		CJokerSkillManager::GetInstance().StartInver(m_PlayerNo, m_InvTime);
		CSoundManager::GetInstance().GetSE(18).Play();
	}
}

void JOKER::Slow() {
	int pno = CControlManager::GetInstance().GetNo(m_PlayerNo);
	if (m_RemSlowGap > 0)
	{
		return;
	}
	if (m_Skill < JOKER_SKILL) { return; }
	if (CInputManager::GetInstance().GetPush(pno, 6))
	{
		m_Skill -= JOKER_SKILL / 2;
		m_RemSlowGap = m_SlowGap;
		CJokerSkillManager::GetInstance().StartSlow(m_PlayerNo, m_SlowMagni, m_SlowTime);
		CSoundManager::GetInstance().GetSE(19).Play();
	}
}

void JOKER::Teleport() {
	int pno = CControlManager::GetInstance().GetNo(m_PlayerNo);
	if (m_RemTelGap > 0)
	{
		return;
	}
	if (m_Skill < m_TeleportEnergy) { return; }
	if (CInputManager::GetInstance().GetPush(pno, 5))
	{
		m_Skill -= m_TeleportEnergy;
		if (CInputManager::GetInstance().GetHorizontal(pno) > 0.1875)
		{
			m_Move.x += m_Teleport;
		}
		if (CInputManager::GetInstance().GetHorizontal(pno) < -0.1875)
		{
			m_Move.x -= m_Teleport;
		}
		if (CInputManager::GetInstance().GetVertical(pno) < -0.1875)
		{
			m_Move.y -= m_Teleport;
		}
		if (CInputManager::GetInstance().GetVertical(pno) > 0.1875)
		{
			m_Move.y += m_Teleport;
		}
		m_RemTelGap = m_TelGap;
		CSoundManager::GetInstance().GetSE(13).Play();
	}
	else if (CInputManager::GetInstance().GetPush(pno, 4))
	{
		m_Skill -= m_HyperTeleportEnergy;
		if (CInputManager::GetInstance().GetHorizontal(pno) > 0.1875)
		{
			m_Move.x += m_HyperTeleport;
		}
		if (CInputManager::GetInstance().GetHorizontal(pno) < -0.1875)
		{
			m_Move.x -= m_HyperTeleport;
		}
		if (CInputManager::GetInstance().GetVertical(pno) < -0.1875)
		{
			m_Move.y -= m_HyperTeleport;
		}
		if (CInputManager::GetInstance().GetVertical(pno) > 0.1875)
		{
			m_Move.y += m_HyperTeleport;
		}
		m_RemTelGap = m_TelGap;
		CSoundManager::GetInstance().GetSE(13).Play();
	}
}

void JOKER::Initialize(CCircle enemy) {
	m_MaxLife = JOKER_LIFE;
	m_MaxSkill = JOKER_SKILL;
	m_Speed = JOKER_SPEED;

	m_Life = m_MaxLife;
	m_Skill = 0;

	m_RemHealGap = 0;
	m_RemInvGap = 0;
	DoubtRingInitialize();
	TGInitialize();
}

void JOKER::Update(CCircle enemy) {
	TimeReduse();
	Generation(enemy);
	Teleport();
	Heal();
	Inversion();
	Slow();
}

void JOKER::TimeReduse() {
	if (CJokerSkillManager::GetInstance().CanMove(m_PlayerNo))
	{
		m_TrickGunFirstRemSetGap = max(m_TrickGunFirstRemSetGap - 1, 0);
		if (m_TrickGunFirstRemSetGap == 0)
		{
			m_TrickGunFirstRemGap = max(m_TrickGunFirstRemGap - 1, 0);
		}
		m_DoubtRingRemGap = max(m_DoubtRingRemGap - 1, 0);
		m_RemHealGap = max(m_RemHealGap - 1, 0);
		m_RemInvGap = max(m_RemInvGap - 1, 0);
		m_RemSlowGap = max(m_RemSlowGap - 1, 0);
		m_RemTelGap = max(m_RemTelGap - 1, 0);
	}
}

void JOKER::Generation(CCircle enemy) {
	DoubtRingGeneration(enemy);
	TGFGeneration(enemy);
	TGGeneration();
}

void JOKER::Collision(CCircle enemy, CCircle egraze, int& damage, int& eskill) {
	int pskill = 0, dam = 0, esk = 0;
	for (int i = 0; i < m_DoubtRingCount; ++i)
	{
		if (m_pDoubtRing[i].Collition(enemy, egraze, pskill, dam, esk))
		{
			m_Skill += pskill;
			damage += dam;
			eskill += esk;
		}
	}
	for (int i = 0; i < m_TrickGunFirstCount; ++i)
	{
		if (m_pTrickGunFirst[i].Collition(enemy, egraze, pskill, dam, esk))
		{
			m_Skill += pskill;
			damage += dam;
			eskill += esk;
		}
	}
	for (int i = 0; i < m_TrickGun2Count; ++i)
	{
		if (m_pTrickGun2[i].Collition(enemy, egraze, pskill, dam, esk))
		{
			m_Skill += pskill;
			damage += dam;
			eskill += esk;
		}
	}
	for (int i = 0; i < m_TrickGun3Count; ++i)
	{
		if (m_pTrickGun3[i].Collition(enemy, egraze, pskill, dam, esk))
		{
			m_Skill += pskill;
			damage += dam;
			eskill += esk;
		}
	}
	for (int i = 0; i < m_TrickGunLastCount; ++i)
	{
		if (m_pTrickGunLast[i].Collition(enemy, egraze, pskill, dam, esk))
		{
			m_Skill += pskill;
			damage += dam;
			eskill += esk;
		}
	}

	if (m_Skill > m_MaxSkill)
		m_Skill = m_MaxSkill;
}

void JOKER::Fly(CCircle enemy) {
	for (int i = 0; i < m_DoubtRingCount; ++i)
	{
		m_pDoubtRing[i].Update(GetCircle(), enemy);
	}
	for (int i = 0; i < m_TrickGunFirstCount; ++i)
	{
		m_pTrickGunFirst[i].Update(GetCircle(), enemy);
	}
	for (int i = 0; i < m_TrickGun2Count; ++i)
	{
		m_pTrickGun2[i].Update(GetCircle(), enemy);
	}
	for (int i = 0; i < m_TrickGun3Count; ++i)
	{
		m_pTrickGun3[i].Update(GetCircle(), enemy);
	}
	for (int i = 0; i < m_TrickGunLastCount; ++i)
	{
		m_pTrickGunLast[i].Update(GetCircle(), enemy);
	}
}

void JOKER::Render() {
	CGraphicsUtilities::RenderCircle(GetRenderCircle(), MOF_XRGB(255, 0, 0));
	CGraphicsUtilities::RenderCircle(GetRenderGrazeCircle(), MOF_XRGB(255, 100, 100));
	for (int i = 0; i < m_DoubtRingCount; ++i)
	{
		m_pDoubtRing[i].Render();
	}
	for (int i = 0; i < m_TrickGunFirstCount; ++i)
	{
		m_pTrickGunFirst[i].Render();
	}
	for (int i = 0; i < m_TrickGun2Count; ++i)
	{
		m_pTrickGun2[i].Render();
	}
	for (int i = 0; i < m_TrickGun3Count; ++i)
	{
		m_pTrickGun3[i].Render();
	}
	for (int i = 0; i < m_TrickGunLastCount; ++i)
	{
		m_pTrickGunLast[i].Render();
	}

	float x = CTextureManager::GetInstance().GetCharacter(0).GetWidth();
	float y = CTextureManager::GetInstance().GetCharacter(0).GetHeight();
	float scale = m_GrazeRadius / max(x, y) * 2;
	x = m_Pos.x - x * scale / 2;
	y = m_Pos.y - y * scale / 2;
	CTextureManager::GetInstance().GetCharacter(2).RenderScale(x, y, scale);
}

void JOKER::Release() {
	if (m_pDoubtRing)
	{
		delete[] m_pDoubtRing;
		m_pDoubtRing = NULL;
	}
	if (m_pTrickGunFirst)
	{
		delete[] m_pTrickGunFirst;
		m_pTrickGunFirst = NULL;
	}
	if (m_pTrickGun2)
	{
		delete[] m_pTrickGun2;
		m_pTrickGun2 = NULL;
	}
	if (m_pTrickGun3)
	{
		delete[] m_pTrickGun3;
		m_pTrickGun3 = NULL;
	}
	if (m_pTrickGunLast)
	{
		delete[] m_pTrickGunLast;
		m_pTrickGunLast = NULL;
	}
}