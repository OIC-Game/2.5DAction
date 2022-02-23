#include "Player.h"



CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
}

bool CPlayer::Load() {
	if (!m_Texture.Load("player.png"))
		return false;

	for (int i = 0; i < FIREBALL_COUNT; i++)
	{
		m_FireBallArray[i].Load(&m_Texture);
	}

	m_Sound1.Load("Sound1.mp3");
	m_Sound2.Load("Sound2.mp3");
	m_Sound3.Load("Sound3.mp3");


	SpriteAnimationCreate anim[] = {
		{
			"���ҋ@",
			0,0,
			64,64,
			FALSE,{ 5,0,0 }
		},
		{
			"������",
			0,0,
			64,64,
			TRUE,{{ 7,0,0 },{ 7,1,0 }}
		},
		{
			"���_�b�V��",
			0,160,
			64,64,
			TRUE,{{ 3,0,0 },{ 3,1,0 }}
		},
		{
			"��������",
			0,0,
			64,64,
			TRUE,{{ 4,0,0 },{ 4,1,0 }}
		},
		{
			"���W�����v",
			0,80,
			64,64,
			FALSE,{ 5,0,0 }
		},
		{
			"������",
			64,80,
			64,64,
			FALSE,{ 5,0,0 }
		},
		{
			"���_�b�V���W�����v",
			128,160,
			64,64,
			FALSE,{ 5,0,0 }
		},
		{
			"���_�b�V���U�����",
			128,80,
			64,64,
			FALSE,{ 5,0,0 }
		},
		{
			"�����Ⴊ��",
			128,0,
			64,64,
			FALSE,{ 5,0,0 }
		},
		{
			"�����グ",
			192,0,
			64,64,
			FALSE,{ 5,0,0 }
		},

		{
			"��ҋ@",
			0,240,
			64,64,
			FALSE,{ 5,0,0 }
		},
		{
			"�����",
			0,240,
			64,64,
			TRUE,{{ 4,0,0 },{ 4,1,0 },{ 4,2,0 }}
		},
		{
			"��_�b�V��",
			0,320,
			64,64,
			TRUE,{{ 4,0,0 },{ 4,1,0 },{ 4,2,0 }}
		},
		{
			"�召����",
			0,240,
			64,64,
			TRUE,{{ 3,0,0 },{ 3,1,0 },{ 3,2,0 }}
		},
		{
			"��W�����v",
			0,400,
			64,64,
			FALSE,{ 5,0,0 }
		},
		{
			"�嗎��",
			64,400,
			64,64,
			FALSE,{ 5,0,0 }
		},
		{
			"��_�b�V���W�����v",
			192,320,
			64,64,
			FALSE,{ 5,0,0 }
		},
		{
			"��_�b�V���U�����",
			192,240,
			64,64,
			FALSE,{ 5,0,0 }
		},
		{
			"�債�Ⴊ��",
			128,400,
			64,64,
			FALSE,{ 5,0,0 }
		},
		{
			"�匩�グ",
			198,400,
			64,64,
			FALSE,{ 5,0,0 }
		},

		{
			"�ԑҋ@",
			0,480,
			64,64,
			FALSE,{ 5,0,0 }
		},
		{
			"�ԕ���",
			0,480,
			64,64,
			TRUE,{{ 4,0,0 },{ 4,1,0 },{ 4,2,0 }}
		},
		{
			"�ԃ_�b�V��",
			0,560,
			64,64,
			TRUE,{{ 4,0,0 },{ 4,1,0 },{ 4,2,0 }}
		},
		{
			"�ԏ�����",
			0,480,
			64,64,
			TRUE,{{ 3,0,0 },{ 3,1,0 },{ 3,2,0 }}
		},
		{
			"�ԃW�����v",
			0,640,
			64,64,
			FALSE,{ 5,0,0 }
		},
		{
			"�ԗ���",
			64,640,
			64,64,
			FALSE,{ 5,0,0 }
		},
		{
			"�ԃ_�b�V���W�����v",
			192,560,
			64,64,
			FALSE,{ 5,0,0 }
		},
		{
			"�ԃ_�b�V���U�����",
			192,480,
			64,64,
			FALSE,{ 5,0,0 }
		},
		{
			"�Ԃ��Ⴊ��",
			128,640,
			64,64,
			FALSE,{ 5,0,0 }
		},
		{
			"�Ԍ��グ",
			198,640,
			64,64,
			FALSE,{ 5,0,0 }
		},
		{
			"�ԃt�@�C���[�{�[��",
			0,720,
			64,64,
			FALSE,{ 8,0,0 }
		},
	};
	m_Motion.Create(anim, MOTION_COUNT);

	return true;
}

