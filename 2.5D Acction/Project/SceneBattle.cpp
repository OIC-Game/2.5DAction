#include "SceneBattle.h"

CSceneBattle::CSceneBattle() :
	m_RemCountDown(0),
	m_EndPattern(0)
{
	memset(m_bLose, false, sizeof(m_bLose));
}

CSceneBattle::~CSceneBattle() {

}

bool CSceneBattle::Load() {
	return true;
}

void CSceneBattle::Initialize() {
	CSoundManager::GetInstance().BGMStop();
	CSoundManager::GetInstance().GetBGM(1).Play();
	for (int i = 0; i < m_PlayerCount; i++)
	{
		int selectno = (m_SelectNo[i] == 4) ? rand() % 4 : m_SelectNo[i];
		free(m_Player[i]);
		switch (selectno)
		{
		case 0:
			m_Player[i] = new Anya;
			break;
		case 1:
			m_Player[i] = new Lovey;
			break;
		case 2:
			m_Player[i] = new JOKER;
			break;
		case 3:
			m_Player[i] = new YamadaTarou;
			break;
		default:
			break;
		}
		if (COpponentManager::GetInstance().GetOpponent() && i == 1)
			m_Player[i]->PosInitialize(1);
		else
			m_Player[i]->PosInitialize(i);
		m_bLose[i] = false;
	}
	for (int i = 0; i < m_PlayerCount; i++)
	{
		m_Player[i]->Initialize((i == 0) ? m_Player[1]->GetCircle() : m_Player[0]->GetCircle());
	}
	CJokerSkillManager::GetInstance().Initialize();
	m_RemCountDown = 240;
	m_bGameEndMenu = false;
	m_bPauseMenu = false;
	m_EndPattern = -1;
}

void CSceneBattle::Update() {
	CJokerSkillManager::GetInstance().Update();
	if (m_bPauseMenu)
	{
		PauseMenu();
		return;
	}

	if (m_bGameEndMenu)
	{
		GameEndMenu();

		// 試合終了後も撃った弾は飛んでいく
		for (int i = 0; i < m_PlayerCount; i++)
		{
			m_Player[i]->Fly((i == 0) ? m_Player[1]->GetCircle() : m_Player[0]->GetCircle());
		}
	}
	else
	{
		if (m_RemCountDown > 0)
		{
			m_RemCountDown--;
			if (m_RemCountDown == 60)
			{
				CSoundManager::GetInstance().GetSE(12).Play();
			}
		}

		// プレイヤーのどちらかのライフがなければ以降の処理を行わない
		for (int i = 0; i < m_PlayerCount; i++)
		{
			if (m_bLose[i])
				m_bGameEndMenu = true;
		}
		if (m_bGameEndMenu)
		{
			if (m_bLose[0] && m_bLose[1])
				m_EndPattern = 0;
			else
				m_EndPattern = (m_bLose[1]) ? 1 : 2;
			m_MenuPlayer = (m_bLose[1]) ? CControlManager::GetInstance().GetNo(0) : CControlManager::GetInstance().GetNo(1);
			return;
		}
		for (int i = 0; i < m_PlayerCount; i++)
		{
			m_Player[i]->UpdateMove();
			m_Player[i]->Fly((i == 0) ? m_Player[1]->GetCircle() : m_Player[0]->GetCircle());
			if (CInputManager::GetInstance().GetPush(i, 8))
			{
				m_bPauseMenu = true;
				m_MenuPlayer = i;
			}
		}
		if (m_RemCountDown > 60) { return; }
		for (int i = 0; i < m_PlayerCount; i++)
		{
			m_Player[i]->Update((i == 0) ? m_Player[1]->GetCircle() : m_Player[0]->GetCircle());
		}
		for (int i = 0; i < m_PlayerCount; i++)
		{
			for (int j = 0; j < m_PlayerCount; j++)
			{
				if (i == j) { continue; }
				int damage = 0, skill = 0;
				m_Player[i]->Collision(m_Player[j]->GetCircle(), m_Player[j]->GetGrazeCircle(), damage, skill);
				m_Player[j]->Damage(damage, skill);
			}
		}
		for (int i = 0; i < m_PlayerCount; i++)
		{
			if (m_Player[i]->GetLose())
			{
				m_bLose[i] = true;
				CSoundManager::GetInstance().GetSE(1).Play();
			}
		}
	}
}

