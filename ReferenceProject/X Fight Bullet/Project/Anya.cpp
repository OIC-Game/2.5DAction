#include "Anya.h"



Anya::Anya()
{
}


Anya::~Anya()
{
}

void Anya::AnyaOrbInitialize(CCircle enemy) {
	for (int i = 0; i < ANYAORB1_COUNT; ++i)
	{
		m_AnyaOrb1[i].SetTacticsNo(0);
		m_AnyaOrb1[i].Initialize(m_PlayerNo, i);
		m_AnyaOrb1[i].Generation(GetCircle(), enemy);
	}
	for (int i = 0; i < ANYAORB2_COUNT; ++i)
	{
		m_AnyaOrb2[i].SetTacticsNo(1);
		m_AnyaOrb2[i].Initialize(m_PlayerNo, i);
		m_AnyaOrb2[i].Generation(GetCircle(), enemy);
	}
	for (int i = 0; i < ANYAORB3_COUNT; ++i)
	{
		m_AnyaOrb3[i].SetTacticsNo(2);
		m_AnyaOrb3[i].Initialize(m_PlayerNo, i);
		m_AnyaOrb3[i].Generation(GetCircle(), enemy);
	}
	for (int i = 0; i < ANYAORBSP_COUNT; ++i)
	{
		m_AnyaOrbS[i].SetTacticsNo(3);
		m_AnyaOrbS[i].Initialize(m_PlayerNo, i);
		m_AnyaOrbS[i].Generation(GetCircle(), enemy);
	}
}

#pragma region タクティクスチェンジ
void Anya::TacticsInitialize() {
	m_TacticsNo = 0;
	m_TC1Start = true;
	m_TC1End = false;
	m_TC2Start = false;
	m_TC2End = true;
	m_TC3Start = false;
	m_TC3End = true;
	m_TCSPStart = false;
	m_TCSPEnd = true;
}

void Anya::TacticsChenge() {
	int pno = CControlManager::GetInstance().GetNo(m_PlayerNo);
	if (m_TC1Start == true || m_TC2Start == true || m_TC3Start == true)
	{
		if (CInputManager::GetInstance().GetPush(pno, 5))
		{
			if (m_TacticsNo < 2)
				m_TacticsNo++;
			else
				m_TacticsNo = 0;
		}
		else if (CInputManager::GetInstance().GetPush(pno, 4))
		{
			if (m_TacticsNo > 0)
				m_TacticsNo--;
			else
				m_TacticsNo = 2;
		}
	}
}

void Anya::TacticsStart() {
	Tactics1Start();
	Tactics2Start();
	Tactics3Start();
	TacticsSPStart();
	Tactics1End();
	Tactics2End();
	Tactics3End();
	TacticsSPEnd();
}

void Anya::Tactics1Start() {
	if (m_TacticsNo != 0 || m_TC2End == false || m_TC3End == false || m_TCSPEnd == false)
	{
		m_TC1Start = false;
		return;
	}
	for (int i = 0; i < 3; ++i)
	{
		if (m_AnyaOrb1[i].GetStarted() == false)
		{
			m_AnyaOrb1[i].Start();
		}
		else
		{
			m_TC1Start = true;
		}
	}
}

void Anya::Tactics2Start() {
	if (m_TacticsNo != 1 || m_TC1End == false || m_TC3End == false || m_TCSPEnd == false)
	{
		m_TC2Start = false;
		return;
	}
	for (int i = 0; i < 5; ++i)
	{
		if (m_AnyaOrb2[i].GetStarted() == false)
		{
			m_AnyaOrb2[i].Start();
		}
		else
		{
			m_TC2Start = true;
		}
	}
}

void Anya::Tactics3Start() {
	if (m_TacticsNo != 2 || m_TC1End == false || m_TC2End == false || m_TCSPEnd == false)
	{
		m_TC3Start = false;
		return;
	}
	for (int i = 0; i < 5; ++i)
	{
		if (m_AnyaOrb3[i].GetStarted() == false)
		{
			m_AnyaOrb3[i].Start();
		}
		else
		{
			m_TC3Start = true;
		}
	}
}

void Anya::TacticsSPStart() {
	if (m_TacticsNo != 3 || m_TC1End == false || m_TC2End == false || m_TC3End == false)
	{
		m_TCSPStart = false;
		return;
	}
	for (int i = 0; i < 5; ++i)
	{
		if (m_AnyaOrbS[i].GetStarted() == false)
		{
			m_AnyaOrbS[i].Start();
		}
		else
		{
			m_TCSPStart = true;
		}
	}
}

void Anya::Tactics1End() {
	if (m_TacticsNo == 0)
	{
		m_TC1End = false;
		return;
	}
	for (int i = 0; i < 3; ++i)
	{
		if (m_AnyaOrb1[i].GetDrow())
		{
			m_AnyaOrb1[i].End();
		}
		else
		{
			m_TC1End = true;
		}
	}
}

void Anya::Tactics2End() {
	if (m_TacticsNo == 1)
	{
		m_TC2End = false;
		return;
	}
	for (int i = 0; i < 5; ++i)
	{
		if (m_AnyaOrb2[i].GetDrow() == true)
		{
			m_AnyaOrb2[i].End();
		}
		else
		{
			m_TC2End = true;
		}
	}
}

