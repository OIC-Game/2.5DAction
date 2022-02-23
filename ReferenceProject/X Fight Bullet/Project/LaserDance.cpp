#include "LaserDance.h"



CLaserDance::CLaserDance()
{
}


CLaserDance::~CLaserDance()
{
}

void CLaserDance::Initialize(int playerno, int posno) {
	m_PlayerNo = playerno;
	m_BStatus.bLaser = 1;
	m_BStatus.Damage = 15;
	m_BStatus.Speed = 80;
	m_BStatus.FirstRadius = 10;
	m_BStatus.GetSkillPoint  = 4;
	m_BStatus.GiveSkillPoint  = 8;
	m_BStatus.NotDamageTime  = 5;
	m_PhaseNo = 0;
	m_bEnd = false;
}

void CLaserDance::Generation(CCircle player, CCircle enemy) {
	m_BStatus.bDrow = true;
	m_BStatus.Radius  = m_BStatus.FirstRadius;
	m_PhaseNo = m_MaxPhaseNo;
	m_BStatus.PerRemTime = m_PerTimeList[m_PhaseNo - 1];
	m_WaitRemTime = 0;
	m_BStatus.Dir = (player.x < enemy.x) ? 0 : 180;
	m_BStatus.StartPos.x = player.x;
	m_BStatus.StartPos.y = player.y;
	m_BStatus.Pos.x = (player.x < enemy.x) ? player.x + m_BStatus.Radius  : player.x - m_BStatus.Radius ;
	m_BStatus.Pos.y = player.y;
	m_bEnd = false;
}

void CLaserDance::Update(CCircle player, CCircle enemy) {
	if (!m_BStatus.bDrow && m_PhaseNo == 0) { return; }
	int slow = CJokerSkillManager::GetInstance().GetSlow(m_PlayerNo);
	if (m_BStatus.bDrow)
	{
		m_BStatus.Move.x = cos(MOF_ToRadian(m_BStatus.Dir)) * m_BStatus.Speed;
		m_BStatus.Move.y = sin(MOF_ToRadian(m_BStatus.Dir)) * m_BStatus.Speed;

		m_BStatus.Pos.x += m_BStatus.Move.x / slow;
		m_BStatus.Pos.y = player.y;
		m_BStatus.StartPos.x = player.x;
		m_BStatus.StartPos.y = player.y;
	}

	if (CJokerSkillManager::GetInstance().CanMove(m_PlayerNo))
	{
		m_WaitRemTime = max(m_WaitRemTime - 1, 0);
		m_BStatus.PerRemTime = max(m_BStatus.PerRemTime - 1, 0);
	}

	if (m_WaitRemTime > 0)
	{
		return;
	}
	else if (!m_BStatus.bDrow)
	{
		CSoundManager::GetInstance().GetSE(0).Play();
		m_BStatus.bDrow = true;
		m_BStatus.Radius  = m_BStatus.FirstRadius;
		m_BStatus.PerRemTime = m_PerTimeList[m_PhaseNo - 1];
	}
	if (m_BStatus.PerRemTime > 0)
	{
	}
	else
	{
		if (m_BStatus.Radius  > 0)
		{
			m_BStatus.Radius -= (float)(1 / slow);
		}
		else
		{
			m_BStatus.bDrow = false;
			m_WaitRemTime = m_WaitTime;
			m_PhaseNo--;
			m_BStatus.StartPos.x = player.x;
			m_BStatus.StartPos.y = player.y;
			m_BStatus.Pos.x = (player.x < enemy.x) ? player.x + m_BStatus.Radius  : player.x - m_BStatus.Radius ;
			m_BStatus.Pos.y = player.y;
		}
	}
	if (m_PhaseNo == 0 && m_BStatus.Radius  == 0)
	{
		m_PhaseNo = 0;
		m_BStatus.bDrow = false;
		m_bEnd = true;
	}
}

void CLaserDance::Render() {
	if (!m_BStatus.bDrow) { return; }
		CGraphicsUtilities::RenderFillRect(GetRenderRect(), (m_PlayerNo == 0) ? MOF_COLOR_WHITE : MOF_COLOR_YELLOW);
		CGraphicsUtilities::RenderFillCircle(GetStartPosRenderCircle(), (m_PlayerNo == 0) ? MOF_COLOR_WHITE : MOF_COLOR_YELLOW);
		CGraphicsUtilities::RenderFillCircle(GetEndPosRenderCircle(), (m_PlayerNo == 0) ? MOF_COLOR_WHITE : MOF_COLOR_YELLOW);
}

void CLaserDance::Release() {
}