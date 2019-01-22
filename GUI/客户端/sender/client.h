//
// Created by 李一航 on 2019/1/4.
//

#ifndef TEST2_CLIENT_H
#define TEST2_CLIENT_H

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
    void End();                         //最终关闭
    void disconnect();                  //check out
    int Login(string, string);
    void SetServerAddress(string);
    int GeneratePort();               //随机生成显示器端口号
    bool Getonlinelist();             //获得在线的用户名
    bool Register(string, string);                  //注册
    int GroupChat(string);                    //群聊
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

extern client myClient;

#endif //TEST2_CLIENT_H