void Anya::Tactics3End() {
	if (m_TacticsNo == 2)
	{
		m_TC3End = false;
		return;
	}
	for (int i = 0; i < 5; ++i)
	{
		if (m_AnyaOrb3[i].GetDrow() == true)
		{
			m_AnyaOrb3[i].End();
		}
		else
		{
			m_TC3End = true;
		}
	}
}

void Anya::TacticsSPEnd() {
	if (m_TacticsNo == 3)
	{
		m_TCSPEnd = false;
		return;
	}
	for (int i = 0; i < 5; ++i)
	{
		if (m_AnyaOrbS[i].GetDrow() == true)
		{
			m_AnyaOrbS[i].End();
		}
		else
		{
			m_TCSPEnd = true;
		}
	}
}
#pragma endregion

void Anya::SpeedChenge() {
	if (m_TC1Start == false && m_TC2Start == false && m_TC3Start == false && m_TCSPStart == false) { return; }
	if (m_TacticsNo == 0 || m_TacticsNo == 3)
		m_Speed = ANYA_SPEED;
	else if (m_TacticsNo == 1)
		m_Speed = ANYA_SECOND_SPEED;
	else if (m_TacticsNo == 2)
		m_Speed = ANYA_THIRD_SPEED;
}

#pragma region リップルショット
void Anya::RipplesShotInitialize() {
	m_RipplesShotCount = m_RipplesShotColumn * m_RipplesShotAmount;
	m_pRipplesShot = new CRipplesShot[m_RipplesShotCount];

	for (int i = 0; i < m_RipplesShotCount; ++i)
	{
		m_pRipplesShot[i].Initialize(m_PlayerNo, 0);
	}
	m_RipplesShotNo = 0;
	m_RipplesShotRemGap = 0;
	for (int i = 0; i < RIPPLESSHOT_COUNT; ++i)
	{
		for (int j = 0; j < RIPPLESSHOT_COUNT; j++)
		{
			m_RipplesBullet1[i][j].Initialize(m_PlayerNo, 0);
			m_RipplesBullet2[i][j].Initialize(m_PlayerNo, 0);
		}
	}
	m_RipplesShotNo = 0;
}

void Anya::RipplesShotGeneration() {
	int pno = CControlManager::GetInstance().GetNo(m_PlayerNo);
	if (m_RipplesShotRemGap > 0)
	{
		return;
	}
	if (m_pRipplesShot[m_RipplesShotNo].GetDrow() == true) { return; }
	if (CInputManager::GetInstance().GetPush(pno, 1))
	{
		m_RipplesShotRemGap = m_RipplesShotGap;

		for (int i = 0; i < 3; ++i)
		{
			m_pRipplesShot[m_RipplesShotNo + i].Generation(m_AnyaOrb1[i].GetCircle(), m_AnyaOrb1[i].GetCircle());
		}

		if (m_RipplesShotNo < RIPPLESSHOT_COUNT - 4)
			m_RipplesShotNo += 3;
		else
			m_RipplesShotNo = 0;
	}
}

void Anya::RipplesShotRender() {
	for (int i = 0; i < RIPPLESSHOT_COUNT; ++i)
	{
		if (!m_pRipplesShot[i].GetDrow()) { continue; }
		for (int j = 0; j < RIPPLESSHOT_COUNT; ++j)
		{
			if (i <= j) { continue; }
			if (!m_pRipplesShot[j].GetDrow()) { continue; }
			float dx = 0;
			float dy = 0;
			float d = 0;

			float cx = 0;
			float cy = 0;

			float a = 0;
			float h = 0;

			float x1 = 0;
			float y1 = 0;
			float x2 = 0;
			float y2 = 0;

			dx = m_pRipplesShot[j].GetCircle().x - m_pRipplesShot[i].GetCircle().x;					//c1とc2のｘ差
			dy = m_pRipplesShot[j].GetCircle().y - m_pRipplesShot[i].GetCircle().y;					//c1とc2のｙ差
			d = sqrt(dx * dx + dy * dy);	//c1とc2の中心間の距離
														//円同士が重なっている
			if (d < m_pRipplesShot[i].GetRadius() + m_pRipplesShot[j].GetRadius())
			{
				//どちらかの円の中に完全に入り込んでしまっていないか
				if (d > abs(m_pRipplesShot[i].GetRadius() - m_pRipplesShot[i].GetRadius()))
				{
					//同じ大きさの円がぴったり同じ位置に無いか
					if (d != 0 || m_pRipplesShot[i].GetRadius() != m_pRipplesShot[j].GetRadius())
					{
						//２つの円はずれて重なっているので交点が2つある

						//２つの円が交差する２点を通る直線と、円の中心同士の直線の交点までの距離
						a = ((m_pRipplesShot[i].GetRadius() * m_pRipplesShot[i].GetRadius()) - (m_pRipplesShot[j].GetRadius() * m_pRipplesShot[j].GetRadius()) + (d * d)) / (2 * d);

						//・c1
						//・２つの円が交差する１点
						//・２つの円が交差する２点を通る直線と、円の中心同士の直線の交点
						//の３点がなす直角三角形の高さ
						h = sqrt(m_pRipplesShot[i].GetRadius() * m_pRipplesShot[i].GetRadius() - a * a);

						//２つの円が交差する２点を通る直線と、円の中心同士の直線の交点
						cx = m_pRipplesShot[i].GetCircle().x + a * dx / d;
						cy = m_pRipplesShot[i].GetCircle().y + a * dy / d;

						//交点１つ目
						x1 = cx + h * dy / d;
						y1 = cy - h * dx / d;

						//交点２つ目
						x2 = cx - h * dy / d;
						y2 = cy + h * dx / d;

						CCircle cir1(x1, y1, 1);
						CCircle cir2(x2, y2, 1);

						m_RipplesBullet1[i][j].Generation(cir1, cir1);
						m_RipplesBullet2[i][j].Generation(cir2, cir2);

						m_RipplesBullet1[i][j].Update(cir1, cir1);
						m_RipplesBullet2[i][j].Update(cir2, cir2);


						m_RipplesBullet1[i][j].Render();
						m_RipplesBullet2[i][j].Render();
					}
				}
			}
		}
	}
}

