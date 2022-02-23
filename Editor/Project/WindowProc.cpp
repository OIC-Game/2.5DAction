#include "WindowProc.h"
#include "resource.h"
#include "GameApp.h"

// コンストラクタ
CWindowProc::CWindowProc() :
	CDefWindowProc() {
}

// デストラクタ
CWindowProc::~CWindowProc() {
}

// ウインドウプロシージャ
MofProcResult CWindowProc::WindowProc(MofWindowHandle hWnd, MofUInt msg, MofProcParamW wpar, MofProcParamL lpar) {
	switch (msg)
	{
		case WM_CREATE:
		{
			// メニューを設定
			SetMenu(hWnd, LoadMenu(NULL, MAKEINTRESOURCE(IDR_MENU1)));
			int w = 1024 + GetSystemMetrics(SM_CXFIXEDFRAME) * 2;
			int h = 768 + GetSystemMetrics(SM_CYFIXEDFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYMENU);
			SetWindowPos(hWnd, NULL, 0, 0, w, h, SWP_NOZORDER | SWP_NOMOVE);
			break;
		}
		case WM_COMMAND:
		{
			// メニュー選択
			switch (LOWORD(wpar))
			{
			case ID_LOADMAP1:						//マップ読み込み
				LoadMapData(0);
				break;
			case ID_LOADMAP2:						//マップ読み込み
				LoadMapData(1);
				break;
			case ID_LOADMAP3:						//マップ読み込み
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
			case ID_SAVEMAP1:						//マップ保存
				SaveMapData(0);
				break;
			case ID_SAVEMAP2:						//マップ保存
				SaveMapData(1);
				break;
			case ID_SAVEMAP3:						//マップ保存
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

				case ID_LOADBACK:					// 背景画像読み込み
					LoadBackTexture(hWnd);
					break;

				case ID_LOADCHIP:					// チップ画像読み込み
					LoadChipTexture(hWnd);
					break;

				case ID_LOADENEMY:					// 敵画像読み込み
					LoadEnemyTexture(hWnd);
					break;

				case ID_LOADITEM:					// アイテム画像読み込み
					LoadItemTexture(hWnd);
					break;

				case ID_MAPSTATE:						//マップ設定
					DialogBox(CUtilities::GetInstanceHandle(), MAKEINTRESOURCE(IDD_MAPSTATE), hWnd, (DLGPROC)MapStateDlgProc);
					break;

				case ID_APPEND:						// 終了
					PostQuitMessage(0);
					break;

				case ID_VERSION:					// バージョン
					ShellAbout(hWnd, "マップエディタ", "OIC", NULL);
					break;
			}
			break;
		}
		// デフォルト処理
		default:
			return CDefWindowProc::WindowProc(hWnd, msg, wpar, lpar);
	}
	return DefWindowProc(hWnd, msg, wpar, lpar);
}