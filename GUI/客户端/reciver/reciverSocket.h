//
// Created by 李一航 on 2019/1/5.
//

#ifndef RECIVER_RECIVERSOCKET_H
#define RECIVER_RECIVERSOCKET_H

#include <iostream>
#include <string>
#include <fstream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>     // sockaddr_in,htons
#include <poll.h>          //poll,pollfd
#include <arpa/inet.h>     //inet_addr,inet_aton
#include <unistd.h>        //read,write
#include <netdb.h>         //gethostbyname

#define DEFAULT_PORT 6464
#define BUFFER_LENGTH 1024

using namespace std;


class reciverSocket
{
public:
    reciverSocket();
    ~reciverSocket();
    string work();


private:
    int rSocket;
    char recv_buf[BUFFER_LENGTH];                  //接收数据的缓冲区
    struct sockaddr_in ser{};                        //客户端地址
    int ser_length = sizeof(ser);                  //客户端地址长度
    struct sockaddr_in receiver{};
};


extern reciverSocket reciver;


#endif //RECIVER_RECIVERSOCKET_H
