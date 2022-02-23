#include "GameOver.h"

CGameOver::CGameOver()
{
}


CGameOver::~CGameOver()
{
}

void CGameOver::Initialize() {
	m_bEnd = false;
	m_Sound.Load("bgmGameover.mp3");
	m_Sound.SetLoop(FALSE);
	m_Sound.Play();
}

bool CGameOver::Load() {
	if (!m_BackImage.Load("GameOver.png"))
		return false;
	return true;
}

void CGameOver::Update() {
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		m_bEnd = true;
		m_NextScene = SCENENO_TITLE;
	}
}

void CGameOver::Render() {
	m_BackImage.Render(0,0);
	CGraphicsUtilities::RenderString(350, 500, MOF_COLOR_WHITE, "GAME OVER Press Enter Key");
}

void CGameOver::RenderDebug() {

}

void CGameOver::Release() {
	m_BackImage.Release();
}