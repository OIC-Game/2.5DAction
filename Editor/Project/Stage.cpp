#include "CStage.h"

CStage::~CStage()
{
}

bool CStage::Load(char* pName) {
	//�e�L�X�g�t�@�C�����J��
	FILE* fp = fopen(pName, "rt");
	if (fp == NULL)
	{
		return false;
	}
	//�t�@�C���̑S�e�ʂ𒲂ׂ�
	//��x�t�@�C���̏I�[�Ɉړ����āA���̈ʒu�𒲂ׂ邱�ƂŃT�C�Y���킩��
	//���׏I�������̓t�@�C���̐擪�Ɉړ����Ė߂��Ă���
	//���������̕��@�ł�����ȃT�C�Y��ǂݍ��ނ��Ƃ͂ł��Ȃ�
	fseek(fp, 0, SEEK_END);
	long fSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	//�t�@�C���T�C�Y�������̃��������m�ۂ���
	//�I�[���܂߂邽�߁{�P���Ă���
	char* pBuffer = (char*)malloc(fSize + 1);
	//�t�@�C����S�ăo�b�t�@�ɓǂݍ���
	//�����Ŏ��ۂɓǂݍ��߂��T�C�Y�𒲂ׂĂ��̏I�[��\0�����
	fSize = fread(pBuffer, 1, fSize, fp);
	pBuffer[fSize] = '\0';
	char* pstr;

	//�e�N�X�`���̓ǂݍ���
	pstr = strtok(pBuffer, ",");
	if (!m_BackTexture.Load(pstr))
	{
		//return false;
	}
	pstr = strtok(NULL, ",");
	if (!m_ChipTexture.Load(pstr))
	{
		//return false;
	}

	//�v���C���[�����ʒu
	pstr = strtok(NULL, ",");
	m_PlayerPosX = atoi(pstr);
	pstr = strtok(NULL, ",");
	m_PlayerPosY = atoi(pstr);
	pstr = strtok(NULL, ",");
	m_PlayerSize = atoi(pstr);

	//�`�b�v�T�C�Y
	pstr = strtok(NULL, ",");
	m_XChipSize = atoi(pstr);
	pstr = strtok(NULL, ",");
	m_YChipSize = atoi(pstr);
	pstr = strtok(NULL, ",");
	m_XChipEditorSize = atoi(pstr);
	pstr = strtok(NULL, ",");
	m_YChipEditorSize = atoi(pstr);
	pstr = strtok(NULL, ",");
	m_bRhombus = atoi(pstr);

	//�}�b�v�̃`�b�v��
	pstr = strtok(NULL, ",");
	m_XChipCount = atoi(pstr);
	pstr = strtok(NULL, ",");
	m_YChipCount = atoi(pstr);
	pstr = strtok(NULL, ",");
	m_LayerCount = atoi(pstr);


	int totalChips = m_XChipCount * m_YChipCount * m_LayerCount;
	//�}�b�v�`�b�v�p�̃������m��
	m_pChipData = (int*)malloc(sizeof(int) * totalChips);
	//�G�z�u�������m��
	m_pEnemyData = (int*)malloc(sizeof(int) * totalChips);
	//�A�C�e���z�u�������m��
	m_pItemData = (int*)malloc(sizeof(int) * totalChips);

	//�`�b�v�f�[�^�̓ǂݍ���
	for (int l = 0; l < m_LayerCount; l++)
	{
		for (int y = 0; y < m_YChipCount; y++)
		{
			for (int x = 0; x < m_XChipCount; x++)
			{
				pstr = strtok(NULL, ",");
				m_pChipData[l * m_XChipCount * m_YChipCount + y * m_XChipCount + x] = atoi(pstr);
			}
		}
	}

	//�G�̃e�N�X�`���ǂݍ���
	pstr = strtok(NULL, ",");
	int ecnt = atoi(pstr);
	for (int i = 0; i < ecnt; i++)
	{
		pstr = strtok(NULL, ",");
		//�ꎞ�ǂݍ��݃e�N�X�`��
		CTexture* tmp = new CTexture();
		//�I�񂾃t�@�C�����J��
		if (!tmp->Load(pstr))
		{
			//return false;
		}
		//�e�N�X�`����z��ɒǉ�����
		m_EnemyTextureArray.Add(&tmp);
	}

	//�z�u�f�[�^�̓ǂݍ���
	m_EnemyCount = 0;
	for (int l = 0; l < m_LayerCount; l++)
	{
		for (int y = 0; y < m_YChipCount; y++)
		{
			for (int x = 0; x < m_XChipCount; x++)
			{
				pstr = strtok(NULL, ",");
				m_pEnemyData[l * m_XChipCount * m_YChipCount + y * m_XChipCount + x] = atoi(pstr);
				if (m_pEnemyData[l * m_XChipCount * m_YChipCount + y * m_XChipCount + x] > 0)
				{
					m_EnemyCount++;
				}
			}
		}
	}

	//�A�C�e���̃e�N�X�`���ǂݍ���
	pstr = strtok(NULL, ",");
	int icnt = atoi(pstr);
	for (int i = 0; i < icnt; i++)
	{
		pstr = strtok(NULL, ",");
		//�ꎞ�ǂݍ��݃e�N�X�`��
		CTexture* tmp = new CTexture();
		//�I�񂾃t�@�C�����J��
		if (!tmp->Load(pstr))
		{
			//return false;
		}
		//�e�N�X�`����z��ɒǉ�����
		m_ItemTextureArray.Add(&tmp);
	}

	//�z�u�f�[�^�̓ǂݍ���
	m_ItemCount = 0;
	for (int l = 0; l < m_LayerCount; l++)
	{
		for (int y = 0; y < m_YChipCount; y++)
		{
			for (int x = 0; x < m_XChipCount; x++)
			{
				pstr = strtok(NULL, ",");
				m_pItemData[l * m_XChipCount * m_YChipCount + y * m_XChipCount + x] = atoi(pstr);
				if (m_pItemData[l * m_XChipCount * m_YChipCount + y * m_XChipCount + x] > 0)
				{
					m_ItemCount++;
				}
			}
		}
	}

	//�M�~�b�N�f�[�^�̓ǂݍ���
	for (int l = 0; l < m_LayerCount; l++)
	{
		for (int y = 0; y < m_YChipCount; y++)
		{
			for (int x = 0; x < m_XChipCount; x++)
			{
				pstr = strtok(NULL, ",");
				m_pGimmickData[l * m_XChipCount * m_YChipCount + y * m_XChipCount + x] = atoi(pstr) - 1;
			}
		}
	}

	//�t�@�C�������
	fclose(fp);
	free(pBuffer);
	return true;
}