void CPlayer::Initialize(float x, float y) {
	m_PosX = x;
	m_PosY = y;
	m_MoveX = 0;
	m_MoveY = 0;
	m_HP = 1;
	m_DamageWait = 0;
	m_StarWait = 0;
	m_bMove = false;
	m_bDash = false;
	m_bGoal = false;
	m_Motion.ChangeMotion(MOTIONNO_SMALL_WAIT);
	for (int i = 0; i < FIREBALL_COUNT; i++)
	{
		m_FireBallArray[i].Initialize();
	}

}

void CPlayer::Update() {
	
	m_bMove = false;
	m_bFall = false;
	if (m_MoveY != 0)
		m_bFall = true;

	UpdateKey();
	UpdateMove();

	m_PosX += m_MoveX;
	m_PosY += m_MoveY;

	if (m_PosX <= 0)
	{
		m_PosX = 0;
	}
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();

	if (m_DamageWait > 0)
	{
		m_DamageWait--;
	}
	if (m_StarWait > 0)
	{
		m_StarWait--;
	}

	ChangeMotions();
	for (int i = 0; i < FIREBALL_COUNT; i++)
	{
		m_FireBallArray[i].Update();
	}
}

void CPlayer::UpdateKey() {

	UpdateKey1();
	if (g_pInput->IsKeyHold(MOFKEY_LEFT))
	{
		UpdateKey2(true);
	}
	else if (g_pInput->IsKeyHold(MOFKEY_RIGHT))
	{
		UpdateKey2(false);
	}
	if (g_pInput->IsKeyHold(MOFKEY_UP))
	{
		m_MoveY--;
		if (m_MoveY < -5)
		{
			m_MoveY = -5;
		}
	}
	else if (g_pInput->IsKeyHold(MOFKEY_DOWN))
	{
		m_MoveY++;
		if (m_MoveY > 5)
		{
			m_MoveY = 5;
		}
	}
	else
	{
		if (m_MoveY > 0)
		{
			m_MoveY--;
		}
		else if (m_MoveY < 0)
		{
			m_MoveY++;
		}
	}
}

void CPlayer::UpdateKey1() {
	if (g_pInput->IsKeyPush(MOFKEY_Z))
	{
		if (!m_bFall)
		{
			if (m_MoveX > PLAYER_MAXSPEED || m_MoveX < -PLAYER_MAXSPEED)
				m_MoveY = PLAYER_DASHJUMP;
			else
				m_MoveY = PLAYER_JUMP;
			m_Sound2.Play();
		}
	}
	if (g_pInput->IsKeyPush(MOFKEY_X))
	{
		if (m_HP == 3 && m_Motion.GetMotionNo() != MOTIONNO_FLOWER_SQUAT)
		{
			m_Motion.ChangeMotion(MOTIONNO_FLOWER_FIRE);
			Fire();
		}
	}
	if (g_pInput->IsKeyHold(MOFKEY_X) && !m_bFall)
	{
		m_bDash = true;
	}
	else
	{
		m_bDash = false;
	}
}

void CPlayer::UpdateKey2(bool bl) {
	int plus = 1;
	
	m_bReverse = bl;
	if (bl)
		plus *= -1;

	if (m_Motion.GetMotionNo() == MOTIONNO_SMALL_SQUAT || m_Motion.GetMotionNo() == MOTIONNO_BIG_SQUAT || m_Motion.GetMotionNo() == MOTIONNO_FLOWER_SQUAT)
	{
		if (!m_bFall)
			return;
	}
	m_bMove = true;
	m_MoveX += PLAYER_SPEED * plus;
	if (m_bDash)
	{
		if (m_MoveX * plus > PLAYER_MAXDASHSPEED)
			m_MoveX = PLAYER_MAXDASHSPEED * plus;
	}
	else if (m_MoveX * plus > PLAYER_MAXSPEED)
	{
		m_MoveX -= PLAYER_SPEED * plus;
	}
}

void CPlayer::Fire() {
	for (int i = 0; i < FIREBALL_COUNT; i++)
	{
		if (m_FireBallArray[i].GetShow())
		{
			continue;
		}
		if (m_bReverse)
		{
			m_FireBallArray[i].Fire(m_PosX, m_PosY + 32, m_bReverse);
		}
		else
		{
			m_FireBallArray[i].Fire(m_PosX + GetRect().GetWidth() + PLAYER_RECTDECREASE, m_PosY + 32, m_bReverse);
		}
		return;
	}
}

