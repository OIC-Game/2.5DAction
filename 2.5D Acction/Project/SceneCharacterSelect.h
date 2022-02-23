#pragma once
#include "SceneBase.h"

class CSceneCharacterSelect : public CSceneBase
{
private:
	static const int m_CharacterCount = 4;
	MofU32			m_Color[2] = { MOF_COLOR_RED ,MOF_COLOR_BLUE };
	std::string		m_CharacterName[m_CharacterCount] = { "�A�[�j��", "�����B�\", "JORKER", "�R�c���Y" };
	bool			m_bDecide[2];
	int plus[4] = { 0 , 235 , 470 , 705 };
	float m_LifePos[2] = { 40,522 };


	int		m_SelectVsCpu;

	// ���j���[��ʂɖ߂�Ƃ��Ɋm�F���郁�j���[

	static const int				m_MenuItemCount = 2;
	bool			m_bMenu = false;	// ���j���[�\��
	int				m_MenuSelect = 0; // ���j���[�I��
	int				m_MenuHSpace = 12;
	int				m_MenuVSpace = 8;

	int				m_MenuPlayer = 0;

	std::string		m_MenuTitle = "���j���[��ʂɖ߂�܂����H";
	std::string		m_MenuItem[m_MenuItemCount] = { "�͂�", "������" };

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