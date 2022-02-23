#include "Lovey.h"



Lovey::Lovey()
{
}


Lovey::~Lovey()
{
}

void Lovey::MachineGunInitialize() {
	m_MachineGunCount = m_MachineGunColumn * m_MachineGunAmount * m_MachineGunSetAmount;
	m_pMachineGun = new CMachineGun[m_MachineGunCount];
	for (int i = 0; i < m_MachineGunCount; ++i)
	{
		m_pMachineGun[i].Initialize(m_PlayerNo, i);
	}
	m_MachineGunNo = 0;
	m_MachineGunSetNo = 0;
	m_MachineGunRemGap = 0;
	m_MachineGunAllRemGap = 0;
}

void Lovey::MachineGunGenerasion(CCircle enemy) {
	int pno = CControlManager::GetInstance().GetNo(m_PlayerNo);
	if (CInputManager::GetInstance().GetPull(pno, 0))
	{
		m_MachineGunSetNo = 0;
	}
	if (m_MachineGunAllRemGap > 0)
	{
		return;
	}
	if (m_MachineGunRemGap > 0)
	{
		return;
	}
	if (m_ChargeLaserRemGap > 0 || m_bContinuousenEnergyShotNow || m_bHomingShotNow) { return; }
	if (CInputManager::GetInstance().GetHold(pno, 0))
	{
		m_MachineGunRemGap = m_MachineGunGap;
		for (int i = 0; i < m_MachineGunColumn; ++i)
		{
			m_pMachineGun[m_MachineGunNo * m_MachineGunColumn + i].Generation(GetCircle(), enemy);
		}
		m_MachineGunNo = (m_MachineGunNo < m_MachineGunCount / m_MachineGunColumn - 1) ? m_MachineGunNo + 1 : 0;
		if (m_MachineGunSetNo < m_MachineGunAmount - 1)
			m_MachineGunSetNo++;
		else
		{
			m_MachineGunSetNo = 0;
			m_MachineGunAllRemGap = m_MachineGunAllGap;
		}
	}
}

void Lovey::ChargeShotInitialize() {
	m_pChargeShot = new CChargeShot[m_ChargeShotCount];
	for (int i = 0; i < m_ChargeShotCount; ++i)
	{
		m_pChargeShot[i].Initialize(m_PlayerNo, 0);
	}
	m_ChargeShotNo = 0;
	m_ChargeShotRemGap = 0;
}

void Lovey::ChargeShotGenerasion(CCircle enemy) {
	int pno = CControlManager::GetInstance().GetNo(m_PlayerNo);
	if (m_ChargeShotRemGap > 0)
	{
		return;
	}
	for (int i = 0; i < m_ChargeShotCount; i++)
	{
		if (m_pChargeShot[i].GetFly()) { continue; }
		if (m_ChargeLaserRemGap > 0 || m_bContinuousenEnergyShotNow || m_bHomingShotNow) { return; }
		if (!m_bChargeShotHold) { m_ChargeShotNo = i; }
		if (CInputManager::GetInstance().GetHold(pno, 1))
		{
			m_pChargeShot[m_ChargeShotNo].Generation(GetCircle(), enemy);
			m_bChargeShotHold = true;
		}
		if (CInputManager::GetInstance().GetPull(pno, 1))
		{
			m_ChargeShotRemGap = m_ChargeShotGap;
			m_pChargeShot[m_ChargeShotNo].SetFly();
			if (m_pChargeShot[m_ChargeShotNo].GetBulletStatus().Damage == m_pChargeShot[m_ChargeShotNo].GetBulletStatus().MaxDamage)
				CSoundManager::GetInstance().GetSE(11).Play();
			else
				CSoundManager::GetInstance().GetSE(7).Play();
			m_bChargeShotHold = false;
		}
		return;
	}
}

void Lovey::ChargeLaserInitialize() {
	m_ChargeLaser.Initialize(m_PlayerNo, 0);
	m_ChargeLaserRemGap = 0;
}

