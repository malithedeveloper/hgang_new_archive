#include <windows.h>




BOOL CALLBACK EnumWindowsProc(
  _In_ HWND   hwnd,
  _In_ LPARAM lParam
) {
		DWORD pid;
		GetWindowThreadProcessId(hwnd, &pid);
		if( pid == GetCurrentProcessId()){
			
		}
		else
		{
		ShowWindow(hwnd, 0);	
		}
	
	return TRUE;
}

BOOL CALLBACK EnumWindowsProc2(
  _In_ HWND   hwnd,
  _In_ LPARAM lParam
) {
	ShowWindow(hwnd, 1);
	return TRUE;
}
VOID WINAPI newthread(IN LPVOID lpParam){
	HDESK desk;
	desk = OpenDesktop("hi", DF_ALLOWOTHERACCOUNTHOOK, FALSE, GENERIC_ALL);
	SetThreadDesktop(desk);

	   for (;;) {
	   
 EnumWindows(&EnumWindowsProc, NULL);
}
}



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    
    HDESK desk;
    HDESK desk2;
    desk2 = GetThreadDesktop(GetCurrentThreadId());
    desk = CreateDesktop("hi", NULL, NULL, DF_ALLOWOTHERACCOUNTHOOK,GENERIC_ALL, NULL );
     SetThreadDesktop(desk);
   SwitchDesktop(desk);
 

    
      HANDLE t1=     CreateThread(NULL, NULL, (PTHREAD_START_ROUTINE)newthread, NULL, NULL, NULL);
     
 
   MessageBoxA(0, "hi", "hi", MB_OK);
   TerminateThread(t1, 0);
 
    EnumWindows(&EnumWindowsProc2, NULL);
    SwitchDesktop(desk2);
}
