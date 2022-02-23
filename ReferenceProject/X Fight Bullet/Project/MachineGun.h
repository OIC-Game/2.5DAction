#pragma once
#include	"BulletBase.h"

class CMachineGun : public CBulletBase
{
private:
	float m_width = 10;

public:
	CMachineGun();
	~CMachineGun();

	void Initialize(int playerno, int posno);
	void Generation(CCircle player, CCircle enemy);
	void Update(CCircle player, CCircle enemy);
	void Render();
	void Release();
};

