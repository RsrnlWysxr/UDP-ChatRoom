//
// Created by 李一航 on 2019/1/4.
//

#include "RegisterWidget.h"
#include "client.h"
#include <QLabel>
#include <QAbstractButton>

RegisterWidget::RegisterWidget(QWidget *parent)
:QWidget(parent)
{
    // 窗口设置
    this->resize(400,300);
    this->setWindowTitle("注册");
    account_le = new QLineEdit();
    passWord_le = new QLineEdit();
    // 注册按钮
    register_b.setParent(this);
    register_b.setText("注册");
    register_b.move(60,225);
    connect(&register_b, &QPushButton::pressed, this, &RegisterWidget::registerSlot);

    // 返回按钮
    returnLogin_b.setParent(this);
    returnLogin_b.setText("返回");
    returnLogin_b.move(280,225);
    connect(&returnLogin_b, &QPushButton::pressed, this, &RegisterWidget::returnLoginSlot);

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
    passWord_le->setParent(this);
    // 匿名显示
    passWord_le->setEchoMode(QLineEdit::Password);
    passWord_le->move(150,150);
}

void RegisterWidget::registerSlot()
{
    if(myClient.Register(account_le->text().toStdString(), passWord_le->text().toStdString()))
    {
        // 非模态对话框,可以忽略
        auto registerAfter_mb_p = new QMessageBox();
        registerAfter_mb_p->resize(180,30);
        registerAfter_mb_p->setAttribute(Qt::WA_DeleteOnClose);
        registerAfter_mb_p->setText("注册成功");
        registerAfter_mb_p->show();
        returnLoginSlot();
    }
    else
    {
        // 模态对话框,不可忽略
        auto registerAfter_mb_p = new QMessageBox();
        registerAfter_mb_p->resize(180,30);
        registerAfter_mb_p->setText("该账号已经存在");
        registerAfter_mb_p->exec();
    }
    account_le->clear();
    passWord_le->clear();
}

void RegisterWidget::returnLoginSlot()
{
    emit returnLoginSignal();
}

RegisterWidget::~RegisterWidget() = default;
