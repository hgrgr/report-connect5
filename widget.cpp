#include "pch.h"
extern ConnectServer* cs;
extern MyFunc * mf;
extern Game* game;
//std::map<QString,QPushButton*> my_map;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    mf = new MyFunc(ui);
    mf->mapping();
    mf->initBoard();
/*
    QIcon pIcon = pan[0];
    QIcon bStone(pan[1]);
    QIcon wStone(pan[2]);
    ui->test_3->setIcon(bStone);
    ui->test_3->setIconSize(QSize(37,37));
    ui->test_3->setFocusPolicy(Qt::NoFocus);
*/
}

Widget::~Widget()
{
   // cs->~ConnectServer();
   // mf->~MyFunc();
    delete ui;
}
void startrecv(){
    printf("Hello startrecv\n");
    MyFormat *buf;
    while(1){
        buf = reinterpret_cast<MyFormat*>((cs->recv()));
        if(buf == NULL){
            continue;
        }
        printf("cmd = %d ",buf->cmd);
        printf("turn = %d ",buf->turn);
        printf("data = %d\n",buf->data);
        fflush(stdout);
    }
}
void Widget::on_pBconnect_clicked()
{
    ui->pBlocal->setEnabled(false);
    ui->pBoto->setEnabled(false);
    ui->pBota->setEnabled(false);
    ui->pBata->setEnabled(false);
    cs = new ConnectServer(ui,mf);
    if(cs->connectHost()){//connect suc
        ui->Tstate->setText("connect Server Ok");
        ui->pBready_on->setEnabled(true);
        ui->pBready_off->setEnabled(true);
        ui->pBme->setEnabled(true);
        ui->pBai->setEnabled(true);

        if(cs->connect())
            ui->Tstate->setText("connect Server Ok2");
        else
            ui->Tstate->setText("connect Server Fail2");

       // auto thread = QThread::create([](){startrecv();});
        //thread->start();
    }else{//sonnect fail
        ui->Tstate->setText("connect Server Fail");
    }

}


void Widget::on_pBready_on_clicked()
{
    if(cs->ready_on()){
        ui->Tstate->setText("Ready on");
        if(mf->mode == 1){
            ui->pBme->setEnabled(true);
            ui->pBai->setEnabled(false);
        }else if(mf->mode == 2){
            ui->pBme->setEnabled(false);
            ui->pBai->setEnabled(true);
        }
        if(cs->recv()){//wait start game
            printf("\n recv = %d %d %d",cs->recv_b[0],cs->recv_b[1],cs->recv_b[2]);
            fflush(stdout);
            if(cs->recv_b[0] == 2){//startGame;
                printf("\nHello Start game ");
                fflush(stdout);
                game = new Game(ui,cs,mf);
                cs->game = game;//connect cs class game - game class
                game->gameStart(cs->recv_b[1]);
                //game->run();
                //game->start();
            }

        }
        //startgame();
    }else
        ui->Tstate->setText("send packet fail or select mode");
}

void Widget::on_pBready_off_clicked()
{
    if(cs->ready_off()){
        ui->Tstate->setText("Ready off");
        ui->pBai->setEnabled(true);
        ui->pBme->setEnabled(true);
    }
    else
        ui->Tstate->setText("send packet faile or not Ready state");
}


void Widget::on_pBdiscon_clicked()
{
    cs->~ConnectServer();
    ui->Tstate->setText("Disconnect Server");
    ui->pBready_on->setEnabled(false);
    ui->pBready_off->setEnabled(false);
    ui->pBme->setEnabled(false);
    ui->pBai->setEnabled(false);
    ui->pBlocal->setEnabled(true);
}


void Widget::on_pBlocal_clicked()
{
    mf->remote = 2;
    ui->pBoto->setEnabled(true);
    ui->pBota->setEnabled(true);
    ui->pBata->setEnabled(true);
    ui->pBconnect->setEnabled(false);
    ui->pBdiscon->setEnabled(false);
}


