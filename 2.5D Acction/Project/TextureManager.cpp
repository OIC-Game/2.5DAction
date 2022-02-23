#include "TextureManager.h"

void CTextureManager::LoadTexture() {
	FILE* fp = fopen("Character/CharacterTexture.txt", "rb");
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
			Icon.push_back(CTexture());
			std::string iname = pstr;
			iname = "Character/" + iname + ".png";
			Icon[i].Load(iname.c_str());
			pstr = strtok(NULL, ",");
			Character.push_back(CTexture());
			std::string cname = pstr;
			cname = "Character/" + cname + ".png";
			Character[i].Load(cname.c_str());
			pstr = strtok(NULL, ",");
		}

		fclose(fp);
		free(pBuffer);
	}
}