#pragma once
#include "BulletBase.h"

class CYamadaOrb : public CBulletBase
{
private:

	 static const int m_AttackCount = 10;
	 static const int m_DirectionCount = 5;

	 int m_DirChenge = 4;
	 int m_DirChengeCount;

	 float m_Attack[m_AttackCount] = { 1,5,10,15,20,25,30,50,80,120 };
	 float m_Direction[m_DirectionCount] = { 30, 15, 0, 345, 330 };

	float m_Len;

public:
	CYamadaOrb();
	~CYamadaOrb();

	void Initialize(int playerno, int posno);
	void Generation(CCircle player, CCircle enemy);
	void Update(CCircle player, CCircle enemy);
	void Render();
	void Release();
};

