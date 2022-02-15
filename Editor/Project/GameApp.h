/*************************************************************************//*!

					@file	GameApp.h
					@brief	��{�Q�[���A�v���B

															@author	�_�c�@��
															@date	2014.05.14
*//**************************************************************************/

#pragma once

//INCLUDE
#include    "GameDefine.h"
#include	"resource.h"


bool OpenFileDialog(HWND hWnd, int mode, const char* Title, const char* Filter, const char* DefExt, char* path);
bool LoadBackTexture(HWND hWnd);
bool LoadChipTexture(HWND hWnd);
bool LoadEnemyTexture(HWND hWnd);
bool LoadItemTexture(HWND hWnd);
LRESULT CALLBACK MapStateDlgProc(HWND hWnd, UINT msg, WPARAM wpar, LPARAM lpar);
bool LoadMapData(int i);
bool SaveMapData(int i);


/*******************************//*!
@brief	��{�Q�[���A�v���B

@author	�_�c�@��
*//********************************/
class CGameApp : public CSingleGameApplication {
public:

	/*************************************************************************//*!
			@brief			�R���X�g���N�^
			@param			None

			@return			None
	*//**************************************************************************/
	CGameApp() {}
	/*************************************************************************//*!
			@brief			�f�X�g���N�^
			@param			None

			@return			None
	*//**************************************************************************/
	virtual ~CGameApp() { Release(); }
	/*************************************************************************//*!
			@brief			�A�v���P�[�V�����̏�����
			@param			None

			@return			TRUE		����<br>
							����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
	*//**************************************************************************/
	virtual MofBool Initialize(void);
	/*************************************************************************//*!
			@brief			�A�v���P�[�V�����̍X�V
			@param			None

			@return			TRUE		����<br>
							����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
	*//**************************************************************************/
	virtual MofBool Update(void);
	/*************************************************************************//*!
			@brief			�A�v���P�[�V�����̕`��
			@param			None

			@return			TRUE		����<br>
							����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
	*//**************************************************************************/
	virtual MofBool Render(void);
	/*************************************************************************//*!
			@brief			�A�v���P�[�V�����̉��
			@param			None

			@return			TRUE		����<br>
							����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
	*//**************************************************************************/
	virtual MofBool Release(void);
};
