#include "stdio.h"
#include "time.h"
#include "conio.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "windows.h"
#define PERR(bSuccess, api){if(!(bSuccess)) printf("%s:Error %d from %s on line %d\n", __FILE__,GetLastError(), api, __LINE__);}

using namespace std;

clock_t NowTime;
const int FRAMES_PER_SECOND = 15;
int timeNex;
int timeUse;
int frame = 0;
int NowFPS;

void cls( HANDLE hConsole )
{
COORD coordScreen = { 0, 0 }; /* 定义光标的位置*/
BOOL bSuccess;
DWORD cCharsWritten;
CONSOLE_SCREEN_BUFFER_INFO csbi; /* 获取缓冲区信息 */
DWORD dwConSize; /* 当前缓冲区的字符数 */
/* 获取当前缓冲区的字符数 */
bSuccess = GetConsoleScreenBufferInfo( hConsole, &csbi );
PERR( bSuccess, "GetConsoleScreenBufferInfo" );
dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
/* 用空格填充整个屏幕 */
bSuccess = FillConsoleOutputCharacter( hConsole, (TCHAR) ' ',
dwConSize, coordScreen, &cCharsWritten );
PERR( bSuccess, "FillConsoleOutputCharacter" );
/* 获取当前文本属性 */
bSuccess = GetConsoleScreenBufferInfo( hConsole, &csbi );
PERR( bSuccess, "ConsoleScreenBufferInfo" );
/* 相应地设置缓冲区属性 */
bSuccess = FillConsoleOutputAttribute( hConsole, csbi.wAttributes,
dwConSize, coordScreen, &cCharsWritten );
PERR( bSuccess, "FillConsoleOutputAttribute" );
/* 把光标放在(0,0) */
bSuccess = SetConsoleCursorPosition( hConsole, coordScreen );
PERR( bSuccess, "SetConsoleCursorPosition" );
return;
}

int main(int argc, char **argv) {
//自己想
filebuf * pbuffer;
ifstream infile;
long size;
char * buffer;
// 要读入整个文件，必须采用二进制打开
infile.open ("bad apple", ios::binary);
// 获取infile对应buffer对象的指针
pbuffer=infile.rdbuf();
// 获取文件大小
size=pbuffer->pubseekoff (0,ios::end,ios::in);
pbuffer->pubseekpos (0,ios::in);
// 分配内存空间
buffer=new char[size];
int key=0;
///////////////////////////////////////////////////////////////////////////主循环哦
while (1) {
///////////////////////////////////////////////////////////////////////////渲染帧
key = int(size / 3280);
// 获取文件内容
pbuffer->sgetn (buffer,key);
cout.write(buffer,key);
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
cls( hConsole );
CloseHandle( hConsole );

NowTime = clock();
///////////////////////////////////////////////////////////////////////////处理帧频
frame++;
if ( clock() <= timeNex ) Sleep( timeNex - clock() ); //限制帧频
timeNex = timeNex + ( 1000 / FRAMES_PER_SECOND );
if ((clock() - timeUse) > 500) { //计算帧率
NowFPS = (frame * 100 * 1000 / (clock() - timeUse)) / 100.f;
timeUse = clock();
frame = 0;
}
}
delete []buffer;
return 0;
infile.close();
getch();
}
