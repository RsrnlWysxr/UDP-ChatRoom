//
// Created by 李一航 on 2019/1/3.
//

#ifndef TEST2_LISTWIDGET_H
#define TEST2_LISTWIDGET_H

#include <QMainWindow>
#include <QPushButton>
#include <string>
#include <QTextEdit>
#include "ChatWidget.h"
using std::string;

class ListWidget: public QMainWindow
{
    Q_OBJECT
public:
    explicit ListWidget(QMainWindow* parent = nullptr);
    ~ListWidget() override;

    // 对应信号的槽函数
    void returnLoginSlot();

signals:
    /*
     * 信号必须由signals关键字来声明
     * 信号没有返回值，但可以有参数
     * 信号就是函数的声明，只需声明，无需定义
     * 使用：emit mySignals()
     * 信号可以重载
     * 重载的信号，使用函数指针区分
     * */
    void returnLoginSignal();

private:
    QPushButton returnLogin_pb;
    QPushButton groupChat_pb;
    QTextEdit* textEditIn_te_p;
    ChatWidget* chatWidget_wg;
};


#endif //TEST2_LISTWIDGET_H
