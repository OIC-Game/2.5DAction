#pragma once
#include "BulletBase.h"

class CDoubtRing : public CBulletBase
{
private:
public:
	CDoubtRing();
	~CDoubtRing();

	void Initialize(int playerno, int posno);
	void Generation(CCircle player, CCircle enemy);
	void Update(CCircle player, CCircle enemy);
	void Render();
	void Release();
};

