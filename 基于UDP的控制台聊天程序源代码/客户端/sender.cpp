#include<Winsock2.h>
#include<iostream>
#include<string>
#include<ctime>
#include<tchar.h>
#include<Windows.h>
#include<fstream>
#include<vector>
#include <sstream>
using namespace std;
#pragma comment(lib,"ws2_32.lib")

#define DEFAULT_PORT 5055
#define DATA_BUFFER 1024

class client
{
public:
	bool Startup();
	void SetServerAddress();
	int GeneratePort();               //���������ʾ���˿ں�
	bool Getonlinelist();             //������ߵ��û���
	void work();                      //��������������
private:
	WSADATA wsaData;
	SOCKET sClient;                       //������Ϣ�ͽ�����Ϣʱʹ�õ��׽���
	struct sockaddr_in ser;               //����������ĵ�ַ
	int ser_length = sizeof(ser);
	struct sockaddr_in communication;
	int communication_length = sizeof(communication);
	char recv_buf[DATA_BUFFER];           //������Ϣ�Ļ�����
	int receiver_port;                    //��ʾ���Ķ˿ں�
	vector<string> onlinelist;            //���������û����û���
	int iSend, iRecv;
};

bool client::Startup()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		cout << "Failed to load Winsock." << endl;
		return false;
	}
	sClient = socket(AF_INET, SOCK_DGRAM, 0);
	if (sClient == INVALID_SOCKET)
	{
		cout << "socket()Failed:" << WSAGetLastError() << endl;
		return false;
	}
	return true;
}
void client::SetServerAddress()
{
	cout << "������ip��ַ:";
	string iptemp;
	cin >> iptemp;
	char *ip = new char[iptemp.length() + 1];
	strcpy(ip, iptemp.c_str());
	//�����������˵�ַ
	ser.sin_family = AF_INET;
	ser.sin_port = htons(DEFAULT_PORT);
	ser.sin_addr.s_addr = inet_addr(ip);
}
int client::GeneratePort()
{
	srand((unsigned)time(NULL));
	int x = 1024 + rand() % (5000 - 1024);
	return x;
}
bool client::Getonlinelist()            //������������ȡ���������б�
{
	if (onlinelist.size() > 0)
		onlinelist.clear();
	char getonlinelist[3] = "PL";
	iSend = sendto(sClient, getonlinelist, 3, 0, (struct sockaddr*)&ser, ser_length);
	if (iSend == SOCKET_ERROR)
	{
		cout << "sendto()Failed:" << WSAGetLastError() << endl;
		return false;
	}
	memset(recv_buf, 0, sizeof(recv_buf));
	iRecv = recvfrom(sClient, recv_buf, sizeof(recv_buf), 0, (struct sockaddr*)&communication, &communication_length);   ///////////////////////////////////////////////////
	if (iRecv == SOCKET_ERROR)
	{
		cout << "recvfrom() Failed" << WSAGetLastError() << endl;
		return false;
	}
	string list(recv_buf);
	string friendname;
	for (int i = 0; i < list.length(); i++)
	{
		if (list[i] == '$')  break;
		else if (list[i] == '#')
		{
			onlinelist.push_back(friendname);
			friendname = "";
		}
		else
			friendname = friendname + list[i];
	}
	cout << "----------------------------" << endl;
	cout << "���ߺ����б�" << endl;
	for (int i = 0; i < onlinelist.size(); i++)
		cout << i << ":  " << onlinelist[i] << endl;
	cout << "----------------------------" << endl;
	return true;
}
void client::work()
{
	while (true)
	{
		memset(recv_buf, 0, sizeof(recv_buf));
		system("cls");
		cout << "****************************************" << endl;
		cout << "*                                      *" << endl;
		cout << "*       1.��¼  2.ע��  3.�˳�         *" << endl;
		cout << "*                                      *" << endl;
		cout << "****************************************" << endl;

		string choice;
		getline(cin, choice);
		if (choice == "1")
		{
			system("cls");
			cout << "�������û���:";
			string username;
			getline(cin, username);
			cout << "����������:";
			string password;
			getline(cin, password);
			//������ʾ���˿�
			receiver_port = GeneratePort();
			//���˿ں�д���ļ�����ʾ�������ȡ
			ofstream out("port.txt");
			out << receiver_port << "\n" << username;
			out.close();

			string init_infortemp = "L" + username + "#" + password + "#" + to_string(receiver_port);
			char *init_infor = new char[init_infortemp.length() + 1];
			strcpy(init_infor, init_infortemp.c_str());
			//���������֤�û���Ϣ
			iSend = sendto(sClient, init_infor, init_infortemp.length() + 1, 0, (struct sockaddr*)&ser, ser_length);
			//���շ�������Ӧ����Ϣ
			iRecv = recvfrom(sClient, recv_buf, sizeof(recv_buf), 0, (SOCKADDR*)&communication, &communication_length);
			if (iRecv == SOCKET_ERROR)
			{
				cout << "recvfrom() Failed:" << GetLastError() << endl;
				cout << "δ�յ�����������Ӧ����¼ʧ��,������Y������ҳ:";
				string ret;
				while (getline(cin, ret))
				{
					if (ret == "Y")break;
					cout << "δ�յ�����������Ӧ����¼ʧ��,������Y������ҳ:";
				}
				continue;
			}
			if (recv_buf[0] == 'Y')   //��¼�ɹ�
			{
				system("cls");
				ShellExecute(NULL, _T("open"), _T("receiver.exe"), NULL, NULL, SW_SHOW);     //������ʾ������
			}
			else if (recv_buf[0] == '0')
			{
				cout << "δע���û�������¼ʧ�ܣ�������Y������ҳ:";
				string ret;
				while (getline(cin, ret))
				{
					if (ret == "Y")break;
					cout << "δע���û�������¼ʧ�ܣ�������Y������ҳ:";
				}
				continue;
			}
			else if (recv_buf[0] == '1')
			{
				cout << "������󣬵�¼ʧ�ܣ�������Y������ҳ:" << endl;
				string ret;
				while (getline(cin, ret))
				{
					if (ret == "Y")break;
					cout << "������󣬵�¼ʧ�ܣ�������Y������ҳ:";
				}
				continue;
			}
			else if (recv_buf[0] == '2')
			{
				cout << "�ظ���¼����¼ʧ�ܣ�������Y������ҳ:" << endl;
				string ret;
				while (getline(cin, ret))
				{
					if (ret == "Y")break;
					cout << "�ظ���¼����¼ʧ�ܣ�������Y������ҳ:";
				}
				continue;
			}

			//ѡ�����췽ʽ
			while (true)
			{
				system("cls");
				cout << "---------------------------------------------------" << endl;
				cout << "                 �û���:" << username << endl << endl;;
				cout << "            1.˽��  2.Ⱥ��  3.�˳���¼             " << endl << endl;
				cout << "---------------------------------------------------" << endl;
				string mode;
				getline(cin, mode);
				if (mode == "1")    //˽��
				{
					system("cls");
					cout << "˽��ģʽ�У�����return������һ��" << endl << endl;
					if (!Getonlinelist())    continue;                           //��ȡ���������б�ʧ��
					cout << "��ѡ��˽�Ķ�������" << endl;
					string choose;
					getline(cin, choose);
					if (choose == "return") continue;
					int i = 0;
					for (i = 0; i < choose.size(); i++)
						if (choose[i] > '9' || choose[i] < '0')break;
					if (i < choose.size()) continue;	
					stringstream stream(choose);
					int index = 0;
					stream >> index;
					if (index<0 || index>=onlinelist.size()) continue;
					while (true)                     //����û�ѭ��������Ϣ��ֱ������return�˳�
					{
						system("cls");
						cout << "���ں�" << onlinelist[index] << "˽����" << "������return������һ��" << endl << endl;
						string message;
						getline(cin, message);
						if (message == "return")
						{
							system("cls");
							break;
						}
						message = "PM" + onlinelist[index] + "#" + message;
						char *buf = new char[message.length() + 1];
						strcpy(buf, message.c_str());
						iSend = sendto(sClient, buf, message.length() + 1, 0, (struct sockaddr*)&ser, ser_length);
						if (iSend == SOCKET_ERROR)
						{
							cout << "sendto()Failed:" << WSAGetLastError() << endl;
							break;
						}
						delete[]buf;
						iRecv = recvfrom(sClient, recv_buf, sizeof(recv_buf), 0, (SOCKADDR*)&communication, &communication_length);
						if (recv_buf[0] == 'Y') continue;
						else
						{
							cout << onlinelist[index] << "������" << "����Y�������˵�";
							string ret;
							while (getline(cin, ret))
							{
								if (ret == "Y") break;
								cout << onlinelist[index] << "������" << "����Y�������˵�";
							}
							break;
						}
					}
				}
				else if (mode == "2")    //Ⱥ��
				{
					system("cls");
					while (true)
					{
						system("cls");
						cout << "Ⱥ��ģʽ������return������һ��" << endl << endl;
						string message;
						getline(cin, message);
						if (message == "return")
						{
							system("cls");
							break;
						}

						message = "G" + message;
						char *buf = new char[message.length() + 1];
						strcpy(buf, message.c_str());
						iSend = sendto(sClient, buf, message.length() + 1, 0, (struct sockaddr*)&ser, ser_length);
						delete[]buf;
						if (iSend == SOCKET_ERROR)
						{
							cout << "sendto()Failed:" << WSAGetLastError() << endl;
							break;
						}
					}
					continue;
				}
				else if (mode == "3")                             //�˳���¼
				{
					char buf[] = "exit";
					iSend = sendto(sClient, buf, sizeof(buf), 0, (struct sockaddr*)&ser, ser_length);
					break;
				}
				else
					continue;
			}
		}
		else if (choice == "2")
		{
			system("cls");
			cout << "�������û���:";
			string username;
			getline(cin, username);
			cout << "�����õ�¼����:";
			string password;
			getline(cin, password);
			string init_infortemp = "R" + username + "#" + password;
			char *init_infor = new char[init_infortemp.length() + 1];
			strcpy(init_infor, init_infortemp.c_str());
			//�����������ע���û���Ϣ
			iSend = sendto(sClient, init_infor, init_infortemp.length() + 1, 0, (struct sockaddr*)&ser, ser_length);
			//���շ�������Ӧ����Ϣ
			iRecv = recvfrom(sClient, recv_buf, sizeof(recv_buf), 0, (struct sockaddr*)&communication, &communication_length);
			if (recv_buf[0] == 'Y')
			{
				cout << "ע��ɹ�" << endl;
				continue;
			}
			else
			{
				cout << "�û����Ѵ��ڣ�ע��ʧ�ܣ�������Y������ҳ:" << endl;
				string ret;
				while (getline(cin, ret))
				{
					if (ret == "Y")break;
					cout << "�û����Ѵ��ڣ�ע��ʧ�ܣ�������Y������ҳ:";
				}
				continue;
			}
		}
		else if (choice == "3")
		{
			closesocket(sClient);
			WSACleanup;
			return;
		}
		else
			continue;
	}
}

int main()
{
	client x;
	if (x.Startup() == false)
		return 0;
	x.SetServerAddress();
	x.work();
}
