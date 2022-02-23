#pragma once
#include "BulletBase.h"
class CWaveShot : public CBulletBase
{
private:
	float m_WaveDir;
public:
	CWaveShot();
	~CWaveShot();
	
	void Initialize(int playerno, int posno);
	void Generation(CCircle player, CCircle enemy);
	void Update(CCircle player, CCircle enemy);
	void Render();
	void Release();
};

