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
	//������ʾ���˵�ַ
	struct sockaddr_in receiver;
	//��ȡ����õĶ˿�
	ifstream in("port.txt");
	string receiver_port;
	string username;
	getline(in, receiver_port);
	getline(in, username);
	in.close();
	remove("port.txt");
	int receiver_port_int = atoi(receiver_port.c_str());

	receiver.sin_family = AF_INET;
	receiver.sin_port = htons(receiver_port_int);    //htons()������һ��˫�ֽ������ֽ�˳�����ת��Ϊ�����ֽ�˳�����
	receiver.sin_addr.s_addr = htonl(INADDR_ANY);    //htonl()������һ�������ֽ�˳�����ת��Ϊ�����ֽ�˳�����   
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

	char recv_buf[BUFFER_LENGTH];                  //�������ݵĻ�����
	memset(recv_buf, 0, sizeof(recv_buf));         //��ʼ�����ջ�����

	struct sockaddr_in ser;                        //�ͻ��˵�ַ
	int ser_length = sizeof(ser);                  //�ͻ��˵�ַ����


	cout << "----------------------------------------" << endl << endl;
	cout << "           ��ʾ��---" << username << endl << endl << endl;
	cout << "----------------------------------------" << endl << endl;

	while (true)                                   //����һ������ѭ�����������ݽ��պͷ���
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