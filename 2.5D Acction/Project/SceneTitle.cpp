#include "SceneTitle.h"

CSceneTitle::CSceneTitle() {

}

CSceneTitle::~CSceneTitle() {

}

bool CSceneTitle::Load() {
	return true;
}

void CSceneTitle::Initialize() {

}

void CSceneTitle::Update() {
	for (int i = 0; i < 5; i++)
	{
		if (CInputManager::GetInstance().GetPush(i, 1))
		{
			CControlManager::GetInstance().SetNo(0, i);

			m_bEnd = true;
			m_NextSceneNo = SCENENO_MENU;
			return;
		}
	}
}

void CSceneTitle::Render() {

	for (int i = 0; i < m_MessageCount; i++)
	{
		CRectangle r;
		CGraphicsUtilities::CalculateStringRect(0, 0, m_OptionMessage[i].c_str(), r);
		float wid = g_pGraphics->GetTargetWidth() / 2;
		float hei = 350 + i * 40;
		CGraphicsUtilities::RenderString(wid - r.GetWidth() / 2, hei, m_OptionMessage[i].c_str());
	}
}

void CSceneTitle::RenderDebug() {

}

void CSceneTitle::Release() {

}