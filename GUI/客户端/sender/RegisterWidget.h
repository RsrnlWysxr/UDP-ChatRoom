//
// Created by 李一航 on 2019/1/4.
//

#ifndef TEST2_REGISTERWIDGET_H
#define TEST2_REGISTERWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QLineEdit>

class RegisterWidget: public QWidget
{
    Q_OBJECT
public:
    explicit RegisterWidget(QWidget* parent = nullptr);
    ~RegisterWidget() override;
    void registerSlot();
    // 槽函数
    void returnLoginSlot();

signals:
    void returnLoginSignal();


private:
    QPushButton register_b;
    QPushButton returnLogin_b;
    QLineEdit* account_le;
    QLineEdit* passWord_le;

};


#endif //TEST2_REGISTERWIDGET_H
