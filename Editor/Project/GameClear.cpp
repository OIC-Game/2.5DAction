#include "GameClear.h"


CGameClear::CGameClear()
{
}

CGameClear::~CGameClear()
{
}

void CGameClear::Initialize() {
	m_bEnd = false;
}

bool CGameClear::Load() {
	if (m_BackImage.Load("Clear.png"))
		return false;
	return true;
}

void CGameClear::Update() {
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		m_bEnd = true;
		m_NextScene = SCENENO_TITLE;
	}
}

void CGameClear::Render() {
	m_BackImage.Render(0,0);
	CGraphicsUtilities::RenderString(350, 500, MOF_COLOR_WHITE, "GAME CLEAR Press Enter Key");
}

void CGameClear::RenderDebug(void) {

}

void CGameClear::Release()
{

}