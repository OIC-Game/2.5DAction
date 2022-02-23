#include "Enemy.h"



CEnemy::CEnemy()
{
}


CEnemy::~CEnemy()
{
}

void CEnemy::Initialize(float px, float py, int type) {
	m_Type = type;
	m_PosX = px;
	m_PosY = py;
	m_PosSX = 0;
	m_PosSY = 0;
	m_MoveX = -1.0f;
	m_MoveY = 0.0f;
	m_MoveSX = 0.0f;
	m_MoveSY = 0.0f;
	m_bReverse = true;
	m_bSReverse = true;
	m_bShow = true;
	m_bSShow = false;
	m_bIn = false;
	m_HP = 1;
	m_DamageWait = 0;
	m_WaitTime = 0;
	m_FloatWait = 0;
	m_bUp = true;

	// アニメーション
	switch (m_Type)
	{
		case 0:
		{
			SpriteAnimationCreate anim[] = {
				{
					"移動",
					0,0,
					256,256,
					TRUE,{ { 10,0,0 },{ 10,2,0 }}
				},
			};
			m_Motion.Create(anim, 1);
			break;
		}
		case 1:
		case 2:
		{
			SpriteAnimationCreate anim[] = {
				{
					"移動",
					0,0,
					64,64,
					TRUE,{ { 10,0,0 },{ 10,1,0 }}
				},
				{
					"甲羅飛びだし",
					0,160,
					64,64,
					FALSE,{ { 20,0,0 },{ 5,1,0 },{ 5,0,0 },{ 5,1,0 },{ 5,0,0 }}
				},
				{
					"バタ足",
					0,160,
					64,64,
					TRUE,{ { 10,0,0 },{ 10,1,0 }}
				},
				{
					"しゃがみ歩き",
					0,160,
					64,64,
					TRUE,{ { 10,2,0 },{ 10,3,0 }}
				},
				{
					"復活",
					0,8,
					64,70,
					FALSE,{ { 50,0,1 },{ 10,0,0 }}
				}
			};
			SpriteAnimationCreate Sanim[] = {
				{
					"甲羅",
					0,80,
					64,64,
					FALSE,{ { 10,0,0 } }
				},
				{
					"甲羅回転",
					0,80,
					64,64,
					TRUE,{ { 5,0,0 }, { 5,2,0 }, { 5,4,0 }, { 5,6,0 }}
				}
			};
			m_Motion.Create(anim, 5);
			m_SMotion.Create(Sanim, 2);
			break;
		}
		case 3:
		case 4:
		{
			SpriteAnimationCreate anim[] = {
				{
					"移動",
					0,0,
					64,64,
					TRUE,{ { 10,0,0 },{ 10,1,0 }}
				},
				{
					"甲羅飛びだし",
					0,160,
					64,64,
					FALSE,{ { 20,0,0 },{ 5,1,0 },{ 5,0,0 },{ 5,1,0 },{ 5,0,0 }}
				},
				{
					"バタ足",
					0,160,
					64,64,
					TRUE,{ { 10,0,0 },{ 10,1,0 }}
				},
				{
					"しゃがみ歩き",
					0,160,
					64,64,
					TRUE,{ { 10,2,0 },{ 10,3,0 }}
				},
				{
					"復活",
					0,8,
					64,70,
					FALSE,{ { 50,0,1 },{ 10,0,0 }}
				},
				{
					"移動",
					128,0,
					64,64,
					TRUE,{ { 10,0,0 },{ 10,1,0 }}
				},
			};
			SpriteAnimationCreate Sanim[] = {
				{
					"甲羅",
					0,80,
					64,64,
					FALSE,{ { 10,0,0 } }
				},
				{
					"甲羅回転",
					0,80,
					64,64,
					TRUE,{ { 5,0,0 }, { 5,2,0 }, { 5,4,0 }, { 5,6,0 }}
				}
			};
			m_Motion.Create(anim, 6);
			m_SMotion.Create(Sanim, 2);
			break;
		}
	}
	m_Motion.ChangeMotion(0);
}

void CEnemy::SetTexture(CTexture* pTexture) {
	m_pTexture = pTexture;
}

