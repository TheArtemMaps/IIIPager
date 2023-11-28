#include "plugin.h"

#include "UserDisplay.h"
#include "Hud.h"
#include "MemoryMgr.h"
#include "extensions/ScriptCommands.h"
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
          VirtualProtect((char*)0x86A470, 0x18, dwProtect[0], &dwProtect[1]);
        };
        Events::reInitGameEvent += []() {
            CHud2::ReInitialise();
        };
        Events::drawHudEvent += []() {
           // CHud2::DrawPager();
            CHud2::DrawHUD();
            
        };
        plugin::Events::gameProcessEvent += []() {
            CUserDisplay::Process();
           
           /* if (KeyPressed(VK_SHIFT)) {
               
                CUserDisplay::Pager.AddMessage((char*)"From Ryder. Hey busta come at Grove. Some balla niggas attacked us!!!", 140, 2, 0);
            }
            if (KeyPressed(VK_END)) {
                CUserDisplay::Pager.ClearMessages();
            }*/
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
// Add pager message with numbers (Dunno what this means)
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
