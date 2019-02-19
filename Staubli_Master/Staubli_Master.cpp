// Staubli_Master.cpp : main project file.
#include "stdafx.h"

#include "Staubli_Master.h"
#include "Form1.h"

using namespace Staubli_Master;
using namespace std;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
#ifndef DEBUG_MODE
	FreeConsole();
#else
	SetConsoleTitle(L"Debug Window");
#endif

	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	Application::Run(gcnew Form1());
	return 0;
}

void TranHandle(char *file_path) {
	//char *file_path;
	char *recvbuf;

	FILE *fp;
	char str[512] = "";
	axis6 point[20000];
	int total = 0;

	//file_path = FileHandle::SysString_StdString(Source);
	fp = FileHandle::FileRead(file_path);

	while (fscanf(fp, "%s", str)!= EOF) {
		char tmp[32]="";
		if (!strncmp(str, "x=\"", 3)) {
			strncpy(tmp, str+3, strlen(str)-4);
			point[total].x = (float)atof(tmp);
		}
		if (!strncmp(str, "y=\"", 3)) {
			strncpy(tmp, str+3, strlen(str)-4);
			point[total].y = (float)atof(tmp);
		}
		if (!strncmp(str, "z=\"", 3)) {
			strncpy(tmp, str+3, strlen(str)-4);
			point[total].z = (float)atof(tmp);
		}
		if (!strncmp(str, "rx=\"", 4)) {
			strncpy(tmp, str+4, strlen(str)-5);
			point[total].rx = (float)atof(tmp);
		}
		if (!strncmp(str, "ry=\"", 4)) {
			strncpy(tmp, str+4, strlen(str)-5);
			point[total].ry = (float)atof(tmp);
		}
		if (!strncmp(str, "rz=\"", 4)) {
			strncpy(tmp, str+4, strlen(str)-5);
			point[total].rz = (float)atof(tmp);
			total++;
		}
	}
	int i=0;
	//10 per time
	server.TCPServer_Setup();
	for(int i=0; i<total;) {
		char *recvbuf=NULL;
		char sendbuf[DEFAULT_BUFLEN]="";
		int sendbuflen = 0;
		for(int j=0; j<2 && i<total; j++, i++) {
				char buf1[DEFAULT_BUFLEN] = "";
				sprintf_s(buf1, DEFAULT_BUFLEN, "%.2f %.2f %.2f %.2f %.2f %.2f ", 
					point[i].x, point[i].y, point[i].z, 
					point[i].rx, point[i].ry, point[i].rz);
				strcat(sendbuf, buf1);
		}
			sendbuflen = strlen(sendbuf)-1;
			printf("%i Send : %i\n", i, sendbuflen);
			printf("%s@@", sendbuf);
			server.TCPSend(sendbuf, sendbuflen);
			//Sleep(100);
			
		do {
			recvbuf = server.TCPReceive();
			} while(*recvbuf != STARTCHAR);
		Sleep(10);
	}
	server.TCPSend("?", 1);
	server.TCPShutdown();
}