#include "Title.h"

CTitle::CTitle() :
	CScensBace()
{
}


CTitle::~CTitle()
{
}

void CTitle::Initialize() {
	m_bEnd = false;
	m_StageNo = 0;
}

bool CTitle::Load() {
	if (!m_BackImage.Load(""))
		return false;
	return true;
}

void CTitle::Update() {
	if (g_pInput->IsKeyPush(MOFKEY_UP))
	{
		m_StageNo--;
		if (m_StageNo <= 0)
			m_StageNo = 0;
	}
	else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
	{
		m_StageNo++;
		if (m_StageNo >= 2)
			m_StageNo = 2;
	}
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		m_bEnd = true;
		m_NextScene = SCENENO_GAME;
	}
	else if (g_pInput->IsKeyPush(MOFKEY_F2))
	{
		m_bEnd = true;
		m_NextScene = SCENENO_EDITOR;
	}
}

void CTitle::Render() {
	CGraphicsUtilities::RenderFillRect(0, 0, g_pGraphics->GetTargetWidth(), g_pGraphics->GetTargetHeight(), MOF_COLOR_WHITE);
	CGraphicsUtilities::RenderString(320, 200, MOF_COLOR_BLACK, "Press Enter Key : GAME START");
	CGraphicsUtilities::RenderString(470, 300, MOF_COLOR_BLACK, "Stage1");
	CGraphicsUtilities::RenderString(470, 380, MOF_COLOR_BLACK, "Stage2");
	CGraphicsUtilities::RenderString(470, 460, MOF_COLOR_BLACK, "Stage3");
	CGraphicsUtilities::RenderString(340, 550, MOF_COLOR_BLACK, "Press F1 Key : DEBUG MODE");
	CGraphicsUtilities::RenderString(335, 600, MOF_COLOR_BLACK, "Press F2 Key : EDITOR MODE");
	switch (m_StageNo)
	{
	case 0:
		CGraphicsUtilities::RenderString(470, 300, MOF_COLOR_RED, "Stage1");
		break;
	case 1:
		CGraphicsUtilities::RenderString(470, 380, MOF_COLOR_RED, "Stage2");
		break;
	case 2:
		CGraphicsUtilities::RenderString(470, 460, MOF_COLOR_RED, "Stage3");
		break;
	default:
		break;
	}
}

void CTitle::RenderDebug(void) {

}

void CTitle::Release() {
	m_BackImage.Release();
}