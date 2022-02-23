#include "TrickGun.h"



CTrickGun::CTrickGun()
{
}


CTrickGun::~CTrickGun()
{
}

void CTrickGun::Initialize(int playerno, int posno) {
	m_PlayerNo = playerno;
	m_BStatus.PosNo = posno;
	m_BStatus.Damage = m_DamagePatern[m_BStatus.PosNo];
	m_BStatus.Speed = m_SpeedPatern[m_BStatus.PosNo];
	m_BStatus.Radius  = 4;
	m_BStatus.GetSkillPoint  = 8;
	m_BStatus.GiveSkillPoint  = 2;
	m_RingNo1 = -1;
	m_RingNo2 = -1;
}

void CTrickGun::DivisionGeneration(CCircle player, int posno) {
	m_BStatus.bDrow = true;
	m_BStatus.Pos.x = player.x;
	m_BStatus.Pos.y = player.y;
	m_ReflectionNo = 4;
	if (m_BStatus.PosNo == 1 || m_BStatus.PosNo == 2)
	{
		posno %= 4;
		m_BStatus.Dir = m_DirPatern[posno];
	}
	else if (m_BStatus.PosNo == 3)
	{
		posno %= 8;
		m_BStatus.Dir = m_DirPatern[posno];
	}
}

void CTrickGun::Generation(CCircle player, CCircle enemy) {
	m_BStatus.bDrow = true;
	m_BStatus.Pos.y = player.y;
	m_BStatus.Pos.x = (player.x < enemy.x) ? player.x + player.r - m_BStatus.Radius  : player.x - player.r + m_BStatus.Radius ;
	m_ReflectionNo = 0;
	m_BStatus.Dir = (player.x < enemy.x) ? 0 : 180;
}

void CTrickGun::SetRingNo(int p,int rn1, int rn2) {
	if (p == 1)
		m_RingNo1 = rn1;
	else if (p == 2)
	{
		m_RingNo1 = rn1;
		m_RingNo2 = rn2;
	}
}

void CTrickGun::Update(CCircle player, CCircle enemy) {
	if (!m_BStatus.bDrow) { return; }
	float w = m_Width;
	float h = m_Height;
	int slow = CJokerSkillManager::GetInstance().GetSlow(m_PlayerNo);

	m_BStatus.Move.x = cos(MOF_ToRadian(m_BStatus.Dir)) * m_BStatus.Speed;
	m_BStatus.Move.y = sin(MOF_ToRadian(m_BStatus.Dir)) * m_BStatus.Speed;

	m_BStatus.Pos.x += m_BStatus.Move.x / slow;
	m_BStatus.Pos.y += m_BStatus.Move.y / slow;
	if (m_ReflectionNo > 0)
	{
		if (m_BStatus.Pos.x < m_BStatus.Radius )
		{
			m_ReflectionNo--;
			m_BStatus.Pos.x = m_BStatus.Radius ;
			m_BStatus.Dir = (m_BStatus.Dir == 180) ? 0 : 180 - m_BStatus.Dir;
		}
		else if (m_BStatus.Pos.x > w - m_BStatus.Radius )
		{
			m_ReflectionNo--;
			m_BStatus.Pos.x = w - m_BStatus.Radius ;
			m_BStatus.Dir = (m_BStatus.Dir == 0) ? 180 : 180 - m_BStatus.Dir;
		}
		else if (m_BStatus.Pos.y < m_BStatus.Radius )
		{
			m_ReflectionNo--;
			m_BStatus.Pos.y = m_BStatus.Radius ;
			m_BStatus.Dir = (m_BStatus.Dir == 270) ? 90 : (m_BStatus.Dir > 270) ? m_BStatus.Dir + 90 : m_BStatus.Dir - 90;
		}
		else if (m_BStatus.Pos.y > h / 8 * 7 - m_BStatus.Radius )
		{
			m_ReflectionNo--;
			m_BStatus.Pos.y = h / 8 * 7 - m_BStatus.Radius ;
			m_BStatus.Dir = (m_BStatus.Dir == 90) ? 270 : (m_BStatus.Dir > 90) ? m_BStatus.Dir + 90 : m_BStatus.Dir - 90;
		}
		if (m_BStatus.Dir < 0)
			m_BStatus.Dir += 360;
		if (m_BStatus.Dir > 360)
			m_BStatus.Dir -= 360;
	}
	else
	{
		if (m_BStatus.Pos.y - m_BStatus.Radius  > h || m_BStatus.Pos.y + m_BStatus.Radius  < 0 || m_BStatus.Pos.x - m_BStatus.Radius  > w || m_BStatus.Pos.x + m_BStatus.Radius  < 0)
			m_BStatus.bDrow = false;
	}
}

void CTrickGun::Render() {
	if (m_BStatus.bDrow == true)
		CGraphicsUtilities::RenderFillCircle(GetRenderCircle(), (m_PlayerNo == 0) ? MOF_COLOR_WHITE : MOF_COLOR_YELLOW);
}

void CTrickGun::Release() {

}