#pragma endregion

#pragma region グロウショット
void Anya::GrowShotInitialize() {
	m_GrowShotCount = m_GrowShotColumn * m_GrowShotAmount * m_GrowShotSetAmount;
	m_pGrowShot = new CGrowShot[m_GrowShotCount];
	for (int i = 0; i < m_GrowShotCount; ++i)
	{
		m_pGrowShot[i].Initialize(m_PlayerNo, i);
	}
	m_GrowShotNo = 0;
	m_GrowShotRemFlyNo = 0;
	m_GrowShotRemGap = 0;
	m_GrowShotRemSetGap = 0;
}

void Anya::GrowShotStart() {
	int pno = CControlManager::GetInstance().GetNo(m_PlayerNo);
	if (m_GrowShotRemFlyNo > 0) { return; }
	if (m_GrowShotRemGap > 0)
	{
		return;
	}
	if (CInputManager::GetInstance().GetHold(pno, 0))
	{
		m_GrowShotRemFlyNo = m_GrowShotFlyNo;
		m_GrowShotRemGap = m_GrowShotGap;
	}
}

void Anya::GrowShotGeneration(CCircle enemy) {
	if (m_GrowShotRemFlyNo == 0) { return; }
	if (m_GrowShotRemSetGap > 0)
	{
		return;
	}
	for (int i = 0; i < m_GrowShotColumn; ++i)
	{
		m_pGrowShot[m_GrowShotNo + i].Generation(m_AnyaOrb1[i].GetCircle(), enemy);
	}
	m_GrowShotRemFlyNo--;
	m_GrowShotRemSetGap = m_GrowShotSetGap;
	if (m_GrowShotNo < m_GrowShotCount - m_GrowShotColumn - 4)
		m_GrowShotNo += m_GrowShotColumn;
	else
		m_GrowShotNo = 0;
}
#pragma endregion

#pragma region マッハショット
void Anya::MachShotInitialize() {
	m_MachShotCount = m_MachShotColumn * m_MachShotAmount * m_MachShotSetAmount;
	m_pMachShot = new CMachShot[m_MachShotCount];
	for (int i = 0; i < m_MachShotCount; ++i)
	{
		m_pMachShot[i].Initialize(m_PlayerNo, i);
	}
	m_MachShotNo = 0;
	m_MachShotRemFlyNo = 0;
	m_MachShotRemGap = 0;
	m_MachShotRemSetGap = 0;
}

void Anya::MachShotStart() {
	int pno = CControlManager::GetInstance().GetNo(m_PlayerNo);
	if (m_MachShotRemFlyNo > 0) { return; }
	if (m_MachShotRemGap > 0)
	{
		return;
	}
	if (CInputManager::GetInstance().GetHold(pno, 0))
	{
		m_MachShotRemFlyNo = m_MachShotFlyNo;
		m_MachShotRemGap = m_MachShotGap;
	}
}

void Anya::MachShotGeneration(CCircle enemy) {
	if (m_MachShotRemFlyNo == 0) { return; }
	if (m_MachShotRemSetGap > 0)
	{
		return;
	}
	for (int i = 0; i < m_MachShotColumn; ++i)
	{
		m_pMachShot[m_MachShotNo + i].Generation(m_AnyaOrb2[4].GetCircle(), enemy);
	}
	m_MachShotRemFlyNo--;
	m_MachShotRemSetGap = m_MachShotSetGap;
	if (m_MachShotNo < m_MachShotCount - 4)
		m_MachShotNo += 3;
	else
		m_MachShotNo = 0;
}
#pragma endregion

#pragma region ソニックビーム
void Anya::SonicBeamInitialize() {
	m_pSonicBeam = new CSonicBeam[m_SonicBeamCount];
	for (int i = 0; i < m_SonicBeamCount; ++i)
	{
		m_pSonicBeam[i].Initialize(m_PlayerNo, i);
	}
	m_SonicBeamNo = 0;
	m_SonicBeamRemGap = 0;
}

