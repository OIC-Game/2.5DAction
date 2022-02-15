#pragma once
#include "GameDefine.h"

class CEnemy
{
private:
	CTexture*					m_pTexture;
	CSpriteMotionController		m_Motion;
	CSpriteMotionController		m_SMotion;

	int					m_Type;
	float				m_PosX;
	float				m_PosY;
	float				m_PosSX;
	float				m_PosSY;
	float				m_MoveX;
	float				m_MoveY;
	float				m_MoveSX;
	float				m_MoveSY;
	bool				m_bReverse;
	bool				m_bSReverse;
	bool				m_bShow;
	bool				m_bSShow;
	bool				m_bIn;
	int					m_WaitTime;
	int					m_FloatWait;
	bool				m_bUp;


	int					m_HP;
	int					m_DamageWait;

	CRectangle			m_SrcRect;
	CRectangle			m_SSrcRect;
public:
	CEnemy();
	~CEnemy();

	void Initialize(float px, float py, int type);
	void Update();
	void Render(float wx, float wy);
	void RenderDebug(float wx, float wy);
	void Release();

	void CollisionStage(float ox, float oy, int s,bool bHit);

	void SetTexture(CTexture* pTexture);

	void Damage(int dmg, bool bRev, bool type);

	void StepOnShel(bool bRev, bool type);

	void CollisionEnemy(float ix) {
		m_bReverse = !m_bReverse;
		m_MoveX *= -1;
		m_PosX += ix;
	}

	//当たり判定全般
	CRectangle GetRect() {
		return { m_PosX + 64,m_PosY + 64,m_PosX + 192, m_PosY + 192 };
	}
	// 踏むことができる、当たり判定上部
	CRectangle GetTRect() {
		return { m_PosX + 64,m_PosY + 64,m_PosX + 192, m_PosY + 96 };
	}

	//当たり判定全般
	CRectangle GetSRect() {
			return { m_PosSX + 16,m_PosSY + 32,m_PosSX + 48, m_PosSY + 64 };
	}
	// 踏むことができる、当たり判定上部
	CRectangle GetSTRect() {
			return { m_PosSX + 16,m_PosSY + 32,m_PosSX + 48, m_PosSY + 40 };
	}
	CRectangle GetForwardRect() {
		switch (m_Type)
		{
		case 0:
			if (m_bReverse)
			{
				return CRectangle(m_PosX - m_SrcRect.GetWidth(), m_PosY, m_PosX, m_PosY + m_SrcRect.GetHeight());
			}
			else
				return CRectangle(m_PosX + m_SrcRect.GetWidth(), m_PosY, m_PosX + m_SrcRect.GetWidth() * 2, m_PosY + m_SrcRect.GetHeight());
		default:
			if (m_bReverse)
			{
				return CRectangle(m_PosX - m_SrcRect.GetWidth() + 48, m_PosY + m_SrcRect.GetHeight() / 2, m_PosX + 16, m_PosY + m_SrcRect.GetHeight());
			}
			else
				return CRectangle(m_PosX + m_SrcRect.GetWidth() - 16, m_PosY + m_SrcRect.GetHeight() / 2, m_PosX + m_SrcRect.GetWidth() * 2 - 48, m_PosY + m_SrcRect.GetHeight());
			break;
		}
	}

	bool GetShow() { return m_bShow; }
	bool GetIn(void) { return m_bIn; }
	bool GetSShow() { return m_bSShow; }
	int GetDamageWait() { return m_DamageWait; }
	int GetType() { return m_Type; }
	int GetSMoveX() { return m_MoveSX; }

	void ChangeReverse() {
		if (m_Type == 2 || m_Type == 4)
		{
			m_bReverse = !m_bReverse;
			m_MoveX *= -1;
		}
	}

	void InChip(bool bIn) {
		if (!bIn)
		{
			if (m_bIn)
				m_DamageWait = 2;
			m_bIn = false;
		}
		else
		{
			//if (m_WaitTime == 1)
				//m_bIn = true;
		}
	}
};

