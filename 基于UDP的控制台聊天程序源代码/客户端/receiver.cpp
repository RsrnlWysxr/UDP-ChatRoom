#include<WinSock2.h>
#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
#define DEFAULT_SPORT 5055
#define DEFAULT_CPORT 5056
#define BUFFER_LENGTH 1024

void main()
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		cout << "Failed to load Winsock." << endl;
		return;
	}
	//建立显示器端地址
	struct sockaddr_in receiver;
	//读取分配好的端口
	ifstream in("port.txt");
	string receiver_port;
	string username;
	getline(in, receiver_port);
	getline(in, username);
	in.close();
	remove("port.txt");
	int receiver_port_int = atoi(receiver_port.c_str());

	receiver.sin_family = AF_INET;
	receiver.sin_port = htons(receiver_port_int);    //htons()函数把一个双字节主机字节顺序的数转换为网络字节顺序的数
	receiver.sin_addr.s_addr = htonl(INADDR_ANY);    //htonl()函数把一个主机字节顺序的数转换为网络字节顺序的数   
	SOCKET rSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (rSocket == INVALID_SOCKET)
	{
		cout << "socket()Failed:" << WSAGetLastError() << endl;
		return;
	}
	if (bind(rSocket, (LPSOCKADDR)&receiver, sizeof(receiver)) == SOCKET_ERROR)
	{
		cout << "bind()Failed:" << WSAGetLastError() << endl;
		return;
	}

	char recv_buf[BUFFER_LENGTH];                  //接收数据的缓冲区
	memset(recv_buf, 0, sizeof(recv_buf));         //初始化接收缓冲区

	struct sockaddr_in ser;                        //客户端地址
	int ser_length = sizeof(ser);                  //客户端地址长度


	cout << "----------------------------------------" << endl << endl;
	cout << "           显示器---" << username << endl << endl << endl;
	cout << "----------------------------------------" << endl << endl;

	while (true)                                   //进入一个无限循环，进行数据接收和发送
	{
		int iRecv = recvfrom(rSocket, recv_buf, BUFFER_LENGTH, 0, (SOCKADDR*)&ser, &ser_length);
		string transmessage(recv_buf);
		if (iRecv == SOCKET_ERROR)
		{
			cout << "recvfrom()Failed:" << WSAGetLastError() << endl;
			break;
		}
		else if (transmessage == "exit") break;
		else
			cout << transmessage << endl;
	}
	closesocket(rSocket);
	WSACleanup();
}