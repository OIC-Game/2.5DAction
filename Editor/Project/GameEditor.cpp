#include "GameEditor.h"


CGameEditor::CGameEditor()
{
	memset(m_MapchipTypeArray,-1,sizeof(m_MapchipTypeArray));
	memset(m_EnemyTypeArray, -1, sizeof(m_EnemyTypeArray));
}

CGameEditor::~CGameEditor()
{
}

bool CGameEditor::OpenFileDialog(HWND hWnd, int mode, const char* Title, const char* Filter, const char* DefExt, char* path) {
	// ファイルダイアログ用構造体
	OPENFILENAME ofn;
	memset(&ofn, 0, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = path;
	ofn.lpstrFilter = Filter;
	ofn.lpstrDefExt = DefExt;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = Title;
	memset(path, 0, MAX_PATH);

	if (mode == 0)
	{
		ofn.Flags = OFN_FILEMUSTEXIST;
		if (!GetOpenFileName(&ofn))
		{
			return false;
		}
	}
	else
	{
		ofn.Flags = OFN_OVERWRITEPROMPT;
		if (!GetSaveFileName(&ofn))
		{
			return false;
		}
	}
	return true;
}

bool CGameEditor::Load() {
	m_PlayerTexture.Load("chara_main_idle.png");
	return true;
}

bool CGameEditor::LoadBackTexture(HWND hWnd) {
	// ファイル選択ダイアログを表示
	char path[MAX_PATH];
	char Filter[] = "画像ファイル\0*.bmp;*.png;*.dds\0 全てのファイル(*.*)\0*.*\0\0";
	char DefExt[] = "bmp\0dds\0png";
	if (!OpenFileDialog(hWnd, 0, "背景画像を開く", Filter, DefExt, path))
	{
		return false;
	}
	// 前の画像を解放
	m_BackTexture.Release();
	// 選んだファイルを開く
	if (!m_BackTexture.Load(path))
	{
		return false;
	}
	return true;
}

bool CGameEditor::LoadChipTexture(HWND hWnd) {
	// ファイル選択ダイアログを表示
	char path[MAX_PATH];
	char Filter[] = "画像ファイル\0*.bmp;*.png;*.dds\0 全てのファイル(*.*)\0*.*\0\0";
	char DefExt[] = "bmp\0dds\0png";
	if (!OpenFileDialog(hWnd, 0, "チップ画像を開く", Filter, DefExt, path))
	{
		return false;
	}
	// 前の画像を解放
	m_ChipTexture.Release();
	// 選んだファイルを開く
	if (!m_ChipTexture.Load(path))
	{
		return false;
	}
	// チップエリアに収めるためのスケールを求める
	float xs = (float)m_ChipAreaWidth / m_ChipTexture.GetWidth();
	float ys = (float)(m_ChipAreaHeight - m_ChipAreaOffset) / m_ChipTexture.GetHeight();
	m_ChipScale = min(xs, ys);
	return true;
}

bool CGameEditor::LoadEnemyTexture(HWND hWnd) {
	// ファイル選択ダイアログを表示
	char path[MAX_PATH];
	char Filter[] = "画像ファイル\0*.bmp;*.png;*.dds\0 全てのファイル(*.*)\0*.*\0\0";
	char DefExt[] = "bmp\0dds\0png";
	if (!OpenFileDialog(hWnd, 0, "チップ画像を開く", Filter, DefExt, path))
	{
		return false;
	}
	// 一時読み込みテクスチャ
	CTexture* tmp = new CTexture();
	// 選んだファイルを開く
	if (!tmp->Load(path))
	{
		return false;
	}
	// テクスチャを配列に追加する
	m_EnemyTextureArray.Add(&tmp);
	return true;
}

bool CGameEditor::LoadItemTexture(HWND hWnd) {
	// ファイル選択ダイアログを表示
	char path[MAX_PATH];
	char Filter[] = "画像ファイル\0*.bmp;*.png;*.dds\0 全てのファイル(*.*)\0*.*\0\0";
	char DefExt[] = "bmp\0dds\0png";
	if (!OpenFileDialog(hWnd, 0, "チップ画像を開く", Filter, DefExt, path))
	{
		return false;
	}
	// 一時読み込みテクスチャ
	CTexture* tmp = new CTexture();
	// 選んだファイルを開く
	if (!tmp->Load(path))
	{
		return false;
	}
	// テクスチャを配列に追加する
	m_ItemTextureArray.Add(&tmp);
	return true;
}

LRESULT CALLBACK CGameEditor::MapStateDlgProc(HWND hWnd, UINT msg, WPARAM wpar, LPARAM lpar) {
	switch (msg)
	{
	case WM_INITDIALOG:
		SetDlgItemInt(hWnd, IDC_XCOUNT, m_XChipCount, FALSE);
		SetDlgItemInt(hWnd, IDC_YCOUNT, m_YChipCount, FALSE);
		SetDlgItemInt(hWnd, IDC_XCHIPSIZE, m_XChipSize, FALSE);
		SetDlgItemInt(hWnd, IDC_YCHIPSIZE, m_YChipSize, FALSE);
		SetDlgItemInt(hWnd, IDC_XEDITORSIZE, m_XChipEditorSize, FALSE);
		SetDlgItemInt(hWnd, IDC_YEDITORSIZE, m_YChipEditorSize, FALSE);
		CheckDlgButton(hWnd, IDC_RHOMBUS, m_bRhombus);

		break;
	case WM_COMMAND:
		switch (LOWORD(wpar))
		{
		case IDOK:
		{
			//ダイアログの設定数値を取得
			BOOL re;
			int xcnt, ycnt, xcsize, ycsize, xesize, yesize;
			bool rhombus;
			xcnt = GetDlgItemInt(hWnd, IDC_XCOUNT, &re, FALSE);
			if (!re || xcnt <= 0)
			{
				MessageBox(hWnd, "1以上の数値を入力してください", "Error", MB_OK);
				break;
			}
			ycnt = GetDlgItemInt(hWnd, IDC_YCOUNT, &re, FALSE);
			if (!re || ycnt <= 0)
			{
				MessageBox(hWnd, "1以上の数値を入力してください", "Error", MB_OK);
				break;
			}
			xcsize = GetDlgItemInt(hWnd, IDC_XCHIPSIZE, &re, FALSE);
			if (!re || xcsize <= 0)
			{
				MessageBox(hWnd, "1以上の数値を入力してください", "Error", MB_OK);
				break;
			}
			ycsize = GetDlgItemInt(hWnd, IDC_YCHIPSIZE, &re, FALSE);
			if (!re || ycsize <= 0)
			{
				MessageBox(hWnd, "1以上の数値を入力してください", "Error", MB_OK);
				break;
			}
			xesize = GetDlgItemInt(hWnd, IDC_XEDITORSIZE, &re, FALSE);
			if (!re || xesize <= 0)
			{
				MessageBox(hWnd, "1以上の数値を入力してください", "Error", MB_OK);
				break;
			}
			yesize = GetDlgItemInt(hWnd, IDC_YEDITORSIZE, &re, FALSE);
			if (!re || yesize <= 0)
			{
				MessageBox(hWnd, "1以上の数値を入力してください", "Error", MB_OK);
				break;
			}
			rhombus = IsDlgButtonChecked(hWnd, IDC_RHOMBUS);


			//マップデータのメモリを再確保する
			int* pMapTemp = (int*)calloc(xcnt * ycnt * m_LayerCount, sizeof(int));
			int* pEnemyTemp = (int*)calloc(xcnt * ycnt * m_LayerCount, sizeof(int));
			int* pItemTemp = (int*)calloc(xcnt * ycnt * m_LayerCount, sizeof(int));
			int* pGimmickTemp = (int*)calloc(xcnt * ycnt * m_LayerCount, sizeof(int));
			//古いデータをコピーする
			for (int l = 0; l < m_LayerCount; l++)
			{
				for (int y = 0; y < ycnt; y++)
				{
					for (int x = 0; x < xcnt; x++)
					{
						if (x < m_XChipCount && y < m_YChipCount && l < m_LayerCount)
						{
							int from_i = l * m_YChipCount * m_XChipCount + y * m_XChipCount + x;
							int to_i = l * ycnt * xcnt + y * xcnt + x;
							pMapTemp[to_i] = m_pChipData[from_i];
							pEnemyTemp[to_i] = m_pEnemyData[from_i];
							pItemTemp[to_i] = m_pItemData[from_i];
							pGimmickTemp[to_i] = m_pGimmickData[from_i];
						}
						else
						{
							int to_i = l * ycnt * xcnt + y * xcnt + x;
							pMapTemp[to_i] = 0;
							pEnemyTemp[to_i] = 0;
							pItemTemp[to_i] = 0;
							pGimmickTemp[to_i] = -1;
						}
					}
				}
			}
			if (m_PlayerPosX > xcnt || m_PlayerPosY > ycnt)
			{
				m_PlayerPosX = -1;
				m_PlayerPosY = -1;
			}
			//古いデータの解放
			free(m_pChipData);
			free(m_pEnemyData);
			free(m_pItemData);
			free(m_pGimmickData);
			//新しいデータに設定
			m_XChipCount = xcnt;
			m_YChipCount = ycnt;
			m_XChipSize = xcsize;
			m_YChipSize = ycsize;
			m_XChipEditorSize = xesize;
			m_YChipEditorSize = yesize;
			m_bRhombus = rhombus;
			m_pChipData = pMapTemp;
			m_pEnemyData = pEnemyTemp;
			m_pItemData = pItemTemp;
			m_pGimmickData = pGimmickTemp;

			EndDialog(hWnd, 0);
			break;
		}
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
	return TRUE;
}

char* Getpath(int i) {
	switch (i)
	{
	case 0:
		return ("Stage1.txt");
		break;
	case 1:
		return ("Stage2.txt");
		break;
	case 2:
		return ("Stage3.txt");
		break;
	case 3:
		return ("Stage4.txt");
		break;
	case 4:
		return ("Stage5.txt");
		break;
	case 5:
		return ("Stage6.txt");
		break;
	case 6:
		return ("Stage7.txt");
		break;
	case 7:
		return ("Stage8.txt");
		break;
	case 8:
		return ("Stage9.txt");
		break;
	case 9:
		return ("Stage10.txt");
		break;
	default:
		break;
	}
}

bool CGameEditor::LoadMapData(int path) {
	//テキストファイルを開く
	FILE* fp = fopen(Getpath(path), "rt");
	if (fp == NULL)
	{
		return false;
	}
	//ファイルの全容量を調べる
	fseek(fp, 0, SEEK_END);
	long fSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	//ファイルサイズ分だけのメモリを確保する
	char* pBuffer = (char*)malloc(fSize + 1);
	//ファイルを全てバッファに読み込む
	fSize = fread(pBuffer, 1, fSize, fp);
	pBuffer[fSize] = '\0';
	char* pstr;

	//古いデータを破棄
	ReleaseMapData();

	//テクスチャの読み込み
	pstr = strtok(pBuffer, ",");
	m_BackTexture.Load(pstr);
	pstr = strtok(NULL, ",");
	m_ChipTexture.Load(pstr);

	//プレイヤー初期位置
	pstr = strtok(NULL, ",");
	m_PlayerPosX = atoi(pstr);
	pstr = strtok(NULL, ",");
	m_PlayerPosY = atoi(pstr);
	pstr = strtok(NULL, ",");
	m_PlayerSize = atoi(pstr);	
	//チップサイズ
	pstr = strtok(NULL, ",");
	m_XChipSize = atoi(pstr);
	pstr = strtok(NULL, ",");
	m_YChipSize = atoi(pstr);
	pstr = strtok(NULL, ",");
	m_XChipEditorSize = atoi(pstr);
	pstr = strtok(NULL, ",");
	m_YChipEditorSize = atoi(pstr);
	pstr = strtok(NULL, ",");
	m_bRhombus = atoi(pstr);
	float xs = (float)m_ChipAreaWidth / m_ChipTexture.GetWidth();
	float ys = (float)(m_ChipAreaHeight - m_ChipAreaOffset) / m_ChipTexture.GetHeight();
	m_ChipScale = min(xs, ys);

	//マップチップ数
	pstr = strtok(NULL, ",");
	m_XChipCount = atoi(pstr);
	pstr = strtok(NULL, ",");
	m_YChipCount = atoi(pstr);
	pstr = strtok(NULL, ",");
	m_LayerCount = atoi(pstr);

	//マップのチップ数総数 (列数*行数)
	int totalChips = m_XChipCount * m_YChipCount * m_LayerCount;

	//マップチップメモリ確保
	m_pChipData = (int*)malloc(sizeof(int) * totalChips);
	//敵配置メモリ確保
	m_pEnemyData = (int*)malloc(sizeof(int) * totalChips);
	//アイテム配置メモリ確保
	m_pItemData = (int*)malloc(sizeof(int) * totalChips);

	m_pGimmickData = (int*)malloc(sizeof(int) * totalChips);

	//チップデータの読み込み
	for (int l = 0; l < m_LayerCount; l++)
	{
		for (int y = 0; y < m_YChipCount; y++)
		{
			for (int x = 0; x < m_XChipCount; x++)
			{
				pstr = strtok(NULL, ",");
				m_pChipData[l * m_XChipCount * m_YChipCount + y * m_XChipCount + x] = atoi(pstr);
			}
		}
	}

	//敵のテクスチャ読み込み
	pstr = strtok(NULL, ",");
	int ecnt = atoi(pstr);
	for (int i = 0; i < ecnt; i++)
	{
		pstr = strtok(NULL, ",");
		//一時読み込みテクスチャ
		CTexture* tmp = new CTexture();
		//選んだファイルを開く
		if (!tmp->Load(pstr))
		{
			return false;
		}
		//テクスチャを配列に追加する
		m_EnemyTextureArray.Add(&tmp);
	}

	//配置データの読み込み
	for (int l = 0; l < m_LayerCount; l++)
	{
		for (int y = 0; y < m_YChipCount; y++)
		{
			for (int x = 0; x < m_XChipCount; x++)
			{
				pstr = strtok(NULL, ",");
				m_pEnemyData[l * m_XChipCount * m_YChipCount + y * m_XChipCount + x] = atoi(pstr);
			}
		}
	}

	//アイテムのテクスチャ読み込み
	pstr = strtok(NULL, ",");
	int icnt = atoi(pstr);
	for (int i = 0; i < icnt; i++)
	{
		pstr = strtok(NULL, ",");
		//一時読み込みテクスチャ
		CTexture* tmp = new CTexture();
		//選んだファイルを開く
		if (!tmp->Load(pstr))
		{
			return false;
		}
		//テクスチャを配列に追加する
		m_ItemTextureArray.Add(&tmp);
	}

	//配置データの読み込み
	for (int l = 0; l < m_LayerCount; l++)
	{
		for (int y = 0; y < m_YChipCount; y++)
		{
			for (int x = 0; x < m_XChipCount; x++)
			{
				pstr = strtok(NULL, ",");
				m_pItemData[l * m_XChipCount * m_YChipCount + y * m_XChipCount + x] = atoi(pstr);
			}
		}
	}

	for (int l = 0; l < m_LayerCount; l++)
	{
		for (int y = 0; y < m_YChipCount; y++)
		{
			for (int x = 0; x < m_XChipCount; x++)
			{
				pstr = strtok(NULL, ",");
				m_pGimmickData[l * m_XChipCount * m_YChipCount + y * m_XChipCount + x] = atoi(pstr) - 1;
			}
		}
	}

	//ファイルを閉じる
	fclose(fp);
	free(pBuffer);
	return true;
}

bool CGameEditor::SaveMapData(int path) {
	if (path == 10)
	{
		path = m_StageNo;
	}
	//テキストファイルを開く
	FILE* fp = fopen(Getpath(path), "wt");
	if (fp == NULL)
	{
		return false;
	}

	char fname[MAX_PATH];
	//テクスチャ名を出力テキストからの相対パスにして出力
	if (!m_BackTexture.GetName()->GetString())
	{
		fprintf(fp, " ,");
	}
	else
	{
		if (PathRelativePathTo(fname, Getpath(path), FILE_ATTRIBUTE_NORMAL, m_BackTexture.GetName()->GetString(), FILE_ATTRIBUTE_NORMAL))
		{
			fprintf(fp, "%s,", fname);
		}
		else
		{
			fprintf(fp, "%s,", m_BackTexture.GetName()->GetString());
		}
	}
	if (!m_ChipTexture.GetName()->GetString())
	{
		fprintf(fp, " ,\n");
	}
	else
	{
		if (PathRelativePathTo(fname, Getpath(path), FILE_ATTRIBUTE_NORMAL, m_ChipTexture.GetName()->GetString(), FILE_ATTRIBUTE_NORMAL))
		{
			fprintf(fp, "%s,\n", fname);
		}
		else
		{
			fprintf(fp, "%s,\n", m_ChipTexture.GetName()->GetString());
		}
	}
	//プレイヤー初期位置
	int px = m_PlayerPosX;
	int py = m_PlayerPosY;
	if (px < 0 || py < 0)
	{
		px = 0;
		py = 0;
	}
	fprintf(fp, "%d,%d,%d,\n", px, py,m_PlayerSize);
	//チップサイズ
	fprintf(fp, "%d,%d,\n", m_XChipSize, m_YChipSize);
	//チップサイズ
	fprintf(fp, "%d,%d,\n", m_XChipEditorSize, m_YChipEditorSize);

	fprintf(fp, "%d,\n", m_bRhombus);

	//マップのチップ数
	fprintf(fp, "%d,%d,%d,\n", m_XChipCount, m_YChipCount, m_LayerCount);

	//チップデータの出力
	for (int l = 0; l < m_LayerCount; l++)
	{
		for (int y = 0; y < m_YChipCount; y++)
		{
			for (int x = 0; x < m_XChipCount; x++)
			{
				int no = m_pChipData[l * m_XChipCount * m_YChipCount + y * m_XChipCount + x];
				if (no <= 0)
					no = 0;
				fprintf(fp, "%2d,", no);
			}
			fprintf(fp, "\n");
		}
	}

	fprintf(fp, "\n");

	//敵のテクスチャ出力
	fprintf(fp, "%d,", m_EnemyTextureArray.GetArrayCount());
	for (int i = 0; i < m_EnemyTextureArray.GetArrayCount(); i++)
	{
		if (PathRelativePathTo(fname, Getpath(path), FILE_ATTRIBUTE_NORMAL, m_EnemyTextureArray[i]->GetName()->GetString(), FILE_ATTRIBUTE_NORMAL))
		{
			fprintf(fp, "%s,", fname);
		}
		else
		{
			fprintf(fp, "%s,", m_EnemyTextureArray[i]->GetName()->GetString());
		}
	}
	fprintf(fp, "\n");

	//配置データの出力
	for (int l = 0; l < m_LayerCount; l++)
	{
		for (int y = 0; y < m_YChipCount; y++)
		{
			for (int x = 0; x < m_XChipCount; x++)
			{
				int no = m_pEnemyData[l * m_XChipCount * m_YChipCount + y * m_XChipCount + x];
				if (no <= 0)
					no = 0;
				fprintf(fp, "%2d,", no);
			}
			fprintf(fp, "\n");
		}
	}
	fprintf(fp, "\n");

	//アイテムのテクスチャ出力
	fprintf(fp, "%d,", m_ItemTextureArray.GetArrayCount());
	for (int i = 0; i < m_ItemTextureArray.GetArrayCount(); i++)
	{
		if (PathRelativePathTo(fname, Getpath(path), FILE_ATTRIBUTE_NORMAL, m_ItemTextureArray[i]->GetName()->GetString(), FILE_ATTRIBUTE_NORMAL))
		{
			fprintf(fp, "%s,", fname);
		}
		else
		{
			fprintf(fp, "%s,", m_ItemTextureArray[i]->GetName()->GetString());
		}
	}
	fprintf(fp, "\n");

	//配置データの出力
	for (int l = 0; l < m_LayerCount; l++)
	{
		for (int y = 0; y < m_YChipCount; y++)
		{
			for (int x = 0; x < m_XChipCount; x++)
			{
				int no = m_pItemData[l * m_XChipCount * m_YChipCount + y * m_XChipCount + x];
				if (no <= 0)
					no = 0;
				fprintf(fp, "%2d,", no);
			}
			fprintf(fp, "\n");
		}
	}
	fprintf(fp, "\n");
	for (int l = 0; l < m_LayerCount; l++)
	{
		for (int y = 0; y < m_YChipCount; y++)
		{
			for (int x = 0; x < m_XChipCount; x++)
			{
				int no = m_pGimmickData[l * m_XChipCount * m_YChipCount + y * m_XChipCount + x] + 1;
				if (no <= 0)
					no = 0;
				if (no > m_LayerCount * m_YChipCount * m_XChipCount)
					no = 0;
				fprintf(fp, "%2d,", no);
			}
			fprintf(fp, "\n");
		}
	}
	//ファイルを閉じる
	fclose(fp);
	return true;
}

void CGameEditor::Initialize() {
	m_bEnd = false;
	// マップのチップ数総数 (列数*行数)
	int totalChips = m_LayerCount * m_XChipCount * m_YChipCount;
	// マップチップメモリ確保
	m_pChipData = (int*)calloc(totalChips, sizeof(int));
	// 敵配置メモリ確保
	m_pEnemyData = (int*)calloc(totalChips, sizeof(int));
	// アイテム配置メモリ確保
	m_pItemData = (int*)calloc(totalChips, sizeof(int));

	m_pGimmickData = (int*)calloc(totalChips, sizeof(int));

	m_GimickSelectNo = -1;

	for (int i = 0; i < totalChips; i++)
	{
		m_pChipData[i] = 0;
		m_pEnemyData[i] = 0;
		m_pItemData[i] = 0;
		m_pGimmickData[i] = 0;
	}

	LoadMapData(m_StageNo);

	float chipsize = m_XChipSize;
	if (m_XChipSize < m_YChipSize)
	{
		chipsize = m_YChipSize;
	}
	float chipsizewidth = m_ChipTexture.GetWidth();
	float chipsizeheight = m_ChipTexture.GetHeight();
	int widthcount = chipsizewidth / chipsize;
	int heightcount = chipsizeheight / chipsize;
	if (heightcount * widthcount >= CHIPAREA_COUNT * 4 - 2)
	{
		for (int i = 0; i < CHIPAREA_COUNT * 4 - 2; i++)
		{
			m_MapchipTypeArray[i] = i;
		}
	}
	else
	{
		for (int i = 0; i < heightcount * widthcount; i++)
		{
			m_MapchipTypeArray[i] = i;
		}
	}
}

void CGameEditor::Update() {
	if (g_pInput->IsKeyPush(MOFKEY_AT) && g_pInput->IsKeyHold(MOFKEY_LCONTROL))
	{
		m_bGrid = !m_bGrid;
	}
	if (g_pInput->IsKeyPush(MOFKEY_F3))
	{
		m_bGimmickMode = !m_bGimmickMode;
		m_XSelect = -1;
		m_YSelect = -1;
	}
	if (g_pInput->IsKeyPush(MOFKEY_F4))
	{
		m_bAllView = !m_bAllView;
	}
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		m_bEnd = true;
		m_NextScene = SCENENO_TITLE;
	}
	// マウス座標の取得
	float mx, my;
	g_pInput->GetMousePos(mx, my);
	if (m_TabViewSelect >= 0)
	{
		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
		{
			// タブエリア
			UpdateTabArea(mx, my);
		}
		if (g_pInput->IsMouseKeyPull(MOFMOUSE_LBUTTON))
		{
			if (m_bTabSelectEnd == true)
			{
				m_TabViewSelect = -1;
				m_EraseSelect = -1;
				m_ChipSelect = 0;
				m_bTabSelectEnd = false;
			}
		}
	}
	// チップ選択エリア
	if (mx < m_ChipAreaWidth)
	{
		// マウス左クリックで選択
		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
		{
			// レイヤーエリア
			UpdateLayerArea(mx, my);
			UpdatePlayerPosArea(mx,my);
		}
		if (g_pInput->IsMouseKeyHold(MOFMOUSE_LBUTTON))
		{
			// チップエリア
			UpdateChipArea(mx, my);
			// 敵エリア
			UpdateEnemyArea(mx, my);
		}
	}
	// マップチップ配置エリア
	else
	{
		if (m_TabViewSelect < 0)
		{
			// マップ表示情報の更新
			UpdateMapScroll();
			// マウス左クリックで配置
			if (g_pInput->IsMouseKeyHold(MOFMOUSE_LBUTTON))
			{
				if (!m_bGimmickMode)
				{
					UpdateChipAdd(mx, my);
					if (m_EraseSelect >= 0)
					{
						UpdateChipRemove(mx, my);
					}
				}
			}
			if (g_pInput->IsMouseKeyHold(MOFMOUSE_RBUTTON))
			{
				if (!m_bGimmickMode)
				{
					UpdateChipCopy(mx, my);
				}
			}
			if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
			{
				if (m_bGimmickMode)
				{
					SelectGimmick(mx, my);
				}
			}
			if (g_pInput->IsMouseKeyPush(MOFMOUSE_RBUTTON))
			{
				if (m_bGimmickMode)
				{
					DeleteGimmick();
				}
			}
		}
	}
}

void CGameEditor::UpdateMapScroll() {
	// 上下左右キーでマップ表示を移動
	if (g_pInput->IsKeyPush(MOFKEY_LEFT))
	{
		if (m_XScroll > 0)
		{
			m_XScroll--;
		}
	}
	else if (g_pInput->IsKeyHold(MOFKEY_LEFT))
	{
		if (m_XScrollWait == 0)
		{
			if (m_XScroll > 0)
			{
				m_XScroll--;
				m_XScrollWait = 2;
			}
		}
		else
		{
			m_XScrollWait--;
			if (m_XScrollWait < 0)
				m_XScrollWait = 0;
		}
	}
	else if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
	{
		if (m_XScroll < m_XChipCount)
		{
			m_XScroll++;
		}
	}
	else if (g_pInput->IsKeyHold(MOFKEY_RIGHT))
	{
		if (m_XScrollWait <= 0)
		{
			if (m_XScroll < m_XChipCount)
			{
				m_XScroll++;
				m_XScrollWait = 2;
			}
		}
		else
		{
			m_XScrollWait--;
			if (m_XScrollWait < 0)
				m_XScrollWait = 0;
		}
	}
	else
	{
		m_XScrollWait = 30;
	}

	if (g_pInput->IsKeyPush(MOFKEY_UP))
	{
		if (m_YScroll > 0)
		{
			m_YScroll--;
		}
	}
	else if (g_pInput->IsKeyHold(MOFKEY_UP))
	{
		if (m_YScrollWait <= 0)
		{
			if (m_YScroll > 0)
			{
				m_YScroll--;
				m_YScrollWait = 2;
			}
		}
		else
		{
			m_YScrollWait--;
			if (m_YScrollWait < 0)
				m_YScrollWait = 0;
		}
	}
	else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
	{
		if (m_YScroll < m_YChipCount)
		{
			if (m_bRhombus)
				m_YScroll += 2;
			else
				m_YScroll += 1;
		}
	}
	else if (g_pInput->IsKeyHold(MOFKEY_DOWN))
	{
		if (m_YScrollWait <= 0)
		{
			if (m_YScroll < m_YChipCount)
			{
				if (m_bRhombus)
					m_YScroll += 2;
				else
					m_YScroll += 1;
				m_YScrollWait = 2;
			}
		}
		else
		{
			m_YScrollWait--;
			if (m_YScrollWait < 0)
				m_YScrollWait = 0;
		}
	}
	else
	{
		m_YScrollWait = 30;
	}
	if (m_bRhombus)
	{
		if (m_YScroll % 2 != 0)
		{
			m_YScroll--;
		}
	}

	// マウスホイール入力でマップを拡大/縮小
	float w = g_pInput->GetMouseWheelMove();
	float maxscale = 256;
	float minscale = 32;
	maxscale /= max(m_XChipEditorSize, m_YChipEditorSize);
	minscale /= max(m_XChipEditorSize, m_YChipEditorSize);
	if (w >= 1.0f)
	{
		m_MapScale += (maxscale - minscale) / 20;
		if (m_MapScale > maxscale)
		{
			m_MapScale = maxscale;
		}
	}
	else if (w <= -1.0f)
	{
		m_MapScale -= (maxscale - minscale) / 20;
		if (m_MapScale < minscale)
		{
			m_MapScale = minscale;
		}
	}
}

void CGameEditor::SelectArea(float mx, float my){
	if (m_bRhombus)
	{
		for (int y = 0; y < m_YChipCount; y++)
		{
			float shiftx = 0.5;
			if (y % 2 == 0)
			{
				shiftx = 1;
			}
			for (int x = 0; x < m_XChipCount; x++)
			{
				float p0x = (x + shiftx) * m_XChipEditorSize * m_MapScale + m_ChipAreaWidth;
				float p0y = y * m_YChipEditorSize * m_MapScale / 2;
				float p1x = (x + shiftx + 0.5) * m_XChipEditorSize * m_MapScale + m_ChipAreaWidth;
				float p1y = p0y + m_YChipEditorSize * m_MapScale / 2;
				float p2x = (x + shiftx) * m_XChipEditorSize * m_MapScale + m_ChipAreaWidth;
				float p2y = p0y + m_YChipEditorSize * m_MapScale;
				double Area = 0.5 *(-p1y * p2x + p0y * (-p1x + p2x) + p0x * (p1y - p2y) + p1x * p2y);
				double s = 1 / (2 * Area)*(p0y*p2x - p0x * p2y + (p2y - p0y)*mx + (p0x - p2x)*my);
				double t = 1 / (2 * Area)*(p0x*p1y - p0y * p1x + (p0y - p1y)*mx + (p1x - p0x)*my);

				if (0 < s  && s < 1 && 0 < t && t < 1) {
					if (0 < 1 - s - t && 1 - s - t < 1)
					{
						m_YSelect = y + m_YScroll;
						m_XSelect = x + m_XScroll;
					}
				}

				p1x = (x + shiftx - 0.5) * m_XChipEditorSize * m_MapScale + m_ChipAreaWidth;
				Area = 0.5 *(-p1y * p2x + p0y * (-p1x + p2x) + p0x * (p1y - p2y) + p1x * p2y);
				s = 1 / (2 * Area)*(p0y*p2x - p0x * p2y + (p2y - p0y)*mx + (p0x - p2x)*my);
				t = 1 / (2 * Area)*(p0x*p1y - p0y * p1x + (p0y - p1y)*mx + (p1x - p0x)*my);

				if (0 < s  && s < 1 && 0 < t && t < 1) {
					if (0 < 1 - s - t && 1 - s - t < 1)
					{
						m_YSelect = y + m_YScroll;
						m_XSelect = x + m_XScroll;
					}
				}
			}
		}
	}
	else
	{
		m_XSelect = (int)(m_XScroll + (mx - m_ChipAreaWidth) / (m_XChipEditorSize * m_MapScale));
		m_YSelect = (int)(m_YScroll + my / (m_YChipEditorSize * m_MapScale));
	}
}

void CGameEditor::UpdateLayerCount(int sign) {
	int layer = m_LayerCount;
	layer += sign;
	if (layer < 1)
	{
		layer = 1;
	}
	//マップデータのメモリを再確保する
	int* pMapTemp = (int*)calloc(m_XChipCount * m_YChipCount * layer, sizeof(int));
	int* pEnemyTemp = (int*)calloc(m_XChipCount * m_YChipCount * layer, sizeof(int));
	int* pItemTemp = (int*)calloc(m_XChipCount * m_YChipCount * layer, sizeof(int));
	int* pGimmickTemp = (int*)calloc(m_XChipCount * m_YChipCount * layer, sizeof(int));
	//古いデータをコピーする
	for (int l = 0; l < layer; l++)
	{
		for (int y = 0; y < m_YChipCount; y++)
		{
			for (int x = 0; x < m_XChipCount; x++)
			{
				if (x < m_XChipCount && y < m_YChipCount && l < m_LayerCount)
				{
					int from_i = l * m_YChipCount * m_XChipCount + y * m_XChipCount + x;
					int to_i = l * m_YChipCount * m_XChipCount + y * m_XChipCount + x;
					pMapTemp[to_i] = m_pChipData[from_i];
					pEnemyTemp[to_i] = m_pEnemyData[from_i];
					pItemTemp[to_i] = m_pItemData[from_i];
					pGimmickTemp[to_i] = m_pGimmickData[from_i];
				}
				else
				{
					int to_i = l * m_YChipCount * m_XChipCount + y * m_XChipCount + x;
					pMapTemp[to_i] = 0;
					pEnemyTemp[to_i] = 0;
					pItemTemp[to_i] = 0;
					pGimmickTemp[to_i] = -1;
				}
			}
		}
	}
	//古いデータの解放
	free(m_pChipData);
	free(m_pEnemyData);
	free(m_pItemData);
	free(m_pGimmickData);
	//新しいデータに設定
	m_LayerCount = layer;
	m_pChipData = pMapTemp;
	m_pEnemyData = pEnemyTemp;
	m_pItemData = pItemTemp;
	m_pGimmickData = pGimmickTemp;
	if (m_Layer >= m_LayerCount)
		m_Layer = m_LayerCount - 1;
}

void CGameEditor::UpdateChipAdd(float mx, float my) {
	SelectArea(mx, my);
	if (m_XSelect < 0 || m_XSelect >= m_XChipCount || m_YSelect < 0 || m_YSelect >= m_YChipCount) { return; }
	if (m_ChipSelect >= 0)
	{
		m_pChipData[m_Layer * m_XChipCount * m_YChipCount + m_YSelect * m_XChipCount + m_XSelect] = m_MapchipTypeArray[m_ChipSelect] + 1;
		int no = -1;
		int selectno = m_MapchipTypeArray[m_ChipSelect];
		if (m_MapchipTypeArray[m_ChipSelect] == m_MapchipTypeArray[0] || m_MapchipTypeArray[m_ChipSelect] == 0)
		{
			return;
		}
		for (int i = 0; i < CHIPAREA_COUNT * 4 - 2; i++)
		{
			if (m_MapchipTypeArray[m_ChipSelect] == m_MapchipTypeArray[i])
			{
				no = i;
			}
		}
		// 入れ替え
		if (no == -1)
		{
			for (int i = CHIPAREA_COUNT * 4 - 4; i >= 0; i--)
			{
				m_MapchipTypeArray[i + 1] = m_MapchipTypeArray[i];
			}
		}
		else
		{
			for (int i = no - 1; i >= 0; i--)
			{
				m_MapchipTypeArray[i + 1] = m_MapchipTypeArray[i];
			}
		}
		m_MapchipTypeArray[0] = selectno;
		m_ChipSelect = 0;
	}
	else if (m_EnemySelect >= 0)
	{
		m_pEnemyData[m_Layer * m_XChipCount * m_YChipCount + m_YSelect * m_XChipCount + m_XSelect] = m_EnemySelect + 1;
	}
	else if (m_ItemSelect >= 0)
	{
		m_pItemData[m_Layer * m_XChipCount * m_YChipCount + m_YSelect * m_XChipCount + m_XSelect] = m_ItemSelect + 1;
	}
	else if (m_PlayerSelect >= 0)
	{
		m_PlayerPosX = m_XSelect;
		m_PlayerPosY = m_YSelect;
	}
}

void CGameEditor::UpdateLayerArea(float mx, float my) {
	if (my < m_LayerAreaOffset || my >= m_LayerAreaHeight) { return; }
	float midHeight = (m_LayerAreaHeight + m_LayerAreaOffset) / 2;
	CRectangle rec[4] = {
		{(float)m_Squares, (float)m_LayerAreaOffset,(float)m_Squares * 2, midHeight},
		{(float)m_Squares, midHeight,(float)m_Squares * 2, (float)m_LayerAreaHeight},
		{(float)m_Squares * 3, (float)m_LayerAreaOffset,(float)m_Squares * 4, midHeight},
		{(float)m_Squares * 3, midHeight,(float)m_Squares * 4, (float)m_LayerAreaHeight}
	};
	for (int i = 0; i < 4; i++)
	{
		if (rec[i].CollisionPoint(mx,my))
		{
			switch (i)
			{
			case 0:
				UpdateLayerCount(1);
				break;
			case 1:
				UpdateLayerCount(-1);
				break;
			case 2:
				m_Layer++;
				if (m_Layer >= m_LayerCount)
				{
					m_Layer = m_LayerCount - 1;
				}
				break;
			case 3:
				m_Layer--;
				if (m_Layer < 0)
				{
					m_Layer = 0;
				}
				break;
			default:
				break;
			}
		}
	}
}

void CGameEditor::UpdateChipArea(float mx, float my) {
	if (my < m_ChipAreaOffset || my >= m_ChipAreaHeight) { return; }
	if (mx > m_ChipAreaWidth) { return; }
	int cnt = m_ChipAreaWidth / m_Squares;
	int selx = (int)(mx / m_Squares);
	int sely = (int)((my - m_ChipAreaOffset) / m_Squares);
	m_ChipSelect = -1;
	m_EnemySelect = -1;
	m_ItemSelect = -1;
	m_PlayerSelect = -1;
	m_EraseSelect = -1;
	m_TabViewSelect = -1;
	switch (sely * cnt + selx)
	{
	case CHIPAREA_COUNT * 4 - 2:
		m_EraseSelect = 0;
		break;
	case CHIPAREA_COUNT * 4 - 1:
		m_TabViewSelect = 0;
		break;
	default:
		m_ChipSelect = sely * cnt + selx;
		break;
	}
}

void CGameEditor::UpdateEnemyArea(float mx, float my) {
	if (my < m_EnemyAreaOffset || my >= m_EnemyAreaHeight) { return; }
	int cnt = m_ChipAreaWidth / m_Squares;
	int selx = (int)(mx / m_Squares);
	int sely = (int)((my - m_EnemyAreaOffset) / m_Squares);
	m_ChipSelect = -1;
	m_EnemySelect = -1;
	m_ItemSelect = -1;
	m_PlayerSelect = -1;
	m_EraseSelect = -1;
	m_TabViewSelect = -1;
	switch (sely * cnt + selx)
	{
	case 4:
		m_EraseSelect = 1;
		break;
	case 5:
		break;
	case 6:
		m_ItemSelect = 0;
		break;
	case 7:
		m_EraseSelect = 2;
		break;
	default:
		m_EnemySelect = sely * cnt + selx;
		break;
	}
}

void CGameEditor::UpdateTabArea(float mx, float my) {
	if (my < m_ChipAreaOffset || my >= m_ChipAreaHeight) { return; }
	float chipsize = m_XChipSize;
	if (m_XChipSize < m_YChipSize)
	{
		chipsize = m_YChipSize;
	}
	float chipsizewidth = m_ChipTexture.GetWidth();
	float chipsizeheight = m_ChipTexture.GetHeight();
	int widthcount = chipsizewidth / chipsize;
	int heightcount = chipsizeheight / chipsize;
	float chipcount = widthcount * heightcount;
	int cnt = ceil(chipcount / CHIPAREA_COUNT);

	if (mx < m_ChipAreaWidth || mx >= m_ChipAreaWidth + cnt * m_Squares) { return; }

	int selx = (int)((mx - m_ChipAreaWidth) / m_Squares);
	int sely = (int)((my - m_ChipAreaOffset) / m_Squares);


	if (sely * cnt + selx >= 0)
	{
		m_ChipSelect = -1;
		m_EnemySelect = -1;
		m_ItemSelect = -1;
		m_EraseSelect = -1;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		int no = -1;
		int selectno = sely * cnt + selx;
		if (selectno == m_MapchipTypeArray[0])
		{
			return;
		}
		for (int i = 0; i < CHIPAREA_COUNT * 4 - 2; i++)
		{
			if (selectno == m_MapchipTypeArray[i])
			{
				no = i;
			}
		}
		// 入れ替え
		if (no == -1)
		{
			for (int i = CHIPAREA_COUNT * 4 - 4; i >= 0; i--)
			{
				m_MapchipTypeArray[i + 1] = m_MapchipTypeArray[i];
			}
		}
		else
		{
			for (int i = no - 1; i >= 0; i--)
			{
				m_MapchipTypeArray[i + 1] = m_MapchipTypeArray[i];
			}
		}
		m_MapchipTypeArray[0] = selectno;
		m_bTabSelectEnd = true;
	}
}

void CGameEditor::UpdateChipRemove(float mx, float my) {
	SelectArea(mx, my);
	if (m_XSelect < 0 || m_XSelect >= m_XChipCount || m_YSelect < 0 || m_YSelect >= m_YChipCount) { return; }

	switch (m_EraseSelect)
	{
	case 0:
	{
		int cn = m_pChipData[m_Layer * m_XChipCount * m_YChipCount + m_YSelect * m_XChipCount + m_XSelect] - 1;
		if (cn == 20 || cn == 22 || cn == 54 || cn == 55)
		{
			int no = m_pGimmickData[m_Layer * m_XChipCount * m_YChipCount + m_YSelect * m_XChipCount + m_XSelect];
			m_pGimmickData[m_Layer * m_XChipCount * m_YChipCount + m_YSelect * m_XChipCount + m_XSelect] = -1;
			if (no >= 0)
			m_pGimmickData[no] = -1;
		}
		m_pChipData[m_Layer * m_XChipCount * m_YChipCount + m_YSelect * m_XChipCount + m_XSelect] = 0;
		break;
	}
	case 1:
		m_pEnemyData[m_Layer * m_XChipCount * m_YChipCount + m_YSelect * m_XChipCount + m_XSelect] = 0;
		break;
	default:
		m_pItemData[m_Layer * m_XChipCount * m_YChipCount + m_YSelect * m_XChipCount + m_XSelect] = 0;
		break;
	}
}

void CGameEditor::UpdateChipCopy(float mx, float my) {
	SelectArea(mx, my);
	if (m_XSelect < 0 || m_XSelect >= m_XChipCount || m_YSelect < 0 || m_YSelect >= m_YChipCount) { return; }
	int no = -1;
	int selectno = m_MapchipTypeArray[m_ChipSelect];
	if (m_pChipData[m_Layer * m_XChipCount * m_YChipCount + m_YSelect * m_XChipCount + m_XSelect] - 1 == m_MapchipTypeArray[0] || m_pChipData[m_Layer * m_XChipCount * m_YChipCount + m_YSelect * m_XChipCount + m_XSelect] == 0)
	{
		return;
	}
	for (int i = 0; i < CHIPAREA_COUNT * 4 - 2; i++)
	{
		if (m_MapchipTypeArray[i] == m_pChipData[m_Layer * m_XChipCount * m_YChipCount + m_YSelect * m_XChipCount + m_XSelect] - 1)
		{
			no = i;
		}
	}
	// 入れ替え
	if (no == -1)
	{
		for (int i = CHIPAREA_COUNT * 4 - 4; i >= 0; i--)
		{
			m_MapchipTypeArray[i + 1] = m_MapchipTypeArray[i];
		}
	}
	else
	{
		for (int i = no - 1; i >= 0; i--)
		{
			m_MapchipTypeArray[i + 1] = m_MapchipTypeArray[i];
		}
	}
	m_MapchipTypeArray[0] = m_pChipData[m_Layer * m_XChipCount * m_YChipCount + m_YSelect * m_XChipCount + m_XSelect] - 1;
	m_ChipSelect = 0;
	m_EnemySelect = -1;
	m_ItemSelect = -1;
	m_PlayerSelect = -1;
	m_EraseSelect = -1;
	m_TabViewSelect = -1;
}

void CGameEditor::UpdatePlayerPosArea(float mx, float my) {
	if (my < m_PlayerAreaOffset || my >= m_PlayerAreaHeight) { return; }
	int cnt = m_ChipAreaWidth / m_Squares;
	int selx = (int)(mx / m_Squares);
	int sely = (int)((my - m_PlayerAreaOffset) / m_Squares);
	m_ChipSelect = -1;
	m_EnemySelect = -1;
	m_ItemSelect = -1;
	m_PlayerSelect = -1;
	m_EraseSelect = -1;
	m_TabViewSelect = -1;
	switch (sely * cnt + selx)
	{
	case 0:
		m_PlayerSelect = 0;
		break;
	case 2:
		m_PlayerDirection++;
		if (m_PlayerDirection > 3)
			m_PlayerDirection -= 4;
		break;
	case 3:
		m_PlayerPosX = -1;
		m_PlayerPosY = -1;
	default:
		break;
	}
}

void CGameEditor::SelectGimmick(float mx, float my) {
	SelectArea(mx, my);
	if (m_XSelect < 0 || m_XSelect >= m_XChipCount || m_YSelect < 0 || m_YSelect >= m_YChipCount) {
		return;
	}
	int cn = m_pChipData[m_Layer * m_XChipCount * m_YChipCount + m_YSelect * m_XChipCount + m_XSelect] - 1;
	if ((cn == 20 || cn == 22 || cn == 54 || cn == 55) == false) { return; }
	if (m_GimickSelectNo < 0)
		m_GimickSelectNo = m_Layer * m_XChipCount * m_YChipCount + m_YSelect * m_XChipCount + m_XSelect;
	else if (m_GimickSelectNo == m_Layer * m_XChipCount * m_YChipCount + m_YSelect * m_XChipCount + m_XSelect)
	{
		m_GimickSelectNo = -1;
	}
	else if (m_pGimmickData[m_pGimmickData[m_GimickSelectNo]] != m_GimickSelectNo && m_pGimmickData[m_Layer * m_XChipCount * m_YChipCount + m_YSelect * m_XChipCount + m_XSelect] == -1)
	{
		int gn = m_pChipData[m_GimickSelectNo] - 1;
		if (gn == 20 || gn == 22)
		{
			if (cn == 54 || cn == 55)
			{
				m_pGimmickData[m_Layer * m_XChipCount * m_YChipCount + m_YSelect * m_XChipCount + m_XSelect] = m_GimickSelectNo;
				m_pGimmickData[m_GimickSelectNo] = m_Layer * m_XChipCount * m_YChipCount + m_YSelect * m_XChipCount + m_XSelect;
			}
		}
		else if (gn == 54 || gn == 55)
		{
			if (cn == 20 || cn == 22)
			{
				m_pGimmickData[m_Layer * m_XChipCount * m_YChipCount + m_YSelect * m_XChipCount + m_XSelect] = m_GimickSelectNo;
				m_pGimmickData[m_GimickSelectNo] = m_Layer * m_XChipCount * m_YChipCount + m_YSelect * m_XChipCount + m_XSelect;
			}
		}
	}
}

void CGameEditor::DeleteGimmick() {
	if (m_GimickSelectNo >= 0)
	{
		if (m_pGimmickData[m_pGimmickData[m_GimickSelectNo]] == m_GimickSelectNo)
		{
			int no = m_pGimmickData[m_GimickSelectNo];
			m_pGimmickData[m_GimickSelectNo] = -1;
			m_pGimmickData[no] = -1;
		}
	}
}

void CGameEditor::Render() {
	// 背景画像描画
	int scw = g_pGraphics->GetTargetWidth();
	int sch = g_pGraphics->GetTargetHeight();
	int wn = m_BackTexture.GetWidth() * m_MapScale;
	int hn = m_BackTexture.GetHeight() * m_MapScale;

	if (wn > 0 && hn > 0)
	{
		float scale = m_XChipEditorSize * m_BackScale * m_MapScale;
		for (float y = ((int)-(m_YScroll * scale) % hn) - hn; y < sch; y += hn)
		{
			for (float x = m_ChipAreaWidth + ((int)-(m_XScroll * scale) % wn) - wn; x < scw; x += wn)
			{
				m_BackTexture.RenderScale(x, y, m_MapScale);
			}
		}
		CGraphicsUtilities::RenderFillRect(0, 0, m_ChipAreaWidth, sch, MOF_XRGB(102, 102, 102));
	}
	// チップ画像描画
	RenderMapChip();

	// 敵画像描画
	CRectangle Erec(0, 0, m_EnemyChipSize, m_EnemyChipSize);
	float EChipSize = m_XChipSize;

	float ex = 0.0f;
	float ey = 0.0f;
	for (DWORD i = 0; i < m_EnemyTextureArray.GetArrayCount(); i++)
	{
		//m_EnemyTextureArray[i]->Render(ex, m_EnemyAreaOffset + ey, 0.2f);
		m_EnemyTextureArray[i]->RenderScale(ex, m_EnemyAreaOffset + ey, 0.2f, Erec);
		ex += m_EnemySize;
		if (ex + m_EnemySize >= m_ChipAreaWidth + 5)
		{
			ex = 0.0f;
			ey += m_EnemySize;
		}
	}

	// アイテム画像描画
	CRectangle Irec(64, 64, 64 + m_ItemSize, 64 + m_ItemSize);
	float ix = 0.0f;
	float iy = 0.0f;
	float scaleItem = m_Squares;
	scaleItem /= m_ItemSize;
	for (DWORD i = 0; i < m_ItemTextureArray.GetArrayCount(); i++)
	{
		m_ItemTextureArray[i]->RenderScale(2 * m_Squares, m_EnemyAreaOffset + m_Squares, scaleItem, Irec);
		ix += m_ItemSize;
		if (ix + m_ItemSize >= m_ChipAreaWidth)
		{
			ix = 0.0f;
			iy += m_ItemSize;
		}
	}

	// プレイヤー画像描画
	CRectangle Prec(0, 0, 256, 256);
	float scale = m_Squares;
	scale /= 256;
	m_PlayerTexture.RenderScale(0,m_PlayerAreaOffset, scale,Prec);


	// 配置チップ描画
	int tcx = m_ChipTexture.GetWidth() / m_XChipSize;
	int tcnt = (m_ChipTexture.GetWidth() / m_YChipEditorSize) * (m_ChipTexture.GetHeight() / m_YChipEditorSize);

	int color = 255;
	int alpha = 255;
	int floorAlpha = m_LayerCount - m_Layer;
	if (!m_bAllView)
	{
		color /= m_Layer + 3;
		alpha /= floorAlpha;
	}
	for (int l = 0; l < m_LayerCount; l++)
	{
		int c = color;
		int a = alpha;



		if (!m_bAllView)
		{
			if (l < m_Layer)
			{
				c *= l + 2;
			}
			else
			{
				c = 255;
			}

			if (l > m_Layer)
			{
				a *= m_LayerCount - l;
			}
			else
			{
				a = 255;
			}
		}
		
		for (int y = m_YScroll; y < m_YChipCount; y++)
		{
			for (int x = m_XScroll; x < m_XChipCount; x++)
			{
				// 描画するチップ番号
				// チップ番号0は描画しない
				int cn = m_pChipData[l * m_XChipCount * m_YChipCount + y * m_XChipCount + x] - 1;
				if (cn < 0 || cn >= tcnt)
				{
					continue;
				}				
				
				if (m_bGimmickMode)
				{
					if ((cn == 20 || cn == 22 || cn == 54 || cn == 55) == false)
						c /= 2;
				}

				// マップチップの矩形
				CRectangle cr(m_XChipSize * (cn % tcx), m_YChipSize * (cn / tcx), m_XChipSize * (cn % tcx + 1), m_YChipSize * (cn / tcx + 1));
				// マップチップの描画
				if (m_bRhombus)
				{
					if (y % 2 == 0)
					{
						m_ChipTexture.RenderScale(m_ChipAreaWidth + (x - m_XScroll + 0.5) * m_XChipEditorSize * m_MapScale, (y - m_YScroll) * m_YChipEditorSize * m_MapScale / 2 - (m_YChipSize - m_YChipEditorSize) * m_MapScale, m_MapScale, cr,MOF_ARGB(a,c,c,c));
					}
					else
					{
						m_ChipTexture.RenderScale(m_ChipAreaWidth + (x - m_XScroll) * m_XChipEditorSize * m_MapScale, (y - m_YScroll) * m_YChipEditorSize * m_MapScale / 2 - (m_YChipSize - m_YChipEditorSize) * m_MapScale, m_MapScale, cr, MOF_ARGB(a,c, c, c));
					}
				}
				else
				{
					m_ChipTexture.RenderScale(m_ChipAreaWidth + (x - m_XScroll) * m_XChipEditorSize * m_MapScale, (y - m_YScroll) * m_YChipEditorSize * m_MapScale - (m_YChipSize - m_YChipEditorSize) * m_MapScale, m_MapScale, cr, MOF_ARGB(a,c, c, c));
				}
			}
		}

		// 配置敵描画
		for (int y = m_YScroll; y < m_YChipCount; y++)
		{
			for (int x = m_XScroll; x < m_XChipCount; x++)
			{
				// 配置敵番号
				int cn = m_pEnemyData[l * m_XChipCount * m_YChipCount + y * m_XChipCount + x] - 1;
				if (cn < 0 || cn >= m_EnemyTextureArray.GetArrayCount())
				{
					continue;
				}

				if (m_bGimmickMode)
				{
					c /= 2;
				}
				// 配置敵の描画
				if (m_bRhombus)
				{
					if (y % 2 == 0)
					{
						m_EnemyTextureArray[cn]->RenderScale(m_ChipAreaWidth + (x - m_XScroll + 0.5) * m_XChipEditorSize * m_MapScale, (y - m_YScroll) * m_YChipEditorSize * m_MapScale / 2 - (m_YChipSize - m_YChipEditorSize) * m_MapScale, m_MapScale, Erec, MOF_ARGB(a, c, c, c));
					}
					else
					{
						m_EnemyTextureArray[cn]->RenderScale(m_ChipAreaWidth + (x - m_XScroll) * m_XChipEditorSize * m_MapScale, (y - m_YScroll) * m_YChipEditorSize * m_MapScale / 2 - (m_YChipSize - m_YChipEditorSize) * m_MapScale, m_MapScale, Erec, MOF_ARGB(a, c, c, c));
					}
				}
				else
				{
					m_EnemyTextureArray[cn]->RenderScale(m_ChipAreaWidth + (x - m_XScroll) * m_XChipEditorSize * m_MapScale, (y - m_YScroll) * m_YChipEditorSize * m_MapScale - (m_YChipSize - m_YChipEditorSize) * m_MapScale, m_MapScale, Erec, MOF_ARGB(a, c, c, c));
				}
			}
		}

		// 配置アイテム描画
		for (int y = m_YScroll; y < m_YChipCount; y++)
		{
			for (int x = m_XScroll; x < m_XChipCount; x++)
			{
				// 配置アイテム番号
				int cn = m_pItemData[l * m_XChipCount * m_YChipCount + y * m_XChipCount + x] - 1;
				if (cn < 0 || cn >= m_ItemTextureArray.GetArrayCount())
				{
					continue;
				}

				if (m_bGimmickMode)
				{
					c /= 2;
				}
				// 配置アイテムの描画
				if (m_bRhombus)
				{
					if (y % 2 == 0)
					{
						m_ItemTextureArray[cn]->RenderScale(m_ChipAreaWidth + (x - m_XScroll + 0.5) * m_XChipEditorSize * m_MapScale, (y - m_YScroll) * m_YChipEditorSize * m_MapScale / 2 - (m_YChipSize - m_YChipEditorSize) * m_MapScale, m_MapScale, Erec, MOF_ARGB(a, c, c, c));
					}
					else
					{
						m_ItemTextureArray[cn]->RenderScale(m_ChipAreaWidth + (x - m_XScroll) * m_XChipEditorSize * m_MapScale, (y - m_YScroll) * m_YChipEditorSize * m_MapScale / 2 - (m_YChipSize - m_YChipEditorSize) * m_MapScale, m_MapScale, Erec, MOF_ARGB(a, c, c, c));
					}
				}
				else
				{
					m_ItemTextureArray[cn]->RenderScale(m_ChipAreaWidth + (x - m_XScroll) * m_XChipEditorSize * m_MapScale, (y - m_YScroll) * m_YChipEditorSize * m_MapScale, m_MapScale, Erec, MOF_ARGB(a, c, c, c));
				}
			}
		}
	}
	if (m_PlayerPosX >= 0 && m_PlayerPosY >= 0)
	{
		CRectangle prec;
		switch (m_PlayerDirection)
		{
		case 0:
			prec = CRectangle(0, 0, m_PlayerSize, m_PlayerSize);
			break;
		case 1:
			prec = CRectangle(0, m_PlayerSize * 7, m_PlayerSize, m_PlayerSize * 8);
			break;
		case 2:
			prec = CRectangle(m_PlayerSize, m_PlayerSize * 14, 0, m_PlayerSize * 15);
			break;
		default:
			prec = CRectangle(0, m_PlayerSize * 14, m_PlayerSize, m_PlayerSize * 15);			
			break;
		}
		if (m_PlayerPosX >= m_XScroll && m_PlayerPosY >= m_YScroll)
		{
			if (m_bRhombus)
			{
				if (m_PlayerPosY % 2 == 0)
					m_PlayerTexture.RenderScale(m_ChipAreaWidth + (m_PlayerPosX + 0.5f - m_XScroll) * m_XChipEditorSize * m_MapScale, (m_PlayerPosY - m_YScroll) * m_YChipEditorSize / 2 * m_MapScale - (m_PlayerSize - m_YChipEditorSize) * m_MapScale, m_MapScale, prec);
				else
					m_PlayerTexture.RenderScale(m_ChipAreaWidth + (m_PlayerPosX - m_XScroll) * m_XChipEditorSize * m_MapScale, (m_PlayerPosY - m_YScroll) * m_YChipEditorSize / 2 * m_MapScale - (m_PlayerSize - m_YChipEditorSize) * m_MapScale, m_MapScale, prec);
			}
			else
				m_PlayerTexture.RenderScale(m_ChipAreaWidth + (m_PlayerPosX - m_XScroll) * m_XChipEditorSize * m_MapScale, (m_PlayerPosY - m_YScroll) * m_YChipEditorSize * m_MapScale - (m_PlayerSize - m_YChipEditorSize) * m_MapScale, m_MapScale, prec);

		}
	}
	RenderFrame();
	RenderTabView();
}

void CGameEditor::RenderDebug(void) {

}

void CGameEditor::RenderFrame() {
	//チップ画像描画エリアとマップ描画エリアの分割線
	CGraphicsUtilities::RenderLine(m_ChipAreaWidth, 0, m_ChipAreaWidth, g_pGraphics->GetTargetHeight(), MOF_COLOR_WHITE);
	//チップ描画エリアに枠の表示

	CGraphicsUtilities::RenderString(0, 0, "レイヤー");
	CGraphicsUtilities::RenderString(0, m_LayerAreaOffset / 2, "最大数");
	CGraphicsUtilities::RenderString(m_ChipAreaWidth / 2, m_LayerAreaOffset / 2, "編集中");


	float LayerHeight = m_LayerAreaHeight + m_LayerAreaOffset;

	CGraphicsUtilities::RenderString(25, LayerHeight / 2 - 10, "%d",m_LayerCount);
	CGraphicsUtilities::RenderString(25 + m_ChipAreaWidth / 2, LayerHeight / 2 - 10, "%d", m_Layer + 1);

	for (int y = m_LayerAreaOffset;y <= m_LayerAreaHeight;y += m_Squares)
	{
		for (int x = 0;x <= m_ChipAreaWidth;x += m_Squares)
		{
			CGraphicsUtilities::RenderLine(x, m_LayerAreaOffset, x, m_LayerAreaHeight, MOF_COLOR_WHITE);
			if ((x / m_Squares) % 2 == 1)
			{
				float midHeight = (m_LayerAreaHeight + m_LayerAreaOffset) / 2;
				CGraphicsUtilities::RenderLine(x, midHeight, x + m_Squares, midHeight, MOF_COLOR_WHITE);

				CGraphicsUtilities::RenderString(x + 20, m_LayerAreaOffset + 5, "↑");

				CGraphicsUtilities::RenderString(x + 20, m_LayerAreaOffset + 35, "↓");
			}
		}
		CGraphicsUtilities::RenderLine(0, y, m_ChipAreaWidth, y, MOF_COLOR_WHITE);
	}

	CGraphicsUtilities::RenderString(0, m_LayerAreaHeight, "マップチップ");
	for (float y = m_ChipAreaOffset;y <= m_ChipAreaHeight;y += m_Squares)
	{
		for (float x = 0;x <= m_ChipAreaWidth;x += m_Squares)
		{
			CGraphicsUtilities::RenderLine(x, m_ChipAreaOffset, x, m_ChipAreaHeight, MOF_COLOR_WHITE);
		}
		CGraphicsUtilities::RenderLine(0, y, m_ChipAreaWidth, y, MOF_COLOR_WHITE);
	}
	CGraphicsUtilities::RenderString(m_Squares * 2 + 18, m_LayerAreaHeight + m_Squares * 5 - 10, "消");
	CGraphicsUtilities::RenderString(m_Squares * 3 + 18, m_LayerAreaHeight + m_Squares * 5 - 10, "全");

	//敵エリアに枠の表示
	CGraphicsUtilities::RenderString(0, m_ChipAreaHeight, "敵");
	for (float y = m_EnemyAreaOffset;y <= m_EnemyAreaHeight;y += m_EnemySize)
	{
		for (float x = 0;x <= m_ChipAreaWidth;x += m_EnemySize)
		{
			CGraphicsUtilities::RenderLine(x, m_EnemyAreaOffset, x, m_EnemyAreaHeight, MOF_COLOR_WHITE);
		}
		CGraphicsUtilities::RenderLine(0, y, m_ChipAreaWidth, y, MOF_COLOR_WHITE);
	}
	CGraphicsUtilities::RenderString(18, m_EnemyAreaOffset + m_Squares + 20, "消");

	CGraphicsUtilities::RenderString(m_Squares + 18, m_EnemyAreaOffset + m_Squares + 20, "ガ");
	CGraphicsUtilities::RenderString(m_Squares * 3 + 18, m_EnemyAreaOffset + m_Squares + 20, "消");


	// プレイヤーエリアに枠の表示
	CGraphicsUtilities::RenderString(0, m_EnemyAreaHeight, "プレイヤー");
	for (float y = m_PlayerAreaOffset;y <= m_PlayerAreaHeight;y += m_EnemySize)
	{
		for (float x = 0;x <= m_ChipAreaWidth;x += m_EnemySize)
		{
			CGraphicsUtilities::RenderLine(x, m_PlayerAreaOffset, x, m_PlayerAreaHeight, MOF_COLOR_WHITE);
		}
		CGraphicsUtilities::RenderLine(0, y, m_ChipAreaWidth, y, MOF_COLOR_WHITE);
	}

	CGraphicsUtilities::RenderString(m_Squares * 2 + 18, m_PlayerAreaHeight - m_Squares + 20, "向");
	CGraphicsUtilities::RenderString(m_Squares * 3 + 18, m_PlayerAreaHeight - m_Squares + 20, "消");


	if (m_bGrid)
	{
		//マップ描画エリアに枠の表示
		if (m_bRhombus)
		{
			if (m_XChipEditorSize >= m_YChipEditorSize)
			{
				int cnt = g_pGraphics->GetTargetHeight() / (m_YChipEditorSize * m_MapScale);
				for (int i = 0;i * m_YChipEditorSize * m_MapScale <= g_pGraphics->GetTargetHeight();i++)
				{
					float x = i * m_XChipEditorSize * m_MapScale + m_ChipAreaWidth;
					float y = i * m_YChipEditorSize * m_MapScale;
					float ratio = m_YChipEditorSize;
					ratio /= m_XChipEditorSize;
					CGraphicsUtilities::RenderLine(x, 0, x + g_pGraphics->GetTargetHeight() / ratio, g_pGraphics->GetTargetHeight(), MOF_COLOR_WHITE);
					CGraphicsUtilities::RenderLine(m_ChipAreaWidth, y, m_ChipAreaWidth + (g_pGraphics->GetTargetHeight() - y) / ratio, g_pGraphics->GetTargetHeight(), MOF_COLOR_WHITE);
				}
				for (int i = 0;i * m_YChipEditorSize * m_MapScale <= g_pGraphics->GetTargetHeight() * 2;i++)
				{
					float x = i * m_XChipEditorSize * m_MapScale + m_ChipAreaWidth;
					float y = i * m_YChipEditorSize * m_MapScale;
					float ratio = m_YChipEditorSize;
					ratio /= m_XChipEditorSize;
					CGraphicsUtilities::RenderLine(x, 0, m_ChipAreaWidth, (x - m_ChipAreaWidth) * ratio, MOF_COLOR_WHITE);
				}
			}
			else
			{
				for (int i = 0;i * m_XChipEditorSize * m_MapScale <= g_pGraphics->GetTargetWidth();i++)
				{
					float x = i * m_XChipEditorSize * m_MapScale + m_ChipAreaWidth;
					float y = i * m_YChipEditorSize * m_MapScale;
					float ratio = m_YChipEditorSize;
					ratio /= m_XChipEditorSize;
					CGraphicsUtilities::RenderLine(x, 0, x + g_pGraphics->GetTargetHeight(), g_pGraphics->GetTargetHeight() * ratio, MOF_COLOR_WHITE);
					CGraphicsUtilities::RenderLine(m_ChipAreaWidth, y, g_pGraphics->GetTargetWidth(), (g_pGraphics->GetTargetHeight() + i * m_XChipEditorSize * m_MapScale) * ratio, MOF_COLOR_WHITE);
				}
				for (int i = 0;i * m_XChipEditorSize * m_MapScale <= g_pGraphics->GetTargetWidth() * 2;i++)
				{
					float x = i * m_XChipEditorSize * m_MapScale + m_ChipAreaWidth;
					float y = i * m_YChipEditorSize * m_MapScale;
					float ratio = m_YChipEditorSize;
					ratio /= m_XChipEditorSize;
					CGraphicsUtilities::RenderLine(x, 0, m_ChipAreaWidth, (x - m_ChipAreaWidth) * ratio, MOF_COLOR_WHITE);
				}
			}
		}
		else
		{
			for (float x = m_ChipAreaWidth;x <= g_pGraphics->GetTargetWidth();x += m_XChipEditorSize * m_MapScale)
			{
				CGraphicsUtilities::RenderLine(x, 0, x, g_pGraphics->GetTargetHeight(), MOF_COLOR_WHITE);
			}
			for (float y = 0;y <= g_pGraphics->GetTargetHeight();y += m_YChipEditorSize * m_MapScale)
			{
				CGraphicsUtilities::RenderLine(m_ChipAreaWidth, y, g_pGraphics->GetTargetWidth(), y, MOF_COLOR_WHITE);
			}
		}
	}
	//チップ選択位置表示
	if (m_ChipSelect >= 0)
	{
		int cnt = m_ChipAreaWidth / m_Squares;
		int xoff = m_ChipSelect % cnt;
		int yoff = m_ChipSelect / cnt;
		float xsel = xoff * m_Squares;
		float ysel = m_ChipAreaOffset + yoff * m_Squares;
		CGraphicsUtilities::RenderRect(xsel, ysel, xsel + m_Squares, ysel + m_Squares, MOF_COLOR_RED);
	}
	if (m_EnemySelect >= 0)
	{
		int cnt = m_ChipAreaWidth / m_Squares;
		int xoff = m_EnemySelect % cnt;
		int yoff = m_EnemySelect / cnt;
		float xsel = xoff * m_Squares;
		float ysel = m_EnemyAreaOffset + yoff * m_Squares;
		CGraphicsUtilities::RenderRect(xsel, ysel, xsel + m_Squares, ysel + m_Squares, MOF_COLOR_RED);
	}
	if (m_ItemSelect == 0)
	{
		CGraphicsUtilities::RenderRect(m_Squares * 2, m_EnemyAreaOffset + m_Squares, m_Squares * 3, m_EnemyAreaOffset + m_Squares * 2, MOF_COLOR_RED);
	}
	if (m_EraseSelect >= 0)
	{
		switch (m_EraseSelect)
		{
		case 0:
			CGraphicsUtilities::RenderRect(m_Squares * 2, m_ChipAreaOffset + m_Squares * (CHIPAREA_COUNT - 1), m_Squares * 3, m_ChipAreaOffset + m_Squares * CHIPAREA_COUNT, MOF_COLOR_BLUE);
			break;
		case 1:
			CGraphicsUtilities::RenderRect(0, m_EnemyAreaOffset + m_Squares, m_Squares, m_EnemyAreaOffset + m_Squares * 2, MOF_COLOR_BLUE);
			break;
		default:
			CGraphicsUtilities::RenderRect(m_Squares * 3, m_EnemyAreaOffset + m_Squares, m_Squares * 4, m_EnemyAreaOffset + m_Squares * 2, MOF_COLOR_BLUE);
			break;
		}
	}
	if (m_PlayerSelect >= 0)
	{
		CGraphicsUtilities::RenderRect(0,m_PlayerAreaOffset,m_Squares,m_PlayerAreaHeight,MOF_COLOR_RED);
	}
	if (m_TabViewSelect == 0)
	{
		CGraphicsUtilities::RenderRect(m_Squares * 3, m_ChipAreaOffset + m_Squares * (CHIPAREA_COUNT - 1), m_Squares * 4, m_ChipAreaOffset + m_Squares * CHIPAREA_COUNT, MOF_COLOR_GREEN);
	}

	//マップ選択位置表示
	if (m_XSelect >= m_XScroll && m_YSelect >= m_YScroll)
	{
		float xsel = 0;
		float ysel = 0;
		if (m_bRhombus)
		{
			if (m_YSelect % 2 == 0)
			{
				xsel = m_ChipAreaWidth + (m_XSelect - m_XScroll + 0.5) * (m_XChipEditorSize * m_MapScale);
			}
			else
			{
				xsel = m_ChipAreaWidth + (m_XSelect - m_XScroll) * (m_XChipEditorSize * m_MapScale);
			}
			ysel = (m_YSelect - m_YScroll) * (m_YChipEditorSize * m_MapScale) / 2;
		}
		else
		{
			xsel = m_ChipAreaWidth + (m_XSelect - m_XScroll) * (m_XChipEditorSize * m_MapScale);
			ysel = (m_YSelect - m_YScroll) * (m_YChipEditorSize * m_MapScale);
		}
		if (m_bRhombus)
		{
			for (int i = 0; i < 2; i++)
			{
				CGraphicsUtilities::RenderLine(xsel + (m_XChipEditorSize * m_MapScale) / 2, ysel + i, xsel + (m_XChipEditorSize * m_MapScale) - i, ysel + (m_YChipEditorSize * m_MapScale) / 2, MOF_COLOR_RED);
				CGraphicsUtilities::RenderLine(xsel + (m_XChipEditorSize * m_MapScale) - i, ysel + (m_YChipEditorSize * m_MapScale) / 2, xsel + (m_XChipEditorSize * m_MapScale) / 2, ysel + (m_YChipEditorSize * m_MapScale) - i, MOF_COLOR_RED);
				CGraphicsUtilities::RenderLine(xsel + (m_XChipEditorSize * m_MapScale) / 2, ysel + (m_YChipEditorSize * m_MapScale) - i, xsel + i, ysel + (m_YChipEditorSize * m_MapScale) / 2, MOF_COLOR_RED);
				CGraphicsUtilities::RenderLine(xsel + i, ysel + (m_YChipEditorSize * m_MapScale) / 2, xsel + (m_XChipEditorSize * m_MapScale) / 2, ysel + i, MOF_COLOR_RED);
			}
		}
		else
		{
			CGraphicsUtilities::RenderRect(xsel, ysel, xsel + (m_XChipEditorSize * m_MapScale), ysel + (m_YChipEditorSize * m_MapScale), MOF_COLOR_RED);
			
		}
	}
	RenderGimmickFrame();
	// エリア端の描画
	for (int i = 0; i < 3; i++)
	{
		if (m_bRhombus)
		{
			CGraphicsUtilities::RenderLine(m_ChipAreaWidth, i + (m_YChipCount + 1 - m_YScroll) * m_YChipEditorSize * m_MapScale / 2, i + m_ChipAreaWidth + (m_XChipCount + 0.5 - m_XScroll) * m_XChipEditorSize * m_MapScale, i + (m_YChipCount + 1 - m_YScroll) * m_YChipEditorSize * m_MapScale / 2, MOF_XRGB(255, 0, 0));
			CGraphicsUtilities::RenderLine(i + m_ChipAreaWidth + (m_XChipCount - m_XScroll + 0.5) * m_XChipEditorSize * m_MapScale, 0, i + m_ChipAreaWidth + (m_XChipCount + 0.5 - m_XScroll) * m_XChipEditorSize * m_MapScale, i + (m_YChipCount + 1 - m_YScroll) * m_YChipEditorSize * m_MapScale / 2, MOF_XRGB(255, 0, 0));
		}
		else
		{
			CGraphicsUtilities::RenderLine(m_ChipAreaWidth, i + (m_YChipCount - m_YScroll) * m_YChipEditorSize * m_MapScale, i + m_ChipAreaWidth + (m_XChipCount - m_XScroll) * m_XChipEditorSize * m_MapScale, i + (m_YChipCount - m_YScroll) * m_YChipEditorSize * m_MapScale, MOF_XRGB(255, 0, 0));
			CGraphicsUtilities::RenderLine(i + m_ChipAreaWidth + (m_XChipCount - m_XScroll) * m_XChipEditorSize * m_MapScale, 0, i + m_ChipAreaWidth + (m_XChipCount - m_XScroll) * m_XChipEditorSize * m_MapScale, i + (m_YChipCount - m_YScroll) * m_YChipEditorSize * m_MapScale, MOF_XRGB(255, 0, 0));
		}
	}
}

void CGameEditor::RenderGimmickFrame() {
	if (!m_bGimmickMode) { return; }
	for (int l = 0; l < m_LayerCount; l++)
	{
		for (int y = 0; y < m_YChipCount; y++)
		{
			for (int x = 0; x < m_XChipCount; x++)
			{
				for (int i = 0; i < 2; i++)
				{
					if (m_pGimmickData[l * m_YChipCount * m_XChipCount + y * m_XChipCount + x] == -1) {
						continue;
					}
					float xsel = 0, ysel = 0;
					if (m_bRhombus)
					{
						if (y % 2 == 0)
						{
							xsel = m_ChipAreaWidth + (x - m_XScroll + 0.5) * (m_XChipEditorSize * m_MapScale);
						}
						else
						{
							xsel = m_ChipAreaWidth + (x - m_XScroll) * (m_XChipEditorSize * m_MapScale);
						}
						ysel = (y - m_YScroll) * (m_YChipEditorSize * m_MapScale) / 2;
					}
					else
					{
						xsel = m_ChipAreaWidth + (x - m_XScroll) * (m_XChipEditorSize * m_MapScale);
						ysel = (y - m_YScroll) * (m_YChipEditorSize * m_MapScale);
					}
					if (m_bRhombus)
					{
						CGraphicsUtilities::RenderLine(xsel + (m_XChipEditorSize * m_MapScale) / 2, ysel + i, xsel + (m_XChipEditorSize * m_MapScale) - i, ysel + (m_YChipEditorSize * m_MapScale) / 2, MOF_XRGB(200, 0, 200));
						CGraphicsUtilities::RenderLine(xsel + (m_XChipEditorSize * m_MapScale) - i, ysel + (m_YChipEditorSize * m_MapScale) / 2, xsel + (m_XChipEditorSize * m_MapScale) / 2, ysel + (m_YChipEditorSize * m_MapScale) - i, MOF_XRGB(200, 0, 200));
						CGraphicsUtilities::RenderLine(xsel + (m_XChipEditorSize * m_MapScale) / 2, ysel + (m_YChipEditorSize * m_MapScale) - i, xsel + i, ysel + (m_YChipEditorSize * m_MapScale) / 2, MOF_XRGB(200, 0, 200));
						CGraphicsUtilities::RenderLine(xsel + i, ysel + (m_YChipEditorSize * m_MapScale) / 2, xsel + (m_XChipEditorSize * m_MapScale) / 2, ysel + i, MOF_XRGB(200, 0, 200));
					}
					else
						CGraphicsUtilities::RenderRect(xsel, ysel, xsel + (m_XChipEditorSize * m_MapScale), ysel + (m_YChipEditorSize * m_MapScale), MOF_XRGB(20, 0, 200));
				}
			}
		}
	}

	if (m_GimickSelectNo >= 0)
	{
		float xsel = 0;
		float ysel = 0;
		float gxsel = 0;
		float gysel = 0;

		//
		int cn = m_GimickSelectNo;
		for (int i = 0; i < m_LayerCount; i++)
		{
			if (cn - m_YChipCount * m_XChipCount >= 0)
			{
				cn -= m_YChipCount * m_XChipCount;
			}
			else
			{
				continue;
			}
		}
		for (int i = 0; i < m_YChipCount; i++)
		{
			if (cn - m_XChipCount >= 0)
			{
				cn -= m_XChipCount;
				ysel++;
			}
			else
			{
				continue;
			}
		}
		if (int(ysel) % 2 == 0)
		{
			xsel = m_ChipAreaWidth + (cn - m_XScroll + 0.5) * (m_XChipEditorSize * m_MapScale);
		}
		else
		{
			xsel = m_ChipAreaWidth + (cn - m_XScroll) * (m_XChipEditorSize * m_MapScale);
		}
		ysel = (ysel - m_YScroll) * (m_YChipEditorSize * m_MapScale) / 2;
		//

		if (m_pGimmickData[m_GimickSelectNo] >= 0 && m_pGimmickData[m_pGimmickData[m_GimickSelectNo]] == m_GimickSelectNo)
		{
			int gn = m_pGimmickData[m_GimickSelectNo];
			for (int i = 0; i < m_LayerCount; i++)
			{
				if (gn - m_YChipCount * m_XChipCount >= 0)
				{
					gn -= m_YChipCount * m_XChipCount;
				}
				else
				{
					continue;
				}
			}
			for (int i = 0; i < m_YChipCount; i++)
			{
				if (gn - m_XChipCount >= 0)
				{
					gn -= m_XChipCount;
					gysel++;
				}
				else
				{
					continue;
				}
			}
			if (int(gysel) % 2 == 0)
			{
				gxsel = m_ChipAreaWidth + (gn - m_XScroll + 0.5) * (m_XChipEditorSize * m_MapScale);
			}
			else
			{
				gxsel = m_ChipAreaWidth + (gn - m_XScroll) * (m_XChipEditorSize * m_MapScale);
			}
			gysel = (gysel - m_YScroll) * (m_YChipEditorSize * m_MapScale) / 2;
		}
		
		for (int i = 0; i < 2; i++)
		{
			if (m_bRhombus)
			{
				CGraphicsUtilities::RenderLine(xsel + (m_XChipEditorSize * m_MapScale) / 2, ysel + i, xsel + (m_XChipEditorSize * m_MapScale) - i, ysel + (m_YChipEditorSize * m_MapScale) / 2, MOF_COLOR_BLUE);
				CGraphicsUtilities::RenderLine(xsel + (m_XChipEditorSize * m_MapScale) - i, ysel + (m_YChipEditorSize * m_MapScale) / 2, xsel + (m_XChipEditorSize * m_MapScale) / 2, ysel + (m_YChipEditorSize * m_MapScale) - i, MOF_COLOR_BLUE);
				CGraphicsUtilities::RenderLine(xsel + (m_XChipEditorSize * m_MapScale) / 2, ysel + (m_YChipEditorSize * m_MapScale) - i, xsel + i, ysel + (m_YChipEditorSize * m_MapScale) / 2, MOF_COLOR_BLUE);
				CGraphicsUtilities::RenderLine(xsel + i, ysel + (m_YChipEditorSize * m_MapScale) / 2, xsel + (m_XChipEditorSize * m_MapScale) / 2, ysel + i, MOF_COLOR_BLUE);
			}
			else
				CGraphicsUtilities::RenderRect(xsel, ysel, xsel + (m_XChipEditorSize * m_MapScale), ysel + (m_YChipEditorSize * m_MapScale), MOF_COLOR_BLUE);
		}

		if (m_pGimmickData[m_GimickSelectNo] >= 0 && m_pGimmickData[m_pGimmickData[m_GimickSelectNo]] == m_GimickSelectNo)
		{
			for (int i = 0; i < 2; i++)
			{
				CGraphicsUtilities::RenderLine(gxsel + (m_XChipEditorSize * m_MapScale) / 2, gysel + i, gxsel + (m_XChipEditorSize * m_MapScale) - i, gysel + (m_YChipEditorSize * m_MapScale) / 2, MOF_COLOR_GREEN);
				CGraphicsUtilities::RenderLine(gxsel + (m_XChipEditorSize * m_MapScale) - i, gysel + (m_YChipEditorSize * m_MapScale) / 2, gxsel + (m_XChipEditorSize * m_MapScale) / 2, gysel + (m_YChipEditorSize * m_MapScale) - i, MOF_COLOR_GREEN);
				CGraphicsUtilities::RenderLine(gxsel + (m_XChipEditorSize * m_MapScale) / 2, gysel + (m_YChipEditorSize * m_MapScale) - i, gxsel + i, gysel + (m_YChipEditorSize * m_MapScale) / 2, MOF_COLOR_GREEN);
				CGraphicsUtilities::RenderLine(gxsel + i, gysel + (m_YChipEditorSize * m_MapScale) / 2, gxsel + (m_XChipEditorSize * m_MapScale) / 2, gysel + i, MOF_COLOR_GREEN);
			}
		}
	}
}

void CGameEditor::RenderMapChip() {
	// m_MapchipTypeArrayに入れる
	float chipsize = m_XChipSize;
	if (m_XChipSize < m_YChipSize)
	{
		chipsize = m_YChipSize;
	}
	float chipsizewidth = m_ChipTexture.GetWidth();
	float chipsizeheight = m_ChipTexture.GetHeight();
	int widthcount = chipsizewidth / chipsize;
	int heightcount = chipsizeheight / chipsize;

	//
	float scale = m_Squares / chipsize;
	for (int i = 0; i < CHIPAREA_COUNT * 4 - 2; i++)
	{
		if (m_MapchipTypeArray[i] == -1) { continue; }
		int xcnt = i % 4;
		int ycnt = i / 4;
		int xtypecnt = m_MapchipTypeArray[i] % widthcount;
		int ytypecnt = m_MapchipTypeArray[i] / widthcount;

		CRectangle rec = {chipsize * xtypecnt,chipsize * ytypecnt,chipsize * (xtypecnt + 1),chipsize * (ytypecnt + 1)};
		m_ChipTexture.RenderScale(m_Squares * xcnt,m_ChipAreaOffset + m_Squares * ycnt,scale,rec);
	}
}

void CGameEditor::RenderTabView() {
	if (m_TabViewSelect < 0) { return; }
	switch (m_TabViewSelect)
	{
	case 0:
	{
		float chipsize = m_XChipSize;
		if (m_XChipSize < m_YChipSize)
		{
			chipsize = m_YChipSize;
		}
		float scale = m_Squares / chipsize;
		int widthcount = m_ChipTexture.GetWidth() / chipsize;
		int heightcount = m_ChipTexture.GetHeight() / chipsize;
		float chipcount = widthcount * heightcount;
		int tabxcount = ceil(chipcount / CHIPAREA_COUNT);

		CGraphicsUtilities::RenderFillRect(m_ChipAreaWidth,m_ChipAreaOffset,m_ChipAreaWidth + m_Squares * tabxcount,m_ChipAreaHeight,MOF_XRGB(80,80,80));

		for (int i = 0; i < widthcount * heightcount; i++)
		{
			int xcnt = i % tabxcount;
			int ycnt = i / tabxcount;
			int xtypecnt = i % widthcount;
			int ytypecnt = i / widthcount;

			CRectangle rec = { chipsize * xtypecnt,chipsize * ytypecnt,chipsize * (xtypecnt + 1),chipsize * (ytypecnt + 1) };
			m_ChipTexture.RenderScale(m_ChipAreaWidth + m_Squares * xcnt, m_ChipAreaOffset + m_Squares * ycnt, scale, rec);
		}
		for (int x = 0; x <= tabxcount; x++)
		{
			CGraphicsUtilities::RenderLine(m_ChipAreaWidth + x * m_Squares, m_ChipAreaOffset, m_ChipAreaWidth + x * m_Squares, m_ChipAreaHeight,MOF_COLOR_WHITE);
		}
		for (int y = 0; y <= CHIPAREA_COUNT; y++)
		{
			CGraphicsUtilities::RenderLine(m_ChipAreaWidth, m_ChipAreaOffset + y * m_Squares, m_ChipAreaWidth + tabxcount * m_Squares, m_ChipAreaOffset + y * m_Squares, MOF_COLOR_WHITE);
		}
	}
		break;
	case 1:
		break;
	default:
		break;
	}
}

void CGameEditor::Release(){
	ReleaseMapData();
}

void CGameEditor::ReleaseMapData() {
	// 確保したデータの解放
	m_BackTexture.Release();
	m_ChipTexture.Release();
	m_EnemyTextureArray.Release();
	m_ItemTextureArray.Release();
	if (m_pChipData)
	{
		free(m_pChipData);
		m_pChipData = NULL;
	}
	if (m_pEnemyData)
	{
		free(m_pEnemyData);
		m_pEnemyData = NULL;
	}
	if (m_pItemData)
	{
		free(m_pItemData);
		m_pItemData = NULL;
	}
	if (m_pGimmickData)
	{
		free(m_pGimmickData);
		m_pGimmickData = NULL;
	}
}