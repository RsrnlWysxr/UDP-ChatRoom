//
// Created by 李一航 on 2019/1/5.
//

#include "ChatWidget.h"
#include <QVBoxLayout>
#include "client.h"
#include <QMessageBox>

ChatWidget::ChatWidget(QWidget *parent)
:QWidget(parent)
{
    // 设置窗口
    resize(500,160);
    setWindowTitle("输入栏");
    move(450,600);
    // 编辑栏
    input_te_p = new QTextEdit;
    // 发送按钮
    send_pb.setText("发送");
    send_pb.setShortcut(tr("ctrl+enter"));
    connect(&send_pb, &QPushButton::pressed,this,&ChatWidget::groupSend);
    // 布局
    auto layout = new QVBoxLayout();
    layout->addWidget(input_te_p);
    layout->addWidget(&send_pb);
    setLayout(layout);

}

void ChatWidget::groupSend()
{
    string message_str = input_te_p->toPlainText().toStdString();
    int ret_i = myClient.GroupChat(message_str);
    if( ret_i == -1 )
    {
        QMessageBox errMessage_mb;
        errMessage_mb.setText("服务器未响应");
        errMessage_mb.show();
    }
    input_te_p->clear();
}

ChatWidget::~ChatWidget() = default;
