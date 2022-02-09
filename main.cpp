#include "pch.h"

char pan[14][14];
ConnectServer* cs;

/*
만들어야 하는것
1. 서버 통신
2. 게임
    2. minimax 알고리즘
     2.1 스코어 계산기
     2.2 알고리즘
3. GUI 환경
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
