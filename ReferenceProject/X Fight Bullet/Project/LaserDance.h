#pragma once
#include "BulletBase.h"
class CLaserDance : public CBulletBase
{
private:
	const int m_PerTimeList[3] = { 40,20,15 };
	const int m_WaitTime = 30;

	int m_WaitRemTime;
	int m_MaxPhaseNo = 3;
	int m_PhaseNo;
	bool m_bEnd;

public:
	CLaserDance();
	~CLaserDance();
	bool GetEnd() { return m_bEnd; }

	void Initialize(int playerno, int posno);
	void Generation(CCircle player, CCircle enemy);
	void Update(CCircle player, CCircle enemy);
	void Render();
	void Release();
};

