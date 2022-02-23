#pragma once
#include <Mof.h>

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