void Widget::on_pBme_clicked()
{
    mf->enableBoard(true);
    ui->pBai->setEnabled(false);
    mf->mode = ME;
}


void Widget::on_pBai_clicked()
{
    mf->enableBoard(false);
    ui->pBme->setEnabled(false);
    mf->mode = AI;
}


void Widget::on_pBoto_clicked()
{
    mf->enableBoard(true);
}


void Widget::on_pBota_clicked()
{
    mf->enableBoard(true);
}


void Widget::on_pBata_clicked()
{
    mf->enableBoard(false);
}

void Widget::on_map_0_0_clicked(){
    game->putStone(0,0);
}

void Widget::on_map_0_1_clicked(){
    game->putStone(0,1);
}

void Widget::on_map_0_2_clicked(){
    game->putStone(0,2);
}

void Widget::on_map_0_3_clicked(){
    game->putStone(0,3);
}

void Widget::on_map_0_4_clicked(){
    game->putStone(0,4);
}

void Widget::on_map_0_5_clicked(){
    game->putStone(0,5);
}

void Widget::on_map_0_6_clicked(){
    game->putStone(0,6);
}

void Widget::on_map_0_7_clicked(){
    game->putStone(0,7);
}

void Widget::on_map_0_8_clicked(){
    game->putStone(0,8);
}

void Widget::on_map_0_9_clicked(){
    game->putStone(0,9);
}

void Widget::on_map_0_10_clicked(){
    game->putStone(0,10);
}

void Widget::on_map_0_11_clicked(){
    game->putStone(0,11);
}

void Widget::on_map_0_12_clicked(){
    game->putStone(0,12);
}

void Widget::on_map_0_13_clicked(){
    game->putStone(0,13);
}

void Widget::on_map_0_14_clicked(){
    game->putStone(0,14);
}

void Widget::on_map_1_0_clicked(){
    game->putStone(1,0);
}

void Widget::on_map_1_1_clicked(){
    game->putStone(1,1);
}

void Widget::on_map_1_2_clicked(){
    game->putStone(1,2);
}

void Widget::on_map_1_3_clicked(){
    game->putStone(1,3);
}

void Widget::on_map_1_4_clicked(){
    game->putStone(1,4);
}

void Widget::on_map_1_5_clicked(){
    game->putStone(1,5);
}

void Widget::on_map_1_6_clicked(){
    game->putStone(1,6);
}

void Widget::on_map_1_7_clicked(){
    game->putStone(1,7);
}

void Widget::on_map_1_8_clicked(){
    game->putStone(1,8);
}

void Widget::on_map_1_9_clicked(){
    game->putStone(1,9);
}

void Widget::on_map_1_10_clicked(){
    game->putStone(1,10);
}

void Widget::on_map_1_11_clicked(){
    game->putStone(1,11);
}

void Widget::on_map_1_12_clicked(){
    game->putStone(1,12);
}

void Widget::on_map_1_13_clicked(){
    game->putStone(1,13);
}

void Widget::on_map_1_14_clicked(){
    game->putStone(1,14);
}

void Widget::on_map_2_0_clicked(){
    game->putStone(2,0);
}

void Widget::on_map_2_1_clicked(){
    game->putStone(2,1);
}

void Widget::on_map_2_2_clicked(){
    game->putStone(2,2);
}

void Widget::on_map_2_3_clicked(){
    game->putStone(2,3);
}

void Widget::on_map_2_4_clicked(){
    game->putStone(2,4);
}

void Widget::on_map_2_5_clicked(){
    game->putStone(2,5);
}

void Widget::on_map_2_6_clicked(){
    game->putStone(2,6);
}

void Widget::on_map_2_7_clicked(){
    game->putStone(2,7);
}

void Widget::on_map_2_8_clicked(){
    game->putStone(2,8);
}

