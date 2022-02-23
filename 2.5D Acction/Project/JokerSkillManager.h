#pragma once
#include <Mobsync.h>

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