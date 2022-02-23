#pragma once
#include	"SoundManager.h"
#include	"TextureManager.h"
#include	"JokerSkillManager.h"

typedef struct tag_BulletStatus {
	CVector2	Pos;						// 弾の座標
	CVector2	StartPos;					// レーザー弾の始点座標
	CVector2	Move;						// 弾の座標移動量

	float		Radius;						// 弾の大きさ、タイプ0は半径、タイプ1は幅
	float		FirstRadius;				// 大きさが変わる弾の最初の大きさ
	float		MinRadius;					// 大きさが変わる弾の最小の大きさ
	float		MaxRadius;					// 大きさが変わる弾の最大の大きさ

	float		Speed;						// 弾の飛ぶ速度 
	float		FirstSpeed;					// 弾速の変わる弾の最初の速度
	float		MinSpeed;					// 弾速が変わる弾の最低速度
	float		MaxSpeed;					// 弾速が変わる弾の最高速度
	float		GrowSpeed;					// 弾が大きくなる時の速度

	float		Damage;						// 弾が敵に与えるダメージ
	float		FirstDamage;				// 弾速の変わる弾の最初のダメージ
	float		MinDamage;					// ダメージが変わる弾の最少ダメージ
	float		MaxDamage;					// ダメージが変わる弾の最大ダメージ

	float		Dir;						// 弾が飛んでいく方向

	float		GetSkillPoint;				// 弾を相手に当てることで得られるスキルポイント
	float		GiveSkillPoint;				// 弾を相手がグレイズしたときに与えるスキルポイント

	int			PosNo;						// 弾が発射される位置を判断する番号
	int			NotDamageTime;				// 弾が当たっても消えない時の、ダメージがなくなる時間
	int			NotDamageRemTime;			// 弾が当たっても消えない時の、ダメージがなくなる残り時間
	int			PerTime;					// レーザー弾などの持続時間
	int			PerRemTime;					// レーザー弾などの持続残り時間

	bool		bLaser;						// 弾の種類、タイプfalse:円(通常段)かタイプtrue:矩形(レーザー弾)かを判断
	bool		bDrow;						// 弾を描画するかどうか
	bool		bFly;						// 弾を描画した後、飛ばすかどうか
	bool		bDisappear;					// 弾が当たった時に消えるかどうか
	bool		bGrowCollitionGraze;		// 弾がグレイズされたときに大きくなるかどうか
	bool		bHitSE;

	tag_BulletStatus() :
		Pos(0, 0),
		StartPos(0, 0),
		Move(0, 0),
		Radius(0),
		FirstRadius(0),
		MinRadius(0),
		MaxRadius(0),
		Speed(0),
		FirstSpeed(0),
		MinSpeed(0),
		MaxSpeed(0),
		GrowSpeed(0),
		Damage(0),
		FirstDamage(0),
		MinDamage(0),
		MaxDamage(0),
		Dir(0),
		GetSkillPoint(0),
		GiveSkillPoint(0),
		PosNo(0),
		NotDamageTime(0),
		NotDamageRemTime(0),
		PerTime(0),
		PerRemTime(0),
		bLaser(false),
		bDrow(false),
		bFly(false),
		bDisappear(true),
		bGrowCollitionGraze(false),
		bHitSE(true) {
	}
}BulletStatus;

class CBulletBase
{
private:
	float m_Scale;						// 画面のサイズに影響されずに行うための数値
protected:
	float m_Width = 1280;
	float m_Height = 720;

	int m_PlayerNo;						// プレイヤーの番号、番号の異なるプレイヤーと衝突でダメージ	

	BulletStatus m_BStatus;

	void SubInitialize();

	CCircle GetStartPosCircle() {
		return CCircle(
			((m_BStatus.Pos.x > m_BStatus.StartPos.x) ? m_BStatus.StartPos.x + m_BStatus.Radius : m_BStatus.Pos.x + m_BStatus.Radius),
			((m_BStatus.Pos.x > m_BStatus.StartPos.x) ? m_BStatus.StartPos.y : m_BStatus.Pos.y),
			m_BStatus.Radius);
	}

