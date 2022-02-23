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
	//カメラ
	CCamera					m_Camera;
	//カメラ位置
	CVector3				m_CPos;
	//カメラ注視点位置
	CVector3				m_TPos;
	//カメラの上方ベクトル
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


	// ポーズ画面のメニュー
	static const int				m_PauseMenuItemCount = 4;
	bool			m_bPauseMenu = false;	// メニュー表示
	int				m_PauseMenuSelect = 0; // メニュー選択
	int				m_MenuHSpace = 12;
	int				m_MenuVSpace = 8;

	int				m_MenuPlayer = 0;

	std::string		m_PauseMenuTitle = "Pause Now! 停止中";
	std::string		m_PauseMenuItem[m_PauseMenuItemCount] = { "ゲームを再開する", "最初からやり直す", "キャラクター選択に戻る", "メニューに戻る" };

	void PauseMenu();
	void RenderPauseMenu();

	// 対戦終了時のメニュー
	static const int				m_GameEndMenuTitleCount = 3;
	static const int				m_GameEndMenuItemCount = 3;
	bool			m_bGameEndMenu = false;	// メニュー表示
	int				m_GameEndMenuSelect = 0; // メニュー選択

	std::string		m_GameEndMenuTitle[m_GameEndMenuTitleCount] = { "Drow ! 引き分けです！" , "1P Win! 1プレイヤーの勝ちです！", "2P Win! 2プレイヤーの勝ちです！"};
	std::string		m_GameEndMenuItem[m_GameEndMenuItemCount] = { "もう一度遊ぶ", "キャラクター選択に戻る", "メニューに戻る"};

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