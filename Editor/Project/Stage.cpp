#include "CStage.h"

CStage::~CStage()
{
}

bool CStage::Load(char* pName) {
	//テキストファイルを開く
	FILE* fp = fopen(pName, "rt");
	if (fp == NULL)
	{
		return false;
	}
	//ファイルの全容量を調べる
	//一度ファイルの終端に移動して、その位置を調べることでサイズがわかる
	//調べ終わった後はファイルの先頭に移動して戻しておく
	//ただしこの方法でも正常なサイズを読み込むことはできない
	fseek(fp, 0, SEEK_END);
	long fSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	//ファイルサイズ分だけのメモリを確保する
	//終端を含めるため＋１しておく
	char* pBuffer = (char*)malloc(fSize + 1);
	//ファイルを全てバッファに読み込む
	//ここで実際に読み込めたサイズを調べてその終端に\0を入る
	fSize = fread(pBuffer, 1, fSize, fp);
	pBuffer[fSize] = '\0';
	char* pstr;

	//テクスチャの読み込み
	pstr = strtok(pBuffer, ",");
	if (!m_BackTexture.Load(pstr))
	{
		//return false;
	}
	pstr = strtok(NULL, ",");
	if (!m_ChipTexture.Load(pstr))
	{
		//return false;
	}

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

	//マップのチップ数
	pstr = strtok(NULL, ",");
	m_XChipCount = atoi(pstr);
	pstr = strtok(NULL, ",");
	m_YChipCount = atoi(pstr);
	pstr = strtok(NULL, ",");
	m_LayerCount = atoi(pstr);


	int totalChips = m_XChipCount * m_YChipCount * m_LayerCount;
	//マップチップ用のメモリ確保
	m_pChipData = (int*)malloc(sizeof(int) * totalChips);
	//敵配置メモリ確保
	m_pEnemyData = (int*)malloc(sizeof(int) * totalChips);
	//アイテム配置メモリ確保
	m_pItemData = (int*)malloc(sizeof(int) * totalChips);

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
			//return false;
		}
		//テクスチャを配列に追加する
		m_EnemyTextureArray.Add(&tmp);
	}

	//配置データの読み込み
	m_EnemyCount = 0;
	for (int l = 0; l < m_LayerCount; l++)
	{
		for (int y = 0; y < m_YChipCount; y++)
		{
			for (int x = 0; x < m_XChipCount; x++)
			{
				pstr = strtok(NULL, ",");
				m_pEnemyData[l * m_XChipCount * m_YChipCount + y * m_XChipCount + x] = atoi(pstr);
				if (m_pEnemyData[l * m_XChipCount * m_YChipCount + y * m_XChipCount + x] > 0)
				{
					m_EnemyCount++;
				}
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
			//return false;
		}
		//テクスチャを配列に追加する
		m_ItemTextureArray.Add(&tmp);
	}

	//配置データの読み込み
	m_ItemCount = 0;
	for (int l = 0; l < m_LayerCount; l++)
	{
		for (int y = 0; y < m_YChipCount; y++)
		{
			for (int x = 0; x < m_XChipCount; x++)
			{
				pstr = strtok(NULL, ",");
				m_pItemData[l * m_XChipCount * m_YChipCount + y * m_XChipCount + x] = atoi(pstr);
				if (m_pItemData[l * m_XChipCount * m_YChipCount + y * m_XChipCount + x] > 0)
				{
					m_ItemCount++;
				}
			}
		}
	}

	//ギミックデータの読み込み
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

/*void CStage::Initialize(CEnemy* pEnemy) {
	m_ScrollX = 0;
	m_ScrollY = 0;
	int n = 0;
	for (int l = 0; l < m_LayerCount; l++)
	{
		for (int y = 0; y < m_YChipCount; y++)
		{
			for (int x = 0; x < m_XChipCount; x++)
			{
				//配置番号
				//番号0は配置しない
				char on = m_pEnemyData[l * m_XChipCount * m_YChipCount + y * m_XChipCount + x] - 1;
				if (on < 0)
				{
					continue;
				}
				//pEnemy[n].SetTexture(m_EnemyTextureArray[on]);
				if (m_bRhombus)
				{
					if (y % 2 == 0)
						pEnemy[n++].Initialize((x + 0.5) * m_XChipEditorSize, y * m_YChipEditorSize / 2, on);
					else
						pEnemy[n++].Initialize(x * m_XChipEditorSize, y * m_YChipEditorSize / 2, on);
				}
				else
					pEnemy[n++].Initialize(x * m_XChipEditorSize, y * m_YChipEditorSize, on);
			}
		}
	}
}*/

void CStage::Update(void) {
}

/*
* 当たり判定
*
* 引数
* [in]		r			判定矩形
* [out]		ox			X埋まり
* [out]		oy			Y埋まり
*/

bool CStage::Collision(CRectangle r, float& ox, float& oy, bool& charge) {
	bool re = false;
	//当たり判定する矩形の左上と右下のチップ位置を求める
	int lc = r.Left / m_XChipEditorSize;
	int rc = r.Right / m_XChipEditorSize;
	int tc = r.Top / m_YChipEditorSize;
	int bc = r.Bottom / m_YChipEditorSize;
	if (m_bRhombus)
	{
		tc = r.Top / m_YChipEditorSize * 2;
		bc = r.Bottom / m_YChipEditorSize * 2;
	}
	//ステージの範囲外にはならないようにする
	tc--;
	lc--;
	if (lc < 0)
	{
		lc = 0;
	}
	if (tc < 0)
	{
		tc = 0;
	}
	if (rc >= m_XChipCount)
	{
		rc = m_XChipCount - 1;
	}
	if (bc >= m_YChipCount)
	{
		bc = m_YChipCount - 1;
	}

	//どこの矩形に衝突しているか
	int left = 0;
	int right = 0;
	int top = 0;
	int bottom = 0;
	//矩形当たり判定カウント用for文
	for (int l = 0; l < m_LayerCount; l++)
	{
		//レイヤー番号1は当たり判定しない
		if (l == 0) { continue; }
		for (int y = tc; y <= bc; y++)
		{
			for (int x = lc; x <= rc; x++)
			{

				//描画するチップ番号
				char cn = m_pChipData[l * m_XChipCount * m_YChipCount + y * m_XChipCount + x] - 1;

				//レイヤー番号2の配置済みチップ、レイヤー番号3のレバーの当たり判定消去
				if (l == 1 && cn >= 0) { continue; }
				if (l == 2 && cn < 0) { continue; }
				if (l == 2 && (cn == LEVER_OFF1 || cn == LEVER_ON1)) { continue; }

				CRectangle cr = GetStageRect(cn, x, y);

				//マップチップの矩形を四分割
				CRectangle rec[4] =
				{
					{cr.Left,cr.Top,cr.Left + cr.GetWidth() / 2,cr.Top + cr.GetHeight() / 2},//左上
					{cr.Left + cr.GetWidth() / 2,cr.Top,cr.Right,cr.Top + cr.GetHeight() / 2},//右上
					{cr.Left,cr.Top + cr.GetHeight() / 2,cr.Left + cr.GetWidth() / 2,cr.Bottom},//左下
					{cr.Left + cr.GetWidth() / 2,cr.Top + cr.GetHeight() / 2,cr.Right,cr.Bottom}//右下
				};

				//当たり判定用のキャラクタ矩形
				//下で範囲を限定した専用の矩形を作成する。
				CRectangle brec = r;
				brec.Top = brec.Bottom - brec.GetHeight() / 4;	//下の矩形は上側を下と同じ値にする
				brec.Expansion(-6, 0);

				//下と当たり判定
				if (rec[0].CollisionRect(brec))//左上
				{
					float FillValue = brec.Bottom - rec[0].Top; // どれだけ埋まったか
					float FillPercentage = FillValue / rec[0].GetHeight(); // 埋まった割合
					float WidthHeight = rec[0].GetWidth() * FillPercentage; // その高さの横幅
					float ReturnValue = rec[0].Right - WidthHeight - brec.Right;
					if (ReturnValue < 0)
					{
						left++;
						top++;
					}
				}
				if (rec[1].CollisionRect(brec))//右上
				{
					float FillValue = brec.Bottom - rec[1].Top; // どれだけ埋まったか
					float FillPercentage = FillValue / rec[1].GetHeight(); // 埋まった割合
					float WidthHeight = rec[1].GetWidth() * FillPercentage; // その高さの横幅
					float ReturnValue = rec[1].Left + WidthHeight - brec.Left;
					if (ReturnValue > 0)
					{
						right++;
						top++;
					}
				}
				if (rec[2].CollisionRect(brec))//左下
				{
					float FillValue = rec[2].Bottom - brec.Top; // どれだけ埋まったか
					float FillPercentage = FillValue / rec[2].GetHeight(); // 埋まった割合
					float WidthHeight = rec[2].GetWidth() * FillPercentage; // その高さの横幅
					float ReturnValue = rec[2].Right - WidthHeight - brec.Right;
					if (ReturnValue < 0)
					{
						left++;
						bottom++;
					}
				}
				if (rec[3].CollisionRect(brec))//右下
				{
					float FillValue = rec[3].Bottom - brec.Top; // どれだけ埋まったか
					float FillPercentage = FillValue / rec[3].GetHeight(); // 埋まった割合
					float WidthHeight = rec[3].GetWidth() * FillPercentage; // その高さの横幅
					float ReturnValue = rec[3].Left + WidthHeight - brec.Left;
					if (ReturnValue > 0)
					{
						right++;
						bottom++;
					}
				}
			}
		}
	}
	//矩形当たり判定計算用for文
	for (int l = 0; l < m_LayerCount; l++)
	{
		//レイヤー番号1は当たり判定しない
		if (l == 0) { continue; }
		for (int y = tc; y <= bc; y++)
		{
			for (int x = lc; x <= rc; x++)
			{

				//描画するチップ番号
				char cn = m_pChipData[l * m_XChipCount * m_YChipCount + y * m_XChipCount + x] - 1;

				//レイヤー番号2の配置済みチップ、レイヤー番号3のレバーの当たり判定消去
				if (l == 1 && cn >= 0) { continue; }
				if (l == 2 && cn < 0) { continue; }
				if (l == 2 && (cn == LEVER_OFF1 || cn == LEVER_ON1)) { continue; }

				CRectangle cr = GetStageRect(cn, x, y);

				//マップチップの矩形を四分割
				CRectangle rec[4] =
				{
					{cr.Left,cr.Top,cr.Left + cr.GetWidth() / 2,cr.Top + cr.GetHeight() / 2},//左上
					{cr.Left + cr.GetWidth() / 2,cr.Top,cr.Right,cr.Top + cr.GetHeight() / 2},//右上
					{cr.Left,cr.Top + cr.GetHeight() / 2,cr.Left + cr.GetWidth() / 2,cr.Bottom},//左下
					{cr.Left + cr.GetWidth() / 2,cr.Top + cr.GetHeight() / 2,cr.Right,cr.Bottom}//右下
				};

				//当たり判定用のキャラクタ矩形
				//下で範囲を限定した専用の矩形を作成する。
				CRectangle brec = r;
				brec.Top = brec.Bottom - brec.GetHeight() / 4;
				brec.Expansion(-6, 0);
				if (left > 0 && left == right && cr.CollisionRect(brec))
				{
					if (top > bottom)
					{
						float FillValue = brec.Right - rec[0].Left; // どれだけ埋まったか
						float FillPercentage = FillValue / rec[0].GetWidth(); // 埋まった割合
						if (FillPercentage > 2)
							FillPercentage -= 2;
						else if (FillPercentage > 1)
							FillPercentage = 1;
						float WidthHeight = rec[0].GetHeight() * FillPercentage; // その高さの横幅
						float ReturnValue = brec.Bottom + WidthHeight - rec[0].Bottom;//rec[0].Bottom - c - brec.Bottom;
						if (ReturnValue > 0)
						{
							oy -= ReturnValue;
							re = true;
						}
					}
					else
					{
						float FillValue = brec.Right - rec[2].Left; // どれだけ埋まったか
						float FillPercentage = FillValue / rec[2].GetWidth(); // 埋まった割合
						if (FillPercentage > 2)
							FillPercentage -= 2;
						else if (FillPercentage > 1)
							FillPercentage = 1;
						float WidthHeight = rec[2].GetHeight() * FillPercentage; // その高さの横幅
						float ReturnValue = brec.Top - WidthHeight - rec[2].Top;//rec[0].Bottom - c - brec.Bottom;
						if (ReturnValue < 0)
						{
							oy -= ReturnValue;
							re = true;
						}
					}
				}
				//下と当たり判定
				else if (rec[0].CollisionRect(brec))//左上
				{
					float FillValue = brec.Bottom - rec[0].Top; // どれだけ埋まったか
					float FillPercentage = FillValue / rec[0].GetHeight(); // 埋まった割合
					float WidthHeight = rec[0].GetWidth() * FillPercentage; // その高さの横幅
					float ReturnValue = rec[0].Right - WidthHeight - brec.Right;
					if (ReturnValue < 0)
					{
						ox += ReturnValue;
						re = true;
					}
				}
				else if (rec[1].CollisionRect(brec))//右上
				{
					float FillValue = brec.Bottom - rec[1].Top; // どれだけ埋まったか
					float FillPercentage = FillValue / rec[1].GetHeight(); // 埋まった割合
					float WidthHeight = rec[1].GetWidth() * FillPercentage; // その高さの横幅
					float ReturnValue = rec[1].Left + WidthHeight - brec.Left;
					if (ReturnValue > 0)
					{
						ox += ReturnValue;
						re = true;
					}
				}
				else if (rec[2].CollisionRect(brec) && (left == 1 && right == 3 && top == 1 && bottom == 3) == false)//左下
				{
					float FillValue = rec[2].Bottom - brec.Top; // どれだけ埋まったか
					float FillPercentage = FillValue / rec[2].GetHeight(); // 埋まった割合
					float WidthHeight = rec[2].GetWidth()* FillPercentage; // その高さの横幅
					float ReturnValue = rec[2].Right - WidthHeight - brec.Right;
					if (ReturnValue < 0)
					{
						ox += ReturnValue;
						re = true;
					}
				}
				else if (rec[3].CollisionRect(brec))//右下
				{
					float FillValue = rec[3].Bottom - brec.Top; // どれだけ埋まったか
					float FillPercentage = FillValue / rec[3].GetHeight(); // 埋まった割合
					float WidthHeight = rec[3].GetWidth() * FillPercentage; // その高さの横幅
					float ReturnValue = rec[3].Left + WidthHeight - brec.Left;
					if (ReturnValue > 0)
					{
						ox += ReturnValue;
						re = true;
					}
				}
				if (re == true && cn == CHARGER)
				{
					charge = true;
				}
			}
		}
	}
	return re;
}

/**
 * ギミック床衝突の判定
 * 衝突している床によってギミックを発動させる
 *
 * 引数
 * [in]			r					プレイヤーの矩形
 */
void CStage::CollisionGimmickFloor(CRectangle r) {
	float mx = (r.Left + r.Right) / 2;
	float my = (r.Top + r.Bottom) / 2;
	int selX;
	int selY;
	//当たり判定の区別
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
				float p0x = (x + shiftx) * m_XChipEditorSize * m_MapScale;
				float p0y = y * m_YChipEditorSize * m_MapScale / 2;
				float p1x = (x + shiftx + 0.5) * m_XChipEditorSize * m_MapScale;
				float p1y = p0y + m_YChipEditorSize * m_MapScale / 2;
				float p2x = (x + shiftx) * m_XChipEditorSize * m_MapScale;
				float p2y = p0y + m_YChipEditorSize * m_MapScale;
				double Area = 0.5 *(-p1y * p2x + p0y * (-p1x + p2x) + p0x * (p1y - p2y) + p1x * p2y);
				double s = 1 / (2 * Area)*(p0y*p2x - p0x * p2y + (p2y - p0y)*mx + (p0x - p2x)*my);
				double t = 1 / (2 * Area)*(p0x*p1y - p0y * p1x + (p0y - p1y)*mx + (p1x - p0x)*my);

				if (0 < s  && s < 1 && 0 < t && t < 1) {
					if (0 < 1 - s - t && 1 - s - t < 1)
					{
						selY = y;
						selX = x;
					}
				}

				p1x = (x + shiftx - 0.5) * m_XChipEditorSize * m_MapScale;
				Area = 0.5 *(-p1y * p2x + p0y * (-p1x + p2x) + p0x * (p1y - p2y) + p1x * p2y);
				s = 1 / (2 * Area)*(p0y*p2x - p0x * p2y + (p2y - p0y)*mx + (p0x - p2x)*my);
				t = 1 / (2 * Area)*(p0x*p1y - p0y * p1x + (p0y - p1y)*mx + (p1x - p0x)*my);

				if (0 < s  && s < 1 && 0 < t && t < 1) {
					if (0 < 1 - s - t && 1 - s - t < 1)
					{
						selY = y;
						selX = x;
					}
				}
			}
		}
	}
	else
	{
		selX = (int)(m_ScrollX + (mx) / (m_XChipEditorSize * m_MapScale));
		selY = (int)(m_ScrollY + my / (m_YChipEditorSize * m_MapScale));
	}

	int no = m_YChipCount * m_XChipCount + selY * m_XChipCount + selX;
	int cn = m_pChipData[no] - 1;
	int gn = m_pGimmickData[no];
	int gnn = 0;
	if (gn != -1)
	{
		gnn = m_pGimmickData[gn];
	}
	//レバーギミック
	if (cn == REDFLOOR_1 || cn == REDFLOOR_2)
	{
		if (m_pChipData[2 * m_YChipCount * m_XChipCount + selY * m_XChipCount + selX] == 0)
		{
			m_pChipData[2 * m_YChipCount * m_XChipCount + selY * m_XChipCount + selX] = 27 + 1;
		}
		else if (gnn == no)
		{
			m_pChipData[2 * m_YChipCount * m_XChipCount + selY * m_XChipCount + selX] = 28 + 1;
			int cgn = m_pChipData[gn];
			if (cgn == 21)
			{
				m_pChipData[m_pGimmickData[no]] = 22;
			}
			else if (cgn == 23)
			{
				m_pChipData[m_pGimmickData[no]] = 24;
			}
		}
	}
	//橋ギミック
	else if (cn == YELLOWFLOOR_1 || cn == YELLOWFLOOR_2)
	{
		BuildBridge(cn, selX, selY);
	}
}

