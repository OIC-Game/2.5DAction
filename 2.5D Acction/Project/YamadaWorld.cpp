#include "YamadaWorld.h"

CYamadaWorld::CYamadaWorld()
{
}

CYamadaWorld::~CYamadaWorld()
{
}

void CYamadaWorld::Initialize(int playerno, int posno) {
	m_PlayerNo = playerno;
	m_BStatus.GetSkillPoint = 10;
	m_BStatus.GiveSkillPoint = 3;
	m_BStatus.MaxSpeed = 15;
	m_BStatus.MaxRadius = 20;
	m_BStatus.MinRadius = 5;
	m_BStatus.PerTime = 600;
	if (m_PlayerNo != 0)
	{
		m_AreaRect = CRectangle(0, 0, m_Width / 16 * 7, (float)m_Height / 8 * 7);
	}
	else
	{
		m_AreaRect = CRectangle(m_Width / 16 * 9, 0, m_Width, m_Height / 8 * 7);
	}
}

void CYamadaWorld::Generation(CCircle player, CCircle enemy) {
	m_GoalRadius = rand() % (int)(m_BStatus.MaxRadius - m_BStatus.MinRadius) + m_BStatus.MinRadius;
	m_BStatus.Pos.x = rand() % (int)(m_AreaRect.Right - m_AreaRect.Left - m_GoalRadius * 2) + m_AreaRect.Left + m_GoalRadius;
	m_BStatus.Pos.y = rand() % (int)(m_AreaRect.Bottom - m_AreaRect.Top - m_GoalRadius * 2) + m_AreaRect.Top + m_GoalRadius;
	m_BStatus.Dir = rand() % 360;
	m_BStatus.GrowSpeed = m_GoalRadius / 20;
	m_BStatus.Damage = m_Attack[rand() % m_AttackCount];
	m_BStatus.PerRemTime = m_BStatus.PerTime;
	m_BStatus.bDrow = true;
	CSoundManager::GetInstance().GetSE(21).Play();
}

void CYamadaWorld::Update(CCircle player, CCircle enemy) {
	if (!m_BStatus.bDrow) { return; }
	int slow = CJokerSkillManager::GetInstance().GetSlow(m_PlayerNo);
	if (m_BStatus.Radius < m_GoalRadius)
	{
		m_BStatus.Radius += m_BStatus.GrowSpeed / slow;
		return;
	}
	m_BStatus.Dir += rand() % 10 - 3;
	m_BStatus.Speed = rand() % (int)m_BStatus.MaxSpeed;
	m_BStatus.Move.x = cos(MOF_ToRadian(m_BStatus.Dir)) * m_BStatus.Speed;
	m_BStatus.Move.y = sin(MOF_ToRadian(m_BStatus.Dir)) * m_BStatus.Speed;

	m_BStatus.Pos.x += m_BStatus.Move.x / slow;
	m_BStatus.Pos.y += m_BStatus.Move.y / slow;
	if (m_BStatus.Pos.x + m_BStatus.Radius > m_AreaRect.Right)
	{
		m_BStatus.Pos.x = m_AreaRect.Right - m_BStatus.Radius;
		if (m_BStatus.Dir > 180)
			m_BStatus.Dir -= 180;
		else
			m_BStatus.Dir += 180;
	}
	if (m_BStatus.Pos.x - m_BStatus.Radius < m_AreaRect.Left)
	{
		m_BStatus.Pos.x = m_AreaRect.Left + m_BStatus.Radius;
		if (m_BStatus.Dir > 180)
			m_BStatus.Dir -= 180;
		else
			m_BStatus.Dir += 180;
	}
	if (m_BStatus.Pos.y + m_BStatus.Radius > m_AreaRect.Bottom)
	{
		m_BStatus.Pos.y = m_AreaRect.Bottom - m_BStatus.Radius;
		if (m_BStatus.Dir > 180)
			m_BStatus.Dir -= 180;
		else
			m_BStatus.Dir += 180;
	}
	if (m_BStatus.Pos.y - m_BStatus.Radius < m_AreaRect.Top)
	{
		m_BStatus.Pos.y = m_AreaRect.Top + m_BStatus.Radius;
		if (m_BStatus.Dir > 180)
			m_BStatus.Dir -= 180;
		else
			m_BStatus.Dir += 180;
	}

	if (m_BStatus.PerRemTime > 0)
	{
		if (CJokerSkillManager::GetInstance().CanMove(m_PlayerNo))
			m_BStatus.PerRemTime--;
	}
	else
	{
		m_BStatus.bDrow = false;
	}
}

void CYamadaWorld::Render() {
	if (!m_BStatus.bDrow) { return; }
	CGraphicsUtilities::RenderCircle(GetRenderCircle(), (m_PlayerNo == 0) ? MOF_COLOR_WHITE : MOF_COLOR_YELLOW);

	float x = CTextureManager::GetInstance().GetCharacter(0).GetWidth();
	float y = CTextureManager::GetInstance().GetCharacter(0).GetHeight();
	float scale = m_BStatus.Radius / max(x, y) * 3;
	x = m_BStatus.Pos.x;
	y = m_BStatus.Pos.y;
	float rot = m_BStatus.PerRemTime % 360;
	CTextureManager::GetInstance().GetCharacter(3).RenderScaleRotate(x, y, scale, MOF_ToRadian(rot),TEXTUREALIGNMENT_CENTERCENTER);
}

void CYamadaWorld::Release() {
}