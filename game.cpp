#include "game.h"

Game:: Game(Ui::Widget *ui, class ConnectServer* cs,class MyFunc *mf)
{
    startBit = false;
    endBit = false;
    put_bit = false;
    this->ui = ui;
    this->cs = cs;
    this->mf = mf;
    turnToggle = mf->turn;
    initBoard();
}
void Game::showGui(){

}

bool Game::myTurn()
{
    ui->Tstate->setText("MY TURN - Put Stone");
    mf->enableBoard(true);
    //for(int i=0; i < 1500;i++){
    for(int i=0; i < 15;i++){
        //QThread::msleep(10);
        QThread::sleep(1);
        if(put_bit == true){
            put_bit = false;
            return true;
        }
    }
    return false; // time out
}

bool Game::waitTurn()
{
    mf->enableBoard(false);
    if(cs->recv()){//wait turn
        if(cs->recv_b[0] == 4){//End Game
            endBit = true;
            return true;
        }else if(cs->recv_b[0] == 2 && cs->recv_b[2] !=0){//BLack put stone
            updateBoard(cs->recv_b[2]);
            showGui();
            return true;
        }
    }
}

void Game::endGame()
{
    endBit = true;
    mf->enableBoard(false);
}

void Game::setMyTurn()
{
    printf("Set MY TURN = %d %d ", mf->turn, turnToggle);
    fflush(stdout);
    if(mf->turn == turnToggle){
        mf->enableBoard(true);
    }else
        mf->enableBoard(false);
}

void Game::putStone(uint8_t y, uint8_t x)
{
    printf("\nput stond = %d, %d   ",y+1,x+1);
 //   if() // remote or local
    if(i_map[y][x] !=2){//already stone

    }else{
        cs->sendStone(y+1,x+1);// 0~14 -> 1~15
        fflush(stdout);
        cs->recvUpdateEnd();
        //i_map[y][x] = turnToggle;
    }
}
void Game::gameStart(int turn)
{

    turnToggle = BLACK;//update 받을때 마다 toggle해준다. - 시작은 항상 Black
    printf("Hello game Start %d \n",turnToggle);
    fflush(stdout);
    //mode
    if(turn == BLACK){
        if(mf->mode == ME){//me
            ui->Tstate->setText("Put Stone");
            mf->enableBoard(true);           
        }else if(mf->mode == AI){//AI
            //minimax();or put(7-7);
            //recv(update)-wait;
        }
    }else if (turn == WHITE){
        if(mf->mode == ME){//me
            mf->enableBoard(false);
            ui->Tstate->setText("Wait");
            cs->recvUpdateEnd();
        }else if(mf->mode == AI){//AI
            //recv(update)-wait;
            //minimax();
        }
    }
}

void Game::initBoard()
{
    //i_map init
    for(int i=0;i<15;i++){
        for(int j=0;j<15;j++){
            i_map[i][j] = 2;
        }
    }
}

void Game::setGui()
{
    printf("\n Set GUi");
    fflush(stdout);
    QString temp;
    for(int i=0;i<15;i++){
        for(int j=0;j<15;j++){
            if(i_map[i][j] == WHITE){
                temp = QString("map_%1_%2").arg(QString::number(i)).arg(QString::number(j));
                mf->my_map[temp]->setIcon(mf->wStone);
                mf->my_map[temp]->setIconSize(QSize(36,36));
                mf->my_map[temp]->setFocusPolicy(Qt::NoFocus);
            }else if(i_map[i][j] == BLACK){
                temp = QString("map_%1_%2").arg(QString::number(i)).arg(QString::number(j));
                mf->my_map[temp]->setIcon(mf->bStone);
                mf->my_map[temp]->setIconSize(QSize(36,36));
                mf->my_map[temp]->setFocusPolicy(Qt::NoFocus);
            }
        }
    }
}

bool Game::updateBoard(uint8_t xy)
{
    if(i_map[(xy & YMASK) - 1][((xy & XMASK)>>4) - 1] == 2){//if board empty
        i_map[(xy & YMASK) - 1][((xy & XMASK)>>4) - 1] = turnToggle;
        setGui();
    }else{
        ui->Tstate->setText("Error - already stone");
        return false;
    }
    return true;
}

void Game::run()
{
    printf("HEllow run()\n");
    fflush(stdout);
    gameStart(mf->turn);
}
