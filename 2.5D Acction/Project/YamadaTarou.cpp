#include "YamadaTarou.h"

YamadaTarou::YamadaTarou()
{
}

YamadaTarou::~YamadaTarou()
{
}

// 山田オーブ
void YamadaTarou::YamadaOrbInitialize() {
	m_pYamadaOrb = new CYamadaOrb[m_YamadaOrbCount];
	for (int i = 0; i < m_YamadaOrbCount; ++i)
	{
		m_pYamadaOrb[i].Initialize(m_PlayerNo, 0);
	}
	m_YamadaOrbNo = 0;
	m_YamadaOrbRemGap = 0;
}

void YamadaTarou::YamadaOrbGeneration(CCircle enemy) {
	int pno = CControlManager::GetInstance().GetNo(m_PlayerNo);
	if (m_YamadaOrbRemGap > 0)
	{
		return;
	}
	if (m_YamadaBeamNow || m_YamadaBallRemGap > 0 || m_YamadaBlizzardNow == true || m_TensionUP == true) { return; }
	if (CInputManager::GetInstance().GetHold(pno, 0))
	{
		int patern = rand() % m_YamadaOrbStartPosPaternCount;
		m_pYamadaOrb[m_YamadaOrbNo].Generation(YamadaOrbPos.GetPosition(patern, GetCircle(), enemy), enemy);
		m_YamadaOrbRemGap = m_YamadaOrbGap;
		if (m_YamadaOrbNo < m_YamadaOrbCount - 1)
			m_YamadaOrbNo++;
		else
			m_YamadaOrbNo = 0;
	}
}

// 山田ビーム
void YamadaTarou::YamadaBeamInitialize() {
	m_YamadaBeam.Initialize(m_PlayerNo, 0);
	m_YamadaBeamRemGap = 0;
}

void YamadaTarou::YamadaBeamGeneration(CCircle enemy) {
	int pno = CControlManager::GetInstance().GetNo(m_PlayerNo);
	m_YamadaBeamNow = false;
	if (m_YamadaBeam.GetDrow())
	{
		m_YamadaBeamNow = true;
		return;
	}
	if (m_YamadaBeamRemGap > 0)
	{
		return;
	}
	if (m_YamadaBallRemGap > 0 || m_YamadaBlizzardNow == true || m_TensionUP == true) { return; }
	if (CInputManager::GetInstance().GetHold(pno, 1))
	{
		m_YamadaBeam.Generation(GetCircle(), enemy);
		m_YamadaBeamRemGap = m_YamadaBeamGap;
	}
}

// 山田ボール
void YamadaTarou::YamadaBallInitialize() {
	m_YamadaBall.Initialize(m_PlayerNo, 0);
	m_YamadaBallRemGap = 0;
}

void YamadaTarou::YamadaBallGeneration(CCircle enemy) {
	int pno = CControlManager::GetInstance().GetNo(m_PlayerNo);
	if (m_YamadaBallRemGap > 0)
	{
		return;
	}
	if (m_YamadaBeamNow || m_TensionUP || m_YamadaBlizzardNow) { return; }
	if (m_Skill < YAMADA_SKILL / 3) { return; }
	if (CInputManager::GetInstance().GetHold(pno, 2))
	{
		m_Skill -= YAMADA_SKILL / 6;
		m_YamadaBall.Generation(GetCircle(), enemy);
		m_YamadaBallRemGap = m_YamadaBallGap;
	}
}

// 山田吹雪
void YamadaTarou::YamadaBlizzardInitialize() {
	m_pYamadaBlizzard = new CYamadaBlizzard[m_YamadaBlizzardCount];
	for (int i = 0; i < m_YamadaOrbCount; ++i)
	{
		m_pYamadaBlizzard[i].Initialize(m_PlayerNo, i);
	}
	m_YamadaBlizzardNo = 0;
	m_YamadaBlizzardNow = false;
	m_YamadaBlizzardAllRemGap = 0;
	m_YamadaBlizzardRemGap = 0;
	m_YamadaBlizzardRemPer = 0;
}

void YamadaTarou::YamadaBlizzardStart() {
	int pno = CControlManager::GetInstance().GetNo(m_PlayerNo);
	m_YamadaBlizzardNow = false;
	if (m_YamadaBlizzardRemPer > 0)
	{
		m_YamadaBlizzardNow = true;
		return;
	}
	if (m_YamadaBlizzardAllRemGap > 0)
	{
		return;
	}
	if (m_YamadaBeamNow == true || m_YamadaBallRemGap > 0 || m_TensionUP == true) { return; }
	if (m_Skill < YAMADA_SKILL / 3 * 2) { return; }
	if (CInputManager::GetInstance().GetPush(pno, 3))
	{
		m_Skill -= YAMADA_SKILL / 3;
		m_YamadaBlizzardAllRemGap = m_YamadaBlizzardAllGap;
		m_YamadaBlizzardRemPer = m_YamadaBlizzardPer;
		CSoundManager::GetInstance().GetSE(23).Play();
	}
}

