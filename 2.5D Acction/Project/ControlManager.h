#pragma once
#include <Mof.h>

class CControlManager {
private:
	int	m_PlayerNo[4];

	CControlManager() {
		for (int i = 0; i < 4; i++)
		{
			m_PlayerNo[i] = -1;
		}
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