void Widget::on_map_2_9_clicked(){
    game->putStone(2,9);
}

void Widget::on_map_2_10_clicked(){
    game->putStone(2,10);
}

void Widget::on_map_2_11_clicked(){
    game->putStone(2,11);
}

void Widget::on_map_2_12_clicked(){
    game->putStone(2,12);
}

void Widget::on_map_2_13_clicked(){
    game->putStone(2,13);
}

void Widget::on_map_2_14_clicked(){
    game->putStone(2,14);
}

void Widget::on_map_3_0_clicked(){
    game->putStone(3,0);
}

void Widget::on_map_3_1_clicked(){
    game->putStone(3,1);
}

void Widget::on_map_3_2_clicked(){
    game->putStone(3,2);
}

void Widget::on_map_3_3_clicked(){
    game->putStone(3,3);
}

void Widget::on_map_3_4_clicked(){
    game->putStone(3,4);
}

void Widget::on_map_3_5_clicked(){
    game->putStone(3,5);
}

void Widget::on_map_3_6_clicked(){
    game->putStone(3,6);
}

void Widget::on_map_3_7_clicked(){
    game->putStone(3,7);
}

void Widget::on_map_3_8_clicked(){
    game->putStone(3,8);
}

void Widget::on_map_3_9_clicked(){
    game->putStone(3,9);
}

void Widget::on_map_3_10_clicked(){
    game->putStone(3,10);
}

void Widget::on_map_3_11_clicked(){
    game->putStone(3,11);
}

void Widget::on_map_3_12_clicked(){
    game->putStone(3,12);
}

void Widget::on_map_3_13_clicked(){
    game->putStone(3,13);
}

void Widget::on_map_3_14_clicked(){
    game->putStone(3,14);
}

void Widget::on_map_4_0_clicked(){
    game->putStone(4,0);
}

void Widget::on_map_4_1_clicked(){
    game->putStone(4,1);
}

void Widget::on_map_4_2_clicked(){
    game->putStone(4,2);
}

void Widget::on_map_4_3_clicked(){
    game->putStone(4,3);
}

void Widget::on_map_4_4_clicked(){
    game->putStone(4,4);
}

void Widget::on_map_4_5_clicked(){
    game->putStone(4,5);
}

void Widget::on_map_4_6_clicked(){
    game->putStone(4,6);
}

void Widget::on_map_4_7_clicked(){
    game->putStone(4,7);
}

void Widget::on_map_4_8_clicked(){
    game->putStone(4,8);
}

void Widget::on_map_4_9_clicked(){
    game->putStone(4,9);
}

void Widget::on_map_4_10_clicked(){
    game->putStone(4,10);
}

void Widget::on_map_4_11_clicked(){
    game->putStone(4,11);
}

void Widget::on_map_4_12_clicked(){
    game->putStone(4,12);
}

void Widget::on_map_4_13_clicked(){
    game->putStone(4,13);
}

void Widget::on_map_4_14_clicked(){
    game->putStone(4,14);
}

void Widget::on_map_5_0_clicked(){
    game->putStone(5,0);
}

void Widget::on_map_5_1_clicked(){
    game->putStone(5,1);
}

void Widget::on_map_5_2_clicked(){
    game->putStone(5,2);
}

void Widget::on_map_5_3_clicked(){
    game->putStone(5,3);
}

void Widget::on_map_5_4_clicked(){
    game->putStone(5,4);
}

void Widget::on_map_5_5_clicked(){
    game->putStone(5,5);
}

void Widget::on_map_5_6_clicked(){
    game->putStone(5,6);
}

void Widget::on_map_5_7_clicked(){
    game->putStone(5,7);
}

void Widget::on_map_5_8_clicked(){
    game->putStone(5,8);
}

void Widget::on_map_5_9_clicked(){
    game->putStone(5,9);
}

