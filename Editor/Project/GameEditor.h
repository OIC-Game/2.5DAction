#pragma once
#include "ScensBace.h"
#include "GameDefine.h"
#include "resource.h"

class CGameEditor : public CScensBace
{
private:
#define  CHIPAREA_COUNT 5
	int m_XScrollWait = 0;
	int m_YScrollWait = 0;

	int m_PlayerPosX = -1;
	int m_PlayerPosY = -1;
	int m_PlayerSize = 256;
	int m_PlayerDirection = 0;

	int			m_Squares = 64;

	int			m_LayerAreaOffset = 64;
	int			m_LayerAreaHeight = m_LayerAreaOffset + m_Squares;

	int			m_ChipAreaOffset = 32 + m_LayerAreaHeight;						//チップ表示エリアのYオフセット位置
	int			m_ChipAreaWidth = 256;					//チップ表示エリアの幅
	int			m_ChipAreaHeight = m_Squares * CHIPAREA_COUNT + m_ChipAreaOffset;	//チップ表示エリアの高さ
	int			m_XChipSize = 32;						//チップサイズ
	int			m_YChipSize = 32;						//チップサイズ
	int			m_XChipEditorSize = 32;						//チップサイズ
	int			m_YChipEditorSize = 32;						//チップサイズ
	float		m_ChipScale = 1.0f;					//チップスケール
	bool		m_bRhombus = false;						//斜め判定

	int			m_EnemyAreaOffset = 32 + m_ChipAreaHeight;	//敵表示エリアのYオフセット位置
	int			m_EnemyAreaHeight = m_Squares * 2 + m_EnemyAreaOffset;//敵表示エリアの高さ
	int			m_EnemySize = 64;						//敵表示のサイズ
	int			m_EnemyChipSize = 256 ;						//敵表示のサイズ

	int			m_ItemSize = 128;						//アイテム表示のサイズ
	
	int			m_PlayerAreaOffset = 32 + m_EnemyAreaHeight;	//アイテム表示エリアのYオフセット位置
	int			m_PlayerAreaHeight = m_Squares + m_PlayerAreaOffset;	//アイテム表示エリアの高さ

	//int			m_StateOffset = 10 + m_ItemAreaHeight;	//状態表示エリアのYオフセット位置

	int			m_XChipCount = 200;					//マップ横チップ数
	int			m_YChipCount = 25;						//マップ縦チップ数
	int			m_LayerCount = 1;						// レイヤー数
	int			m_Layer = 0;

	int			m_XScroll = 0;						//マップXスクロール
	int			m_YScroll = 0;						//マップYスクロール
	float		m_MapScale = 1.0f;					//マップスケール

	int			m_XSelect = 0;						//マップX選択
	int			m_YSelect = 0;						//マップY選択

	int			m_ChipSelect = -1;						//チップ選択
	int			m_EnemySelect = -1;						//敵選択
	int			m_ItemSelect = -1;						//アイテム選択
	int			m_PlayerSelect = -1;

	float						m_BackScale = 1.0f;
	CTexture					m_BackTexture;
	CTexture					m_ChipTexture;
	CTexture					m_PlayerTexture;

	int*						m_pChipData = NULL;

	CDynamicArray< CTexture* >	m_EnemyTextureArray;		// 敵画像配置
	CDynamicArray< CTexture* >	m_ItemTextureArray;			// アイテム画像配置
	int*		m_pEnemyData = NULL;					// 配置敵データ
	int*		m_pItemData = NULL;					// 配置アイテムデータ
	int*		m_pGimmickData = NULL;


	// 直近数回のチップの種類の配列保持
	int			m_MapchipTypeArray[CHIPAREA_COUNT * 4 - 2];
	int			m_EnemyTypeArray[4];
	int			m_ItemTypeArray = 0;
	int			m_EraseSelect = -1;
	int			m_TabViewSelect = -1;
	bool		m_bTabSelectEnd = false;


	int			m_GimickSelectNo;


	bool m_Check = false;
	bool m_bGrid = true;
	bool m_bGimmickMode = false;
	bool m_bAllView = true;

public:
	CGameEditor();
	~CGameEditor();
	bool Load(void);
	void Initialize(void);
	void Update(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);

	void UpdateMapScroll();
	void RenderFrame();
	void RenderGimmickFrame();

	// エディタ用関数プロトタイプ宣言
	void ReleaseMapData();
	bool OpenFileDialog(HWND hWnd, int mode, const char* Title, const char* Filter, const char* DefExt, char* path);
	bool LoadBackTexture(HWND hWnd);
	bool LoadChipTexture(HWND hWnd);
	bool LoadEnemyTexture(HWND hWnd);
	bool LoadItemTexture(HWND hWnd);
	LRESULT CALLBACK MapStateDlgProc(HWND hWnd, UINT msg, WPARAM wpar, LPARAM lpar);
	bool LoadMapData(int i);
	bool SaveMapData(int i);

	// 18-4, 18-5
	void UpdateLayerCount(int sign);
	void UpdateLayerArea(float mx, float my);
	void UpdateChipArea(float mx, float my);
	void UpdateEnemyArea(float mx, float my);
	void UpdateTabArea(float mx, float my);
	void UpdateChipAdd(float mx, float my);
	void UpdateChipRemove(float mx, float my);
	void UpdateChipCopy(float mx, float my);
	void SelectArea(float mx, float my);
	void UpdatePlayerPosArea(float mx, float my);
	void SelectGimmick(float mx, float my);
	void DeleteGimmick();

	void RenderMapChip(void);
	void RenderTabView(void);
};

