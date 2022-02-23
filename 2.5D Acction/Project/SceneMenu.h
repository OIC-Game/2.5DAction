#pragma once
#include "SceneBase.h"

class CSceneMenu : public CSceneBase
{
private:

	static const int m_MessageCount = 3;
	std::string		m_MenuMessage[m_MessageCount] = { "�ΐ탂�[�h" ,"�I�v�V����" ,"�^�C�g���ɖ߂�" };

public:
	CSceneMenu();
	~CSceneMenu();
	void Initialize(void);
	bool Load(void);
	void Update(void);
	void UpdateDebug(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
};