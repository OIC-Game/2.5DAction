#pragma once
#include "BulletBase.h"
class CRipplesBullet : public CBulletBase
{
private:
public:
	CRipplesBullet();
	~CRipplesBullet();

	void Initialize(int playerno, int posno);
	void Generation(CCircle player, CCircle enemy);
	void Update(CCircle player, CCircle enemy);
	void Render();
	void Release();
};

