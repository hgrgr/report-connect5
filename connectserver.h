#ifndef CONNECTSERVER_H
#define CONNECTSERVER_H
#include "pch.h"

class ConnectServer
{
public:
    struct MyFormat *msg;
    char *send_b;
    char *recv_b;
    QTcpSocket socket;
    Ui::Widget *ui;
    class MyFunc *mf;
private:

    //static bool fd_flag;


public:
    ConnectServer(Ui::Widget *ui,class MyFunc *mf);
    ~ConnectServer();
    bool recv();
    //static QTcpSocket* getSocket();
    bool connectHost();
    bool connect();
    bool ready_on();
    bool ready_off();
};

#endif // CONNECTSERVER_H
