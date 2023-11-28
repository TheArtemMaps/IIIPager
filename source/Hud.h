#pragma once

#include "CSprite2d.h"

enum
{
	FLASH_Armourbar = 3,
	FLASH_Healthbar = 4,
	FLASH_Staminabar = 10
};

enum eHudTextures
{
	HUD_Fist,
	HUD_SiteM16,
	HUD_Siterocket,
	HUD_Radardisc,
	HUD_BarInside,
	HUD_BarOutline,
	HUD_Pager,
    HUD_SiteSniper,
    HUD_SiteLaser,
    HUD_LaserDot,
    HUD_Triangle,
    HUD_ViewFinder,
	HUD_NUMBERS,
	NUM_HUD_SPRITES
};

#define UI_SAFEZONE						-FrontEndMenuManager.m_fSafeZone

#define	BAR_ENERGY_LOSS_FLASH_DURATION	2000
#define HUD_TRANSPARENCY_BACK			215
#define HUD_TRANSPARENCY_FRONT			(HUD_TRANSPARENCY_BACK+8)
#define RADAR_RANGE                     100.0f

#define HUD_POS_X						 1.0f
#define HUD_POS_Y						 1.0f

// For 2p HUD
#define HUD_POS_Y_2P_OFFSET				100.0f

//#define COMPILE_SLANTED_TEXT
//#define DRAW_OVERSCAN_720P

class CHud2
{


private:

	static char		m_PagerMessage[256];


public:
	static CSprite2d Sprites[1];

public:
	static void		GetRidOfAllCustomHUDMessages();
	static void		Initialise();
	static void		ReInitialise();
	static void		Shutdown();
	static void DrawHUD();
	static void		SetPagerMessage(char* pMsg);
	static void		DrawPager();
};