/**
 * 橋作成
 * 対象となる黄色い床に向かって橋を生成する
 *
 * 引数
 * [in]			cn					チップナンバー
 * [in]			selx				X座標
 * [in]			sely				Y座標
 */
void CStage::BuildBridge(int cn, int selx, int sely) {
	int countBridge = 0;
	int direction = 0;
	int checkno = 0;
	int selX = selx;
	int selY = sely;
	if (cn == YELLOWFLOOR_1)
	{
		do
		{
			if (selY % 2 == 0)
			{
				// 右上
				selY--;
				selX++;
				countBridge++;
			}
			else
			{
				selY--;
				countBridge++;
			}
			int cnn = m_pChipData[m_YChipCount * m_XChipCount + selY * m_XChipCount + selX] - 1;
			if (cnn != -1 || selX > m_XChipCount || selY < 0)
			{
				if (cnn == YELLOWFLOOR_1)
				{
					checkno = 1;
					direction = 1;
				}
				else
				{
					checkno = 2;
				}
			}
		} while (checkno == 0);
		if (checkno == 2)
		{
			checkno = 0;
			selX = selx;
			selY = sely;
			countBridge = 0;
			do
			{
				if (selY % 2 == 0)
				{
					// 右上
					selY++;
					countBridge++;
				}
				else
				{
					selY++;
					selX--;
					countBridge++;
				}
				int cnn = m_pChipData[m_YChipCount * m_XChipCount + selY * m_XChipCount + selX] - 1;
				if (cnn != -1 || selY > m_YChipCount || selX < 0)
				{
					if (cnn == YELLOWFLOOR_1)
					{
						checkno = 1;
						direction = 2;
					}
					else
					{
						checkno = 2;
					}
				}
			} while (checkno == 0);
		}
	}
	else if (cn == YELLOWFLOOR_2)
	{
		do
		{
			if (selY % 2 == 0)
			{
				// 左上
				selY--;
				countBridge++;
			}
			else
			{
				selY--;
				selX--;
				countBridge++;
			}
			int cnn = m_pChipData[m_YChipCount * m_XChipCount + selY * m_XChipCount + selX] - 1;
			if (cnn != -1 || selX < 0 || selY < 0)
			{
				if (cnn == YELLOWFLOOR_2)
				{
					checkno = 1;
					direction = 1;
				}
				else
				{
					checkno = 2;
				}
			}
		} while (checkno == 0);
		if (checkno == 2)
		{
			checkno = 0;
			selX = selx;
			selY = sely;
			countBridge = 0;
			do
			{
				if (selY % 2 == 0)
				{
					// 右上
					selY++;
					selX++;
					countBridge++;
				}
				else
				{
					selY++;
					countBridge++;
				}
				int cnn = m_pChipData[m_YChipCount * m_XChipCount + selY * m_XChipCount + selX] - 1;
				if (cnn != -1 || selY > m_YChipCount || selX > m_XChipCount)
				{
					if (cnn == YELLOWFLOOR_2)
					{
						checkno = 1;
						direction = 2;
					}
					else
					{
						checkno = 2;
					}
				}
			} while (checkno == 0);
		}
	}

	// 橋の設置
	if (countBridge <= 1 || checkno != 1) { return; }
	selX = selx;
	selY = sely;
	if (cn == YELLOWFLOOR_1)
	{
		for (int i = 0; i < countBridge - 1; i++)
		{
			if (direction == 1)
			{
				if (selY % 2 == 0)
				{
					// 右上
					selY--;
					selX++;
				}
				else
				{
					selY--;
				}
			}
			else if (direction == 2)
			{
				if (selY % 2 == 0)
				{
					// 右上
					selY++;
				}
				else
				{
					selY++;
					selX--;
				}
			}

			if (i == 0)
			{
				if (direction == 1)
					m_pChipData[m_YChipCount * m_XChipCount + selY * m_XChipCount + selX] = BRIDGE_LEFTDOWN;
				else
					m_pChipData[m_YChipCount * m_XChipCount + selY * m_XChipCount + selX] = BRIDGE_LEFTUP;
			}
			else if (i == countBridge - 2)
			{
				if (direction == 1)
					m_pChipData[m_YChipCount * m_XChipCount + selY * m_XChipCount + selX] = BRIDGE_LEFTUP;
				else
					m_pChipData[m_YChipCount * m_XChipCount + selY * m_XChipCount + selX] = BRIDGE_LEFTDOWN;
			}
			else
			{
				m_pChipData[m_YChipCount * m_XChipCount + selY * m_XChipCount + selX] = BRIDGE_LEFTMIDDLE;
			}
		}
	}
	else if (cn == YELLOWFLOOR_2)
	{
		for (int i = 0; i < countBridge - 1; i++)
		{
			if (direction == 1)
			{
				if (selY % 2 == 0)
				{
					// 右上
					selY--;
				}
				else
				{
					selY--;
					selX--;
				}
			}
			else if (direction == 2)
			{
				if (selY % 2 == 0)
				{
					// 右上
					selY++;
					selX++;
				}
				else
				{
					selY++;
				}
			}

			if (i == 0)
			{
				if (direction == 1)
					m_pChipData[m_YChipCount * m_XChipCount + selY * m_XChipCount + selX] = BRIDGE_RIGHTDOWN;
				else
					m_pChipData[m_YChipCount * m_XChipCount + selY * m_XChipCount + selX] = BRIDGE_RIGHTUP;
			}
			else if (i == countBridge - 2)
			{
				if (direction == 1)
					m_pChipData[m_YChipCount * m_XChipCount + selY * m_XChipCount + selX] = BRIDGE_RIGHTUP;
				else
					m_pChipData[m_YChipCount * m_XChipCount + selY * m_XChipCount + selX] = BRIDGE_RIGHTDOWN;
			}
			else
			{
				m_pChipData[m_YChipCount * m_XChipCount + selY * m_XChipCount + selX] = BRIDGE_RIGHTMIDDLE;
			}
		}
	}
}

