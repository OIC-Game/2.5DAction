#include "InputManager.h"

void CInputManager::Refresh() {
	for (int i = 1; i < 5; i++)
	{
		pad[i - 1].RefreshKey();
		key[i].Horizontal = 0;
		key[i].Vertical = 0;
		for (int j = 0; j < 10; j++)
		{
			key[i].prev[j] = key[i].now[j];
			key[i].now[j] = false;
		}

		if (pad[i - 1].IsKeyHold(XINPUT_DP_LEFT))
		{
			key[i].Horizontal = -1;
		}
		else if (pad[i - 1].IsKeyHold(XINPUT_DP_RIGHT))
		{
			key[i].Horizontal = 1;
		}
		else
		{
			key[i].Horizontal = pad[i - 1].GetStickHorizontal();
		}

		if (pad[i - 1].IsKeyHold(XINPUT_DP_UP))
		{
			key[i].Vertical = 1;
		}
		else if (pad[i - 1].IsKeyHold(XINPUT_DP_DOWN))
		{
			key[i].Vertical = -1;
		}
		else
		{
			key[i].Vertical = pad[i - 1].GetStickVertical();
		}

		key[i].now[0] = pad[i - 1].IsKeyHold(XINPUT_A);
		key[i].now[1] = pad[i - 1].IsKeyHold(XINPUT_B);
		key[i].now[2] = pad[i - 1].IsKeyHold(XINPUT_X);
		key[i].now[3] = pad[i - 1].IsKeyHold(XINPUT_Y);
		key[i].now[4] = pad[i - 1].IsKeyHold(XINPUT_L_BTN);
		key[i].now[5] = pad[i - 1].IsKeyHold(XINPUT_R_BTN);
		key[i].now[6] = pad[i - 1].IsKeyHold(XINPUT_LS_PUSH);
		key[i].now[7] = pad[i - 1].IsKeyHold(XINPUT_RS_PUSH);
		key[i].now[8] = pad[i - 1].IsKeyHold(XINPUT_START);
		key[i].now[9] = pad[i - 1].IsKeyHold(XINPUT_BACK);

	}

	key[0].Horizontal = 0;
	key[0].Vertical = 0;
	for (int j = 0; j < 10; j++)
	{
		key[0].prev[j] = key[0].now[j];
		key[0].now[j] = false;
	}
	if (g_pInput->IsKeyHold(MOFKEY_LEFT))
	{
		key[0].Horizontal = -1;
	}
	else if (g_pInput->IsKeyHold(MOFKEY_RIGHT))
	{
		key[0].Horizontal = 1;
	}

	if (g_pInput->IsKeyHold(MOFKEY_UP))
	{
		key[0].Vertical = 1;
	}
	else if (g_pInput->IsKeyHold(MOFKEY_DOWN))
	{
		key[0].Vertical = -1;
	}
	if (g_pInput->IsKeyHold(MOFKEY_X))
	{
		key[0].now[0] = true;
	}
	if (g_pInput->IsKeyHold(MOFKEY_Z))
	{
		key[0].now[1] = true;
	}
	if (g_pInput->IsKeyHold(MOFKEY_A))
	{
		key[0].now[2] = true;
	}
	if (g_pInput->IsKeyHold(MOFKEY_S))
	{
		key[0].now[3] = true;
	}
	if (g_pInput->IsKeyHold(MOFKEY_D))
	{
		key[0].now[4] = true;
	}
	if (g_pInput->IsKeyHold(MOFKEY_C))
	{
		key[0].now[5] = true;
	}
	if (g_pInput->IsKeyHold(MOFKEY_LSHIFT))
	{
		key[0].now[6] = true;
	}
	if (g_pInput->IsKeyHold(MOFKEY_CAPSLOCK))
	{
		key[0].now[7] = true;
	}
	if (g_pInput->IsKeyHold(MOFKEY_SPACE))
	{
		key[0].now[8] = true;
	}
	if (g_pInput->IsKeyHold(MOFKEY_RETURN))
	{
		key[0].now[9] = true;
	}

	// CPU‚Í—”‚Å‹^Ž—“I‚ÉŽÀ‘•
	if (CPUTime > 0)
	{
		CPUTime--;
		return;
	}
	key[5].Horizontal = (float)(rand() % 200 - 100) / 100;
	key[5].Vertical = (float)(rand() % 200 - 100) / 100;
	for (int i = 0; i < 10; i++)
	{
		key[5].prev[i] = key[5].now[i];
		key[5].now[i] = false;
	}
	key[5].now[0] = (rand() % 5 <= 3) ? true : false;
	key[5].now[1] = (rand() % 5 <= 3) ? true : false;
	key[5].now[2] = (rand() % 20 == 0) ? true : false;
	key[5].now[3] = (rand() % 16 == 0) ? true : false;
	key[5].now[4] = (rand() % 10 == 0) ? true : false;
	key[5].now[5] = (rand() % 10 == 0) ? true : false;
	key[5].now[6] = (rand() % 2 == 0) ? true : false;
	key[5].now[7] = (rand() % 2 == 0) ? true : false;
	key[5].now[8] = false;
	key[5].now[9] = false;
	CPUTime = 24;
}