void YamadaTarou::YamadaBlizzardGeneration(CCircle enemy) {
	if (m_YamadaBlizzardRemPer == 0) { return; }
	if (m_YamadaBlizzardRemGap > 0)
	{
		return;
	}
	int patern = rand() % m_YamadaOrbStartPosPaternCount;
	m_pYamadaBlizzard[m_YamadaBlizzardNo].Generation(YamadaOrbPos.GetPosition(patern, GetCircle(), enemy), enemy);
	m_YamadaBlizzardRemGap = m_YamadaBlizzardGap;
	if (m_YamadaBlizzardNo < m_YamadaOrbCount - 1)
		m_YamadaBlizzardNo++;
	else
		m_YamadaBlizzardNo = 0;

}

// 山田世界
void YamadaTarou::YamadaWorldInitialize() {
	m_pYamadaWorld = new CYamadaWorld[m_YamadaWorldCount];
	for (int i = 0; i < m_YamadaWorldCount; ++i)
	{
		m_pYamadaWorld[i].Initialize(m_PlayerNo, i);
	}
	m_YamadaWorldRemPer = 0;
}

void YamadaTarou::YamadaWorldGeneration(CCircle enemy) {
	int pno = CControlManager::GetInstance().GetNo(m_PlayerNo);
	if (m_YamadaWorldRemPer > 0)
	{
		return;
	}
	if (m_YamadaBeamNow == true || m_YamadaBallRemGap > 0 || m_YamadaBlizzardNow == true || m_TensionUP == true) { return; }
	if (m_Skill < YAMADA_SKILL) { return; }
	if (CInputManager::GetInstance().GetPush(pno, 6))
	{
		m_Skill -= YAMADA_SKILL / 2;
		m_YamadaWorldRemPer = m_YamadaWorldPer;
		for (int i = 0; i < m_YamadaWorldCount; ++i)
		{
			m_pYamadaWorld[i].Generation(GetCircle(), enemy);
		}
	}
}

// ノリと勢い
void YamadaTarou::TensionUP() {
	int pno = CControlManager::GetInstance().GetNo(m_PlayerNo);
	m_TensionUP = false;
	m_BigTensionUP = false;
	if (m_YamadaBeamNow == true || m_YamadaBlizzardNow == true) { return; }
	if (CInputManager::GetInstance().GetHold(pno, 5))
	{
		if (m_Skill < YAMADA_SKILL)
			m_Skill += m_BigTensionPoint;
		else
			m_Skill = YAMADA_SKILL;
		m_BigTensionUP = true;
		m_TensionUP = true;
	}
	else if (CInputManager::GetInstance().GetHold(pno, 4))
	{
		if (m_Skill < YAMADA_SKILL)
			m_Skill += m_TensionPoint;
		else
			m_Skill = YAMADA_SKILL;
		m_TensionUP = true;
	}
}

void YamadaTarou::Appeal() {
	if (m_AppealRemGap > 0)
	{
		return;
	}
	if (m_AppealRemGrowSize < m_AppealGrowSize)
	{
		m_Radius += 1;
		m_GrazeRadius += 1;
		m_AppealRemGrowSize++;
		m_AppealRemGap = m_AppealGap;
		CSoundManager::GetInstance().GetSE(20).Play();
	}
}

void YamadaTarou::Initialize(CCircle enemy) {
	m_MaxLife = YAMADA_LIFE;
	m_MaxSkill = YAMADA_SKILL;
	m_Speed = YAMADA_SPEED;

	m_Life = m_MaxLife;
	m_Skill = 0;

	m_AppealRemGrowSize = 0;
	m_AppealRemGap = 0;

	YamadaOrbInitialize();
	YamadaBeamInitialize();
	YamadaBallInitialize();
	YamadaBlizzardInitialize();
	YamadaWorldInitialize();
}

void YamadaTarou::Update(CCircle enemy) {
	TimeReduse();
	Generation(enemy);
	Reaction();
	Appeal();
}

void YamadaTarou::TimeReduse() {
	if (CJokerSkillManager::GetInstance().CanMove(m_PlayerNo))
	{
		m_YamadaOrbRemGap = max(m_YamadaOrbRemGap - 1, 0);
		if (!m_YamadaBeam.GetDrow())
		{
			m_YamadaBeamRemGap = max(m_YamadaBeamRemGap - 1, 0);
		}
		m_YamadaBallRemGap = max(m_YamadaBallRemGap - 1, 0);
		m_YamadaBlizzardRemPer = max(m_YamadaBlizzardRemPer - 1, 0);
		if (m_YamadaBlizzardRemPer == 0)
		{
			m_YamadaBlizzardAllRemGap = max(m_YamadaBlizzardAllRemGap - 1, 0);
		}
		if (m_YamadaBlizzardRemPer != 0)
		{
			m_YamadaBlizzardRemGap = max(m_YamadaBlizzardRemGap - 1, 0);
		}
		m_YamadaWorldRemPer = max(m_YamadaWorldRemPer - 1, 0);
		m_AppealRemGap = max(m_AppealRemGap - 1, 0);
	}
}

