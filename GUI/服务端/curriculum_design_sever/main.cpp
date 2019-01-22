#include <iostream>
#include "Server.h"
#include <QApplication>
#include <QLabel>

int main()
{
    server x;
    x.SetServerSocket();
    x.work();
    return 0;
}