void Anya::SonicBeamGeneration(CCircle enemy) {
	int pno = CControlManager::GetInstance().GetNo(m_PlayerNo);
	if (m_SonicBeamRemGap > 0)
	{
		return;
	}
	if (m_pSonicBeam[m_SonicBeamNo].GetRadius() > 0) { return; }
	if (CInputManager::GetInstance().GetPush(pno, 1))
	{
		m_pSonicBeam[m_SonicBeamNo].Generation(m_AnyaOrb2[4].GetCircle(), enemy);
		m_SonicBeamRemGap = m_SonicBeamGap;
		if (m_SonicBeamNo < m_SonicBeamCount - 1)
			m_SonicBeamNo++;
		else
			m_SonicBeamNo = 0;
	}
}
#pragma endregion

#pragma region エクスプロージョンショット
void Anya::ExplosionShotInitialize() {
	m_ExplosionShotCount = m_ExplosionShotColumn * m_ExplosionShotAmount;
	m_pExplosionShot = new CExplosionShot[m_ExplosionShotCount];
	for (int i = 0; i < m_ExplosionShotCount; ++i)
	{
		m_pExplosionShot[i].Initialize(m_PlayerNo, i);
	}
	m_ExplosionShotNo = 0;
	m_ExplosionShotRemGap = 0;
}

void Anya::ExplosionShotGeneration(CCircle enemy) {
	int pno = CControlManager::GetInstance().GetNo(m_PlayerNo);
	if (m_ExplosionShotRemGap > 0)
	{
		return;
	}
	if (CInputManager::GetInstance().GetHold(pno, 0))
	{
		for (int i = 0; i < m_ExplosionShotColumn; ++i)
		{
			m_pExplosionShot[m_ExplosionShotNo + i].Generation(m_AnyaOrb3[i].GetCircle(), enemy);
		}
		m_ExplosionShotRemGap = m_ExplosionShotGap;
		if (m_ExplosionShotNo < m_ExplosionShotCount - m_ExplosionShotColumn - 1)
			m_ExplosionShotNo += m_ExplosionShotColumn;
		else
			m_ExplosionShotNo = 0;
	}
}

#pragma endregion

#pragma region ウェーブショット
void Anya::WaveShotInitialize() {
	m_WaveShotCount = m_WaveShotColumn * m_WaveShotAmount;
	m_pWaveShot = new CWaveShot[m_WaveShotCount];
	for (int i = 0; i < m_WaveShotCount; ++i)
	{
		m_pWaveShot[i].Initialize(m_PlayerNo, i);
	}
	m_WaveShotNo = 0;
	m_WaveShotRemGap = 0;
}

void Anya::WaveShotGeneration(CCircle enemy) {
	int pno = CControlManager::GetInstance().GetNo(m_PlayerNo);
	if (m_WaveShotRemGap > 0)
	{
		return;
	}
	if (CInputManager::GetInstance().GetPush(pno, 1))
	{
		for (int i = 0; i < m_WaveShotColumn; ++i)
		{
			m_pWaveShot[m_WaveShotNo + i].Generation(m_AnyaOrb3[i].GetCircle(), enemy);
		}
		m_WaveShotRemGap = m_WaveShotGap;
		if (m_WaveShotNo < m_SonicBeamCount - m_WaveShotColumn - 1)
			m_WaveShotNo += 2;
		else
			m_WaveShotNo = 0;
	}
}

#pragma endregion

#pragma region レーザーダンス
void Anya::LaserDanceInitialize() {
	m_pLaserDance = new CLaserDance[m_LaserDanceCount];
	for (int i = 0; i < m_LaserDanceCount; ++i)
	{
		m_pLaserDance[i].Initialize(m_PlayerNo, i);
	}
	m_LaserDanceRemGap = 0;
	m_bLaserDanceNow = false;
	m_bLaserDanceSet = false;
}

void Anya::LaserDanceGeneration(CCircle enemy) {
	int pno = CControlManager::GetInstance().GetNo(m_PlayerNo);
	if (m_bLaserDanceNow || m_bHomingGunNow == true || m_ChaosRipplesShotNow == true) { return; }
	if (CInputManager::GetInstance().GetPush(pno, 2))
	{
		if (!m_bLaserDanceSet)
		{
			if (m_Skill >= ANYA_SKILL / 3)
			{
				m_Skill -= ANYA_SKILL / 6;
				m_BeforeTCNo = m_TacticsNo;
				m_TacticsNo = 3;
				m_bLaserDanceSet = true;
			}
		}
	}
	if (m_TCSPStart && m_bLaserDanceSet)
	{
		m_bLaserDanceSet = false;
		m_bLaserDanceNow = true;
		for (int i = 0; i < m_LaserDanceCount; ++i)
		{
			m_pLaserDance[i].Generation(m_AnyaOrbS[i].GetCircle(), enemy);
		}
	}
}

void Anya::LaserDanceEnd() {
	if (!m_bLaserDanceNow) { return; }
	if (m_pLaserDance[0].GetEnd())
	{
		m_TacticsNo = m_BeforeTCNo;
		m_bLaserDanceNow = false;
	}
}

#pragma endregion

#pragma region ホーミングガン
void Anya::HomingGunInitialize() {
	m_HomingGunCount = m_HomingGunColumn * m_HomingGunAmount * m_HomingGunSetAmount;
	m_pHomingGun = new CHomingGun[m_HomingGunCount];
	for (int i = 0; i < m_HomingGunCount; ++i)
	{
		m_pHomingGun[i].Initialize(m_PlayerNo, i);
	}
	m_HomingGunNo = 0;
	m_HomingGunRemGap = 0;
	m_bHomingGunNow = false;
	m_bHomingGunSet = false;
	m_HomingGunSetNo = 0;
}

