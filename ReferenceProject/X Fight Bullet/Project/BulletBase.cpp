#include "BulletBase.h"

CBulletBase::CBulletBase() :
	m_PlayerNo(0),
	m_BStatus() {
	m_Scale = g_pGraphics->GetTargetHeight();
	m_Scale /= m_Height;
}

CBulletBase::~CBulletBase() {

}

void CBulletBase::SubInitialize() {

}

bool CBulletBase::Collition(CCircle enemy, CCircle egraze, int& pskill, int& damage, int& eskill) {
	pskill = 0;
	damage = 0;
	eskill = 0;
	if (!m_BStatus.bDrow) { return false; }
	if (m_BStatus.NotDamageRemTime > 0)
	{
		m_BStatus.NotDamageRemTime--;
		return false;
	}
	bool re = false;
	if (!m_BStatus.bLaser)
	{
		if (GetCircle().CollisionCircle(enemy))
		{
			damage = m_BStatus.Damage;
			pskill = m_BStatus.GetSkillPoint;
			if (m_BStatus.bDisappear)
			{
				m_BStatus.bDrow = false;
				m_BStatus.bFly = false;
			}
			else
			{
				m_BStatus.NotDamageRemTime = m_BStatus.NotDamageTime;
			}
			if (m_BStatus.bHitSE)
				CSoundManager::GetInstance().GetSE(3).Play();
			re = true;
		}
		else if (GetCircle().CollisionCircle(egraze))
		{
			eskill = m_BStatus.GiveSkillPoint;
			if (m_BStatus.bGrowCollitionGraze)
			{
				m_BStatus.Radius += m_BStatus.GrowSpeed;
			}
			re = true;
		}
	}
	else
	{
		CRectangle erec(enemy.x - enemy.r, enemy.y - enemy.r, enemy.x + enemy.r, enemy.y + enemy.r);
		CRectangle egrec(egraze.x - egraze.r, egraze.y - egraze.r, egraze.x + egraze.r, egraze.y + egraze.r);

		bool dam = false;

		if (GetStartPosCircle().CollisionCircle(enemy))
		{
			dam = true;
		}
		else if (GetEndPosCircle().CollisionCircle(enemy))
		{
			dam = true;
		}
		else if (GetRect().CollisionRect(erec))
		{
			dam = true;
		}

		if (dam)
		{
			damage = m_BStatus.Damage;
			pskill = m_BStatus.GetSkillPoint;
			m_BStatus.NotDamageRemTime = m_BStatus.NotDamageTime;
			if (m_BStatus.bHitSE)
			CSoundManager::GetInstance().GetSE(3).Play();
			return true;
		}

		bool skill = false;
		if (GetStartPosCircle().CollisionCircle(egraze))
		{
			skill = true;
		}
		else if (GetEndPosCircle().CollisionCircle(egraze))
		{
			skill = true;
		}
		else if (GetRect().CollisionRect(egrec))
		{
			skill = true;
		}

		if (skill)
		{
			eskill = m_BStatus.GiveSkillPoint;
			if (m_BStatus.bGrowCollitionGraze)
			{
				m_BStatus.Radius += m_BStatus.GrowSpeed;
			}
			re = true;
		}
	}
	return re;
}