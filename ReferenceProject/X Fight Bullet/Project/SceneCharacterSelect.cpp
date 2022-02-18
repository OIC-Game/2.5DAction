#include "SceneCharacterSelect.h"

CSceneCharacterSelect::CSceneCharacterSelect() :
	m_bDecide(),
	m_SelectVsCpu(0) {
	memset(m_bDecide, false, sizeof(m_bDecide));
}

CSceneCharacterSelect::~CSceneCharacterSelect() {

}

bool CSceneCharacterSelect::Load() {
	return true;
}

void CSceneCharacterSelect::Initialize() {

}

void CSceneCharacterSelect::Update() {
	if (m_bMenu)
	{
		RetrunMenu();
		return;
	}
	if (COpponentManager::GetInstance().GetOpponent())
	{
		int pno = CControlManager::GetInstance().GetNo(0);

		if (CInputManager::GetInstance().GetPush(pno, 0))
		{
			if (m_bDecide[m_SelectVsCpu])
			{
				m_bDecide[m_SelectVsCpu] = false;
				m_SelectVsCpu--;
			}
			else
			{
				m_bMenu = true;
				m_MenuSelect = 0;
				m_MenuPlayer = pno;
			}
		}
		if (m_bDecide[0] == true && m_bDecide[1] == true)
		{
			if (CInputManager::GetInstance().GetPush(pno, 8))
			{
				m_bEnd = true;
				m_NextSceneNo = SCENENO_BATTLE;
				CControlManager::GetInstance().SetNo(1,5);
			}
		}
		if (m_SelectVsCpu == 2) { return; }
		CInputManager::GetInstance().SelectHorizontal(pno, m_SelectNo[m_SelectVsCpu], m_CharacterCount + 1, 0, true);
		if (CInputManager::GetInstance().GetPush(pno, 1))
		{
			m_bDecide[m_SelectVsCpu] = true;
			m_SelectVsCpu++;
		}
	}
	else
	{
		for (int i = 0; i < 2; i++)
		{
			int pno = CControlManager::GetInstance().GetNo(i);
			if (pno == -1)
			{
				for (int j = 0; j < 5; j++)
				{
					if (j == CControlManager::GetInstance().GetNo(0)) { continue; }
					if (CInputManager::GetInstance().GetPush(j, 1))
					{
						CControlManager::GetInstance().SetNo(i, j);
						break;
					}
				}
			}
			if (CInputManager::GetInstance().GetPush(pno, 0))
			{
				if (m_bDecide[i])
					m_bDecide[i] = false;
				else
				{
					m_bMenu = true;
					m_MenuSelect = 0;
					m_MenuPlayer = pno;
				}
			}
			if (m_bDecide[0] == true && m_bDecide[1] == true)
			{
				if (CInputManager::GetInstance().GetPush(pno, 8))
				{
					m_bEnd = true;
					m_NextSceneNo = SCENENO_BATTLE;
				}
			}
			if (m_bDecide[i]) { continue; }
			CInputManager::GetInstance().SelectHorizontal(pno, m_SelectNo[i], m_CharacterCount + 1, 0, true);
			if (CInputManager::GetInstance().GetPush(pno, 1))
			{
				m_bDecide[i] = true;
			}
		}
	}
}

void CSceneCharacterSelect::RetrunMenu() {
	CInputManager::GetInstance().SelectVertical(m_MenuPlayer, m_MenuSelect, m_MenuItemCount, 0, true);
	if (CInputManager::GetInstance().GetPush(m_MenuPlayer, 1))
	{
		if (m_MenuSelect == 0)
		{
			m_bEnd = true;
			m_NextSceneNo = SCENENO_MENU;
		}
		else
		{
			m_bMenu = false;
		}
	}
	else if (CInputManager::GetInstance().GetPush(m_MenuPlayer, 0))
	{
		m_bMenu = false;
	}
}

