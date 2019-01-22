//
// Created by 李一航 on 2019/1/5.
//

#ifndef TEST2_CHATWIDGET_H
#define TEST2_CHATWIDGET_H

#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include "client.h"

class ChatWidget : public QWidget
{
    Q_OBJECT
public:
    explicit  ChatWidget(QWidget* parent = nullptr);
    ~ChatWidget() override;
    void groupSend();

private:
    QTextEdit* input_te_p;
    QPushButton send_pb;
};


#endif //TEST2_CHATWIDGET_H
