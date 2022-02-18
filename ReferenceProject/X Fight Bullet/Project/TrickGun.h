#pragma once
#include  "BulletBase.h"
class CTrickGun : public CBulletBase
{
private:
	const float m_DirPatern[8] = { 45,135,225,315, 90,180,270,0};
	const float m_DamagePatern[4] = { 50,10,5,3 };
	const float m_SpeedPatern[4] = {14,6,7,9};


	int m_RingNo1;
	int m_RingNo2;
	int m_ReflectionNo;

public:
	CTrickGun();
	~CTrickGun();

	void DivisionGeneration(CCircle player,int posno);
	void SetRingNo(int p,int rn1,int rn2);
	int GetRingNo1() { return m_RingNo1; }
	int GetRingNo2() { return m_RingNo2; }
	void Initialize(int playerno, int posno);
	void Generation(CCircle player, CCircle enemy);
	void Update(CCircle player, CCircle enemy);
	void Render();
	void Release();
	void EndDrow() { m_BStatus.bDrow = false; }
};

