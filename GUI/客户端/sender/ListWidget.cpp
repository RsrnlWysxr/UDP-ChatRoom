//
// Created by 李一航 on 2019/1/3.
//

#include "ListWidget.h"
#include "client.h"
#include <QMenuBar>
#include <QMenu>
#include <QLabel>
#include <QStatusBar>
#include <QToolBar>
#include <QDockWidget>


ListWidget::ListWidget(QMainWindow* parent)
:QMainWindow(parent)
{
    // 设置窗口
    resize(250,600);
    setWindowTitle("list");

    chatWidget_wg = new ChatWidget();

    // 设置输入框
    textEditIn_te_p = new QTextEdit();
    textEditIn_te_p->resize(500,160);

    // 设置切换用户按钮
    returnLogin_pb.setParent(this);
    returnLogin_pb.setText("返回登陆界面");
    returnLogin_pb.resize(150,30);
    returnLogin_pb.move(55,540);
    connect(&returnLogin_pb, &QPushButton::pressed, this, &ListWidget::returnLoginSlot);

    // 设置群聊按钮
    groupChat_pb.setParent(this);
    groupChat_pb.setText("群聊");
    groupChat_pb.resize(230,30);
    groupChat_pb.move(10,50);
    connect(&groupChat_pb, &QPushButton::pressed,
            [=]()
            {
                system("open /Users/liyihang/QT_learn/reciver/cmake-build-debug/reciver");
                chatWidget_wg->show();
            }
            );


    // 核心控件
    // setCentralWidget();


    /*
     * // 浮动窗口
    auto dockWidget_dwg_p = new QDockWidget(this);
    addDockWidget(Qt::BottomDockWidgetArea,dockWidget_dwg_p);
    dockWidget_dwg_p->resize(100,100);
    // 给浮动窗口添加控件
    auto textEdit_te_p = new QTextEdit(this);
    textEdit_te_p->resize(250,200);
    dockWidget_dwg_p->setWidget(textEdit_te_p);
    */



    // 获取菜单栏，父类自带
    QMenuBar* menuBar_mb_p = menuBar();
    // mac专用
    menuBar_mb_p->setNativeMenuBar(false);
    // 添加菜单
    QMenu* about_me_p = menuBar_mb_p->addMenu("about");
    // 添加菜单项，添加菜单
    // QAction* change_ac_p = about_me_p->addAction("当前所在服务器");
    // 添加分割线
    about_me_p->addSeparator();
    QAction* bye_ac_p = about_me_p->addAction("退出");
    connect(bye_ac_p, &QAction::triggered,
            [=]()
            {
                myClient.disconnect();
                close();
            }
    );
/*
    // 工具栏,菜单项的快捷方式
    QToolBar* toolBar_tb_p = addToolBar("tool bar");
    // 添加工具项
    auto * bye_pb_p = new QPushButton(this);
    bye_pb_p->setText("退出");
    connect(bye_pb_p, &QPushButton::pressed,
            [=]()
            {
                close();
            }
            );
    toolBar_tb_p->addWidget(bye_pb_p);*/

    // 状态栏
    // 一般写法
    QStatusBar* statusBar_sb = statusBar();
    QLabel* label_lb = new QLabel(this);
    label_lb->setText("版本号:");
    statusBar_sb->addWidget(label_lb);
    // 简略写法，从左往右添加
    statusBar_sb->addWidget(new QLabel("0.0", this));
    // 从右往左添加
    statusBar_sb->addPermanentWidget(new QLabel("作者:lyh", this));


}

ListWidget::~ListWidget() = default;

void ListWidget::returnLoginSlot()
{
    myClient.disconnect();
    emit returnLoginSignal();
}






