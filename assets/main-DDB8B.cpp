#include <windows.h>




int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
DEVMODE mode;
//first get setting for "current" screen
EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &mode);

if (mode.dmFields | DM_DISPLAYORIENTATION)
{
    mode.dmDisplayOrientation = DMDO_180;
   
     ChangeDisplaySettings(&mode, CDS_UPDATEREGISTRY | CDS_RESET | CDS_GLOBAL);
   
}
}
