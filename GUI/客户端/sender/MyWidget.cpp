//
// Created by 李一航 on 2019/1/3.
//
#include "MyWidget.h"
#include "client.h"
#include <iostream>
#include <QLabel>
#include <QMessageBox>

MyWidget::MyWidget(QWidget* parent)
:QWidget(parent)
{
    // 窗口设置
    resize(400,300);
    setWindowTitle("登陆");
    account_le = new QLineEdit;
    passWord_le = new QLineEdit;

    // 登陆按钮
    login_b = new QPushButton(this);
    login_b->setText("登陆");
    login_b->move(60,225);
    connect(login_b, &QPushButton::pressed, this, &MyWidget::loginSlot);

    // 用户名文本框
    auto account_lb = new QLabel(this);
    account_lb->setText("登录名");
    account_lb->move(75,75);
    account_le->setParent(this);
    account_le->move(150,75);

    // 密码文本框
    auto passWord_lb = new QLabel(this);
    passWord_lb->setText("密 码");
    passWord_lb->move(75,150);
    // 匿名显示
    passWord_le->setEchoMode(QLineEdit::Password);
    passWord_le->setParent(this);
    passWord_le->move(150,150);



    // 注册按钮
    register_b = new QPushButton(this);
    register_b->setText("注册");
    register_b->move(170,225);
    connect(register_b, &QPushButton::pressed,
            /*
             * Lamda表达式
             * []中：为可见变量
             * =：外部局部变量，类中成员变量，按值传递
             * this：类中成员变量，按值传递
             * &：外部局部变量，引用传递
             * ()中：为传入的参数*/
            [=]()
            {
                hide();
                register_wg.show();
            }
            );
    // 处理register_wg下returnLogin_b的信号
    connect(&register_wg, &RegisterWidget::returnLoginSignal,
            [=]()
            {
                show();
                register_wg.hide();
            }
            );

    // 退出按钮
    exit_b.setParent(this);
    exit_b.setText("退出");
    exit_b.move(280,225);
    connect(&exit_b, &QPushButton::pressed,
            [=]()
            {
                myClient.End();
                close();
            }
            );

    // connect可以使用SIGNAL和SLOT宏
    // 处理list_wg下returnLogin_b的信号
    connect(&list_wg, &ListWidget::returnLoginSignal, this, &MyWidget::returnLoginSlot);

}

MyWidget::~MyWidget()
{
    delete login_b;
}
void MyWidget::loginSlot()
{
    int ret_i = myClient.Login(account_le->text().toStdString(), passWord_le->text().toStdString());
    auto loginAfter_mb = new QMessageBox();
    loginAfter_mb->resize(180,30);
    switch (ret_i)
    {
        case 0:
        {
            list_wg.show();
            hide();
            // system("open -a Terminal.app /Users/liyihang/curriculum_design/curriculum_design_client/receiver/cmake-build-debug/receiver");
            break;
        }
        case -1:
        {
            loginAfter_mb->setText("登陆失败,服务器未响应");
            loginAfter_mb->exec();
            break;
        }
        case 1:
        {
            loginAfter_mb->setText("登陆失败,账号或密码错误");
            loginAfter_mb->exec();
            break;
        }
        case 2:
        {
            loginAfter_mb->setText("登陆失败,已登陆");
            loginAfter_mb->exec();
            break;
        }
        default:
            assert(ret_i==100);
    }
}

void MyWidget::returnLoginSlot()
{
    show();
    list_wg.hide();
}
