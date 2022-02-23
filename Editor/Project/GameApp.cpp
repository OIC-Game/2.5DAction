/*************************************************************************//*!

					@file	GameApp.cpp
					@brief	��{�Q�[���A�v���B

															@author	�_�c�@��
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"

#include "Title.h"
#include "Game.h"
#include "GameClear.h"
#include "GameOver.h"
#include "GameEditor.h"

CScensBace*					gpScene = NULL;
bool						gbDebug = true;
bool						gbEditor = false;
int							g_Width[2];
int							g_Height[2];
bool						g_bFullScreen = false;

/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̏�����
		@param			None

		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Initialize(void) {
	//���\�[�X�z�u�̃f�B���N�g���̐ݒ�
	CUtilities::SetCurrentDirectory("Resource");

	g_Width[0] = 1024;
	g_Width[1] = GetSystemMetrics(SM_CXSCREEN);
	g_Height[0] = 768;
	g_Height[1] = GetSystemMetrics(SM_CYSCREEN);

	g_pGraphics->SetScreenSize(g_Width[0], g_Height[0]);

	gpScene = new CTitle();
	gpScene->Initialize();
	
	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̍X�V
		@param			None

		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/

MofBool CGameApp::Update(void) {
	//�L�[�̍X�V
	g_pInput->RefreshKey();
	if (g_pInput->IsKeyPush(MOFKEY_SPACE))
	{
		if (g_bFullScreen)
			g_pGraphics->SetScreenSize(g_Width[0], g_Height[0]);
		else
		{
			MoveWindow(g_pFramework->GetWindow()->GetWindowHandle(),-10,0,g_Width[1],g_Height[1],FALSE);
			g_pGraphics->SetScreenSize(g_Width[1], g_Height[1]);
		}
		g_bFullScreen = !g_bFullScreen;
	}

	if (g_pInput->IsKeyPush(MOFKEY_F1))
	{
		gbDebug = !gbDebug;
	}

	int StageNo = 0;
	gpScene->Update();
	if (gpScene->IsEnd())
	{
		StageNo = gpScene->GetStageNo();
		int change = gpScene->GetNextScene();
		gpScene->Release();
		delete gpScene;

		switch (change)
		{
		case SCENENO_TITLE:
			gpScene = new CTitle();
			gpScene->SetScene(SCENENO_TITLE);
			gpScene->SetStageNo(0);
			break;
		case SCENENO_GAME:
			gpScene = new CGame();
			gpScene->SetScene(SCENENO_GAME);
			gpScene->SetStageNo(StageNo);
			break;
		case SCENENO_GAMECLEAR:
			gpScene = new CGameClear();
			gpScene->SetScene(SCENENO_GAMECLEAR);
			gpScene->SetStageNo(0);
			break;
		case SCENENO_GAMEOVER:
			gpScene = new CGameOver();
			gpScene->SetScene(SCENENO_GAMEOVER);
			gpScene->SetStageNo(0);
			break;
		case SCENENO_EDITOR:
			gpScene = new CGameEditor();
			gpScene->SetScene(SCENENO_EDITOR);
			gpScene->SetStageNo(StageNo);
			break;
		default:
			break;
		}
		gpScene->Load();
		gpScene->Initialize();
	}

	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̕`��
		@param			None

		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/

MofBool CGameApp::Render(void) {

	// �`��J�n
	g_pGraphics->RenderStart();
	// ��ʂ̃N���A
	g_pGraphics->ClearTarget(0.0f, 0.f, 0.0f, 0.0f, 1.0f, 0);

	gpScene->Render();
	if (gbDebug)
	{
		gpScene->RenderDebug();
	}

	//�`��̏I��
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
	gpScene->Release();
	if (gpScene)
	{
		delete gpScene;
		gpScene = NULL;
	}
	return TRUE;
}

bool OpenFileDialog(HWND hWnd, int mode, const char* Title, const char* Filter, const char* DefExt, char* path) {
	bool re = false;
	if (gpScene->GetScene() == SCENENO_EDITOR)
		re = gpScene->OpenFileDialog(hWnd, mode, Title, Filter, DefExt, path);
	return re;
}

bool LoadBackTexture(HWND hWnd) {
	bool re = false;
	if (gpScene->GetScene() == SCENENO_EDITOR)
		re = gpScene->LoadBackTexture(hWnd);
	return re;
}

bool LoadChipTexture(HWND hWnd) {
	bool re = false;
	if (gpScene->GetScene() == SCENENO_EDITOR)
		re = gpScene->LoadChipTexture(hWnd);
	return re;
}

bool LoadEnemyTexture(HWND hWnd) {
	bool re = false;
	if (gpScene->GetScene() == SCENENO_EDITOR)
		re = gpScene->LoadEnemyTexture(hWnd);
	return re;
}

bool LoadItemTexture(HWND hWnd) {
	bool re = false;
	if (gpScene->GetScene() == SCENENO_EDITOR)
		re = gpScene->LoadItemTexture(hWnd);
	return re;
}

LRESULT CALLBACK MapStateDlgProc(HWND hWnd, UINT msg, WPARAM wpar, LPARAM lpar) {
	bool re = false;
	if (gpScene->GetScene() == SCENENO_EDITOR)
		re = gpScene->MapStateDlgProc(hWnd, msg, wpar, lpar);

	switch (msg)
	{
	case WM_COMMAND:
		switch (LOWORD(wpar))
		{
		case IDCANCEL:
			EndDialog(hWnd, 0);
			break;
		default:
			return FALSE;
		}
		break;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		break;
	default:
		return FALSE;
	}

	return re;
}

bool LoadMapData(int i) {
	bool re = false;
	if (gpScene->GetScene() == SCENENO_EDITOR)
		re = gpScene->LoadMapData(i);
	return re;
}

bool SaveMapData(int i) {
	bool re = false;
	if (gpScene->GetScene() == SCENENO_EDITOR)
		re = gpScene->SaveMapData(i);
	return re;
}