void Anya::HomingGunStart() {
	int pno = CControlManager::GetInstance().GetNo(m_PlayerNo);
	if (m_bLaserDanceNow || m_bHomingGunNow || m_ChaosRipplesShotNow) { return; }
	if (CInputManager::GetInstance().GetPush(pno, 3))
	{
		if (!m_bHomingGunSet)
		{
			if (m_Skill >= ANYA_SKILL / 3 * 2)
			{
				m_Skill -= ANYA_SKILL / 3;
				m_BeforeTCNo = m_TacticsNo;
				m_TacticsNo = 3;
				m_bHomingGunSet = true;
			}
		}
	}
	if (m_TCSPStart && m_bHomingGunSet)
	{
		m_bHomingGunSet = false;
		m_bHomingGunNow = true;
		m_HomingGunNo = 0;
	}
}

void Anya::HomingGunGeneration(CCircle enemy) {
	if (!m_bHomingGunNow) { return; }
	if (m_HomingGunRemSetGap > 0)
	{
		return;
	}
	if (m_HomingGunRemGap > 0)
	{
		return;
	}
	if (m_HomingGunNo < m_HomingGunCount / m_HomingGunColumn)
	{
		for (int i = 0; i < m_HomingGunColumn; ++i)
		{
			m_pHomingGun[m_HomingGunNo * m_HomingGunColumn + i].Generation(m_AnyaOrbS[i].GetCircle(), enemy);
		}
		m_HomingGunRemGap = m_HomingGunGap;
		m_HomingGunNo++;
		if (m_HomingGunSetNo < m_HomingGunAmount - 1)
			m_HomingGunSetNo++;
		else
		{
			m_HomingGunSetNo = 0;
			m_HomingGunRemSetGap = m_HomingGunSetGap;
		}
	}
	else
	{
		m_TacticsNo = m_BeforeTCNo;
		m_bHomingGunNow = false;
	}
}
#pragma endregion

#pragma region カオスリップル
void Anya::ChaosRipplesShotInitialize() {
	m_ChaosRipplesShotCount = m_ChaosRipplesShotColumn * m_ChaosRipplesShotAmount;
	m_pChaosRipplesShot = new CRipplesShot[m_ChaosRipplesShotCount];
	for (int i = 0; i < m_ChaosRipplesShotCount; ++i)
	{
		m_pChaosRipplesShot[i].Initialize(m_PlayerNo, i);
	}
	m_ChaosRipplesShotNo = 0;
	m_ChaosRipplesShotRemGap = 0;
	m_ChaosRipplesShotSet = false;
	m_ChaosRipplesShotNow = false;
	for (int i = 0; i < m_ChaosRipplesShotCount; ++i)
	{
		for (int j = 0; j < m_ChaosRipplesShotCount; j++)
		{
			m_ChaosRipplesBullet1[i][j].Initialize(m_PlayerNo, 0);
			m_ChaosRipplesBullet2[i][j].Initialize(m_PlayerNo, 0);
		}
	}
}

void Anya::ChaosRipplesShotStart() {
	int pno = CControlManager::GetInstance().GetNo(m_PlayerNo);
	if (m_bLaserDanceNow || m_bHomingGunNow || m_ChaosRipplesShotNow) { return; }
	if (CInputManager::GetInstance().GetPush(pno, 6))
	{
		if (m_ChaosRipplesShotSet == false)
		{
			if (m_Skill >= ANYA_SKILL)
			{
				m_Skill -= ANYA_SKILL / 2;
				m_BeforeTCNo = m_TacticsNo;
				m_TacticsNo = 3;
				m_ChaosRipplesShotSet = true;
			}
		}
	}
	if (m_TCSPStart == true && m_ChaosRipplesShotSet == true)
	{
		m_ChaosRipplesShotSet = false;
		m_ChaosRipplesShotNow = true;
		m_ChaosRipplesShotNo = 0;
	}
}

void Anya::ChaosRipplesShotGeneration(CCircle enemy) {
	if (!m_ChaosRipplesShotNow) { return; }
	if (m_ChaosRipplesShotRemGap > 0)
	{
		return;
	}
	if (m_ChaosRipplesShotNo < m_ChaosRipplesShotCount / m_ChaosRipplesShotColumn)
	{
		for (int i = 0; i < m_ChaosRipplesShotColumn; ++i)
		{
			m_pChaosRipplesShot[m_ChaosRipplesShotNo * m_ChaosRipplesShotColumn + i].Generation(m_AnyaOrbS[i].GetCircle(), enemy);
		}
		m_ChaosRipplesShotRemGap = m_ChaosRipplesShotGap;

		m_ChaosRipplesShotNo++;
	}
	else
	{
		m_TacticsNo = m_BeforeTCNo;
		m_ChaosRipplesShotNow = false;
	}
}

