/*************************************************************************//*!

					@file	GameApp.cpp
					@brief	基本ゲームアプリ。

															@author	濱田　享
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"

// シーンを構成する基底クラス"SceneBase"と派生クラス5つ
#include	"SceneBase.h"
#include	"SceneTitle.h"
#include	"SceneMenu.h"
#include	"SceneCharacterSelect.h"
#include	"SceneBattle.h"
#include	"SceneOption.h"
#include	"SceneSelectOpponent.h"

CSceneBase* g_pScene = NULL;
bool		g_bDebug = false;

// 初期化
MofBool CGameApp::Initialize(void) {
	CUtilities::SetCurrentDirectory("Resource");

	CSoundManager::GetInstance().GetBGM(2).Play();

	MoveWindow(g_pFramework->GetWindow()->GetWindowHandle(), (GetSystemMetrics(SM_CXSCREEN) - 1280) / 2, (GetSystemMetrics(SM_CYSCREEN) - 720) / 2, 1280, 720, FALSE);
	g_pGraphics->SetScreenSize(1280, 720);

	CScalingManager::GetInstance().SetScale(float(1280 / 720));

	g_pScene = new CSceneTitle();
	return TRUE;
}

// 更新
MofBool CGameApp::Update(void) {
	//キーの更新
	g_pInput->RefreshKey();

	CInputManager::GetInstance().Refresh();

	if (g_pInput->IsKeyPush(MOFKEY_F1))
	{
		g_bDebug = !g_bDebug;
	}

	g_pScene->Update();
	if (g_pScene->IsEnd())
	{
		int selectno[2];
		for (int i = 0; i < 2; i++)
		{
			selectno[i] = g_pScene->GetSelectNo(i);
		}
		int change = g_pScene->GetNextScene();
		g_pScene->Release();
		delete g_pScene;

		switch (change)
		{
		case SCENENO_TITLE:
			g_pScene = new CSceneTitle();
			g_pScene->SetScene(SCENENO_TITLE);
			break;
		case SCENENO_MENU:
			g_pScene = new CSceneMenu();
			g_pScene->SetScene(SCENENO_MENU);
			break;
		case SCENENO_OPPOENT:
			g_pScene = new CSceneSelectOpponent();
			g_pScene->SetScene(SCENENO_OPPOENT);
			break;
		case SCENENO_CHARACTERSELECT:
			CSoundManager::GetInstance().BGMStop(2);
			CSoundManager::GetInstance().BGMPlay(2);
			g_pScene = new CSceneCharacterSelect();
			g_pScene->SetScene(SCENENO_CHARACTERSELECT);
			for (int i = 0; i < 2; i++)
			{
				g_pScene->SetSelectNo(i, selectno[i]);
			}
			break;
		case SCENENO_BATTLE:
			g_pScene = new CSceneBattle();
			g_pScene->SetScene(SCENENO_BATTLE);
			for (int i = 0; i < 2; i++)
			{
				g_pScene->SetSelectNo(i, selectno[i]);
			}
			break;
		case SCENENO_OPTION:
			g_pScene = new CSceneOption();
			g_pScene->SetScene(SCENENO_OPTION);
			break;
		default:
			break;
		}
		g_pScene->Initialize();
	}
	return TRUE;
}

// 描画
MofBool CGameApp::Render(void) {

	// 描画開始
	g_pGraphics->RenderStart();
	// 画面のクリア
	g_pGraphics->ClearTarget(0.0f, 0.f, 0.0f, 0.0f, 1.0f, 0);

	g_pScene->Render();
	if (g_bDebug)
	{
		g_pScene->RenderDebug();
	}

	// 描画の終了
	g_pGraphics->RenderEnd();
	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの解放
		@param			None

		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Release(void) {
	g_pScene->Release();
	if (g_pScene)
	{
		delete g_pScene;
		g_pScene = NULL;
	}
	CSoundManager::GetInstance().Release();
	CTextureManager::GetInstance().Release();
	return TRUE;
}