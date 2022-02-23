#pragma once
#include "SceneNo.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "ControlManager.h"
#include "OpponentManager.h"

class CSceneBase
{
private:
protected:
	bool				m_bEnd;					// シーンの終了判定に使用
	SceneNo				m_NextSceneNo;			// 次に遷移するシーンの番号
	int					m_Scene;				// いるかどうか不明
	int					m_StageNo;				// いるかどうか不明
	CTexture			m_BackImage;			// 画像を用意できる気がしない	

	int					m_SelectNo[2];
	float				m_CharacterLife[4] = { 900.0f,1000.0f,600.0f,1200.0f };
	float				m_CharacterEnergy[4] = { 900.0f,1000.0f,600.0f,1200.0f };
	float				m_CharacterSpeed[4] = { 8.5f,7.5f,6.0f,10.0f };

public:
	CSceneBase();
	virtual ~CSceneBase() {};
	virtual void Initialize(void) = 0;
	virtual bool Load(void) = 0;
	virtual void Update(void) = 0;
	virtual void UpdateDebug(void) = 0;
	virtual void Render(void) = 0;
	virtual void RenderDebug(void) = 0;
	virtual void Release(void) = 0;

	SceneNo GetNextScene(void) { return m_NextSceneNo; }
	bool IsEnd(void) { return m_bEnd; }
};