void Anya::ChaosRipplesShotRender() {
	for (int i = 0; i < m_ChaosRipplesShotCount; ++i)
	{
		if (!m_pChaosRipplesShot[i].GetDrow()) { continue; }
		for (int j = 0; j < m_ChaosRipplesShotCount; ++j)
		{
			if (i <= j) { continue; }
			if (!m_pChaosRipplesShot[j].GetDrow()) { continue; }
			float dx = 0;
			float dy = 0;
			float d = 0;

			float cx = 0;
			float cy = 0;

			float a = 0;
			float h = 0;

			float x1 = 0;
			float y1 = 0;
			float x2 = 0;
			float y2 = 0;

			dx = m_pChaosRipplesShot[j].GetCircle().x - m_pChaosRipplesShot[i].GetCircle().x;					//c1とc2のｘ差
			dy = m_pChaosRipplesShot[j].GetCircle().y - m_pChaosRipplesShot[i].GetCircle().y;					//c1とc2のｙ差
			d = sqrt(dx * dx + dy * dy);	//c1とc2の中心間の距離
														//円同士が重なっている
			if (d < m_pChaosRipplesShot[i].GetRadius() + m_pChaosRipplesShot[j].GetRadius())
			{
				//どちらかの円の中に完全に入り込んでしまっていないか
				if (d > abs(m_pChaosRipplesShot[i].GetRadius() - m_pChaosRipplesShot[i].GetRadius()))
				{
					//同じ大きさの円がぴったり同じ位置に無いか
					if (d != 0 || m_pChaosRipplesShot[i].GetRadius() != m_pChaosRipplesShot[j].GetRadius())
					{
						//２つの円はずれて重なっているので交点が2つある

						//２つの円が交差する２点を通る直線と、円の中心同士の直線の交点までの距離
						a = ((m_pChaosRipplesShot[i].GetRadius() * m_pChaosRipplesShot[i].GetRadius()) - (m_pChaosRipplesShot[j].GetRadius() * m_pChaosRipplesShot[j].GetRadius()) + (d * d)) / (2 * d);

						//・c1
						//・２つの円が交差する１点
						//・２つの円が交差する２点を通る直線と、円の中心同士の直線の交点
						//の３点がなす直角三角形の高さ
						h = sqrt(m_pChaosRipplesShot[i].GetRadius() * m_pChaosRipplesShot[i].GetRadius() - a * a);

						//２つの円が交差する２点を通る直線と、円の中心同士の直線の交点
						cx = m_pChaosRipplesShot[i].GetCircle().x + a * dx / d;
						cy = m_pChaosRipplesShot[i].GetCircle().y + a * dy / d;

						//交点１つ目
						x1 = cx + h * dy / d;
						y1 = cy - h * dx / d;

						//交点２つ目
						x2 = cx - h * dy / d;
						y2 = cy + h * dx / d;

						CCircle cir1(x1, y1, 1);
						CCircle cir2(x2, y2, 1);

						m_ChaosRipplesBullet1[i][j].Generation(cir1, cir1);
						m_ChaosRipplesBullet2[i][j].Generation(cir2, cir2);

						m_ChaosRipplesBullet1[i][j].Update(cir1, cir1);
						m_ChaosRipplesBullet2[i][j].Update(cir2, cir2);

						m_ChaosRipplesBullet1[i][j].Render();
						m_ChaosRipplesBullet2[i][j].Render();
					}
				}
			}
		}
	}
}

#pragma endregion

void Anya::Initialize(CCircle enemy) {
	m_MaxLife = ANYA_LIFE;
	m_MaxSkill = ANYA_SKILL;
	m_Speed = ANYA_SPEED;

	m_Life = m_MaxLife;
	m_Skill = 0;


	TacticsInitialize();
	AnyaOrbInitialize(enemy);
	RipplesShotInitialize();
	GrowShotInitialize();
	MachShotInitialize();
	SonicBeamInitialize();
	ExplosionShotInitialize();
	WaveShotInitialize();
	LaserDanceInitialize();
	HomingGunInitialize();
	ChaosRipplesShotInitialize();
	/*
	*/
}

void Anya::Update(CCircle enemy) {
	TimeReduse();
	Generation(enemy);
}

void Anya::TimeReduse() {
	if (CJokerSkillManager::GetInstance().CanMove(m_PlayerNo))
	{
		m_RipplesShotRemGap = max(m_RipplesShotRemGap - 1, 0);
		if (m_GrowShotRemFlyNo == 0)
		{
			m_GrowShotRemGap = max(m_GrowShotRemGap - 1, 0);
		}
		if (m_GrowShotRemFlyNo != 0)
		{
			m_GrowShotRemSetGap = max(m_GrowShotRemSetGap - 1, 0);
		}
		if (m_MachShotRemFlyNo == 0)
		{
			m_MachShotRemGap = max(m_MachShotRemGap - 1, 0);
		}
		if (m_MachShotRemFlyNo != 0)
		{
			m_MachShotRemSetGap = max(m_MachShotRemSetGap - 1, 0);
		}
		m_SonicBeamRemGap = max(m_SonicBeamRemGap - 1, 0);
		m_ExplosionShotRemGap = max(m_ExplosionShotRemGap - 1, 0);
		m_WaveShotRemGap = max(m_WaveShotRemGap - 1, 0);
		if (m_bHomingGunNow)
		{
			m_HomingGunRemSetGap = max(m_HomingGunRemSetGap - 1, 0);
		}
		if (m_HomingGunRemSetGap == 0)
		{
			m_HomingGunRemGap = max(m_HomingGunRemGap - 1, 0);
		}
		if (m_ChaosRipplesShotNow)
		{
			m_ChaosRipplesShotRemGap = max(m_ChaosRipplesShotRemGap - 1, 0);
		}
	}
}

