#include "HomingGun.h"



CHomingGun::CHomingGun()
{
}


CHomingGun::~CHomingGun()
{
}

void CHomingGun::Initialize(int playerno, int posno) {
	m_PlayerNo = playerno;
	m_BStatus.Damage = 30;
	m_BStatus.Speed = 23;
	m_BStatus.Radius  = 5;
	m_BStatus.GetSkillPoint  = 2;
	m_BStatus.GiveSkillPoint  = 5;
}

void CHomingGun::Generation(CCircle player, CCircle enemy) {
	m_BStatus.bDrow = true;
	m_BStatus.Pos.y = player.y;
	m_BStatus.Pos.x = (player.x < enemy.x) ? player.x + player.r - m_BStatus.Radius  : player.x - player.r + m_BStatus.Radius ;
	m_BStatus.Dir = atan2(enemy.y - m_BStatus.Pos.y, enemy.x - m_BStatus.Pos.x);
	CSoundManager::GetInstance().GetSE(10).Play();
}

void CHomingGun::Update(CCircle player, CCircle enemy) {
	if (m_BStatus.bDrow == false) { return; }
	int slow = CJokerSkillManager::GetInstance().GetSlow(m_PlayerNo);

	m_BStatus.Move.x = cos(m_BStatus.Dir) * m_BStatus.Speed;
	m_BStatus.Move.y = sin(m_BStatus.Dir) * m_BStatus.Speed;

	m_BStatus.Pos.x += m_BStatus.Move.x / slow;
	m_BStatus.Pos.y += m_BStatus.Move.y / slow;

	if (m_BStatus.Pos.y - m_BStatus.Radius  > m_Height / 8 * 7 || m_BStatus.Pos.y + m_BStatus.Radius  < 0 || m_BStatus.Pos.x - m_BStatus.Radius  > m_Width || m_BStatus.Pos.x + m_BStatus.Radius  < 0)
		m_BStatus.bDrow = false;
}

void CHomingGun::Render() {
	if (m_BStatus.bDrow)
		CGraphicsUtilities::RenderFillCircle(GetRenderCircle(), (m_PlayerNo == 0) ? MOF_COLOR_WHITE : MOF_COLOR_YELLOW);
}

void CHomingGun::Release() {
}