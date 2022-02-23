#pragma once
#include "GameDefine.h"
#include "Enemy.h"
#include "Item.h"
#include "FireBall.h"


//“–‚½‚è”»’èŒ¸Š•
#define	PLAYER_RECTDECREASE		16
#define PLAYER_SPEED	0.3f
#define PLAYER_MAXSPEED	4.0f
#define PLAYER_MAXDASHSPEED	7.0f
#define PLAYER_JUMP		-9.0f
#define PLAYER_DASHJUMP		-10.0f
#define FIREBALL_COUNT	2
class CPlayer
{
private:
	CTexture					m_Texture;
	CSpriteMotionController		m_Motion;

	CFireBall					m_FireBallArray[FIREBALL_COUNT];

	bool						m_bMove;
	bool						m_bFall;
	bool						m_bDash;
	bool						m_bReverse;
	bool						m_bGoal;

	float						m_PosX;
	float						m_PosY;
	float						m_MoveX;
	float						m_MoveY;

	int							m_HP;
	int							m_DamageWait;
	int							m_StarWait;

	CRectangle					m_SrcRect;

	CSoundBuffer				m_Sound1;
	CSoundBuffer				m_Sound2;
	CSoundBuffer				m_Sound3;

	enum tug_MOTIONNO
	{
		MOTIONNO_SMALL_WAIT,
		MOTIONNO_SMALL_WALK,
		MOTIONNO_SMALL_DASH,
		MOTIONNO_SMALL_DASHMINI,
		MOTIONNO_SMALL_JUMP,
		MOTIONNO_SMALL_FALL,
		MOTIONNO_SMALL_DASHJUMP,
		MOTIONNO_SMALL_DASHTURN,
		MOTIONNO_SMALL_SQUAT,
		MOTIONNO_SMALL_LOOKUP,

		MOTIONNO_BIG_WAIT,
		MOTIONNO_BIG_WALK,
		MOTIONNO_BIG_DASH,
		MOTIONNO_BIG_DASHMINI,
		MOTIONNO_BIG_JUMP,
		MOTIONNO_BIG_FALL,
		MOTIONNO_BIG_DASHJUMP,
		MOTIONNO_BIG_DASHTURN,
		MOTIONNO_BIG_SQUAT,
		MOTIONNO_BIG_LOOKUP,

		MOTIONNO_FLOWER_WAIT,
		MOTIONNO_FLOWER_WALK,
		MOTIONNO_FLOWER_DASH,
		MOTIONNO_FLOWER_DASHMINI,
		MOTIONNO_FLOWER_JUMP,
		MOTIONNO_FLOWER_FALL,
		MOTIONNO_FLOWER_DASHJUMP,
		MOTIONNO_FLOWER_DASHTURN,
		MOTIONNO_FLOWER_SQUAT,
		MOTIONNO_FLOWER_LOOKUP,
		MOTIONNO_FLOWER_FIRE,

		MOTION_COUNT
	};

public:
	CPlayer();
	~CPlayer();

	void Initialize(float x, float y);
	bool Load(void);
	void Update(void);
	void UpdateKey(void);
	void UpdateKey1(void);
	void UpdateKey2(bool pl);
	void Fire(void);
	void UpdateMove(void);
	void ChangeMotions(void);
	void CollisionStage(float ox, float oy, int scno);
	void CollisionStageFireBall(float ox, float oy, int scno, int i);
	bool CollisionEnemy(CEnemy& ene);
	bool CollisionItem(CItem& itm);
	bool IsGoal(void) { return m_bGoal; }
	bool IsDead(void) {
		if (m_HP > 0) { return false; }
		else { return true; }
	}
	void Render(float wx, float wy);
	void RenderDebug(float wx, float wy);
	void Release(void);

	CRectangle GetRect() {
		switch (m_HP)
		{
		case 1:
		{
			switch (m_Motion.GetMotionNo())
			{
			case MOTIONNO_SMALL_SQUAT:
				return { m_PosX + PLAYER_RECTDECREASE,m_PosY + 40,m_PosX + m_SrcRect.GetWidth() - PLAYER_RECTDECREASE,m_PosY + 64 };
				break;
			default:
				return { m_PosX + PLAYER_RECTDECREASE,m_PosY + 32,m_PosX + m_SrcRect.GetWidth() - PLAYER_RECTDECREASE,m_PosY + 64 };
				break;
			}
			break;
		}
		case 2:
		case 3:
			switch (m_Motion.GetMotionNo())
			{
			case MOTIONNO_BIG_SQUAT:
			case MOTIONNO_FLOWER_SQUAT:
				return { m_PosX + PLAYER_RECTDECREASE,m_PosY + 32,m_PosX + m_SrcRect.GetWidth() - PLAYER_RECTDECREASE,m_PosY + 64 };
				break;
			default:
				return { m_PosX + PLAYER_RECTDECREASE,m_PosY + 16,m_PosX + m_SrcRect.GetWidth() - PLAYER_RECTDECREASE,m_PosY + 64 };
				break;
			}
			break;
		default:
			break;
		}
	}
	CRectangle GetBRect() { return { m_PosX + PLAYER_RECTDECREASE,m_PosY + 56,m_PosX + m_SrcRect.GetWidth() - PLAYER_RECTDECREASE,m_PosY + 64 }; }

	float GetMoveY() { return m_MoveY; }
	int GetHP() { return m_HP; }

	int GetFireCount() { return FIREBALL_COUNT; }
	CRectangle GetFireRect(int i) { return m_FireBallArray[i].GetRect(); }

	bool GetFireBallShow(int i) { return m_FireBallArray[i].GetShow(); }

	int GetStarWait() { return m_StarWait; }
};