void CPlayer::UpdateMove() {
	if (!m_bMove)
	{
		if (m_MoveX > 0)
		{
			m_MoveX -= PLAYER_SPEED;
			if (m_MoveX <= 0)
			{
				m_MoveX = 0;
			}
		}
		else if (m_MoveX < 0)
		{
			m_MoveX += PLAYER_SPEED;
			if (m_MoveX >= 0)
			{
				m_MoveX = 0;
			}
		}
	}

	// �d�͂ɂ�闎��
	//m_MoveY += GRAVITY;
	if (m_MoveY >= 20.0f)
	{
		m_MoveY = 20.0f;
	}
}

void CPlayer::ChangeMotions() {
	switch (m_HP)
	{
	case 1:
	{
		if (m_bFall)
		{
			if (m_Motion.GetMotionNo() == MOTIONNO_SMALL_SQUAT)
			{
				return;
			}
			if (m_Motion.GetMotionNo() == MOTIONNO_SMALL_DASH || m_Motion.GetMotionNo() == MOTIONNO_SMALL_DASHJUMP)
			{
				m_Motion.ChangeMotion(MOTIONNO_SMALL_DASHJUMP);
				return;
			}
			else if (m_MoveY > 0)
			{
				m_Motion.ChangeMotion(MOTIONNO_SMALL_FALL);
			}
			else if (m_MoveY < 0)
			{
				m_Motion.ChangeMotion(MOTIONNO_SMALL_JUMP);
			}
		}
		else
		{
			if (g_pInput->IsKeyHold(MOFKEY_DOWN))
			{
				m_Motion.ChangeMotion(MOTIONNO_SMALL_SQUAT);
			}
			else if (m_MoveX == 0)
			{
				if (g_pInput->IsKeyHold(MOFKEY_UP))
				{
					m_Motion.ChangeMotion(MOTIONNO_SMALL_LOOKUP);
				}
				else
				{
					m_Motion.ChangeMotion(MOTIONNO_SMALL_WAIT);
				}
			}
			else
			{
				if ((m_MoveX >= PLAYER_MAXDASHSPEED && g_pInput->IsKeyHold(MOFKEY_RIGHT)) || (m_MoveX <= -PLAYER_MAXDASHSPEED && g_pInput->IsKeyHold(MOFKEY_LEFT)))
				{
					if (m_Motion.GetMotionNo() != MOTIONNO_SMALL_DASH)
						m_Motion.ChangeMotion(MOTIONNO_SMALL_DASH);

				}
				else if ((m_MoveX > 0 && g_pInput->IsKeyHold(MOFKEY_LEFT)) || (m_MoveX < 0 && g_pInput->IsKeyHold(MOFKEY_RIGHT)))
				{
					if (m_Motion.GetMotionNo() != MOTIONNO_SMALL_DASHTURN && m_Motion.GetMotionNo() == MOTIONNO_SMALL_DASH)
						m_Motion.ChangeMotion(MOTIONNO_SMALL_DASHTURN);
				}
				else if (m_MoveX > 4.0f || m_MoveX < -4.0f)
				{
					if (m_Motion.GetMotionNo() != MOTIONNO_SMALL_DASHMINI)
						m_Motion.ChangeMotion(MOTIONNO_SMALL_DASHMINI);
				}
				else if ((m_MoveX < 0 && g_pInput->IsKeyHold(MOFKEY_LEFT)) || (m_MoveX > 0 && g_pInput->IsKeyHold(MOFKEY_RIGHT)))
				{
					if (m_Motion.GetMotionNo() != MOTIONNO_SMALL_WALK)
						m_Motion.ChangeMotion(MOTIONNO_SMALL_WALK);
				}

			}
		}
		break;
	}
	case 2:
	{
		if (m_bFall)
		{
			if (m_Motion.GetMotionNo() == MOTIONNO_BIG_SQUAT)
			{
				return;
			}
			if (m_Motion.GetMotionNo() == MOTIONNO_BIG_DASH || m_Motion.GetMotionNo() == MOTIONNO_BIG_DASHJUMP)
			{
				m_Motion.ChangeMotion(MOTIONNO_BIG_DASHJUMP);
				return;
			}
			else if (m_MoveY > 0)
			{
				m_Motion.ChangeMotion(MOTIONNO_BIG_FALL);
			}
			else if (m_MoveY < 0)
			{
				m_Motion.ChangeMotion(MOTIONNO_BIG_JUMP);
			}
		}
		else
		{
			if (g_pInput->IsKeyHold(MOFKEY_DOWN))
			{
				m_Motion.ChangeMotion(MOTIONNO_BIG_SQUAT);
			}
			else if (m_MoveX == 0)
			{
				if (g_pInput->IsKeyHold(MOFKEY_UP))
				{
					m_Motion.ChangeMotion(MOTIONNO_BIG_LOOKUP);
				}
				else
				{
					m_Motion.ChangeMotion(MOTIONNO_BIG_WAIT);
				}
			}
			else
			{
				if ((m_MoveX >= PLAYER_MAXDASHSPEED && g_pInput->IsKeyHold(MOFKEY_RIGHT)) || (m_MoveX <= -PLAYER_MAXDASHSPEED && g_pInput->IsKeyHold(MOFKEY_LEFT)))
				{
					if (m_Motion.GetMotionNo() != MOTIONNO_BIG_DASH)
						m_Motion.ChangeMotion(MOTIONNO_BIG_DASH);

				}
				else if ((m_MoveX > 0 && g_pInput->IsKeyHold(MOFKEY_LEFT)) || (m_MoveX < 0 && g_pInput->IsKeyHold(MOFKEY_RIGHT)))
				{
					if (m_Motion.GetMotionNo() != MOTIONNO_BIG_DASHTURN && m_Motion.GetMotionNo() == MOTIONNO_BIG_DASH)
						m_Motion.ChangeMotion(MOTIONNO_BIG_DASHTURN);
				}
				else if (m_MoveX > 4.0f || m_MoveX < -4.0f)
				{
					if (m_Motion.GetMotionNo() != MOTIONNO_BIG_DASHMINI)
						m_Motion.ChangeMotion(MOTIONNO_BIG_DASHMINI);
				}
				else if ((m_MoveX < 0 && g_pInput->IsKeyHold(MOFKEY_LEFT)) || (m_MoveX > 0 && g_pInput->IsKeyHold(MOFKEY_RIGHT)))
				{
					if (m_Motion.GetMotionNo() != MOTIONNO_BIG_WALK)
						m_Motion.ChangeMotion(MOTIONNO_BIG_WALK);
				}

			}
		}
		break;
	}
	case 3:
	{
		if (m_Motion.GetMotionNo() == MOTIONNO_FLOWER_FIRE)
		{
			if (!m_Motion.IsEndMotion())
				return;
		}
		if (m_bFall)
		{
			if (m_Motion.GetMotionNo() == MOTIONNO_FLOWER_SQUAT)
			{
				return;
			}
			if (m_Motion.GetMotionNo() == MOTIONNO_FLOWER_DASH || m_Motion.GetMotionNo() == MOTIONNO_FLOWER_DASHJUMP)
			{
				m_Motion.ChangeMotion(MOTIONNO_FLOWER_DASHJUMP);
				return;
			}
			else if (m_MoveY > 0)
			{
				m_Motion.ChangeMotion(MOTIONNO_FLOWER_FALL);
			}
			else if (m_MoveY < 0)
			{
				m_Motion.ChangeMotion(MOTIONNO_FLOWER_JUMP);
			}
		}
		else
		{
			if (g_pInput->IsKeyHold(MOFKEY_DOWN))
			{
				m_Motion.ChangeMotion(MOTIONNO_FLOWER_SQUAT);
			}
			else if (m_MoveX == 0)
			{
				if (g_pInput->IsKeyHold(MOFKEY_UP))
				{
					m_Motion.ChangeMotion(MOTIONNO_FLOWER_LOOKUP);
				}
				else
				{
					m_Motion.ChangeMotion(MOTIONNO_FLOWER_WAIT);
				}
			}
			else
			{
				if ((m_MoveX >= PLAYER_MAXDASHSPEED && g_pInput->IsKeyHold(MOFKEY_RIGHT)) || (m_MoveX <= -PLAYER_MAXDASHSPEED && g_pInput->IsKeyHold(MOFKEY_LEFT)))
				{
					if (m_Motion.GetMotionNo() != MOTIONNO_FLOWER_DASH)
						m_Motion.ChangeMotion(MOTIONNO_FLOWER_DASH);

				}
				else if ((m_MoveX > 0 && g_pInput->IsKeyHold(MOFKEY_LEFT)) || (m_MoveX < 0 && g_pInput->IsKeyHold(MOFKEY_RIGHT)))
				{
					if (m_Motion.GetMotionNo() != MOTIONNO_FLOWER_DASHTURN && m_Motion.GetMotionNo() == MOTIONNO_FLOWER_DASH)
						m_Motion.ChangeMotion(MOTIONNO_FLOWER_DASHTURN);
				}
				else if (m_MoveX > 4.0f || m_MoveX < -4.0f)
				{
					if (m_Motion.GetMotionNo() != MOTIONNO_FLOWER_DASHMINI)
						m_Motion.ChangeMotion(MOTIONNO_FLOWER_DASHMINI);
				}
				else if ((m_MoveX < 0 && g_pInput->IsKeyHold(MOFKEY_LEFT)) || (m_MoveX > 0 && g_pInput->IsKeyHold(MOFKEY_RIGHT)))
				{
					if (m_Motion.GetMotionNo() != MOTIONNO_FLOWER_WALK)
						m_Motion.ChangeMotion(MOTIONNO_FLOWER_WALK);
				}

			}
		}
		break;
	}
	default:
		break;
	}
	
}

