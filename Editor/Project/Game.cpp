#include "Game.h"

CGame::CGame() :
	CScensBace()
{
}


CGame::~CGame()
{
}

bool CGame::Load() {
	//if (!m_BackImage.Load(""))
		//return false;
	// �v���C���[�̑f�ޓǂݍ���
	m_Player.Load();
	// �X�e�[�W�̑f�ޓǂݍ���
	switch (m_StageNo)
	{
	case 0:
		m_Stage.Load("Stage1.txt");
		break;
	case 1:
		m_Stage.Load("Stage2.txt");
		break;
	case 2:
		m_Stage.Load("Stage3.txt");
		break;
	default:
		break;
	}
	// �G�������m��
	m_EnemyArray = new CEnemy[m_Stage.GetEnemyCount()];
	//�A�C�e���������m��
	m_ItemArray = new CItem[m_Stage.GetItemCount()];

	return true;
}

void CGame::Initialize() {
	m_bEnd = false;
	// �v���C���[�̏�ԏ�����
	m_Player.Initialize(m_Stage.GetPlayerPosX(),m_Stage.GetPlayerPosY());
	// �v���C���[�̏�ԏ�����
	m_Stage.Initialize(m_EnemyArray, m_ItemArray);

	/*
	m_Sound1.Load("bgm1.mp3");
	m_Sound2.Load("bgm2.mp3");
	m_Sound1.SetLoop(TRUE);
	m_Sound2.SetLoop(TRUE);
	m_Sound1.Play();
	*/
}

