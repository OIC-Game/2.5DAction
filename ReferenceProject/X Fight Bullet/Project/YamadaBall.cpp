#include "YamadaBall.h"

CYamadaBall::CYamadaBall()
{
}

CYamadaBall::~CYamadaBall()
{
}

void CYamadaBall::Initialize(int playerno, int posno) {
	m_PlayerNo = playerno;
	m_BStatus.Damage = 120;
	m_BStatus.Speed = 25;
	m_BStatus.Radius = 80;
	m_BStatus.FirstRadius = 3;
	m_BStatus.NotDamageTime = 50;
	m_BStatus.GetSkillPoint = 15;
	m_BStatus.GiveSkillPoint = 5;
	m_BStatus.bDisappear = false;
}

void CYamadaBall::Generation(CCircle player, CCircle enemy) {
	m_BStatus.bDrow = true;
	m_BStatus.Pos.y = player.y;
	m_BStatus.Pos.x = (player.x < enemy.x) ? player.x + player.r - m_BStatus.Radius : player.x - player.r + m_BStatus.Radius;
	m_BStatus.Dir = (player.x < enemy.x) ? 0 : 180;
	m_BStatus.NotDamageRemTime = 0;
	CSoundManager::GetInstance().GetSE(22).Play();
}

void CYamadaBall::Update(CCircle player, CCircle enemy) {
	if (m_BStatus.bDrow == false) { return; }
	int slow = CJokerSkillManager::GetInstance().GetSlow(m_PlayerNo);
	m_BStatus.Move.x = cos(MOF_ToRadian(m_BStatus.Dir)) * m_BStatus.Speed;
	m_BStatus.Move.y = sin(MOF_ToRadian(m_BStatus.Dir)) * m_BStatus.Speed;

	m_BStatus.Pos.x += m_BStatus.Move.x / slow;
	m_BStatus.Pos.y += m_BStatus.Move.y / slow;

	if (m_BStatus.Pos.y - m_BStatus.Radius > m_Height / 8 * 7 || m_BStatus.Pos.y + m_BStatus.Radius  < 0 || m_BStatus.Pos.x - m_BStatus.Radius  > m_Width || m_BStatus.Pos.x + m_BStatus.Radius < 0)
		m_BStatus.bDrow = false;
}

void CYamadaBall::Render() {
	if (m_BStatus.bDrow)
		CGraphicsUtilities::RenderFillCircle(GetRenderCircle(), (m_PlayerNo == 0) ? MOF_COLOR_WHITE : MOF_COLOR_YELLOW);
}

void CYamadaBall::Release() {

}