void Widget::on_map_5_10_clicked(){
    game->putStone(5,10);
}

void Widget::on_map_5_11_clicked(){
    game->putStone(5,11);
}

void Widget::on_map_5_12_clicked(){
    game->putStone(5,12);
}

void Widget::on_map_5_13_clicked(){
    game->putStone(5,13);
}

void Widget::on_map_5_14_clicked(){
    game->putStone(5,14);
}

void Widget::on_map_6_0_clicked(){
    game->putStone(6,0);
}

void Widget::on_map_6_1_clicked(){
    game->putStone(6,1);
}

void Widget::on_map_6_2_clicked(){
    game->putStone(6,2);
}

void Widget::on_map_6_3_clicked(){
    game->putStone(6,3);
}

void Widget::on_map_6_4_clicked(){
    game->putStone(6,4);
}

void Widget::on_map_6_5_clicked(){
    game->putStone(6,5);
}

void Widget::on_map_6_6_clicked(){
    game->putStone(6,6);
}

void Widget::on_map_6_7_clicked(){
    game->putStone(6,7);
}

void Widget::on_map_6_8_clicked(){
    game->putStone(6,8);
}

void Widget::on_map_6_9_clicked(){
    game->putStone(6,9);
}

void Widget::on_map_6_10_clicked(){
    game->putStone(6,10);
}

void Widget::on_map_6_11_clicked(){
    game->putStone(6,11);
}

void Widget::on_map_6_12_clicked(){
    game->putStone(6,12);
}

void Widget::on_map_6_13_clicked(){
    game->putStone(6,13);
}

void Widget::on_map_6_14_clicked(){
    game->putStone(6,14);
}

void Widget::on_map_7_0_clicked(){
    game->putStone(7,0);
}

void Widget::on_map_7_1_clicked(){
    game->putStone(7,1);
}

void Widget::on_map_7_2_clicked(){
    game->putStone(7,2);
}

void Widget::on_map_7_3_clicked(){
    game->putStone(7,3);
}

void Widget::on_map_7_4_clicked(){
    game->putStone(7,4);
}

void Widget::on_map_7_5_clicked(){
    game->putStone(7,5);
}

void Widget::on_map_7_6_clicked(){
    game->putStone(7,6);
}

void Widget::on_map_7_7_clicked(){
    game->putStone(7,7);
}

void Widget::on_map_7_8_clicked(){
    game->putStone(7,8);
}

void Widget::on_map_7_9_clicked(){
    game->putStone(7,9);
}

void Widget::on_map_7_10_clicked(){
    game->putStone(7,10);
}

void Widget::on_map_7_11_clicked(){
    game->putStone(7,11);
}

void Widget::on_map_7_12_clicked(){
    game->putStone(7,12);
}

void Widget::on_map_7_13_clicked(){
    game->putStone(7,13);
}

void Widget::on_map_7_14_clicked(){
    game->putStone(7,14);
}

void Widget::on_map_8_0_clicked(){
    game->putStone(8,0);
}

void Widget::on_map_8_1_clicked(){
    game->putStone(8,1);
}

void Widget::on_map_8_2_clicked(){
    game->putStone(8,2);
}

void Widget::on_map_8_3_clicked(){
    game->putStone(8,3);
}

void Widget::on_map_8_4_clicked(){
    game->putStone(8,4);
}

void Widget::on_map_8_5_clicked(){
    game->putStone(8,5);
}

void Widget::on_map_8_6_clicked(){
    game->putStone(8,6);
}

void Widget::on_map_8_7_clicked(){
    game->putStone(8,7);
}

void Widget::on_map_8_8_clicked(){
    game->putStone(8,8);
}

void Widget::on_map_8_9_clicked(){
    game->putStone(8,9);
}

void Widget::on_map_8_10_clicked(){
    game->putStone(8,10);
}

void Widget::on_map_8_11_clicked(){
    game->putStone(8,11);
}

