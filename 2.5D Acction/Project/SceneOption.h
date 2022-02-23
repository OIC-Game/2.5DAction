#pragma once
#include "SceneBase.h"

class CSceneOption : public CSceneBase
{
private:
	static const int m_MessageCount = 8;

	std::string		m_OptionMessage[m_MessageCount] = { "��ʃT�C�Y�ύX","1280 �~ 720","1920 �~ 1080" ,"�t���X�N���[��","BGM����","SE����", "�ۑ����Ȃ��ŏI���", "�ۑ����ďI���" };
	int			m_Width[3] = { 1280,1920,GetSystemMetrics(SM_CXSCREEN) };
	int			m_Height[3] = { 720,1080,GetSystemMetrics(SM_CYSCREEN) };

	int				m_BGMVolume = 0;
	int				m_SEVolume = 0;
	int				m_VolumeCount = 20;
	float			m_VolumeWidth = 200;
public:
	CSceneOption();
	~CSceneOption();
	void Initialize(void);
	bool Load(void);
	void Update(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
};