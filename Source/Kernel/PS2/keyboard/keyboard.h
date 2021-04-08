#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_


unsigned char commandKeyboard(unsigned char byte);

unsigned char readKeyboard();

int initKeyboard();

unsigned char ScancodeToKeyCode(unsigned char scancode, int e0, int prntscrn, int pause);

unsigned char KeyCodeToASCII(unsigned char KeyCode, int isShift, int isAlt);

char KeyCodeToScancode8[256];

char ScancodeToKeyCode8[256];

char KeyCodeToScancode16[256];

char ScancodeToKeyCode16[256];

char KeyCodeToASCII8[256];

char KeyCodeToASCIIShift8[256];

char KeyPressed[256];

enum KeyCodes 
{
	ESC = 1, 
	F1 = 2,
	F2 = 3,
	F3 = 4,
	F4 = 5,
	F5 = 6,
	F6 = 7,
	F7 = 8,
	F8 = 9,
	F9 = 10,
	F10 = 11,
	F11 = 12,
	F12 = 13,
	PRNTSCRN = 14,
	SCROLL = 15,
	PAUSE = 16,
	GRAVE_ACCENT = 32,
	N1 = 33,
	N2 = 34,
	N3 = 35,
	N4 = 36,
	N5 = 37,
	N6 = 38,
	N7 = 39,
	N8 = 40,
	N9 = 41,
	N0 = 42,
	HYPHEN = 43,
	EQUALS = 44,
	BCKSPC = 45,
	INSERT = 46,
	HOME = 47,
	PAGE_UP = 48,
	NUM_LOCK = 49,
	KEYDIV = 50,
	KEYMUL = 51,
	KEYSUB = 52,
	TAB = 64,
	CQ = 65,
	CW = 66,
	CE = 67,
	CR = 68,
	CT = 69,
	CY = 70,
	CU = 71,
	CI = 72,
	CO = 73,
	CP = 74,
	LBRACKET = 75,
	RBRACKET = 76,
	DEL = 78,
	END = 79,
	PAGE_DOWN = 80,
	KEYN7 = 81,
	KEYN8 = 82,
	KEYN9 = 83,
	KEYADD = 84,
	CAPS_LOCK = 96,
	CA = 97,
	CS = 98,
	CD = 99,
	CF = 100,
	CG = 101,
	CH = 102,
	CJ = 103,
	CK = 104,
	CL = 105,
	SEMI_COLON = 106,
	APOSTROPHE = 107,
	BACKSLASH = 108,
	ENTER = 109,
	KEYN4 = 113,
	KEYN5 = 114,
	KEYN6 = 115,
	LSHIFT = 128,
	CZ = 129,
	CX = 130,
	CC = 131,
	CV = 132,
	CB = 133,
	CN = 134,
	CM = 135,
	COMMA = 136,
	DOT = 137,
	SLASH = 138,
	RSHIFT = 139,
	UP_KEY = 143,
	KEYN1 = 145,
	KEYN2 = 146,
	KEYN3 = 147,
	KEYENTER = 148,
	LCTRL = 160,
	LWIN = 161,
	LALT = 162,
	SPACE = 163,
	RALT = 164,
	RWIN = 165,
	APPS = 166,
	RCTRL = 167,
	LEFT_KEY = 174,
	DOWN_KEY = 175,
	RIGHT_KEY = 176,
	KEYN0 = 177,
	KEYDOT = 178
};




#endif