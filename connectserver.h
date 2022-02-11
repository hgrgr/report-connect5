#ifndef CONNECTSERVER_H
#define CONNECTSERVER_H
#include "pch.h"

class ConnectServer: public QObject
{
    Q_OBJECT
public:
    struct MyFormat *msg;
    char *send_b;
    char *recv_b;
    bool readybit;
    QTcpSocket socket;
    Ui::Widget *ui;
    class MyFunc *mf;
    class Game *game;

signals:
    void readyRead();
public slots:
    int recvUpdateEnd();

public:
    explicit ConnectServer(Ui::Widget *ui,class MyFunc *mf);
    ~ConnectServer();
    bool recv();
    void readyUpdateSlot();
    int sendStone(uint8_t y, uint8_t x);
    bool connectHost();
    bool connect();
    bool ready_on();
    bool ready_off();

};

#endif // CONNECTSERVER_H
