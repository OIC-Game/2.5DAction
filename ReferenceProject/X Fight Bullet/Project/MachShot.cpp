#include "MachShot.h"



CMachShot::CMachShot()
{
}


CMachShot::~CMachShot()
{
}

void CMachShot::Initialize(int playerno, int posno) {
	m_PlayerNo = playerno;
	m_BStatus.PosNo = posno % 3;
	m_BStatus.Damage = 15;
	m_BStatus.Speed = 20;
	m_BStatus.Radius  = 3;
	m_BStatus.GetSkillPoint  = 10;
	m_BStatus.GiveSkillPoint  = 10;
	m_BStatus.bDrow = false;
}

void CMachShot::Generation(CCircle player, CCircle enemy) {
	m_BStatus.bDrow = true;
	m_BStatus.Pos.y = player.y;
	m_BStatus.Pos.x = (player.x < enemy.x) ? player.x + player.r - m_BStatus.Radius  : player.x - player.r + m_BStatus.Radius ;
	m_BStatus.Dir = m_DirPatern[m_BStatus.PosNo] + 90;
	m_BStatus.Dir += (player.x > enemy.x) ? 0 : 180;
	CSoundManager::GetInstance().GetSE(10).Play();
}

void CMachShot::Update(CCircle player, CCircle enemy) {
	if (m_BStatus.bDrow == false) { return; }
	int slow = CJokerSkillManager::GetInstance().GetSlow(m_PlayerNo);

	m_BStatus.Move.x = cos(MOF_ToRadian(m_BStatus.Dir)) * m_BStatus.Speed;
	m_BStatus.Move.y = sin(MOF_ToRadian(m_BStatus.Dir)) * m_BStatus.Speed;

	m_BStatus.Pos.x += m_BStatus.Move.x / slow;
	m_BStatus.Pos.y += m_BStatus.Move.y / slow;

	if (m_BStatus.Pos.y - m_BStatus.Radius  > m_Height / 8 * 7 || m_BStatus.Pos.y + m_BStatus.Radius  < 0 || m_BStatus.Pos.x - m_BStatus.Radius  > m_Width || m_BStatus.Pos.x + m_BStatus.Radius  < 0)
		m_BStatus.bDrow = false;
}

void CMachShot::Render() {
	if (m_BStatus.bDrow)
		CGraphicsUtilities::RenderFillCircle(GetRenderCircle(), (m_PlayerNo == 0) ? MOF_COLOR_WHITE : MOF_COLOR_YELLOW);
}

void CMachShot::Release() {

}