void Anya::Generation(CCircle enemy) {
	TacticsChenge();
	TacticsStart();
	SpeedChenge();
	if (m_TC1Start == true)
	{
		RipplesShotGeneration();
		GrowShotStart();
		GrowShotGeneration(enemy);
	}
	else if (m_TC2Start == true)
	{
		MachShotStart();
		MachShotGeneration(enemy);
		SonicBeamGeneration(enemy);
	}
	else if (m_TC3Start == true)
	{
		ExplosionShotGeneration(enemy);
		WaveShotGeneration(enemy);
	}
	LaserDanceGeneration(enemy);
	LaserDanceEnd();
	HomingGunStart();
	HomingGunGeneration(enemy);
	ChaosRipplesShotStart();
	ChaosRipplesShotGeneration(enemy);
}

void Anya::Collision(CCircle enemy, CCircle egraze, int& damage, int& eskill) {
	int pskill = 0, dam = 0, esk = 0;
	for (int i = 0; i < RIPPLESSHOT_COUNT; ++i)
	{
		if (!m_pRipplesShot[i].GetDrow()) { continue; }
		for (int j = 0; j < RIPPLESSHOT_COUNT; j++)
		{
			if (i <= j) { continue; }
			if (!m_pRipplesShot[j].GetDrow()) { continue; }
			if (m_RipplesBullet1[i][j].Collition(enemy, egraze, pskill, dam, esk))
			{
				m_Skill += pskill;
				damage += dam;
				eskill += esk;
			}
			if (m_RipplesBullet2[i][j].Collition(enemy, egraze, pskill, dam, esk))
			{
				m_Skill += pskill;
				damage += dam;
				eskill += esk;
			}
		}
	}
	for (int i = 0; i < m_GrowShotCount; ++i)
	{
		if (m_pGrowShot[i].Collition(enemy, egraze, pskill, dam, esk))
		{
			m_Skill += pskill;
			damage += dam;
			eskill += esk;
		}
	}
	for (int i = 0; i < m_MachShotCount; ++i)
	{
		if (m_pMachShot[i].Collition(enemy, egraze, pskill, dam, esk))
		{
			m_Skill += pskill;
			damage += dam;
			eskill += esk;
		}
	}
	for (int i = 0; i < m_SonicBeamCount; ++i)
	{
		if (m_pSonicBeam[i].Collition(enemy, egraze, pskill, dam, esk))
		{
			m_Skill += pskill;
			damage += dam;
			eskill += esk;
		}
	}
	for (int i = 0; i < m_ExplosionShotCount; ++i)
	{
		if (m_pExplosionShot[i].Collition(enemy, egraze, pskill, dam, esk))
		{
			m_Skill += pskill;
			damage += dam;
			eskill += esk;
		}
	}
	for (int i = 0; i < m_WaveShotCount; ++i)
	{
		if (m_pWaveShot[i].Collition(enemy, egraze, pskill, dam, esk))
		{
			m_Skill += pskill;
			damage += dam;
			eskill += esk;
		}
	}
	for (int i = 0; i < m_LaserDanceCount; ++i)
	{
		if (m_pLaserDance[i].Collition(enemy, egraze, pskill, dam, esk))
		{
			m_Skill += pskill;
			damage += dam;
			eskill += esk;
		}
	}
	for (int i = 0; i < m_HomingGunCount; ++i)
	{
		if (m_pHomingGun[i].Collition(enemy, egraze, pskill, dam, esk))
		{
			m_Skill += pskill;
			damage += dam;
			eskill += esk;
		}
	}
	for (int i = 0; i < m_ChaosRipplesShotCount; ++i)
	{
		if (!m_pChaosRipplesShot[i].GetDrow()) { continue; }
		for (int j = 0; j < m_ChaosRipplesShotCount; j++)
		{
			if (i <= j) { continue; }
			if (!m_pChaosRipplesShot[j].GetDrow()) { continue; }
			if (m_ChaosRipplesBullet1[i][j].Collition(enemy, egraze, pskill, dam, esk))
			{
				m_Skill += pskill;
				damage += dam;
				eskill += esk;
			}
			if (m_ChaosRipplesBullet2[i][j].Collition(enemy, egraze, pskill, dam, esk))
			{
				m_Skill += pskill;
				damage += dam;
				eskill += esk;
			}
		}
	}
	if (m_Skill > m_MaxSkill)
		m_Skill = m_MaxSkill;
}

