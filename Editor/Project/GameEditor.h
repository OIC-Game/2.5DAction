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

	int			m_ChipAreaOffset = 32 + m_LayerAreaHeight;						//�`�b�v�\���G���A��Y�I�t�Z�b�g�ʒu
	int			m_ChipAreaWidth = 256;					//�`�b�v�\���G���A�̕�
	int			m_ChipAreaHeight = m_Squares * CHIPAREA_COUNT + m_ChipAreaOffset;	//�`�b�v�\���G���A�̍���
	int			m_XChipSize = 32;						//�`�b�v�T�C�Y
	int			m_YChipSize = 32;						//�`�b�v�T�C�Y
	int			m_XChipEditorSize = 32;						//�`�b�v�T�C�Y
	int			m_YChipEditorSize = 32;						//�`�b�v�T�C�Y
	float		m_ChipScale = 1.0f;					//�`�b�v�X�P�[��
	bool		m_bRhombus = false;						//�΂ߔ���

	int			m_EnemyAreaOffset = 32 + m_ChipAreaHeight;	//�G�\���G���A��Y�I�t�Z�b�g�ʒu
	int			m_EnemyAreaHeight = m_Squares * 2 + m_EnemyAreaOffset;//�G�\���G���A�̍���
	int			m_EnemySize = 64;						//�G�\���̃T�C�Y
	int			m_EnemyChipSize = 256 ;						//�G�\���̃T�C�Y

	int			m_ItemSize = 128;						//�A�C�e���\���̃T�C�Y
	
	int			m_PlayerAreaOffset = 32 + m_EnemyAreaHeight;	//�A�C�e���\���G���A��Y�I�t�Z�b�g�ʒu
	int			m_PlayerAreaHeight = m_Squares + m_PlayerAreaOffset;	//�A�C�e���\���G���A�̍���

	//int			m_StateOffset = 10 + m_ItemAreaHeight;	//��ԕ\���G���A��Y�I�t�Z�b�g�ʒu

	int			m_XChipCount = 200;					//�}�b�v���`�b�v��
	int			m_YChipCount = 25;						//�}�b�v�c�`�b�v��
	int			m_LayerCount = 1;						// ���C���[��
	int			m_Layer = 0;

	int			m_XScroll = 0;						//�}�b�vX�X�N���[��
	int			m_YScroll = 0;						//�}�b�vY�X�N���[��
	float		m_MapScale = 1.0f;					//�}�b�v�X�P�[��

	int			m_XSelect = 0;						//�}�b�vX�I��
	int			m_YSelect = 0;						//�}�b�vY�I��

	int			m_ChipSelect = -1;						//�`�b�v�I��
	int			m_EnemySelect = -1;						//�G�I��
	int			m_ItemSelect = -1;						//�A�C�e���I��
	int			m_PlayerSelect = -1;

	float						m_BackScale = 1.0f;
	CTexture					m_BackTexture;
	CTexture					m_ChipTexture;
	CTexture					m_PlayerTexture;

	int*						m_pChipData = NULL;

	CDynamicArray< CTexture* >	m_EnemyTextureArray;		// �G�摜�z�u
	CDynamicArray< CTexture* >	m_ItemTextureArray;			// �A�C�e���摜�z�u
	int*		m_pEnemyData = NULL;					// �z�u�G�f�[�^
	int*		m_pItemData = NULL;					// �z�u�A�C�e���f�[�^
	int*		m_pGimmickData = NULL;


	// ���ߐ���̃`�b�v�̎�ނ̔z��ێ�
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

	// �G�f�B�^�p�֐��v���g�^�C�v�錾
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