void CEnemy::Update() {
	if (m_bIn)
	{
		return;
	}

	if (m_Type != 0)
	{
		if (m_bSShow)
		{
			m_MoveSY += GRAVITY;
			m_PosSX += m_MoveSX;
			m_PosSY += m_MoveSY;
			m_SMotion.AddTimer(CUtilities::GetFrameSecond());
			m_SSrcRect = m_SMotion.GetSrcRect();
		}
	}
	// 非表示
	if (!m_bShow)
	{
		return;
	}
	// 重力により下に少しずつ下がる
	if (m_Type == 4 && m_Motion.GetMotionNo() == 0)
	{
		if (m_bUp)
		{
			if (m_FloatWait > 0)
				m_MoveY = 1.5f;
			else
			{
				m_bUp = !m_bUp;
				m_FloatWait = 140;
			}
		}
		else
		{
			if (m_FloatWait > 0)
				m_MoveY = -1.5f;
			else
			{
				m_bUp = !m_bUp;
				m_FloatWait = 140;
			}
		}
		m_FloatWait--;
	}
	//else
		//m_MoveY += GRAVITY;

	if (m_MoveY >= 20.0f)
	{
		m_MoveY = 20.0f;
	}

	// 実際に座標を移動させる
	if (m_Type == 4 && m_Motion.GetMotionNo() == 0)
	{
		m_MoveX = 0;
	}
	m_PosX += m_MoveX;
	m_PosY += m_MoveY;

		m_DamageWait--;
		if (m_DamageWait <= 0)
			m_DamageWait = 0;

	if (m_Type != 0)
	{
		switch (m_Motion.GetMotionNo())
		{
		case 1:
			if (m_MoveX > 0)
			{
				m_MoveX -= 0.5f;
				if (m_MoveX <= 0)
					m_MoveX = 0;
			}
			else if (m_MoveX < 0)
			{
				m_MoveX += 0.5f;
				if (m_MoveX >= 0)
					m_MoveX = 0;
			}
			if (m_MoveX == 0)
			{
				m_Motion.ChangeMotion(2);
				m_DamageWait = 60;
			}
			break;
		case 2:
			if (m_DamageWait == 0)
				m_Motion.ChangeMotion(3);
			break;
		case 3:
			if (m_bReverse)
			{
				m_MoveX = -0.5f;
			}
			else
				m_MoveX = 0.5f;
			if (GetRect().CollisionRect(GetSRect()) && m_MoveSX == 0)
			{
				m_MoveX = 0;
				m_Motion.ChangeMotion(4);
				m_bSShow = false;
			}
			break;
		default:
			if (m_Motion.IsEndMotion())
			{
				if (m_Type == 1 || m_Type == 2)
					m_Motion.ChangeMotion(0);
				else
					m_Motion.ChangeMotion(5);
				if (m_bReverse)
				{
					m_MoveX = -0.5f;
				}
				else
					m_MoveX = 0.5f;
			}
			break;
		}
		
	}

	if (m_PosY >= g_pGraphics->GetTargetHeight())
	{
		m_bShow = false;
	}
	if (m_PosSY >= g_pGraphics->GetTargetHeight())
	{
		m_bSShow = false;
	}

	// アニメーションの更新
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();

	if (m_WaitTime < 3)
		m_WaitTime++;
}

void CEnemy::Damage(int dmg, bool bRev, bool type) {
	if (type == true)
	{
		m_bShow = false;
		return;
	}
	m_HP -= dmg;
	m_DamageWait = 60;
	switch (m_Type)
	{
	case 0:
		if (bRev)
		{
			m_MoveX = -5.0f;
			m_bReverse = false;
		}
		else
		{
			m_MoveX = 5.0f;
			m_bReverse = true;
		}
		if (m_HP <= 0)
		{
			m_bShow = false;
		}
		break;
	case 1:
	case 2:
		switch (m_Motion.GetMotionNo())
		{
		case 0:
			if (bRev)
			{
				m_MoveX = -12.0f;
				m_bReverse = false;
			}
			else
			{
				m_MoveX = 12.0f;
				m_bReverse = true;
			}
			m_PosSX = m_PosX;
			m_PosSY = m_PosY;
			m_bSShow = true;
			m_Motion.ChangeMotion(1);
			break;

		default:
			m_bShow = false;
			break;
		}
	case 3:
	case 4:
		switch (m_Motion.GetMotionNo())
		{
		case 0:
			m_Motion.ChangeMotion(5);
			if (m_MoveX <= 0)
			{
				m_MoveX = -1.0f;
				m_bReverse = true;
			}
			else
			{
				m_MoveX = 1.0f;
				m_bReverse = false;
			}
			m_DamageWait = 0;
			break;

		case 5:
			if (bRev)
			{
				m_MoveX = -12.0f;
				m_bReverse = false;
			}
			else
			{
				m_MoveX = 12.0f;
				m_bReverse = true;
			}
			m_PosSX = m_PosX;
			m_PosSY = m_PosY;
			m_bSShow = true;
			m_Motion.ChangeMotion(1);
			break;
		default:
			break;
		}
	}
}

