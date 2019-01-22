//
// Created by 李一航 on 2019/1/4.
//

#include <QLabel>
#include <string>
#include "InputIpWidget.h"
#include "MyWidget.h"
#include "client.h"

using std::string;


InputIpWidget::InputIpWidget(QWidget *parent)
:QWidget(parent)
{
    // 设置窗口
    resize(300,75);
    setWindowTitle("登陆服务器");
    auto ip_lb = new QLabel(this);
    ip_lb->setText("服务器ip:");
    ip_lb->move(40,15);
    ip_le.setParent(this);
    ip_le.move(110,15);

    // 设置按钮
    ipConfirm_pb.setParent(this);
    ipConfirm_pb.setText("登入服务器");
    ipConfirm_pb.move(100,40);
    connect(&ipConfirm_pb, &QPushButton::pressed, this, &InputIpWidget::loginServerSlot);
}

InputIpWidget::~InputIpWidget() = default;

void InputIpWidget::loginServerSlot()
{
    myClient.SetServerAddress(ip_le.text().toStdString());
    hide();
    login_wg.show();
}


