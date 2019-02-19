#include "stdafx.h"

#include "Staubli_Master.h"

static SOCKET ClientSocket = INVALID_SOCKET;

Server::Server(void) {
}

Server::~Server(void) {
	//ICMPClose(hIcmpFile);
	TCPShutdown();
}

//Ping
HANDLE Server::ICMPSetup() {
	HANDLE hIcmpFile;

	hIcmpFile = IcmpCreateFile();
	if (hIcmpFile == INVALID_HANDLE_VALUE) {
		printf("\tUnable to open handle.\n");
		printf("IcmpCreatefile returned error: %ld\n", GetLastError() );
		return ERROR;
	}  
	return hIcmpFile;
}

void Server::ICMPClose(HANDLE hIcmpFile) {
	//Need to close the handle when done using it
	IcmpCloseHandle(hIcmpFile);
}

bool Server::PingEcho(char *ip) {
	DWORD dwRetVal = 0;
	HANDLE hIcmpFile;
	unsigned long ipaddr = INADDR_NONE;

	LPVOID reply_buffer = NULL;
	DWORD reply_size = 0;

	hIcmpFile = Server::ICMPSetup();

	char SendData[32] = "Ika is the best";

	ipaddr = inet_addr(ip);
	if (ipaddr == INADDR_NONE) {
		printf("usage: %s IP address\n", ip);
		Server::ICMPClose(hIcmpFile);
		return ERROR;
	} 

	reply_size = sizeof(ICMP_ECHO_REPLY) + sizeof(SendData);
	reply_buffer = (VOID*) malloc(reply_size);
	if (reply_buffer == NULL) {
		printf("\tUnable to allocate memory\n");
		Server::ICMPClose(hIcmpFile);
		return ERROR;
	}    


	dwRetVal = IcmpSendEcho(hIcmpFile, ipaddr, SendData, sizeof(SendData), 
		NULL, reply_buffer, reply_size, 1000);
	if (dwRetVal != 0) {
		PICMP_ECHO_REPLY pEchoReply = (PICMP_ECHO_REPLY)reply_buffer;
		struct in_addr ReplyAddr;
		ReplyAddr.S_un.S_addr = pEchoReply->Address;
		printf("Sent icmp message to %s\n", ip);
		if (dwRetVal > 1) {
			printf("Received %ld icmp message responses\n", dwRetVal);
			printf("Information from the first response:\n"); 
		}    
		else {    
			printf("Received %ld icmp message response\n", dwRetVal);
			printf("Information from this response:\n"); 
		}    
		printf("\tReceived from %s\n", inet_ntoa( ReplyAddr ) );
		printf("\tStatus = %ld\n", 
			pEchoReply->Status);
		printf("\tRoundtrip time = %ld milliseconds\n", 
			pEchoReply->RoundTripTime);
	}
	else {
		printf("\tCall to IcmpSendEcho failed.\n");
		printf("\tIcmpSendEcho returned error: %ld\n", GetLastError() );
		Server::ICMPClose(hIcmpFile);
		return ERROR;
	}
	Server::ICMPClose(hIcmpFile);
	return SUCESS;
}

void Server::PingReply_Listen() {
	HANDLE hIcmpFile;
	LPVOID reply_buffer = NULL;
	DWORD reply_size = 0;

	hIcmpFile = Server::ICMPSetup();

	printf("Handle created");

	reply_size = sizeof (ICMP_ECHO_REPLY);
	reply_buffer = (VOID *) malloc(reply_size);
	PICMP_ECHO_REPLY pecho_reply;

	//IcmpParseReplies(reply_buffer, (int)sizeof(reply_buffer));
	pecho_reply = (PICMP_ECHO_REPLY) reply_buffer;

	printf("Status = %ld\n", pecho_reply->Status);
	switch (pecho_reply->Status) {
case IP_SUCCESS:
	printf("Destination host was unreachable\n");
	break;
case IP_DEST_HOST_UNREACHABLE:
	printf("Destination host was unreachable\n");
	break;
case IP_DEST_NET_UNREACHABLE:
	printf("Destination Network was unreachable\n");
	break;
case IP_REQ_TIMED_OUT:
	printf("Request timed out\n");
	break;
default:
	printf("\n");
	break;
	} 
}

//TCP
int Server::TCPServer_Setup() {
	WSADATA wsaData;
	SOCKET ListenSocket = INVALID_SOCKET;
	int iResult;
	struct addrinfo *result = NULL;
	struct addrinfo hints;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return ERROR;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the Server address and port
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if ( iResult != 0 ) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return ERROR;
	}

	// Create a SOCKET for connecting to Server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return ERROR;
	}

	// Setup the TCP listening socket
	iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return ERROR;
	}

	freeaddrinfo(result);

	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return ERROR;
	}

	// Accept a client socket
	ClientSocket = accept(ListenSocket, NULL, NULL);
	if (ClientSocket == INVALID_SOCKET) {
		printf("accept failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return ERROR;
	}

	// No longer need Server socket
	closesocket(ListenSocket);
	return SUCESS;
}

bool Server::TCPSend(const char *sendbuf, int sendbuflen) {
	int iSendResult;

	iSendResult = send( ClientSocket, sendbuf, sendbuflen, 0 );
	if (iSendResult == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(ClientSocket);
		WSACleanup();
		return ERROR;
	}
	printf("SUCESS\n");
	return SUCESS;
}

char *Server::TCPReceive() {
	int iRecvResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

	iRecvResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
	if (iRecvResult > 0) {
		printf("Bytes received: %d\n", iRecvResult);
	}
	else if (iRecvResult == 0)
		printf("Connection closing...\n");
	else  {
		printf("recv failed with error: %d\n", WSAGetLastError());
		closesocket(ClientSocket);
		WSACleanup();
		return ERROR;
	}
	return recvbuf;
}

int Server::TCPShutdown() {
	int iResult;
	// shutdown the connection since we're done
	iResult = shutdown(ClientSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ClientSocket);
		WSACleanup();
		return 1;
	}

	// cleanup
	closesocket(ClientSocket);
	WSACleanup();
	return 0;
}