#include "Player.h"



CPlayer::CPlayer() :
	m_Pos(0, 0),
	m_Move(0, 0),
	m_Radius(20),
	m_AreaRect()
{
	m_Scale = g_pGraphics->GetTargetHeight();
	m_Scale /= 720;
}


CPlayer::~CPlayer()
{
}

void CPlayer::PosInitialize(int no) {
	m_PlayerNo = no;
	m_Pos.x = (m_PlayerNo == 0) ? m_Width / 32 * 7 : m_Width / 32 * 25;
	m_Pos.y = m_Height / 16 * 7;


	m_Radius = m_FistRadius;
	m_GrazeRadius = m_FirstGraysRadius;

	m_bLose = false;
	if (m_PlayerNo == 0)
	{
		m_AreaRect = CRectangle(0, 0, m_Width / 16 * 7, m_Height / 8 * 7);
	}
	else
	{
		m_AreaRect = CRectangle(m_Width / 16 * 9, 0, m_Width, m_Height / 8 * 7);
	}
}

void CPlayer::UpdateMove() {
	int inv = CJokerSkillManager::GetInstance().GetInver(m_PlayerNo);
	int slow = CJokerSkillManager::GetInstance().GetSlow(m_PlayerNo);
	m_Pos.x += m_Move.x * inv / slow;
	m_Pos.y -= m_Move.y * inv / slow;

	if (m_Pos.x - m_Radius < m_AreaRect.Left)
	{
		m_Pos.x = m_AreaRect.Left + m_Radius;
	}
	else if (m_Pos.x + m_Radius > m_AreaRect.Right)
	{
		m_Pos.x = m_AreaRect.Right - m_Radius;
	}
	if (m_Pos.y - m_Radius < m_AreaRect.Top)
	{
		m_Pos.y = m_AreaRect.Top + m_Radius;
	}
	else if (m_Pos.y + m_Radius > m_AreaRect.Bottom)
	{
		m_Pos.y = m_AreaRect.Bottom - m_Radius;
	}

	m_Move.x = 0;
	m_Move.y = 0;
	int pno = CControlManager::GetInstance().GetNo(m_PlayerNo);
	if (CInputManager::GetInstance().GetHorizontal(pno) > 0.1875)
	{
		m_Move.x = CInputManager::GetInstance().GetHorizontal(pno) * m_Speed;
	}
	if (CInputManager::GetInstance().GetHorizontal(pno) < -0.1875)
	{
		m_Move.x = CInputManager::GetInstance().GetHorizontal(pno) * m_Speed;
	}
	if (CInputManager::GetInstance().GetVertical(pno) > 0.1875)
	{
		m_Move.y = CInputManager::GetInstance().GetVertical(pno) * m_Speed;
	}
	if (CInputManager::GetInstance().GetVertical(pno) < -0.1875)
	{
		m_Move.y = CInputManager::GetInstance().GetVertical(pno) * m_Speed;
	}
}

void CPlayer::Damage(int damage, int skill) {
	m_Life -= damage;
	if (m_Life <= 0)
	{
		m_Life = 0;
		m_bLose = true;
	}
	m_Skill += skill;
	if (m_Skill >= m_MaxSkill)
		m_Skill = m_MaxSkill;
}