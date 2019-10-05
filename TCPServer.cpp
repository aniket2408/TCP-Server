/*All right reserved to awinsyspro.com 2019*/
/* TCP Server Sample program*/

#define _WINSOCK_DEPRECATED_NO_WARNINGS 1
#include"pch.h"
#include<WinSock2.h>
#include<ws2tcpip.h>
#include<iostream>
#pragma comment(lib, "Ws2_32.lib")

using namespace std;

int main()
{
	cout << "\t\t------ TCP SERVER ---------" << endl;
	cout << endl;
	//Local Variable
	WSADATA   Winsockdata;
	int       iWsaStartup;
	int       iWsaCleanup;

	SOCKET   TCPServerSocket;
	int      iCloseSocket;

	struct  sockaddr_in  TCPServerAdd;
	struct  sockaddr_in  TCPClientAdd;
	int     iTCPClientAdd = sizeof(TCPClientAdd);

	int iBind;

	int iListen;

	SOCKET sAcceptSocket;

	int   iSend;
	char  SenderBuffer[512] = "Hello from Server!";
	int   iSenderBuffer = strlen(SenderBuffer) + 1;

	int  iRecv;
	char RecvBuffer[512];
	int  iRecvBuffer = strlen(RecvBuffer) + 1;

	// STEP -1 WSAStartUp Fun
	iWsaStartup = WSAStartup(MAKEWORD(2, 2), &Winsockdata);
	if (iWsaStartup != 0)
	{
		cout << "WSAStartUp Failed" << endl;
	}
	cout << "WSAStartUp Success" << endl;

	// STEP-2 Fill the Structure
	TCPServerAdd.sin_family = AF_INET;
	//InetPton(AF_INET, PCWSTR("127.0.0.1"), &TCPServerAdd.sin_addr.S_un.S_addr);
	//TCPServerAdd.sin_addr.s_addr = inet_addr("127.0.0.1");
	TCPServerAdd.sin_addr.S_un.S_addr = INADDR_ANY;
	TCPServerAdd.sin_port = htons(54000);

	//STEP -3 Socket Creation
	TCPServerSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (TCPServerSocket == INVALID_SOCKET)
	{
		cout << "TCP Server Socket Creation Failed" << endl;
		cout << "Error Code - " << WSAGetLastError() << endl;
	}
	cout << "TCP Server Socket Creation Success" << endl;

	//STEP-4 bind fun
	iBind = bind(
		TCPServerSocket,
		(SOCKADDR*)&TCPServerAdd,
		sizeof(TCPServerAdd));
	if (iBind == SOCKET_ERROR)
	{
		cout << "Binding Failed" << endl;
		cout << "Error No-> " << WSAGetLastError() << endl;
	}
	cout << "Binding Success" << endl;

	//STEP-5 Listen fun
	iListen = listen(TCPServerSocket, 2);
	if (iListen == SOCKET_ERROR)
	{
		cout << "Listen Fun Failed " << endl;
		cout << "Error No-> " << WSAGetLastError() << endl;
	}
	cout << "Listen Fun Success" << endl;

	// STEP-6 Accept
	sAcceptSocket = accept(
		TCPServerSocket,
		(SOCKADDR*)&TCPClientAdd,
		&iTCPClientAdd);
	if (sAcceptSocket == INVALID_SOCKET)
	{
		cout << "Accept Failed " << endl;
		cout << "Error No-> " << WSAGetLastError() << endl;
	}
	cout << "Connection Accepted" << endl;

	// STEP-7 Send Data to Client
	iSend = send(sAcceptSocket, SenderBuffer, iSenderBuffer, 0);
	if (iSend == SOCKET_ERROR)
	{
		cout << "Sending Failed " << endl;
		cout << "Error No-> " << WSAGetLastError() << endl;
	}
	cout << "Data Sending Success " << endl;

	// STEP-8 Recv Data from Client
	iRecv = recv(sAcceptSocket, RecvBuffer, iRecvBuffer, 0);
	if (iRecv == SOCKET_ERROR)
	{
		cout << "Receive Data Failed " << endl;
		cout << "Error No-> " << WSAGetLastError() << endl;
	}
	cout << "DATA RECEIVED -> " << RecvBuffer << endl;


	// STEP-9 Close Socket
	iCloseSocket = closesocket(TCPServerSocket);
	if (iCloseSocket == SOCKET_ERROR)
	{
		cout << "Closing Socket Failed " << endl;
		cout << "Error No-> " << WSAGetLastError() << endl;
	}
	cout << "Closing Socket Success" << endl;
	// STEP-10 CleanUp from DLL
	iWsaCleanup = WSACleanup();
	if (iWsaCleanup == SOCKET_ERROR)
	{
		cout << "CleanUp Fun Failed " << WSAGetLastError() << endl;
		cout << "Error No-> " << WSAGetLastError() << endl;
	}
	cout << "CleanUp Fun Success" << endl;

	system("PAUSE");
	return 0;
}