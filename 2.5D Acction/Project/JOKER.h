#pragma once
#include "Player.h"
#include "TrickGun.h"
#include "DoubtRing.h"

class JOKER : public CPlayer
{
private:
	const float JOKER_LIFE = 600;
	const float JOKER_SKILL = 1200;
	const float JOKER_SPEED = 6;

	// トリックガン
	int m_TrickGunAmount = 3;
	int m_TrickGunSetAmount = 5;
	int m_TrickGun2DivisionAmount = 4;
	int m_TrickGun3DivisionAmount = 4;
	int m_TrickGunLastDivisionAmount = 8;
	int m_TrickGunFirstCount = 0;
	int m_TrickGun2Count = 0;
	int m_TrickGun3Count = 0;
	int m_TrickGunLastCount = 0;

	CTrickGun* m_pTrickGunFirst;
	CTrickGun* m_pTrickGun2;
	CTrickGun* m_pTrickGun3;
	CTrickGun* m_pTrickGunLast;

	const int m_TrickGunFirstGap = 5;
	int m_TrickGunFirstRemGap;
	const int m_TrickGunFirstSetGap = 45;
	int m_TrickGunFirstRemSetGap;
	int m_TrickGunFirstNo;
	int m_TrickGunFirstSetNo;
	int m_TrickGun2No;
	int m_TrickGun3No;
	int m_TrickGunLastNo;

	void TGInitialize();
	void TGFGeneration(CCircle enemy);
	void TGGeneration();
	void TGDivision(int p,CCircle cir1, CCircle cir2, int cn1, int cn2);

	// ダウトリング
	int m_DoubtRingCount = 3;
	CDoubtRing* m_pDoubtRing;
	int m_DoubtRingNo;
	int m_DoubtRingGap = 180;
	int m_DoubtRingRemGap;

	void DoubtRingInitialize();
	void DoubtRingGeneration(CCircle enemy);

	// テレポート
	float m_Teleport = 100;
	float m_HyperTeleport = 200;
	float m_TelGap = 60;
	float m_RemTelGap;
	float m_TeleportEnergy = 25;
	float m_HyperTeleportEnergy = 60;

	void Teleport();

	//
	int m_HealGap = 120;
	int m_RemHealGap;
	void Heal();

	//
	int m_InvTime = 300;
	int m_InvGap = 660;
	int m_RemInvGap;

	void Inversion();

	int m_SlowMagni = 3;
	int m_SlowTime = 300;
	int m_SlowGap = 660;
	int m_RemSlowGap;

	void Slow();

	void TimeReduse();
	void Generation(CCircle enemy);
	void Collision(CCircle enemy, CCircle egraze, int& damage, int& eskill);
	

public:
	JOKER();
	~JOKER();
	// ステータスの受け渡し
	float GetLife() { return JOKER_LIFE; }
	float GetSkill() { return JOKER_SKILL; }
	float GetSpeed() { return JOKER_SPEED; }

	//int GetSlow() { return m_Slow; }
	//int GetInversion() { return m_Inv; }

	void Initialize(CCircle enemy);
	void Update(CCircle enemy);
	void Fly(CCircle enemy);
	void Render();
	void Release();
};