/*
* �X�e�[�W�Ƃ̓�����
*
* ����
* [in]					ox						X���܂��
* [in]					oy						Y���܂��
*/

void CPlayer::CollisionStage(float ox, float oy, int scno) {

	scno += 1;
	switch (scno)
	{
	case 13:
		break;
	case 6:
	case 14:
	case 22:
		m_bGoal = true;
		break;
	default:
		m_PosX += ox;
		m_PosY += oy;
		// �������̉����܂�A�W�����v���̏㖄�܂�̏ꍇ�͈ړ�������������B
		if (oy < 0 && m_MoveY > 0)
		{
			m_MoveY = 0;
		}
		else if (oy > 0 && m_MoveY < 0)
		{
			m_MoveY = 0;
		}

		// ���ړ����̍����܂�A�E�ړ����̉E���܂�̏ꍇ�͈ړ�������������B
		if (ox < 0 && m_MoveX > 0)
		{
			m_MoveX = 0;
		}
		else if (ox > 0 && m_MoveX < 0)
		{
			m_MoveX = 0;
		}
		break;
	}
}

void CPlayer::CollisionStageFireBall(float ox, float oy, int scno, int i) {

	scno += 1;
	switch (scno)
	{
	case 13:
	case 6:
	case 14:
	case 17:
	case 22:
		break;
	default:
		m_FireBallArray[i].Collision(ox,oy);
		break;
	}
}