void CSceneBattle::PauseMenu() {
	CInputManager::GetInstance().SelectVertical(m_MenuPlayer, m_PauseMenuSelect, m_PauseMenuItemCount, 0, true);
	if (CInputManager::GetInstance().GetPush(m_MenuPlayer, 2))
	{
		if (m_PauseMenuSelect == 0)
		{
			m_bPauseMenu = false;
		}
		else if (m_PauseMenuSelect == 1)
		{
			Release();
			Initialize();
		}
		else if (m_PauseMenuSelect == 2)
		{
			m_bEnd = true;
			m_NextSceneNo = SCENENO_CHARACTERSELECT;
		}
		else
		{
			m_bEnd = true;
			m_NextSceneNo = SCENENO_MENU;
		}
		m_PauseMenuSelect = 0;
	}
	else if (CInputManager::GetInstance().GetPush(m_MenuPlayer, 0) || CInputManager::GetInstance().GetPush(m_MenuPlayer, 8))
	{
		m_bPauseMenu = false;
		m_PauseMenuSelect = 0;
	}
}

void CSceneBattle::GameEndMenu() {
	CInputManager::GetInstance().SelectVertical(m_MenuPlayer, m_GameEndMenuSelect, m_GameEndMenuItemCount, 0, true);
	if (CInputManager::GetInstance().GetPush(m_MenuPlayer, 1))
	{
		if (m_GameEndMenuSelect == 0)
		{
			Release();
			Initialize();
		}
		else if (m_GameEndMenuSelect == 1)
		{
			m_bEnd = true;
			m_NextSceneNo = SCENENO_CHARACTERSELECT;
		}
		else
		{
			m_bEnd = true;
			m_NextSceneNo = SCENENO_MENU;
		}
	}
}

void CSceneBattle::Render() {
	RenderCountDown();
	// 自機となる円の表示
	for (int i = 0; i < m_PlayerCount; ++i)
	{
		m_Player[i]->Render();
	}

	RenderUI();
	if (m_bGameEndMenu)
	{
		RenderGameEndMenu();
	}
	else if (m_bPauseMenu)
	{
		RenderPauseMenu();
	}
}

void CSceneBattle::RenderCountDown() {
	float w = g_pGraphics->GetTargetWidth();
	float h = g_pGraphics->GetTargetHeight();

	CRectangle srec;

	if (m_RemCountDown > 180)
	{
		CGraphicsUtilities::CalculateStringRect(0, 0, "3", srec);
		CGraphicsUtilities::RenderString(w * 0.4f - srec.GetWidth() * 0.5f, h * 0.4f, "3");
	}
	else if (m_RemCountDown > 120)
	{
		CGraphicsUtilities::CalculateStringRect(0, 0, "2", srec);
		CGraphicsUtilities::RenderString(w * 0.5f - srec.GetWidth() * 0.5f, h * 0.4f, "2");
	}
	else if (m_RemCountDown > 60)
	{
		CGraphicsUtilities::CalculateStringRect(0, 0, "1", srec);
		CGraphicsUtilities::RenderString(w * 0.6f - srec.GetWidth() * 0.5f, h * 0.4f, "1");
	}
	else if (m_RemCountDown > 0)
	{
		CGraphicsUtilities::CalculateStringRect(0, 0, "Start!", srec);
		CGraphicsUtilities::RenderString(w * 0.5f - srec.GetWidth() * 0.5f, h * 0.4f, "Start!");
	}
}

