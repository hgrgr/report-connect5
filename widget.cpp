#include "pch.h"
extern ConnectServer* cs;
extern MyFunc * mf;
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
    cs->~ConnectServer();
    mf->~MyFunc();
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
        //startgame();
    }else
        ui->Tstate->setText("send packet faile(Ready on Button)");
}

void Widget::on_pBready_off_clicked()
{
    if(cs->ready_off()){
        ui->Tstate->setText("Ready off");
        ui->pBai->setEnabled(true);
        ui->pBme->setEnabled(true);
    }
    else
        ui->Tstate->setText("send packet faile(Ready on Button)");
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
}


void Widget::on_pBai_clicked()
{
    mf->enableBoard(false);
    ui->pBme->setEnabled(false);
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

