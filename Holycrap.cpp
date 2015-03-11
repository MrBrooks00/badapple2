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
COORD coordScreen = { 0, 0 }; /* �������λ��*/
BOOL bSuccess;
DWORD cCharsWritten;
CONSOLE_SCREEN_BUFFER_INFO csbi; /* ��ȡ��������Ϣ */
DWORD dwConSize; /* ��ǰ���������ַ��� */
/* ��ȡ��ǰ���������ַ��� */
bSuccess = GetConsoleScreenBufferInfo( hConsole, &csbi );
PERR( bSuccess, "GetConsoleScreenBufferInfo" );
dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
/* �ÿո����������Ļ */
bSuccess = FillConsoleOutputCharacter( hConsole, (TCHAR) ' ',
dwConSize, coordScreen, &cCharsWritten );
PERR( bSuccess, "FillConsoleOutputCharacter" );
/* ��ȡ��ǰ�ı����� */
bSuccess = GetConsoleScreenBufferInfo( hConsole, &csbi );
PERR( bSuccess, "ConsoleScreenBufferInfo" );
/* ��Ӧ�����û��������� */
bSuccess = FillConsoleOutputAttribute( hConsole, csbi.wAttributes,
dwConSize, coordScreen, &cCharsWritten );
PERR( bSuccess, "FillConsoleOutputAttribute" );
/* �ѹ�����(0,0) */
bSuccess = SetConsoleCursorPosition( hConsole, coordScreen );
PERR( bSuccess, "SetConsoleCursorPosition" );
return;
}

int main(int argc, char **argv) {
//�Լ���
filebuf * pbuffer;
ifstream infile;
long size;
char * buffer;
// Ҫ���������ļ���������ö����ƴ�
infile.open ("bad apple", ios::binary);
// ��ȡinfile��Ӧbuffer�����ָ��
pbuffer=infile.rdbuf();
// ��ȡ�ļ���С
size=pbuffer->pubseekoff (0,ios::end,ios::in);
pbuffer->pubseekpos (0,ios::in);
// �����ڴ�ռ�
buffer=new char[size];
int key=0;
///////////////////////////////////////////////////////////////////////////��ѭ��Ŷ
while (1) {
///////////////////////////////////////////////////////////////////////////��Ⱦ֡
key = int(size / 3280);
// ��ȡ�ļ�����
pbuffer->sgetn (buffer,key);
cout.write(buffer,key);
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
cls( hConsole );
CloseHandle( hConsole );

NowTime = clock();
///////////////////////////////////////////////////////////////////////////����֡Ƶ
frame++;
if ( clock() <= timeNex ) Sleep( timeNex - clock() ); //����֡Ƶ
timeNex = timeNex + ( 1000 / FRAMES_PER_SECOND );
if ((clock() - timeUse) > 500) { //����֡��
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
