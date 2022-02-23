#include "SceneOption.h"

CSceneOption::CSceneOption() {

}

CSceneOption::~CSceneOption() {

}

bool CSceneOption::Load() {
	return true;
}

void CSceneOption::Initialize() {
	m_BGMVolume = CSoundManager::GetInstance().GetBGMVolume() * 20;
	m_SEVolume = CSoundManager::GetInstance().GetSEVolume() * 20;
}

void CSceneOption::Update() {
	int pno = CControlManager::GetInstance().GetNo(0);
	CInputManager::GetInstance().SelectVertical(pno, m_SelectNo[0], m_MessageCount - 1, 0, true);
	if (m_SelectNo[0] == 3)
	{
		CInputManager::GetInstance().SelectHorizontal(pno, m_BGMVolume, m_VolumeCount + 1, false);
		CSoundManager::GetInstance().SetBGMVolume((float)m_BGMVolume / m_VolumeCount);
	}
	else if (m_SelectNo[0] == 4)
	{
		CInputManager::GetInstance().SelectHorizontal(pno, m_SEVolume, m_VolumeCount + 1, 0, false);
		CSoundManager::GetInstance().SetSEVolume((float)m_SEVolume / m_VolumeCount);
	}
	if (CInputManager::GetInstance().GetPush(pno, 0))
	{
		CSoundManager::GetInstance().LoadVolume();
		m_bEnd = true;
		m_NextSceneNo = SCENENO_MENU;
	}
	if (CInputManager::GetInstance().GetPush(pno, 1))
	{
		switch (m_SelectNo[0])
		{
		case 3:
		case 4:
			break;
		case 5:
			CSoundManager::GetInstance().LoadVolume();
			m_bEnd = true;
			m_NextSceneNo = SCENENO_MENU;
			break;
		case 6:
			CSoundManager::GetInstance().SaveVolume();
			m_bEnd = true;
			m_NextSceneNo = SCENENO_MENU;
			break;
		default:
			if (GetSystemMetrics(SM_CXSCREEN) >= m_Width[m_SelectNo[0]] && (GetSystemMetrics(SM_CYSCREEN) >= m_Height[m_SelectNo[0]]))
			{
				int w = m_Width[m_SelectNo[0]];
				int h = m_Height[m_SelectNo[0]];
				if (m_SelectNo[0] == 2)
					MoveWindow(g_pFramework->GetWindow()->GetWindowHandle(), (GetSystemMetrics(SM_CXSCREEN) - w) / 2 - 8, (GetSystemMetrics(SM_CYSCREEN) - h) / 2, w - 8, h - 31, FALSE);
				else
					MoveWindow(g_pFramework->GetWindow()->GetWindowHandle(), (GetSystemMetrics(SM_CXSCREEN) - w) / 2, (GetSystemMetrics(SM_CYSCREEN) - h) / 2, w, h, FALSE);
				g_pGraphics->SetScreenSize(w, (m_SelectNo[0] == 2) ? h - 31 : h);
			}
			break;
		}
	}
}

void CSceneOption::Render() {

	for (int i = 0; i < m_MessageCount; i++)
	{
		CRectangle r;
		CGraphicsUtilities::CalculateStringRect(0, 0, m_OptionMessage[i].c_str(), r);
		float wid = g_pGraphics->GetTargetWidth() / 2;
		float hei = g_pGraphics->GetTargetHeight() * 0.1f;
		float windowhei = g_pGraphics->GetTargetHeight() * 0.8f - r.GetHeight();
		windowhei /= m_MessageCount - 1;
		switch (i)
		{
		case 4:
		case 5:
		{
			if (m_SelectNo[0] + 1 == i)
			{
				CGraphicsUtilities::RenderFillRect(wid - r.GetWidth() - 20, hei + windowhei * i, wid - 20, hei + windowhei * i + r.GetHeight(), MOF_COLOR_RED);
			}
			CGraphicsUtilities::RenderString(wid - r.GetWidth() - 20, hei + windowhei * i, m_OptionMessage[i].c_str());
			// BGM,SE‚Ì‘å‚«‚³
			int vol = m_BGMVolume;
			if (i == 5)
				vol = m_SEVolume;
			CGraphicsUtilities::RenderFillRect(g_pGraphics->GetTargetWidth() / 2, hei + windowhei * i - 5, g_pGraphics->GetTargetWidth() / 2 + m_VolumeWidth, r.GetHeight() + hei + windowhei * i + 5, MOF_XRGB(100, 50, 0));
			CGraphicsUtilities::RenderFillRect(g_pGraphics->GetTargetWidth() / 2, hei + windowhei * i - 5, g_pGraphics->GetTargetWidth() / 2 + m_VolumeWidth / 20 * vol, r.GetHeight() + hei + windowhei * i + 5, MOF_XRGB(255, 255, 0));
			// ‹æØ‚èü
			for (int j = 0; j < m_VolumeCount; j++)
			{
				CGraphicsUtilities::RenderLine(g_pGraphics->GetTargetWidth() / 2 + m_VolumeWidth / m_VolumeCount * j, hei + windowhei * i - 5, g_pGraphics->GetTargetWidth() / 2 + m_VolumeWidth / m_VolumeCount * j, r.GetHeight() + hei + windowhei * i + 5, MOF_XRGB(0, 0, 0));
			}
			break;
		}
		default:
			if (m_SelectNo[0] + 1 == i)
			{
				CGraphicsUtilities::RenderFillRect(wid - r.GetWidth() / 2, hei + windowhei * i, wid - r.GetWidth() / 2 + r.GetWidth(), hei + windowhei * i + r.GetHeight(), MOF_COLOR_RED);
			}
			CGraphicsUtilities::RenderString(wid - r.GetWidth() / 2, hei + windowhei * i, m_OptionMessage[i].c_str());
			break;
		}
	}
}

void CSceneOption::RenderDebug() {

	CGraphicsUtilities::RenderString(10, 40, "%d", m_SelectNo[0]);
	CGraphicsUtilities::RenderLine(0, g_pGraphics->GetTargetHeight() * 0.1f, g_pGraphics->GetTargetWidth(), g_pGraphics->GetTargetHeight() * 0.1f, MOF_XRGB(0, 255, 0));
	CGraphicsUtilities::RenderLine(0, g_pGraphics->GetTargetHeight() * 0.9f, g_pGraphics->GetTargetWidth(), g_pGraphics->GetTargetHeight() * 0.9f, MOF_XRGB(0, 255, 0));
}

void CSceneOption::Release() {

}