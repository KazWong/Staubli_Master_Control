#ifndef _Server_
#define _Server_
#endif

#pragma once

#include "stdafx.h"

//#define _WIN32_WINNT 0x0500
#define WIN32_LEAN_AND_MEAN
#define DEBUG_MODE
#undef UNICODE

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "1000"

#define SUCESS 1
#define ERROR 0

const char STARTCHAR = '@';

struct axis6 {
	float x;
	float y;
	float z;
	float rx;
	float ry;
	float rz;
};

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

class FileHandle {
public : 
	FileHandle();
	~FileHandle();

public : 
	static char *SysString_StdString(System::String ^Source);
	static FILE *FileRead(char *file_path);
};

static class Server {
public : 
	Server(void);
~Server(void);

public:
	//Ping
	static HANDLE ICMPSetup();
	static void ICMPClose(HANDLE hIcmpFile);
	static bool PingEcho(char *ip);
	static void PingReply_Listen();

	//TCP
	static int TCPServer_Setup();
	static int TCPShutdown();
	static bool TCPSend(const char *sendbuf, int sendbuflen);
	static char *TCPReceive();
}server;

void TranHandle(char *file_path);