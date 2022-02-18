#include "WaveShot.h"



CWaveShot::CWaveShot()
{
}


CWaveShot::~CWaveShot()
{
}

void CWaveShot::Initialize(int playerno, int posno) {
	m_PlayerNo = playerno;
	m_BStatus.PosNo = posno % 2;
	m_BStatus.Damage = 100;
	m_BStatus.Speed = 12;
	m_BStatus.Radius  = 18;
	m_BStatus.GetSkillPoint  = 18;
	m_BStatus.GiveSkillPoint  = 10;
	m_WaveDir = 0;
	m_BStatus.bDrow = false;
}

void CWaveShot::Generation(CCircle player, CCircle enemy) {
	m_BStatus.bDrow = true;
	m_BStatus.Pos.y = player.y;
	m_BStatus.Pos.x = (player.x < enemy.x) ? player.x + player.r - m_BStatus.Radius  : player.x - player.r + m_BStatus.Radius ;
	m_BStatus.Dir = (player.x < enemy.x) ? 0 : 180;
	m_WaveDir = 0;
	CSoundManager::GetInstance().GetSE(1).Play();
}

void CWaveShot::Update(CCircle player, CCircle enemy) {
	if (!m_BStatus.bDrow) { return; }
	if (m_BStatus.bDrow == false) { return; }
	int slow = CJokerSkillManager::GetInstance().GetSlow(m_PlayerNo);

	m_BStatus.Move.x = cos(MOF_ToRadian(m_BStatus.Dir)) * m_BStatus.Speed;
	m_BStatus.Move.y = (player.x > enemy.x) ? sin(MOF_ToRadian(m_WaveDir)) * m_BStatus.Speed : -sin(MOF_ToRadian(m_WaveDir)) * m_BStatus.Speed;
	m_WaveDir += (m_BStatus.PosNo == 0) ? 15 : -15;

	m_BStatus.Pos.x += m_BStatus.Move.x / slow;
	m_BStatus.Pos.y += m_BStatus.Move.y / slow;

	if (m_BStatus.Pos.y - m_BStatus.Radius  > m_Height / 8 * 7 || m_BStatus.Pos.y + m_BStatus.Radius  < 0 || m_BStatus.Pos.x - m_BStatus.Radius  > m_Width || m_BStatus.Pos.x + m_BStatus.Radius  < 0)
		m_BStatus.bDrow = false;
}

void CWaveShot::Render() {
	if (m_BStatus.bDrow)
		CGraphicsUtilities::RenderFillCircle(GetRenderCircle(), (m_PlayerNo == 0) ? MOF_COLOR_WHITE : MOF_COLOR_YELLOW);
}

void CWaveShot::Release() {

}