#pragma once
#include "BulletBase.h"

class CYamadaBlizzard : public CBulletBase
{
private:

	static const int m_AttackCount = 10;
	static const int m_DirectionCount = 9;

	int m_DirChenge = 6;
	int m_DirChengeCount;
	float m_Len;

	float m_Attack[m_AttackCount] = { 1,5,10,15,20,25,30,40,50,70 };
	float m_Direction[m_DirectionCount] = { 250,255,260,265,270,275,280,285,290 };
public:
	CYamadaBlizzard();
	~CYamadaBlizzard();

	void Initialize(int playerno, int posno);
	void Generation(CCircle player, CCircle enemy);
	void Update(CCircle player, CCircle enemy);
	void Render();
	void Release();
};

