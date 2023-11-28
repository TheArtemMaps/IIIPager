#include "plugin.h"
#include "CHud.h"
#include "Hud.h"

#include "CVehicle.h"
#include "CPed.h"
#include "CStats.h"
#include "CWorld.h"
#include "Timer.h"
#include "UserDisplay.h"
#include "Audio.h"
#include "CText.h"
#include "CDarkel.h"
#include "CCamera.h"
#include "CClock.h"
#include "CPlayerInfo.h"
#include "CTxdStore.h"
#include "CSprite.h"
#include "CPad.h"
#include "CRadar.h"
#include "CMessages.h"
#include "CCutsceneMgr.h"
#include "CAudioEngine.h"
#include "CFont.h"
#define DEFAULT_SCREEN_WIDTH  (640.0f)
#define DEFAULT_SCREEN_HEIGHT (448.0f)
#define SCREEN_STRETCH_Y(a)   ((a) * (float) SCREEN_HEIGHT / DEFAULT_SCREEN_HEIGHT)
#define SCREEN_STRETCH_X(a)   ((a) * (float) SCREEN_WIDTH / DEFAULT_SCREEN_WIDTH)
#define SCREEN_SCALE_AR(a) (a)
#define SCREEN_SCALE_X(a) SCREEN_SCALE_AR(SCREEN_STRETCH_X(a))
#define SCREEN_SCALE_Y(a) SCREEN_STRETCH_Y(a)
#define SCREEN_SCALE_Y(a) SCREEN_STRETCH_Y(a)
#define SCREEN_SCALE_X_FIX(a) SCREEN_SCALE_X(a)
#define SCREEN_SCALE_Y_FIX(a) SCREEN_SCALE_Y(a)
#define SCREEN_STRETCH_X(a)   ((a) * (float) SCREEN_WIDTH / DEFAULT_SCREEN_WIDTH)

#define SCREEN_SCALE_X(a) SCREEN_SCALE_AR(SCREEN_STRETCH_X(a))
#define SCREEN_SCALE_X(a) SCREEN_SCALE_AR(SCREEN_STRETCH_X(a))

#define ARRAY_SIZE(array)                (sizeof(array) / sizeof(array[0]))
char					CHud2::m_PagerMessage[256];
CSprite2d   		    CHud2::Sprites[1];
int16_t PagerTimer;
static unsigned char	PagerOn;
static bool				PagerSoundPlayed;



static const char* const			HudSpriteFilenames[1] = { "pager",};

void CHud2::GetRidOfAllCustomHUDMessages()
{

	CUserDisplay::Pager.ClearMessages();
}

void CHud2::Initialise()
{


	CTxdStore::PushCurrentTxd();
	int32_t slot2 = CTxdStore::AddTxdSlot("pager");
	CTxdStore::LoadTxd(slot2, GAME_PATH((char*)"MODELS\\PAGER.TXD"));
	int32_t slot = CTxdStore::FindTxdSlot("pager");
	CTxdStore::SetCurrentTxd(slot);


		Sprites[0].SetTexture("pager", "");

	CTxdStore::PopCurrentTxd();
	PagerOn = 0;
	PagerTimer = 0;
	PagerSoundPlayed = 0;
	PagerXOffset = 150.0f;
	ReInitialise();
}

void CHud2::ReInitialise()
{
	// Call SA ReInitialise function
	((void(*)())0x588880)();
	CHud2::GetRidOfAllCustomHUDMessages();
	PagerOn = 0;
	PagerTimer = 0;
	PagerSoundPlayed = 0;
	PagerXOffset = 150.0f;
}

void CHud2::Shutdown()
{
	int slot2 = CTxdStore::FindTxdSlot("pager");
	CTxdStore::RemoveTxdSlot(slot2);
		Sprites[0].Delete();
}

