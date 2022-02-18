/*************************************************************************//*!

					@file	GameApp.cpp
					@brief	��{�Q�[���A�v���B

															@author	�_�c�@��
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"

// �V�[�����\��������N���X"SceneBase"�Ɣh���N���X5��
#include	"SceneBase.h"
#include	"SceneTitle.h"
#include	"SceneMenu.h"
#include	"SceneCharacterSelect.h"
#include	"SceneBattle.h"
#include	"SceneOption.h"
#include	"SceneSelectOpponent.h"

CSceneBase* g_pScene = NULL;
bool		g_bDebug = false;

// ������
MofBool CGameApp::Initialize(void) {
	CUtilities::SetCurrentDirectory("Resource");

	CSoundManager::GetInstance().GetBGM(2).Play();

	MoveWindow(g_pFramework->GetWindow()->GetWindowHandle(), (GetSystemMetrics(SM_CXSCREEN) - 1280) / 2, (GetSystemMetrics(SM_CYSCREEN) - 720) / 2, 1280, 720, FALSE);
	g_pGraphics->SetScreenSize(1280, 720);

	CScalingManager::GetInstance().SetScale(float(1280 / 720));

	g_pScene = new CSceneTitle();
	return TRUE;
}

// �X�V
MofBool CGameApp::Update(void) {
	//�L�[�̍X�V
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

// �`��
MofBool CGameApp::Render(void) {

	// �`��J�n
	g_pGraphics->RenderStart();
	// ��ʂ̃N���A
	g_pGraphics->ClearTarget(0.0f, 0.f, 0.0f, 0.0f, 1.0f, 0);

	g_pScene->Render();
	if (g_bDebug)
	{
		g_pScene->RenderDebug();
	}

	// �`��̏I��
	g_pGraphics->RenderEnd();
	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̉��
		@param			None

		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
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