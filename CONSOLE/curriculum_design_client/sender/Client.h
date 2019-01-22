//
// Created by 李一航 on 2018/12/26.
//

#ifndef CURRICULUM_DESIGN_CLIENT_CLIENT_H
#define CURRICULUM_DESIGN_CLIENT_CLIENT_H


#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>


#include <sys/socket.h>   //connect,send,recv,setsockopt...
#include <sys/types.h>
#include <netinet/in.h>     // sockaddr_in,htons
#include <poll.h>          //poll,pollfd
#include <arpa/inet.h>     //inet_addr,inet_aton
#include <unistd.h>        //read,write
#include <netdb.h>         //gethostbyname



#define DEFAULT_PORT 6464
#define DATA_BUFFER 1024

using namespace std;

class client
{
public:
    bool Startup();
    void SetServerAddress();
    int GeneratePort();               //随机生成显示器端口号
    bool Getonlinelist();             //获得在线的用户名
    void work();                      //发送器的主函数
private:
    int sClient;                       //发送信息和接收信息时使用的套接字
    struct sockaddr_in ser;               //保存服务器的地址
    int ser_length = sizeof(ser);
    struct sockaddr_in communication;
    int communication_length = sizeof(communication);
    char recv_buf[DATA_BUFFER];           //接收信息的缓冲区
    int receiver_port;                    //显示器的端口号
    vector<string> onlinelist;            //保存在线用户的用户名
    int iSend, iRecv;
};

