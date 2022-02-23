#include "ExplosionShot.h"

CExplosionShot::CExplosionShot()
{
}


CExplosionShot::~CExplosionShot()
{
}

void CExplosionShot::Initialize(int playerno, int posno) {
	m_PlayerNo = playerno;
	m_Len = 0;
	m_BStatus.Damage = m_FlyDamage;
	m_BStatus.Speed = 18;
	m_BStatus.GrowSpeed = 10;
	m_BStatus.FirstRadius = 3;
	m_BStatus.MaxRadius = 70;
	m_BStatus.PerTime = 20;
	m_BStatus.NotDamageTime  = 50;
	m_BStatus.GetSkillPoint  = 15;
	m_BStatus.GiveSkillPoint  = 5;
	m_BStatus.bDrow = false;
	m_BStatus.bDisappear = false;
}

void CExplosionShot::Generation(CCircle player, CCircle enemy) {
	m_BStatus.bDrow = true;
	m_PhaseNo = 0;
	m_BStatus.Radius  = m_BStatus.FirstRadius;
	m_Len = 0;
	m_WaiteRemTime = 0;
	m_BStatus.PerRemTime = 0;
	m_BStatus.NotDamageRemTime = 0;
	m_BStatus.Damage = m_FlyDamage;
	m_BStatus.Pos.y = player.y;
	m_BStatus.Pos.x = (player.x < enemy.x) ? player.x + player.r - m_BStatus.Radius  : player.x - player.r + m_BStatus.Radius ;
	m_BStatus.Dir = (player.x < enemy.x) ? 0 : 180;
}

void CExplosionShot::Update(CCircle player, CCircle enemy){
	if (!m_BStatus.bDrow) { return; }
	int slow = CJokerSkillManager::GetInstance().GetSlow(m_PlayerNo);
	if (CJokerSkillManager::GetInstance().CanMove(m_PlayerNo))
	{
		m_WaiteRemTime = max(m_WaiteRemTime - 1, 0);
		m_BStatus.PerRemTime = max(m_BStatus.PerRemTime - 1, 0);
	}
	if (m_WaiteRemTime > 0)
	{
		return;
	}
	if (m_BStatus.PerRemTime > 0)
	{
		return;
	}
	if (m_Len < g_pGraphics->GetTargetWidth() * 0.4f)
	{
		m_Len += m_BStatus.Speed / slow;
		m_BStatus.Move.x = cos(MOF_ToRadian(m_BStatus.Dir)) * m_BStatus.Speed;
		m_BStatus.Move.y = sin(MOF_ToRadian(m_BStatus.Dir)) * m_BStatus.Speed;

		m_BStatus.Pos.x += m_BStatus.Move.x / slow;
		m_BStatus.Pos.y += m_BStatus.Move.y / slow;
	}
	else if (m_PhaseNo == 0)
	{
		CSoundManager::GetInstance().GetSE(14).Play();
		m_WaiteRemTime = m_WaiteTime;
		m_PhaseNo = 1;
	}
	else if (m_PhaseNo == 1)
	{
		m_BStatus.Damage = m_ExpDamage;
		if (m_BStatus.Radius  < m_BStatus.MaxRadius)
			m_BStatus.Radius  += m_BStatus.GrowSpeed / slow;
		else
		{
			m_BStatus.Radius  = m_BStatus.MaxRadius;
			m_BStatus.PerRemTime = m_BStatus.PerTime;
			m_PhaseNo = 2;
		}
	}
	else if (m_PhaseNo == 2)
	{
		if (m_BStatus.Radius  > 0)
			m_BStatus.Radius  -= m_Smaller / slow;
		else
		{
			m_BStatus.Radius  = 0;
			m_BStatus.bDrow = false;
		}
	}
}

void CExplosionShot::Render() {
	if (!m_BStatus.bDrow) { return; }
	CMatrix44 matWorld;
	matWorld.Scaling(1, 1, 1);
	matWorld.SetTranslation(m_BStatus.Pos.x, 0, m_BStatus.Pos.y);
	CGraphicsUtilities::RenderSphere(matWorld, CVector4(1.0f, 1.0f, 0.0f, 1.0f));
}

void CExplosionShot::Release() {

}