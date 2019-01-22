//
// Created by 李一航 on 2019/1/5.
//

#ifndef RECIVER_OUTCHATWIDGET_H
#define RECIVER_OUTCHATWIDGET_H

#include <QWidget>
#include <QTextEdit>
#include "reciverSocket.h"


class outChatWidget : public QWidget
{
    Q_OBJECT
public:
    explicit  outChatWidget(QWidget* parent = nullptr);
    ~outChatWidget() override;
    void work();
    void workSlot(string);
signals:
    void workSignal(string);

private:
    QTextEdit* output_te_p;
};



#endif //RECIVER_OUTCHATWIDGET_H
