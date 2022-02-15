#include "WindowProc.h"
#include "resource.h"
#include "GameApp.h"

// �R���X�g���N�^
CWindowProc::CWindowProc() :
	CDefWindowProc() {
}

// �f�X�g���N�^
CWindowProc::~CWindowProc() {
}

// �E�C���h�E�v���V�[�W��
MofProcResult CWindowProc::WindowProc(MofWindowHandle hWnd, MofUInt msg, MofProcParamW wpar, MofProcParamL lpar) {
	switch (msg)
	{
		case WM_CREATE:
		{
			// ���j���[��ݒ�
			SetMenu(hWnd, LoadMenu(NULL, MAKEINTRESOURCE(IDR_MENU1)));
			int w = 1024 + GetSystemMetrics(SM_CXFIXEDFRAME) * 2;
			int h = 768 + GetSystemMetrics(SM_CYFIXEDFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYMENU);
			SetWindowPos(hWnd, NULL, 0, 0, w, h, SWP_NOZORDER | SWP_NOMOVE);
			break;
		}
		case WM_COMMAND:
		{
			// ���j���[�I��
			switch (LOWORD(wpar))
			{
			case ID_LOADMAP1:						//�}�b�v�ǂݍ���
				LoadMapData(0);
				break;
			case ID_LOADMAP2:						//�}�b�v�ǂݍ���
				LoadMapData(1);
				break;
			case ID_LOADMAP3:						//�}�b�v�ǂݍ���
				LoadMapData(2);
				break;
			case ID_LOADMAP4:
				LoadMapData(3);
				break;
			case ID_LOADMAP5:
				LoadMapData(4);
				break;
			case ID_LOADMAP6:
				LoadMapData(5);
				break;
			case ID_LOADMAP7:
				LoadMapData(6);
				break;
			case ID_LOADMAP8:
				LoadMapData(7);
				break;
			case ID_LOADMAP9:
				LoadMapData(8);
				break;
			case ID_LOADMAP10:
				LoadMapData(9);
				break;
			case ID_SAVEMAP1:						//�}�b�v�ۑ�
				SaveMapData(0);
				break;
			case ID_SAVEMAP2:						//�}�b�v�ۑ�
				SaveMapData(1);
				break;
			case ID_SAVEMAP3:						//�}�b�v�ۑ�
				SaveMapData(2);
				break;
			case ID_SAVEMAP4:
				SaveMapData(3);
				break;
			case ID_SAVEMAP5:
				SaveMapData(4);
				break;
			case ID_SAVEMAP6:
				SaveMapData(5);
				break;
			case ID_SAVEMAP7:
				SaveMapData(6);
				break;
			case ID_SAVEMAP8:
				SaveMapData(7);
				break;
			case ID_SAVEMAP9:
				SaveMapData(8);
				break;
			case ID_SAVEMAP10:
				SaveMapData(9);
				break;

			case ID_OVERWRITE:
				SaveMapData(10);
				break;

				case ID_LOADBACK:					// �w�i�摜�ǂݍ���
					LoadBackTexture(hWnd);
					break;

				case ID_LOADCHIP:					// �`�b�v�摜�ǂݍ���
					LoadChipTexture(hWnd);
					break;

				case ID_LOADENEMY:					// �G�摜�ǂݍ���
					LoadEnemyTexture(hWnd);
					break;

				case ID_LOADITEM:					// �A�C�e���摜�ǂݍ���
					LoadItemTexture(hWnd);
					break;

				case ID_MAPSTATE:						//�}�b�v�ݒ�
					DialogBox(CUtilities::GetInstanceHandle(), MAKEINTRESOURCE(IDD_MAPSTATE), hWnd, (DLGPROC)MapStateDlgProc);
					break;

				case ID_APPEND:						// �I��
					PostQuitMessage(0);
					break;

				case ID_VERSION:					// �o�[�W����
					ShellAbout(hWnd, "�}�b�v�G�f�B�^", "OIC", NULL);
					break;
			}
			break;
		}
		// �f�t�H���g����
		default:
			return CDefWindowProc::WindowProc(hWnd, msg, wpar, lpar);
	}
	return DefWindowProc(hWnd, msg, wpar, lpar);
}