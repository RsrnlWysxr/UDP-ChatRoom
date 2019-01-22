//
// Created by 李一航 on 2018/12/26.
//

#ifndef CURRICULUM_DESIGN_SERVER_H
#define CURRICULUM_DESIGN_SERVER_H

#include <string>
#include <iostream>
#include <vector>
#include <fstream>


#include <sys/socket.h>   //connect,send,recv,setsockopt...
#include <sys/types.h>
#include <netinet/in.h>     // sockaddr_in,htons
#include <poll.h>          //poll,pollfd
#include <arpa/inet.h>     //inet_addr,inet_aton
#include <unistd.h>        //read,write
#include <netdb.h>         //gethostbyname

#define BUFFER_LENGTH 1024
#define DEFAULT_PORT 6464

using namespace std;

class user
{
public:
    user(string username,string ip,int sender_port,int receiver_port)
    {
        this->username = username;
        this->ip = ip;
        this->sender_port = sender_port;
        this->receiver_port = receiver_port;

        //设置接收器的地址
        receiver.sin_family = AF_INET;
        receiver.sin_port = htons(receiver_port);
        char *addr = new char[ip.length() + 1];
        strcpy(addr, ip.c_str());
        receiver.sin_addr.s_addr = inet_addr(addr);
    }
    string username;              //用户名
    string ip;                    //客户端ip地址
    int sender_port;              //发送器端口
    int receiver_port;            //接收器端口
    struct sockaddr_in receiver;  //存储接收器的地址
};

class server
{
public:
    bool SetServerSocket();
    //设置服务器用来监听信息的socket套接字
    bool Checktxt();
    //检测存储文件是否存在，若不存在，创建一个
    void work();
    //服务器运行的主函数
    void SendMessage(string message, struct sockaddr_in x);
    //发送信息的函数
    void Sendonlinelist();
    //向客户端发送好友在线列表
    bool TestUsernameAndPassword(string username, string password, int &flag);
    //测试用户名和密码是否正确
    bool TestDuplicateLogin(string username);
    //测试是否重复登录
    bool TestDuplicateRigister(string username);
    //测试是否重复注册
    string Getusername(string ip,int port);
    //根据ip和端口号获得用户名
    int  Getuserindex(string username);
    //根据用户名获得用户在在线用户表的索引号
    void extractLoginuserinfor(string userinfor, string &username, string &password, string &receiverport);
    //提取登录请求中的用户名密码和显示器端口号
    void extractRegisteruserinfor(string userinfor, string&username,string&password);
    //提取注册请求中的用户名和密码
    void extactPersonalMessageReceivername(string &message,string &receivername);
    //提取私聊消息中的接收者的姓名

private:
    int sSocket;                            //用来接收消息的套接字
    struct sockaddr_in ser;                    //服务器地址
    struct sockaddr_in cli;                    //客户地址
    int cli_length=sizeof(cli);                //客户地址长度
    char recv_buf[BUFFER_LENGTH];              //接收数据的缓冲区
    vector<user> usertable;                    //在线用户表
    string sendmessage,printmessage;           //存储服务器转发、打印用的字符串
    int iSend, iRecv;                          //存储服务器发送和接收的字符串的长度
};

bool server::SetServerSocket()
{
    sSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (sSocket == -1)
    {
        cout << "Server's Socket Create Failed" << endl;
        return false;
    }
    //建立服务器端地址
    ser.sin_family = AF_INET;
    ser.sin_port = htons(DEFAULT_PORT);               //htons()函数把一个双字节主机字节顺序的数转换为网络字节顺序的数
    ser.sin_addr.s_addr = htonl(INADDR_ANY);          //htonl()函数把一个主机字节顺序的数转换为网络字节顺序的数
    if( ::bind(sSocket, (sockaddr*)&ser, (socklen_t )sizeof(ser)) < 0 )
    {
        cout << "Server Bind Failed" << endl;
        return false;
    }
    return true;
}

