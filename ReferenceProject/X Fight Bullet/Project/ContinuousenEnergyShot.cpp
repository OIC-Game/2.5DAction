#include "ContinuousenEnergyShot.h"

CContinuousenEnergyShot::CContinuousenEnergyShot()
{
}

CContinuousenEnergyShot::~CContinuousenEnergyShot()
{
}

void CContinuousenEnergyShot::Initialize(int playerno, int posno) {
	m_PlayerNo = playerno;
	m_BStatus.Damage = 40;
	m_BStatus.Speed = 28;
	m_BStatus.Radius  = 18;
	m_BStatus.GetSkillPoint  = 15;
	m_BStatus.GiveSkillPoint  = 5;
}

void CContinuousenEnergyShot::Generation(CCircle player, CCircle enemy) {
	m_BStatus.bDrow = true;
	m_BStatus.Pos.y = player.y;
	m_BStatus.Pos.x = (player.x < enemy.x) ? player.x + player.r - m_BStatus.Radius  : player.x - player.r + m_BStatus.Radius ;
	m_BStatus.Dir = (player.x < enemy.x) ? 0 : 180;
	CSoundManager::GetInstance().GetSE(10).Play();
}

void CContinuousenEnergyShot::Update(CCircle player, CCircle enemy) {
	if (m_BStatus.bDrow == false) { return; }
	int slow = CJokerSkillManager::GetInstance().GetSlow(m_PlayerNo);
	m_BStatus.Move.x = cos(MOF_ToRadian(m_BStatus.Dir)) * m_BStatus.Speed;
	m_BStatus.Move.y = sin(MOF_ToRadian(m_BStatus.Dir)) * m_BStatus.Speed;

	m_BStatus.Pos.x += m_BStatus.Move.x / slow;
	m_BStatus.Pos.y += m_BStatus.Move.y / slow;

	if (m_BStatus.Pos.y - m_BStatus.Radius  > m_Height / 8 * 7 || m_BStatus.Pos.y + m_BStatus.Radius  < 0 || m_BStatus.Pos.x - m_BStatus.Radius  > m_Width || m_BStatus.Pos.x + m_BStatus.Radius  < 0)
		m_BStatus.bDrow = false;
}

void CContinuousenEnergyShot::Render() {
	if (m_BStatus.bDrow)
		CGraphicsUtilities::RenderFillCircle(GetRenderCircle(), (m_PlayerNo == 0) ? MOF_COLOR_WHITE : MOF_COLOR_YELLOW);
}

void CContinuousenEnergyShot::Release() {

}