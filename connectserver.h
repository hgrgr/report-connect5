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
private:

    //static bool fd_flag;


public:
    ConnectServer();
    ~ConnectServer();
    bool recv();
    //static QTcpSocket* getSocket();
    bool connectHost();
    bool connect();
    bool ready_on();
    bool ready_off();
};

#endif // CONNECTSERVER_H
