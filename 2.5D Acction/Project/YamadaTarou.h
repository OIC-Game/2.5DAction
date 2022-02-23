#pragma once
#include "Player.h"
#include "YamadaOrb.h"
#include "YamadaOrbLaunch.h"
#include "YamadaBeam.h"
#include "YamadaBall.h"
#include "YamadaBlizzard.h"
#include "YamadaWorld.h"


class YamadaTarou : public CPlayer
{
private:
	const float YAMADA_LIFE = 1200;
	const float YAMADA_SKILL = 2100;
	const float YAMADA_SPEED = 10;

#pragma region 弾
	// 山田オーブ
	int m_YamadaOrbCount = 150;
	static const int m_YamadaOrbStartPosPaternCount = 5;
	YamadaOrbLaunch YamadaOrbPos;
	CYamadaOrb* m_pYamadaOrb;
	int m_YamadaOrbNo;
	int m_YamadaOrbGap = 5;
	int m_YamadaOrbRemGap;

	void YamadaOrbGeneration(CCircle enemy);
	void YamadaOrbInitialize();

	// 山田ビーム
	CYamadaBeam m_YamadaBeam;
	const int m_YamadaBeamGap = 100;
	int m_YamadaBeamRemGap;
	const int m_YamadaBeamReaction = 8;
	bool m_YamadaBeamNow;

	void YamadaBeamGeneration(CCircle enemy);
	void YamadaBeamInitialize();

	// 山田ボール
	CYamadaBall m_YamadaBall;
	const int m_YamadaBallGap = 120;
	int m_YamadaBallRemGap;

	void YamadaBallInitialize();
	void YamadaBallGeneration(CCircle enemy);

	// 山田吹雪
	int m_YamadaBlizzardCount = 450;
	CYamadaBlizzard* m_pYamadaBlizzard;
	int m_YamadaBlizzardNo;
	const int m_YamadaBlizzardPer = 420;
	int m_YamadaBlizzardRemPer;
	const int m_YamadaBlizzardAllGap = 400;
	int m_YamadaBlizzardAllRemGap;
	const int m_YamadaBlizzardGap = 1;
	int m_YamadaBlizzardRemGap;
	bool m_YamadaBlizzardNow;

	void YamadaBlizzardStart();
	void YamadaBlizzardInitialize();
	void YamadaBlizzardGeneration(CCircle enemy);

	// 山田世界
	int m_YamadaWorldCount = 12;
	CYamadaWorld* m_pYamadaWorld;
	const int m_YamadaWorldPer = 960;
	int m_YamadaWorldRemPer;

	void YamadaWorldInitialize();
	void YamadaWorldGeneration(CCircle enemy);

	// 鼓舞
	// const~
	 int m_TensionPoint = 1;
	 int m_BigTensionPoint = 2;
	 int m_TensionReaction = 6;
	 // ~const
	bool m_TensionUP;
	bool m_BigTensionUP;

	void TensionUP();

#pragma endregion

	//	激しい主張
	float m_AppealGrowSize = 9;
	float m_AppealRemGrowSize;
	int m_AppealGap = 300;
	int m_AppealRemGap;

	void Appeal();

	void TimeReduse();
	void Generation(CCircle enemy);
	void Collision(CCircle enemy, CCircle egraze, int& damage, int& eskill);
	void Reaction();
public:
	YamadaTarou();
	~YamadaTarou();
	// ステータスの受け渡し
	float GetLife() { return YAMADA_LIFE; }
	float GetSkill() { return YAMADA_SKILL; }
	float GetSpeed() { return YAMADA_SPEED; }
	void Initialize(CCircle enemy);
	void Update(CCircle enemy);
	void Fly(CCircle enemy);
	void Render();
	void Release();
};