void CSceneCharacterSelect::Render() {
	//画面下のプレイヤーを分ける線
	float w = g_pGraphics->GetTargetWidth();
	float h = g_pGraphics->GetTargetHeight();

	CGraphicsUtilities::RenderLine(w * 0.5f, h * 0.9f, w * 0.5f, h, MOF_XRGB(0, 255, 0));
	CGraphicsUtilities::RenderLine(0, h * 0.9f, w * 0.5f, h * 0.9f, MOF_XRGB(255, 0, 0));
	CGraphicsUtilities::RenderLine(w * 0.5f, h * 0.9f, w, h * 0.9f, MOF_XRGB(0, 255, 255));
	CGraphicsUtilities::RenderLine(w * 0.2f, h * 0.85f, w * 0.3f, h * 0.9f, MOF_XRGB(255, 0, 0));
	CGraphicsUtilities::RenderLine(w * 0.7f, h * 0.9f, w * 0.8f, h * 0.85f, MOF_XRGB(0, 255, 255));
	CGraphicsUtilities::RenderLine(0, h * 0.85f, w * 0.2f, h * 0.85f, MOF_XRGB(255, 0, 0));
	CGraphicsUtilities::RenderLine(w * 0.8f, h * 0.85f, w, h * 0.85f, MOF_XRGB(0, 255, 255));

	int	step = (m_CharacterCount + 1 % 2 == 0) ? 2 : 1;
	float sw = w * 0.8f;
	sw /= (m_CharacterCount + 1) / step;
	float rectsize = sw * 0.8f;

	//文字
	for (int i = 0; i < m_CharacterCount; i++)
	{
		CRectangle srec;
		CGraphicsUtilities::CalculateStringRect(0, 0, m_CharacterName[i].c_str(), srec);
		float x = (rectsize - srec.GetWidth()) / 2;
		float y = (h * 0.05 - srec.GetHeight()) / 2;
		CGraphicsUtilities::RenderString(w * 0.1f + sw * i + sw * 0.1f + x, h * 0.15f + y, m_CharacterName[i].c_str());
	}

	for (int i = 0; i < 2; ++i)
	{
		//プレイヤーの選択キャラクター
		if (m_SelectNo[0] == m_SelectNo[1])
			CGraphicsUtilities::RenderFillRect(w * 0.1f + sw * m_SelectNo[i] + sw * 0.1f - 2 + i * 4, h * 0.2f - 2 + i * 4, w * 0.1f + sw * m_SelectNo[i] + sw * 0.1f + rectsize - 2 + i * 4, h * 0.2f + rectsize - 2 + i * 4, m_Color[i]);
		else
			CGraphicsUtilities::RenderFillRect(w * 0.1f + sw * m_SelectNo[i] + sw * 0.1f - 2, h * 0.2f - 2, w * 0.1f + sw * m_SelectNo[i] + sw * 0.1f + rectsize + 2, h * 0.2f + rectsize + 2, m_Color[i]);
	}
	//プレイヤーの選択したキャラクター
	RenderStatus();
	for (int i = 0; i < m_CharacterCount + 1; ++i)
	{
		//画像の背景となる四角
		CGraphicsUtilities::RenderFillRect(w * 0.1f + sw * i + sw * 0.1f, h * 0.2f, w * 0.1f + sw * i + sw * 0.1f + rectsize, h * 0.2f + rectsize, MOF_XRGB(150, 150, 100));
	}
	for (int i = 0; i < 4; ++i)
	{
		float scale = rectsize;
		scale /= CTextureManager::GetInstance().GetIcon(i).GetWidth();
		//画像描写
		CTextureManager::GetInstance().GetIcon(i).RenderScale(w * 0.1f + sw * i + sw * 0.1f, h * 0.2f, scale);
	}
	//
	if (m_bDecide[0] == true && m_bDecide[1] == true)
	{
		CRectangle srec;
		CGraphicsUtilities::CalculateStringRect(0, 0, "Pless : SpaceKey", srec);
		CGraphicsUtilities::RenderString((w - srec.GetWidth()) * 0.5f, (h - srec.GetHeight()) * 0.5f, "Pless : SpaceKey");
	}
	if (m_bMenu)
	{
		RenderMenu();
	}
}

