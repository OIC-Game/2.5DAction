#pragma once
#include "SceneBase.h"
#include "Player.h"
#include	"Anya.h"
#include	"Lovey.h"
#include	"JOKER.h"
#include	"YamadaTarou.h"

class CSceneBattle : public CSceneBase
{
private:
	//�J����
	CCamera					m_Camera;
	//�J�����ʒu
	CVector3				m_CPos;
	//�J���������_�ʒu
	CVector3				m_TPos;
	//�J�����̏���x�N�g��
	CVector3				m_CUp;

	CVector3				m_Pos[4];
	int						m_MoveNo;

	static const int m_PlayerCount = 2;
	int m_RemCountDown;
	bool m_bLose[m_PlayerCount];
	int  m_EndPattern;
	CPlayer* m_Player[m_PlayerCount] = { NULL,NULL };

	float m_BerWidth = 300;
	float m_BerHeight = 30;
	float m_BerEdgeSize = 2;

	void RenderCountDown();
	void RenderUI();


	// �|�[�Y��ʂ̃��j���[
	static const int				m_PauseMenuItemCount = 4;
	bool			m_bPauseMenu = false;	// ���j���[�\��
	int				m_PauseMenuSelect = 0; // ���j���[�I��
	int				m_MenuHSpace = 12;
	int				m_MenuVSpace = 8;

	int				m_MenuPlayer = 0;

	std::string		m_PauseMenuTitle = "Pause Now! ��~��";
	std::string		m_PauseMenuItem[m_PauseMenuItemCount] = { "�Q�[�����ĊJ����", "�ŏ������蒼��", "�L�����N�^�[�I���ɖ߂�", "���j���[�ɖ߂�" };

	void PauseMenu();
	void RenderPauseMenu();

	// �ΐ�I�����̃��j���[
	static const int				m_GameEndMenuTitleCount = 3;
	static const int				m_GameEndMenuItemCount = 3;
	bool			m_bGameEndMenu = false;	// ���j���[�\��
	int				m_GameEndMenuSelect = 0; // ���j���[�I��

	std::string		m_GameEndMenuTitle[m_GameEndMenuTitleCount] = { "Drow ! ���������ł��I" , "1P Win! 1�v���C���[�̏����ł��I", "2P Win! 2�v���C���[�̏����ł��I"};
	std::string		m_GameEndMenuItem[m_GameEndMenuItemCount] = { "������x�V��", "�L�����N�^�[�I���ɖ߂�", "���j���[�ɖ߂�"};

	void GameEndMenu();
	void RenderGameEndMenu();

public:
	CSceneBattle();
	~CSceneBattle();
	void Initialize(void);
	bool Load(void);
	void Update(void);
	void UpdateDebug(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
};