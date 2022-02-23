#pragma once
#include	"BulletBase.h"
class CYamadaWorld : public CBulletBase
{
private:
	static const int m_AttackCount = 10;
	 int m_Attack[m_AttackCount] = { 5,10,15,20,30,50,80,100,120,150 };

	float m_GoalRadius;
	CRectangle m_AreaRect;

public:
	CYamadaWorld();
	~CYamadaWorld();

	void Initialize(int playerno, int posno);
	void Generation(CCircle player, CCircle enemy);
	void Update(CCircle player, CCircle enemy);
	void Render();
	void Release();
};

