#include "JokerSkillManager.h"

void CJokerSkillManager::Initialize() {
	for (int i = 0; i < 2; i++)
	{
		SlowTime[i] = 0;
		InverTime[i] = 0;
	}
}

void CJokerSkillManager::Update() {
	for (int i = 0; i < 2; i++)
	{
		SlowTime[i] = max(SlowTime[i] - 1, 0);
		InverTime[i] = max(InverTime[i] - 1, 0);
	}
}

int CJokerSkillManager::GetSlow(int pno) {
	for (int i = 0; i < 2; i++)
	{
		if (i == pno) { continue; }
		if (SlowTime[i] > 0)
		{
			return SlowMagni[i];
		}
	}
	return 1;
}

void CJokerSkillManager::StartSlow(int pno, int slowmag, int time) {
	SlowMagni[pno] = slowmag;
	SlowTime[pno] = time;
}

bool CJokerSkillManager::CanMove(int pno) {
	for (int i = 0; i < 2; i++)
	{
		if (i == pno) { continue; }
		if (SlowTime[i] % SlowMagni[i] == 0)
		{
			return true;
		}
	}
	return false;
}

int CJokerSkillManager::GetInver(int pno) {
	for (int i = 0; i < 2; i++)
	{
		if (i == pno) { continue; }
		if (InverTime[i] > 0)
		{
			return -1;
		}
	}
	return 1;
}

void CJokerSkillManager::StartInver(int pno, int time) {
	InverTime[pno] = time;
}