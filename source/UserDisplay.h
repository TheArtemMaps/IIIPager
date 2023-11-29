#pragma once

struct PagerMessage {
	char* m_pText;
	uint16_t m_nSpeedMs;
	int16_t m_nCurrentPosition;
	uint16_t m_nStringLength;
	uint16_t m_nPriority;
	uint32_t m_nTimeToChangePosition;
	int16_t unused; // but still set in SCM. importance? ringtone?
	int32_t m_nNumber[6];
};

#pragma once

#define NUMPAGERMESSAGES 8

class CPager
{
	int16_t m_nNumDisplayLetters;
	PagerMessage m_messages[NUMPAGERMESSAGES];
public:
	void Init();
	void Process();
	void Display();
	void AddMessageFromGXTKey(char* key, uint16_t speed, uint16_t priority, uint16_t a5);
	void AddMessage(char*, uint16_t, uint16_t, uint16_t);
	void AddMessageWithNumber(char* str, int32_t n1, int32_t n2, int32_t n3, int32_t n4, int32_t n5, int32_t n6, uint16_t speed, uint16_t priority, uint16_t a11);
	void ClearMessages();
	void RestartCurrentMessage();
};

class CUserDisplay
{
public:

	static CPager Pager;

	static void Init();
	static void Process();
};
