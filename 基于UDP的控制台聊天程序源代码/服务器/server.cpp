#include<WinSock2.h>
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>
#pragma comment(lib,"ws2_32.lib")
using namespace std;

#define DEFAULT_PORT 5055
#define BUFFER_LENGTH 1024
class user
{
public:
	user(string username, string ip, int sender_port, int receiver_port)
	{
		this->username = username;
		this->ip = ip;
		this->sender_port = sender_port;
		this->receiver_port = receiver_port;

		//���ý������ĵ�ַ
		receiver.sin_family = AF_INET;
		receiver.sin_port = htons(receiver_port);
		char *addr = new char[ip.length() + 1];
		strcpy(addr, ip.c_str());
		receiver.sin_addr.s_addr = inet_addr(addr);
	}
	string username;              //�û���
	string ip;                    //�ͻ���ip��ַ
	int sender_port;              //�������˿�
	int receiver_port;	          //�������˿�
	struct sockaddr_in receiver;  //�洢�������ĵ�ַ
};
class server
{
public:
	bool Startup();                                                   //����Ƿ�������������еĻ���
	bool SetServerSocket();                                           //���÷���������������Ϣ��socket�׽���
	bool Checktxt();                                                  //���洢�ļ��Ƿ���ڣ��������ڣ�����һ��
	void work();                                                      //���������е�������
	void SendMessage(string message, struct sockaddr_in x);           //������Ϣ�ĺ���
	void Sendonlinelist();                                            //��ͻ��˷��ͺ��������б�
	bool TestUsernameAndPassword(string username, string password, int &flag);   //�����û����������Ƿ���ȷ
	bool TestDuplicateLogin(string username);                         //�����Ƿ��ظ���¼
	bool TestDuplicateRigister(string username);                      //�����Ƿ��ظ�ע��
	string Getusername(string ip, int port);                           //����ip�Ͷ˿ںŻ���û���
	int  Getuserindex(string username);                               //�����û�������û��������û����������	
	void extractLoginuserinfor(string userinfor, string &username, string &password, string &receiverport); //��ȡ��¼�����е��û����������ʾ���˿ں�
	void extractRegisteruserinfor(string userinfor, string&username, string&password);                       //��ȡע�������е��û���������
	void extactPersonalMessageReceivername(string &message, string &receivername);                           //��ȡ˽����Ϣ�еĽ����ߵ�����

private:
	WSADATA wsaData;
	SOCKET sSocket;                            //����������Ϣ���׽���
	struct sockaddr_in ser;                    //��������ַ
	struct sockaddr_in cli;                    //�ͻ���ַ
	int cli_length = sizeof(cli);                //�ͻ���ַ����
	char recv_buf[BUFFER_LENGTH];              //�������ݵĻ�����
	vector<user> usertable;                    //�����û���
	string sendmessage, printmessage;           //�洢������ת������ӡ�õ��ַ���
	int iSend, iRecv;                          //�洢���������ͺͽ��յ��ַ����ĳ���
};

