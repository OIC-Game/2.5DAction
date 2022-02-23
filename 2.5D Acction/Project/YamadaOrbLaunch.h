#pragma once
#include	<Mof.h>
//  î≠éÀínì_ÇÃê∂ê¨
class YamadaOrbLaunch
{
	static const int m_PaternCount = 5;
	const float PosPatern[m_PaternCount][2] = { { MOF_ToRadian(110) ,70 } , { MOF_ToRadian(140) ,50 } , { MOF_ToRadian(180) ,45 } , { MOF_ToRadian(220) ,50 } , { MOF_ToRadian(250) ,70 } };

	float m_PPosX, m_PPosY, m_EPosX;
public:
	YamadaOrbLaunch();
	~YamadaOrbLaunch();
	CCircle GetPosition(int pos, CCircle player, CCircle enemy);
	void Render(int pos);
};