/**
 * PC設置
 * PCが設置されていない机にPCを設置する
 *
 * 引数
 * [in]			selx				X座標
 * [in]			sely				Y座標
 */
void CStage::SetPC(int selx, int sely) {
	int selX = selx;
	int selY = sely;

	if (selY % 2 == 0)
	{
		// 右上
		selY--;
		selX++;
	}
	else
	{
		selY--;
	}
	int no = 2 * m_YChipCount * m_XChipCount + selY * m_XChipCount + selX;

	int cn = m_pChipData[no];
	if (cn == DESC)
	{
		m_pChipData[no] = PCDESC;
	}
}

void CStage::Render() {
	// テクスチャの横幅からマップチップの縦オフセットを求める
	int tcx = m_ChipTexture.GetWidth() / m_XChipSize;
	// マップチップの描画
	for (int l = 0; l < m_LayerCount; l++)
	{
		for (int y = 0; y < m_YChipCount; y++)
		{
			for (int x = 0; x < m_XChipCount; x++)
			{
				// 描画するチップ番号
				// チップ番号0は描画しない
				char cn = m_pChipData[l * m_XChipCount * m_YChipCount + y * m_XChipCount + x] - 1;
				if (cn + 1 == 0) { continue; }
				// マップチップの矩形
				CRectangle cr(m_XChipSize * (cn % tcx), m_YChipSize * (cn / tcx), m_XChipSize * (cn % tcx + 1), m_YChipSize * (cn / tcx + 1));
				// マップチップの描画
				if (m_bRhombus)
				{
					if (y % 2 == 0)
					{
						m_ChipTexture.Render(-m_ScrollX + (x + 0.5) * m_XChipEditorSize - (m_XChipSize - m_XChipEditorSize), -m_ScrollY + y * m_YChipEditorSize / 2 - (m_YChipSize - m_YChipEditorSize), cr);
					}
					else
					{
						m_ChipTexture.Render(-m_ScrollX + x * m_XChipEditorSize - (m_XChipSize - m_XChipEditorSize), -m_ScrollY + y * m_YChipEditorSize / 2 - (m_YChipSize - m_YChipEditorSize), cr);
					}
				}
				else
				{
					m_ChipTexture.Render(-m_ScrollX + x * m_XChipEditorSize - (m_XChipSize - m_XChipEditorSize), -m_ScrollY + y * m_YChipEditorSize - (m_YChipSize - m_YChipEditorSize), cr);
				}
			}
		}
	}
}

