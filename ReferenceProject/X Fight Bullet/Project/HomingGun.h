#pragma once
#include "BulletBase.h"
class CHomingGun : public CBulletBase
{
private:
public:
	CHomingGun();
	~CHomingGun();

	void Initialize(int playerno, int posno);
	void Generation(CCircle player, CCircle enemy);
	void Update(CCircle player, CCircle enemy);
	void Render();
	void Release();
};

