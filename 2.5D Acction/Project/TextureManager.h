#pragma once
#include <Mof.h>

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