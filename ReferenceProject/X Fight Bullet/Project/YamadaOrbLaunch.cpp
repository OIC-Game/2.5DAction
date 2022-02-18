#include "YamadaOrbLaunch.h"



YamadaOrbLaunch::YamadaOrbLaunch()
{
}


YamadaOrbLaunch::~YamadaOrbLaunch()
{
}

CCircle YamadaOrbLaunch::GetPosition(int pos, CCircle player, CCircle enemy)
{
	m_PPosX = player.x;
	m_PPosY = player.y;
	m_EPosX = enemy.x;

	float	m_PosX = (m_PPosX > m_EPosX) ? m_PPosX + cos(PosPatern[pos][0]) * PosPatern[pos][1] : m_PPosX + cos(PosPatern[pos][0] - MOF_ToRadian(180)) * PosPatern[pos][1];
	float	m_PosY = (m_PPosX > m_EPosX) ? m_PPosY + sin(PosPatern[pos][0]) * PosPatern[pos][1] : m_PPosY + sin(PosPatern[pos][0] - MOF_ToRadian(180)) * PosPatern[pos][1];

	return CCircle(m_PosX, m_PosY, 1);
}

void YamadaOrbLaunch::Render(int pos) {
	float	m_PosX = (m_PPosX > m_EPosX) ? m_PPosX + cos(PosPatern[pos][0]) * PosPatern[pos][1] : m_PPosX + cos(PosPatern[pos][0] - MOF_ToRadian(180)) * PosPatern[pos][1];
	float	m_PosY = (m_PPosX > m_EPosX) ? m_PPosY + sin(PosPatern[pos][0]) * PosPatern[pos][1] : m_PPosY + sin(PosPatern[pos][0] - MOF_ToRadian(180)) * PosPatern[pos][1];
	CGraphicsUtilities::RenderFillCircle(m_PosX, m_PosY, 5, MOF_COLOR_RED);
}