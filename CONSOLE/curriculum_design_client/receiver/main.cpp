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

int main()
{
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
    int rSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (rSocket == -1)
    {
        cout << "socket Failed:" << endl;
        return 0;
    }
    if ( ::bind(rSocket, (struct sockaddr*)&receiver, sizeof(receiver)) < 0 )
    {
        cout << "bind Failed:"  << endl;
        return 0;
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
        int iRecv = recvfrom(rSocket, recv_buf, BUFFER_LENGTH, 0, (struct sockaddr*)&ser, (socklen_t *)&ser_length);
        string transmessage(recv_buf);
        if (iRecv == -1)
        {
            cout << "recvfrom Failed:"  << endl;
            break;
        }
        else if (transmessage == "exit") break;
        else
            cout << transmessage << endl;
    }
    close(rSocket);
    return 0;
}