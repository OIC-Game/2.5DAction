#include "SceneMenu.h"

CSceneMenu::CSceneMenu(){

}

CSceneMenu::~CSceneMenu() {

}

bool CSceneMenu::Load() {
	return true;
}

void CSceneMenu::Initialize() {

}

void CSceneMenu::Update() {
	int pno = CControlManager::GetInstance().GetNo(0);
	CInputManager::GetInstance().SelectVertical(pno, m_SelectNo[0], m_MessageCount, 0 , true);
	if (CInputManager::GetInstance().GetPush(pno,0))
	{
		m_bEnd = true;
		m_NextSceneNo = SCENENO_TITLE;
	}
	if (CInputManager::GetInstance().GetPush(pno,1))
	{
		m_bEnd = true;
		switch (m_SelectNo[0])
		{
		case 0:
				m_NextSceneNo = SCENENO_OPPOENT;
			break;
		case 1:
				m_NextSceneNo = SCENENO_OPTION;
			break;
		case 2:
				m_NextSceneNo = SCENENO_TITLE;
			break;
		default:
			break;
		}
	}
}

void CSceneMenu::UpdateDebug() {

}

void CSceneMenu::Render() {

	for (int i = 0; i < 3; i++)
	{
		CRectangle r;
		CGraphicsUtilities::CalculateStringRect(0, 0, m_MenuMessage[i].c_str(), r);
			float wid = g_pGraphics->GetTargetWidth() / 2;
			float hei = 350 + i * 40;
		if (m_SelectNo[0] == i)
		{
			CGraphicsUtilities::RenderFillRect(wid - r.GetWidth() / 2, hei, wid - r.GetWidth() / 2 + r.GetWidth(), hei + r.GetHeight(), MOF_COLOR_RED);
		}
		CGraphicsUtilities::RenderString(wid - r.GetWidth() / 2, hei, m_MenuMessage[i].c_str());
	}
}

void CSceneMenu::RenderDebug() {
	CGraphicsUtilities::RenderString(10, 10, "ÉÅÉjÉÖÅ[");
	CGraphicsUtilities::RenderString(10, 40, "%d", m_SelectNo[0]);
}

void CSceneMenu::Release() {

}