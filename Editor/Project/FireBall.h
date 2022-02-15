#pragma once
#include "GameDefine.h"
class CFireBall
{
private:
	CTexture*		m_pTexture;
	CSpriteMotionController		m_Motion;

	float			m_PosX;
	float			m_PosY;
	float			m_MoveX;
	float			m_MoveY;
	bool			m_bShow;
	bool			m_bReverse;
	CRectangle		m_SrcRect;

public:
	CFireBall();
	~CFireBall();
	void Load(CTexture* pTexture);
	void Initialize(void);
	void Update(void);
	void Render(float wx, float wy);
	void RenderDebug(float wx, float wy);
	void Release(void);

	void Collision(float ox, float oy);
	void Fire(float px, float py, bool bRev) {
		m_PosY = py;
		m_MoveY = -2;
		m_bShow = true;
		m_bReverse = bRev;
		if (bRev)
		{
			m_PosX = px - GetRect().GetWidth();
			m_MoveX = -3.0f;
		}
		else
		{
			m_PosX = px;
			m_MoveX = 3.0f;
		}
	}
	CRectangle GetRect() {
		return CRectangle{ m_PosX, m_PosY, m_PosX + m_SrcRect.GetWidth(), m_PosY + m_SrcRect.GetHeight()};
	}
	bool GetShow() {
		return m_bShow;
	}
	void Hit() { m_bShow = false; }
	void SetMoveY(float my) { m_MoveY = my; }
};

