#ifndef MYFUNC_H
#define MYFUNC_H
#include "pch.h"

class MyFunc
{
public:
    int remote;// 1 = remote, 2 = local
    int mode;// 1-1 : AI-remote, 1-2 : me-remote
            //2-1 : 1:1 , 2-2: 1:AI, 3-3: AI:AI
    bool turn; // 0 : black, 1: white
    QPixmap pan[4];
    QIcon pIcon;
    QIcon bStone;
    QIcon wStone;
    QIcon nonStone;
    std::map<QString,QPushButton*> my_map;
    Ui::Widget *ui;
public:
    MyFunc(Ui::Widget *ui);
    void mapping();
    void initBoard();
    void enableBoard(bool temp);
};

#endif // MYFUNC_H