void Widget::on_map_8_12_clicked(){
    game->putStone(8,12);
}

void Widget::on_map_8_13_clicked(){
    game->putStone(8,13);
}

void Widget::on_map_8_14_clicked(){
    game->putStone(8,14);
}

void Widget::on_map_9_0_clicked(){
    game->putStone(9,0);
}

void Widget::on_map_9_1_clicked(){
    game->putStone(9,1);
}

void Widget::on_map_9_2_clicked(){
    game->putStone(9,2);
}

void Widget::on_map_9_3_clicked(){
    game->putStone(9,3);
}

void Widget::on_map_9_4_clicked(){
    game->putStone(9,4);
}

void Widget::on_map_9_5_clicked(){
    game->putStone(9,5);
}

void Widget::on_map_9_6_clicked(){
    game->putStone(9,6);
}

void Widget::on_map_9_7_clicked(){
    game->putStone(9,7);
}

void Widget::on_map_9_8_clicked(){
    game->putStone(9,8);
}

void Widget::on_map_9_9_clicked(){
    game->putStone(9,9);
}

void Widget::on_map_9_10_clicked(){
    game->putStone(9,10);
}

void Widget::on_map_9_11_clicked(){
    game->putStone(9,11);
}

void Widget::on_map_9_12_clicked(){
    game->putStone(9,12);
}

void Widget::on_map_9_13_clicked(){
    game->putStone(9,13);
}

void Widget::on_map_9_14_clicked(){
    game->putStone(9,14);
}

void Widget::on_map_10_0_clicked(){
    game->putStone(10,0);
}

void Widget::on_map_10_1_clicked(){
    game->putStone(10,1);
}

void Widget::on_map_10_2_clicked(){
    game->putStone(10,2);
}

void Widget::on_map_10_3_clicked(){
    game->putStone(10,3);
}

void Widget::on_map_10_4_clicked(){
    game->putStone(10,4);
}

void Widget::on_map_10_5_clicked(){
    game->putStone(10,5);
}

void Widget::on_map_10_6_clicked(){
    game->putStone(10,6);
}

void Widget::on_map_10_7_clicked(){
    game->putStone(10,7);
}

void Widget::on_map_10_8_clicked(){
    game->putStone(10,8);
}

void Widget::on_map_10_9_clicked(){
    game->putStone(10,9);
}

void Widget::on_map_10_10_clicked(){
    game->putStone(10,10);
}

void Widget::on_map_10_11_clicked(){
    game->putStone(10,11);
}

void Widget::on_map_10_12_clicked(){
    game->putStone(10,12);
}

void Widget::on_map_10_13_clicked(){
    game->putStone(10,13);
}

void Widget::on_map_10_14_clicked(){
    game->putStone(10,14);
}

void Widget::on_map_11_0_clicked(){
    game->putStone(11,0);
}

void Widget::on_map_11_1_clicked(){
    game->putStone(11,1);
}

void Widget::on_map_11_2_clicked(){
    game->putStone(11,2);
}

void Widget::on_map_11_3_clicked(){
    game->putStone(11,3);
}

void Widget::on_map_11_4_clicked(){
    game->putStone(11,4);
}

void Widget::on_map_11_5_clicked(){
    game->putStone(11,5);
}

void Widget::on_map_11_6_clicked(){
    game->putStone(11,6);
}

void Widget::on_map_11_7_clicked(){
    game->putStone(11,7);
}

void Widget::on_map_11_8_clicked(){
    game->putStone(11,8);
}

void Widget::on_map_11_9_clicked(){
    game->putStone(11,9);
}

void Widget::on_map_11_10_clicked(){
    game->putStone(11,10);
}

void Widget::on_map_11_11_clicked(){
    game->putStone(11,11);
}

void Widget::on_map_11_12_clicked(){
    game->putStone(11,12);
}