void server::work()
{
    cout << "-----------------" << endl;
    cout << "Server running" << endl;
    cout << "-----------------" << endl;
    while (true)                                       //进入一个无限循环，进行数据接收和发送
    {
        memset(recv_buf, 0, sizeof(recv_buf));         //初始化接收缓冲区
        iRecv = recvfrom(sSocket, recv_buf, sizeof(recv_buf), 0, (struct sockaddr*)&cli, (socklen_t *)&cli_length);
        if (iRecv == -1)
        {
            cout << "Recvfrom Failed" << endl;
            continue;
        }

        //获取发送方的地址（ip和端口）
        char *x = inet_ntoa(cli.sin_addr); string address(x);         //获取客户端ip
        int userport = ntohs(cli.sin_port);                           //获取客户端端口

        string infortype=string(recv_buf);                            //根据infortype[0]来判断消息的类型
        if (infortype[0] == 'L')                                      //登录请求
        {
            string userinfor = infortype.substr(1);                   //除去消息类型
            string username,password,receiver_port;
            extractLoginuserinfor(userinfor, username, password, receiver_port);  //提取用户名和密码
            //向不合法用户发送登录失败的回应
            int flag = 0;
            if (!TestUsernameAndPassword(username,password,flag))
            {
                SendMessage("1", cli);
                continue;
            }
            //查询该用户是否重复登录
            if (TestDuplicateLogin(username))
            {
                SendMessage("2", cli);
                continue;
            }
            //将合法的未登录的用户加入列表
            int receiver_port_int = atoi(receiver_port.c_str());
            user newuser(username, address, userport, receiver_port_int);
            usertable.push_back(newuser);

            printmessage="(上线消息)"+ newuser.username + "已上线";               //设置要打印的消息
            sendmessage = printmessage;                                           //设置要转发的消息
            SendMessage("Y", cli);                                                //向客户端发送登录成功的回应
        }
        else if (infortype[0] == 'R')                 //注册信息
        {
            string userinfor = infortype.substr(1);                  //除去消息类型
            string username, password;
            extractRegisteruserinfor(userinfor, username, password); //提取用户名和密码

            //检测用户名是否已经注册过
            if (TestDuplicateRigister(username))
            {
                SendMessage("N", cli);
                continue;
            }
            //向文件写入新注册的用户名和密码
            if (!Checktxt())
            {
                SendMessage("N", cli);
                continue;
            }
            fstream out("userform.txt", ios::app);
            out << userinfor << endl;
            out.close();
            //发送注册成功的回应
            SendMessage("Y", cli);
            cout << "注册成功" << endl<<"新用户名为:"<<username<<endl<<endl;
            continue;
        }
        else if (infortype[0] == 'G')                                          //群聊消息
        {
            string message = infortype.substr(1);
            string sendername = Getusername(address, userport);                  //获取发送者姓名
            if (sendername == "")   continue;
            printmessage = "(群消息）" + sendername + ":" + message;             //设置要打印的消息
            sendmessage = printmessage;
            //sendmessage = "G#"+sendername + ":" + message;                       //设置要转发的消息
        }
        else if (infortype[0] == 'P')                     //私聊消息
        {
            if (infortype[1] == 'L')                      //获取在线好友列表的请求
            {
                Sendonlinelist();
                continue;
            }
            if (infortype[1] == 'M')                      //私聊消息
            {
                string message = infortype.substr(2);
                string sendername = Getusername(address, userport);  //提取发送者姓名
                if (sendername == "")  continue;
                //提取接收者姓名
                string receivername;
                extactPersonalMessageReceivername(message, receivername);
                //检查接收者是否离线
                int i = Getuserindex(receivername);
                if (i == usertable.size())                              //接收者已经离线
                {
                    Sendonlinelist();                                   //重新将一份好友在线列表发送给发送方
                    continue;
                }
                SendMessage("Y", cli);                                  //向发送方发送成功的响应
                printmessage = "(私消息)" + sendername + "->" + receivername + ":" + message;               //设置要打印的消息
                cout << printmessage << endl;
                cout << "用户ip:" << address << endl;
                cout << "用户端口:" << userport << endl;
                cout << "当前在线人数:" << usertable.size() << endl << endl;
                sendmessage= printmessage;                                                                 //设置要发送的消息
                SendMessage(sendmessage, usertable[i].receiver);
                continue;
            }
        }
        else if (infortype == "exit")
        {
            string sendername = Getusername(address, userport);
            if (sendername == "") continue;
            int i = Getuserindex(sendername);
            if (i >= usertable.size() || i < 0) continue;
            SendMessage("exit", usertable[i].receiver);                                 //向该用户显示器发送退出命令
            usertable.erase(usertable.begin() + i);
            printmessage = "(下线消息)" +sendername + "已下线";                         //设置要打印的消息
            sendmessage = printmessage;                                                 //设置要转发的消息

        }
        //在服务器上打印消息
        cout << printmessage << endl;
        cout << "用户ip:" << address << endl;
        cout << "用户端口:" << userport << endl;
        cout << "当前在线人数:" << usertable.size() << endl << endl;
        //向客户端发送消息
        for (int i = 0; i < usertable.size(); i++)
            SendMessage(sendmessage, usertable[i].receiver);
    }
}

