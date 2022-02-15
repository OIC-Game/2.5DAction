#include	"Item.h"

/**
 * �R���X�g���N�^
 *
 */
CItem::CItem() :
	m_pTexture(NULL),
	m_Motion(),
	m_PosX(0.0f),
	m_PosY(0.0f),
	m_MoveX(0.0f),
	m_MoveY(0.0f),
	m_bShow(false),
	m_WaitTime(0),
	m_SrcRect() {
}

/**
 * �f�X�g���N�^
 *
 */
CItem::~CItem() {
	//delete[] �ŉ�������悤��Release���f�X�g���N�^�Ŏ��s����
	Release();
}

/**
 * ������
 * �p�����[�^�[����W������������B
 *
 * ����
 * [in]			px					X���W
 * [in]			py					Y���W
 * [in]			type				�G�^�C�v
 */
void CItem::Initialize(float px, float py, int type) {
	m_Type = type;
	m_PosX = px;
	m_PosY = py;
	m_MoveX = 0.0f;
	m_MoveY = 0.0f;
	m_bShow = true;
	m_bIn = false;
	m_WaitTime = 0;
	//�A�j���[�V�������쐬
	switch (m_Type)
	{
		case ITEM_MUSHROOM:
		{
			m_MoveX = 1.5f;
			SpriteAnimationCreate anim = {
			"�X�[�p�[�L�m�R",
			0,0,
			32,32,
			FALSE,{5,0,0}
			};
			m_Motion.Create(anim);
			break;
		}
		case ITEM_FLOWER:
		{
			SpriteAnimationCreate anim = {
			"�t�@�C���[�t�����[",
			0,0,
			32,32,
			TRUE,{{8,0,0}, {8,2,0}}
			};
			m_Motion.Create(anim);
			break;
		}
		case ITEM_STAR:
		{
			m_MoveX = 2.0f;
			m_MoveY = -8.0f;
			SpriteAnimationCreate anim = {
			"�X�[�p�[�X�^�[",
			0,0,
			32,32,
			TRUE,{{20,0,0}, {4,2,0}}
			};
			m_Motion.Create(anim);
			break;
		}
	default:
		break;
	}
	m_Motion.ChangeMotion(0);
}

/**
 * �X�V
 *
 */
void CItem::Update(void) {
	//��\��
	if (!m_bShow || m_bIn)
	{
		return;
	}
	//�d�͂ɂ�艺�ɏ�����������
	m_MoveY += GRAVITY;
	if (m_MoveY >= 20.0f)
	{
		m_MoveY = 20.0f;
	}
	//���ۂɍ��W���ړ�������
	m_PosX += m_MoveX;
	m_PosY += m_MoveY;

	if (m_PosY >= g_pGraphics->GetTargetHeight())
	{
		m_bShow = false;
	}

	//�A�j���[�V�����̍X�V
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
	if (m_WaitTime < 3)
		m_WaitTime++;
}

/**
 * �X�e�[�W�Ƃ̓�����
 *
 * ����
 * [in]			ox					X���܂��
 * [in]			oy					Y���܂��
 */
void CItem::CollisionStage(float ox, float oy) {
	m_PosX += ox;
	m_PosY += oy;
	//�������̉����܂�A�W�����v���̏㖄�܂�̏ꍇ�͈ړ�������������B
	if (oy < 0 && m_MoveY > 0)
	{
		m_MoveY = 0;
		if (m_Type == ITEM_STAR)
			m_MoveY = -8;
	}
	else if (oy > 0 && m_MoveY < 0)
	{
		m_MoveY = 0;
	}
	//���ړ����̍����܂�A�E�ړ����̉E���܂�̏ꍇ�͈ړ�������������B
	if (ox < 0 && m_MoveX > 0)
	{
		m_MoveX *= -1;
	}
	else if (ox > 0 && m_MoveX < 0)
	{
		m_MoveX *= -1;
	}
}

/**
 * �`��
 *
 * ����
 * [in]			wx					���[���h�̕ω�
 * [in]			wy					���[���h�̕ω�
 */
void CItem::Render(float wx, float wy) {
	//��\��
	if (!m_bShow || m_bIn)
	{
		return;
	}
	//�e�N�X�`���̕`��
	m_pTexture->Render(m_PosX - wx, m_PosY - wy, m_SrcRect);
}

/**
 * �f�o�b�O�`��
 *
 * ����
 * [in]			wx					���[���h�̕ω�
 * [in]			wy					���[���h�̕ω�
 */
void CItem::RenderDebug(float wx, float wy) {
	//��\��
	if (!m_bShow)
	{
		return;
	}
	//�����蔻��̕\��
	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_XRGB(255, 0, 0));
}

/**
 * ���
 *
 */
void CItem::Release(void) {
	m_Motion.Release();
}