/*void CStage::Initialize(CEnemy* pEnemy) {
	m_ScrollX = 0;
	m_ScrollY = 0;
	int n = 0;
	for (int l = 0; l < m_LayerCount; l++)
	{
		for (int y = 0; y < m_YChipCount; y++)
		{
			for (int x = 0; x < m_XChipCount; x++)
			{
				//�z�u�ԍ�
				//�ԍ�0�͔z�u���Ȃ�
				char on = m_pEnemyData[l * m_XChipCount * m_YChipCount + y * m_XChipCount + x] - 1;
				if (on < 0)
				{
					continue;
				}
				//pEnemy[n].SetTexture(m_EnemyTextureArray[on]);
				if (m_bRhombus)
				{
					if (y % 2 == 0)
						pEnemy[n++].Initialize((x + 0.5) * m_XChipEditorSize, y * m_YChipEditorSize / 2, on);
					else
						pEnemy[n++].Initialize(x * m_XChipEditorSize, y * m_YChipEditorSize / 2, on);
				}
				else
					pEnemy[n++].Initialize(x * m_XChipEditorSize, y * m_YChipEditorSize, on);
			}
		}
	}
}*/

void CStage::Update(void) {
}

/*
* �����蔻��
*
* ����
* [in]		r			�����`
* [out]		ox			X���܂�
* [out]		oy			Y���܂�
*/

