#include "pch.h"

ConnectServer::ConnectServer(Ui::Widget *ui, MyFunc *mf)
{
    send_b = new char[BUFSIZE];
    recv_b = new char[BUFSIZE];
    msg = new MyFormat();
    this->ui = ui;
    this->mf = mf;
    //socket = new QTcpSocket();
}

ConnectServer::~ConnectServer()
{
    free(send_b);
    free(recv_b);
    socket.close();
}

bool ConnectServer::recv()
{
    if(socket.waitForReadyRead()){
        qint64 size = socket.read(recv_b,3);
        if(size != -1)
            return true;
        else
            return false;
    }else
        return false;
}

bool ConnectServer::connectHost()
{
    socket.connectToHost("127.0.0.1", 1234); // ip address, port

    if(!(socket.waitForConnected())){
        printf("connection fail");
        return false;
    }
    else{
        printf("connection OK");
        return true;
    }
}

bool ConnectServer::connect()
{
    msg->cmd = 0;
    msg->turn = 0;
    msg->data = 0;
    memcpy(send_b,msg,3);
    printf("\n %d %d %d",send_b[0],send_b[1],send_b[2]);
    fflush(stdout);

    if((socket.write(send_b,3)) > 0){
        if(this->recv()){//
            printf("\n %d %d %d",recv_b[0],recv_b[1],recv_b[2]);
            fflush(stdout);
            return true;
        }
    }else
        return false;

    return false;
}

bool ConnectServer::ready_on()
{
    if(mf)
    msg->cmd = 1;
    msg->turn = 0;
    msg->data = 1;

    if((socket.write(send_b,3)) > 0)
        return true;
    return false;
}

bool ConnectServer::ready_off()
{
    msg->cmd = 1;
    msg->turn = 0;
    msg->data = 0;

    if((socket.write(send_b,3)) > 0)
        return true;
    return false;
}