bool CPlayer::CollisionEnemy(CEnemy& ene) {

	CRectangle prec = GetRect();
	CRectangle erec = ene.GetRect();
	CRectangle pbrec = GetBRect();
	CRectangle etrec = ene.GetTRect();

	
	if (ene.GetShow() && !ene.GetIn())
	{
		if (ene.GetDamageWait() == 0)
		{
			if (m_StarWait > 0)
			{
				if (prec.CollisionRect(erec))
				{
					ene.Damage(1, m_bReverse, true);
					return true;
				}
			}
			for (int i = 0; i < FIREBALL_COUNT; i++)
			{
				if (!m_FireBallArray[i].GetShow())
				{
					continue;
				}
				CRectangle fr = m_FireBallArray[i].GetRect();
				if (fr.CollisionRect(erec))
				{
					ene.Damage(1, m_bReverse, true);
					m_FireBallArray[i].Hit();
				}
			}
			if (pbrec.CollisionRect(etrec))
			{
				m_Sound3.Play();
				bool Rev = false;
				if (pbrec.Left > etrec.Left)
					Rev = true;
				ene.Damage(1, Rev, false);
				// ���܂���������y�������炷
				int Buried = pbrec.Bottom - etrec.Top - 1;
				m_PosY -= Buried;
				if (g_pInput->IsKeyHold(MOFKEY_Z))
					m_MoveY = PLAYER_JUMP * 1.1f;
				else
					m_MoveY = PLAYER_JUMP * 0.8f;
				return true;
			}

			if (m_DamageWait == 0 && prec.CollisionRect(erec))
			{
				m_HP -= 1;
				m_DamageWait = 120;
				return true;
			}
		}
	}

	if (ene.GetType() != 0 && ene.GetSShow())
	{
		CRectangle esrec = ene.GetSRect();
		CRectangle estrec = ene.GetSTRect();

		if (m_StarWait > 0)
		{
			if (prec.CollisionRect(esrec))
			{
				ene.StepOnShel(m_bReverse, true);
				return true;
			}
		}
		for (int i = 0; i < FIREBALL_COUNT; i++)
		{
			if (!m_FireBallArray[i].GetShow())
			{
				continue;
			}
			CRectangle fr = m_FireBallArray[i].GetRect();
			if (fr.CollisionRect(esrec))
			{
				ene.StepOnShel(m_bReverse, true);
				m_FireBallArray[i].Hit();
			}
		}
		if (pbrec.CollisionRect(estrec))
		{
			m_Sound3.Play();
			bool Rev = false;
			if (pbrec.Left > estrec.Left)
				Rev = true;
			ene.StepOnShel(Rev, false);
			// ���܂���������y�������炷
			int Buried = pbrec.Bottom - estrec.Top - 1;
			m_PosY -= Buried;
			if (g_pInput->IsKeyHold(MOFKEY_Z))
				m_MoveY = PLAYER_JUMP * 1.1f;
			else
				m_MoveY = PLAYER_JUMP * 0.8f;
			return true;
		}
		else if (m_DamageWait == 0 && prec.CollisionRect(esrec))
		{
			if (ene.GetSMoveX() == 0)
			{
				bool Rev = false;
				if (pbrec.Left > etrec.Left)
					Rev = true;
				ene.StepOnShel(Rev, false);
				return true;
			}
			else
			{
				m_HP -= 1;
				m_DamageWait = 120;
				return true;
			}
		}
	}
	return false;
}

