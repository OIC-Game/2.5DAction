#pragma once
#include "BulletBase.h"
class CExplosionShot : public CBulletBase
{
private:
	int m_FlyDamage = 5;
	int m_ExpDamage = 90;
	float m_Smaller = 5;
	int m_WaiteTime = 20;

	int m_PhaseNo;
	float m_Len;
	int m_WaiteRemTime;

public:
	CExplosionShot();
	~CExplosionShot();

	void Initialize(int playerno, int posno);
	void Generation(CCircle player, CCircle enemy);
	void Update(CCircle player, CCircle enemy);
	void Render();
	void Release();
};