void Anya::Fly(CCircle enemy) {
	for (int i = 0; i < ANYAORB1_COUNT; ++i)
	{
		m_AnyaOrb1[i].Update(GetCircle(), enemy);
	}
	for (int i = 0; i < ANYAORB2_COUNT; ++i)
	{
		m_AnyaOrb2[i].Update(GetCircle(), enemy);
	}
	for (int i = 0; i < ANYAORB3_COUNT; ++i)
	{
		m_AnyaOrb3[i].Update(GetCircle(), enemy);
	}
	for (int i = 0; i < ANYAORBSP_COUNT; ++i)
	{
		m_AnyaOrbS[i].Update(GetCircle(), enemy);
	}
	for (int i = 0; i < m_RipplesShotCount; ++i)
	{
		m_pRipplesShot[i].Update(GetCircle(), enemy);
	}
	for (int i = 0; i < m_GrowShotCount; ++i)
	{
		m_pGrowShot[i].Update(GetCircle(), enemy);
	}
	for (int i = 0; i < m_MachShotCount; ++i)
	{
		m_pMachShot[i].Update(GetCircle(), enemy);
	}
	for (int i = 0; i < m_SonicBeamCount; ++i)
	{
		m_pSonicBeam[i].Update(GetCircle(), enemy);
	}
	for (int i = 0; i < m_ExplosionShotCount; ++i)
	{
		m_pExplosionShot[i].Update(GetCircle(), enemy);
	}
	for (int i = 0; i < m_WaveShotCount; ++i)
	{
		m_pWaveShot[i].Update(GetCircle(), enemy);
	}
	for (int i = 0; i < m_LaserDanceCount; ++i)
	{
		m_pLaserDance[i].Update(m_AnyaOrbS[i].GetCircle(), enemy);
	}
	for (int i = 0; i < m_HomingGunCount; ++i)
	{
		m_pHomingGun[i].Update(GetCircle(), enemy);
	}
	for (int i = 0; i < m_ChaosRipplesShotCount; ++i)
	{
		m_pChaosRipplesShot[i].Update(GetCircle(), enemy);
	}
}

void Anya::Render() {
	CGraphicsUtilities::RenderCircle(GetRenderCircle(), MOF_XRGB(255, 0, 0));
	CGraphicsUtilities::RenderCircle(GetRenderGrazeCircle(), MOF_XRGB(255, 100, 100));
	for (int i = 0; i < ANYAORB1_COUNT; ++i)
	{
		m_AnyaOrb1[i].Render();
	}
	for (int i = 0; i < ANYAORB2_COUNT; ++i)
	{
		m_AnyaOrb2[i].Render();
	}
	for (int i = 0; i < ANYAORB3_COUNT; ++i)
	{
		m_AnyaOrb3[i].Render();
	}
	for (int i = 0; i < ANYAORBSP_COUNT; ++i)
	{
		m_AnyaOrbS[i].Render();
	}
	for (int i = 0; i < m_RipplesShotCount; ++i)
	{
		m_pRipplesShot[i].Render();
	}
	RipplesShotRender();
	for (int i = 0; i < m_GrowShotCount; ++i)
	{
		m_pGrowShot[i].Render();
	}
	for (int i = 0; i < m_MachShotCount; ++i)
	{
		m_pMachShot[i].Render();
	}
	for (int i = 0; i < m_SonicBeamCount; ++i)
	{
		m_pSonicBeam[i].Render();
	}
	for (int i = 0; i < m_ExplosionShotCount; ++i)
	{
		m_pExplosionShot[i].Render();
	}
	for (int i = 0; i < m_WaveShotCount; ++i)
	{
		m_pWaveShot[i].Render();
	}
	for (int i = 0; i < m_LaserDanceCount; ++i)
	{
		m_pLaserDance[i].Render();
	}
	for (int i = 0; i < m_HomingGunCount; ++i)
	{
		m_pHomingGun[i].Render();
	}
	for (int i = 0; i < m_ChaosRipplesShotCount; ++i)
	{
		m_pChaosRipplesShot[i].Render();
	}
	ChaosRipplesShotRender();

	float x = CTextureManager::GetInstance().GetCharacter(0).GetWidth();
	float y = CTextureManager::GetInstance().GetCharacter(0).GetHeight();
	float scale = m_GrazeRadius / max(x, y) * 2;
	x = m_Pos.x - x * scale / 2;
	y = m_Pos.y - y * scale / 2;
	CTextureManager::GetInstance().GetCharacter(0).RenderScale(x, y, scale);

}

void Anya::Release() {
	if (m_pGrowShot)
	{
		delete[] m_pGrowShot;
		m_pGrowShot = NULL;
	}
	if (m_pRipplesShot)
	{
		delete[] m_pRipplesShot;
		m_pRipplesShot = NULL;
	}
	if (m_pMachShot)
	{
		delete[] m_pMachShot;
		m_pMachShot = NULL;
	}
	if (m_pSonicBeam)
	{
		delete[] m_pSonicBeam;
		m_pSonicBeam = NULL;
	}
	if (m_pExplosionShot)
	{
		delete[] m_pExplosionShot;
		m_pExplosionShot = NULL;
	}
	if (m_pWaveShot)
	{
		delete[] m_pWaveShot;
		m_pWaveShot = NULL;
	}
	if (m_pLaserDance)
	{
		delete[] m_pLaserDance;
		m_pLaserDance = NULL;
	}
	if (m_pHomingGun)
	{
		delete[] m_pHomingGun;
		m_pHomingGun = NULL;
	}
	if (m_pChaosRipplesShot)
	{
		delete[] m_pChaosRipplesShot;
		m_pChaosRipplesShot = NULL;
	}
}