	CCircle GetEndPosCircle() {
		return CCircle(
			((m_BStatus.Pos.x > m_BStatus.StartPos.x) ? m_BStatus.Pos.x : m_BStatus.StartPos.x),
			((m_BStatus.Pos.x > m_BStatus.StartPos.x) ? m_BStatus.Pos.y : m_BStatus.StartPos.y),
			m_BStatus.Radius);
	}

	CRectangle GetRect() {
		return CRectangle(
			((m_BStatus.Pos.x > m_BStatus.StartPos.x) ? m_BStatus.StartPos.x + m_BStatus.Radius : m_BStatus.Pos.x + m_BStatus.Radius),
			((m_BStatus.Pos.x > m_BStatus.StartPos.x) ? m_BStatus.StartPos.y - m_BStatus.Radius : m_BStatus.Pos.y - m_BStatus.Radius),
			((m_BStatus.Pos.x > m_BStatus.StartPos.x) ? m_BStatus.Pos.x : m_BStatus.StartPos.x),
			((m_BStatus.Pos.x > m_BStatus.StartPos.x) ? m_BStatus.StartPos.y + m_BStatus.Radius : m_BStatus.Pos.y + m_BStatus.Radius));
	}

	CCircle GetStartPosRenderCircle() {
		return CCircle(
			((m_BStatus.Pos.x > m_BStatus.StartPos.x) ? m_BStatus.StartPos.x + m_BStatus.Radius : m_BStatus.Pos.x + m_BStatus.Radius) * m_Scale,
			((m_BStatus.Pos.x > m_BStatus.StartPos.x) ? m_BStatus.StartPos.y : m_BStatus.Pos.y) * m_Scale,
			m_BStatus.Radius * m_Scale);
	}

	CCircle GetEndPosRenderCircle() {
		return CCircle(
			((m_BStatus.Pos.x > m_BStatus.StartPos.x) ? m_BStatus.Pos.x : m_BStatus.StartPos.x) * m_Scale,
			((m_BStatus.Pos.x > m_BStatus.StartPos.x) ? m_BStatus.Pos.y : m_BStatus.StartPos.y) * m_Scale,
			m_BStatus.Radius * m_Scale);
	}

	CRectangle GetRenderRect() {
		return CRectangle(
			((m_BStatus.Pos.x > m_BStatus.StartPos.x) ? m_BStatus.StartPos.x + m_BStatus.Radius : m_BStatus.Pos.x + m_BStatus.Radius) * m_Scale,
			((m_BStatus.Pos.x > m_BStatus.StartPos.x) ? m_BStatus.StartPos.y - m_BStatus.Radius : m_BStatus.Pos.y - m_BStatus.Radius) * m_Scale,
			((m_BStatus.Pos.x > m_BStatus.StartPos.x) ? m_BStatus.Pos.x : m_BStatus.StartPos.x) * m_Scale,
			((m_BStatus.Pos.x > m_BStatus.StartPos.x) ? m_BStatus.StartPos.y + m_BStatus.Radius : m_BStatus.Pos.y + m_BStatus.Radius) * m_Scale);
	}
public:
	CBulletBase();
	~CBulletBase();

	virtual void Initialize(int playerno, int posno) = 0;
	virtual void Update(CCircle player, CCircle enemy) = 0;
	virtual void Generation(CCircle player, CCircle enemy) = 0;
	bool Collition(CCircle enemy, CCircle egraze, int& pskill, int& damage, int& eskill);
	virtual void Render() = 0;
	virtual void Release() = 0;

	bool GetDrow() { return m_BStatus.bDrow; }
	bool GetFly() { return m_BStatus.bFly; }
	void SetFly() { m_BStatus.bFly = true; }
	float GetRadius() { return m_BStatus.Radius; }

	CCircle GetCircle() { return CCircle(m_BStatus.Pos.x, m_BStatus.Pos.y, m_BStatus.Radius); }
	CCircle GetRenderCircle() { return CCircle(m_BStatus.Pos.x * m_Scale, m_BStatus.Pos.y * m_Scale, m_BStatus.Radius * m_Scale); }

	const BulletStatus& GetBulletStatus() { return m_BStatus; }
};

