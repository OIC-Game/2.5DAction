#pragma once
#include	"BulletBase.h"

class CYamadaBall : public CBulletBase
{
private:
public:
	CYamadaBall();
	~CYamadaBall();

	void Initialize(int playerno, int posno);
	void Generation(CCircle player, CCircle enemy);
	void Update(CCircle player, CCircle enemy);
	void Render();
	void Release();
};