void Widget::on_map_11_13_clicked(){
    game->putStone(11,13);
}

void Widget::on_map_11_14_clicked(){
    game->putStone(11,14);
}

void Widget::on_map_12_0_clicked(){
    game->putStone(12,0);
}

void Widget::on_map_12_1_clicked(){
    game->putStone(12,1);
}

void Widget::on_map_12_2_clicked(){
    game->putStone(12,2);
}

void Widget::on_map_12_3_clicked(){
    game->putStone(12,3);
}

void Widget::on_map_12_4_clicked(){
    game->putStone(12,4);
}

void Widget::on_map_12_5_clicked(){
    game->putStone(12,5);
}

void Widget::on_map_12_6_clicked(){
    game->putStone(12,6);
}

void Widget::on_map_12_7_clicked(){
    game->putStone(12,7);
}

void Widget::on_map_12_8_clicked(){
    game->putStone(12,8);
}

void Widget::on_map_12_9_clicked(){
    game->putStone(12,9);
}

void Widget::on_map_12_10_clicked(){
    game->putStone(12,10);
}

void Widget::on_map_12_11_clicked(){
    game->putStone(12,11);
}

void Widget::on_map_12_12_clicked(){
    game->putStone(12,12);
}

void Widget::on_map_12_13_clicked(){
    game->putStone(12,13);
}

void Widget::on_map_12_14_clicked(){
    game->putStone(12,14);
}

void Widget::on_map_13_0_clicked(){
    game->putStone(13,0);
}

void Widget::on_map_13_1_clicked(){
    game->putStone(13,1);
}

void Widget::on_map_13_2_clicked(){
    game->putStone(13,2);
}

void Widget::on_map_13_3_clicked(){
    game->putStone(13,3);
}

void Widget::on_map_13_4_clicked(){
    game->putStone(13,4);
}

void Widget::on_map_13_5_clicked(){
    game->putStone(13,5);
}

void Widget::on_map_13_6_clicked(){
    game->putStone(13,6);
}

void Widget::on_map_13_7_clicked(){
    game->putStone(13,7);
}

void Widget::on_map_13_8_clicked(){
    game->putStone(13,8);
}

void Widget::on_map_13_9_clicked(){
    game->putStone(13,9);
}

void Widget::on_map_13_10_clicked(){
    game->putStone(13,10);
}

void Widget::on_map_13_11_clicked(){
    game->putStone(13,11);
}

void Widget::on_map_13_12_clicked(){
    game->putStone(13,12);
}

void Widget::on_map_13_13_clicked(){
    game->putStone(13,13);
}

void Widget::on_map_13_14_clicked(){
    game->putStone(13,14);
}

void Widget::on_map_14_0_clicked(){
    game->putStone(14,0);
}

void Widget::on_map_14_1_clicked(){
    game->putStone(14,1);
}

void Widget::on_map_14_2_clicked(){
    game->putStone(14,2);
}

void Widget::on_map_14_3_clicked(){
    game->putStone(14,3);
}

void Widget::on_map_14_4_clicked(){
    game->putStone(14,4);
}

void Widget::on_map_14_5_clicked(){
    game->putStone(14,5);
}

void Widget::on_map_14_6_clicked(){
    game->putStone(14,6);
}

void Widget::on_map_14_7_clicked(){
    game->putStone(14,7);
}

void Widget::on_map_14_8_clicked(){
    game->putStone(14,8);
}

void Widget::on_map_14_9_clicked(){
    game->putStone(14,9);
}

void Widget::on_map_14_10_clicked(){
    game->putStone(14,10);
}

void Widget::on_map_14_11_clicked(){
    game->putStone(14,11);
}

void Widget::on_map_14_12_clicked(){
    game->putStone(14,12);
}

void Widget::on_map_14_13_clicked(){
    game->putStone(14,13);
}

void Widget::on_map_14_14_clicked(){
    game->putStone(14,14);
}
