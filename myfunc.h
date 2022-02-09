#ifndef MYFUNC_H
#define MYFUNC_H
#include "pch.h"

class MyFunc
{
public:
    int remote;// 1 = server, 2 = local
    int mode;// 1-1 : AI-remote, 1-2 : me-remote
            //2-1 : 1:1 , 2-2: 1:AI, 3-3: AI:AI
    int turn; // 0 : black, 1: white
    QPixmap pan[3];
    QIcon pIcon;
    QIcon bStone;
    QIcon wStone;
    std::map<QString,QPushButton*> my_map;
    std::array<std::array<int,15>,15> i_map;
    Ui::Widget *ui;
public:
    MyFunc(Ui::Widget *ui);
    void mapping();
    void initBoard();
    void initIBoard();
    void setGui();
    void enableBoard(bool temp);
};

#endif // MYFUNC_H
