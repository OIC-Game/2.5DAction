#pragma once
#include "Player.h"
#include "ChargeShot.h"
#include "MachineGun.h"
#include "ChargeLaser.h"
#include "ContinuousenEnergyShot.h"
#include "HomingShot.h"

class Lovey : public CPlayer
{
private:
	float LOVEY_LIFE = 1000;
	float LOVEY_SKILL = 960;
	float LOVEY_SPEED = 7.5;

#pragma region 弾
	// マシンガン
	int m_MachineGunColumn = 2;
	int m_MachineGunAmount = 6;
	int m_MachineGunSetAmount = 4;
	int m_MachineGunCount = 0;

	CMachineGun* m_pMachineGun;
	int m_MachineGunNo;
	int m_MachineGunSetNo;
	int m_MachineGunGap = 3;
	int m_MachineGunRemGap;
	int m_MachineGunAllGap = 17;
	int m_MachineGunAllRemGap;

	void MachineGunInitialize();
	void MachineGunGenerasion(CCircle enemy);

	// チャージショット
	int m_ChargeShotCount = 4;

	CChargeShot* m_pChargeShot;
	int m_ChargeShotNo;
	const int m_ChargeShotGap = 15;
	int m_ChargeShotRemGap;
	bool m_bChargeShotHold = false;
	
	void ChargeShotInitialize();
	void ChargeShotGenerasion(CCircle enemy);

	// チャージレーザー
	CChargeLaser m_ChargeLaser;
	int m_ChargeLaserGap = 120;
	int m_ChargeLaserRemGap;

	void ChargeLaserInitialize();
	void ChargeLaserGenerasion(CCircle enemy);

	// 連続エネルギーショット

	int m_ContinuousenEnergyShotAmount = 4;
	int m_ContinuousenEnergyShotSetAmount = 12;
	int m_ContinuousenEnergyShotCount;
	CContinuousenEnergyShot* m_pContinuousenEnergyShot;
	int m_ContinuousenEnergyShotNo;
	int m_ContinuousenEnergyShotSetNo;
	const int m_ContinuousenEnergyShotAllGap = 400;
	int m_ContinuousenEnergyShotAllRemGap;
	const int m_ContinuousenEnergyShotSetGap = 7;
	int m_ContinuousenEnergyShotSetRemGap;
	const int m_ContinuousenEnergyShotGap = 1;
	int m_ContinuousenEnergyShotRemGap;
	bool m_bContinuousenEnergyShotNow;

	void ContinuousenEnergyShotStart();
	void ContinuousenEnergyShotGeneration(CCircle enemy);
	void ContinuousenEnergyShotInitialize();

	// ホーミング弾
	int m_HomingShotColumn = 3;
	int m_HomingShotAmount = 5;
	int m_HomingShotCount = 0;

	CHomingShot* m_pHomingShot;
	int m_HomingShotNo;
	int m_HomingShotGap = 40;
	int m_HomingShotRemGap;
	bool m_bHomingShotNow;

	void HomingShotInitialize();
	void HomingShotStart();
	void HomingShotGeneration(CCircle enemy);

	// ブーストダッシュ
	int m_BoostDashNo;
	int m_BoostDashSpeed = 3.5;
	float m_BoostDashSize = 3;
	int m_SuperBoostDashSpeed = 7.5;
	float m_SuperBoostDashSize = 5;
	float m_BoostDashEnergy = 0.5;
	float m_SuperBoostDashEnergy = 1;

	void BoostDash();
#pragma endregion

	void TimeReduse();
	void Generasion(CCircle enemy);
	void Collision(CCircle enemy, CCircle egraze, int& damage, int& eskill);

public:
	Lovey();
	~Lovey();
	//
	void Initialize(CCircle enemy);
	void Update(CCircle enemy);
	void Fly(CCircle enemy);
	void Render();
	void Release();
	int GetBoostDashNo() { return m_BoostDashNo; }
	// ステータスの受け渡し
	float GetLife() { return LOVEY_LIFE; }
	float GetSkill() { return LOVEY_SKILL; }
	float GetSpeed() { return LOVEY_SPEED; }
};