bool CPlayer::CollisionItem(CItem& itm) {
	if (!itm.GetShow() || itm.GetIn())
	{
		return false;
	}
	//�A�C�e���̋�`�Ǝ����̋�`�œ����蔻��
	CRectangle prec = GetRect();
	CRectangle irec = itm.GetRect();
	if (prec.CollisionRect(irec))
	{
		itm.SetShow(false);
		switch (itm.GetType())
		{
		case ITEM_MUSHROOM:
			if (m_HP == 1)
				m_Sound1.Play();
			if (m_HP < 2)
				m_HP = 2;
			break;
		case ITEM_FLOWER:
			if (m_HP != 3)
				m_Sound1.Play();
			m_HP = 3;
			break;
		case ITEM_STAR:
			m_StarWait = 600;
			break;
		}
		return true;
	}
	return false;
}

/**
	*�`��
	*
	* ����
	* [in]					wx					���[���h�̕ω�
	* [in]					wy					���[���h�̕ω�
	*/

void CPlayer::Render(float wx, float wy) {
	for (int i = 0; i < FIREBALL_COUNT; i++)
	{
		m_FireBallArray[i].Render(wx, wy);
	}
	if (m_DamageWait % 4 >= 2)
	{
		return;
	}
	// �`���`
	CRectangle dr = m_SrcRect;

	// �`��ʒu
	float px = m_PosX - wx;
	float py = m_PosY - wy;

	// ���]�t���O��ON�̏ꍇ�A�`���`�𔽓]������
	if (m_bReverse)
	{
		float tmp = dr.Right;
		dr.Right = dr.Left;
		dr.Left = tmp;
	}

	// �e�N�X�`���̕`��
	if (m_StarWait % 12 <= 6)
		m_Texture.Render(px, py, dr);
	else
	{
		m_Texture.Render(px, py, dr, MOF_XRGB(255, 255, 0));
	}
}

void CPlayer::RenderDebug(float wx, float wy) {
	/**
	*�`��
	*
	* ����
	* [in]					wx					���[���h�̕ω�
	* [in]					wy					���[���h�̕ω�
	*/

	// �ʒu�̕`��
	CGraphicsUtilities::RenderString(10, 70, "�v���C���[�ʒu X : %.0f , Y : %.0f", m_PosX, m_PosY);
	CGraphicsUtilities::RenderString(10, 200, "�}�X%0.f", m_PosX / 32);

	// �����蔻��̕\��
	CRectangle hr = GetRect();
	CRectangle br = GetBRect();
	CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_COLOR_GREEN);
	CGraphicsUtilities::RenderRect(br.Left - wx, br.Top - wy, br.Right - wx, br.Bottom - wy, MOF_COLOR_RED);

	for (int i = 0; i < FIREBALL_COUNT; i++)
	{
		m_FireBallArray[i].RenderDebug(wx, wy);
	}
}

void CPlayer::Release() {
	m_Texture.Release();
	m_Sound1.Release();
	m_Sound2.Release();
	m_Sound3.Release();
}