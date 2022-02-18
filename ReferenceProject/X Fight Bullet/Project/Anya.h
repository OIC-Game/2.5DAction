#pragma once
#include <Mof.h>
#include "Player.h"
#include "AnyaOrb.h"
#include "RipplesShot.h"
#include "RipplesBullet.h"
#include "GrowShot.h"
#include "MachShot.h"
#include "SonicBeam.h"
#include "ExplosionShot.h"
#include "WaveShot.h"
#include "LaserDance.h"
#include "HomingGun.h"

#define ANYAORB1_COUNT 3
#define ANYAORB2_COUNT 5
#define ANYAORB3_COUNT 5
#define ANYAORBSP_COUNT 5
#define RIPPLESSHOT_COUNT 18
#define CHAOSRIPPLESSHOT_COUNT 50
class Anya : public CPlayer
{
private:
	// ステータス
	const float ANYA_LIFE = 900;
	 float ANYA_SKILL = 900;
	const float ANYA_SPEED = 8.5;
	const float ANYA_SECOND_SPEED = 13;
	const float ANYA_THIRD_SPEED = 5;


	CAnyaOrb m_AnyaOrb1[ANYAORB1_COUNT];
	CAnyaOrb m_AnyaOrb2[ANYAORB2_COUNT];
	CAnyaOrb m_AnyaOrb3[ANYAORB3_COUNT];
	CAnyaOrb m_AnyaOrbS[ANYAORBSP_COUNT];

	void AnyaOrbInitialize(CCircle enemy);

#pragma region 弾
	// タクティクスチェンジ
	int m_TacticsNo;
	bool m_TC1Start;
	bool m_TC2Start;
	bool m_TC3Start;
	bool m_TCSPStart;
	bool m_TC1End;
	bool m_TC2End;
	bool m_TC3End;
	bool m_TCSPEnd;

	void TacticsInitialize();
	void TacticsChenge();
	void TacticsStart();
	void Tactics1Start();
	void Tactics2Start();
	void Tactics3Start();
	void TacticsSPStart();
	void Tactics1End();
	void Tactics2End();
	void Tactics3End();
	void TacticsSPEnd();

	void SpeedChenge();

	// リップルショット
	int m_RipplesShotColumn = 3;
	int m_RipplesShotAmount = 6;
	int m_RipplesShotCount;

	CRipplesShot* m_pRipplesShot;
	CRipplesBullet m_RipplesBullet1[RIPPLESSHOT_COUNT][RIPPLESSHOT_COUNT];
	CRipplesBullet m_RipplesBullet2[RIPPLESSHOT_COUNT][RIPPLESSHOT_COUNT];

	int m_RipplesShotNo;
	int m_RipplesShotGap = 40;
	int m_RipplesShotRemGap;

	void RipplesShotInitialize();
	void RipplesShotGeneration();
	void RipplesShotRender();



	// グロウショット
	int m_GrowShotColumn = 3;
	int m_GrowShotAmount = 3;
	int m_GrowShotSetAmount = 4;
	int m_GrowShotCount = 0;

	CGrowShot* m_pGrowShot;
	int m_GrowShotNo;
	const int m_GrowShotFlyNo = 3;
	int m_GrowShotRemFlyNo;
	const int m_GrowShotSetGap = 4;
	int m_GrowShotRemSetGap;
	const int m_GrowShotGap = 30;
	int m_GrowShotRemGap;


	void GrowShotInitialize();
	void GrowShotStart();
	void GrowShotGeneration(CCircle enemy);

	// マッハショット
	int m_MachShotColumn = 3;
	int m_MachShotAmount = 3;
	int m_MachShotSetAmount = 4;
	int m_MachShotCount = 0;

	CMachShot* m_pMachShot;
	int m_MachShotNo;
	const int m_MachShotFlyNo = 3;
	int m_MachShotRemFlyNo;
	const int m_MachShotSetGap = 4;
	int m_MachShotRemSetGap;
	const int m_MachShotGap = 30;
	int m_MachShotRemGap;

