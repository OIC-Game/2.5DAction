#include "AnyaOrb.h"



CAnyaOrb::CAnyaOrb()
{
}


CAnyaOrb::~CAnyaOrb()
{
}

void CAnyaOrb::Initialize(int playerno, int posno) {
	m_PlayerNo = playerno;
	m_BStatus.PosNo = posno;
	m_Len = 0;
	m_BStatus.Radius = 15;	
}

void CAnyaOrb::Update(CCircle player, CCircle enemy) {
	if (m_TacticsNo == 0 || m_TacticsNo == 3)
		m_BStatus.Dir++;
	m_BStatus.Pos.x = player.x + cos(MOF_ToRadian(m_BStatus.Dir)) * m_Len;
	m_BStatus.Pos.y = player.y + sin(MOF_ToRadian(m_BStatus.Dir)) * m_Len;
	if (m_Started== false) { return; }
	if (m_TacticsNo == 3)
	{
		if (m_PhaseNo == 0)
		{
			if (m_Len < m_TacticsSP_Len[0])
				m_Len++;
			else
				m_PhaseNo = 1;
		}
		else if (m_PhaseNo == 1)
		{
			if (m_Len > m_TacticsSP_Len[4])
				m_Len--;
			else
				m_PhaseNo = 0;
		}
	}
}

void CAnyaOrb::Generation(CCircle player, CCircle enemy) {
	switch (m_TacticsNo)
	{
	case 0:
		m_BStatus.Dir = m_Tactics1_Dir[m_BStatus.PosNo];
		m_GoalLen = m_Tactics1_Len[m_BStatus.PosNo];
		m_Len = m_GoalLen;
		m_BStatus.bDrow = true;
		m_Started= true;
		break;
	case 1:
		m_BStatus.Dir = m_Tactics2_Dir[m_BStatus.PosNo];
		m_GoalLen = m_Tactics2_Len[m_BStatus.PosNo];
		m_BStatus.bDrow = false;
		m_Started= false;
		break;
	case 2:
		m_BStatus.Dir = m_Tactics3_Dir[m_BStatus.PosNo];
		m_GoalLen = m_Tactics3_Len[m_BStatus.PosNo];
		m_BStatus.bDrow = false;
		m_Started= false;
		break;
	case 3:
		m_BStatus.Dir = m_TacticsSP_Dir[m_BStatus.PosNo];
		m_GoalLen = m_TacticsSP_Len[m_BStatus.PosNo];
		m_BStatus.bDrow = false;
		m_Started= false;
		break;
	default:
		break;
	}

	m_BStatus.Dir += (player.x < enemy.x) ? 0 : 180;
}

void CAnyaOrb::Start() {
	if (m_Started== true) { return; }
	m_BStatus.bDrow = true;
	m_PhaseNo = 0;
	if (m_Len < m_GoalLen)
		m_Len++;
	else
	{
		m_Len = m_GoalLen;
		m_Started= true;
	}
}

void CAnyaOrb::End() {
	if (m_BStatus.bDrow == false) { return; }
	m_Started= false;
	if (m_Len > 0)
		m_Len--;
	else
	{
		m_Len = 0;
		m_BStatus.bDrow = false;
	}
}

void CAnyaOrb::Render() {
	if (m_BStatus.bDrow == true)
		CGraphicsUtilities::RenderFillCircle(GetRenderCircle(),MOF_COLOR_BLUE);
}

void CAnyaOrb::Release() {

}