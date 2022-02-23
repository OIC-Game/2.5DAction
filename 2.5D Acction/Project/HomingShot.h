#pragma once
#include "BulletBase.h"

class CHomingShot : public CBulletBase
{
private:
	 int m_FormNo = 6;
	 int m_FormPer = 40;

	 float m_DirPatern[3] = { 45,90,135 };

	int m_RemFormNo;
	int m_RemFormPer;

public:
	CHomingShot();
	~CHomingShot();

	void Initialize(int playerno, int posno);
	void Generation(CCircle player, CCircle enemy);
	void Update(CCircle player, CCircle enemy);
	void Render();
	void Release();
};

