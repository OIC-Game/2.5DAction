#include "GrowShot.h"



CGrowShot::CGrowShot()
{
}


CGrowShot::~CGrowShot()
{
}

void CGrowShot::Initialize(int playerno, int posno) {
	m_PlayerNo = playerno;
	m_BStatus.PosNo = posno % 3;
	m_BStatus.FirstRadius = 3;
	m_BStatus.Speed = 13;
	m_BStatus.GrowSpeed = 0.5;
	m_BStatus.Damage = 25;
	m_BStatus.GetSkillPoint  = 20;
	m_BStatus.GiveSkillPoint  = 2;
}

void CGrowShot::Generation(CCircle player, CCircle enemy) {
	m_BStatus.bDrow = true;
	m_BStatus.Pos.y = player.y;
	m_BStatus.Pos.x = (player.x < enemy.x) ? player.x + player.r - m_BStatus.Radius  : player.x - player.r + m_BStatus.Radius ;
	m_BStatus.Radius  = m_BStatus.FirstRadius;
	m_BStatus.Dir = (player.x < enemy.x) ? 0 : 180;
	CSoundManager::GetInstance().GetSE(10).Play();
}

void CGrowShot::Update(CCircle player, CCircle enemy) {
	if (m_BStatus.bDrow == false) { return; }
	int slow = CJokerSkillManager::GetInstance().GetSlow(m_PlayerNo);

	m_BStatus.Radius  += m_BStatus.GrowSpeed;

	m_BStatus.Move.x = cos(MOF_ToRadian(m_BStatus.Dir)) * m_BStatus.Speed;
	m_BStatus.Move.y = sin(MOF_ToRadian(m_BStatus.Dir)) * m_BStatus.Speed;

	m_BStatus.Pos.x += m_BStatus.Move.x / slow;
	m_BStatus.Pos.y += m_BStatus.Move.y / slow;

	if (m_BStatus.Pos.y - m_BStatus.Radius  > m_Height / 8 * 7 || m_BStatus.Pos.y + m_BStatus.Radius  < 0 || m_BStatus.Pos.x - m_BStatus.Radius  > m_Width || m_BStatus.Pos.x + m_BStatus.Radius  < 0)
		m_BStatus.bDrow = false;
}

void CGrowShot::Render() {
	if (m_BStatus.bDrow)
		CGraphicsUtilities::RenderFillCircle(GetRenderCircle(), (m_PlayerNo == 0) ? MOF_COLOR_WHITE : MOF_COLOR_YELLOW);
}

void CGrowShot::Release() {

}