bool CStage::Collision(CRectangle r, float& ox, float& oy, bool& charge) {
	bool re = false;
	//�����蔻�肷���`�̍���ƉE���̃`�b�v�ʒu�����߂�
	int lc = r.Left / m_XChipEditorSize;
	int rc = r.Right / m_XChipEditorSize;
	int tc = r.Top / m_YChipEditorSize;
	int bc = r.Bottom / m_YChipEditorSize;
	if (m_bRhombus)
	{
		tc = r.Top / m_YChipEditorSize * 2;
		bc = r.Bottom / m_YChipEditorSize * 2;
	}
	//�X�e�[�W�͈̔͊O�ɂ͂Ȃ�Ȃ��悤�ɂ���
	tc--;
	lc--;
	if (lc < 0)
	{
		lc = 0;
	}
	if (tc < 0)
	{
		tc = 0;
	}
	if (rc >= m_XChipCount)
	{
		rc = m_XChipCount - 1;
	}
	if (bc >= m_YChipCount)
	{
		bc = m_YChipCount - 1;
	}

	//�ǂ��̋�`�ɏՓ˂��Ă��邩
	int left = 0;
	int right = 0;
	int top = 0;
	int bottom = 0;
	//��`�����蔻��J�E���g�pfor��
	for (int l = 0; l < m_LayerCount; l++)
	{
		//���C���[�ԍ�1�͓����蔻�肵�Ȃ�
		if (l == 0) { continue; }
		for (int y = tc; y <= bc; y++)
		{
			for (int x = lc; x <= rc; x++)
			{

				//�`�悷��`�b�v�ԍ�
				char cn = m_pChipData[l * m_XChipCount * m_YChipCount + y * m_XChipCount + x] - 1;

				//���C���[�ԍ�2�̔z�u�ς݃`�b�v�A���C���[�ԍ�3�̃��o�[�̓����蔻�����
				if (l == 1 && cn >= 0) { continue; }
				if (l == 2 && cn < 0) { continue; }
				if (l == 2 && (cn == LEVER_OFF1 || cn == LEVER_ON1)) { continue; }

				CRectangle cr = GetStageRect(cn, x, y);

				//�}�b�v�`�b�v�̋�`���l����
				CRectangle rec[4] =
				{
					{cr.Left,cr.Top,cr.Left + cr.GetWidth() / 2,cr.Top + cr.GetHeight() / 2},//����
					{cr.Left + cr.GetWidth() / 2,cr.Top,cr.Right,cr.Top + cr.GetHeight() / 2},//�E��
					{cr.Left,cr.Top + cr.GetHeight() / 2,cr.Left + cr.GetWidth() / 2,cr.Bottom},//����
					{cr.Left + cr.GetWidth() / 2,cr.Top + cr.GetHeight() / 2,cr.Right,cr.Bottom}//�E��
				};

				//�����蔻��p�̃L�����N�^��`
				//���Ŕ͈͂����肵����p�̋�`���쐬����B
				CRectangle brec = r;
				brec.Top = brec.Bottom - brec.GetHeight() / 4;	//���̋�`�͏㑤�����Ɠ����l�ɂ���
				brec.Expansion(-6, 0);

				//���Ɠ����蔻��
				if (rec[0].CollisionRect(brec))//����
				{
					float FillValue = brec.Bottom - rec[0].Top; // �ǂꂾ�����܂�����
					float FillPercentage = FillValue / rec[0].GetHeight(); // ���܂�������
					float WidthHeight = rec[0].GetWidth() * FillPercentage; // ���̍����̉���
					float ReturnValue = rec[0].Right - WidthHeight - brec.Right;
					if (ReturnValue < 0)
					{
						left++;
						top++;
					}
				}
				if (rec[1].CollisionRect(brec))//�E��
				{
					float FillValue = brec.Bottom - rec[1].Top; // �ǂꂾ�����܂�����
					float FillPercentage = FillValue / rec[1].GetHeight(); // ���܂�������
					float WidthHeight = rec[1].GetWidth() * FillPercentage; // ���̍����̉���
					float ReturnValue = rec[1].Left + WidthHeight - brec.Left;
					if (ReturnValue > 0)
					{
						right++;
						top++;
					}
				}
				if (rec[2].CollisionRect(brec))//����
				{
					float FillValue = rec[2].Bottom - brec.Top; // �ǂꂾ�����܂�����
					float FillPercentage = FillValue / rec[2].GetHeight(); // ���܂�������
					float WidthHeight = rec[2].GetWidth() * FillPercentage; // ���̍����̉���
					float ReturnValue = rec[2].Right - WidthHeight - brec.Right;
					if (ReturnValue < 0)
					{
						left++;
						bottom++;
					}
				}
				if (rec[3].CollisionRect(brec))//�E��
				{
					float FillValue = rec[3].Bottom - brec.Top; // �ǂꂾ�����܂�����
					float FillPercentage = FillValue / rec[3].GetHeight(); // ���܂�������
					float WidthHeight = rec[3].GetWidth() * FillPercentage; // ���̍����̉���
					float ReturnValue = rec[3].Left + WidthHeight - brec.Left;
					if (ReturnValue > 0)
					{
						right++;
						bottom++;
					}
				}
			}
		}
	}
	//��`�����蔻��v�Z�pfor��
	for (int l = 0; l < m_LayerCount; l++)
	{
		//���C���[�ԍ�1�͓����蔻�肵�Ȃ�
		if (l == 0) { continue; }
		for (int y = tc; y <= bc; y++)
		{
			for (int x = lc; x <= rc; x++)
			{

				//�`�悷��`�b�v�ԍ�
				char cn = m_pChipData[l * m_XChipCount * m_YChipCount + y * m_XChipCount + x] - 1;

				//���C���[�ԍ�2�̔z�u�ς݃`�b�v�A���C���[�ԍ�3�̃��o�[�̓����蔻�����
				if (l == 1 && cn >= 0) { continue; }
				if (l == 2 && cn < 0) { continue; }
				if (l == 2 && (cn == LEVER_OFF1 || cn == LEVER_ON1)) { continue; }

				CRectangle cr = GetStageRect(cn, x, y);

				//�}�b�v�`�b�v�̋�`���l����
				CRectangle rec[4] =
				{
					{cr.Left,cr.Top,cr.Left + cr.GetWidth() / 2,cr.Top + cr.GetHeight() / 2},//����
					{cr.Left + cr.GetWidth() / 2,cr.Top,cr.Right,cr.Top + cr.GetHeight() / 2},//�E��
					{cr.Left,cr.Top + cr.GetHeight() / 2,cr.Left + cr.GetWidth() / 2,cr.Bottom},//����
					{cr.Left + cr.GetWidth() / 2,cr.Top + cr.GetHeight() / 2,cr.Right,cr.Bottom}//�E��
				};

				//�����蔻��p�̃L�����N�^��`
				//���Ŕ͈͂����肵����p�̋�`���쐬����B
				CRectangle brec = r;
				brec.Top = brec.Bottom - brec.GetHeight() / 4;
				brec.Expansion(-6, 0);
				if (left > 0 && left == right && cr.CollisionRect(brec))
				{
					if (top > bottom)
					{
						float FillValue = brec.Right - rec[0].Left; // �ǂꂾ�����܂�����
						float FillPercentage = FillValue / rec[0].GetWidth(); // ���܂�������
						if (FillPercentage > 2)
							FillPercentage -= 2;
						else if (FillPercentage > 1)
							FillPercentage = 1;
						float WidthHeight = rec[0].GetHeight() * FillPercentage; // ���̍����̉���
						float ReturnValue = brec.Bottom + WidthHeight - rec[0].Bottom;//rec[0].Bottom - c - brec.Bottom;
						if (ReturnValue > 0)
						{
							oy -= ReturnValue;
							re = true;
						}
					}
					else
					{
						float FillValue = brec.Right - rec[2].Left; // �ǂꂾ�����܂�����
						float FillPercentage = FillValue / rec[2].GetWidth(); // ���܂�������
						if (FillPercentage > 2)
							FillPercentage -= 2;
						else if (FillPercentage > 1)
							FillPercentage = 1;
						float WidthHeight = rec[2].GetHeight() * FillPercentage; // ���̍����̉���
						float ReturnValue = brec.Top - WidthHeight - rec[2].Top;//rec[0].Bottom - c - brec.Bottom;
						if (ReturnValue < 0)
						{
							oy -= ReturnValue;
							re = true;
						}
					}
				}
				//���Ɠ����蔻��
				else if (rec[0].CollisionRect(brec))//����
				{
					float FillValue = brec.Bottom - rec[0].Top; // �ǂꂾ�����܂�����
					float FillPercentage = FillValue / rec[0].GetHeight(); // ���܂�������
					float WidthHeight = rec[0].GetWidth() * FillPercentage; // ���̍����̉���
					float ReturnValue = rec[0].Right - WidthHeight - brec.Right;
					if (ReturnValue < 0)
					{
						ox += ReturnValue;
						re = true;
					}
				}
				else if (rec[1].CollisionRect(brec))//�E��
				{
					float FillValue = brec.Bottom - rec[1].Top; // �ǂꂾ�����܂�����
					float FillPercentage = FillValue / rec[1].GetHeight(); // ���܂�������
					float WidthHeight = rec[1].GetWidth() * FillPercentage; // ���̍����̉���
					float ReturnValue = rec[1].Left + WidthHeight - brec.Left;
					if (ReturnValue > 0)
					{
						ox += ReturnValue;
						re = true;
					}
				}
				else if (rec[2].CollisionRect(brec) && (left == 1 && right == 3 && top == 1 && bottom == 3) == false)//����
				{
					float FillValue = rec[2].Bottom - brec.Top; // �ǂꂾ�����܂�����
					float FillPercentage = FillValue / rec[2].GetHeight(); // ���܂�������
					float WidthHeight = rec[2].GetWidth()* FillPercentage; // ���̍����̉���
					float ReturnValue = rec[2].Right - WidthHeight - brec.Right;
					if (ReturnValue < 0)
					{
						ox += ReturnValue;
						re = true;
					}
				}
				else if (rec[3].CollisionRect(brec))//�E��
				{
					float FillValue = rec[3].Bottom - brec.Top; // �ǂꂾ�����܂�����
					float FillPercentage = FillValue / rec[3].GetHeight(); // ���܂�������
					float WidthHeight = rec[3].GetWidth() * FillPercentage; // ���̍����̉���
					float ReturnValue = rec[3].Left + WidthHeight - brec.Left;
					if (ReturnValue > 0)
					{
						ox += ReturnValue;
						re = true;
					}
				}
				if (re == true && cn == CHARGER)
				{
					charge = true;
				}
			}
		}
	}
	return re;
}