void YamadaTarou::Generation(CCircle enemy) {

	// 山田オーブ
	YamadaOrbGeneration(enemy);
	// 山田ビーム
	YamadaBeamGeneration(enemy);
	// 山田ボール
	YamadaBallGeneration(enemy);
	// 山田吹雪
	YamadaBlizzardStart();
	YamadaBlizzardGeneration(enemy);
	// 山田世界
	YamadaWorldGeneration(enemy);
	// 鼓舞
	TensionUP();
}

void YamadaTarou::Collision(CCircle enemy, CCircle egraze, int& damage, int& eskill) {
	int pskill = 0, dam = 0, esk = 0;
	for (int i = 0; i < m_YamadaOrbCount; ++i)
	{
		if (m_pYamadaOrb[i].Collition(enemy, egraze, pskill, dam, esk))
		{
			m_Skill += pskill;
			damage += dam;
			eskill += esk;
		}
	}
	if (m_YamadaBeam.Collition(enemy, egraze, pskill, dam, esk))
	{
		m_Skill += pskill;
		damage += dam;
		eskill += esk;
	}
	if (m_YamadaBall.Collition(enemy, egraze, pskill, dam, esk))
	{
		m_Skill += pskill;
		damage += dam;
		eskill += esk;
	}
	for (int i = 0; i < m_YamadaOrbCount; ++i)
	{
		if (m_pYamadaBlizzard[i].Collition(enemy, egraze, pskill, dam, esk))
		{
			m_Skill += pskill;
			damage += dam;
			eskill += esk;
		}
	}
	for (int i = 0; i < m_YamadaWorldCount; ++i)
	{
		if (m_pYamadaWorld[i].Collition(enemy, egraze, pskill, dam, esk))
		{
			m_Skill += pskill;
			damage += dam;
			eskill += esk;
		}
	}
	if (m_Skill > m_MaxSkill)
		m_Skill = m_MaxSkill;
}

void YamadaTarou::Fly(CCircle enemy) {
	for (int i = 0; i < m_YamadaOrbCount; ++i)
	{
		m_pYamadaOrb[i].Update(GetCircle(), enemy);
	}
	m_YamadaBeam.Update(GetCircle(), enemy);
	m_YamadaBall.Update(GetCircle(), enemy);
	for (int i = 0; i < m_YamadaOrbCount; ++i)
	{
		m_pYamadaBlizzard[i].Update(GetCircle(), enemy);
	}
	for (int i = 0; i < m_YamadaWorldCount; ++i)
	{
		m_pYamadaWorld[i].Update(GetCircle(), enemy);
	}
}

void YamadaTarou::Reaction() {
	m_Speed = YAMADA_SPEED;
	if (m_YamadaBeamNow == true)
	{
		m_Speed -= m_YamadaBeamReaction;
	}
	else if (m_BigTensionUP == true)
	{
		m_Speed -= m_TensionReaction;
	}
}

void YamadaTarou::Render() {
	CPlayer::Render();

	/*
	CGraphicsUtilities::RenderCircle(GetRenderCircle(), MOF_XRGB(255, 0, 0));
	CGraphicsUtilities::RenderCircle(GetRenderGrazeCircle(), MOF_XRGB(255, 100, 100));
	for (int i = 0; i < m_YamadaOrbCount; ++i)
	{
		m_pYamadaOrb[i].Render();
	}
	for (int i = 0; i < m_YamadaOrbStartPosPaternCount; ++i)
	{
		//YamadaOrbPos.Render(i);
	}
	m_YamadaBeam.Render();
	for (int i = 0; i < m_YamadaOrbCount; ++i)
	{
		m_pYamadaBlizzard[i].Render();
	}
	m_YamadaBall.Render();
	for (int i = 0; i < m_YamadaWorldCount; ++i)
	{
		m_pYamadaWorld[i].Render();
	}

	float x = CTextureManager::GetInstance().GetCharacter(0).GetWidth();
	float y = CTextureManager::GetInstance().GetCharacter(0).GetHeight();
	float scale = m_GrazeRadius / max(x, y) * 2;
	x = m_Pos.x - x * scale / 2;
	y = m_Pos.y - y * scale / 2;
	CTextureManager::GetInstance().GetCharacter(3).RenderScale(x, y, scale);
	*/
}

void YamadaTarou::Release() {
	if (m_pYamadaOrb)
	{
		delete[] m_pYamadaOrb;
		m_pYamadaOrb = NULL;
	}
	if (m_pYamadaBlizzard)
	{
		delete[] m_pYamadaBlizzard;
		m_pYamadaBlizzard = NULL;
	}
	if (m_pYamadaWorld)
	{
		delete[] m_pYamadaWorld;
		m_pYamadaWorld = NULL;
	}
}