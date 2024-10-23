#include <windows.h>
#include <psapi.h>
#include <tlhelp32.h>

BOOL
WINAPI
SetPrivilege(
	_In_ HANDLE hToken,
	_In_ PCSTR szPrivilege,
	_In_ BOOL bEnablePrivilege
)
{
	TOKEN_PRIVILEGES tp;
	LUID luid;

	if ( !LookupPrivilegeValueA( NULL, szPrivilege, &luid ) )
	{
		return FALSE;
	}

	tp.PrivilegeCount = 1;
	tp.Privileges[ 0 ].Luid = luid;
	if ( bEnablePrivilege )
		tp.Privileges[ 0 ].Attributes = SE_PRIVILEGE_ENABLED;
	else
		tp.Privileges[ 0 ].Attributes = 0;

	if ( !AdjustTokenPrivileges( hToken, FALSE, &tp, sizeof( TOKEN_PRIVILEGES ), ( PTOKEN_PRIVILEGES )NULL, ( PDWORD )NULL ) )
	{
		return FALSE;
	}

	if ( GetLastError( ) == ERROR_NOT_ALL_ASSIGNED )
	{
		return FALSE;
	}

	return TRUE;
}

void SuspendProcessID(DWORD dwProcessID)
{
    HANDLE hThreadSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    THREADENTRY32 threadEntry;
    threadEntry.dwSize = sizeof(THREADENTRY32);
    BOOL bSuspendThreadRes = Thread32First(hThreadSnapshot, &threadEntry);
    while (bSuspendThreadRes)
    {
        if (threadEntry.th32OwnerProcessID == dwProcessID)
        {
            HANDLE hThread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, threadEntry.th32ThreadID);
            SuspendThread(hThread);
            CloseHandle(hThread);
        }
        bSuspendThreadRes = Thread32Next(hThreadSnapshot, &threadEntry);
    }
    CloseHandle(hThreadSnapshot);
}

void ResumeProcessID(DWORD dwProcessID)
{
    HANDLE hThreadSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    THREADENTRY32 threadEntry;
    threadEntry.dwSize = sizeof(THREADENTRY32);
    BOOL bSuspendThreadRes = Thread32First(hThreadSnapshot, &threadEntry);
    while (bSuspendThreadRes)
    {
        if (threadEntry.th32OwnerProcessID == dwProcessID)
        {
            HANDLE hThread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, threadEntry.th32ThreadID);
            ResumeThread(hThread);
            CloseHandle(hThread);
        }
        bSuspendThreadRes = Thread32Next(hThreadSnapshot, &threadEntry);
    }
    CloseHandle(hThreadSnapshot);
}


void SuspendWinLogon(){
	 HANDLE hToken = NULL;
	 char logon[MAX_PATH];
	 GetSystemDirectoryA(logon, sizeof(logon));
	 lstrcatA(logon, "\\winlogon.exe");
    OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &hToken);
    SetPrivilege(hToken, SE_DEBUG_NAME, TRUE);
     SetPrivilege(hToken, SE_RESTORE_NAME, TRUE);
      SetPrivilege(hToken, SE_BACKUP_NAME, TRUE);
       SetPrivilege(hToken, SE_TAKE_OWNERSHIP_NAME, TRUE);
         SetPrivilege(hToken, SE_SHUTDOWN_NAME, TRUE);
          DWORD aProcesses[1024], cbNeeded, cProcesses;
    unsigned int i;
    if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) )
    {
        return 1;
    }
 cProcesses = cbNeeded / sizeof(DWORD);

    // Print the name and process identifier for each process.

    for ( i = 0; i < cProcesses; i++ )
    {
        if( aProcesses[i] != 0 )
        {
             HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_SUSPEND_RESUME |
                                   PROCESS_VM_READ,
                                   FALSE, aProcesses[i] );
                                   char name[MAX_PATH];
                                   GetModuleFileNameExA(hProcess, NULL, name, sizeof(name));
                                   if (lstrcmpiA(logon, name) == 0){
                                   	SuspendProcessID(aProcesses[i]);
								   }
        }
    }
}

void ResumeWinLogon(){
	 HANDLE hToken = NULL;
	 char logon[MAX_PATH];
	 GetSystemDirectoryA(logon, sizeof(logon));
	 lstrcatA(logon, "\\winlogon.exe");
    OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &hToken);
    SetPrivilege(hToken, SE_DEBUG_NAME, TRUE);
     SetPrivilege(hToken, SE_RESTORE_NAME, TRUE);
      SetPrivilege(hToken, SE_BACKUP_NAME, TRUE);
       SetPrivilege(hToken, SE_TAKE_OWNERSHIP_NAME, TRUE);
         SetPrivilege(hToken, SE_SHUTDOWN_NAME, TRUE);
          DWORD aProcesses[1024], cbNeeded, cProcesses;
    unsigned int i;
    if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) )
    {
        return 1;
    }
 cProcesses = cbNeeded / sizeof(DWORD);

    // Print the name and process identifier for each process.

    for ( i = 0; i < cProcesses; i++ )
    {
        if( aProcesses[i] != 0 )
        {
             HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_SUSPEND_RESUME |
                                   PROCESS_VM_READ,
                                   FALSE, aProcesses[i] );
                                   char name[MAX_PATH];
                                   GetModuleFileNameExA(hProcess, NULL, name, sizeof(name));
                                   if (lstrcmpiA(logon, name) == 0){
                                   	ResumeProcessID(aProcesses[i]);
								   }
        }
    }
}

int main(){
SuspendWinLogon();
Sleep(10000);
ResumeWinLogon();
}