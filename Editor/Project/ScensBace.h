#pragma once
#include <Mof.h>

class CScensBace
{
protected:
	bool				m_bEnd;
	int					m_NextScene;
	int					m_Scene;
	int					m_StageNo;
	CTexture			m_BackImage;
public:
	CScensBace() :
		m_bEnd(false),
		m_NextScene(0) {
	}
	virtual ~CScensBace() {};
	virtual void Initialize(void) = 0;
	virtual bool Load(void) = 0;
	virtual void Update(void) = 0;
	virtual void Render(void) = 0;
	virtual void RenderDebug(void) = 0;
	virtual void Release(void) = 0;
	virtual bool OpenFileDialog(HWND hWnd, int mode, const char* Title, const char* Filter, const char* DefExt, char* path) = 0;
	virtual bool LoadBackTexture(HWND hWnd) = 0;
	virtual bool LoadChipTexture(HWND hWnd) = 0;
	virtual bool LoadEnemyTexture(HWND hWnd) = 0;
	virtual bool LoadItemTexture(HWND hWnd) = 0;
	virtual LRESULT CALLBACK MapStateDlgProc(HWND hWnd, UINT msg, WPARAM wpar, LPARAM lpar) = 0;
	virtual bool LoadMapData(int i) = 0;
	virtual bool SaveMapData(int i) = 0;
	void SetScene(int scene) { m_Scene = scene; }
	int GetScene() { return m_Scene; }
	int GetNextScene(void) { return m_NextScene; }
	int GetStageNo() { return m_StageNo; }
	int SetStageNo(int i) { return m_StageNo = i; }
	bool IsEnd(void) { return m_bEnd; }
};

