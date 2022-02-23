#pragma once
#include "BulletBase.h"
class CChargeLaser : public CBulletBase
{
private:
public:
	CChargeLaser();
	~CChargeLaser();

	void Initialize(int playerno, int posno);
	void Generation(CCircle player, CCircle enemy);
	void Update(CCircle player, CCircle enemy);
	void Render();
	void Release();
};

