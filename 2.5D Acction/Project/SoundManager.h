#pragma once
#include <Mof.h>

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