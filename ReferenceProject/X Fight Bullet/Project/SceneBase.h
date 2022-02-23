#pragma once
#include <Mof.h>
#include "GameDefine.h"
class CSceneBase
{
private:
protected:
	bool				m_bEnd;					// �V�[���̏I������Ɏg�p
	int					m_NextSceneNo;			// ���ɑJ�ڂ���V�[���̔ԍ�
	int					m_Scene;				// ���邩�ǂ����s��
	int					m_StageNo;				// ���邩�ǂ����s��
	CTexture			m_BackImage;			// �摜��p�ӂł���C�����Ȃ�	

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
	virtual void Render(void) = 0;
	virtual void RenderDebug(void) = 0;
	virtual void Release(void) = 0;

	void SetScene(int scene) { m_Scene = scene; }
	int GetScene() { return m_Scene; }
	int GetNextScene(void) { return m_NextSceneNo; }
	int GetSelectNo(int i) { return m_SelectNo[i]; }
	void SetSelectNo(int i, int no) { m_SelectNo[i] = no; }
	bool IsEnd(void) { return m_bEnd; }

};