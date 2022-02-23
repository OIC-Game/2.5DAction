#pragma once
#include	"BulletBase.h"
class CAnyaOrb : public CBulletBase
{
private:

	float m_Tactics1_Dir[3] = {0,120,240};
	float m_Tactics2_Dir[5] = {15 + 90,65 + 90,115 + 90,165 + 90,270 + 90 };
	float m_Tactics3_Dir[5] = {240 + 90,300 + 90,40 + 90,90 + 90,140 + 90 };
	float m_TacticsSP_Dir[5] = { 0,72,144,216,288 };

	float m_Tactics1_Len[3] = { 50,50,50 };
	float m_Tactics2_Len[5] = { 50,50,50,50,50 };
	float m_Tactics3_Len[5] = { 50,50,50,50,50 };
	float m_TacticsSP_Len[5] = { 55,50,45,40,35 };

	float m_Len;
	float m_GoalLen;
	int m_TacticsNo;
	int m_PhaseNo;
	bool m_Started;

public:
	CAnyaOrb();
	~CAnyaOrb();

	void Initialize(int playerno, int posno);
	void Generation(CCircle player, CCircle enemy);
	void Update(CCircle player, CCircle enemy);
	void Render();
	void Release();
	void Start();
	void End();
	bool GetStarted() { return m_Started; }
	void SetTacticsNo(int no) { m_TacticsNo = no; }
};

