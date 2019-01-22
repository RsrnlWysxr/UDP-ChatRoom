#include <QApplication>
#include "outChatWidget.h"
#include "reciverSocket.h"

reciverSocket reciver;

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    outChatWidget out_wg;
    out_wg.show();
    QApplication::processEvents();
    while (true)
    {
        out_wg.work();
        QApplication::processEvents();
    }
}