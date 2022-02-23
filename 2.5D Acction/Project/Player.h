#pragma once
#include	<Mof.h>
#include	"SceneBase.h"

typedef struct tag_PlayerStatus {

	tag_PlayerStatus()	{
	}
}PlayerStatus;

class CPlayer
{
private:
	float m_Scale;
protected:
	float m_Width = 1280;
	float m_Height = 720;

	const float m_FistRadius = 21;
	const float m_FirstGraysRadius = 34;

	int m_PlayerNo;
	CVector2 m_Pos;
	CVector2 m_Move;
	float m_Radius ;
	float m_GrazeRadius;
	float m_Life,m_MaxLife;
	float m_Skill,m_MaxSkill;
	float m_Speed;

	bool m_bLose;

	CRectangle m_AreaRect;
	
public:
	CPlayer();
	~CPlayer();

	void PosInitialize(int no);
	virtual void Initialize(CCircle enemy) = 0;
	virtual void Update(CCircle enemy) = 0;
	virtual void Collision(CCircle enemy, CCircle egraze, int& damage, int& eskill) = 0;
	virtual void Fly(CCircle enemy) = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;

	void UpdateMove();

	float GetMaxLife() { return m_MaxLife; }
	float GetSpeed() { return m_Speed; }
	// 対戦モードのプログラム

	float GetLifePercent() { return m_Life / m_MaxLife; }
	float GetSkillPercent() { return m_Skill / m_MaxSkill; }

	void Damage(int damage, int skill);
	bool GetLose() { return m_bLose; }

	CRectangle GetLine() { return m_AreaRect; }

	CCircle GetCircle() { return CCircle(m_Pos.x, m_Pos.y, m_Radius ); }
	CCircle GetGrazeCircle() { return CCircle(m_Pos.x, m_Pos.y, m_GrazeRadius); }
	CCircle GetRenderCircle() { return CCircle(m_Pos.x * m_Scale, m_Pos.y * m_Scale, m_Radius  * m_Scale); }
	CCircle GetRenderGrazeCircle() { return CCircle(m_Pos.x * m_Scale, m_Pos.y * m_Scale, m_GrazeRadius * m_Scale); }
};

