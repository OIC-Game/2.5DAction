#pragma once

#include "GameApp.h"
#include "CPlayer.h"
#include "CEnemy.h"

class CStage
{
private:
	//チップ番号列挙型変数
	enum tag_CHIPNO {
		LEVER_OFF1 = 27,
		LEVER_ON1 = 28,
		LEVER_OFF2 = 30,
		LEVER_ON2 = 29,
		REDFLOOR_1 = 53,
		REDFLOOR_2 = 54,
		YELLOWFLOOR_1 = 56,
		YELLOWFLOOR_2 = 57,
		BRIDGE_LEFTDOWN = 15,
		BRIDGE_LEFTUP = 16,
		BRIDGE_LEFTMIDDLE = 20,
		BRIDGE_RIGHTDOWN = 18,
		BRIDGE_RIGHTUP = 19,
		BRIDGE_RIGHTMIDDLE = 17,
		DESC = 14,
		PCDESC = 13,
		CHARGER = 6,
	};

	CTexture				m_ChipTexture;
	CTexture				m_BackTexture;

	int						m_PlayerPosX = 0;					//プレイヤーの初期位置
	int						m_PlayerPosY = 0;
	int						m_PlayerSize = 256;

	int						m_XChipSize;						//チップサイズ
	int						m_YChipSize;						//チップサイズ
	int						m_XChipEditorSize;					//エディタチップサイズ
	int						m_YChipEditorSize;					//エディタチップサイズ
	int						m_XChipCount;
	int						m_YChipCount;
	int						m_LayerCount;						// レイヤー数
	int*					m_pChipData = NULL;

	int						m_bRhombus;							//斜め判定

	float					m_ScrollX;
	float					m_ScrollY;

	float					m_MapScale = 1.0f;					//マップの拡大率

	int						m_EnemyTextureCount;
	CDynamicArray< CTexture* >	m_EnemyTextureArray;			// 敵画像配置
	int*					m_pEnemyData;
	int						m_EnemyCount;

	int						m_ItemTextureCount;
	CDynamicArray< CTexture* >	m_ItemTextureArray;				// アイテム画像配置
	int*					m_pItemData;
	int						m_ItemCount;

	int*		m_pGimmickData = NULL;							//ギミックデータ格納用

public:
	CStage() :
		m_ChipTexture(),
		m_BackTexture(),
		m_XChipSize(0),
		m_YChipSize(0),
		m_XChipCount(0),
		m_YChipCount(0),
		m_pChipData(NULL),
		m_ScrollX(0),
		m_ScrollY(0) {

	}
	~CStage();
	bool Load(char* pName);
	void Initialize(CEnemy* pEnemy);
	void Update(void);
	bool Collision(CRectangle r, float& ox, float& oy, bool& chrage);
	void CollisionGimmickFloor(CRectangle r);
	void BuildBridge(int cn, int selx, int sely);
	void SetPC(int selx, int sely);
	void Render(void);
	void RenderFrontWall(void);
	void RenderDebug(void);
	void Release(void);
	float GetScrollX(void) { return m_ScrollX; };
	float GetScrollY(void) { return m_ScrollY; };

	CRectangle GetStageRect(int cn, int x, int y) {
		if (m_bRhombus)
		{
			if (y % 2 == 0)
				return CRectangle((x + 0.5) * m_XChipEditorSize, y * m_YChipEditorSize / 2, (x + 0.5) * m_XChipEditorSize + m_XChipEditorSize, y * m_YChipEditorSize / 2 + m_YChipEditorSize);
			else
				return CRectangle(x * m_XChipEditorSize, y * m_YChipEditorSize / 2, (x + 1) * m_XChipEditorSize, y * m_YChipEditorSize / 2 + m_YChipEditorSize);
		}
		return CRectangle(x * m_XChipEditorSize, y * m_YChipEditorSize, x * m_XChipEditorSize + m_XChipEditorSize, y * m_YChipEditorSize + m_YChipEditorSize - (m_XChipEditorSize - m_YChipEditorSize));
	}

	//敵の数をカウント
	int GetEnemyCount(void) { return m_EnemyCount; }
};

