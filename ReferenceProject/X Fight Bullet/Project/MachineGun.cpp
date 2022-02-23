#include "MachineGun.h"

CMachineGun::CMachineGun()
{
}

CMachineGun::~CMachineGun()
{
}

void CMachineGun::Initialize(int playerno, int posno) {
	m_PlayerNo = playerno;
	m_BStatus.PosNo = posno % 2;
	m_BStatus.Damage = 5;
	m_BStatus.Speed = 12;
	m_BStatus.Radius  = 4;
	m_BStatus.GetSkillPoint  = 15;
	m_BStatus.GiveSkillPoint  = 5;
	m_BStatus.bDrow = false;
}

void CMachineGun::Generation(CCircle player, CCircle enemy) {
	m_BStatus.bDrow = true;
	m_BStatus.Pos.y = (m_BStatus.PosNo == 0) ? player.y - m_width : player.y + m_width;
	m_BStatus.Pos.x = (player.x < enemy.x) ? player.x + player.r - m_BStatus.Radius  : player.x - player.r + m_BStatus.Radius ;
	m_BStatus.Dir = (player.x < enemy.x) ? 0 : 180;
	CSoundManager::GetInstance().GetSE(6).Play();
}

void CMachineGun::Update(CCircle player, CCircle enemy) {
	if (m_BStatus.bDrow == false) { return; }
	int slow = CJokerSkillManager::GetInstance().GetSlow(m_PlayerNo);
	m_BStatus.Move.x = cos(MOF_ToRadian(m_BStatus.Dir)) * m_BStatus.Speed;
	m_BStatus.Move.y = sin(MOF_ToRadian(m_BStatus.Dir)) * m_BStatus.Speed;

	m_BStatus.Pos.x += m_BStatus.Move.x / slow;
	m_BStatus.Pos.y += m_BStatus.Move.y / slow;

	if (m_BStatus.Pos.y - m_BStatus.Radius  > g_pGraphics->GetTargetHeight() || m_BStatus.Pos.y + m_BStatus.Radius  < 0 || m_BStatus.Pos.x - m_BStatus.Radius  > g_pGraphics->GetTargetWidth() || m_BStatus.Pos.x + m_BStatus.Radius  < 0)
		m_BStatus.bDrow = false;
}

void CMachineGun::Render() {
	if (m_BStatus.bDrow)
		CGraphicsUtilities::RenderFillCircle(GetRenderCircle(), (m_PlayerNo == 0) ? MOF_COLOR_WHITE : MOF_COLOR_YELLOW);
}

void CMachineGun::Release() {

}