#pragma once
#include "BulletBase.h"

class CGrowShot : public CBulletBase
{
private:
	
public:
	CGrowShot();
	~CGrowShot();

	void Initialize(int playerno, int posno);
	void Generation(CCircle player, CCircle enemy);
	void Update(CCircle player, CCircle enemy);
	void Render();
	void Release();
};

