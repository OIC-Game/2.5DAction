#include "SonicBeam.h"

CSonicBeam::CSonicBeam()
{
}


CSonicBeam::~CSonicBeam()
{
}

void CSonicBeam::Initialize(int playerno, int posno) {
	m_PlayerNo = playerno;
	m_BStatus.bLaser = 1;
	m_BStatus.Damage = 60;
	m_BStatus.Speed = 50;
	m_BStatus.FirstRadius = 15;
	m_BStatus.GetSkillPoint = 20;
	m_BStatus.GiveSkillPoint = 8;
	m_BStatus.PerTime = 100;
	m_BStatus.NotDamageTime = 20;
}

void CSonicBeam::Generation(CCircle player, CCircle enemy) {
	m_BStatus.bDrow = true;
	m_BStatus.Radius = m_BStatus.FirstRadius;
	m_BStatus.PerRemTime = m_BStatus.PerTime;
	m_WaitRemTime = m_WaitTime;
	m_BStatus.Dir = (player.x < enemy.x) ? 0 : 180;
	m_BStatus.StartPos.x = player.x;
	m_BStatus.StartPos.y = player.y;
	m_BStatus.Pos.x = (player.x < enemy.x) ? player.x + m_BStatus.Radius : player.x - m_BStatus.Radius;
	m_BStatus.Pos.y = player.y;
}

void CSonicBeam::Update(CCircle player, CCircle enemy) {
	if (!m_BStatus.bDrow) { return; }
	int slow = CJokerSkillManager::GetInstance().GetSlow(m_PlayerNo);

	if (CJokerSkillManager::GetInstance().CanMove(m_PlayerNo))
	{
		m_WaitRemTime = max(m_WaitRemTime - 1, 0);
		m_BStatus.PerRemTime = max(m_BStatus.PerRemTime - 1, 0);
	}

	if (m_WaitRemTime > 0)
	{
		if (m_WaitRemTime == 1)
		{
			CSoundManager::GetInstance().GetSE(0).Play();
		}
		return;
	}
	m_BStatus.Move.x = cos(MOF_ToRadian(m_BStatus.Dir)) * m_BStatus.Speed;
	m_BStatus.Pos.x += m_BStatus.Move.x / slow;
	if (m_BStatus.PerRemTime > 0)
	{
		return;
	}
	if (m_BStatus.Radius > 0)
		m_BStatus.Radius -= (float)(1 / slow);
	else
		m_BStatus.bDrow = false;
}

void CSonicBeam::Render() {
	if (!m_BStatus.bDrow) { return; }
	CGraphicsUtilities::RenderFillRect(GetRenderRect(), (m_PlayerNo == 0) ? MOF_COLOR_WHITE : MOF_COLOR_YELLOW);
	CGraphicsUtilities::RenderFillCircle(GetStartPosRenderCircle(), (m_PlayerNo == 0) ? MOF_COLOR_WHITE : MOF_COLOR_YELLOW);
	CGraphicsUtilities::RenderFillCircle(GetEndPosRenderCircle(), (m_PlayerNo == 0) ? MOF_COLOR_WHITE : MOF_COLOR_YELLOW);
}

void CSonicBeam::Release() {

}