void CEnemy::StepOnShel(bool bRev, bool type) {
	if (type)
	{
		m_bSShow = false;
	}
	if (m_MoveSX == 0)
	{
		if (bRev)
		{
			m_MoveSX = -5.0f;
			m_PosSX -= 5.0f;
			m_bSReverse = false;
		}
		else
		{
			m_MoveSX = 5.0f;
			m_PosSX += 5.0f;
			m_bSReverse = true;
		}
		m_SMotion.ChangeMotion(1);
	}
	else
	{
		m_MoveSX = 0;
		m_SMotion.ChangeMotion(0);
	}
}

void CEnemy::CollisionStage(float ox, float oy, int s, bool bHit) {
	if (s == 0)
	{
		if (bHit && m_DamageWait == 0)
			m_bShow = false;
		m_PosX += ox;
		m_PosY += oy;

		// 落下中の上埋まりの場合は移動を初期化する
		if (oy < 0 && m_MoveY > 0)
		{
			m_MoveY = 0;
			if (m_Type == 3 && m_Motion.GetMotionNo() == 0)
				m_MoveY = -5.0f;
		}
		else if (oy > 0 && m_MoveY < 0)
		{
			m_MoveY = 0;
		}

		// 左移動中の左埋まり、右移動中の右埋まりの場合は移動を初期化する
		if (ox < 0 && m_MoveX > 0)
		{
			m_MoveX *= -1;
			m_bReverse = true;
		}
		else if (ox > 0 && m_MoveX < 0)
		{
			m_MoveX *= -1;
			m_bReverse = false;
		}
	}
	else if (s == 1)
	{
		if (bHit)
			m_bSShow = false;
		m_PosSX += ox;
		m_PosSY += oy;
		// 落下中の上埋まりの場合は移動を初期化する
		if (oy < 0 && m_MoveSY > 0)
		{
			m_MoveSY = 0;
		}
		else if (oy > 0 && m_MoveSY < 0)
		{
			m_MoveSY = 0;
		}

		// 左移動中の左埋まり、右移動中の右埋まりの場合は移動を初期化する
		if (ox < 0 && m_MoveSX > 0)
		{
			m_MoveSX *= -1;
			m_bSReverse = true;
		}
		else if (ox > 0 && m_MoveSX < 0)
		{
			m_MoveSX *= -1;
			m_bSReverse = false;
		}
	}
}

void CEnemy::Render(float wx, float wy) {
	if (m_bIn)
	{
		return;
	}
	if (m_Type != 0)
	{
		if (m_bSShow)
		{
			//描画矩形
			CRectangle sdr = m_SSrcRect;
			//反転フラグがONの場合描画矩形を反転させる
			if (!m_bReverse)
			{
				float tmp = sdr.Right;
				sdr.Right = sdr.Left;
				sdr.Left = tmp;
			}
			m_pTexture->Render(m_PosSX - wx, m_PosSY - wy, sdr);
		}
	}
	//非表示
	if (!m_bShow)
	{
		return;
	}
	//描画矩形
	CRectangle dr = m_SrcRect;
	//反転フラグがONの場合描画矩形を反転させる
	if (!m_bReverse)
	{
		float tmp = dr.Right;
		dr.Right = dr.Left;
		dr.Left = tmp;
	}
	//テクスチャの描画
	m_pTexture->Render(m_PosX - wx, m_PosY - wy, dr);
	
}

void CEnemy::RenderDebug(float wx, float wy) {
	if (m_Type != 0)
	{
		if (m_bSShow)
		{
			CRectangle shr = GetSRect();
			CRectangle str = GetSTRect();
			CGraphicsUtilities::RenderRect(shr.Left - wx, shr.Top - wy, shr.Right - wx, shr.Bottom - wy, MOF_COLOR_GREEN);
			CGraphicsUtilities::RenderRect(str.Left - wx, str.Top - wy, str.Right - wx, str.Bottom - wy, MOF_COLOR_RED);
		}
	}
	//非表示
	if (!m_bShow)
	{
		return;
	}
	CRectangle hr = GetRect();
	CRectangle tr = GetTRect();
	CRectangle fr = GetForwardRect();
	CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_COLOR_GREEN);
	CGraphicsUtilities::RenderRect(tr.Left - wx, tr.Top - wy, tr.Right - wx, tr.Bottom - wy, MOF_COLOR_RED);
	CGraphicsUtilities::RenderRect(fr.Left - wx, fr.Top - wy, fr.Right - wx, fr.Bottom - wy, MOF_COLOR_BLUE);
}

void CEnemy::Release() {
	m_pTexture->Release();
}