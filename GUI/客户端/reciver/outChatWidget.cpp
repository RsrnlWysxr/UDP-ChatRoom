//
// Created by 李一航 on 2019/1/5.
//

#include <QVBoxLayout>
#include <QApplication>
#include "outChatWidget.h"

outChatWidget::outChatWidget(QWidget *parent)
:QWidget(parent)
{
    // 设置窗口
    resize(500,400);
    setWindowTitle("输出栏");
    move(450,190);
    // 编辑栏
    output_te_p = new QTextEdit;
    output_te_p->setReadOnly(true);
    output_te_p->setPlainText("欢迎加入聊天室");
    // 布局
    auto layout = new QVBoxLayout();
    layout->addWidget(output_te_p);

    setLayout(layout);
    connect(this, &outChatWidget::workSignal, this, &outChatWidget::workSlot);
}

void outChatWidget::work()
{
    string out = reciver.work();
    workSignal(out);
}

void outChatWidget::workSlot(string out)
{
    output_te_p->append(QString::fromStdString(out));
    QApplication::processEvents();
}

outChatWidget::~outChatWidget() = default;
