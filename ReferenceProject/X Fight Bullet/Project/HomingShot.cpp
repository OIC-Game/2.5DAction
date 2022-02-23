#include "HomingShot.h"

CHomingShot::CHomingShot()
{
}

CHomingShot::~CHomingShot()
{
}

void CHomingShot::Initialize(int playerno, int posno) {
	m_PlayerNo = playerno;
	m_BStatus.PosNo = posno % 3;
	m_BStatus.Damage = 35;
	m_BStatus.Speed = 10;
	m_BStatus.Radius = 18;
	m_BStatus.GetSkillPoint = 15;
	m_BStatus.GiveSkillPoint = 5;
	m_RemFormPer = 0;
	m_RemFormNo = 0;
	m_BStatus.bDrow = false;
}

void CHomingShot::Generation(CCircle player, CCircle enemy) {
	m_BStatus.bDrow = true;
	m_BStatus.Pos.y = player.y;
	m_BStatus.Pos.x = (player.x < enemy.x) ? player.x + player.r - m_BStatus.Radius : player.x - player.r + m_BStatus.Radius;
	m_BStatus.Dir = MOF_ToRadian(m_DirPatern[m_BStatus.PosNo] + 90);
	m_BStatus.Dir += MOF_ToRadian((player.x > enemy.x) ? 0 : 180);
	m_RemFormNo = 0;
	m_RemFormPer = m_FormPer;
	CSoundManager::GetInstance().GetSE(10).Play();
}

void CHomingShot::Update(CCircle player, CCircle enemy) {
	if (m_BStatus.bDrow == false) { return; }
	int slow = CJokerSkillManager::GetInstance().GetSlow(m_PlayerNo);
	m_BStatus.Move.x = cos(m_BStatus.Dir) * m_BStatus.Speed;
	m_BStatus.Move.y = sin(m_BStatus.Dir) * m_BStatus.Speed;

	m_BStatus.Pos.x += m_BStatus.Move.x / slow;
	m_BStatus.Pos.y += m_BStatus.Move.y / slow;


	if (m_RemFormNo < m_FormNo)
	{
		if (CJokerSkillManager::GetInstance().CanMove(m_PlayerNo))
			m_RemFormPer = max(m_RemFormPer - 1, 0);
		else
		{
			m_BStatus.Dir = atan2(enemy.y - m_BStatus.Pos.y, enemy.x - m_BStatus.Pos.x);
			m_RemFormPer = m_FormPer * slow;
			m_RemFormNo++;
		}
	}
	else if (m_BStatus.Pos.y - m_BStatus.Radius > m_Height / 8 * 7 || m_BStatus.Pos.y + m_BStatus.Radius  < 0 || m_BStatus.Pos.x - m_BStatus.Radius  > m_Width || m_BStatus.Pos.x + m_BStatus.Radius < 0)
		m_BStatus.bDrow = false;
}

void CHomingShot::Render() {
	if (m_BStatus.bDrow)
		CGraphicsUtilities::RenderFillCircle(GetRenderCircle(), (m_PlayerNo == 0) ? MOF_COLOR_WHITE : MOF_COLOR_YELLOW);
}

void CHomingShot::Release() {
}