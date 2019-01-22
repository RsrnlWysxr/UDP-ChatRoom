//
// Created by 李一航 on 2019/1/4.
//

#ifndef TEST2_INPUTIPWIDGET_H
#define TEST2_INPUTIPWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include "MyWidget.h"
#include <QMessageBox>
#include "client.h"

using std::string;

class InputIpWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InputIpWidget(QWidget* parent = nullptr);
    ~InputIpWidget() override;
    void loginServerSlot();

private:
    QLineEdit ip_le;
    QPushButton ipConfirm_pb;
    MyWidget login_wg;
};


#endif //TEST2_INPUTIPWIDGET_H
