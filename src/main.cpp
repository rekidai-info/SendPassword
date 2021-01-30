#include <windows.h>
#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

#if defined _M_IX86
# pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
# pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
# pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
# pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif

// https://gist.github.com/tracend/912308
void sendInput(int ch)
{
	std::map<int, int> directInputScanCodes;

	directInputScanCodes['0'] = 0x0B;
	directInputScanCodes['1'] = 0x02;
	directInputScanCodes['2'] = 0x03;
	directInputScanCodes['3'] = 0x04;
	directInputScanCodes['4'] = 0x05;
	directInputScanCodes['5'] = 0x06;
	directInputScanCodes['6'] = 0x07;
	directInputScanCodes['7'] = 0x08;
	directInputScanCodes['8'] = 0x09;
	directInputScanCodes['9'] = 0x0A;

	directInputScanCodes['a'] = 0x1E;
	directInputScanCodes['b'] = 0x30;
	directInputScanCodes['c'] = 0x2E;
	directInputScanCodes['d'] = 0x20;
	directInputScanCodes['e'] = 0x12;
	directInputScanCodes['f'] = 0x21;
	directInputScanCodes['g'] = 0x22;
	directInputScanCodes['h'] = 0x23;
	directInputScanCodes['i'] = 0x17;
	directInputScanCodes['j'] = 0x24;
	directInputScanCodes['k'] = 0x25;
	directInputScanCodes['l'] = 0x26;
	directInputScanCodes['m'] = 0x32;
	directInputScanCodes['n'] = 0x31;
	directInputScanCodes['o'] = 0x18;
	directInputScanCodes['p'] = 0x19;
	directInputScanCodes['q'] = 0x10;
	directInputScanCodes['r'] = 0x13;
	directInputScanCodes['s'] = 0x1F;
	directInputScanCodes['t'] = 0x14;
	directInputScanCodes['u'] = 0x16;
	directInputScanCodes['v'] = 0x2F;
	directInputScanCodes['w'] = 0x11;
	directInputScanCodes['x'] = 0x2D;
	directInputScanCodes['y'] = 0x15;
	directInputScanCodes['z'] = 0x2C;

	directInputScanCodes['-'] = 0x0C;
	directInputScanCodes['='] = 0x0D;
	directInputScanCodes['\t'] = 0x0F;
	directInputScanCodes['@'] = 0x1A;
	directInputScanCodes['['] = 0x1B;
	directInputScanCodes['\n'] = 0x1C;
	directInputScanCodes[';'] = 0x27;
	directInputScanCodes[':'] = 0x28;
	directInputScanCodes[']'] = 0x2B;
	directInputScanCodes[','] = 0x33;
	directInputScanCodes['.'] = 0x34;
	directInputScanCodes['/'] = 0x35;
	directInputScanCodes['*'] = 0x37;
	directInputScanCodes[' '] = 0x39;

	directInputScanCodes['!'] = 0x02;
	directInputScanCodes['"'] = 0x03;
	directInputScanCodes['#'] = 0x04;
	directInputScanCodes['$'] = 0x05;
	directInputScanCodes['%'] = 0x06;
	directInputScanCodes['&'] = 0x07;
	directInputScanCodes['\''] = 0x08;
	directInputScanCodes['('] = 0x09;
	directInputScanCodes[')'] = 0x0A;
	directInputScanCodes['<'] = 0x33;
	directInputScanCodes['>'] = 0x34;
	directInputScanCodes['?'] = 0x35;

	if (std::isupper(ch) || ch == '!' || ch == '"' || ch == '#' || ch == '$' || ch == '%' || ch == '&' || ch == '\'' || ch == '(' || ch == ')' || ch == '<' || ch == '>' || ch == '?') { // 大文字/記号はシフトキーダウンする
		INPUT input = {
			INPUT_KEYBOARD,
		};
		input.ki = KEYBDINPUT{
			0,
			0x36, // RSHIFT
			KEYEVENTF_SCANCODE,
			0,
			0
		};
		SendInput(1, &input, sizeof(INPUT));
		Sleep(50);
	}

	INPUT input = {
		INPUT_KEYBOARD,
	};
	input.ki = KEYBDINPUT{
		0,
		static_cast<WORD>(directInputScanCodes[std::tolower(ch)]),
		KEYEVENTF_SCANCODE,
		0,
		0
	};
	SendInput(1, &input, sizeof(INPUT)); // キーダウン
	Sleep(50);

	input.ki.dwFlags |= KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT)); // キーアップ
	Sleep(50);

	if (std::isupper(ch) || ch == '!' || ch == '"' || ch == '#' || ch == '$' || ch == '%' || ch == '&' || ch == '\'' || ch == '(' || ch == ')' || ch == '<' || ch == '>' || ch == '?') { // 大文字/記号はシフトキーアップする
		INPUT input = {
			INPUT_KEYBOARD,
		};
		input.ki = KEYBDINPUT{
			0,
			0x36, // RSHIFT
			KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP,
			0,
			0
		};
		SendInput(1, &input, sizeof(INPUT));
		Sleep(50);
	}
}

void sendInputs(std::wstring s) {
	for (wchar_t& ch : s) {
		sendInput(ch);
	}
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE, LPWSTR cmdLine, int)
{
	std::wifstream wifstr("password.txt");
	if (wifstr.fail() || !wifstr.is_open()) {
		MessageBox(nullptr, L"password.txt ファイルが存在しません", nullptr, MB_ICONERROR);
		return 0;
	}

	std::wstring line;
	std::getline(wifstr, line);

	if (line.empty()) {
		MessageBox(nullptr, L"password.txt ファイルが空です", nullptr, MB_ICONERROR);
		return 0;
	}

	Sleep(3000);

	sendInputs(line);
	sendInput('\n');

	return 0;
}