void CSceneCharacterSelect::RenderMenu() {
	CRectangle trec;
	CRectangle drec;
	CGraphicsUtilities::CalculateStringRect(0, 0, m_MenuTitle.c_str(), trec);
	drec.Right = MOF_MAX(drec.Right, trec.Right + m_MenuHSpace * 2);
	drec.Bottom += trec.Bottom + m_MenuVSpace * 2;
	for (int i = 0; i < m_MenuItemCount; i++)
	{
		CGraphicsUtilities::CalculateStringRect(0, 0, m_MenuItem[i].c_str(), trec);
		drec.Right = MOF_MAX(drec.Right, trec.Right + m_MenuHSpace * 2);
		drec.Bottom += trec.Bottom + m_MenuVSpace;
	}
	drec.Bottom += m_MenuVSpace;

	//矩形を中央に設置
	float cx = g_pGraphics->GetTargetWidth() * 0.5f;
	float cy = g_pGraphics->GetTargetHeight() * 0.5f;
	float w = drec.GetWidth();
	float h = drec.GetHeight();
	drec.Top = cy - h * 0.5f;
	drec.Bottom = drec.Top + h;
	drec.Left = cx - w * 0.5f;
	drec.Right = drec.Left + w;

	CGraphicsUtilities::RenderFillRect(drec.Left - 2, drec.Top - 2, drec.Right + 2, drec.Bottom + 2, MOF_ARGB(200, 0, 200, 200));
	CGraphicsUtilities::RenderFillRect(drec, MOF_ARGB(200, 0, 0, 0));
	CGraphicsUtilities::CalculateStringRect(0, 0, m_MenuTitle.c_str(), trec);

	CRectangle hrec = drec;
	hrec.Bottom = hrec.Top + trec.Bottom + m_MenuVSpace * 2;
	CGraphicsUtilities::RenderFillRect(hrec, MOF_ARGB(200, 64, 64, 64));

	// 項目の文字を描画
	drec.Top += m_MenuVSpace;
	CGraphicsUtilities::RenderString(cx - trec.GetWidth() * 0.5f, drec.Top, MOF_COLOR_WHITE, m_MenuTitle.c_str());
	drec.Top += trec.Bottom + m_MenuVSpace;

	for (int i = 0; i < m_MenuItemCount; i++)
	{
		CGraphicsUtilities::CalculateStringRect(0, 0, m_MenuItem[i].c_str(), trec);
		CGraphicsUtilities::RenderString(cx - trec.GetWidth() * 0.5, drec.Top + m_MenuVSpace, ((m_MenuSelect == i) ? MOF_XRGB(255, 255, 255) : MOF_XRGB(128, 128, 128)), m_MenuItem[i].c_str());
		drec.Top += trec.Bottom + m_MenuVSpace;
	}
}

