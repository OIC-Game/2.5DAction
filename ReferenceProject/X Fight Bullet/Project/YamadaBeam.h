#pragma once
#include "BulletBase.h"

class CYamadaBeam : public CBulletBase
{
private:
public:
	CYamadaBeam();
	~CYamadaBeam();

	void Initialize(int playerno, int posno);
	void Generation(CCircle player, CCircle enemy);
	void Update(CCircle player, CCircle enemy);
	void Render();
	void Release();
};

