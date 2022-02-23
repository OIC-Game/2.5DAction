#pragma once
#include "BulletBase.h"
class CContinuousenEnergyShot : public CBulletBase
{
private:
public:
	CContinuousenEnergyShot();
	~CContinuousenEnergyShot();

	void Initialize(int playerno, int posno);
	void Generation(CCircle player, CCircle enemy);
	void Update(CCircle player, CCircle enemy);
	void Render();
	void Release();
};

