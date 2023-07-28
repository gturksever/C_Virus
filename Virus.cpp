#include <stdio.h>
#include <windows.h>

LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        MSLLHOOKSTRUCT* pMouseStruct = (MSLLHOOKSTRUCT*)lParam;

        
        pMouseStruct->pt.x = GetSystemMetrics(SM_CXSCREEN) - pMouseStruct->pt.x;
        pMouseStruct->pt.y = GetSystemMetrics(SM_CYSCREEN) - pMouseStruct->pt.y;
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

void ReverseMouseCursor() {
    HHOOK hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseHookProc, NULL, 0);
    if (hMouseHook == NULL) {
        printf("Null\n");
        return;
    }
    
    getchar();

    UnhookWindowsHookEx(hMouseHook);
}

void WriteToNotepad(const char* text) {
    HWND hWnd = FindWindowA("Notepad", NULL);
    if (hWnd != NULL) {
        HWND hEdit = FindWindowExA(hWnd, NULL, "Edit", NULL);
        SendMessageA(hEdit, WM_SETTEXT, 0, (LPARAM)text);
    }
}

int main() {
    const char* targetAppName = "notepad.exe";
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);
    int i = 0;
    

    while (1) {
        STARTUPINFO startupInfo;
        PROCESS_INFORMATION processInfo;
        ZeroMemory(&startupInfo, sizeof(startupInfo));
        ZeroMemory(&processInfo, sizeof(processInfo));
        

        if (CreateProcess(NULL, (LPSTR)targetAppName, NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &processInfo)) {
            printf("Great.\n");

           
            const char* text = "Hacked";
            Sleep(100);
            WriteToNotepad(text);
            

            
            WaitForSingleObject(processInfo.hProcess, INFINITE);

            printf("close notepad\n");
            

            CloseHandle(processInfo.hProcess);
            CloseHandle(processInfo.hThread);
        } else {
            printf("none\n");
        }
        i++;
    }

    return 0;
}