void CStage::RenderFrontWall(void) {
	// テクスチャの横幅からマップチップの縦オフセットを求める
	int tcx = m_ChipTexture.GetWidth() / m_XChipSize;
	// マップチップの描画
	for (int l = 0; l < m_LayerCount; l++)
	{
		for (int y = 0; y < m_YChipCount; y++)
		{
			for (int x = 0; x < m_XChipCount; x++)
			{
				// 描画するチップ番号
				// チップ番号36,41,42以外は描画しない
				char cn = m_pChipData[l * m_XChipCount * m_YChipCount + y * m_XChipCount + x] - 1;
				if (cn == 36 || cn == 41 || cn == 42)
				{
					// マップチップの矩形
					CRectangle cr(m_XChipSize * (cn % tcx), m_YChipSize * (cn / tcx), m_XChipSize * (cn % tcx + 1), m_YChipSize * (cn / tcx + 1));
					// マップチップの描画
					if (m_bRhombus)
					{
						if (y % 2 == 0)
						{
							m_ChipTexture.Render(-m_ScrollX + (x + 0.5) * m_XChipEditorSize - (m_XChipSize - m_XChipEditorSize), -m_ScrollY + y * m_YChipEditorSize / 2 - (m_YChipSize - m_YChipEditorSize), cr);
						}
						else
						{
							m_ChipTexture.Render(-m_ScrollX + x * m_XChipEditorSize - (m_XChipSize - m_XChipEditorSize), -m_ScrollY + y * m_YChipEditorSize / 2 - (m_YChipSize - m_YChipEditorSize), cr);
						}
					}
					else
					{
						m_ChipTexture.Render(-m_ScrollX + x * m_XChipEditorSize - (m_XChipSize - m_XChipEditorSize), -m_ScrollY + y * m_YChipEditorSize - (m_YChipSize - m_YChipEditorSize), cr);
					}
				}
				else
				{
					continue;
				}
			}
		}
	}
}

void CStage::RenderDebug(void) {
}

void CStage::Release() {
	m_ChipTexture.Release();
	m_BackTexture.Release();
	if (m_pChipData)
	{
		free(m_pChipData);
		m_pChipData = NULL;
	}
}