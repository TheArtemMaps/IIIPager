#include "plugin.h"

#include "UserDisplay.h"
#include "Timer.h"
#include "CMessages.h"
#include "CHud.h"
#include "CCamera.h"
#include "Hud.h"
#include "MemoryMgr.h"
#include <game_sa/CText.h>
CPager			CUserDisplay::Pager;
void 
CUserDisplay::Init() {
	Pager.Init();
}

void
CUserDisplay::Process() {
	((void(*)())0x5720A0)();
	Pager.Process();
}

void
CPager::Init()
{
	ClearMessages();
	m_nNumDisplayLetters = 8;
}

void
CPager::Process()
{
	if (m_messages[0].m_pText != NULL && m_messages[0].m_nCurrentPosition >= (int32_t)m_messages[0].m_nStringLength) {
		m_messages[0].m_pText = NULL;
		uint16_t i = 0;
		while (i < NUMPAGERMESSAGES - 1) {
			if (m_messages[i + 1].m_pText == NULL) break;
			m_messages[i] = m_messages[i + 1];
			i++;
		}
		m_messages[i].m_pText = NULL;
		if (m_messages[0].m_pText != NULL)
			CMessages::AddToPreviousBriefArray(
				m_messages[0].m_pText,
				m_messages[0].m_nNumber[0],
				m_messages[0].m_nNumber[1],
				m_messages[0].m_nNumber[2],
				m_messages[0].m_nNumber[3],
				m_messages[0].m_nNumber[4],
				m_messages[0].m_nNumber[5],
				0);
	}
	Display();
	if (m_messages[0].m_pText != NULL) {
		if (TheCamera.m_bWideScreenOn || !CHud::m_Wants_To_Draw_Hud || CHud::m_BigMessage[0][0] || CHud::m_BigMessage[2][0]) {
			RestartCurrentMessage();
		}
		else {
			if (CTimer::m_snTimeInMilliseconds > m_messages[0].m_nTimeToChangePosition) {
				m_messages[0].m_nCurrentPosition++;
				m_messages[0].m_nTimeToChangePosition = CTimer::m_snTimeInMilliseconds + m_messages[0].m_nSpeedMs;
			}
		}
	}
}

void
CPager::Display()
{
	char outstr1[256];
	char outstr2[260];

	char* pText = m_messages[0].m_pText;
	uint16_t i = 0;
	if (pText != NULL) {
		CMessages::InsertNumberInString(
			pText,
			m_messages[0].m_nNumber[0],
			m_messages[0].m_nNumber[1],
			m_messages[0].m_nNumber[2],
			m_messages[0].m_nNumber[3],
			m_messages[0].m_nNumber[4],
			m_messages[0].m_nNumber[5],
			outstr1);
		for (; i < m_nNumDisplayLetters; i++) {
			int pos = m_messages[0].m_nCurrentPosition + i;
			if (pos >= 0) {
				if (!outstr1[pos]) break;

				outstr2[i] = outstr1[pos];
			}
			else {
				outstr2[i] = ' ';
			}
		}
	}
	outstr2[i] = '\0';
	CHud2::SetPagerMessage(outstr2);
}

void
CPager::AddMessage(char* str, uint16_t speed, uint16_t priority, uint16_t a5)
{
	uint16_t size = CMessages::GetStringLength(str);
	for (int32_t i = 0; i < NUMPAGERMESSAGES; i++) {
		if (m_messages[i].m_pText) {
			if (m_messages[i].m_nPriority >= priority)
				continue;

			for (int j = NUMPAGERMESSAGES - 1; j > i; j--)
				m_messages[j] = m_messages[j - 1];

		}
		m_messages[i].m_pText = str;
		m_messages[i].m_nSpeedMs = speed;
		m_messages[i].m_nPriority = priority;
		m_messages[i].unused = a5;
		m_messages[i].m_nCurrentPosition = -(m_nNumDisplayLetters + 10);
		m_messages[i].m_nTimeToChangePosition = CTimer::m_snTimeInMilliseconds + speed;
		m_messages[i].m_nStringLength = size;
		m_messages[i].m_nNumber[0] = -1;
		m_messages[i].m_nNumber[1] = -1;
		m_messages[i].m_nNumber[2] = -1;
		m_messages[i].m_nNumber[3] = -1;
		m_messages[i].m_nNumber[4] = -1;
		m_messages[i].m_nNumber[5] = -1;

		if (i == 0)
			CMessages::AddToPreviousBriefArray(
				m_messages[0].m_pText,
				m_messages[0].m_nNumber[0],
				m_messages[0].m_nNumber[1],
				m_messages[0].m_nNumber[2],
				m_messages[0].m_nNumber[3],
				m_messages[0].m_nNumber[4],
				m_messages[0].m_nNumber[5],
				NULL);
		return;
	}
}

