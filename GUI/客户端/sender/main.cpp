#include <QApplication>
#include <string>
#include <iostream>
#include "InputIpWidget.h"
#include "MyWidget.h"
#include "client.h"

client myClient;

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    if (!myClient.Startup())
    {
       return 0;
    }
    InputIpWidget inputIpWidget_wid;
    inputIpWidget_wid.show();
    return app.exec();
}