#pragma once
#include "BulletBase.h"
class CRipplesShot : public CBulletBase
{
private:
public:
	CRipplesShot();
	~CRipplesShot();

	void Initialize(int playerno, int posno);
	void Generation(CCircle player, CCircle enemy);
	void Update(CCircle player, CCircle enemy);
	void Render();
	void Release();
};

