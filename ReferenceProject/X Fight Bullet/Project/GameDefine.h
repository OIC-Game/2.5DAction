#pragma once
#include <Mof.h>

enum tag_SCENENO
{
	SCENENO_TITLE,
	SCENENO_MENU,
	SCENENO_OPPOENT,
	SCENENO_CHARACTERSELECT,
	SCENENO_BATTLE,
	SCENENO_OPTION,

	SCENENO_COUNT
};

class CScalingManager {
private:
	float Scale;
	CScalingManager() :
		Scale(0) {
	}
public:
	static CScalingManager& GetInstance() {
		static CScalingManager obj;
		return obj;
	}

	float GetScale() { return Scale; }
	void SetScale(float s) { Scale = s; }
};

class CControlManager {
private:
	int	m_PlayerNo[2];

	CControlManager() {
		m_PlayerNo[0] = -1;
		m_PlayerNo[1] = -1;
	}
public:
	static CControlManager& GetInstance()
	{
		static CControlManager obj;
		return obj;
	}

	void SetNo(int pno, int no) {
		m_PlayerNo[pno] = no;
	}
	int GetNo(int pno) {
		return m_PlayerNo[pno];
	}

};

class COpponentManager {
private:
	bool bVsCpu;

	COpponentManager() :
		bVsCpu(false)
	{
	}

public:
	static COpponentManager& GetInstance()
	{
		static COpponentManager obj;
		return obj;
	}
	bool GetOpponent() { return bVsCpu; }
	void SetOpponent(bool op) { bVsCpu = op; }
};

class CJokerSkillManager {
private:
	// éûä‘å∏ë¨î\óÕ
	int SlowTime[2];
	int SlowMagni[2];

	// ëÄçÏîΩì]î\óÕ
	int InverTime[2];

	CJokerSkillManager() {
		SlowTime[0] = 0;
		SlowTime[1] = 0;
		SlowMagni[0] = 1;
		SlowMagni[1] = 1;
		InverTime[0] = 0;
		InverTime[1] = 0;
	}

public:
	static CJokerSkillManager& GetInstance()
	{
		static CJokerSkillManager obj;
		return obj;
	}

	void Initialize();
	void Update();
	int GetSlow(int pno);
	void StartSlow(int pno, int slowmag, int time);
	bool CanMove(int pno);
	int GetInver(int pno);
	void StartInver(int pno, int time);
};

class CInputManager {
private:
	CXGamePad pad[4];

	typedef struct tag_Key {
		float Horizontal;
		float Vertical;

		bool now[10];
		bool prev[10];

		tag_Key() {
			Horizontal = 0;
			Vertical = 0;
			for (int i = 0; i < 10; i++)
			{
				now[i] = false;
				prev[i] = false;
			}
		}
	}Key;

	typedef struct tag_SelectNo {
		int					m_RemainVerticalGap;
		int					m_RemainHorizontalGap;
		int					m_ContinuousVerticalCount;
		int					m_ContinuousHorizontalCount;

		tag_SelectNo() {
			m_RemainVerticalGap = 0;
			m_RemainHorizontalGap = 0;
			m_ContinuousVerticalCount = 0;
			m_ContinuousHorizontalCount = 0;
		};
	}SelectNo;
	int					m_SelectGap[3] = { 25,15,5 };

	Key key[6];
	SelectNo			m_Select[6];

	int	CPUTime;

	CInputManager() :
		key(),
		m_Select(),
		CPUTime(0)
	{
		XGAMEPADCREATEINFO cinfo;
		for (int i = 0; i < 4; i++)
		{
			cinfo.No = i;
			pad[i].Create(&cinfo);
		}
	}
public:
	float GetHorizontal(int i) {
		if (i < 0 || i > 5)
			return 0.0f;
		return key[i].Horizontal;
	}

	float GetVertical(int i) {
		if (i < 0 || i > 5)
			return 0.0f;
		return key[i].Vertical;
	}

	bool GetHold(int i, int btnno) {
		if (i < 0 || i > 5)
			return false;
		return key[i].now[btnno];
	}

	bool GetPush(int i, int btnno) {
		if (i < 0 || i > 5)
			return false;
		return !key[i].prev[btnno] && key[i].now[btnno];
	}

	bool GetPull(int i, int btnno) {
		if (i < 0 || i > 5)
			return false;
		return key[i].prev[btnno] && !key[i].now[btnno];
	}

	void SelectVertical(int p, int& no, int count, int min, bool loop = true);

	void SelectHorizontal(int p, int& no, int count, int min, bool loop = true);

	void Refresh();

	static CInputManager& GetInstance()
	{
		static CInputManager obj;
		return obj;
	}
};

class CSoundManager {
private:
	std::vector<CSoundBuffer> Bgm;
	std::vector<CSoundBuffer> SE;
	float BGMVolume = 1;
	float SEVolume = 1;

	CSoundManager() {
		LoadBGM();
		LoadVolume();
	}

	void LoadBGM();

public:
	CSoundBuffer& GetBGM(int i)
	{
		return Bgm[i];
	}

	CSoundBuffer& GetSE(int i)
	{
		return SE[i];
	}

	void BGMStop(int no = -1);

	void BGMPlay(int no);

	float GetBGMVolume() {
		return BGMVolume;
	}

	float GetSEVolume() {
		return SEVolume;
	}

	void SetBGMVolume(float vol) {
		if (vol < 0)
			vol = 0;
		if (vol > 1)
			vol = 1;
		BGMVolume = vol;
		for (int i = 0; i < Bgm.size(); i++)
		{
			Bgm[i].SetVolume(BGMVolume);
		}
	}

	void SetSEVolume(float vol) {
		if (vol < 0)
			vol = 0;
		if (vol > 1)
			vol = 1;
		SEVolume = vol;
		for (int i = 0; i < SE.size(); i++)
		{
			SE[i].SetVolume(SEVolume);
		}
	}

	void SaveVolume() {
		FILE* fp = fopen("BGM SE/Volume.dat", "wb");
		if (fp)
		{
			fwrite(&BGMVolume, sizeof(float), 1, fp);
			fwrite(&SEVolume, sizeof(float), 1, fp);
			fclose(fp);
		}
		SetBGMVolume(BGMVolume);
		SetSEVolume(SEVolume);
	}

	void LoadVolume() {
		FILE* fp = fopen("BGM SE/Volume.dat", "rb");
		if (fp)
		{
			fread(&BGMVolume, sizeof(float), 1, fp);
			fread(&SEVolume, sizeof(float), 1, fp);
			fclose(fp);
		}
		SetBGMVolume(BGMVolume);
		SetSEVolume(SEVolume);
	}

	void Release()
	{
		for (int i = 0; i < Bgm.size(); i++)
		{
			Bgm[i].Release();
		}
		for (int i = 0; i < SE.size(); i++)
		{
			SE[i].Release();
		}
	}

	static CSoundManager& GetInstance()
	{
		static CSoundManager obj;
		return obj;
	}
};

class CTextureManager {

private:
	std::vector<CTexture> Icon;
	std::vector<CTexture> Character;

	CTextureManager() {
		LoadTexture();
	}

	void LoadTexture();

public:
	static CTextureManager& GetInstance()
	{
		static CTextureManager obj;
		return obj;
	}

	CTexture GetIcon(int no) { return Icon[no]; }
	CTexture GetCharacter(int no) { return Character[no]; }

	void Release() {
		for (int i = 0; i < Icon.size(); i++)
		{
			Icon[i].Release();
		}
		for (int i = 0; i < Character.size(); i++)
		{
			Character[i].Release();
		}
	}
};