/**
 * �M�~�b�N���Փ˂̔���
 * �Փ˂��Ă��鏰�ɂ���ăM�~�b�N�𔭓�������
 *
 * ����
 * [in]			r					�v���C���[�̋�`
 */
void CStage::CollisionGimmickFloor(CRectangle r) {
	float mx = (r.Left + r.Right) / 2;
	float my = (r.Top + r.Bottom) / 2;
	int selX;
	int selY;
	//�����蔻��̋��
	if (m_bRhombus)
	{
		for (int y = 0; y < m_YChipCount; y++)
		{
			float shiftx = 0.5;
			if (y % 2 == 0)
			{
				shiftx = 1;
			}
			for (int x = 0; x < m_XChipCount; x++)
			{
				float p0x = (x + shiftx) * m_XChipEditorSize * m_MapScale;
				float p0y = y * m_YChipEditorSize * m_MapScale / 2;
				float p1x = (x + shiftx + 0.5) * m_XChipEditorSize * m_MapScale;
				float p1y = p0y + m_YChipEditorSize * m_MapScale / 2;
				float p2x = (x + shiftx) * m_XChipEditorSize * m_MapScale;
				float p2y = p0y + m_YChipEditorSize * m_MapScale;
				double Area = 0.5 *(-p1y * p2x + p0y * (-p1x + p2x) + p0x * (p1y - p2y) + p1x * p2y);
				double s = 1 / (2 * Area)*(p0y*p2x - p0x * p2y + (p2y - p0y)*mx + (p0x - p2x)*my);
				double t = 1 / (2 * Area)*(p0x*p1y - p0y * p1x + (p0y - p1y)*mx + (p1x - p0x)*my);

				if (0 < s  && s < 1 && 0 < t && t < 1) {
					if (0 < 1 - s - t && 1 - s - t < 1)
					{
						selY = y;
						selX = x;
					}
				}

				p1x = (x + shiftx - 0.5) * m_XChipEditorSize * m_MapScale;
				Area = 0.5 *(-p1y * p2x + p0y * (-p1x + p2x) + p0x * (p1y - p2y) + p1x * p2y);
				s = 1 / (2 * Area)*(p0y*p2x - p0x * p2y + (p2y - p0y)*mx + (p0x - p2x)*my);
				t = 1 / (2 * Area)*(p0x*p1y - p0y * p1x + (p0y - p1y)*mx + (p1x - p0x)*my);

				if (0 < s  && s < 1 && 0 < t && t < 1) {
					if (0 < 1 - s - t && 1 - s - t < 1)
					{
						selY = y;
						selX = x;
					}
				}
			}
		}
	}
	else
	{
		selX = (int)(m_ScrollX + (mx) / (m_XChipEditorSize * m_MapScale));
		selY = (int)(m_ScrollY + my / (m_YChipEditorSize * m_MapScale));
	}

	int no = m_YChipCount * m_XChipCount + selY * m_XChipCount + selX;
	int cn = m_pChipData[no] - 1;
	int gn = m_pGimmickData[no];
	int gnn = 0;
	if (gn != -1)
	{
		gnn = m_pGimmickData[gn];
	}
	//���o�[�M�~�b�N
	if (cn == REDFLOOR_1 || cn == REDFLOOR_2)
	{
		if (m_pChipData[2 * m_YChipCount * m_XChipCount + selY * m_XChipCount + selX] == 0)
		{
			m_pChipData[2 * m_YChipCount * m_XChipCount + selY * m_XChipCount + selX] = 27 + 1;
		}
		else if (gnn == no)
		{
			m_pChipData[2 * m_YChipCount * m_XChipCount + selY * m_XChipCount + selX] = 28 + 1;
			int cgn = m_pChipData[gn];
			if (cgn == 21)
			{
				m_pChipData[m_pGimmickData[no]] = 22;
			}
			else if (cgn == 23)
			{
				m_pChipData[m_pGimmickData[no]] = 24;
			}
		}
	}
	//���M�~�b�N
	else if (cn == YELLOWFLOOR_1 || cn == YELLOWFLOOR_2)
	{
		BuildBridge(cn, selX, selY);
	}
}

