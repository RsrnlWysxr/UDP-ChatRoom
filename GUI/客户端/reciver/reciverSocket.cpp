//
// Created by 李一航 on 2019/1/5.
//

#include "reciverSocket.h"

reciverSocket::reciverSocket()
{
    //读取分配好的端口
    ifstream in("/Users/liyihang/QT_learn/test02/cmake-build-debug/port.txt");
    string receiver_port;
    string username;
    getline(in, receiver_port);
    getline(in, username);
    in.close();
    // remove("port.txt");
    int receiver_port_int = atoi(receiver_port.c_str());

    receiver.sin_family = AF_INET;
    receiver.sin_port = htons(receiver_port_int);    //htons()函数把一个双字节主机字节顺序的数转换为网络字节顺序的数
    receiver.sin_addr.s_addr = htonl(INADDR_ANY);    //htonl()函数把一个主机字节顺序的数转换为网络字节顺序的数
    rSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (rSocket == -1)
    {
        exit(0);
    }
    if ( ::bind(rSocket, (struct sockaddr*)&receiver, sizeof(receiver)) < 0 )
    {
        exit(0);
    }
}

string reciverSocket::work()
{
    memset(recv_buf, 0, sizeof(recv_buf));         //初始化接收缓冲区
    int iRecv = recvfrom(rSocket, recv_buf, BUFFER_LENGTH, 0, (struct sockaddr*)&ser, (socklen_t *)&ser_length);
    string transmessage(recv_buf);
    if (iRecv == -1)
    {
        return "";
    }
    else
        return transmessage;
}

reciverSocket::~reciverSocket() = default;
