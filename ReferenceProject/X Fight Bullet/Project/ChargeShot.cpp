#include "ChargeShot.h"

CChargeShot::CChargeShot()
{
}

CChargeShot::~CChargeShot()
{
}

void CChargeShot::Initialize(int playerno, int posno) {
	m_PlayerNo = playerno;
	m_BStatus.FirstDamage = 30;
	m_BStatus.MaxDamage = 160;
	m_BStatus.FirstRadius = 10;
	m_BStatus.MaxRadius = 23;
	m_BStatus.FirstSpeed = 3;
	m_BStatus.MaxSpeed = 30;
	m_BStatus.GetSkillPoint  = 30;
	m_BStatus.GiveSkillPoint  = 15;
	m_BStatus.bDrow = false;
}

void CChargeShot::Generation(CCircle player, CCircle enemy) {
	int slow = CJokerSkillManager::GetInstance().GetSlow(m_PlayerNo);
	if (m_BStatus.bDrow == false)
	{
		m_BStatus.bDrow = true;
		m_BStatus.bFly = false;
		m_BStatus.Radius  = m_BStatus.FirstRadius;
		m_BStatus.Speed = m_BStatus.FirstSpeed;
		m_BStatus.Damage = m_BStatus.FirstDamage;
	}
	m_BStatus.Pos.y = player.y;
	if (m_BStatus.Speed < m_BStatus.MaxSpeed)
		m_BStatus.Speed *= 1 + m_SpeedRate / slow;
	else
		m_BStatus.Speed = m_BStatus.MaxSpeed;
	if (m_BStatus.Damage < m_BStatus.MaxDamage)
		m_BStatus.Damage *= 1 + m_DamageRate / slow;
	else
		m_BStatus.Damage = m_BStatus.MaxDamage;
	if (m_BStatus.Radius  < m_BStatus.MaxRadius)
		m_BStatus.Radius  *= 1 + m_RadiusRate / slow;
	else
	{
		m_BStatus.Radius  = m_BStatus.MaxRadius;
		m_BStatus.Speed = m_BStatus.MaxSpeed;
		m_BStatus.Damage = m_BStatus.MaxDamage;
	}
	m_BStatus.Pos.x = (player.x < enemy.x) ? player.x + player.r + m_BStatus.Radius  : player.x - player.r - m_BStatus.Radius ;
	m_BStatus.Dir = (player.x < enemy.x) ? 0 : 180;
}

void CChargeShot::Update(CCircle player, CCircle enemy) {
	if (!m_BStatus.bDrow) 
	{
		m_BStatus.bFly = false;
		return;
	}
	int slow = CJokerSkillManager::GetInstance().GetSlow(m_PlayerNo);
	if (!m_BStatus.bFly) { return; }
	m_BStatus.Move.x = cos(MOF_ToRadian(m_BStatus.Dir)) * m_BStatus.Speed;
	m_BStatus.Move.y = sin(MOF_ToRadian(m_BStatus.Dir)) * m_BStatus.Speed;

	m_BStatus.Pos.x += m_BStatus.Move.x / slow;
	m_BStatus.Pos.y += m_BStatus.Move.y / slow;

	if (m_BStatus.Pos.y - m_BStatus.Radius  > m_Height / 8 * 7 || m_BStatus.Pos.y + m_BStatus.Radius  < 0 || m_BStatus.Pos.x - m_BStatus.Radius  > m_Width || m_BStatus.Pos.x + m_BStatus.Radius  < 0)
	{
		m_BStatus.bDrow = false;
		m_BStatus.bFly = false;
	}
}

void CChargeShot::Render() {
	if (m_BStatus.bDrow == true)
		CGraphicsUtilities::RenderFillCircle(GetRenderCircle(), (m_PlayerNo == 0) ? MOF_COLOR_WHITE : MOF_COLOR_YELLOW);
}

void CChargeShot::Release() {

}