	void MachShotInitialize();
	void MachShotStart();
	void MachShotGeneration(CCircle enemy);

	// ソニックビーム
	int m_SonicBeamCount = 4;
	CSonicBeam* m_pSonicBeam;
	int m_SonicBeamNo;
	const int m_SonicBeamGap = 50;
	int m_SonicBeamRemGap;

	void SonicBeamInitialize();
	void SonicBeamGeneration(CCircle enemy);

	// エクスプロージョンショット
	int m_ExplosionShotColumn = 2;
	int m_ExplosionShotAmount = 5;
	int m_ExplosionShotCount = 0;

	CExplosionShot* m_pExplosionShot;
	int m_ExplosionShotNo;
	const int m_ExplosionShotGap = 50;
	int m_ExplosionShotRemGap;

	void ExplosionShotInitialize();
	void ExplosionShotGeneration(CCircle enemy);

	// ウェーブショット
	int m_WaveShotColumn = 2;
	int m_WaveShotAmount = 3;
	int m_WaveShotCount = 0;

	CWaveShot* m_pWaveShot;
	int m_WaveShotNo;
	const int m_WaveShotGap = 60;
	int m_WaveShotRemGap;

	void WaveShotInitialize();
	void WaveShotGeneration(CCircle enemy);

	int m_BeforeTCNo;
	// レーザーダンス
	int m_LaserDanceCount = 5;
	CLaserDance* m_pLaserDance;
	int m_LaserDanceGap = 150;
	int m_LaserDanceRemGap;
	bool m_bLaserDanceNow;
	bool m_bLaserDanceSet;

	void LaserDanceInitialize();
	void LaserDanceEnd();
	void LaserDanceGeneration(CCircle enemy);

	// ホーミングガン
	int m_HomingGunColumn = 5;
	int m_HomingGunAmount = 5;
	int m_HomingGunSetAmount = 8;
	int m_HomingGunCount = 0;

	CHomingGun* m_pHomingGun;
	int m_HomingGunNo;
	int m_HomingGunSetNo;
	int m_HomingGunSetGap = 14;
	int m_HomingGunRemSetGap;
	int m_HomingGunGap = 4;
	int m_HomingGunRemGap;
	bool m_bHomingGunNow;
	bool m_bHomingGunSet;

	void HomingGunInitialize();
	void HomingGunStart();
	void HomingGunGeneration(CCircle enemy);

	// カオスタイム
	int m_ChaosRipplesShotColumn = 5;
	int m_ChaosRipplesShotAmount = 10;
	int m_ChaosRipplesShotCount;

	CRipplesShot* m_pChaosRipplesShot;
	CRipplesBullet m_ChaosRipplesBullet1[CHAOSRIPPLESSHOT_COUNT][CHAOSRIPPLESSHOT_COUNT];
	CRipplesBullet m_ChaosRipplesBullet2[CHAOSRIPPLESSHOT_COUNT][CHAOSRIPPLESSHOT_COUNT];

	int m_ChaosRipplesShotNo;
	const int m_ChaosRipplesShotGap = 15;
	int m_ChaosRipplesShotRemGap;
	bool m_ChaosRipplesShotNow;
	bool m_ChaosRipplesShotSet;

	void ChaosRipplesShotInitialize();
	void ChaosRipplesShotStart();
	void ChaosRipplesShotGeneration(CCircle enemy);
	void ChaosRipplesShotRender();

#pragma endregion

	void TimeReduse();
	void Generation(CCircle enemy);
	void Collision(CCircle enemy, CCircle egraze, int& damage, int& eskill);

public:
	Anya();
	~Anya();
	// ステータスの受け渡し
	float GetLife() { return ANYA_LIFE; }
	float GetSkill() { return ANYA_SKILL; }
	float GetSpeed() { return ANYA_SPEED; }

	void Initialize(CCircle enemy);
	void Update(CCircle enemy);
	void Fly(CCircle enemy);
	void Render();
	void Release();
};

