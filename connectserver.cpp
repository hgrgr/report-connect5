#include "pch.h"

ConnectServer::ConnectServer()
{
    send_b = new char[BUFSIZE];
    recv_b = new char[BUFSIZE];
    //socket = new QTcpSocket();
}

ConnectServer::~ConnectServer()
{
    free(send_b);
    free(recv_b);
}

char* ConnectServer::recv()
{
    if(socket.waitForReadyRead()){
        qint64 size = socket.read(recv_b,BUFSIZE);
        if(size != -1)
            return recv_b;
        else
            return NULL;
    }else
        return NULL;

    /*
    while(1){
        printf("Hello recv");
        fflush(stdout);
        QThread::sleep(3);
    }
    */


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
    //memcpy(send_b,msg,3);
    //printf("\n %d %d %d",send_b[0],send_b[1],send_b[2]);
    /*
    if((socket.write(send_b,BUFSIZE)) > 0){
        return true;
    }else
        return false;
    */
    return true;
}

bool ConnectServer::ready_on()
{
    msg->cmd = 0;
    msg->turn = 0;
    msg->data = 0;
    return true;
}

bool ConnectServer::ready_off()
{
    msg->cmd = 0;
    msg->turn = 0;
    msg->data = 0;
    return true;
}