/**
 * ���쐬
 * �ΏۂƂȂ鉩�F�����Ɍ������ċ��𐶐�����
 *
 * ����
 * [in]			cn					�`�b�v�i���o�[
 * [in]			selx				X���W
 * [in]			sely				Y���W
 */
void CStage::BuildBridge(int cn, int selx, int sely) {
	int countBridge = 0;
	int direction = 0;
	int checkno = 0;
	int selX = selx;
	int selY = sely;
	if (cn == YELLOWFLOOR_1)
	{
		do
		{
			if (selY % 2 == 0)
			{
				// �E��
				selY--;
				selX++;
				countBridge++;
			}
			else
			{
				selY--;
				countBridge++;
			}
			int cnn = m_pChipData[m_YChipCount * m_XChipCount + selY * m_XChipCount + selX] - 1;
			if (cnn != -1 || selX > m_XChipCount || selY < 0)
			{
				if (cnn == YELLOWFLOOR_1)
				{
					checkno = 1;
					direction = 1;
				}
				else
				{
					checkno = 2;
				}
			}
		} while (checkno == 0);
		if (checkno == 2)
		{
			checkno = 0;
			selX = selx;
			selY = sely;
			countBridge = 0;
			do
			{
				if (selY % 2 == 0)
				{
					// �E��
					selY++;
					countBridge++;
				}
				else
				{
					selY++;
					selX--;
					countBridge++;
				}
				int cnn = m_pChipData[m_YChipCount * m_XChipCount + selY * m_XChipCount + selX] - 1;
				if (cnn != -1 || selY > m_YChipCount || selX < 0)
				{
					if (cnn == YELLOWFLOOR_1)
					{
						checkno = 1;
						direction = 2;
					}
					else
					{
						checkno = 2;
					}
				}
			} while (checkno == 0);
		}
	}
	else if (cn == YELLOWFLOOR_2)
	{
		do
		{
			if (selY % 2 == 0)
			{
				// ����
				selY--;
				countBridge++;
			}
			else
			{
				selY--;
				selX--;
				countBridge++;
			}
			int cnn = m_pChipData[m_YChipCount * m_XChipCount + selY * m_XChipCount + selX] - 1;
			if (cnn != -1 || selX < 0 || selY < 0)
			{
				if (cnn == YELLOWFLOOR_2)
				{
					checkno = 1;
					direction = 1;
				}
				else
				{
					checkno = 2;
				}
			}
		} while (checkno == 0);
		if (checkno == 2)
		{
			checkno = 0;
			selX = selx;
			selY = sely;
			countBridge = 0;
			do
			{
				if (selY % 2 == 0)
				{
					// �E��
					selY++;
					selX++;
					countBridge++;
				}
				else
				{
					selY++;
					countBridge++;
				}
				int cnn = m_pChipData[m_YChipCount * m_XChipCount + selY * m_XChipCount + selX] - 1;
				if (cnn != -1 || selY > m_YChipCount || selX > m_XChipCount)
				{
					if (cnn == YELLOWFLOOR_2)
					{
						checkno = 1;
						direction = 2;
					}
					else
					{
						checkno = 2;
					}
				}
			} while (checkno == 0);
		}
	}

	// ���̐ݒu
	if (countBridge <= 1 || checkno != 1) { return; }
	selX = selx;
	selY = sely;
	if (cn == YELLOWFLOOR_1)
	{
		for (int i = 0; i < countBridge - 1; i++)
		{
			if (direction == 1)
			{
				if (selY % 2 == 0)
				{
					// �E��
					selY--;
					selX++;
				}
				else
				{
					selY--;
				}
			}
			else if (direction == 2)
			{
				if (selY % 2 == 0)
				{
					// �E��
					selY++;
				}
				else
				{
					selY++;
					selX--;
				}
			}

			if (i == 0)
			{
				if (direction == 1)
					m_pChipData[m_YChipCount * m_XChipCount + selY * m_XChipCount + selX] = BRIDGE_LEFTDOWN;
				else
					m_pChipData[m_YChipCount * m_XChipCount + selY * m_XChipCount + selX] = BRIDGE_LEFTUP;
			}
			else if (i == countBridge - 2)
			{
				if (direction == 1)
					m_pChipData[m_YChipCount * m_XChipCount + selY * m_XChipCount + selX] = BRIDGE_LEFTUP;
				else
					m_pChipData[m_YChipCount * m_XChipCount + selY * m_XChipCount + selX] = BRIDGE_LEFTDOWN;
			}
			else
			{
				m_pChipData[m_YChipCount * m_XChipCount + selY * m_XChipCount + selX] = BRIDGE_LEFTMIDDLE;
			}
		}
	}
	else if (cn == YELLOWFLOOR_2)
	{
		for (int i = 0; i < countBridge - 1; i++)
		{
			if (direction == 1)
			{
				if (selY % 2 == 0)
				{
					// �E��
					selY--;
				}
				else
				{
					selY--;
					selX--;
				}
			}
			else if (direction == 2)
			{
				if (selY % 2 == 0)
				{
					// �E��
					selY++;
					selX++;
				}
				else
				{
					selY++;
				}
			}

			if (i == 0)
			{
				if (direction == 1)
					m_pChipData[m_YChipCount * m_XChipCount + selY * m_XChipCount + selX] = BRIDGE_RIGHTDOWN;
				else
					m_pChipData[m_YChipCount * m_XChipCount + selY * m_XChipCount + selX] = BRIDGE_RIGHTUP;
			}
			else if (i == countBridge - 2)
			{
				if (direction == 1)
					m_pChipData[m_YChipCount * m_XChipCount + selY * m_XChipCount + selX] = BRIDGE_RIGHTUP;
				else
					m_pChipData[m_YChipCount * m_XChipCount + selY * m_XChipCount + selX] = BRIDGE_RIGHTDOWN;
			}
			else
			{
				m_pChipData[m_YChipCount * m_XChipCount + selY * m_XChipCount + selX] = BRIDGE_RIGHTMIDDLE;
			}
		}
	}
}