void CSceneCharacterSelect::RenderStatus() {
	float w = g_pGraphics->GetTargetWidth();
	float h = g_pGraphics->GetTargetHeight();

	for (int i = 0; i < 2; i++)
	{
		std::string		player = (i == 0) ? "1プレイヤー" : "2プレイヤー";
		CRectangle srec;
		CGraphicsUtilities::CalculateStringRect(0, 0, player.c_str(), srec);
		float x = (i == 0) ? w * 0.05f : w * 0.95f - srec.GetWidth();
		float y = (h * 0.05f - srec.GetHeight()) / 2;

		//プレイヤー
		CGraphicsUtilities::RenderString(x, h * 0.85f + y, player.c_str());
	}

	for (int i = 0; i < 2; i++)
	{
		CRectangle srec;
		CGraphicsUtilities::CalculateStringRect(0, 0, (m_SelectNo[i] == m_CharacterCount) ? "???" : m_CharacterName[m_SelectNo[i]].c_str(), srec);
		float y = (h * 0.05f - srec.GetHeight()) / 2;
		CGraphicsUtilities::RenderString((i == 0) ? w * 0.05f : w * 0.95f - srec.GetWidth(), h * 0.8f + y, (m_SelectNo[i] == m_CharacterCount) ? "???" : m_CharacterName[m_SelectNo[i]].c_str());
		if (m_bDecide[i] == true)
		{
			CGraphicsUtilities::RenderString((i == 0) ? w * 0.15f : w * 0.83f, h * 0.8f + y, "OK!");
		}
	}
	w /= 6;

	for (int i = 0; i < 2; i++)
	{
		if (!COpponentManager::GetInstance().GetOpponent())
		{
			if (i == 1 && CControlManager::GetInstance().GetNo(i) == -1)
			{
				std::string	message;
				message = (CControlManager::GetInstance().GetNo(0) == 0) ? "Press B" : "Press B or Z";
				CRectangle srec;
				CGraphicsUtilities::CalculateStringRect(0, 0, message.c_str(), srec);

				float x = w * 1.5;
				float y = h * 0.05f - srec.GetHeight() / 2;
				CGraphicsUtilities::RenderString(w * 3 * i + x - srec.GetWidth() / 2, h * 0.9f + y, message.c_str());

				return;
			}
		}
		for (int j = 0; j < 3; j++)
		{
			std::string	status;
			switch (j)
			{
			case 0:
				status = "ライフ";
				break;
			case 1:
				status = "最大SP";
				break;
			default:
				status = "スピード";
				break;
			}
			float fstatus;
			switch (j)
			{
			case 0:
				fstatus = m_CharacterLife[m_SelectNo[i]];
				break;
			case 1:
				fstatus = m_CharacterEnergy[m_SelectNo[i]];
				break;
			default:
				fstatus = m_CharacterSpeed[m_SelectNo[i]];
				break;
			}
			CRectangle srec;
			CGraphicsUtilities::CalculateStringRect(0, 0, status.c_str(), srec);
			float x = w * j + w / 2;
			float y = (h * 0.05f - srec.GetHeight()) / 2;
			CGraphicsUtilities::RenderString(w * 3 * i + x - srec.GetWidth() / 2, h * 0.9f + y, status.c_str());
			CGraphicsUtilities::RenderString(w * 3 * i + x - srec.GetWidth() / 2, h * 0.95f + y, (m_SelectNo[i] == m_CharacterCount) ? "???" : "%.0f", fstatus);
		}
	}
}

void CSceneCharacterSelect::RenderDebug() {

	CGraphicsUtilities::RenderString(20, 10, "キャラクター選択");

	CGraphicsUtilities::RenderLine(g_pGraphics->GetTargetWidth() * 0.1f, 0, g_pGraphics->GetTargetWidth() * 0.1f, g_pGraphics->GetTargetHeight(), MOF_XRGB(0, 255, 0));
	CGraphicsUtilities::RenderLine(g_pGraphics->GetTargetWidth() * 0.9f, 0, g_pGraphics->GetTargetWidth() * 0.9f, g_pGraphics->GetTargetHeight(), MOF_XRGB(0, 255, 0));

	CGraphicsUtilities::RenderLine(0, g_pGraphics->GetTargetHeight(), g_pGraphics->GetTargetWidth(), g_pGraphics->GetTargetHeight(), MOF_XRGB(0, 255, 0));

	float w = g_pGraphics->GetTargetWidth() / 6;
	for (int i = 0; i < 6; i++)
	{
		CGraphicsUtilities::RenderLine(w * i, g_pGraphics->GetTargetHeight() * 0.9f, w * i, g_pGraphics->GetTargetHeight(), MOF_XRGB(0, 255, 0));
	}
}

void CSceneCharacterSelect::Release() {
}