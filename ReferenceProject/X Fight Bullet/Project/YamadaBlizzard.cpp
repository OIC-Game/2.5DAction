#include "YamadaBlizzard.h"

CYamadaBlizzard::CYamadaBlizzard()
{
}

CYamadaBlizzard::~CYamadaBlizzard()
{
}

void CYamadaBlizzard::Initialize(int playerno, int posno) {
	m_PlayerNo = playerno;
	m_BStatus.MaxSpeed = 9;
	m_BStatus.MinSpeed = 5;
	m_BStatus.MaxRadius = 6;
	m_BStatus.MinRadius = 3;
	m_BStatus.GetSkillPoint = 6;
	m_BStatus.GiveSkillPoint = 10;
	m_BStatus.bDrow = false;
}

void CYamadaBlizzard::Generation(CCircle player, CCircle enemy) {
	m_BStatus.bDrow = true;
	m_BStatus.Pos.x = player.x;
	m_BStatus.Pos.y = player.y;
	m_Len = 0;
	m_BStatus.Radius = rand() % (int)(m_BStatus.MaxRadius - m_BStatus.MinRadius) + m_BStatus.MinRadius;
	m_DirChengeCount = rand() % m_DirChenge;
	m_BStatus.Dir = m_Direction[rand() % m_DirectionCount] + 90;
	m_BStatus.Damage = m_Attack[rand() % m_AttackCount];
	m_BStatus.Speed = rand() % (int)(m_BStatus.MaxSpeed - m_BStatus.MinSpeed) + m_BStatus.MinSpeed;
	if (player.x > enemy.x)
		m_BStatus.Dir -= 180;
	CSoundManager::GetInstance().GetSE(24).Play();
}

void CYamadaBlizzard::Update(CCircle player, CCircle enemy) {
	if (m_BStatus.bDrow == false) { return; }
	int slow = CJokerSkillManager::GetInstance().GetSlow(m_PlayerNo);
	m_BStatus.Move.x = cos(MOF_ToRadian(m_BStatus.Dir)) * m_BStatus.Speed;
	m_BStatus.Move.y = sin(MOF_ToRadian(m_BStatus.Dir)) * m_BStatus.Speed;

	m_BStatus.Pos.x += m_BStatus.Move.x / slow;
	m_BStatus.Pos.y += m_BStatus.Move.y / slow;

	if (m_DirChengeCount > 0)
	{
		m_Len += m_BStatus.Speed / slow;
		if (m_Len > 200)
		{
			m_BStatus.Dir = m_Direction[rand() % m_DirectionCount] + 90;
			m_Len = 0;
			m_DirChengeCount--;
			if (m_PlayerNo == 1)
				m_BStatus.Dir -= 180;
		}
	}

	if (m_BStatus.Pos.y - m_BStatus.Radius > m_Height / 8 * 7 || m_BStatus.Pos.y + m_BStatus.Radius  < 0 || m_BStatus.Pos.x - m_BStatus.Radius  > m_Width || m_BStatus.Pos.x + m_BStatus.Radius < 0)
		m_BStatus.bDrow = false;
}

void CYamadaBlizzard::Render() {
	if (m_BStatus.bDrow)
		CGraphicsUtilities::RenderFillCircle(GetRenderCircle(), (m_PlayerNo == 0) ? MOF_COLOR_WHITE : MOF_COLOR_YELLOW);
}

void CYamadaBlizzard::Release() {

}