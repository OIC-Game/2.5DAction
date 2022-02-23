#pragma once
#include	"SoundManager.h"
#include	"TextureManager.h"
#include	"JokerSkillManager.h"

typedef struct tag_BulletStatus {
	CVector2	Pos;						// �e�̍��W
	CVector2	StartPos;					// ���[�U�[�e�̎n�_���W
	CVector2	Move;						// �e�̍��W�ړ���

	float		Radius;						// �e�̑傫���A�^�C�v0�͔��a�A�^�C�v1�͕�
	float		FirstRadius;				// �傫�����ς��e�̍ŏ��̑傫��
	float		MinRadius;					// �傫�����ς��e�̍ŏ��̑傫��
	float		MaxRadius;					// �傫�����ς��e�̍ő�̑傫��

	float		Speed;						// �e�̔�ԑ��x 
	float		FirstSpeed;					// �e���̕ς��e�̍ŏ��̑��x
	float		MinSpeed;					// �e�����ς��e�̍Œᑬ�x
	float		MaxSpeed;					// �e�����ς��e�̍ō����x
	float		GrowSpeed;					// �e���傫���Ȃ鎞�̑��x

	float		Damage;						// �e���G�ɗ^����_���[�W
	float		FirstDamage;				// �e���̕ς��e�̍ŏ��̃_���[�W
	float		MinDamage;					// �_���[�W���ς��e�̍ŏ��_���[�W
	float		MaxDamage;					// �_���[�W���ς��e�̍ő�_���[�W

	float		Dir;						// �e�����ł�������

	float		GetSkillPoint;				// �e�𑊎�ɓ��Ă邱�Ƃœ�����X�L���|�C���g
	float		GiveSkillPoint;				// �e�𑊎肪�O���C�Y�����Ƃ��ɗ^����X�L���|�C���g

	int			PosNo;						// �e�����˂����ʒu�𔻒f����ԍ�
	int			NotDamageTime;				// �e���������Ă������Ȃ����́A�_���[�W���Ȃ��Ȃ鎞��
	int			NotDamageRemTime;			// �e���������Ă������Ȃ����́A�_���[�W���Ȃ��Ȃ�c�莞��
	int			PerTime;					// ���[�U�[�e�Ȃǂ̎�������
	int			PerRemTime;					// ���[�U�[�e�Ȃǂ̎����c�莞��

	bool		bLaser;						// �e�̎�ށA�^�C�vfalse:�~(�ʏ�i)���^�C�vtrue:��`(���[�U�[�e)���𔻒f
	bool		bDrow;						// �e��`�悷�邩�ǂ���
	bool		bFly;						// �e��`�悵����A��΂����ǂ���
	bool		bDisappear;					// �e�������������ɏ����邩�ǂ���
	bool		bGrowCollitionGraze;		// �e���O���C�Y���ꂽ�Ƃ��ɑ傫���Ȃ邩�ǂ���
	bool		bHitSE;

	tag_BulletStatus() :
		Pos(0, 0),
		StartPos(0, 0),
		Move(0, 0),
		Radius(0),
		FirstRadius(0),
		MinRadius(0),
		MaxRadius(0),
		Speed(0),
		FirstSpeed(0),
		MinSpeed(0),
		MaxSpeed(0),
		GrowSpeed(0),
		Damage(0),
		FirstDamage(0),
		MinDamage(0),
		MaxDamage(0),
		Dir(0),
		GetSkillPoint(0),
		GiveSkillPoint(0),
		PosNo(0),
		NotDamageTime(0),
		NotDamageRemTime(0),
		PerTime(0),
		PerRemTime(0),
		bLaser(false),
		bDrow(false),
		bFly(false),
		bDisappear(true),
		bGrowCollitionGraze(false),
		bHitSE(true) {
	}
}BulletStatus;

class CBulletBase
{
private:
	float m_Scale;						// ��ʂ̃T�C�Y�ɉe�����ꂸ�ɍs�����߂̐��l
protected:
	float m_Width = 1280;
	float m_Height = 720;

	int m_PlayerNo;						// �v���C���[�̔ԍ��A�ԍ��̈قȂ�v���C���[�ƏՓ˂Ń_���[�W	

	BulletStatus m_BStatus;

	void SubInitialize();

