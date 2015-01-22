/*
 * xdokodemo.h
 */

//listen port
#define PORT_NO		34600


//dekodemo command list
#define CMD_HELLO       0 
#define CMD_FINE        1 
#define CMD_BYE         2 
#define CMD_LEFT_UP     3 
#define CMD_LEFT_DOWN   4 
#define CMD_RIGHT_UP    5 
#define CMD_RIGHT_DOWN  6 
#define CMD_MIDDLE_UP   7 
#define CMD_MIDDLE_DOWN 8 
#define CMD_MOUSE_MOVE  9 
#define CMD_MOUSE_WHEEL 10
#define CMD_KEY_UP      11
#define CMD_KEY_DOWN    12
#define CMD_CLIPBOARD   13
#define CMD_X1_UP       14
#define CMD_X1_DOWN     15
#define CMD_X2_UP       16
#define CMD_X2_DOWN     17

//Windows Key definition
#define VK_BACK       8   
#define VK_TAB        9   
#define VK_CLEAR      12  
#define VK_RETURN     13  
#define VK_SHIFT      16
#define VK_CONTROL    17  
#define VK_MENU       18  
#define VK_PAUSE      19  
#define VK_CAPITAL    20  
#define VK_KANA       21  
#define VK_JUNJA      23  
#define VK_FINAL      24  
#define VK_KANJI      25  
#define VK_CONVERT    28  
#define VK_NONCONVERT 29  
#define VK_ACCEPT     30  
#define VK_MODECHANGE 31  
#define VK_ESCAPE     27  
#define VK_SPACE      32
#define VK_PRIOR      33  
#define VK_NEXT       34  
#define VK_END        35  
#define VK_HOME       36  
#define VK_LEFT       37  
#define VK_UP         38  
#define VK_RIGHT      39  
#define VK_DOWN       40  
#define VK_SELECT     41  
#define VK_PRINT      42  
#define VK_EXECUTE    43  
#define VK_SNAPSHOT   44  
#define VK_INSERT     45  
#define VK_DELETE     46  
#define VK_HELP       47  
//	0-9,A-Z
#define VK_LWIN       91 
#define VK_RWIN       92 
#define VK_APPS       93 
#define VK_NUMPAD0    96 
#define VK_NUMPAD1    97 
#define VK_NUMPAD2    98 
#define VK_NUMPAD3    99 
#define VK_NUMPAD4    100
#define VK_NUMPAD5    101
#define VK_NUMPAD6    102
#define VK_NUMPAD7    103
#define VK_NUMPAD8    104
#define VK_NUMPAD9    105
#define VK_MULTIPLY   106
#define VK_ADD        107
#define VK_SEPARATOR  108
#define VK_SUBTRACT   109
#define VK_DECIMAL    110
#define VK_DIVIDE     111
#define VK_F1         112
#define VK_F2         113
#define VK_F3         114
#define VK_F4         115
#define VK_F5         116
#define VK_F6         117
#define VK_F7         118
#define VK_F8         119
#define VK_F9         120
#define VK_F10        121
#define VK_F11        122
#define VK_F12        123
#define VK_NUMLOCK    144
#define VK_SCROLL     145
#define VK_LSHIFT     160
#define VK_RSHIFT     161
#define VK_LCONTROL   162
#define VK_RCONTROL   163
#define VK_LMENU      164
#define VK_RMENU      165

//dokodemo packet struct
struct command {
	char id[3];
	char cmd;
	unsigned short param1;
	unsigned short param2;
	int param3;
};
