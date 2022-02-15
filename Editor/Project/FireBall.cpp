#include "FireBall.h"

CFireBall::CFireBall():
	m_PosX(0),
	m_PosY(0),
	m_bShow(false)
{

}

CFireBall::~CFireBall()
{

}

void CFireBall::Load(CTexture* pTexture) {
	m_pTexture = pTexture;
	SpriteAnimationCreate anim =
	{
			"ファイヤーボール",
			80,764,
			18,20,
			FALSE,{ 5,0,0 }
	};
	m_Motion.Create(anim);
	m_Motion.ChangeMotion(0);
}

void CFireBall::Initialize() {
	m_PosX = 0;
	m_PosY = 0;
	m_MoveX = 0;
	m_MoveY = 0;
	m_bShow = false;
	m_bReverse = false;
}

void CFireBall::Update() {
	if (!m_bShow)
	{
		return;
	}

	m_PosX += m_MoveX;
	m_PosY += m_MoveY;

	m_MoveY += GRAVITY * 1.5f;
	if (m_MoveY >= 20.0f)
	{
		m_MoveY = 20.0f;
	}

	if (m_PosY >= g_pGraphics->GetTargetHeight())
	{
		m_bShow = false;
	}

	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
}

void CFireBall::Collision(float ox, float oy) {
	m_PosY += oy;
	// 落下中の下埋まり、ジャンプ中の上埋まりの場合は移動を初期化する。
	if (oy < 0 && m_MoveY > 0)
	{
		m_MoveY = -3;
	}
	else if (oy > 0 && m_MoveY < 0)
	{
		m_MoveY = 0;
	}

	// 左移動中の左埋まり、右移動中の右埋まりの場合は移動を初期化する。
	if (ox != 0)
	{
		m_bShow = false;
	}
}

void CFireBall::Render(float wx, float wy) {
	if (!m_bShow)
	{
		return;
	}
	CRectangle dr = m_SrcRect;

	// 描画位置
	float px = m_PosX - wx;
	float py = m_PosY - wy;

	// 反転フラグがONの場合、描画矩形を反転させる
	if (m_bReverse)
	{
		float tmp = dr.Right;
		dr.Right = dr.Left;
		dr.Left = tmp;
	}

		m_pTexture->Render(px, py, dr);
}

void CFireBall::RenderDebug(float wx, float wy) {
	if (!m_bShow)
	{
		return;
	}
	CRectangle fr = GetRect();
	CGraphicsUtilities::RenderRect(fr.Left - wx, fr.Top - wy, fr.Right - wx, fr.Bottom - wy,MOF_COLOR_RED);
}

void CFireBall::Release() {
	m_pTexture->Release();
}