void CHud2::SetPagerMessage(char* message)
{
	int i = 0;
	for (i = 0; i < ARRAY_SIZE(m_PagerMessage); i++) {
		if (message[i] == 0)
			break;

		m_PagerMessage[i] = message[i];
	}
	m_PagerMessage[i] = 0;
}

void CHud2::DrawHUD() {
	RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, reinterpret_cast<void*>(rwFILTERLINEARMIPLINEAR));

	RwRenderStateSet(rwRENDERSTATEZTESTENABLE, reinterpret_cast<void*>(0));
	RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, reinterpret_cast<void*>(0));
	RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void*>(1));
	RwRenderStateSet(rwRENDERSTATESRCBLEND, reinterpret_cast<void*>(5));
	RwRenderStateSet(rwRENDERSTATEDESTBLEND, reinterpret_cast<void*>(6));
	RwRenderStateSet(rwRENDERSTATEFOGENABLE, reinterpret_cast<void*>(0));
	RwRenderStateSet(rwRENDERSTATECULLMODE, reinterpret_cast<void*>(1));

	// Pager
	DrawPager();
}

void CHud2::DrawPager() {
	if (!m_PagerMessage[0] && PagerOn == 1) {
		PagerSoundPlayed = false;
		PagerOn = 2;
	}
	if (m_PagerMessage[0] || PagerOn == 2) {
		if (!PagerOn) {
			PagerOn = 1;
			PagerXOffset = 150.0f;
		}
		if (PagerOn == 1) {
			if (PagerXOffset > 0.0f) {
				float fStep = PagerXOffset * 0.1f;
				if (fStep > 10.0f)
					fStep = 10.0f;
				PagerXOffset -= fStep * CTimer::ms_fTimeStep;
			}
			if (!PagerSoundPlayed) {
				AudioEngine.ReportFrontendAudioEvent(46, 0.0f, 1.0f);
				PagerSoundPlayed = 1;
			}
		}
		else if (PagerOn == 2) {
			float fStep = PagerXOffset * 0.1f;
			if (fStep < 2.0f)
				fStep = 2.0f;
			PagerXOffset += fStep;
			if (PagerXOffset > 150.0f) {
				PagerXOffset = 150.0f;
				PagerOn = 0;
			}
		}
		CRGBA PAGER_COLOR(32, 162, 66, 205);
		Sprites[0].Draw(CRect(SCREEN_SCALE_X(26.0f) - SCREEN_SCALE_X_FIX(PagerXOffset), SCREEN_SCALE_Y(27.0f), SCREEN_SCALE_X(160.0f) + SCREEN_SCALE_X(26.0f) - SCREEN_SCALE_X_FIX(PagerXOffset), SCREEN_SCALE_Y(80.0f) + SCREEN_SCALE_Y(27.0f)), CRGBA(255, 255, 255, 255));
			CFont::SetBackground(false, false);
			CFont::SetScale(0.68f * static_cast<float>(RsGlobal.maximumWidth) / DEFAULT_SCREEN_WIDTH,
				1.0f * static_cast<float>(RsGlobal.maximumHeight) / DEFAULT_SCREEN_HEIGHT);
			CFont::SetColor(PAGER_COLOR);
			CFont::m_bFontRightAlign = false;
			CFont::SetBackground(false, false);
			CFont::m_bFontCentreAlign = false;
			CFont::SetWrapx(SCREEN_STRETCH_X(DEFAULT_SCREEN_WIDTH));
			CFont::SetJustify(false);
			//CFont::SetProportional(false);
			CFont::m_bFontPropOn = false;
			CFont::SetDropShadowPosition(1);
			CFont::SetDropColor(CRGBA(0, 0, 0, 255));
			CFont::SetFontStyle(eFontStyle::FONT_PRICEDOWN);
			CFont::PrintString(SCREEN_SCALE_X(52.0f) - SCREEN_SCALE_X_FIX(PagerXOffset), SCREEN_SCALE_Y(54.0f), m_PagerMessage);
		}
	}