void server::SendMessage(string message, struct sockaddr_in x)
{
    char *send_buf = new char[message.length() + 1];
    strcpy(send_buf, message.c_str());
    int rSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (rSocket == -1)
    {
        cout << "socket Failed" << endl;
        return;
    }
    iSend = sendto(rSocket, send_buf, message.length() + 1, 0, (struct sockaddr*)&(x), sizeof(x));
    if (iSend == -1)
    {
        cout << "sendto failed" << endl;
        close(rSocket);
        return;
    }
    close(rSocket);
}
void server::Sendonlinelist()
{
    string onlinelist;
    for (int i = 0; i < usertable.size(); i++)
        onlinelist = onlinelist + usertable[i].username + "#";
    onlinelist = onlinelist + "$";                //结束标志
    SendMessage(onlinelist, cli);
}
bool server::TestUsernameAndPassword(string username, string password, int &flag)
{
    if (!Checktxt())
    {
        cout << "无法找到存储文件." << endl << endl;
        flag = 0;                                 //未找到用户名的标志
        return false;
    }
    fstream in("userform.txt");
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
        if (username_txt == username)         //该用户名存在
        {
            if (password == password_txt)     //且密码正确
            {
                in.close();
                return true;                  //返回验证成功
            }
            cout << "用户" << username << "登录密码错误" << endl << endl;       //返回密码错误的信息
            flag = 1;                        //密码错误的标志
            return false;
        }
    }
    in.close();
    cout << "未注册过的用户:" << username << endl << endl;
    flag = 0;                                 //未找到用户名的标志
    return false;
}
bool server::TestDuplicateLogin(string username)
{
    int i;
    for (i = 0; i < usertable.size(); i++)
        if (usertable[i].username == username) break;
    if (i == usertable.size())     //该用户还没有登录过
        return false;
    else
    {
        cout << "用户" << username << "重复登录" << endl;
        return true;
    }
}
bool server::TestDuplicateRigister(string username)
{
    if (!Checktxt())
    {
        cout << "无法找到存储文件." << endl << endl;
        return true;
    }
    fstream in("userform.txt");
    string line;
    while (getline(in, line))
    {
        string username_txt;
        for (int i = 0; i < line.size(); i++)
        {
            if (line[i] == '#')
            {
                username_txt = line.substr(0, i);              //提取用户名
                if (username_txt == username)                  //对比，相等则表明已经注册过
                {
                    in.close();
                    cout << "用户名" << username << "重复注册" << endl << endl;
                    return true;
                }
                break;                                         //否则继续对比下一个用户名
            }
        }
    }
    in.close();
    return false;                                               //代码执行到这说明该用户名还没有注册过
}
string server::Getusername(string ip, int port)
{
    for (int i = 0; i < usertable.size(); i++)
        if (usertable[i].ip == ip&&usertable[i].sender_port == port)
            return usertable[i].username;
    cout << "非法的用户连接上服务器" << endl;
    cout << "ip地址为:" << ip << endl << "端口号为:" << port << endl;
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
    for (i = 0; i < userinfor.length(); i++)           //提取用户名
    {
        if (userinfor[i] == '#')
        {
            username = userinfor.substr(0, i);
            break;
        }
    }
    for (int j = i + 1; j < userinfor.length(); j++)  //提取密码和显示器端口号
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
    FILE *fp = fopen("userform.txt", "r");

    if (fp == NULL)
    {
        ofstream out;
        out.open( "userform.txt", ios::out );
        if (!out)
            return false;
        out.close();
        return true;
    }
    return true;
}




#endif //CURRICULUM_DESIGN_SERVER_H
