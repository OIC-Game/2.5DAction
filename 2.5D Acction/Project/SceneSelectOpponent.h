#pragma once
#include "SceneBase.h"

class CSceneSelectOpponent : public CSceneBase
{
private:
	static const int m_MessageCount = 2;
	std::string		m_Message[m_MessageCount] = { "Player VS Player","Player VS CPU" };
public:
	CSceneSelectOpponent();
	~CSceneSelectOpponent();
	void Initialize(void);
	bool Load(void);
	void Update(void);
	void UpdateDebug(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
};

