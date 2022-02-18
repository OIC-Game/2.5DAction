#pragma once
#include "BulletBase.h"

class CMachShot : public CBulletBase
{
private:
	const int m_DirPatern[3] = {80,90,100};
public:
	CMachShot();
	~CMachShot();

	void Initialize(int playerno, int posno);
	void Generation(CCircle player, CCircle enemy);
	void Update(CCircle player, CCircle enemy);
	void Render();
	void Release();
};

