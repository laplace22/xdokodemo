/*
 * dokodemo client soft
 * 
 * dokodemo
 * http://gr-avalon.hp.infoseek.co.jp/dokodemo_desc.html
 * 
 * UDP Programming
 * http://www.katto.comm.waseda.ac.jp/~katto/Class/GazoTokuron/code/socket.html
 * 
 * XTest
 * http://homepage3.nifty.com/tsato/x/xtestlib-j.html
 * 
 * w2xw
 * http://www.h7.dion.ne.jp/~umiumi/
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <X11/keysym.h>
#include <X11/extensions/XTest.h>
#include <string.h>
#include <stdlib.h>

#include "xdokodemo.h"

#define BUFFER_SIZE 256


int chgkey(int mtkey)
{
    switch (mtkey) {
        case VK_BACK:       return XK_BackSpace;
        case VK_TAB:        return XK_Tab;
        case VK_CLEAR:      return XK_Clear;
        case VK_RETURN:     return XK_Return;
        case VK_SHIFT:      return XK_Shift_L;
        case VK_CONTROL:    return XK_Control_L;
        case VK_MENU:       return XK_Alt_L;
        case VK_PAUSE:      return XK_Pause;
        case VK_CAPITAL:    return XK_Caps_Lock;
        case VK_KANA:       return XK_Hiragana_Katakana;
        case VK_KANJI:      return XK_Kanji;
        case VK_CONVERT:    return XK_Henkan;
        case VK_NONCONVERT: return XK_Muhenkan;
//      case VK_JUNJA, VK_FINAL, VK_ACCEPT, VK_MODECHANGE
        case VK_ESCAPE:    return XK_Escape;
        case VK_PRIOR:     return XK_Prior;
        case VK_NEXT:      return XK_Next;
        case VK_END:       return XK_End;
        case VK_HOME:      return XK_Home;
        case VK_LEFT:      return XK_Left;
        case VK_UP:        return XK_Up;
        case VK_RIGHT:     return XK_Right;
        case VK_DOWN:      return XK_Down;
        case VK_PRINT:     return XK_Print;
        case VK_SNAPSHOT:  return XK_Sys_Req;
        case VK_INSERT:    return XK_Insert;
        case VK_DELETE:    return XK_Delete;
        case VK_HELP:      return XK_Help;
        case VK_LWIN:      return XK_F13;
        case VK_RWIN:      return XK_Meta_R;
        case VK_NUMPAD0:   return XK_KP_0;
        case VK_NUMPAD1:   return XK_KP_1;
        case VK_NUMPAD2:   return XK_KP_2;
        case VK_NUMPAD3:   return XK_KP_3;
        case VK_NUMPAD4:   return XK_KP_4;
        case VK_NUMPAD5:   return XK_KP_5;
        case VK_NUMPAD6:   return XK_KP_6;
        case VK_NUMPAD7:   return XK_KP_7;
        case VK_NUMPAD8:   return XK_KP_8;
        case VK_NUMPAD9:   return XK_KP_9;
        case VK_MULTIPLY:  return XK_KP_Multiply;
        case VK_ADD:       return XK_KP_Add;
        case VK_SEPARATOR: return XK_KP_Separator;
        case VK_SUBTRACT:  return XK_KP_Subtract;
        case VK_DECIMAL:   return XK_KP_Decimal;
        case VK_DIVIDE:    return XK_KP_Divide;
        case VK_F1:        return XK_F1;
        case VK_F2:        return XK_F2;
        case VK_F3:        return XK_F3;
        case VK_F4:        return XK_F4;
        case VK_F5:        return XK_F5;
        case VK_F6:        return XK_F6;
        case VK_F7:        return XK_F7;
        case VK_F8:        return XK_F8;
        case VK_F9:        return XK_F9;
        case VK_F10:       return XK_F10;
        case VK_F11:       return XK_F11;
        case VK_F12:       return XK_F12;
        case VK_NUMLOCK:   return XK_Num_Lock;
        case VK_SCROLL:    return XK_Scroll_Lock;
        case VK_LSHIFT:    return XK_Shift_L;
        case VK_RSHIFT:    return XK_Shift_R;
        case VK_LCONTROL:  return XK_Control_L;
        case VK_RCONTROL:  return XK_Control_R;
        case VK_LMENU:     return XK_Alt_L;
        case VK_RMENU:     return XK_Alt_R;
        //common keys
        case 188:          return XK_comma;        // ,
        case 189:          return XK_minus;        // -
        case 190:          return XK_period;       // .
        case 191:          return XK_slash;        // /
        case 219:          return XK_bracketleft;  // [
        case 220:          return XK_bar;          // yen
        case 221:          return XK_bracketright; // ]
        case 226:          return XK_underscore;   // backslash
        case 186:          return XK_colon;        // :
        case 187:          return XK_semicolon;    // ;
        case 192:          return XK_at;           // @
        case 222:          return XK_asciicircum;  // ^
        //Windows fitting
        case 244:          return XK_Kanji;        // hankaku_zenkaku
    }
    return mtkey;
}

void usage(){
    printf(
            "xdokodemo - version 1.0.2\n"
            "usage: xdokodemo [-f ipaddress[/range]] [-p port] [-x]\n"
            "\t-f ipaddress[/range]\n"
            "\t\trestrict ip address\n"
            "\t-p port\n"
            "\t\tUDP port setting\n"
            "\t-x\n"
            "\t\tdpms controling enable(default false)\n");
}

int main(int argc, char *argv[], char *envp[]) {
    /* ポート番号、ソケット */
    unsigned short port = 34600;
    int recvSocket;

    /* sockaddr_in 構造体 */
    struct sockaddr_in sockAddr;

    // 各種パラメータ
    int tmp,tmp2;
    char* tmpp;
    int status;
    int numrcv;
    unsigned int addr;
    char buffer[BUFFER_SIZE];

    // for mask
    struct in_addr net,mask;

    // dpms setting
    Bool b_dpms=False;

    net.s_addr  = inet_addr("0.0.0.0");
    mask.s_addr = inet_addr("0.0.0.0");

    struct command packet;

    //コマンドラインオプションチェック
    for(tmp=1;tmp<argc;tmp++){
        if(argv[tmp][0]=='-'){
            switch(argv[tmp][1]){
            case 'f'://from アドレスチェック
                if(argv[tmp][2]=='\0'){
                    tmpp=argv[tmp+1];
                    tmp++;
                }else{
                    tmpp=argv[tmp]+2;
                }
                if (strchr(tmpp,'/')){
                    //maskあり
                    tmp2=atoi(strchr(tmpp,'/')+1);
                    if (tmp2<1||tmp2>32){
                        perror("Ip address error.(mask)");
                        return 1;
                    }
                    mask.s_addr=-1<<(32-tmp2);
                    *strchr(tmpp,'/')='\0';
                    if (!inet_aton(tmpp,&net)){
                        printf("%s",tmpp);
                        perror("Ip address error.(addr)");
                        return 1;
                    }
                }else{
                    //maskなし
                    if (!inet_aton(tmpp,&net)){
                        perror("Ip address error.(addr)");
                        return 1;
                    }
                    mask.s_addr=-1;
                }
                break;
            case 'p'://ポート指定
                if(argv[tmp][2]=='\0'){
                    port=atoi(argv[tmp+1]);
                    tmp++;
                }else{
                    port=atoi(argv[tmp]+2);
                }
                if(port==0)port=34600;
                break;
            case 'x'://dpms(省電力)設定
                b_dpms=True;
                break;
            default:
                usage();
                exit(0);
            }
        }
    }

    /*XWindow 関連*/
    Display *disp = NULL;
    if ((disp=XOpenDisplay(NULL)) == NULL) {
        perror("XOpenDisplay");
        return 1;
    }
    XTestGrabControl(disp, True);

    /************************************************************/
    /* sockaddr_in 構造体のセット */
    memset(&sockAddr,0,sizeof(sockAddr));
    sockAddr.sin_port        = htons(port);
    sockAddr.sin_family      = AF_INET;
    sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    /* ソケット生成 */
    recvSocket=socket(AF_INET,SOCK_DGRAM,0);

    /* バインド */
    status=bind(recvSocket,(struct sockaddr*)&sockAddr,(socklen_t)sizeof(sockAddr));

    /* パケット受信 */
    while(1) {
        //受信処理
        tmp=sizeof(struct sockaddr_in);
        numrcv=recvfrom(recvSocket,buffer,(size_t)BUFFER_SIZE,0,(struct sockaddr*)&sockAddr,(socklen_t *)&tmp);
        if(numrcv==-1){
            status=close(recvSocket);
            break;
        }
        memcpy(&packet,buffer,sizeof(packet));
        //from アドレスチェック
        addr=ntohl(sockAddr.sin_addr.s_addr);
        if ((addr&mask.s_addr)==ntohl(net.s_addr)){
            addr=ntohl(sockAddr.sin_addr.s_addr);
            switch(packet.cmd){
                case CMD_HELLO://HELLO command 受信
                    packet.cmd=1;
                    sendto(recvSocket,&packet,(size_t)sizeof(packet),0,(struct sockaddr *)&sockAddr,(socklen_t)sizeof(sockAddr));
                    if(b_dpms){
                        system("xset dpms force on");//ディスプレイ省電力停止
                    }
                    break;

                case CMD_MOUSE_MOVE://マウス移動
                    XTestFakeMotionEvent(disp,-1,((int)packet.param1)*XDisplayWidth (disp,0)/65535,
                                                 ((int)packet.param2)*XDisplayHeight(disp,0)/65535,0);
                    break;

                case CMD_LEFT_UP://マウスクリック関連
                case CMD_LEFT_DOWN:
                case CMD_RIGHT_UP:
                case CMD_RIGHT_DOWN:
                case CMD_MIDDLE_UP:
                case CMD_MIDDLE_DOWN:
                    switch ((packet.cmd-3)>>1){
                        case 0: tmp=Button1; break;
                        case 1: tmp=Button3; break;
                        case 2: tmp=Button2; break;
                    }
                    XTestFakeMotionEvent(disp,-1,((int)packet.param1)*XDisplayWidth (disp,0)/65535,
                                                 ((int)packet.param2)*XDisplayHeight(disp,0)/65535,0);
                    if(packet.cmd&1){
                        XTestFakeButtonEvent(disp,tmp,False,0);
                    }else{
                        XTestFakeButtonEvent(disp,tmp,True,0);
                    }
                    break;

                case CMD_MOUSE_WHEEL://マウスホイール回転関連
                    if(packet.param3>0){
                        XTestFakeButtonEvent(disp,Button4,True, 0);
                        XTestFakeButtonEvent(disp,Button4,False,0);
                    }else{
                        XTestFakeButtonEvent(disp,Button5,True, 0);
                        XTestFakeButtonEvent(disp,Button5,False,0);
                    }
                    break;

                case CMD_KEY_UP://キーボード関連
                case CMD_KEY_DOWN:
                    if((tmp=XKeysymToKeycode(disp,chgkey(packet.param1)))<=0)break;
                    if(tmp==49){
                        XTestFakeKeyEvent(disp,tmp,True,0);
                        XTestFakeKeyEvent(disp,tmp,False,0);
                    }else{
                        if(packet.cmd&1){
                            XTestFakeKeyEvent(disp,tmp,False,0);
                        }else{
                            XTestFakeKeyEvent(disp,tmp,True,0);
                        }
                    }
                    break;
            }
        }else{
            packet.cmd=2;
            sendto(recvSocket,&packet,(size_t)sizeof(packet),0,(struct sockaddr *)&sockAddr,(socklen_t)sizeof(sockAddr));
        }
        XFlush(disp);
    }
}
