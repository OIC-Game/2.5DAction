#pragma once
#include "BulletBase.h"
class CSonicBeam : public CBulletBase
{
private:
	const int m_WaitTime = 90;

	int m_WaitRemTime;

public:
	CSonicBeam();
	~CSonicBeam();

	void Initialize(int playerno, int posno);
	void Generation(CCircle player, CCircle enemy);
	void Update(CCircle player, CCircle enemy);
	void Render();
	void Release();
};