/**
 * PC�ݒu
 * PC���ݒu����Ă��Ȃ�����PC��ݒu����
 *
 * ����
 * [in]			selx				X���W
 * [in]			sely				Y���W
 */
void CStage::SetPC(int selx, int sely) {
	int selX = selx;
	int selY = sely;

	if (selY % 2 == 0)
	{
		// �E��
		selY--;
		selX++;
	}
	else
	{
		selY--;
	}
	int no = 2 * m_YChipCount * m_XChipCount + selY * m_XChipCount + selX;

	int cn = m_pChipData[no];
	if (cn == DESC)
	{
		m_pChipData[no] = PCDESC;
	}
}

void CStage::Render() {
	// �e�N�X�`���̉�������}�b�v�`�b�v�̏c�I�t�Z�b�g�����߂�
	int tcx = m_ChipTexture.GetWidth() / m_XChipSize;
	// �}�b�v�`�b�v�̕`��
	for (int l = 0; l < m_LayerCount; l++)
	{
		for (int y = 0; y < m_YChipCount; y++)
		{
			for (int x = 0; x < m_XChipCount; x++)
			{
				// �`�悷��`�b�v�ԍ�
				// �`�b�v�ԍ�0�͕`�悵�Ȃ�
				char cn = m_pChipData[l * m_XChipCount * m_YChipCount + y * m_XChipCount + x] - 1;
				if (cn + 1 == 0) { continue; }
				// �}�b�v�`�b�v�̋�`
				CRectangle cr(m_XChipSize * (cn % tcx), m_YChipSize * (cn / tcx), m_XChipSize * (cn % tcx + 1), m_YChipSize * (cn / tcx + 1));
				// �}�b�v�`�b�v�̕`��
				if (m_bRhombus)
				{
					if (y % 2 == 0)
					{
						m_ChipTexture.Render(-m_ScrollX + (x + 0.5) * m_XChipEditorSize - (m_XChipSize - m_XChipEditorSize), -m_ScrollY + y * m_YChipEditorSize / 2 - (m_YChipSize - m_YChipEditorSize), cr);
					}
					else
					{
						m_ChipTexture.Render(-m_ScrollX + x * m_XChipEditorSize - (m_XChipSize - m_XChipEditorSize), -m_ScrollY + y * m_YChipEditorSize / 2 - (m_YChipSize - m_YChipEditorSize), cr);
					}
				}
				else
				{
					m_ChipTexture.Render(-m_ScrollX + x * m_XChipEditorSize - (m_XChipSize - m_XChipEditorSize), -m_ScrollY + y * m_YChipEditorSize - (m_YChipSize - m_YChipEditorSize), cr);
				}
			}
		}
	}
}

