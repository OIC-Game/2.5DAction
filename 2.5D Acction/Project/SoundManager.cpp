#include "SoundManager.h"

void CSoundManager::LoadBGM() {
	FILE* fp = fopen("BGM SE/Bgm SE.txt", "rb");
	if (fp)
	{
		fseek(fp, 0, SEEK_END);
		long fSize = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		//ファイルサイズ分だけのメモリを確保する
		char* pBuffer = (char*)malloc(fSize + 1);
		//ファイルを全てバッファに読み込む
		fSize = fread(pBuffer, 1, fSize, fp);
		pBuffer[fSize] = '\0';
		char* pstr;

		pstr = strtok(pBuffer, ",");

		int cnt = atoi(pstr);
		pstr = strtok(NULL, ",");

		for (int i = 0; i < cnt; i++)
		{
			Bgm.push_back(CSoundBuffer());
			std::string name = pstr;
			name = "BGM SE/" + name + ".mp3";
			Bgm[i].Load(name.c_str());
			pstr = strtok(NULL, ",");
		}

		cnt = atoi(pstr);
		pstr = strtok(NULL, ",");

		for (int i = 0; i < cnt; i++)
		{
			SE.push_back(CSoundBuffer());
			std::string name = pstr;
			name = "BGM SE/" + name + ".mp3";
			SE[i].Load(name.c_str());
			pstr = strtok(NULL, ",");
		}

		fclose(fp);
		free(pBuffer);
	}
}

void CSoundManager::BGMStop(int no) {
	for (int i = 0; i < Bgm.size(); i++)
	{
		if (i == no) { continue; }
		Bgm[i].Stop();
	}
}

void CSoundManager::BGMPlay(int no) {
	if (!Bgm[no].IsPlay())
	{
		Bgm[no].Play();
	}
}