void Lovey::ChargeLaserGenerasion(CCircle enemy) {
	int pno = CControlManager::GetInstance().GetNo(m_PlayerNo);
	if (m_ChargeLaser.GetDrow())
	{
		return;
	}
	if (m_ChargeLaserRemGap > 0)
	{
		return;
	}
	if (m_bContinuousenEnergyShotNow || m_bHomingShotNow) { return; }
	if (m_Skill < LOVEY_SKILL / 3) { return; }
	if (CInputManager::GetInstance().GetPull(pno, 2))
	{
		m_Skill -= LOVEY_SKILL / 6;
		m_ChargeLaser.Generation(GetCircle(), enemy);
		m_ChargeLaserRemGap = m_ChargeLaserGap;
	}
}

void Lovey::ContinuousenEnergyShotInitialize() {
	m_ContinuousenEnergyShotCount = m_ContinuousenEnergyShotAmount * m_ContinuousenEnergyShotSetAmount;
	m_pContinuousenEnergyShot = new CContinuousenEnergyShot[m_ContinuousenEnergyShotCount];
	for (int i = 0; i < m_ContinuousenEnergyShotCount; ++i)
	{
		m_pContinuousenEnergyShot[i].Initialize(m_PlayerNo, 0);
	}
	m_ContinuousenEnergyShotNo = 0;
	m_ContinuousenEnergyShotSetNo = 0;
	m_ContinuousenEnergyShotRemGap = 0;
	m_ContinuousenEnergyShotAllRemGap = 0;
	m_bContinuousenEnergyShotNow = false;
}

void Lovey::ContinuousenEnergyShotStart() {
	int pno = CControlManager::GetInstance().GetNo(m_PlayerNo);
	if (m_bContinuousenEnergyShotNow)
	{
		return;
	}
	if (m_ContinuousenEnergyShotAllRemGap > 0)
	{
		return;
	}
	if (m_ChargeLaserRemGap > 0 || m_bHomingShotNow) { return; }
	if (m_Skill < LOVEY_SKILL / 3 * 2) { return; }
	if (CInputManager::GetInstance().GetPull(pno, 3))
	{
		m_Skill -= LOVEY_SKILL / 3;
		m_ContinuousenEnergyShotAllRemGap = m_ContinuousenEnergyShotAllGap;
		m_bContinuousenEnergyShotNow = true;
	}
}

void Lovey::ContinuousenEnergyShotGeneration(CCircle enemy) {
	if (!m_bContinuousenEnergyShotNow)
	{
		return;
	}
	if (m_ContinuousenEnergyShotSetRemGap > 0)
	{
		return;
	}
	if (m_ContinuousenEnergyShotRemGap > 0)
	{
		return;
	}
	m_pContinuousenEnergyShot[m_ContinuousenEnergyShotNo].Generation(GetCircle(), enemy);
	m_ContinuousenEnergyShotRemGap = m_ContinuousenEnergyShotGap;
	if (m_ContinuousenEnergyShotNo < m_ContinuousenEnergyShotCount - 1)
		m_ContinuousenEnergyShotNo++;
	else
	{
		m_ContinuousenEnergyShotNo = 0;
		m_bContinuousenEnergyShotNow = false;
	}
	if (m_ContinuousenEnergyShotSetNo < m_ContinuousenEnergyShotAmount - 1)
		m_ContinuousenEnergyShotSetNo++;
	else
	{
		m_ContinuousenEnergyShotSetNo = 0;
		m_ContinuousenEnergyShotSetRemGap = m_ContinuousenEnergyShotSetGap;
	}
}

void Lovey::HomingShotInitialize() {
	m_HomingShotCount = m_HomingShotColumn * m_HomingShotAmount;
	m_pHomingShot = new CHomingShot[m_HomingShotCount];
	for (int i = 0; i < m_HomingShotCount; ++i)
	{
		m_pHomingShot[i].Initialize(m_PlayerNo, i);
	}
	m_HomingShotNo = 0;
	m_HomingShotRemGap = 0;
	m_bHomingShotNow = false;
}

void Lovey::HomingShotStart() {
	int pno = CControlManager::GetInstance().GetNo(m_PlayerNo);
	if (m_bHomingShotNow) { return; }
	if (m_ChargeLaserRemGap > 0 || m_bContinuousenEnergyShotNow) { return; }
	if (m_Skill < LOVEY_SKILL) { return; }
	if (CInputManager::GetInstance().GetPush(pno, 6))
	{
		m_Skill -= LOVEY_SKILL / 2;
		m_bHomingShotNow = true;
		m_HomingShotNo = 0;
	}
}

