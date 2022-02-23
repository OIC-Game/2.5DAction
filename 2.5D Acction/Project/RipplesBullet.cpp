#include "RipplesBullet.h"



CRipplesBullet::CRipplesBullet()
{
}


CRipplesBullet::~CRipplesBullet()
{
}

void CRipplesBullet::Initialize(int playerno, int posno) {
	m_PlayerNo = playerno;
	m_BStatus.Radius  = 2;
	m_BStatus.Damage = 10;
	m_BStatus.GiveSkillPoint  = 3;
	m_BStatus.GetSkillPoint  = 3;
	m_BStatus.bDisappear = false;
	m_BStatus.NotDamageTime  = 30;
}

void CRipplesBullet::Generation(CCircle player, CCircle enemy) {
	m_BStatus.bDrow = true;
	m_BStatus.Pos.x = player.x;
	m_BStatus.Pos.y = player.y;
}

void CRipplesBullet::Update(CCircle player, CCircle enemy) {
	if (!m_BStatus.bDrow) { return; }
	m_BStatus.Pos.x = player.x;
	m_BStatus.Pos.y = player.y;

	if (m_BStatus.Pos.y - m_BStatus.Radius  > m_Height / 8 * 7 || m_BStatus.Pos.y + m_BStatus.Radius  < 0 || m_BStatus.Pos.x - m_BStatus.Radius  > m_Width || m_BStatus.Pos.x + m_BStatus.Radius  < 0)
		m_BStatus.bDrow = false;
}

void CRipplesBullet::Render() {
	if (m_BStatus.bDrow)
	{
		CGraphicsUtilities::RenderFillCircle(GetRenderCircle().x,GetRenderCircle().y,GetRenderCircle().r * 2, MOF_COLOR_GREEN);
		CGraphicsUtilities::RenderFillCircle(GetRenderCircle(), (m_PlayerNo == 0) ? MOF_COLOR_WHITE : MOF_COLOR_YELLOW);
	}		
}

void CRipplesBullet::Release() {

}