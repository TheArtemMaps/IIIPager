#include "plugin.h"

#include "UserDisplay.h"
#include "Hud.h"
#include "MemoryMgr.h"
#include "CText.h"

using namespace plugin;
class IIIPager {
public:
    IIIPager() {
        plugin::Events::initGameEvent += []() {
            CUserDisplay::Init();
            CHud2::Initialise();
            DWORD dwProtect[2];
            Nop(0x4DDE6F, 8);	// Pager sound fix
                VirtualProtect((char*)0x86A470, 0x18, PAGE_EXECUTE_READWRITE, &dwProtect[0]);
         strncpy((char*)0x86A470, "pagerA", 12);
         strncpy((char*)0x86A47C, "pager", 12);
         strncpy((char*)0x86A488, "barOutlineA", 16);
         strncpy((char*)0x86A498, "barOutline", 16);
         //InjectHook(0x7193A0, &CFont2::SetScaleForCurrentLanguage, PATCH_JUMP);
       //  Patch<void*>(0x71985E, CFont2::Sprite);
       //  Patch<void*>(0x719B08, CFont2::Sprite);
        // InjectHook(0x7192C0, &CFont2::FindSubFontCharacter, PATCH_JUMP);
         //call(0x5BA6BD, &LoadFontsHack, PATCH_JUMP);
         //call(0x7189B2, &ReleaseFontsHack, PATCH_JUMP);
     //   patch::RedirectJump(0x719490, CFont2::SetFontStyle);
     //   patch::RedirectJump(0x5BD76A, CFont2::Initialise);
      //  patch::RedirectJump(0x53BBA7, CFont2::Shutdown);
//patch::RedirectJump(0x71A700, CFont2::PrintString);
       // patch::RedirectJump(0x719490, CFont2::SetFontStyle);
       // patch::RedirectJump(0x7195B0, CFont2::SetProportional);
       //  patch::RedirectJump(0x719600, CFont2::SetJustify);
       //  patch::RedirectJump(0x7194D0, CFont2::SetWrapx);
        // patch::RedirectJump(0x7195C0, CFont2::SetBackground);
        // patch::RedirectJump(0x7187C0, CFont2::LoadFontValues);
        // Nop(0x718B64, 6);
         //call(0x7196DB, &CFont::FindSubFontCharacter, PATCH_NOTHING);
         //call(0x719770, &CFont::FindSubFontCharacter, PATCH_NOTHING);
         //call(0x7199C3, &CFont::FindSubFontCharacter, PATCH_NOTHING);
          VirtualProtect((char*)0x86A470, 0x18, dwProtect[0], &dwProtect[1]);
        };
        Events::reInitGameEvent += []() {
            CHud2::ReInitialise();
        };
        Events::drawHudEvent += []() {
            CHud2::DrawPager();
            
        };
        plugin::Events::gameProcessEvent += []() {
            CUserDisplay::Process();
           
           // if (KeyPressed(VK_SHIFT)) {
               // CUserDisplay::Pager.AddMessage(TheText.Get("USJ_ALL"), 140, 2, 0);
           // CUserDisplay::Pager.AddMessageFromGXTKey("USJ_ALL", 140, 2, 0);
               // CUserDisplay::Pager.AddMessageWithNumber("NEEEEEEEEEEEEEEEEE", 1, 1, 1, 1, 1, 1, 140, 2, 0);
               // CUserDisplay::Pager.AddMessage((char*)"From Ryder. Hey busta come at Grove. Some balla niggas attacked us!!!", 140, 2, 0);
          //  }
          //  if (KeyPressed(VK_END)) {
               // CUserDisplay::Pager.ClearMessages();
           // }
        };
        plugin::Events::shutdownRwEvent += []() {
            CHud2::Shutdown();
        };
    }
} _IIIPager;

// Exported function to add messages to players pager through cleo
extern "C" void __declspec(dllexport) AddPagerMessage(char* str, uint16_t speed, uint16_t priority, uint16_t a5)
{
    CUserDisplay::Pager.AddMessage(str, speed, priority, a5);
    return;
}

// Sends a new message to players pager from GXT Table
extern "C" void __declspec(dllexport) AddPagerMessageFromGXTTable(char* key, uint16_t speed, uint16_t priority, uint16_t a5)
{
    CUserDisplay::Pager.AddMessageFromGXTKey(key, speed, priority, a5);
    return;
}

// Sends a new message in which the first string token~1~ is substituted with the specified number to the player's pager
extern "C" void __declspec(dllexport) AddPagerMessageWithNumber(char* str, int32_t n1, int32_t n2, int32_t n3, int32_t n4, int32_t n5, int32_t n6, uint16_t speed, uint16_t priority, uint16_t a11)
{
    CUserDisplay::Pager.AddMessageWithNumber(str, n1, n2, n3, n4, n5, n6, speed, priority, a11);
    return;
}
// Clear pager messages
extern "C" void __declspec(dllexport) ClearPagerMessages()
{
    CUserDisplay::Pager.ClearMessages();
    return;
}
// Restarts current message
extern "C" void __declspec(dllexport) RestartCurrentPagerMessage()
{
    CUserDisplay::Pager.RestartCurrentMessage();
    return;
}