void CGame::Update() {
	// �v���C���[�̍X�V
	m_Player.Update();

	if (m_Player.GetStarWait() > 0)
	{
		if (!m_Sound2.IsPlay())
		{
			m_Sound1.SetVolume(0);
			m_Sound2.Play();
		}
	}
	else
	{
		if (m_Sound2.IsPlay())
		{
			m_Sound2.Stop();
			m_Sound1.SetVolume(1);
		}
	}

	// �X�e�[�W�ƃv���C���[�̓����蔻��
	float ox = 0, oy = 0; int StageChipNo;bool bHit = false, bIn = false;
	if (m_Stage.Collision(m_Player.GetRect(), ox, oy, StageChipNo))
	{
		m_Player.CollisionStage(ox, oy, StageChipNo);
	}
	for (int i = 0; i < m_Player.GetFireCount(); i++)
	{
		if (!m_Player.GetFireBallShow(i))
		{
			continue;
		}
		if (m_Stage.Collision(m_Player.GetFireRect(i), ox, oy, StageChipNo))
		{
			m_Player.CollisionStageFireBall(ox, oy, StageChipNo,i);
		}
	}

	// 17-6
	// �G�̍X�V
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		if (!m_EnemyArray[i].GetShow() && m_EnemyArray[i].GetType() == 0)
		{
			continue;
		}
		if (m_EnemyArray[i].GetRect().Left > m_Stage.GetScrollX() + g_pGraphics->GetTargetWidth() + 200 || m_EnemyArray[i].GetRect().Right < m_Stage.GetScrollX() - 200)
		{
			continue;
		}
		m_EnemyArray[i].Update();
		float ox = 0, oy = 0; int StageChipNo; bool bHit = false, bIn = false;
		if (m_Stage.Collision(m_EnemyArray[i].GetRect(), ox, oy, StageChipNo))
		{
			m_EnemyArray[i].InChip(bIn);
			if (!bIn)
				m_EnemyArray[i].CollisionStage(ox, oy, 0, bHit);
			if (!m_Stage.Collision(m_EnemyArray[i].GetForwardRect(), ox, oy, StageChipNo))
			{
				m_EnemyArray[i].ChangeReverse();
			}
		}
		if (m_EnemyArray[i].GetType() != 0)
		{
			if (m_Stage.Collision(m_EnemyArray[i].GetSRect(), ox, oy, StageChipNo))
			{
				m_EnemyArray[i].CollisionStage(ox, oy, 1, bHit);
			}
		}
		for (int j = 0; j < m_Stage.GetEnemyCount(); j++)
		{
			if (m_EnemyArray[i].GetType() != 0 && m_EnemyArray[i].GetSMoveX() != 0)
			{
				if (m_EnemyArray[i].GetSRect().CollisionRect(m_EnemyArray[j].GetRect()))
				{
					m_EnemyArray[j].Damage(1,true,true);
				}
			}
			if (i == j || m_EnemyArray[i].GetDamageWait() > 0 || !m_EnemyArray[i].GetShow() || !m_EnemyArray[j].GetShow())
			{
				continue;
			}
			if (m_EnemyArray[i].GetRect().CollisionRect(m_EnemyArray[j].GetRect()))
			{
				float ix;
				if (m_EnemyArray[i].GetRect().Left > m_EnemyArray[j].GetRect().Left)
					ix = m_EnemyArray[j].GetRect().Right - m_EnemyArray[i].GetRect().Left;
				else
					ix = m_EnemyArray[i].GetRect().Right - m_EnemyArray[j].GetRect().Left;
				m_EnemyArray[i].CollisionEnemy(ix);
			}
		}
	}
	//�A�C�e���̍X�V
	for (int i = 0;i < m_Stage.GetItemCount();i++)
	{
		if (!m_ItemArray[i].GetShow())
		{
			continue;
		}
		m_ItemArray[i].Update();
		float ox = 0, oy = 0;bool bHit = false, bIn = false;
		if (m_Stage.Collision(m_ItemArray[i].GetRect(), ox, oy, StageChipNo))
		{
				m_ItemArray[i].InChip(bIn);
			if (!bIn)
				m_ItemArray[i].CollisionStage(ox, oy);
		}
	}
	// �G�Ƃ̓����蔻��
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		m_Player.CollisionEnemy(m_EnemyArray[i]);
	}
	for (int i = 0;i < m_Stage.GetItemCount();i++)
	{
		m_Player.CollisionItem(m_ItemArray[i]);
	}

	// �X�e�[�W�̍X�V
	m_Stage.Update(m_Player);

	if (m_Player.IsDead())
	{
		m_bEnd = true;
		m_NextScene = SCENENO_GAMEOVER;
	}
	if (m_Player.IsGoal())
	{
		m_bEnd = true;
		m_NextScene = SCENENO_GAMECLEAR;
	}
	if (g_pInput->IsKeyPush(MOFKEY_F2))
	{
		m_bEnd = true;

		m_NextScene = SCENENO_TITLE;
	}
	else if (g_pInput->IsKeyPush(MOFKEY_F3))
	{
		m_bEnd = true;
		m_NextScene = SCENENO_GAMECLEAR;
	}
	else if (g_pInput->IsKeyPush(MOFKEY_F3))
	{
		m_bEnd = true;
		m_NextScene = SCENENO_GAMEOVER;
	}
}

void CGame::Render() {
	// �X�e�[�W�̕`��
	m_Stage.Render();
	// �v���C���[�̕`��
	m_Player.Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	// �G�̕`��
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		m_EnemyArray[i].Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
	//�A�C�e���̕`��
	for (int i = 0;i < m_Stage.GetItemCount();i++)
	{
		m_ItemArray[i].Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
}

void CGame::RenderDebug(void) {
	// �X�e�[�W�̃f�o�b�O�`��
	m_Stage.RenderDebug();
	// �v���C���[�̃f�o�b�O�`��
	m_Player.RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	// �G�̃f�o�b�O�`��
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		m_EnemyArray[i].RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
	//�A�C�e���̃f�o�b�O�`��
	for (int i = 0;i < m_Stage.GetItemCount();i++)
	{
		m_ItemArray[i].RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
}

void CGame::Release() {
	//m_BackImage.Release();
	// �X�e�[�W�̉��
	m_Stage.Release();
	// �v���C���[�̉��
	m_Player.Release();
	// �G�̉��
	if (m_EnemyArray)
	{
		delete[] m_EnemyArray;
		m_EnemyArray = NULL;
	}
	//�A�C�e���̉��
	if (m_ItemArray)
	{
		delete[] m_ItemArray;
		m_ItemArray = NULL;
	}
	m_Sound1.Release();
	m_Sound2.Release();
}