void Lovey::HomingShotGeneration(CCircle enemy) {
	if (!m_bHomingShotNow) { return; }
	if (m_HomingShotRemGap > 0)
	{
		return;
	}
	for (int i = 0; i < m_HomingShotColumn; ++i)
	{
		m_pHomingShot[m_HomingShotNo * m_HomingShotColumn + i].Generation(GetCircle(), enemy);
	}
	m_HomingShotRemGap = m_HomingShotGap;
	if (m_HomingShotNo < m_HomingShotCount / m_HomingShotColumn - 1)
	{
		m_HomingShotNo++;
	}
	else
	{
		m_HomingShotNo = 0;
		m_bHomingShotNow = false;
	}
}

void Lovey::BoostDash() {
	int pno = CControlManager::GetInstance().GetNo(m_PlayerNo);
	m_Speed = LOVEY_SPEED;
	m_Radius = m_FistRadius;
	m_GrazeRadius = m_FirstGraysRadius;
	m_BoostDashNo = 0;
	if (CInputManager::GetInstance().GetHold(pno, 5))
	{
		if (m_Skill > m_SuperBoostDashEnergy)
		{
			m_Speed += m_SuperBoostDashSpeed;
			m_Radius -= m_SuperBoostDashSize;
			m_GrazeRadius -= m_SuperBoostDashSize;
			m_Skill -= m_SuperBoostDashEnergy;
			m_BoostDashNo = 1;
		}
	}
	else if (CInputManager::GetInstance().GetHold(pno, 4))
	{
		if (m_Skill > m_BoostDashEnergy)
		{
			m_Speed += m_BoostDashSpeed;
			m_Radius -= m_BoostDashSize;
			m_GrazeRadius -= m_BoostDashSize;
			m_Skill -= m_BoostDashEnergy;
			m_BoostDashNo = 2;
		}
	}
}

void Lovey::Initialize(CCircle enemy) {
	m_MaxLife = LOVEY_LIFE;
	m_MaxSkill = LOVEY_SKILL;
	m_Speed = LOVEY_SPEED;

	m_Life = m_MaxLife;
	m_Skill = 0;

	m_BoostDashNo = 0;
	MachineGunInitialize();
	ChargeShotInitialize();
	ChargeLaserInitialize();
	ContinuousenEnergyShotInitialize();
	HomingShotInitialize();
}

void Lovey::TimeReduse() {
	if (CJokerSkillManager::GetInstance().CanMove(m_PlayerNo))
	{
		m_MachineGunAllRemGap = max(m_MachineGunAllRemGap - 1, 0);
		if (m_MachineGunAllRemGap == 0)
		{
			m_MachineGunRemGap = max(m_MachineGunRemGap - 1, 0);
		}
		m_ChargeShotRemGap = max(m_ChargeShotRemGap - 1, 0);
		if (!m_ChargeLaser.GetDrow())
		{
			m_ChargeLaserRemGap = max(m_ChargeLaserRemGap - 1, 0);
		}
		if (!m_bContinuousenEnergyShotNow)
		{
			m_ContinuousenEnergyShotAllRemGap = max(m_ContinuousenEnergyShotAllRemGap - 1, 0);
		}
		if (m_bContinuousenEnergyShotNow)
		{
			m_ContinuousenEnergyShotSetRemGap = max(m_ContinuousenEnergyShotSetRemGap - 1, 0);
		}
		if (m_bContinuousenEnergyShotNow && m_ContinuousenEnergyShotSetRemGap == 0)
		{
			m_ContinuousenEnergyShotRemGap = max(m_ContinuousenEnergyShotRemGap - 1, 0);
		}
		if (m_bHomingShotNow)
		{
			m_HomingShotRemGap = max(m_HomingShotRemGap - 1, 0);
		}
	}
}

void Lovey::Update(CCircle enemy) {
	TimeReduse();
	Generasion(enemy);
}

void Lovey::Generasion(CCircle enemy) {
	MachineGunGenerasion(enemy);
	ChargeShotGenerasion(enemy);
	ChargeLaserGenerasion(enemy);
	ContinuousenEnergyShotStart();
	ContinuousenEnergyShotGeneration(enemy);
	HomingShotStart();
	HomingShotGeneration(enemy);
	BoostDash();
}

