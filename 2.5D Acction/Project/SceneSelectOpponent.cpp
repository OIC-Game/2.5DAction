#include "SceneSelectOpponent.h"

CSceneSelectOpponent::CSceneSelectOpponent() {

}

CSceneSelectOpponent::~CSceneSelectOpponent() {

}

bool CSceneSelectOpponent::Load() {
	return true;
}

void CSceneSelectOpponent::Initialize() {

}

void CSceneSelectOpponent::Update() {
	int pno = CControlManager::GetInstance().GetNo(0);
	CInputManager::GetInstance().SelectVertical(pno, m_SelectNo[0], m_MessageCount, 0, true);
	if (CInputManager::GetInstance().GetPush(pno, 0))
	{
		m_bEnd = true;
		m_NextSceneNo = SCENENO_MENU;
	}
	if (CInputManager::GetInstance().GetPush(pno, 1))
	{
		m_bEnd = true;
		m_NextSceneNo = SCENENO_CHARACTERSELECT;

		COpponentManager::GetInstance().SetOpponent(m_SelectNo[0] != 0);
		m_SelectNo[0] = 0;
		m_SelectNo[1] = 0;
	}
}

void CSceneSelectOpponent::UpdateDebug() {

}

void CSceneSelectOpponent::Render() {

	for (int i = 0; i < m_MessageCount; i++)
	{
		CRectangle r;
		CGraphicsUtilities::CalculateStringRect(0, 0, m_Message[i].c_str(), r);
		float wid = g_pGraphics->GetTargetWidth() / 2;
		float hei = 350 + i * 40;
		if (m_SelectNo[0] == i)
		{
			CGraphicsUtilities::RenderFillRect(wid - r.GetWidth() / 2, hei, wid - r.GetWidth() / 2 + r.GetWidth(), hei + r.GetHeight(), MOF_COLOR_RED);
		}
		CGraphicsUtilities::RenderString(wid - r.GetWidth() / 2, hei, m_Message[i].c_str());
	}
}

void CSceneSelectOpponent::RenderDebug() {

}

void CSceneSelectOpponent::Release() {

}