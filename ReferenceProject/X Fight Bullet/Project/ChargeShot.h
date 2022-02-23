#pragma once
#include	"BulletBase.h"
class CChargeShot : public CBulletBase
{
private:
	float m_DamageRate = 0.05f;
	float m_SpeedRate = 0.05f;
	float m_RadiusRate = 0.03f;

public:
	CChargeShot();
	~CChargeShot();

	void Initialize(int playerno, int posno);
	void Generation(CCircle player, CCircle enemy);
	void Update(CCircle player, CCircle enemy);
	void Render();
	void Release();
};