void CSceneBattle::RenderUI() {
	float h = g_pGraphics->GetTargetHeight();
	float w = g_pGraphics->GetTargetWidth();
	CGraphicsUtilities::RenderLine(w / 16 * 7, 0, w / 16 * 7, h / 8 * 7, MOF_XRGB(0, 255, 0));
	CGraphicsUtilities::RenderLine(w / 16 * 9, 0, w / 16 * 9, h / 8 * 7, MOF_XRGB(0, 255, 0));

	float scale = h;
	scale /= 720;

	CGraphicsUtilities::RenderFillRect(0, h / 8 * 7, g_pGraphics->GetTargetWidth() / 2, g_pGraphics->GetTargetHeight(), MOF_XRGB(255, 0, 0));
	CGraphicsUtilities::RenderFillRect(g_pGraphics->GetTargetWidth() / 2, h / 8 * 7, g_pGraphics->GetTargetWidth(), g_pGraphics->GetTargetHeight(), MOF_XRGB(0, 0, 255));

	// ライフバー、スキルバー
	float BerHei = m_BerHeight * scale;
	float BerWid = m_BerWidth * scale;
	float SkillBerHei = h * 0.99f;
	float LifeBerHei = SkillBerHei - BerHei - h * 0.02f;
	// 1P
	CGraphicsUtilities::RenderFillRect(w / 16 * 7 - BerWid - m_BerEdgeSize, SkillBerHei - BerHei - m_BerEdgeSize, w / 16 * 7 + m_BerEdgeSize, SkillBerHei + m_BerEdgeSize, MOF_XRGB(0, 0, 0));
	CGraphicsUtilities::RenderFillRect(w / 16 * 7 - BerWid, SkillBerHei - BerHei, w / 16 * 7, SkillBerHei, MOF_XRGB(50, 50, 0));
	CGraphicsUtilities::RenderFillRect(w / 16 * 7 - BerWid - m_BerEdgeSize, LifeBerHei - BerHei - m_BerEdgeSize, w / 16 * 7 + m_BerEdgeSize, LifeBerHei + m_BerEdgeSize, MOF_XRGB(0, 0, 0));

	CGraphicsUtilities::RenderFillRect(w / 16 * 7 - BerWid, SkillBerHei - BerHei, w / 16 * 7 - BerWid * (1 - m_Player[0]->GetSkillPercent()), SkillBerHei, MOF_XRGB(255, 255, 0));
	CGraphicsUtilities::RenderFillRect(w / 16 * 7 - BerWid, LifeBerHei - BerHei, w / 16 * 7 - BerWid * (1 - m_Player[0]->GetLifePercent()), LifeBerHei, MOF_XRGB(0, 255, 0));
	// 2P
	CGraphicsUtilities::RenderFillRect(w / 16 * 9 - m_BerEdgeSize, SkillBerHei - BerHei - m_BerEdgeSize, w / 16 * 9 + BerWid + m_BerEdgeSize, SkillBerHei + m_BerEdgeSize, MOF_XRGB(0, 0, 0));
	CGraphicsUtilities::RenderFillRect(w / 16 * 9, SkillBerHei - BerHei, w / 16 * 9 + BerWid, SkillBerHei, MOF_XRGB(50, 50, 0));
	CGraphicsUtilities::RenderFillRect(w / 16 * 9 - m_BerEdgeSize, LifeBerHei - BerHei - m_BerEdgeSize, w / 16 * 9 + BerWid + m_BerEdgeSize, LifeBerHei + m_BerEdgeSize, MOF_XRGB(0, 0, 0));

	CGraphicsUtilities::RenderFillRect(w / 16 * 9, SkillBerHei - BerHei, w / 16 * 9 + BerWid * m_Player[1]->GetSkillPercent(), SkillBerHei, MOF_XRGB(255, 255, 0));
	CGraphicsUtilities::RenderFillRect(w / 16 * 9, LifeBerHei - BerHei, w / 16 * 9 + BerWid * m_Player[1]->GetLifePercent(), LifeBerHei, MOF_XRGB(0, 255, 0));
	//
	CGraphicsUtilities::RenderLine(w / 16 * 7 - BerWid / 3, SkillBerHei - BerHei, w / 16 * 7 - BerWid / 3, SkillBerHei, MOF_XRGB(0, 0, 0));
	CGraphicsUtilities::RenderLine(w / 16 * 7 - BerWid / 3 * 2, SkillBerHei - BerHei, w / 16 * 7 - BerWid / 3 * 2, SkillBerHei, MOF_XRGB(0, 0, 0));

	CGraphicsUtilities::RenderLine(w / 16 * 9 + BerWid / 3, SkillBerHei - BerHei, w / 16 * 9 + BerWid / 3, SkillBerHei, MOF_XRGB(0, 0, 0));
	CGraphicsUtilities::RenderLine(w / 16 * 9 + BerWid / 3 * 2, SkillBerHei - BerHei, w / 16 * 9 + BerWid / 3 * 2, SkillBerHei, MOF_XRGB(0, 0, 0));
}

