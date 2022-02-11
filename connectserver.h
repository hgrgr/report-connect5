#ifndef CONNECTSERVER_H
#define CONNECTSERVER_H
#include "pch.h"

class ConnectServer
{
public:
    struct MyFormat *msg;
    char *send_b;
    char *recv_b;
    bool readybit;
    QTcpSocket socket;
    Ui::Widget *ui;
    class MyFunc *mf;
    class Game *game;
private:
    //static bool fd_flag;

public:
    ConnectServer(Ui::Widget *ui,class MyFunc *mf);
    ~ConnectServer();
    bool recv();
    int recvUpdateEnd();
    int sendStone(uint8_t y, uint8_t x);
    //static QTcpSocket* getSocket();
    bool connectHost();
    bool connect();
    bool ready_on();
    bool ready_off();
private slots:
    void on_map_0_0_clicked();
};

#endif // CONNECTSERVER_H