void CStage::RenderFrontWall(void) {
	// �e�N�X�`���̉�������}�b�v�`�b�v�̏c�I�t�Z�b�g�����߂�
	int tcx = m_ChipTexture.GetWidth() / m_XChipSize;
	// �}�b�v�`�b�v�̕`��
	for (int l = 0; l < m_LayerCount; l++)
	{
		for (int y = 0; y < m_YChipCount; y++)
		{
			for (int x = 0; x < m_XChipCount; x++)
			{
				// �`�悷��`�b�v�ԍ�
				// �`�b�v�ԍ�36,41,42�ȊO�͕`�悵�Ȃ�
				char cn = m_pChipData[l * m_XChipCount * m_YChipCount + y * m_XChipCount + x] - 1;
				if (cn == 36 || cn == 41 || cn == 42)
				{
					// �}�b�v�`�b�v�̋�`
					CRectangle cr(m_XChipSize * (cn % tcx), m_YChipSize * (cn / tcx), m_XChipSize * (cn % tcx + 1), m_YChipSize * (cn / tcx + 1));
					// �}�b�v�`�b�v�̕`��
					if (m_bRhombus)
					{
						if (y % 2 == 0)
						{
							m_ChipTexture.Render(-m_ScrollX + (x + 0.5) * m_XChipEditorSize - (m_XChipSize - m_XChipEditorSize), -m_ScrollY + y * m_YChipEditorSize / 2 - (m_YChipSize - m_YChipEditorSize), cr);
						}
						else
						{
							m_ChipTexture.Render(-m_ScrollX + x * m_XChipEditorSize - (m_XChipSize - m_XChipEditorSize), -m_ScrollY + y * m_YChipEditorSize / 2 - (m_YChipSize - m_YChipEditorSize), cr);
						}
					}
					else
					{
						m_ChipTexture.Render(-m_ScrollX + x * m_XChipEditorSize - (m_XChipSize - m_XChipEditorSize), -m_ScrollY + y * m_YChipEditorSize - (m_YChipSize - m_YChipEditorSize), cr);
					}
				}
				else
				{
					continue;
				}
			}
		}
	}
}

void CStage::RenderDebug(void) {
}

void CStage::Release() {
	m_ChipTexture.Release();
	m_BackTexture.Release();
	if (m_pChipData)
	{
		free(m_pChipData);
		m_pChipData = NULL;
	}
}