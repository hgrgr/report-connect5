#include "pch.h"

ConnectServer::ConnectServer(Ui::Widget *ui, MyFunc *mf)
{
    send_b = new char[BUFSIZE];
    recv_b = new char[BUFSIZE];
    msg = new MyFormat();
    readybit = false;
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

void ConnectServer::readyUpdateSlot()
{
    QObject::connect(&socket,SIGNAL(readyRead(void)),this,SLOT(recvUpdateEnd(void)));
}

int ConnectServer::recvUpdateEnd()//recv update packet and update GUI,
{
    printf("\n recvUpdateENd     ");
    fflush(stdout);
    qint64 size = socket.read(recv_b,3);
    if(recv_b[0] == 2 && size != -1){//recv Update packet
        printf("\n updateEnd = %d %d %d",recv_b[0],recv_b[1],recv_b[2]);
        fflush(stdout);
        game->updateBoard(recv_b[2]);
        game->turnToggle = !(game->turnToggle);//toggle

        if(game->turnToggle == WHITE)
            ui->Tstate->setText(" 백 ");
        else if(game->turnToggle == BLACK)
            ui->Tstate->setText(" 흑 ");

        game->setMyTurn();
        game->find3(&game->i_map);
        game->find4(&game->i_map);
        game->setGui();
        return true;
    }else if(recv_b[0] == 4 && size != -1){//recv End packet
        printf("- ENd packet %d %d %d ", recv_b[0],recv_b[1],recv_b[2]);
        if(recv_b[1] == 1){//win
            ui->Tstate->setText("WIN");
            if(recv_b[2] == 0){
                ui->Tstate->setText("WIN - (Error)");
            }else if(recv_b[2] == 1){
                ui->Tstate->setText("WIN - (TIME OUT)");
            }else{
                ui->Tstate->setText("WIN - (Connect 5)");
                game->updateBoard(recv_b[2]);
                game->turnToggle = !(game->turnToggle);//toggle
                game->setMyTurn();
                game->find3(&game->i_map);
                game->find4(&game->i_map);
                game->setGui();
            }
        }else if(recv_b[1] == 0){//loser
            ui->Tstate->setText("Loss");
            if(recv_b[2] == 0){
                ui->Tstate->setText("Loss - (Error)");
            }else if(recv_b[2] == 1){
                ui->Tstate->setText("Loss - (TIME OUT)");
            }else{
                ui->Tstate->setText("Loss - (Connect 5)");
                game->updateBoard(recv_b[2]);
                game->turnToggle = !(game->turnToggle);//toggle
                game->setMyTurn();
                game->find3(&game->i_map);
                game->find4(&game->i_map);
                game->setGui();
            }
        }
        fflush(stdout);
        return true;
    }
    return false;
}

int ConnectServer::sendStone(uint8_t y, uint8_t x)
{
    msg->cmd = 3;
    msg->turn = 0;
    msg->data = ((x<<4)&XMASK) | (y&YMASK);
    memcpy(send_b,msg,3);
    if((socket.write(send_b,3)) > 0){
        printf("\n send Stone = %d %d %d",send_b[0],send_b[1],send_b[2]);
        fflush(stdout);
//        recvUpdateEnd();
        return 1;
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
            mf->remote = 1;
            mf->turn = recv_b[1];//set turn;
            return true;
        }
    }else
        return false;

    return false;
}

bool ConnectServer::ready_on()
{
    if(mf->mode != 0)
    {
        msg->cmd = 1;
        msg->turn = 0;
        msg->data = 1;
        memcpy(send_b,msg,3);
        if((socket.write(send_b,3)) > 0){
            printf("\n send = %d %d %d",send_b[0],send_b[1],send_b[2]);
            fflush(stdout);
            readybit = true;
            return true;
        }
        else
            return false;
    }
    return false;
}

bool ConnectServer::ready_off()
{
    if(readybit == true){
        msg->cmd = 1;
        msg->turn = 0;
        msg->data = 0;
        memcpy(send_b,msg,3);
        if((socket.write(send_b,3)) > 0){
            printf("\n send = %d %d %d",send_b[0],send_b[1],send_b[2]);
            fflush(stdout);
            readybit = false;
            return true;
        }
        return false;
    }
    return false;
}


