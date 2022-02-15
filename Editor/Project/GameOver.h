#pragma once
#include "ScensBace.h"
#include "GameDefine.h"

class CGameOver : public CScensBace
{
private:
	CSoundBuffer			m_Sound;
public:
	CGameOver();
	~CGameOver();
	void Initialize(void);
	bool Load(void);
	void Update(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);

	bool OpenFileDialog(HWND hWnd, int mode, const char* Title, const char* Filter, const char* DefExt, char* path) { return false; }
	bool LoadBackTexture(HWND hWnd) { return false; }
	bool LoadChipTexture(HWND hWnd) { return false; }
	bool LoadEnemyTexture(HWND hWnd) { return false; }
	bool LoadItemTexture(HWND hWnd) { return false; }
	LRESULT CALLBACK MapStateDlgProc(HWND hWnd, UINT msg, WPARAM wpar, LPARAM lpar) { return FALSE; }
	bool LoadMapData(int i) { return false; }
	bool SaveMapData(int i) { return false; }
};