void Lovey::Collision(CCircle enemy, CCircle egraze, int& damage, int& eskill) {
	int pskill = 0, dam = 0, esk = 0;
	for (int i = 0; i < m_MachineGunCount; ++i)
	{
		if (m_pMachineGun[i].Collition(enemy, egraze, pskill, dam, esk))
		{
			m_Skill += pskill;
			damage += dam;
			eskill += esk;
		}
	}
	for (int i = 0; i < m_ChargeShotCount; ++i)
	{
		if (m_pChargeShot[i].Collition(enemy, egraze, pskill, dam, esk))
		{
			m_Skill += pskill;
			damage += dam;
			eskill += esk;
		}
	}
	if (m_ChargeLaser.Collition(enemy, egraze, pskill, dam, esk))
	{
		m_Skill += pskill;
		damage += dam;
		eskill += esk;
	}
	for (int i = 0; i < m_ContinuousenEnergyShotCount; ++i)
	{
		if (m_pContinuousenEnergyShot[i].Collition(enemy, egraze, pskill, dam, esk))
		{
			m_Skill += pskill;
			damage += dam;
			eskill += esk;
		}
	}
	for (int i = 0; i < m_HomingShotCount; ++i)
	{
		if (m_pHomingShot[i].Collition(enemy, egraze, pskill, dam, esk))
		{
			m_Skill += pskill;
			damage += dam;
			eskill += esk;
		}
	}
	if (m_Skill > m_MaxSkill)
		m_Skill = m_MaxSkill;
}

void Lovey::Fly(CCircle enemy) {
	for (int i = 0; i < m_MachineGunCount; ++i)
	{
		m_pMachineGun[i].Update(GetCircle(), enemy);
	}
	for (int i = 0; i < m_ChargeShotCount; ++i)
	{
		m_pChargeShot[i].Update(GetCircle(), enemy);
	}
	m_ChargeLaser.Update(GetCircle(), enemy);
	for (int i = 0; i < m_ContinuousenEnergyShotCount; ++i)
	{
		m_pContinuousenEnergyShot[i].Update(GetCircle(), enemy);
	}
	for (int i = 0; i < m_HomingShotCount; ++i)
	{
		m_pHomingShot[i].Update(GetCircle(), enemy);
	}
}

void Lovey::Render() {
	CGraphicsUtilities::RenderCircle(GetRenderCircle(), MOF_XRGB(255, 0, 0));
	CGraphicsUtilities::RenderCircle(GetRenderGrazeCircle(), MOF_XRGB(255, 100, 100));
	for (int i = 0; i < m_MachineGunCount; ++i)
	{
		m_pMachineGun[i].Render();
	}
	for (int i = 0; i < m_ChargeShotCount; ++i)
	{
		m_pChargeShot[i].Render();
	}
	m_ChargeLaser.Render();
	for (int i = 0; i < m_ContinuousenEnergyShotCount; ++i)
	{
		m_pContinuousenEnergyShot[i].Render();
	}
	for (int i = 0; i < m_HomingShotCount; ++i)
	{
		m_pHomingShot[i].Render();
	}

	float x = CTextureManager::GetInstance().GetCharacter(0).GetWidth();
	float y = CTextureManager::GetInstance().GetCharacter(0).GetHeight();
	float scale = m_GrazeRadius / max(x, y) * 2;
	x = m_Pos.x - x * scale / 2;
	y = m_Pos.y - y * scale / 2;
	CTextureManager::GetInstance().GetCharacter(1).RenderScale(x, y, scale);
}

void Lovey::Release() {
	if (m_pMachineGun)
	{
		delete[] m_pMachineGun;
		m_pMachineGun = NULL;
	}
	if (m_pChargeShot)
	{
		delete[] m_pChargeShot;
		m_pChargeShot = NULL;
	}
	if (m_pContinuousenEnergyShot)
	{
		delete[] m_pContinuousenEnergyShot;
		m_pContinuousenEnergyShot = NULL;
	}
	if (m_pHomingShot)
	{
		delete[] m_pHomingShot;
		m_pHomingShot = NULL;
	}
}