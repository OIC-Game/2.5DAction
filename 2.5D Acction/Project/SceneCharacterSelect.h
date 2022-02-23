#pragma once
#include "SceneBase.h"

class CSceneCharacterSelect : public CSceneBase
{
private:
	static const int m_CharacterCount = 4;
	MofU32			m_Color[2] = { MOF_COLOR_RED ,MOF_COLOR_BLUE };
	std::string		m_CharacterName[m_CharacterCount] = { "アーニャ", "ラヴィ―", "JORKER", "山田太郎" };
	bool			m_bDecide[2];
	int plus[4] = { 0 , 235 , 470 , 705 };
	float m_LifePos[2] = { 40,522 };


	int		m_SelectVsCpu;

	// メニュー画面に戻るときに確認するメニュー

	static const int				m_MenuItemCount = 2;
	bool			m_bMenu = false;	// メニュー表示
	int				m_MenuSelect = 0; // メニュー選択
	int				m_MenuHSpace = 12;
	int				m_MenuVSpace = 8;

	int				m_MenuPlayer = 0;

	std::string		m_MenuTitle = "メニュー画面に戻りますか？";
	std::string		m_MenuItem[m_MenuItemCount] = { "はい", "いいえ" };

	void RetrunMenu();
	void RenderMenu();

	void RenderStatus();
public:
	CSceneCharacterSelect();
	~CSceneCharacterSelect();
	void Initialize(void);
	bool Load(void);
	void Update(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
};