void CSceneBattle::RenderPauseMenu() {
	CRectangle trec;
	CRectangle drec;
	CGraphicsUtilities::CalculateStringRect(0, 0, m_PauseMenuTitle.c_str(), trec);
	drec.Right = MOF_MAX(drec.Right, trec.Right + m_MenuHSpace * 2);
	drec.Bottom += trec.Bottom + m_MenuVSpace * 2;
	for (int i = 0; i < m_PauseMenuItemCount; i++)
	{
		CGraphicsUtilities::CalculateStringRect(0, 0, m_PauseMenuItem[i].c_str(), trec);
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
	CGraphicsUtilities::CalculateStringRect(0, 0, m_PauseMenuTitle.c_str(), trec);

	CRectangle hrec = drec;
	hrec.Bottom = hrec.Top + trec.Bottom + m_MenuVSpace * 2;
	CGraphicsUtilities::RenderFillRect(hrec, MOF_ARGB(200, 64, 64, 64));

	// 項目の文字を描画
	drec.Top += m_MenuVSpace;
	CGraphicsUtilities::RenderString(cx - trec.GetWidth() * 0.5f, drec.Top, MOF_COLOR_WHITE, m_PauseMenuTitle.c_str());
	drec.Top += trec.Bottom + m_MenuVSpace;

	for (int i = 0; i < m_PauseMenuItemCount; i++)
	{
		CGraphicsUtilities::CalculateStringRect(0, 0, m_PauseMenuItem[i].c_str(), trec);
		CGraphicsUtilities::RenderString(cx - trec.GetWidth() * 0.5, drec.Top + m_MenuVSpace, ((m_PauseMenuSelect == i) ? MOF_XRGB(255, 255, 255) : MOF_XRGB(128, 128, 128)), m_PauseMenuItem[i].c_str());
		drec.Top += trec.Bottom + m_MenuVSpace;
	}
}

void CSceneBattle::RenderGameEndMenu() {
	CRectangle trec;
	CRectangle drec;
	CGraphicsUtilities::CalculateStringRect(0, 0, m_GameEndMenuTitle[m_EndPattern].c_str(), trec);
	drec.Right = MOF_MAX(drec.Right, trec.Right + m_MenuHSpace * 2);
	drec.Bottom += trec.Bottom + m_MenuVSpace * 2;
	for (int i = 0; i < m_GameEndMenuItemCount; i++)
	{
		CGraphicsUtilities::CalculateStringRect(0, 0, m_GameEndMenuItem[i].c_str(), trec);
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
	CGraphicsUtilities::CalculateStringRect(0, 0, m_GameEndMenuTitle[m_EndPattern].c_str(), trec);

	CRectangle hrec = drec;
	hrec.Bottom = hrec.Top + trec.Bottom + m_MenuVSpace * 2;
	CGraphicsUtilities::RenderFillRect(hrec, MOF_ARGB(200, 64, 64, 64));

	// 項目の文字を描画
	drec.Top += m_MenuVSpace;
	CGraphicsUtilities::RenderString(cx - trec.GetWidth() * 0.5f, drec.Top, MOF_COLOR_WHITE, m_GameEndMenuTitle[m_EndPattern].c_str());
	drec.Top += trec.Bottom + m_MenuVSpace;

	for (int i = 0; i < m_GameEndMenuItemCount; i++)
	{
		CGraphicsUtilities::CalculateStringRect(0, 0, m_GameEndMenuItem[i].c_str(), trec);
		CGraphicsUtilities::RenderString(cx - trec.GetWidth() * 0.5, drec.Top + m_MenuVSpace, ((m_GameEndMenuSelect == i) ? MOF_XRGB(255, 255, 255) : MOF_XRGB(128, 128, 128)), m_GameEndMenuItem[i].c_str());
		drec.Top += trec.Bottom + m_MenuVSpace;
	}
}

void CSceneBattle::RenderDebug() {

}

void CSceneBattle::Release() {
	for (int i = 0; i < 2; i++)
	{
		m_Player[i]->Release();
		free(m_Player[i]);
		m_Player[i] = NULL;
	}
}