bool client::Startup()
{
    sClient = socket(AF_INET, SOCK_DGRAM, 0);
    if (sClient == -1)
    {
        cout << "Socket Failed:" << endl;
        return false;
    }
    return true;
}
void client::SetServerAddress()
{
    cout << "请输入ip地址:";
    string iptemp;
    cin >> iptemp;
    char *ip = new char[iptemp.length() + 1];
    strcpy(ip, iptemp.c_str());
    //建立服务器端地址
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
bool client::Getonlinelist()            //向服务器请求获取好友在线列表
{
    if (onlinelist.size() > 0)
        onlinelist.clear();
    char getonlinelist[3] = "PL";
    iSend = sendto(sClient, getonlinelist, 3, 0, (struct sockaddr*)&ser, ser_length);
    if (iSend == -1)
    {
        cout << "sendto()Failed:" << endl;
        return false;
    }
    memset(recv_buf, 0, sizeof(recv_buf));
    iRecv = recvfrom(sClient, recv_buf, sizeof(recv_buf), 0, (struct sockaddr*)&communication, (socklen_t *)&communication_length);
    if (iRecv == -1)
    {
        cout << "recvfrom Failed" << endl;
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
    cout << "在线好友列表" << endl;
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
        cout << "****************************************" << endl;
        cout << "*                                      *" << endl;
        cout << "*       1.登录  2.注册  3.退出         *" << endl;
        cout << "*                                      *" << endl;
        cout << "****************************************" << endl;

        string choice;
        getline(cin, choice);
        if (choice == "1")
        {
            cout << "请输入用户名:";
            string username;
            getline(cin, username);
            cout << "请输入密码:";
            string password;
            getline(cin, password);
            //产生显示器端口
            receiver_port = GeneratePort();
            //将端口号写入文件供显示器程序读取
            ofstream out("port.txt");
            out << receiver_port << "\n" << username;
            out.close();

            string init_infortemp = "L" + username + "#" + password + "#" + to_string(receiver_port);
            char *init_infor = new char[init_infortemp.length() + 1];
            strcpy(init_infor, init_infortemp.c_str());
            //向服务器验证用户信息
            iSend = sendto(sClient, init_infor, init_infortemp.length() + 1, 0, (struct sockaddr*)&ser, ser_length);
            //接收服务器回应的消息
            iRecv = recvfrom(sClient, recv_buf, sizeof(recv_buf), 0, (struct sockaddr*)&communication, (socklen_t *)&communication_length);
            if (iRecv == -1)
            {
                cout << "recvfrom Failed" << endl;
                cout << "未收到服务器的响应，登录失败,请输入Y返回首页:";
                string ret;
                while (getline(cin, ret))
                {
                    if (ret == "Y")break;
                    cout << "未收到服务器的响应，登录失败,请输入Y返回首页:";
                }
                continue;
            }
            if (recv_buf[0] == 'Y')   //登录成功
            {
                // 运行显示器
          /*      if( fork() == 0 )
                {

                }
                else
                {
                    cout << "登陆成功" << endl;
                }*/
                system("open -a Terminal.app /Users/liyihang/curriculum_design/curriculum_design_client/receiver/cmake-build-debug/receiver");
                cout << "登陆成功" << endl;
            }
            else if (recv_buf[0] == '0')
            {
                cout << "未注册用户名，登录失败，请输入Y返回首页:";
                string ret;
                while (getline(cin, ret))
                {
                    if (ret == "Y")break;
                    cout << "未注册用户名，登录失败，请输入Y返回首页:";
                }
                continue;
            }
            else if (recv_buf[0] == '1')
            {
                cout << "密码错误，登录失败，请输入Y返回首页:" << endl;
                string ret;
                while (getline(cin, ret))
                {
                    if (ret == "Y")break;
                    cout << "密码错误，登录失败，请输入Y返回首页:";
                }
                continue;
            }
            else if (recv_buf[0] == '2')
            {
                cout << "重复登录，登录失败，请输入Y返回首页:" << endl;
                string ret;
                while (getline(cin, ret))
                {
                    if (ret == "Y")break;
                    cout << "重复登录，登录失败，请输入Y返回首页:";
                }
                continue;
            }

            //选择聊天方式
            while (true)
            {
                cout << "---------------------------------------------------" << endl;
                cout << "                 用户名:" << username << endl << endl;;
                cout << "            1.私聊  2.群聊  3.退出登录             " << endl << endl;
                cout << "---------------------------------------------------" << endl;
                string mode;
                getline(cin, mode);
                if (mode == "1")    //私聊
                {
                    cout << "私聊模式中，输入return返回上一级" << endl << endl;
                    if (!Getonlinelist())    continue;                           //获取好友在线列表失败
                    cout << "请选择私聊对象的序号" << endl;
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
                    while (true)                     //向该用户循环发送消息，直到输入return退出
                    {
                        cout << "正在和" << onlinelist[index] << "私聊中" << "，输入return返回上一级" << endl << endl;
                        string message;
                        getline(cin, message);
                        if (message == "return")
                        {
                            break;
                        }
                        message = "PM" + onlinelist[index] + "#" + message;
                        char *buf = new char[message.length() + 1];
                        strcpy(buf, message.c_str());
                        iSend = sendto(sClient, buf, message.length() + 1, 0, (struct sockaddr*)&ser, ser_length);
                        if (iSend == -1)
                        {
                            cout << "sendto()Failed:" << endl;
                            break;
                        }
                        delete[]buf;
                        iRecv = recvfrom(sClient, recv_buf, sizeof(recv_buf), 0, (struct sockaddr*)&communication, (socklen_t *)&communication_length);
                        if (recv_buf[0] == 'Y') continue;
                        else
                        {
                            cout << onlinelist[index] << "已下线" << "输入Y返回主菜单";
                            string ret;
                            while (getline(cin, ret))
                            {
                                if (ret == "Y") break;
                                cout << onlinelist[index] << "已下线" << "输入Y返回主菜单";
                            }
                            break;
                        }
                    }
                }
                else if (mode == "2")    //群聊
                {
                    while (true)
                    {
                        cout << "群聊模式，输入return返回上一级" << endl << endl;
                        string message;
                        getline(cin, message);
                        if (message == "return")
                        {
                            break;
                        }

                        message = "G" + message;
                        char *buf = new char[message.length() + 1];
                        strcpy(buf, message.c_str());
                        iSend = sendto(sClient, buf, message.length() + 1, 0, (struct sockaddr*)&ser, ser_length);
                        delete[]buf;
                        if (iSend == -1)
                        {
                            cout << "sendto()Failed:" << endl;
                            break;
                        }
                    }
                    continue;
                }
                else if (mode == "3")                             //退出登录
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
            cout << "请设置用户名:";
            string username;
            getline(cin, username);
            cout << "请设置登录密码:";
            string password;
            getline(cin, password);
            string init_infortemp = "R" + username + "#" + password;
            char *init_infor = new char[init_infortemp.length() + 1];
            strcpy(init_infor, init_infortemp.c_str());
            //向服务器发送注册用户信息
            iSend = sendto(sClient, init_infor, init_infortemp.length() + 1, 0, (struct sockaddr*)&ser, ser_length);
            //接收服务器回应的消息
            iRecv = recvfrom(sClient, recv_buf, sizeof(recv_buf), 0, (struct sockaddr*)&communication, (socklen_t *)&communication_length);
            if (recv_buf[0] == 'Y')
            {
                cout << "注册成功" << endl;
                continue;
            }
            else
            {
                cout << "用户名已存在，注册失败，请输入Y返回首页:" << endl;
                string ret;
                while (getline(cin, ret))
                {
                    if (ret == "Y")break;
                    cout << "用户名已存在，注册失败，请输入Y返回首页:";
                }
                continue;
            }
        }
        else if (choice == "3")
        {
            close(sClient);
            return;
        }
        else
            continue;
    }
}

#endif //CURRICULUM_DESIGN_CLIENT_CLIENT_H
