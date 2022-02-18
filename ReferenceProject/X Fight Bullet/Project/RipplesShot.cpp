#include "RipplesShot.h"



CRipplesShot::CRipplesShot()
{
}


CRipplesShot::~CRipplesShot()
{
}

void CRipplesShot::Initialize(int playerno, int posno) {
	m_BStatus.Speed = 1;
}

void CRipplesShot::Generation(CCircle player, CCircle enemy) {
	m_BStatus.bDrow = true;
	m_BStatus.Pos.x = player.x;
	m_BStatus.Pos.y = player.y;
	m_BStatus.Radius  = player.r;
	CSoundManager::GetInstance().GetSE(15).Play();
}

void CRipplesShot::Update(CCircle player, CCircle enemy) {
	if (!m_BStatus.bDrow) { return; }
	int slow = CJokerSkillManager::GetInstance().GetSlow(m_PlayerNo);
	m_BStatus.Radius  += m_BStatus.Speed / slow;
	if (m_BStatus.Radius  > 1000)
		m_BStatus.bDrow = false;
}

void CRipplesShot::Render() {
	if (m_BStatus.bDrow)
		CGraphicsUtilities::RenderCircle(GetRenderCircle(), (m_PlayerNo == 0) ? MOF_COLOR_WHITE : MOF_COLOR_YELLOW);
}

void CRipplesShot::Release() {

}