void CInputManager::SelectVertical(int p, int& no, int count, int min, bool loop) {
	if (p < 0 || p > 4) { return; }
	if (GetVertical(p) < 0.25 && GetInstance().GetVertical(p) > -0.25)
	{
		m_Select[p].m_RemainVerticalGap = 0;
		m_Select[p].m_ContinuousVerticalCount = 0;
	}
	if (m_Select[p].m_RemainVerticalGap > 0)
	{
		m_Select[p].m_RemainVerticalGap--;
		return;
	}
	if (GetVertical(p) > 0.75)
	{
		m_Select[p].m_RemainVerticalGap = m_SelectGap[m_Select[p].m_ContinuousVerticalCount];
		m_Select[p].m_ContinuousVerticalCount++;
		if (m_Select[p].m_ContinuousVerticalCount >= 2)
			m_Select[p].m_ContinuousVerticalCount = 2;

		no--;
		if (no < min)
		{
			if (loop)
				no = (count - 1 < min) ? min : count - 1;
			else
				no = min;
		}
	}
	if (GetVertical(p) < -0.75)
	{
		m_Select[p].m_RemainVerticalGap = m_SelectGap[m_Select[p].m_ContinuousVerticalCount];
		m_Select[p].m_ContinuousVerticalCount++;
		if (m_Select[p].m_ContinuousVerticalCount >= 2)
			m_Select[p].m_ContinuousVerticalCount = 2;

		no++;
		if (no > count - 1)
		{
			if (loop)
				no = min;
			else
				no = count - 1;
		}
	}
}

void CInputManager::SelectHorizontal(int p, int& no, int count, int min, bool loop) {
	if (p < 0 || p > 4) { return; }
	if (GetHorizontal(p) < 0.25 && GetHorizontal(p) > -0.25)
	{
		m_Select[p].m_RemainHorizontalGap = 0;
		m_Select[p].m_ContinuousHorizontalCount = 0;
	}
	if (m_Select[p].m_RemainHorizontalGap > 0)
	{
		m_Select[p].m_RemainHorizontalGap--;
		return;
	}
	if (GetHorizontal(p) > 0.75)
	{
		m_Select[p].m_RemainHorizontalGap = m_SelectGap[m_Select[p].m_ContinuousHorizontalCount];
		m_Select[p].m_ContinuousHorizontalCount++;
		if (m_Select[p].m_ContinuousHorizontalCount >= 2)
			m_Select[p].m_ContinuousHorizontalCount = 2;

		no++;
		if (no > count - 1)
		{
			if (loop)
				no = min;
			else
				no = count - 1;
		}
	}
	if (GetHorizontal(p) < -0.75)
	{
		m_Select[p].m_RemainHorizontalGap = m_SelectGap[m_Select[p].m_ContinuousHorizontalCount];
		m_Select[p].m_ContinuousHorizontalCount++;
		if (m_Select[p].m_ContinuousHorizontalCount >= 2)
			m_Select[p].m_ContinuousHorizontalCount = 2;

		no--;
		if (no < min)
		{
			if (loop)
				no = (count - 1 < min) ? min : count - 1;
			else
				no = min;
		}
	}
}