bool server::Startup()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		cout << "Failed to load Winsock." << endl;
		return false;
	}
	return true;
}
bool server::SetServerSocket()
{
	//�������������׽ӿ�
	sSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (sSocket == INVALID_SOCKET)
	{
		cout << "socket()Failed:" << WSAGetLastError() << endl;
		return false;
	}
	//�����������˵�ַ
	ser.sin_family = AF_INET;
	ser.sin_port = htons(DEFAULT_PORT);               //htons()������һ��˫�ֽ������ֽ�˳�����ת��Ϊ�����ֽ�˳�����
	ser.sin_addr.s_addr = htonl(INADDR_ANY);          //htonl()������һ�������ֽ�˳�����ת��Ϊ�����ֽ�˳�����   
	if (bind(sSocket, (LPSOCKADDR)&ser, sizeof(ser)) == SOCKET_ERROR)
	{
		cout << "bind()Failed:" << WSAGetLastError() << endl;
		return false;
	}
	return true;
}
void server::SendMessage(string message, struct sockaddr_in x)
{
	char *send_buf = new char[message.length() + 1];
	strcpy(send_buf, message.c_str());
	SOCKET rSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (rSocket == INVALID_SOCKET)
	{
		cout << "socket()Failed:" << WSAGetLastError() << endl;
		return;
	}
	iSend = sendto(rSocket, send_buf, message.length() + 1, 0, (SOCKADDR*)&(x), sizeof(x));
	if (iSend == SOCKET_ERROR)
	{
		cout << "sendto failed:" << WSAGetLastError() << endl;
		closesocket(rSocket);
		return;
	}
	closesocket(rSocket);
}
void server::Sendonlinelist()
{
	string onlinelist;
	for (int i = 0; i < usertable.size(); i++)
		onlinelist = onlinelist + usertable[i].username + "#";
	onlinelist = onlinelist + "$";                //������־
	SendMessage(onlinelist, cli);
}
bool server::TestUsernameAndPassword(string username, string password, int &flag)
{
	if (!Checktxt())
	{
		cout << "�޷��ҵ��洢�ļ�." << endl << endl;
		flag = 0;                                 //δ�ҵ��û����ı�־
		return false;
	}
	fstream in("C:\\userform\\userform.txt");
	string line;
	string username_txt, password_txt;
	while (getline(in, line))
	{
		for (int i = 0; i < line.size(); i++)
		{
			if (line[i] == '#')
			{
				username_txt = line.substr(0, i);
				password_txt = line.substr(i + 1);
				break;
			}
		}
		if (username_txt == username)         //���û�������
		{
			if (password == password_txt)     //��������ȷ
			{
				in.close();
				return true;                  //������֤�ɹ�
			}
			cout << "�û�" << username << "��¼�������" << endl << endl;       //��������������Ϣ
			flag = 1;                        //�������ı�־
			return false;
		}
	}
	in.close();
	cout << "δע������û�:" << username << endl << endl;
	flag = 0;                                 //δ�ҵ��û����ı�־
	return false;
}
bool server::TestDuplicateLogin(string username)
{
	int i;
	for (i = 0; i < usertable.size(); i++)
		if (usertable[i].username == username) break;
	if (i == usertable.size())     //���û���û�е�¼��
		return false;
	else
	{
		cout << "�û�" << username << "�ظ���¼" << endl;
		return true;
	}
}
bool server::TestDuplicateRigister(string username)
{
	if (!Checktxt())
	{
		cout << "�޷��ҵ��洢�ļ�." << endl << endl;
		return true;
	}
	fstream in("C:\\userform\\userform.txt");
	string line;
	while (getline(in, line))
	{
		string username_txt;
		for (int i = 0; i < line.size(); i++)
		{
			if (line[i] == '#')
			{
				username_txt = line.substr(0, i);              //��ȡ�û���
				if (username_txt == username)                  //�Աȣ����������Ѿ�ע���
				{
					in.close();
					cout << "�û���" << username << "�ظ�ע��" << endl << endl;
					return true;
				}
				break;                                         //��������Ա���һ���û���
			}
		}
	}
	in.close();
	return false;                                               //����ִ�е���˵�����û�����û��ע���
}
string server::Getusername(string ip, int port)
{
	for (int i = 0; i < usertable.size(); i++)
		if (usertable[i].ip == ip&&usertable[i].sender_port == port)
			return usertable[i].username;
	cout << "�Ƿ����û������Ϸ�����" << endl;
	cout << "ip��ַΪ:" << ip << endl << "�˿ں�Ϊ:" << port << endl;
	return "";
}
int server::Getuserindex(string username)
{
	int i = 0;
	for (i = 0; i < usertable.size(); i++)
		if (usertable[i].username == username) break;
	return i;
}
void server::extractLoginuserinfor(string userinfor, string &username, string &password, string &receiverport)
{
	int i;
	for (i = 0; i < userinfor.length(); i++)           //��ȡ�û���
	{
		if (userinfor[i] == '#')
		{
			username = userinfor.substr(0, i);
			break;
		}
	}
	for (int j = i + 1; j < userinfor.length(); j++)  //��ȡ�������ʾ���˿ں�
	{
		if (userinfor[j] == '#')
		{
			password = userinfor.substr(i + 1, j - i - 1);
			receiverport = userinfor.substr(j + 1);
			break;
		}
	}
}
void server::extractRegisteruserinfor(string userinfor, string&username, string&password)
{
	for (int i = 0; i < userinfor.size(); i++)
	{
		if (userinfor[i] == '#')
		{
			username = userinfor.substr(0, i);
			password = userinfor.substr(i + 1);
			break;
		}
	}
}
void server::extactPersonalMessageReceivername(string &message, string &receivername)
{
	for (int i = 0; i < message.size(); i++)
	{
		if (message[i] == '#')
		{
			receivername = message.substr(0, i);
			message = message.substr(i + 1);
			break;
		}
	}
}
bool server::Checktxt()
{
	FILE *fp = fopen("C:\\userform\\userform.txt", "r");
	if (fp == NULL)
	{
		system("md C:\\userform");
		ofstream out("C:\\userform\\userform.txt");
		if (!out)
			return false;
		out.close();
		return true;
	}
	return true;
}
void server::work()
{
	cout << "-----------------" << endl;
	cout << "Server running" << endl;
	cout << "-----------------" << endl;
	while (true)                                       //����һ������ѭ�����������ݽ��պͷ���
	{
		memset(recv_buf, 0, sizeof(recv_buf));         //��ʼ�����ջ�����
		iRecv = recvfrom(sSocket, recv_buf, BUFFER_LENGTH, 0, (struct sockaddr*)&cli, &cli_length);
		if (iRecv == SOCKET_ERROR)
		{
			cout << "recvfrom()Failed:" << WSAGetLastError() << endl;
			continue;
		}

		//��ȡ���ͷ��ĵ�ַ��ip�Ͷ˿ڣ�
		char *x = inet_ntoa(cli.sin_addr); string address(x);         //��ȡ�ͻ���ip
		int userport = ntohs(cli.sin_port);                           //��ȡ�ͻ��˶˿�

		string infortype = string(recv_buf);                            //����infortype[0]���ж���Ϣ������       
		if (infortype[0] == 'L')                                      //��¼����
		{
			string userinfor = infortype.substr(1);                   //��ȥ��Ϣ����
			string username, password, receiver_port;
			extractLoginuserinfor(userinfor, username, password, receiver_port);  //��ȡ�û���������
																				  //�򲻺Ϸ��û����͵�¼ʧ�ܵĻ�Ӧ
			int flag = 0;
			if (!TestUsernameAndPassword(username, password, flag))
			{
				if (flag == 0)
					SendMessage("0", cli);
				if (flag == 1)
					SendMessage("1", cli);
				continue;
			}
			//��ѯ���û��Ƿ��ظ���¼
			if (TestDuplicateLogin(username))
			{
				SendMessage("2", cli);
				continue;
			}
			//���Ϸ���δ��¼���û������б�
			int receiver_port_int = atoi(receiver_port.c_str());
			user newuser(username, address, userport, receiver_port_int);
			usertable.push_back(newuser);

			printmessage = "(������Ϣ)" + newuser.username + "������";               //����Ҫ��ӡ����Ϣ
			sendmessage = printmessage;                                           //����Ҫת������Ϣ	
			SendMessage("Y", cli);                                                //��ͻ��˷��͵�¼�ɹ��Ļ�Ӧ
		}
		else if (infortype[0] == 'R')                 //ע����Ϣ
		{
			string userinfor = infortype.substr(1);                  //��ȥ��Ϣ����		
			string username, password;
			extractRegisteruserinfor(userinfor, username, password); //��ȡ�û���������

																	 //����û����Ƿ��Ѿ�ע���
			if (TestDuplicateRigister(username))
			{
				SendMessage("N", cli);
				continue;
			}
			//���ļ�д����ע����û���������
			if (!Checktxt())
			{
				SendMessage("N", cli);
				continue;
			}
			fstream out("C:\\userform\\userform.txt", ios::app);
			out << userinfor << endl;
			out.close();
			//����ע��ɹ��Ļ�Ӧ
			SendMessage("Y", cli);
			cout << "ע��ɹ�" << endl << "���û���Ϊ:" << username << endl << endl;
			continue;
		}
		else if (infortype[0] == 'G')                                          //Ⱥ����Ϣ
		{
			string message = infortype.substr(1);
			string sendername = Getusername(address, userport);                  //��ȡ����������
			if (sendername == "")   continue;
			printmessage = "(Ⱥ��Ϣ��" + sendername + ":" + message;             //����Ҫ��ӡ����Ϣ
			sendmessage = printmessage;
			//sendmessage = "G#"+sendername + ":" + message;                       //����Ҫת������Ϣ
		}
		else if (infortype[0] == 'P')                     //˽����Ϣ
		{
			if (infortype[1] == 'L')                      //��ȡ���ߺ����б������
			{
				Sendonlinelist();
				continue;
			}
			if (infortype[1] == 'M')                      //˽����Ϣ
			{
				string message = infortype.substr(2);
				string sendername = Getusername(address, userport);  //��ȡ����������
				if (sendername == "")  continue;
				//��ȡ����������
				string receivername;
				extactPersonalMessageReceivername(message, receivername);
				//���������Ƿ�����
				int i = Getuserindex(receivername);
				if (i == usertable.size())                              //�������Ѿ�����
				{
					SendMessage("N", cli);
					continue;
				}
				SendMessage("Y", cli);                                  //���ͷ����ͳɹ�����Ӧ
				printmessage = "(˽��Ϣ)" + sendername + "->" + receivername + ":" + message;               //����Ҫ��ӡ����Ϣ
				cout << printmessage << endl;
				cout << "�û�ip:" << address << endl;
				cout << "�û��˿�:" << userport << endl;
				cout << "��ǰ��������:" << usertable.size() << endl << endl;
				sendmessage = printmessage;                                                                 //����Ҫ���͵���Ϣ
				SendMessage(sendmessage, usertable[i].receiver);
				if (sendername != receivername)
				{
					int j = Getuserindex(sendername);
					SendMessage(sendmessage, usertable[j].receiver);
				}
				continue;
			}
		}
		else if (infortype == "exit")
		{
			string sendername = Getusername(address, userport);
			if (sendername == "") continue;
			int i = Getuserindex(sendername);
			if (i >= usertable.size() || i < 0) continue;
			SendMessage("exit", usertable[i].receiver);                                 //����û���ʾ�������˳�����
			usertable.erase(usertable.begin() + i);
			printmessage = "(������Ϣ)" + sendername + "������";                         //����Ҫ��ӡ����Ϣ
			sendmessage = printmessage;                                                 //����Ҫת������Ϣ

		}
		//�ڷ������ϴ�ӡ��Ϣ	
		cout << printmessage << endl;
		cout << "�û�ip:" << address << endl;
		cout << "�û��˿�:" << userport << endl;
		cout << "��ǰ��������:" << usertable.size() << endl << endl;
		//��ͻ��˷�����Ϣ
		for (int i = 0; i < usertable.size(); i++)
			SendMessage(sendmessage, usertable[i].receiver);
	}
}

int main()
{
	server x;
	if (x.Startup() == false)
		return 0;
	if (x.SetServerSocket() == false)
		return 0;
	x.work();
	return 0;
}