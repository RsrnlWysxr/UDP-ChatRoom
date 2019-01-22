//
// Created by 李一航 on 2019/1/3.
//

#ifndef TEST02_MYWIDGETS_H
#define TEST02_MYWIDGETS_H

#include <QWidget>
#include <QLineEdit>
#include "ListWidget.h"
#include "RegisterWidget.h"

class MyWidget: public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget* parent = nullptr);
    ~MyWidget() override;
    /*
     * 自定义槽，普通函数用法
     * 槽函数与信号一致（参数，返回值）
     * 由于信号没有返回值，所以槽函数一定没有返回值
     * 信号的参数，传给槽函数
     * */
private slots:  void loginSlot();
private slots:  void returnLoginSlot();
private:
    QPushButton exit_b;
    QPushButton *login_b;
    QPushButton *register_b;
    ListWidget list_wg;
    RegisterWidget register_wg;
    QLineEdit* account_le;
    QLineEdit* passWord_le;

};
#endif //TEST02_MYWIDGETS_H
