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
    if(mf->remote == REMOTE){//remote
        if(i_map[y][x] !=2){//already stone
            ui->Tstate->setText("already Stone here");
        }else{
            cs->sendStone(y+1,x+1);// 0~14 -> 1~15
            fflush(stdout);
    //       cs->recvUpdateEnd();
            //i_map[y][x] = turnToggle;
        }
    }else if(mf->remote == LOCAL){//local
        if(i_map[y][x] !=2){//already stone here
            ui->Tstate->setText("already Stone here");
        }else{
            printf("\n check %d %d",x,y);
            printf("\n check %d %d",(((x+1)<<4)&XMASK),((y&YMASK) + 1));
            updateBoard( (((x+1)<<4)&XMASK) | ((y&YMASK) + 1) );
            if(check5(i_map)){
                endGame();
            }else{
                turnToggle = !(turnToggle);//toggle
                if(mf->mode != OTO){
                    setMyTurn();
                }
            }
        }
    }

}
void Game::gameStart(int turn)
{
    turnToggle = BLACK;//update 받을때 마다 toggle해준다. - 시작은 항상 Black
    printf("Hello game Start %d \n",turnToggle);
    fflush(stdout);
    //mode
    if(mf->remote == REMOTE){
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
//               cs->recvUpdateEnd();
            }else if(mf->mode == AI){//AI
                //recv(update)-wait;
                //minimax();
            }
        }
    }else if(mf->remote == LOCAL){
        if(mf->mode == OTO){// local 1 : 1
            mf->enableBoard(true);
        }else if(mf->mode == OTA){// local 1 : AI
            mf->enableBoard(true);
            if(turn == BLACK)//user first Attack
                mf->enableBoard(true);
            else if (turn == WHITE){//user seconed Attack
                turnToggle = BLACK;
                putStone(7,7);
            }
        }else if(mf->mode == ATA){// local AI : AI
            mf->enableBoard(false);
            putStone(7,7);
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

int Game::searchWidth(std::array<std::array<int, 15>, 15> i_map, int num, bool color)
{

}

int Game::searchLength(std::array<std::array<int, 15>, 15> i_map, int num, bool color)
{

}

int Game::searchDia(std::array<std::array<int, 15>, 15> i_map, int num, bool color)
{

}

int Game::check5(std::array<std::array<int, 15>, 15> i_map, bool color)
{
    if(searchWidth(i_map,5,color)){
        return 1000000;
    }else if(searchLength(i_map,5,color)){
        return 1000000;
    }else if(searchDia(i_map,5,color)){
        return 1000000;
    }
    return 0;

    searchWidth(i_map,5,color);
    searchLength(i_map,5,color);
    searchDia(i_map,5,color);
}

int Game::check4(std::array<std::array<int, 15>, 15> i_map)
{


}

int Game::check3(std::array<std::array<int, 15>, 15> i_map)
{

}

int Game::check2(std::array<std::array<int, 15>, 15> i_map)
{

}

int Game::calScore(std::array<std::array<int, 15>, 15> i_map)
{

}

bool Game::checkNon(std::array<std::array<int, 15>, 15> i_map)
{

}

std::vector<std::pair<int, int> > Game::findSpot(std::array<std::array<int, 15>, 15> i_map)
{

}