void
CPager::AddMessageFromGXTKey(char* key, uint16_t speed, uint16_t priority, uint16_t a5)
{
	char* text = TheText.Get(key);
	uint16_t size = CMessages::GetStringLength(text);
	for (int32_t i = 0; i < NUMPAGERMESSAGES; i++) {
		if (m_messages[i].m_pText) {
			if (m_messages[i].m_nPriority >= priority)
				continue;

			for (int j = NUMPAGERMESSAGES - 1; j > i; j--)
				m_messages[j] = m_messages[j - 1];

		}
		m_messages[i].m_pText = text;
		m_messages[i].m_nSpeedMs = speed;
		m_messages[i].m_nPriority = priority;
		m_messages[i].unused = a5;
		m_messages[i].m_nCurrentPosition = -(m_nNumDisplayLetters + 10);
		m_messages[i].m_nTimeToChangePosition = CTimer::m_snTimeInMilliseconds + speed;
		m_messages[i].m_nStringLength = size;
		m_messages[i].m_nNumber[0] = -1;
		m_messages[i].m_nNumber[1] = -1;
		m_messages[i].m_nNumber[2] = -1;
		m_messages[i].m_nNumber[3] = -1;
		m_messages[i].m_nNumber[4] = -1;
		m_messages[i].m_nNumber[5] = -1;

		if (i == 0)
			CMessages::AddToPreviousBriefArray(
				m_messages[0].m_pText,
				m_messages[0].m_nNumber[0],
				m_messages[0].m_nNumber[1],
				m_messages[0].m_nNumber[2],
				m_messages[0].m_nNumber[3],
				m_messages[0].m_nNumber[4],
				m_messages[0].m_nNumber[5],
				NULL);
		return;
	}
}

void
CPager::AddMessageWithNumber(char* str, int32_t n1, int32_t n2, int32_t n3, int32_t n4, int32_t n5, int32_t n6, uint16_t speed, uint16_t priority, uint16_t a11)
{
	char nstr[520];

	CMessages::InsertNumberInString(str, n1, n2, n3, n4, n5, n6, nstr);
	uint16_t size = CMessages::GetStringLength(nstr);
	for (int32_t i = 0; i < NUMPAGERMESSAGES; i++) {
		if (m_messages[i].m_pText) {
			if (m_messages[i].m_nPriority >= priority)
				continue;

			for (int j = NUMPAGERMESSAGES - 1; j > i; j--)
				m_messages[j] = m_messages[j - 1];

		}
		m_messages[i].m_pText = str;
		m_messages[i].m_nSpeedMs = speed;
		m_messages[i].m_nPriority = priority;
		m_messages[i].unused = a11;
		m_messages[i].m_nCurrentPosition = -(m_nNumDisplayLetters + 10);
		m_messages[i].m_nTimeToChangePosition = CTimer::m_snTimeInMilliseconds + speed;
		m_messages[i].m_nStringLength = size;
		m_messages[i].m_nNumber[0] = n1;
		m_messages[i].m_nNumber[1] = n2;
		m_messages[i].m_nNumber[2] = n3;
		m_messages[i].m_nNumber[3] = n4;
		m_messages[i].m_nNumber[4] = n5;
		m_messages[i].m_nNumber[5] = n6;

		if (i == 0)
			CMessages::AddToPreviousBriefArray(
				m_messages[0].m_pText,
				m_messages[0].m_nNumber[0],
				m_messages[0].m_nNumber[1],
				m_messages[0].m_nNumber[2],
				m_messages[0].m_nNumber[3],
				m_messages[0].m_nNumber[4],
				m_messages[0].m_nNumber[5],
				NULL);
		return;
	}
}

void
CPager::ClearMessages()
{
	for (int32_t i = 0; i < NUMPAGERMESSAGES; i++)
		m_messages[i].m_pText = NULL;
}

void
CPager::RestartCurrentMessage()
{
	if (m_messages[0].m_pText != NULL) {
		m_messages[0].m_nCurrentPosition = -(m_nNumDisplayLetters + 10);
		m_messages[0].m_nTimeToChangePosition = CTimer::m_snTimeInMilliseconds + m_messages[0].m_nSpeedMs;
	}
}