	CCircle GetStartPosCircle() {
		return CCircle(
			((m_BStatus.Pos.x > m_BStatus.StartPos.x) ? m_BStatus.StartPos.x + m_BStatus.Radius : m_BStatus.Pos.x + m_BStatus.Radius),
			((m_BStatus.Pos.x > m_BStatus.StartPos.x) ? m_BStatus.StartPos.y : m_BStatus.Pos.y),
			m_BStatus.Radius);
	}

	CCircle GetEndPosCircle() {
		return CCircle(
			((m_BStatus.Pos.x > m_BStatus.StartPos.x) ? m_BStatus.Pos.x : m_BStatus.StartPos.x),
			((m_BStatus.Pos.x > m_BStatus.StartPos.x) ? m_BStatus.Pos.y : m_BStatus.StartPos.y),
			m_BStatus.Radius);
	}

	CRectangle GetRect() {
		return CRectangle(
			((m_BStatus.Pos.x > m_BStatus.StartPos.x) ? m_BStatus.StartPos.x + m_BStatus.Radius : m_BStatus.Pos.x + m_BStatus.Radius),
			((m_BStatus.Pos.x > m_BStatus.StartPos.x) ? m_BStatus.StartPos.y - m_BStatus.Radius : m_BStatus.Pos.y - m_BStatus.Radius),
			((m_BStatus.Pos.x > m_BStatus.StartPos.x) ? m_BStatus.Pos.x : m_BStatus.StartPos.x),
			((m_BStatus.Pos.x > m_BStatus.StartPos.x) ? m_BStatus.StartPos.y + m_BStatus.Radius : m_BStatus.Pos.y + m_BStatus.Radius));
	}

	CCircle GetStartPosRenderCircle() {
		return CCircle(
			((m_BStatus.Pos.x > m_BStatus.StartPos.x) ? m_BStatus.StartPos.x + m_BStatus.Radius : m_BStatus.Pos.x + m_BStatus.Radius) * m_Scale,
			((m_BStatus.Pos.x > m_BStatus.StartPos.x) ? m_BStatus.StartPos.y : m_BStatus.Pos.y) * m_Scale,
			m_BStatus.Radius * m_Scale);
	}

	CCircle GetEndPosRenderCircle() {
		return CCircle(
			((m_BStatus.Pos.x > m_BStatus.StartPos.x) ? m_BStatus.Pos.x : m_BStatus.StartPos.x) * m_Scale,
			((m_BStatus.Pos.x > m_BStatus.StartPos.x) ? m_BStatus.Pos.y : m_BStatus.StartPos.y) * m_Scale,
			m_BStatus.Radius * m_Scale);
	}

	CRectangle GetRenderRect() {
		return CRectangle(
			((m_BStatus.Pos.x > m_BStatus.StartPos.x) ? m_BStatus.StartPos.x + m_BStatus.Radius : m_BStatus.Pos.x + m_BStatus.Radius) * m_Scale,
			((m_BStatus.Pos.x > m_BStatus.StartPos.x) ? m_BStatus.StartPos.y - m_BStatus.Radius : m_BStatus.Pos.y - m_BStatus.Radius) * m_Scale,
			((m_BStatus.Pos.x > m_BStatus.StartPos.x) ? m_BStatus.Pos.x : m_BStatus.StartPos.x) * m_Scale,
			((m_BStatus.Pos.x > m_BStatus.StartPos.x) ? m_BStatus.StartPos.y + m_BStatus.Radius : m_BStatus.Pos.y + m_BStatus.Radius) * m_Scale);
	}
public:
	CBulletBase();
	~CBulletBase();

	virtual void Initialize(int playerno, int posno) = 0;
	virtual void Update(CCircle player, CCircle enemy) = 0;
	virtual void Generation(CCircle player, CCircle enemy) = 0;
	bool Collition(CCircle enemy, CCircle egraze, int& pskill, int& damage, int& eskill);
	virtual void Render() = 0;
	virtual void Release() = 0;

	bool GetDrow() { return m_BStatus.bDrow; }
	bool GetFly() { return m_BStatus.bFly; }
	void SetFly() { m_BStatus.bFly = true; }
	float GetRadius() { return m_BStatus.Radius; }

	CCircle GetCircle() { return CCircle(m_BStatus.Pos.x, m_BStatus.Pos.y, m_BStatus.Radius); }
	CCircle GetRenderCircle() { return CCircle(m_BStatus.Pos.x * m_Scale, m_BStatus.Pos.y * m_Scale, m_BStatus.Radius * m_Scale); }

	const BulletStatus& GetBulletStatus() { return m_BStatus; }
};

