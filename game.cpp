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
    if(turnToggle == BLACK)
        ui->Tstate->setText("BLACK WIN");
    else
       ui->Tstate->setText("WHITE WIN");
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
        if(turnToggle == WHITE){
            if(i_map[y][x] == 1 || i_map[y][x] == 0){//already stone
                ui->Tstate->setText("already Stone here");
            }else{
                cs->sendStone(y+1,x+1);// 0~14 -> 1~15
                fflush(stdout);
        //       cs->recvUpdateEnd();
                //i_map[y][x] = turnToggle;
            }
        }else if(turnToggle == BLACK){
            if(i_map[y][x] !=2){//already stone
                ui->Tstate->setText("already Stone here");
            }else{
                cs->sendStone(y+1,x+1);// 0~14 -> 1~15
                fflush(stdout);
        //       cs->recvUpdateEnd();
                //i_map[y][x] = turnToggle;
            }
        }
        setGui();
    }else if(mf->remote == LOCAL){//local -- testing
        if(mf->mode == OTO){//one to one
            if(turnToggle == WHITE){
                if(i_map[y][x] == 1 || i_map[y][x] == 0){//already stone here
                    ui->Tstate->setText("already Stone here");
                }else{
                    printf("\n check %d %d",x,y);
                    printf("\n check %d %d",(((x+1)<<4)&XMASK),((y&YMASK) + 1));
                    updateBoard( (((x+1)<<4)&XMASK) | ((y&YMASK) + 1) );
                    if(check5(i_map,turnToggle)){
                        endGame();
                    }else{
                        find3(&i_map);
                        find4(&i_map);
                        //miniMax(i_map,1,1,1,turnToggle);
                        turnToggle = !(turnToggle);//toggle
                        if(turnToggle == BLACK)
                            ui->turn->setText(" 흑 ");
                        else if(turnToggle == WHITE)
                            ui->turn->setText(" 백 ");
                        if(mf->mode != OTO){
                            setMyTurn();
                        }
                    }
                }
            }else if(turnToggle == BLACK){
                if(i_map[y][x] !=2){//already stone here
                    ui->Tstate->setText("already Stone here");
                }else{
                    printf("\n check %d %d",x,y);
                    printf("\n check %d %d",(((x+1)<<4)&XMASK),((y&YMASK) + 1));
                    updateBoard( (((x+1)<<4)&XMASK) | ((y&YMASK) + 1) );
                    if(check5(i_map,turnToggle)){
                        endGame();
                    }else{
                        find3(&i_map);
                        find4(&i_map);
                        //miniMax(i_map,1,1,1,turnToggle);
                        turnToggle = !(turnToggle);//toggle
                        if(turnToggle == BLACK)
                            ui->turn->setText(" 흑 ");
                        else if(turnToggle == WHITE)
                            ui->turn->setText(" 백 ");
                        if(mf->mode != OTO){
                            setMyTurn();
                        }
                        setGui();
                        //miniMax(i_map,0,1,1,!turnToggle);
                    }
                }
            }
        }else if(mf->mode == OTA){
            if(mf->turn == turnToggle){//myturn
                if(turnToggle == WHITE){
                    if(i_map[y][x] == 1 || i_map[y][x] == 0){//already stone here
                        ui->Tstate->setText("already Stone here");
                    }else{
                        printf("\n check %d %d",x,y);
                        printf("\n check %d %d",(((x+1)<<4)&XMASK),((y&YMASK) + 1));
                        updateBoard( (((x+1)<<4)&XMASK) | ((y&YMASK) + 1) );
                        if(check5(i_map,turnToggle)){
                            endGame();
                        }else{
                            find3(&i_map);
                            find4(&i_map);
                            //miniMax(i_map,1,1,1,turnToggle);
                            turnToggle = !(turnToggle);//toggle
                            if(turnToggle == BLACK)
                                ui->turn->setText(" 흑 ");
                            else if(turnToggle == WHITE)
                                ui->turn->setText(" 백 ");
                            if(mf->mode != OTO){
                                setMyTurn();
                            }
                            setGui();
                            miniMax(i_map,0,1,1,!turnToggle);
                        }
                    }
                }else if(turnToggle == BLACK){
                    if(i_map[y][x] !=2){//already stone here
                        ui->Tstate->setText("already Stone here");
                    }else{
                        printf("\n check %d %d",x,y);
                        printf("\n check %d %d",(((x+1)<<4)&XMASK),((y&YMASK) + 1));
                        updateBoard( (((x+1)<<4)&XMASK) | ((y&YMASK) + 1) );
                        if(check5(i_map,turnToggle)){
                            endGame();
                        }else{
                            find3(&i_map);
                            find4(&i_map);
                            //miniMax(i_map,1,1,1,turnToggle);
                            turnToggle = !(turnToggle);//toggle
                            if(turnToggle == BLACK)
                                ui->turn->setText(" 흑 ");
                            else if(turnToggle == WHITE)
                                ui->turn->setText(" 백 ");
                            if(mf->mode != OTO){
                                setMyTurn();
                            }
                            setGui();
                            miniMax(i_map,0,1,1,!turnToggle);
                        }
                    }
                }
            }else{
                if(turnToggle == WHITE){
                    if(i_map[y][x] == 1 || i_map[y][x] == 0){//already stone here
                        ui->Tstate->setText("already Stone here");
                    }else{
                        printf("\n check %d %d",x,y);
                        printf("\n check %d %d",(((x+1)<<4)&XMASK),((y&YMASK) + 1));
                        updateBoard( (((x+1)<<4)&XMASK) | ((y&YMASK) + 1) );
                        if(check5(i_map,turnToggle)){
                            endGame();
                        }else{
                            find3(&i_map);
                            find4(&i_map);
                            //miniMax(i_map,1,1,1,turnToggle);
                            turnToggle = !(turnToggle);//toggle
                            if(turnToggle == BLACK)
                                ui->turn->setText(" 흑 ");
                            else if(turnToggle == WHITE)
                                ui->turn->setText(" 백 ");
                            if(mf->mode != OTO){
                                setMyTurn();
                            }
                            setGui();
                            //miniMax(i_map,0,1,1,!turnToggle);
                        }
                    }
                }else if(turnToggle == BLACK){
                    if(i_map[y][x] !=2){//already stone here
                        ui->Tstate->setText("already Stone here");
                    }else{
                        printf("\n check %d %d",x,y);
                        printf("\n check %d %d",(((x+1)<<4)&XMASK),((y&YMASK) + 1));
                        updateBoard( (((x+1)<<4)&XMASK) | ((y&YMASK) + 1) );
                        if(check5(i_map,turnToggle)){
                            endGame();
                        }else{
                            find3(&i_map);
                            find4(&i_map);
                            //miniMax(i_map,1,1,1,turnToggle);
                            turnToggle = !(turnToggle);//toggle
                            if(turnToggle == BLACK)
                                ui->turn->setText(" 흑 ");
                            else if(turnToggle == WHITE)
                                ui->turn->setText(" 백 ");
                            if(mf->mode != OTO){
                                setMyTurn();
                            }
                            setGui();
                            //miniMax(i_map,0,1,1,!turnToggle);
                        }
                    }
                }

            }
        }else if(mf->mode == ATA){
            if(turnToggle == WHITE){
                if(i_map[y][x] == 1 || i_map[y][x] == 0){//already stone here
                    ui->Tstate->setText("already Stone here");
                }else{
                    printf("\n check %d %d",x,y);
                    printf("\n check %d %d",(((x+1)<<4)&XMASK),((y&YMASK) + 1));
                    updateBoard( (((x+1)<<4)&XMASK) | ((y&YMASK) + 1) );
                    if(check5(i_map,turnToggle)){
                        endGame();
                    }else{
                        find3(&i_map);
                        find4(&i_map);
                        //miniMax(i_map,1,1,1,turnToggle);
                        turnToggle = !(turnToggle);//toggle
                        if(turnToggle == BLACK)
                            ui->turn->setText(" 흑 ");
                        else if(turnToggle == WHITE)
                            ui->turn->setText(" 백 ");
                        if(mf->mode != OTO){
                            setMyTurn();
                        }
                        miniMax(i_map,0,1,1,!turnToggle);
                    }
                }
            }else if(turnToggle == BLACK){
                if(i_map[y][x] !=2){//already stone here
                    ui->Tstate->setText("already Stone here");
                }else{
                    printf("\n check %d %d",x,y);
                    printf("\n check %d %d",(((x+1)<<4)&XMASK),((y&YMASK) + 1));
                    updateBoard( (((x+1)<<4)&XMASK) | ((y&YMASK) + 1) );
                    if(check5(i_map,turnToggle)){
                        endGame();
                    }else{
                        find3(&i_map);
                        find4(&i_map);
                        //miniMax(i_map,1,1,1,turnToggle);
                        turnToggle = !(turnToggle);//toggle
                        if(turnToggle == BLACK)
                            ui->turn->setText(" 흑 ");
                        else if(turnToggle == WHITE)
                            ui->turn->setText(" 백 ");
                        if(mf->mode != OTO){
                            setMyTurn();
                        }
                        miniMax(i_map,0,1,1,!turnToggle);
                    }
                }
            }
        }

        setGui();
/*
        std::array<std::array<int,2>,10> temp;
        findB4(i_map,temp,1);
        findW4(i_map,temp,1);
        findFB3(i_map,temp,1);
        findFW3(i_map,temp,1);
        findHB3(i_map,temp,1);
        findHW3(i_map,temp,1);
        findB2(i_map,temp,1);
        findW2(i_map,temp,1);
        //findB1(i_map,temp,1);
        //findW1(i_map,temp,1);
*/
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
                putStone(7,7);
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
    printf("\n\n");
    for(int i = 0; i < 15; i++){
        for(int j=0; j < 15; j++){
            printf("%d ", i_map[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
    fflush(stdout);
    QString temp;
    if(mf->remote == REMOTE){
        if(mf->turn == WHITE){
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
                    }else if(i_map[i][j] == PAN || i_map[i][j] == NON){
                        temp = QString("map_%1_%2").arg(QString::number(i)).arg(QString::number(j));
                        mf->my_map[temp]->setIcon(mf->pIcon);
                        mf->my_map[temp]->setIconSize(QSize(36,36));
                        mf->my_map[temp]->setFocusPolicy(Qt::NoFocus);
                    }
                }
            }
        }else if(mf->turn == BLACK){
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
                    }else if(i_map[i][j] == PAN){
                        temp = QString("map_%1_%2").arg(QString::number(i)).arg(QString::number(j));
                        mf->my_map[temp]->setIcon(mf->pIcon);
                        mf->my_map[temp]->setIconSize(QSize(36,36));
                        mf->my_map[temp]->setFocusPolicy(Qt::NoFocus);
                    }else if(i_map[i][j] == NON){
                        temp = QString("map_%1_%2").arg(QString::number(i)).arg(QString::number(j));
                        mf->my_map[temp]->setIcon(mf->nonStone);
                        mf->my_map[temp]->setIconSize(QSize(36,36));
                        mf->my_map[temp]->setFocusPolicy(Qt::NoFocus);
                    }
                }
            }
        }
    }else if(mf->remote == LOCAL){
        if(turnToggle == WHITE){
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
                    }else if(i_map[i][j] == PAN || i_map[i][j] == NON){
                        temp = QString("map_%1_%2").arg(QString::number(i)).arg(QString::number(j));
                        mf->my_map[temp]->setIcon(mf->pIcon);
                        mf->my_map[temp]->setIconSize(QSize(36,36));
                        mf->my_map[temp]->setFocusPolicy(Qt::NoFocus);
                    }
                }
            }
        }else if(turnToggle == BLACK){
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
                    }else if(i_map[i][j] == PAN){
                        temp = QString("map_%1_%2").arg(QString::number(i)).arg(QString::number(j));
                        mf->my_map[temp]->setIcon(mf->pIcon);
                        mf->my_map[temp]->setIconSize(QSize(36,36));
                        mf->my_map[temp]->setFocusPolicy(Qt::NoFocus);
                    }else if(i_map[i][j] == NON){
                        temp = QString("map_%1_%2").arg(QString::number(i)).arg(QString::number(j));
                        mf->my_map[temp]->setIcon(mf->nonStone);
                        mf->my_map[temp]->setIconSize(QSize(36,36));
                        mf->my_map[temp]->setFocusPolicy(Qt::NoFocus);
                    }
                }
            }
        }
    }

}

bool Game::updateBoard(uint8_t xy)
{
    if(turnToggle == WHITE){
        if(i_map[(xy & YMASK) - 1][((xy & XMASK)>>4) - 1] == 2 || i_map[(xy & YMASK) - 1][((xy & XMASK)>>4) - 1] == 3){//if board empty
            i_map[(xy & YMASK) - 1][((xy & XMASK)>>4) - 1] = turnToggle;
        }else{
            ui->Tstate->setText("Error - already stone");
            return false;
        }
    }else if(turnToggle == BLACK){
        if(i_map[(xy & YMASK) - 1][((xy & XMASK)>>4) - 1] == 2){//if board empty
            i_map[(xy & YMASK) - 1][((xy & XMASK)>>4) - 1] = turnToggle;
        }else{
            ui->Tstate->setText("Error - already stone");
            return false;
        }
    }

    return true;
}

int Game::find3(std::array<std::array<int, 15>, 15> *p_map)
{
    int line_num;
    printf(" find 3 ");
    for(int j = 0; j < 15; j++){
        for( int i =0; i < 15; i++){
            line_num = 0;
            if((*p_map)[j][i] == BLACK || (*p_map)[j][i] == WHITE)//if already stone here -> not check
                continue;
            if( (j - 1 >= 0 && i - 1 >= 0 ) && ( j +1 <= 14 && i+1 <= 14)){// \ check
                if( ( (*p_map)[j-1][i-1] == BLACK) && ( (*p_map)[j+1][i+1] == NON || (*p_map)[j+1][i+1] == PAN  ) )// Black - NoN
                {
                    if(j -3 >= 0 && i - 3 >= 0){
                        if( ((*p_map)[j-3][i-3] == NON || (*p_map)[j-3][i-3] == PAN ) && (*p_map)[j-2][i-2] == BLACK )// N B (B (B) N)
                            line_num++;
                    }
                }
                else if( ( (*p_map)[j-1][i-1] == PAN || (*p_map)[j-1][i-1] == NON) &&  (*p_map)[j+1][i+1] == BLACK )// NoN - Black
                {
                    if( i + 3 <= 14 && j + 3 <= 14){
                        if( ((*p_map)[j+3][i+3] == PAN || (*p_map)[j+3][i+3] == NON) && (*p_map)[j+2][i+2] == BLACK)// (N (B) B) B N
                        line_num++;
                    }
                }
                else if( ( (*p_map)[j-1][i-1] == BLACK ) && ( (*p_map)[j+1][i+1] == BLACK) )// Black - Black
                {
                    if( (i+2 <= 14 && j +2 <= 14) && (i-2>=0 && j-2>=0) ){
                        if( ((*p_map)[j-2][i-2] == NON || (*p_map)[j-2][i-2] == PAN) && ((*p_map)[j+2][i+2] == NON || (*p_map)[j+2][i+2] == PAN) )//N (B (B) B) N
                            line_num++;
                    }
                }
            }
            if( j - 1 >= 0 && j + 1 <= 14 ){// | check
                if( ( (*p_map)[j-1][i] == BLACK) && ( (*p_map)[j+1][i] == NON || (*p_map)[j+1][i] == PAN  ) )// Black - NoN
                {
                    if( j-3 >= 0){
                        if( ( (*p_map)[j-3][i] == NON || (*p_map)[j-3][i] == PAN) && (*p_map)[j-2][i] == BLACK )// N B ( B (B) N)
                            line_num++;
                    }
                }
                else if( ( (*p_map)[j-1][i] == PAN || (*p_map)[j-1][i] == NON) && ( (*p_map)[j+1][i] == BLACK ))// NoN - Black
                {
                    if( j + 3 <= 14){
                        if( ((*p_map)[j+3][i] == NON || (*p_map)[j+3][i] == PAN) && (*p_map)[j+2][i] == BLACK)// (N (B) B) B N
                            line_num++;
                    }
                }
                else if( ( (*p_map)[j-1][i] == BLACK ) && ( (*p_map)[j+1][i] == BLACK) )// Black - Black
                    if( j - 2 >=0 && j + 2 <= 14){
                        if( ((*p_map)[j-2][i] == NON || (*p_map)[j-2][i] == PAN ) && ( (*p_map)[j+2][i] == NON || (*p_map)[j+2][i] == PAN ))//N (B (B) B) N
                            line_num++;
                    }
           }
            if((j + 1 <= 14 && i - 1 >= 0 ) && (j-1 >=0 && i+1 <=14)){// / check
                if( ( (*p_map)[j+1][i-1] == BLACK) && ( (*p_map)[j-1][i+1] == NON || (*p_map)[j-1][i+1] == PAN  ) )// Black - NoN
                {
                    if( j+3 <= 14 && i-3 >= 0){
                        if( ((*p_map)[j+3][i-3] == NON || (*p_map)[j+3][i-3] == PAN) && (*p_map)[j+2][i-2] == BLACK )// N B ( B (B) N)
                            line_num++;
                    }
                }
                else if( ( (*p_map)[j+1][i-1] == PAN || (*p_map)[j+1][i-1] == NON) && ( (*p_map)[j-1][i+1] == BLACK ))// NoN - Black
                {
                    if(j-3 >= 0 && i+3 <=14){
                        if(((*p_map)[j-3][i+3] == NON || (*p_map)[j-3][i+3] == PAN ) && (*p_map)[j-2][i+2] == BLACK)//(N (B) B) B N
                            line_num++;
                    }
                }
                else if( ( (*p_map)[j+1][i-1] == BLACK ) && ( (*p_map)[j-1][i+1] == BLACK) )// Black - Black
                {
                    if( (j+2 >= 0 && i-2 <= 14) && (j-2 >= 0 && i+2 <= 14)){
                        if(((*p_map)[j+2][i-2] == NON || (*p_map)[j+2][i-2] == PAN) && ((*p_map)[j-2][i+2] == NON || (*p_map)[j-2][i+2] == PAN))//N (B (B) B) N
                            line_num++;
                    }
                }
            }
            if(i-1 >=0 && i+1 <= 14){// - check
                if( ( (*p_map)[j][i-1] == BLACK) && ( (*p_map)[j][i+1] == NON || (*p_map)[j][i+1] == PAN  ) )// Black - NoN
                {
                    if( i -3 >=0 ){
                        if( ((*p_map)[j][i-3] == NON || (*p_map)[j][i-3] == PAN ) && (*p_map)[j][i-2] == BLACK )
                            line_num++;
                    }
                }
                else if( ( (*p_map)[j][i-1] == PAN || (*p_map)[j][i-1] == NON) && ( (*p_map)[j][i+1] == BLACK ))// NoN - Black
                {
                    if( i + 3 <= 14){
                        if( ((*p_map)[j][i+3] == NON || (*p_map)[j][i+3] == PAN) && (*p_map)[j][i+2] == BLACK)
                            line_num++;
                    }
                }
                else if( ( (*p_map)[j][i-1] == BLACK ) && ( (*p_map)[j][i+1] == BLACK) )// Black - Black
                {
                    if( i - 2 >= 0 && i + 2 <= 14){
                        if( ((*p_map)[j][i-2] == NON ||(*p_map)[j][i-2] == PAN) && ((*p_map)[j][i+2] == NON || (*p_map)[j][i+2] == PAN))
                            line_num++;
                    }
                }
            }
            if(line_num >= 2){
                (*p_map)[j][i] = NON;
            }else
                (*p_map)[j][i] = PAN;
        }
    }
    setGui();
}

int Game::find4(std::array<std::array<int, 15>, 15> *p_map)
{
    int line_num;
    printf(" find 4 ");
    for(int j = 0; j < 15; j++){
        for( int i =0; i < 15; i++){
            line_num = 0;
            if((*p_map)[j][i] == BLACK || (*p_map)[j][i] == WHITE)//if already stone here -> not check
                continue;
            if( (j - 1 >= 0 && i - 1 >= 0 ) && ( j +1 <= 14 && i+1 <= 14)){// \ check
                if( ( (*p_map)[j-1][i-1] == BLACK) && ( (*p_map)[j+1][i+1] == NON || (*p_map)[j+1][i+1] == PAN  ) )// Black - NoN
                {
                    if(j -4 >= 0 && i - 4 >= 0){
                        if( ((*p_map)[j-4][i-4] == NON || (*p_map)[j-4][i-4] == PAN ) && (*p_map)[j-3][i-3] == BLACK && (*p_map)[j-2][i-2] == BLACK )// N B (B (B) N)
                            line_num++;
                    }
                }
                else if( ( (*p_map)[j-1][i-1] == PAN || (*p_map)[j-1][i-1] == NON) &&  (*p_map)[j+1][i+1] == BLACK )// NoN - Black
                {
                    if( i + 4 <= 14 && j + 4 <= 14){
                        if( ((*p_map)[j+4][i+4] == PAN || (*p_map)[j+4][i+4] == NON) && (*p_map)[j+3][i+3] == BLACK && (*p_map)[j+2][i+2] == BLACK)// (N (B) B) B N
                        line_num++;
                    }
                }
                else if( ( (*p_map)[j-1][i-1] == BLACK ) && ( (*p_map)[j+1][i+1] == BLACK) )// Black - Black
                {
                    if( (i+3 <= 14 && j +3 <= 14) && (i-2>=0 && j-2>=0) ){
                        if( ((*p_map)[j-2][i-2] == NON || (*p_map)[j-2][i-2] == PAN) && (*p_map)[j+2][i+2] == BLACK && ((*p_map)[j+3][i+3] == NON || (*p_map)[j+3][i+3] == PAN) )//N (B (B) B) N
                            line_num++;
                    }
                    if( (i+2 <= 14 && j + 2 <= 14) && (i-3>=0 && j-3>=0) ){
                        if( ((*p_map)[j-3][i-3] == NON || (*p_map)[j-3][i-3] == PAN) && (*p_map)[j-2][i-2] == BLACK && ((*p_map)[j+2][i+2] == NON || (*p_map)[j+2][i+2] == PAN) )//N (B (B) B) N
                            line_num++;
                    }
                }
            }
            if( j - 1 >= 0 && j + 1 <= 14 ){// | check
                if( ( (*p_map)[j-1][i] == BLACK) && ( (*p_map)[j+1][i] == NON || (*p_map)[j+1][i] == PAN  ) )// Black - NoN
                {
                    if( j-4 >= 0){
                        if( ( (*p_map)[j-4][i] == NON || (*p_map)[j-4][i] == PAN) && (*p_map)[j-3][i] == BLACK && (*p_map)[j-2][i] == BLACK)// N B ( B (B) N)
                            line_num++;
                    }
                }
                else if( ( (*p_map)[j-1][i] == PAN || (*p_map)[j-1][i] == NON) && ( (*p_map)[j+1][i] == BLACK ))// NoN - Black
                {
                    if( j + 4 <= 14){
                        if( ((*p_map)[j+4][i] == NON || (*p_map)[j+4][i] == PAN) && (*p_map)[j+3][i] == BLACK && (*p_map)[j+2][i] == BLACK)// (N (B) B) B N
                            line_num++;
                    }
                }
                else if( ( (*p_map)[j-1][i] == BLACK ) && ( (*p_map)[j+1][i] == BLACK) )// Black - Black
                {
                    if( j - 2 >=0 && j + 3 <= 14){
                        if( ((*p_map)[j-2][i] == NON || (*p_map)[j-2][i] == PAN ) && (*p_map)[j+2][i] == BLACK && ( (*p_map)[j+3][i] == NON || (*p_map)[j+3][i] == PAN ))//N (B (B) B) N
                            line_num++;
                    }
                    if( j - 3 >=0 && j + 2 <= 14){
                        if( ((*p_map)[j-3][i] == NON || (*p_map)[j-3][i] == PAN ) && (*p_map)[j-2][i] == BLACK && ( (*p_map)[j+2][i] == NON || (*p_map)[j+2][i] == PAN ))//N (B (B) B) N
                            line_num++;
                    }
                }
           }
            if((j + 1 <= 14 && i - 1 >= 0 ) && (j-1 >=0 && i+1 <=14)){// / check
                if( ( (*p_map)[j+1][i-1] == BLACK) && ( (*p_map)[j-1][i+1] == NON || (*p_map)[j-1][i+1] == PAN  ) )// Black - NoN
                {
                    if( j+4 <= 14 && i-4 >= 0){
                        if( ((*p_map)[j+4][i-4] == NON || (*p_map)[j+4][i-4] == PAN) && (*p_map)[j+3][i-3] == BLACK && (*p_map)[j+2][i-2] == BLACK )// N B ( B (B) N)
                            line_num++;
                    }
                }
                else if( ( (*p_map)[j+1][i-1] == PAN || (*p_map)[j+1][i-1] == NON) && ( (*p_map)[j-1][i+1] == BLACK ))// NoN - Black
                {
                    if(j-4 >= 0 && i+4 <=14){
                        if(((*p_map)[j-4][i+4] == NON || (*p_map)[j-4][i+4] == PAN) && (*p_map)[j-3][i+3] == BLACK && (*p_map)[j-2][i+2] == BLACK)//(N (B) B) B N
                            line_num++;
                    }
                }
                else if( ( (*p_map)[j+1][i-1] == BLACK ) && ( (*p_map)[j-1][i+1] == BLACK) )// Black - Black
                {
                    if( (j+2 >= 0 && i-2 <= 14) && (j-3 >= 0 && i+3 <= 14)){
                        if(((*p_map)[j+2][i-2] == NON || (*p_map)[j+2][i-2] == PAN) &&(*p_map)[j-2][i+2] == BLACK  && ((*p_map)[j-3][i+3] == NON || (*p_map)[j-3][i+3] == PAN))//N (B (B) B) N
                            line_num++;
                    }
                    if( (j+3 >= 0 && i-3 <= 14) && (j-2 >= 0 && i+2 <= 14)){
                        if(((*p_map)[j+3][i-3] == NON || (*p_map)[j+3][i-3] == PAN) && (*p_map)[j+2][i-2] == BLACK && ((*p_map)[j-2][i+2] == NON || (*p_map)[j-2][i+2] == PAN))//N (B (B) B) N
                            line_num++;
                    }
                }
            }
            if(i-1 >=0 && i+1 <= 14){// - check
                if( ( (*p_map)[j][i-1] == BLACK) && ( (*p_map)[j][i+1] == NON || (*p_map)[j][i+1] == PAN  ) )// Black - NoN
                {
                    if( i -4 >=0 ){
                        if( ((*p_map)[j][i-4] == NON || (*p_map)[j][i-4] == PAN ) && (*p_map)[j][i-3] == BLACK && (*p_map)[j][i-2] == BLACK )
                            line_num++;
                    }
                }
                else if( ( (*p_map)[j][i-1] == PAN || (*p_map)[j][i-1] == NON) && ( (*p_map)[j][i+1] == BLACK ))// NoN - Black
                {
                    if( i + 4 <= 14){
                        if( ((*p_map)[j][i+4] == NON || (*p_map)[j][i+4] == PAN) && (*p_map)[j][i+3] == BLACK && (*p_map)[j][i+2] == BLACK)
                            line_num++;
                    }
                }
                else if( ( (*p_map)[j][i-1] == BLACK ) && ( (*p_map)[j][i+1] == BLACK) )// Black - Black
                {
                    if( i - 2 >= 0 && i + 3 <= 14){
                        if( ((*p_map)[j][i-2] == NON ||(*p_map)[j][i-2] == PAN) && (*p_map)[j][j+2] == BLACK && ((*p_map)[j][i+3] == NON || (*p_map)[j][i+3] == PAN))
                            line_num++;
                    }
                    if( i - 3 >= 0 && i + 2 <= 14){
                        if( ((*p_map)[j][i-3] == NON ||(*p_map)[j][i-3] == PAN) && (*p_map)[j][i-2] == BLACK && ((*p_map)[j][i+2] == NON || (*p_map)[j][i+2] == PAN))
                            line_num++;
                    }
                }
            }
            if(line_num >= 2){
                (*p_map)[j][i] = NON;
            }else if( (*p_map)[j][i] != NON && line_num < 2)
                (*p_map)[j][i] = PAN;
        }
    }
}

int Game::find33(std::array<std::array<int, 15>, 15>* p_map)
{
    printf("\n find 33");
    //std::array<std::array<int, 15>, 15> *i_map = p_map;
    for(int i=1;i<14;i++)//15 - 2개 체크
    {
        if(i == 1 || i == 13){//꼭지점
            printf("\nTest 0");
            fflush(stdout);
            if((*p_map)[1][1] == NON || (*p_map)[1][1] == PAN ){//빈칸일 경우
                if((((*p_map)[1][0] == PAN || (*p_map)[1][0] == NON) && (*p_map)[1][2] == BLACK && (*p_map)[1][3] == BLACK && ((*p_map)[1][4] == PAN || (*p_map)[1][4] == NON)) && (((*p_map)[0][1] == PAN || (*p_map)[0][1] == NON) && (*p_map)[2][1] == BLACK && (*p_map)[3][1] == BLACK && ((*p_map)[4][1] == PAN || (*p_map)[0][1] == NON)))
                    (*p_map)[1][1] = NON;//3 == 33
                else if((((*p_map)[0][0] == PAN || (*p_map)[0][0] == NON ) && (*p_map)[2][2] == BLACK && (*p_map)[3][3] == BLACK && ((*p_map)[4][4] == PAN || (*p_map)[4][4] == NON)) &&  (((*p_map)[1][0] == PAN || (*p_map)[1][0] == NON) && (*p_map)[1][2] == BLACK && (*p_map)[1][3] == BLACK && ((*p_map)[1][4] == PAN || (*p_map)[1][4] == NON)))
                    (*p_map)[1][1] = NON;
                else if((((*p_map)[0][0] == PAN || (*p_map)[0][0] == NON ) && (*p_map)[2][2] == BLACK && (*p_map)[3][3] == BLACK && ((*p_map)[4][4] == PAN || (*p_map)[4][4] == NON)) &&  (((*p_map)[0][1] == PAN || (*p_map)[0][1] == NON) && (*p_map)[2][1] == BLACK && (*p_map)[3][1] == BLACK && ((*p_map)[4][1] == PAN || (*p_map)[0][1] == NON)))
                    (*p_map)[1][1] = NON;
                else
                    (*p_map)[1][1] = PAN;
            }
            if( (*p_map)[1][13] == NON || (*p_map)[1][13] == PAN){
                if(( ((*p_map)[1][14] == PAN || (*p_map)[1][14] == NON) && (*p_map)[1][12] == BLACK && (*p_map)[1][11] == BLACK && ((*p_map)[1][10] == PAN || (*p_map)[1][10] == NON)) && (((*p_map)[0][13] == PAN  || (*p_map)[0][13] == NON) && (*p_map)[2][13] == BLACK && (*p_map)[3][13] == BLACK && ((*p_map)[4][13] == PAN || (*p_map)[4][13] == NON)))
                    (*p_map)[1][13] = NON;
                else if(( ((*p_map)[0][14] == PAN || (*p_map)[0][14] == NON) && (*p_map)[2][12] == BLACK && (*p_map)[3][11] == BLACK && ((*p_map)[4][10] == PAN || (*p_map)[4][10] == NON)) && ( ((*p_map)[1][14] == PAN || (*p_map)[1][14] == NON)&& (*p_map)[1][12] == BLACK && (*p_map)[1][11] == BLACK && ((*p_map)[1][10] == PAN || (*p_map)[1][10] == NON)))
                    (*p_map)[1][13] = NON;
                else if( ( ((*p_map)[0][14] == PAN || (*p_map)[0][14] == NON) && (*p_map)[2][12] == BLACK && (*p_map)[3][11] == BLACK && ((*p_map)[4][10] == PAN || (*p_map)[4][10] == NON)) && (((*p_map)[0][13] == PAN  || (*p_map)[0][13] == NON) && (*p_map)[2][13] == BLACK && (*p_map)[3][13] == BLACK && ((*p_map)[4][13] == PAN || (*p_map)[4][13] == NON)))
                    (*p_map)[1][13] = NON;
                else
                    (*p_map)[1][13] = PAN;
            }
            if((*p_map)[13][1] == NON || (*p_map)[13][1] == PAN){
                if( ((*p_map)[13][0] == PAN && (*p_map)[13][2] == BLACK && (*p_map)[13][3] == BLACK && (*p_map)[13][4] == PAN) && ((*p_map)[14][1] == PAN && (*p_map)[12][1] == BLACK && (*p_map)[11][1] == BLACK && (*p_map)[10][1] == PAN) )
                    (*p_map)[13][1] = NON;
                else if( ((*p_map)[14][0] == PAN && (*p_map)[12][2] == BLACK && (*p_map)[11][3] == BLACK && (*p_map)[10][4] == PAN) && ((*p_map)[13][0] == PAN && (*p_map)[13][2] == BLACK && (*p_map)[13][3] == BLACK && (*p_map)[13][4] == PAN) )
                    (*p_map)[13][1] = NON;
                else if( ((*p_map)[14][0] == PAN && (*p_map)[12][2] == BLACK && (*p_map)[11][3] == BLACK && (*p_map)[10][4] == PAN) && ((*p_map)[14][1] == PAN && (*p_map)[12][1] == BLACK && (*p_map)[11][1] == BLACK && (*p_map)[10][1] == PAN))
                    (*p_map)[13][1] = NON;
                else
                    (*p_map)[13][1] = PAN;
            }
            if( (*p_map)[13][13] == PAN || (*p_map)[13][13] == PAN){
                if( ((*p_map)[13][14] == PAN && (*p_map)[13][12] == BLACK && (*p_map)[13][11] == BLACK && (*p_map)[13][10] == PAN) && ((*p_map)[14][13] == PAN && (*p_map)[12][13] == BLACK && (*p_map)[11][13] == BLACK && (*p_map)[10][13] == PAN))
                    (*p_map)[13][13] = NON;
                else if( ((*p_map)[14][14] == PAN && (*p_map)[12][12] == BLACK && (*p_map)[11][11] == BLACK && (*p_map)[10][10] == PAN) && ((*p_map)[13][14] == PAN && (*p_map)[13][12] == BLACK && (*p_map)[13][11] == BLACK && (*p_map)[13][10] == PAN))
                    (*p_map)[13][13] = NON;
                else if(((*p_map)[14][14] == PAN && (*p_map)[12][12] == BLACK && (*p_map)[11][11] == BLACK && (*p_map)[10][10] == PAN) && ((*p_map)[14][13] == PAN && (*p_map)[12][13] == BLACK && (*p_map)[11][13] == BLACK && (*p_map)[10][13] == PAN))
                    (*p_map)[13][13] = NON;
                else
                    (*p_map)[13][13] = PAN;
            }
        }else if(i == 2 || i == 12){//꼭지점에서 한칸씩 떨어져 있는 경우
            if( (*p_map)[1][2] == NON || (*p_map)[1][2] == PAN){
                if( ( ((*p_map)[1][1] == PAN || (*p_map)[1][1] == NON) && ((*p_map)[1][5] == PAN || (*p_map)[1][5] == NON) && (*p_map)[1][3] == BLACK && (*p_map)[1][4] == BLACK ) &&
                        ( ((*p_map)[0][1] == PAN || (*p_map)[0][1] == NON) && ((*p_map)[4][5] == PAN || (*p_map)[4][5] == NON) && (*p_map)[2][3] == BLACK && (*p_map)[3][4] == BLACK))
                    (*p_map)[1][2] = NON;
                else if(  ( ((*p_map)[0][1] == PAN || (*p_map)[0][1] == NON) && ((*p_map)[4][5] == PAN || (*p_map)[4][5] == NON) && (*p_map)[2][3] == BLACK && (*p_map)[3][4] == BLACK) &&
                         ( ((*p_map)[0][2] == PAN || (*p_map)[0][2] == NON) && ((*p_map)[4][2] == PAN || (*p_map)[4][2] == NON) && (*p_map)[2][2] == BLACK && (*p_map)[3][2] == BLACK))
                    (*p_map)[1][2] = NON;
                else if( ( ((*p_map)[1][1] == PAN || (*p_map)[1][1] == NON) && ((*p_map)[1][5] == PAN || (*p_map)[1][5] == NON) && (*p_map)[1][3] == BLACK && (*p_map)[1][4] == BLACK ) &&
                         ( ((*p_map)[0][2] == PAN || (*p_map)[0][2] == NON) && ((*p_map)[4][2] == PAN || (*p_map)[4][2] == NON) && (*p_map)[2][2] == BLACK && (*p_map)[3][2] == BLACK))
                    (*p_map)[1][2] = NON;
                else if ( ( ((*p_map)[1][0] == PAN || (*p_map)[1][0] == NON) && ((*p_map)[1][4] == PAN || (*p_map)[1][4] == NON) && (*p_map)[1][1] == BLACK && (*p_map)[1][3] == BLACK) &&
                          ( ((*p_map)[0][1] == PAN || (*p_map)[0][1] == NON) && ((*p_map)[4][5] == PAN || (*p_map)[4][5] == NON) && (*p_map)[2][3] == BLACK && (*p_map)[3][4] == BLACK))
                    (*p_map)[1][2] = NON;
                else if ( ( ((*p_map)[1][0] == PAN || (*p_map)[1][0] == NON) && ((*p_map)[1][4] == PAN || (*p_map)[1][4] == NON) && (*p_map)[1][1] == BLACK && (*p_map)[1][3] == BLACK) &&
                          ( ((*p_map)[0][2] == PAN || (*p_map)[0][2] == NON) && ((*p_map)[4][2] == PAN || (*p_map)[4][2] == NON) && (*p_map)[2][2] == BLACK && (*p_map)[3][2] == BLACK))
                    (*p_map)[1][2] = NON;
                else
                    (*p_map)[1][2] = PAN;
            }
            if( (*p_map)[2][1] == 3 || (*p_map)[2][1] == 2){
                if( ( ((*p_map)[1][1] == PAN || (*p_map)[1][1] == NON) && ((*p_map)[5][1] == PAN || (*p_map)[5][1] == NON) && (*p_map)[3][1] == BLACK && (*p_map)[4][1] == BLACK ) &&
                        ( ((*p_map)[1][0] == PAN || (*p_map)[1][0] == NON) && ((*p_map)[5][4] == PAN | (*p_map)[5][4] == NON) && (*p_map)[3][2] == BLACK && (*p_map)[4][3] == BLACK ))
                { printf("check 0 ");(*p_map)[2][1] = NON;
                }else if( ( ((*p_map)[1][1] == PAN || (*p_map)[1][1] == NON) && ((*p_map)[5][1] == PAN || (*p_map)[5][1] == NON) && (*p_map)[3][1] == BLACK && (*p_map)[4][1] == BLACK ) &&
                         ( ((*p_map)[2][0] == PAN || (*p_map)[2][0] == NON) && ((*p_map)[2][4] == PAN || (*p_map)[2][4] == NON) && (*p_map)[2][2] == BLACK && (*p_map)[2][2] == BLACK))
                 {   printf("check 2 ");(*p_map)[2][1] = NON;
                }else if( ( ((*p_map)[1][0] == PAN || (*p_map)[1][0] == NON) && ((*p_map)[5][4] == PAN || (*p_map)[5][4] == NON) && (*p_map)[3][2] == BLACK && (*p_map)[3][2] == BLACK ) &&
                         ( ((*p_map)[2][0] == PAN || (*p_map)[2][0] == NON) && ((*p_map)[2][4] == PAN || (*p_map)[2][4] == NON) && (*p_map)[2][2] == BLACK && (*p_map)[2][2] == BLACK))
                {    printf("check 3 ");(*p_map)[2][1] = NON;
                }else if( ( ((*p_map)[0][1] == PAN || (*p_map)[0][1] == NON) && ((*p_map)[4][1] == PAN || (*p_map)[4][1] == NON) && (*p_map)[1][1] == BLACK && (*p_map)[3][1] == BLACK ) &&
                         ( ((*p_map)[2][0] == PAN || (*p_map)[2][0] == NON) && ((*p_map)[2][4] == PAN || (*p_map)[2][4] == NON) && (*p_map)[2][2] == BLACK && (*p_map)[2][3] == BLACK ))
                 {   printf("check 4 ");(*p_map)[2][1] = NON;
                }else if( ( ((*p_map)[0][1] == PAN || (*p_map)[0][1] == NON) && ((*p_map)[4][1] == PAN || (*p_map)[4][1] == NON) && (*p_map)[1][1] == BLACK && (*p_map)[3][1] == BLACK ) &&
                         ( ((*p_map)[1][0] == PAN || (*p_map)[1][0] == NON) && ((*p_map)[5][4] == PAN || (*p_map)[5][4] == NON) && (*p_map)[3][2] == BLACK && (*p_map)[4][3] == BLACK ))
                {    printf("check 5 ");(*p_map)[2][1] = NON;
                }else
                    (*p_map)[2][1] = PAN;

            }
            if((*p_map)[13][2] == 3 || (*p_map)[13][2] == 2){

            }
            if( (*p_map)[12][1] == 3 ||(*p_map)[12][1] == 2){

            }
            if( (*p_map)[1][12] == 3 || (*p_map)[1][12] == 2){

            }
            if( (*p_map)[2][3] == 3 || (*p_map)[2][3] == 2){

            }
            if((*p_map)[12][13] == 3 || (*p_map)[12][13] == 2){

            }
            if((*p_map)[13][12] == 3 || (*p_map)[13][12] == 2){

            }
        }else{//나머지 경우 - 같은 라인일 경우 전부 동일
            if((*p_map)[1][i] == 2){

            }
            if((*p_map)[i][1] == 2){

            }
            if((*p_map)[13][i] == 2){

            }
            if((*p_map)[i][13] == 2){

            }
        }
    }
    for(int i=2;i<13;i++){//15 - 4개 체크
        if(i == 2 || i == 12){//꼭지점
            if((*p_map)[2][2] == 2){

            }
            if((*p_map)[2][12] == 2){

            }
            if((*p_map)[12][2] == 2){

            }
            if((*p_map)[12][12] == 2){

            }
        }else{//나머지는 동일
            if(i_map[2][i] == 2){

            }
            if(i_map[i][2] == 2){

            }
            if(i_map[12][i] == 2){

            }
            if(i_map[i][12] == 2){

            }
        }
        i_map[2][i];
        i_map[i][2];
        i_map[12][i];
        i_map[i][12];
    }
    for(int i=3; i < 12; i++){//15 - 6개 체크 -- 모두 동일 루틴
        for(int j=3; j < 12; j++){

        }
    }
    printf("\n\n");
    for(int i = 0; i < 15; i++){
        for(int j=0; j < 15; j++){
            printf("%d ", i_map[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
    //setGui();
}

int Game::searchWidth(std::array<std::array<int, 15>, 15> i_map, int num, bool color)
{
    if(num == 5){//find connect5 - sp case
        for(int j=0; j < 15; j++){
            for(int i=0; i< 11; i++){//10 11 12 13 14 - 5
                if(i_map[j][i] == color && i_map[j][i+1] == color &&
                        i_map[j][i+2] == color && i_map[j][i+3] == color && i_map[j][i+4] == color){
                    if( i_map[j][i+5] != color && i_map[j][i-1] != color && i-1 >= 0 && i+5 <=14)
                        return 1;
                    else if(i_map[j][i+5] != color && i == 0)
                        return 1;
                    else if(i_map[j][i-1] !=color && i == 10)
                        return 1;
                }
            }
        }
    }
    return 0;
}

int Game::searchLength(std::array<std::array<int, 15>, 15> i_map, int num, bool color)
{
    if(num == 5){//find connect5 - sp case
        for(int j=0; j < 11; j++){//10 11 12 13 14 - 5
            for(int i=0; i< 15; i++){
                if(i_map[j][i]== color && i_map[j+1][i]== color &&
                        i_map[j+2][i]== color && i_map[j+3][i]== color && i_map[j+4][i]== color){
                    if( i_map[j+5][i] != color && i_map[j-1][i] != color && j-1>=0 && j+5<=14)
                        return 1;
                    else if( i_map[j+5][i] != color && j == 0)
                        return 1;
                    else if( i_map[j-1][i] != color && j == 10)
                        return 1;

                }
            }
        }
    }
    return 0;
}

int Game::searchDia(std::array<std::array<int, 15>, 15> i_map, int num, bool color)
{
    if(num == 5){//find connect5 - sp case
        for(int j=0; j<11;j++){// 10 11 12 13 14 - 5
            for(int i=0; i< 11; i++){// 10 11 12 13 14 - 5
                if(i_map[j][i] == color && i_map[j+1][i+1] == color && i_map[j+2][i+2] == color &&
                        i_map[j+3][i+3] == color && i_map[j+4][i+4] == color){//find \ dia1
                    if( i_map[j+5][i+5] !=color && i_map[j-1][i-1] != color &&//양쪽 모두 체크
                            (j+5 <= 14 && j-1 >= 0 ) && (i+5 <= 14 && i-1>=0 ))
                        {printf("\n con5 1 "); return 1;}
                    else if( (i == 0 && j == 10) ||(i == 10 && j == 0))
                        {printf("\n con5 4 "); return 1;}
                    else if( i_map[j+5][i+5] != color && (i==0 || j == 0) )//우측 체크
                        {printf("\n con5 2 "); return 1;}
                    else if( i_map[j-1][i-1] !=color && (i == 10 || j == 10))//좌측 체크
                        {printf("\n con5 3 "); return 1;}

                }
            }
        }
        for(int j=4; j< 15; j++){
            for(int i=0; i<11; i++){
                if(i_map[j][i] == color && i_map[j-1][i+1] == color && i_map[j-2][i+2] == color &&// find / dia2
                        i_map[j-3][i+3] == color && i_map[j-4][i+4] == color){
                    if( i_map[j-5][i+5] != color && i_map[j+1][i-1] != color && ( j > 4 && j < 14 ) && ( i > 0 && i < 10) )
                        {printf("\n con5 1 "); return 1;}
                    else if( (i == 0 && j == 4) || (j == 14 && i == 10))
                        {printf("\n con5 4 "); return 1;}
                    else if( i_map[j-5][i+5] != color && (i == 0 || j == 14 ) )//우측 +5칸
                        {printf("\n con5 2 "); return 1;}
                    else if(i_map[j+1][i-1] != color && (j == 4 || i == 10) )//좌측 -1 칸
                        {printf("\n con5 3 "); return 1;}
                }
            }
        }
    }
    return 0;
}

int Game::check5(std::array<std::array<int, 15>, 15> i_map, bool color)
{
    if(searchWidth(i_map,5,color)){
        return 1;
    }else if(searchLength(i_map,5,color)){
        return 1;
    }else if(searchDia(i_map,5,color)){
        return 1;
    }
    return 0;
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

int Game::calScore(std::array<std::array<int, 15>, 15>& p_map,int turn)
{
    //findB4(std::array<std::array<int,15>,15>& p_map, std::array<std::array<int,2>,10>& buf_xy, int buf_size);
    std::array<std::array<int,2>,10> buf_xy;
    int sc = 0;
    sc = rand() % 10;
    int temp=0;
    if(check5(p_map,!turn) == 1)//5개 완성한 경우 (턴은 상위 턴 기준으로 계산 해야한다)
        return 99999999;//0이 5개
    if((!turn) == BLACK){//상위 턴이 블랙일경우 (뎁스 5기준 원래 턴과 동일)
        //다음 턴이 화이트 이기 때뭉네 b4보다 w4우선시 되어야한다
        if(findW4(p_map,buf_xy,1) >0 ){//white 4 가 존재시
            return -900000;//최저값 - 이미 진 경우
        }
        if((temp = findB4(p_map,buf_xy,10)) > 0 ){//white4 없고 black 4는 존재할 경우
            sc += 2000*temp;// 0이 4개
        }
        if((temp = findFW3(p_map,buf_xy,10)) > 0)//열린 white 3 존재시
        {
            sc -= 1000*temp;// 0이 3개
        }
        if((temp = findFB3(p_map,buf_xy,10)) >0 )//열린 black 존재시 -> 화이트가 막아야함
        {
            sc += 310*temp;
         }
        if((temp = findHW3(p_map,buf_xy,10) > 0)){// 닫힌 white 3 존재시
            sc -= 150*temp;
        }
        if((temp = findHB3(p_map,buf_xy,10)) >0){// 닫힌 black 3 존재시
           sc += 70*temp;
        }
        if((temp = findW2(p_map,buf_xy,10))>0){//열린 white2 존재시
            sc -= 50*temp;
        }
        return sc;
    }else if((!turn) == WHITE){//상위 턴이 화이트일 경우 (뎁스 5기준 원래 턴과 동일)
        //다음 턴이 화이트 이기 때뭉네 b4보다 w4우선시 되어야한다
        if(findB4(p_map,buf_xy,1) >0 ){//Black 4 가 존재시
            return -900000;//최저값 - 이미 진 경우
        }
        if((temp = findW4(p_map,buf_xy,10)) > 0 ){//black4 없고 white 4는 존재할 경우
            sc += 2000*temp;// 0이 4개
        }
        if((temp = findFB3(p_map,buf_xy,10)) > 0)//열린 Black 3 존재시
        {
            sc -= 1000*temp;// 0이 3개
        }
        if((temp = findFW3(p_map,buf_xy,10)) >0 )//열린 White 존재시 -> 블랙이 막아야함
        {
            sc += 310*temp;
         }
        if((temp = findHB3(p_map,buf_xy,10) > 0)){// 닫힌 BLack 3 존재시
            sc -= 150*temp;
        }
        if((temp = findHW3(p_map,buf_xy,10)) >0){// 닫힌 White 3 존재시
           sc += 70*temp;
        }
        if((temp = findB2(p_map,buf_xy,10))>0){//열린 Black2 존재시
            sc -= 50*temp;
        }
        return sc;
    }
    return sc;
}

int Game::findSpotW(std::array<std::array<int,15>,15>& p_map, std::array<std::array<int, 2>, 10> &buf_xy, int buf_size)
{
    std::array<std::array<int,15>,15> bit_map;
    for(int i=0;i<15;i++){//init bit_map;
        for(int j=0; j <15;j++){
            bit_map[i][j]=0;
        }
    }
    int m_size = 0;
    m_size += findW4(p_map, buf_xy, buf_size);//무조권 놓아야함

    if(m_size < buf_size){
        m_size += findB4(p_map, buf_xy, buf_size - m_size);//무조권 놓아야함
    }
    if(m_size < buf_size){
        m_size += findFW3(p_map, buf_xy, buf_size - m_size);//최선의 수 계산 필요 // 44 - 43 가능 수 최우선으로 찾아야함
    }
    if(m_size < buf_size){
        m_size += findFB3(p_map, buf_xy, buf_size - m_size);//최선의 수 계산 필요//43 가능수 방어 필요
    }
    if(m_size < buf_size){
        m_size += findHW3(p_map, buf_xy, buf_size - m_size);//최선의 수 계산 필요 // 막힌 43, 44 최우선으로 찾아야함
    }
    if(m_size < buf_size){
        m_size += findHB3(p_map, buf_xy, buf_size - m_size);//수 계산 필요 - 막힌 43, 띄엄 44 공격수 찾아야함
    }
    if(m_size < buf_size){
        m_size += findW2(p_map, buf_xy, buf_size - m_size);//수 계산 필요 - 33 최우선으로 찾아야함
    }
    if(m_size < buf_size){
        m_size += findB2(p_map, buf_xy, buf_size - m_size);//수 계산 필요 띄엄 띄엄 33 최우선 방어 필요
    }
    if(m_size < buf_size){
        findW1(p_map, buf_xy,bit_map, buf_size - m_size);
        printf("find b1 m_size = %d \n",m_size);
        for(int i=m_size; i<buf_size;i++){
            int max_num = 0;
            int t_x =0;
            int t_y =0;
            for(int k=0;k<15;k++){//bit map scane
                for(int t=0; t<15;t++){
                    if(bit_map[k][t] > max_num){
                        max_num = bit_map[k][t];
                        t_y = k;
                        t_x = t;
                    }
                }
            }
            if(max_num == 0)
                break;
            buf_xy[i][0] = t_y;
            buf_xy[i][1] = t_x;
            bit_map[t_y][t_x] = 0;//없애준다.
            max_num = 0;
            printf("\n m_size *=* %d", m_size++);

        }
    }
    if(m_size < buf_size){
        findB1(p_map, buf_xy,bit_map, buf_size - m_size);
        printf("find b1 m_size = %d \n",m_size);
        for(int i=m_size; i<buf_size;i++){
            int max_num = 0;
            int t_x =0;
            int t_y =0;
            for(int k=0;k<15;k++){//bit map scane
                for(int t=0; t<15;t++){
                    if(bit_map[k][t] > max_num){
                        max_num = bit_map[k][t];
                        t_y = k;
                        t_x = t;
                    }
                }
            }
            if(max_num == 0)
                break;
            buf_xy[i][0] = t_y;
            buf_xy[i][1] = t_x;
            bit_map[t_y][t_x] = 0;//없애준다.
            max_num = 0;
            printf("\n m_size *=* %d", m_size++);

        }
    }
    //

    return m_size;
}

int Game::findSpotB(std::array<std::array<int,15>,15>& p_map, std::array<std::array<int, 2>, 10> &buf_xy, int buf_size)
{
    std::array<std::array<int,15>,15> bit_map;

    for(int i=0;i<15;i++){//init bit_map;
        for(int j=0; j <15;j++){
            bit_map[i][j]=0;
        }
    }
    int m_size = 0;
    m_size += findB4(p_map, buf_xy, buf_size);//buf_size = 10 - 무조건 막아야함
    printf("m_size = %d \n",m_size);
    if(m_size < buf_size){
        m_size += findW4(p_map, buf_xy, buf_size - m_size);//무조건 막아야함
        printf("m_size = %d \n",m_size);
    }
    if(m_size < buf_size){
        m_size += findFB3(p_map, buf_xy, buf_size - m_size);//띄엄 44,34 공격 찾는게 최우선
        printf("m_size = %d \n",m_size);
    }
    if(m_size < buf_size){
        m_size += findFW3(p_map, buf_xy, buf_size - m_size);
        printf("m_size = %d \n",m_size);
    }
    if(m_size < buf_size){
        m_size += findHB3(p_map, buf_xy, buf_size - m_size);
        printf("m_size = %d \n",m_size);
    }
    if(m_size < buf_size){
        m_size += findHW3(p_map, buf_xy, buf_size - m_size);
        printf("m_size = %d \n",m_size);
    }
    if(m_size < buf_size){
        m_size += findB2(p_map, buf_xy, buf_size - m_size);
        printf("m_size = %d \n",m_size);
    }
    if(m_size < buf_size){
        m_size += findW2(p_map, buf_xy, buf_size - m_size);
        printf("m_size = %d \n",m_size);
    }
    if(m_size < buf_size){
        findB1(p_map, buf_xy,bit_map, buf_size - m_size);
        printf("find b1 m_size = %d \n",m_size);
        for(int i=m_size; i<buf_size;i++){
            int max_num = 0;
            int t_x =0;
            int t_y =0;
            for(int k=0;k<15;k++){//bit map scane
                for(int t=0; t<15;t++){
                    if(bit_map[k][t] > max_num){
                        max_num = bit_map[k][t];
                        t_y = k;
                        t_x = t;
                    }
                }
            }
            if(max_num == 0)
                break;
            buf_xy[i][0] = t_y;
            buf_xy[i][1] = t_x;
            bit_map[t_y][t_x] = 0;//없애준다.
            max_num = 0;
            printf("\n m_size *=* %d", m_size++);

        }
    }
    if(m_size < buf_size){
        findW1(p_map, buf_xy,bit_map, buf_size - m_size);
        printf("find b1 m_size = %d \n",m_size);
        for(int i=m_size; i<buf_size;i++){
            int max_num = 0;
            int t_x =0;
            int t_y =0;
            for(int k=0;k<15;k++){//bit map scane
                for(int t=0; t<15;t++){
                    if(bit_map[k][t] > max_num){
                        max_num = bit_map[k][t];
                        t_y = k;
                        t_x = t;
                    }
                }
            }
            if(max_num == 0)
                break;
            buf_xy[i][0] = t_y;
            buf_xy[i][1] = t_x;
            bit_map[t_y][t_x] = 0;//없애준다.
            max_num = 0;
            printf("\n m_size *=* %d", m_size++);

        }
    }
    //
    return m_size;
}

int Game::findB4(std::array<std::array<int,15>,15>& p_map,std::array<std::array<int, 2>, 10> &buf_xy, int buf_size)//will make 5
{
    printf("\n **** find B4******");
    int p = 0;
    int b = 0;
    int buf_p = 10 - buf_size;
    int find_num =0;
    for(int j = 0; j < 15; j++){
        for(int i =0; i < 15; i++){
            if(p_map[j][i] == PAN){//only PAN
                if(i+4 <= 14){ // 가로 - N B B B B
                    if(p_map[j][i+1] == BLACK && p_map[j][i+2] == BLACK && p_map[j][i+3] == BLACK && p_map[j][i+4] == BLACK){
                        if( p_map[j][i-1]  != BLACK && i-1>=0) // 좌측 검사
                        {
                            printf("\n 1-1 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                        else if( i == 0) //
                        {   //push(j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                            printf("\n 1-2 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if(i-1 >= 0 && i+3 <=14){// 가로 - B N B B B
                    if(p_map[j][i-1] == BLACK && p_map[j][i+1] == BLACK && p_map[j][i+2] == BLACK && p_map[j][i+3] == BLACK){
                        if( p_map[j][i-2] != BLACK && p_map[j][i+4] != BLACK && (i-2 >=0 && i+4 <= 14) ){//양쪽 모두 체크 - 중앙에 있음
                            printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j][i-2] != BLACK && i+3 == 14){//좌측 체크 (우측은 이미 끝에 도달)
                            printf("\n 1-4 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j][i+4] != BLACK && i -1 == 0 ){//우측 체크
                            printf("\n 1-5 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if(i-2 >=0 && i+2 <=14){// 가로 - B  B N B B
                    if(p_map[j][i-2] == BLACK && p_map[j][i-1] == BLACK && p_map[j][i+1] == BLACK && p_map[j][i+2] == BLACK ){
                        if( p_map[j][i-3] != BLACK && p_map[j][i+3] != BLACK && i+3 <= 14 && i-3 >= 0){
                            printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j][i+3] != BLACK && i - 2 == 0){//좌측에 붙어있음 -> 우측만 검사
                            printf("\n 1-7 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j][i-3] != BLACK && i + 2 == 14){//우측에 붙어 있음 -> 좌측만 검사
                            printf("\n 1-8 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if( i-3 >=0 && i+1 <= 14){// 가로 - B B  B N B
                    if(p_map[j][i-3] == BLACK && p_map[j][i-2] == BLACK && p_map[j][i-1] == BLACK && p_map[j][i+1] == BLACK){
                        if( p_map[j][i+2] != BLACK && p_map[j][i-4] != BLACK && i+2 <= 14 && i-4 >= 0){
                            printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if ( p_map[j][i+2] !=BLACK && i -3 == 0){//좌측에 붙음 -> 우측만 검사
                            printf("\n 1-10 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j][i-4] != BLACK && i+1 == 14){//우측에 붙음 -> 좌측만 검사
                            printf("\n 1-11 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if( i-4 >= 0){// 가로 - B B B B N
                    if(p_map[j][i-4] == BLACK && p_map[j][i-3] == BLACK && p_map[j][i-2] == BLACK && p_map[j][i-1] == BLACK){
                        if(i == 14){//이미 끝에 도달 - 검사할것 없음(원래는 우측 검사)
                            printf("\n 1-12 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j][i+1] != BLACK && i != 14){//우측 검사
                            printf("\n 1-13 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                //// - 세로
                if(j+4 <= 14){ // 세로 - N B B B B
                    if(p_map[j+1][i] == BLACK && p_map[j+2][i] == BLACK && p_map[j+3][i] == BLACK && p_map[j+4][i] == BLACK){
                        if( p_map[j-1][i]  != BLACK && j-1>=0)//상단 검사 할거리 있을 경우
                        {
                            printf("\n 2-1 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                        else if( j== 0)//상단에 붙어있음 - 검사 할거리 없음
                        {   //push(j,i);
                            printf("\n 2-2 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if(j-1 >= 0 && j+3 <=14){// 세로 - B N B B B
                    if(p_map[j-1][i] == BLACK && p_map[j+1][i] == BLACK && p_map[j+2][i] == BLACK && p_map[j+3][i] == BLACK){
                        if( p_map[j-2][i] != BLACK && p_map[j+4][i] != BLACK && (j-2 >=0 && j+4 <= 14) ){//양쪽 모두 체크 - 중앙에 있음
                            printf("\n 2-3 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j-2][i] != BLACK && j+3 == 14){//상단 체크 (하단은 이미 끝에 도달)
                            printf("\n 2-4 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j+4][i] != BLACK && j -1 == 0 ){//하단 체크 - 상단은 이미 상단에 도달
                            printf("\n 2-5 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if(j-2 >=0 && j+2 <=14){// 세로 - B  B N B B
                    if(p_map[j-2][i] == BLACK && p_map[j-1][i] == BLACK && p_map[j+1][i] == BLACK && p_map[j+2][i] == BLACK ){
                        if( p_map[j-3][i] != BLACK && p_map[j+3][i] != BLACK && j+3 <= 14 && j-3 >= 0){
                            printf("\n 2-6 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j+3][i] != BLACK && j - 2 == 0){//상단에 붙어 있을 경우 -> 하단만 검사
                            printf("\n 2-7 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j-3][i] != BLACK && j + 2 == 14){//하단에 붙어 있을경우 -> 상단만 검사
                            printf("\n 2-8 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if( j-3 >=0 && j+1 <= 14){// 세로 - B B  B N B
                    if(p_map[j-3][i] == BLACK && p_map[j-2][i] == BLACK && p_map[j-1][i] == BLACK && p_map[j+1][i] == BLACK){
                        if( p_map[j+2][i] != BLACK && p_map[j-4][i] != BLACK && j+2 <= 14 && j-4 >= 0){
                            printf("\n 2-9 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if ( p_map[j+2][i] !=BLACK && j -3 == 0){//상단에 붙음 - 하단만 검사
                            printf("\n 2-10 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j-4][i] != BLACK && j+1 == 14){//하단에 붙음 - 상단만 검사
                            printf("\n 2-11 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if( j-4 >= 0){// 세로 - B B B B N
                    if(p_map[j-4][i] == BLACK && p_map[j-3][i] == BLACK && p_map[j-2][i] == BLACK && p_map[j-1][i] == BLACK){
                        if(j == 14){//이미 끝에 도달 - 굳이 상단 검사할 필요없음 - 5개여서
                            printf("\n 2-12 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j+1][i] != BLACK && j != 14){//하단 검사
                            printf("\n 2-13 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                // Dia 1 - "\"
                if( i+4 <= 14 && j+4 <= 14){ // dia1 - N B B B B
                    if(p_map[j+1][i+1] == BLACK && p_map[j+2][i+2] == BLACK && p_map[j+3][i+3] == BLACK && p_map[j+4][i+4] == BLACK){
                        if( p_map[j-1][i-1] != BLACK && j-1>=0 && i-1>=0)//우측에 있으면 이미 5개임 -> 검사할 필요 없음 - 좌측만 돌 없으면 4
                        {
                            printf("\n 3-1 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                        else if( i == 0 || j== 0)//좌측에 달라 붙어 있을경우 - 검사 필요 없음
                        {   //push(j,i);
                            printf("\n 3-2 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if(i-1 >= 0 && i+3 <=14 && j-1 >= 0 && j+3 <=14){// dia1 - B N B B B
                    if(p_map[j-1][i-1] == BLACK && p_map[j+1][i+1] == BLACK && p_map[j+2][i+2] == BLACK && p_map[j+3][i+3] == BLACK){
                        if( p_map[j-2][i-2] != BLACK && p_map[j+4][i+4] != BLACK && (i-2 >=0 && i+4 <= 14) && (j-2 >=0 && j+4 <= 14) ){//양쪽 모두 체큰 - 중앙에 있음
                            printf("\n 3-3 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j-2][i-2] != BLACK && (i+3 == 14 || j+3 == 14)){//좌측 체크 (우측은 이미 끝에 도달)
                            printf("\n 3-4 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j+4][i+4] != BLACK && (i -1 == 0  || j -1 == 0) ){//우측 체크
                            printf("\n 3-5 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if(i-2 >=0 && i+2 <=14 && j-2 >=0 && j+2 <=14){// dia1 - B  B N B B
                    if(p_map[j-2][i-2] == BLACK && p_map[j-1][i-1] == BLACK && p_map[j+1][i+1] == BLACK && p_map[j+2][i+2] == BLACK ){
                        if( p_map[j-3][i-3] != BLACK && p_map[j+3][i+3] != BLACK && i+3 <= 14 && i-3 >= 0 && j+3 <= 14 && j-3 >= 0){
                            printf("\n 3-6 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j+3][i+3] != BLACK && (i - 2 == 0 || j - 2 == 0)){
                            printf("\n 3-7 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j-3][i-3] != BLACK && (i + 2 == 14 || j + 2 == 14)){
                            printf("\n 3-8 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if( i-3 >=0 && i+1 <= 14 && j-3 >=0 && j+1 <= 14){// dia1 - B B  B N B
                    if(p_map[j-3][i-3] == BLACK && p_map[j-2][i-2] == BLACK && p_map[j-1][i-1] == BLACK && p_map[j+1][i+1] == BLACK){
                        if( p_map[j+2][i+2] != BLACK && p_map[j-4][i-4] != BLACK && i+2 <= 14 && i-4 >= 0 && j+2 <= 14 && j-4 >= 0){
                            printf("\n 3-9 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if ( p_map[j+2][i+2] !=BLACK && (i -3 == 0 || j -3 == 0)){
                            printf("\n 3-10 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j-4][i-4] != BLACK && (i+1 == 14 || j+1 == 14)){
                            printf("\n 3-11 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if( i-4 >= 0 && j-4 >= 0){// dia1 - B B B B N
                    if(p_map[j-4][i-4] == BLACK && p_map[j-3][i-3] == BLACK && p_map[j-2][i-2] == BLACK && p_map[j-1][i-1] == BLACK){
                        if( i == 14 || j == 14){//이미 끝에 도달 -- 좌측 검사할 필요 없음(5개니까) - 우측 검사할 칸 없음
                            printf("\n 3-12 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j+1][i+1] != BLACK && i != 14 && j != 14){
                            printf("\n 3-13 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                // DIa 2 - /
                if( j-4 >=0 && i+4 <= 14){ // dia2 - N B B B B
                    if(p_map[j-1][i+1] == BLACK && p_map[j-2][i+2] == BLACK && p_map[j-3][i+3] == BLACK && p_map[j-4][i+4] == BLACK){
                        if( p_map[j+1][i-1]  != BLACK && j+1<=14 && i-1>=0) // 좌측 검사 - 좌측이 있을 경우
                        {
                            printf("\n 4-1 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                        else if( j == 14 || i == 0)//ㄴ 라인
                        {   //push(j,i);
                            printf("\n 4-2 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if( j-3 >= 0 && j+1 <=14 && i-1 >= 0 && i+3 <=14){// dia2 - B N B B B
                    if(p_map[j+1][i-1] == BLACK && p_map[j-1][i+1] == BLACK && p_map[j-2][i+2] == BLACK && p_map[j-3][i+3] == BLACK){
                        if( p_map[j+2][i-2] != BLACK && p_map[j-4][i+4] != BLACK &&
                                (i-2 >=0 && i+4 <= 14) && (j-4 >=0 && j+2 <= 14) ){//양쪽 모두 체큰 - 중앙에 있음
                            printf("\n 4-3 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j+2][i-2] != BLACK  && (i+3 == 14 || j-3 == 0)){//좌측 체크 (우측은 이미 끝에 도달) ㄱ 형태
                            printf("\n 4-4 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j-4][i+4] != BLACK && (j + 1 == 14 || i -1 == 0 )){//우측 체크 ㄴ 형태
                            printf("\n 4-5 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if(j-2 >=0 && j+2 <=14 && i-2 >=0 && i+2 <=14){// dia2 - B  B N B B
                    if(p_map[j+2][i-2] == BLACK && p_map[j+1][i-1] == BLACK && p_map[j-1][i+1] == BLACK && p_map[j-2][i+2] == BLACK ){
                        if( p_map[j+3][i-3] != BLACK && p_map[j-3][i+3] != BLACK &&
                                (i-3 >=0 && i+3 <=14 ) && (j-3 >=0 && j+3 <= 14)){
                            printf("\n 4-6find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j+3][i-3] != BLACK && ( j == 2 || i == 12)){//하단 검사
                            printf("\n 4-7 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j-3][i+3] != BLACK && ( j == 12 || i == 2)){//상단 검사
                            printf("\n 4-8 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if( j+3 <= 14 && i-3 >=0 && j-1 >=0 && i+1 <= 14){// dia2 - B B  B N B
                    if(p_map[j+3][i-3] == BLACK && p_map[j+2][i-2] == BLACK && p_map[j+1][i-1] == BLACK && p_map[j-1][i+1] == BLACK){
                        if( p_map[j+4][i-4] != BLACK && p_map[j-2][i+2] != BLACK &&
                                (j+4 <= 14 && i-4>=0) && (j-2 >=0 && i+2 <= 14)){// 2<=j<= 10   4<=i<=12
                            printf("\n 4-9 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if ( p_map[j+4][i-4] !=BLACK && (j == 1 || i == 13)){
                            printf("\n 4-10 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j-2][i+2] != BLACK && (j == 11 || i == 3)){
                            printf("\n 4-11 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if( j+4 <= 14 && i-4 >= 0){// dia2 - B B B B N
                    if(p_map[j+4][i-4] == BLACK && p_map[j+3][i-3] == BLACK && p_map[j+2][i-2] == BLACK && p_map[j+1][i-1] == BLACK){
                        if(p_map[j-1][i+1] !=BLACK && (j-1>=0 && i+1<=14)){//우측 검사 - 우측이 있을 경우
                            printf("\n 4-12 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( j == 0 || i == 14){// 검사 필요 없음
                            printf("\n 4-13 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
            }
        }
    }
     printf("\n **** ENd B4******");
     return find_num;
}
int Game::findFB3(std::array<std::array<int,15>,15>& p_map, std::array<std::array<int, 2>, 10> &buf_xy, int buf_size)//양쪽 뚫린 3 - will make 4
{
    printf("\n **** find Full B3******");
    /*
      경우의 수
      (B) (N) B B (N)
     */
     int p = 0;
     int b = 0;
     int buf_p = 10 - buf_size;
     int find_num =0;
     for(int j = 0; j < 15; j++){
         for(int i =0; i < 15; i++){
             if(p_map[j][i] == PAN){//only PAN - Black cannot put NON
                 if(i+3 <= 14){// 가로 - (N) <N> B B B (N)
                     if(p_map[j][i+1] == BLACK && p_map[j][i+2] == BLACK && p_map[j][i+3] == BLACK){
                         if( p_map[j][i-1] == PAN && p_map[j][i+4] == PAN && i+4 <= 14 && i-1>=0) // 좌 우측 검사
                         {
                             printf("\n 1-1 find connect 4 - j = %d , i = %d   ",j,i);
                             if(buf_p<10){
                                 buf_xy[buf_p][0]=j;
                                 buf_xy[buf_p][1]=i;
                                 buf_p++;
                                 find_num++;
                             }
                         }
                     }
                 }
                 if(i-1 >= 0 && i+2 <=14){// 가로 - (N) B <N> B B (N)
                     if(p_map[j][i-1] == BLACK && p_map[j][i+1] == BLACK && p_map[j][i+2] == BLACK){
                         if( p_map[j][i-2] == PAN && p_map[j][i+3] == PAN && (i-2 >=0 && i+3 <= 14) ){//양쪽 모두 체크 - 중앙에 있음
                             printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                             if(buf_p<10){
                                 buf_xy[buf_p][0]=j;
                                 buf_xy[buf_p][1]=i;
                                 buf_p++;
                                 find_num++;
                             }
                         }
                     }
                 }
                 if(i-2 >=0 && i+1 <=14){// 가로 - (N) B  B <N> B (N)
                     if(p_map[j][i-2] == BLACK && p_map[j][i-1] == BLACK && p_map[j][i+1] == BLACK){
                         if( p_map[j][i-3] == PAN && p_map[j][i+2] == PAN && i+2 <= 14 && i-3 >= 0){
                             printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                             if(buf_p<10){
                                 buf_xy[buf_p][0]=j;
                                 buf_xy[buf_p][1]=i;
                                 buf_p++;
                                 find_num++;
                             }
                         }
                     }
                 }
                 if( i-3 >=0 ){// 가로 - (N) B B  B <N> (N)
                     if(p_map[j][i-3] == BLACK && p_map[j][i-2] == BLACK && p_map[j][i-1] == BLACK){
                         if( p_map[j][i-4] == PAN && p_map[j][i+1] == PAN && i+1 <= 14 && i-4 >= 0){
                             printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                             if(buf_p<10){
                                 buf_xy[buf_p][0]=j;
                                 buf_xy[buf_p][1]=i;
                                 buf_p++;
                                 find_num++;
                             }
                         }
                     }
                 }
                 //// - 세로
                 if(j+3 <= 14){// 세로 - (N) <N> B B B (N)
                     if(p_map[j+1][i] == BLACK && p_map[j+2][i] == BLACK && p_map[j+3][i] == BLACK){
                         if( p_map[j-1][i] == PAN && p_map[j+4][i] == PAN && j+4 <= 14 && j-1>=0) // 좌 우측 검사
                         {
                             printf("\n 1-1 find connect 4 - j = %d , i = %d   ",j,i);
                             if(buf_p<10){
                                 buf_xy[buf_p][0]=j;
                                 buf_xy[buf_p][1]=i;
                                 buf_p++;
                                 find_num++;
                             }
                         }
                     }
                 }
                 if(j-1 >= 0 && j+2 <=14){// 세로 - (N) B <N> B B (N)
                     if(p_map[j-1][i] == BLACK && p_map[j+1][i] == BLACK && p_map[j+2][i] == BLACK){
                         if( p_map[j-2][i] == PAN && p_map[j+3][i] == PAN && (j-2 >=0 && j+3 <= 14) ){//양쪽 모두 체크 - 중앙에 있음
                             printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                             if(buf_p<10){
                                 buf_xy[buf_p][0]=j;
                                 buf_xy[buf_p][1]=i;
                                 buf_p++;
                                 find_num++;
                             }
                         }
                     }
                 }
                 if(j-2 >=0 && j+1 <=14){// 세로 - (N) B  B <N> B (N)
                     if(p_map[j-2][i] == BLACK && p_map[j-1][i] == BLACK && p_map[j+1][i] == BLACK){
                         if( p_map[j-3][i] == PAN && p_map[j+2][i] == PAN && j+2 <= 14 && j-3 >= 0){
                             printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                             if(buf_p<10){
                                 buf_xy[buf_p][0]=j;
                                 buf_xy[buf_p][1]=i;
                                 buf_p++;
                                 find_num++;
                             }
                         }
                     }
                 }
                 if( j-3 >=0){// 세로 - (N) B B  B <N> (N)
                     if(p_map[j-3][i] == BLACK && p_map[j-2][i] == BLACK && p_map[j-1][i] == BLACK){
                         if( p_map[j-4][i] == PAN && p_map[j+1][i] == PAN && j+1 <= 14 && j-4 >= 0){
                             printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                             if(buf_p<10){
                                 buf_xy[buf_p][0]=j;
                                 buf_xy[buf_p][1]=i;
                                 buf_p++;
                                 find_num++;
                             }
                         }
                     }
                 }
                 // Dia 1 - "\"
                 if(i+1 <= 14 && j+3 <= 14){// Dia 1 - (N) <N> B B B (N)
                     if(p_map[j+1][i+1] == BLACK && p_map[j+2][i+2] == BLACK && p_map[j+3][i+3] == BLACK){
                         if( p_map[j-1][i-1] == PAN && p_map[j+4][i+4] == PAN && j+4 <= 14 && j-1>=0 && i+4 <= 14 && i-1>=0) // 좌 우측 검사
                         {
                             printf("\n 1-1 find connect 4 - j = %d , i = %d   ",j,i);
                             if(buf_p<10){
                                 buf_xy[buf_p][0]=j;
                                 buf_xy[buf_p][1]=i;
                                 buf_p++;
                                 find_num++;
                             }
                         }
                     }
                 }
                 if( i-1 >= 0 && i+2 <=14 && j-1 >= 0 && j+2 <=14){// Dia 1 - (N) B <N> B B (N)
                     if(p_map[j-1][i-1] == BLACK && p_map[j+1][i+1] == BLACK && p_map[j+2][i+2] == BLACK){
                         if( p_map[j-2][i-2] == PAN && p_map[j+3][i+3] == PAN && (j-2 >=0 && j+3 <= 14) && (i-2 >=0 && i+3 <= 14) ){//양쪽 모두 체크 - 중앙에 있음
                             printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                             if(buf_p<10){
                                 buf_xy[buf_p][0]=j;
                                 buf_xy[buf_p][1]=i;
                                 buf_p++;
                                 find_num++;
                             }
                         }
                     }
                 }
                 if(i-2 >=0 && i+1 <=14 && j-2 >=0 && j+1 <=14){// Dia 1 - (N) B  B <N> B (N)
                     if(p_map[j-2][i-2] == BLACK && p_map[j-1][i-1] == BLACK && p_map[j+1][i+1] == BLACK){
                         if( p_map[j-3][i-3] == PAN && p_map[j+2][i+2] == PAN && j+2 <= 14 && j-3 >= 0 && i+2 <= 14 && i-3 >= 0){
                             printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                             if(buf_p<10){
                                 buf_xy[buf_p][0]=j;
                                 buf_xy[buf_p][1]=i;
                                 buf_p++;
                                 find_num++;
                             }
                         }
                     }
                 }
                 if( i-3 >=0 && j-3 >=0){// Dia 1 - (N) B B  B <N> (N)
                     if(p_map[j-3][i-3] == BLACK && p_map[j-2][i-2] == BLACK && p_map[j-1][i-1] == BLACK){
                         if( p_map[j-4][i-4] == PAN && p_map[j+1][i+1] == PAN && j+1 <= 14 && j-4 >= 0 && i+1 <= 14 && i-4 >= 0){
                             printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                             if(buf_p<10){
                                 buf_xy[buf_p][0]=j;
                                 buf_xy[buf_p][1]=i;
                                 buf_p++;
                                 find_num++;
                             }
                         }
                     }
                 }

                 // DIa 2 - /
                 if(i+3 <= 14 && j-3 >=0 ){// DIa 2 - (N) <N> B B B (N)
                     if(p_map[j-1][i+1] == BLACK && p_map[j-2][i+2] == BLACK && p_map[j-3][i+3] == BLACK){
                         if( p_map[j+1][i-1] == PAN && p_map[j-4][i+4] == PAN && (j+1<=14 && j-4>=0) && (i+4<=14 && i-1>=0)) // 좌 우측 검사
                         {
                             printf("\n 1-1 find connect 4 - j = %d , i = %d   ",j,i);
                             if(buf_p<10){
                                 buf_xy[buf_p][0]=j;
                                 buf_xy[buf_p][1]=i;
                                 buf_p++;
                                 find_num++;
                             }
                         }
                     }
                 }
                 if( i-1>=0 && i+2<=14 && j-2>=0 && j+1<=14 ){// Dia 2 - (N) B <N> B B (N)
                     if(p_map[j+1][i-1] == BLACK && p_map[j-1][i+1] == BLACK && p_map[j-2][i+2] == BLACK){
                         if( p_map[j+2][i-2] == PAN && p_map[j-3][i+3] == PAN && (j-3 >=0 && j+2 <= 14) && (i-2 >=0 && i+3 <= 14) ){//양쪽 모두 체크 - 중앙에 있음
                             printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                             if(buf_p<10){
                                 buf_xy[buf_p][0]=j;
                                 buf_xy[buf_p][1]=i;
                                 buf_p++;
                                 find_num++;
                             }
                         }
                     }
                 }
                 if(i-2 >=0 && i+1 <=14 && j+2 >=0 && j-1 <=14){// Dia 2 - (N) B  B <N> B (N)
                     if(p_map[j+2][i-2] == BLACK && p_map[j+1][i-1] == BLACK && p_map[j-1][i+1] == BLACK){
                         if( p_map[j+3][i-3] == PAN && p_map[j-2][i+2] == PAN && j+3 <= 14 && j-2 >= 0 && i+2 <= 14 && i-3 >= 0){
                             printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                             if(buf_p<10){
                                 buf_xy[buf_p][0]=j;
                                 buf_xy[buf_p][1]=i;
                                 buf_p++;
                                 find_num++;
                             }
                         }
                     }
                 }
                 if( i-3 >=0 && j+3 <= 14){// Dia 2 - (N) B B  B <N> (N)
                     if(p_map[j+3][i-3] == BLACK && p_map[j+2][i-2] == BLACK && p_map[j+1][i-1] == BLACK){
                         if( p_map[j+4][i-4] == PAN && p_map[j-1][i+1] == PAN && j+4 <= 14 && j-1 >= 0 && i+1 <= 14 && i-4 >= 0){
                             printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                             if(buf_p<10){
                                 buf_xy[buf_p][0]=j;
                                 buf_xy[buf_p][1]=i;
                                 buf_p++;
                                 find_num++;
                             }
                         }
                     }
                 }
                 //
             }
         }
     }
      printf("\n **** ENd Full B3******");
      return find_num;

}
int Game::findFW3(std::array<std::array<int,15>,15>& p_map, std::array<std::array<int, 2>, 10> &buf_xy, int buf_size)
{
    printf("\n **** find Full W3******");
    /*
      경우의 수
      (B) (N) B B (N)
     */
     int p = 0;
     int b = 0;
     int buf_p = 10 - buf_size;
     int find_num = 0;
     for(int j = 0; j < 15; j++){
         for(int i =0; i < 15; i++){
             if(p_map[j][i] == PAN || p_map[j][i] == NON){//only PAN, NON - White can put NON
                 if(i+3 <= 14){// 가로 - (N) <N> B B B (N)
                     if(p_map[j][i+1] == WHITE && p_map[j][i+2] == WHITE && p_map[j][i+3] == WHITE){
                         if( p_map[j][i-1] == PAN && p_map[j][i+4] == PAN && i+4 <= 14 && i-1>=0) // 좌 우측 검사
                         {
                             printf("\n 1-1 find connect 4 - j = %d , i = %d   ",j,i);
                             if(buf_p<10){
                                 buf_xy[buf_p][0]=j;
                                 buf_xy[buf_p][1]=i;
                                 buf_p++;
                                 find_num++;
                             }
                         }
                     }
                 }
                 if(i-1 >= 0 && i+2 <=14){// 가로 - (N) B <N> B B (N)
                     if(p_map[j][i-1] == WHITE && p_map[j][i+1] == WHITE && p_map[j][i+2] == WHITE){
                         if( p_map[j][i-2] == PAN && p_map[j][i+3] == PAN && (i-2 >=0 && i+3 <= 14) ){//양쪽 모두 체크 - 중앙에 있음
                             printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                             if(buf_p<10){
                                 buf_xy[buf_p][0]=j;
                                 buf_xy[buf_p][1]=i;
                                 buf_p++;
                                 find_num++;
                             }
                         }
                     }
                 }
                 if(i-2 >=0 && i+1 <=14){// 가로 - (N) B  B <N> B (N)
                     if(p_map[j][i-2] == WHITE && p_map[j][i-1] == WHITE && p_map[j][i+1] == WHITE){
                         if( p_map[j][i-3] == PAN && p_map[j][i+2] == PAN && i+2 <= 14 && i-3 >= 0){
                             printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                             if(buf_p<10){
                                 buf_xy[buf_p][0]=j;
                                 buf_xy[buf_p][1]=i;
                                 buf_p++;
                                 find_num++;
                             }
                         }
                     }
                 }
                 if( i-3 >=0 ){// 가로 - (N) B B  B <N> (N)
                     if(p_map[j][i-3] == WHITE && p_map[j][i-2] == WHITE && p_map[j][i-1] == WHITE){
                         if( p_map[j][i-4] == PAN && p_map[j][i+1] == PAN && i+1 <= 14 && i-4 >= 0){
                             printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                             if(buf_p<10){
                                 buf_xy[buf_p][0]=j;
                                 buf_xy[buf_p][1]=i;
                                 buf_p++;
                                 find_num++;
                             }
                         }
                     }
                 }
                 //// - 세로
                 if(j+3 <= 14){// 세로 - (N) <N> B B B (N)
                     if(p_map[j+1][i] == WHITE && p_map[j+2][i] == WHITE && p_map[j+3][i] == WHITE){
                         if( (p_map[j-1][i] == PAN || p_map[j-1][i] == NON) && (p_map[j+4][i] == PAN || p_map[j+4][i] == NON) && j+4 <= 14 && j-1>=0) // 좌 우측 검사
                         {
                             printf("\n 1-1 find connect 4 - j = %d , i = %d   ",j,i);
                             if(buf_p<10){
                                 buf_xy[buf_p][0]=j;
                                 buf_xy[buf_p][1]=i;
                                 buf_p++;
                                 find_num++;
                             }
                         }
                     }
                 }
                 if(j-1 >= 0 && j+2 <=14){// 세로 - (N) B <N> B B (N)
                     if(p_map[j-1][i] == WHITE && p_map[j+1][i] == WHITE && p_map[j+2][i] == WHITE){
                         if( ( p_map[j-2][i] == NON || p_map[j-2][i] == PAN) && (p_map[j+3][i] == PAN || p_map[j+3][i] == NON) && (j-2 >=0 && j+3 <= 14) ){//양쪽 모두 체크 - 중앙에 있음
                             printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                             if(buf_p<10){
                                 buf_xy[buf_p][0]=j;
                                 buf_xy[buf_p][1]=i;
                                 buf_p++;
                                 find_num++;
                             }
                         }
                     }
                 }
                 if(j-2 >=0 && j+1 <=14){// 세로 - (N) B  B <N> B (N)
                     if(p_map[j-2][i] == WHITE && p_map[j-1][i] == WHITE && p_map[j+1][i] == WHITE){
                         if( (p_map[j-3][i] == PAN || p_map[j-3][i] == NON) && (  p_map[j+2][i] == NON ||p_map[j+2][i] == PAN) && j+2 <= 14 && j-3 >= 0){
                             printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                             if(buf_p<10){
                                 buf_xy[buf_p][0]=j;
                                 buf_xy[buf_p][1]=i;
                                 buf_p++;
                                 find_num++;
                             }
                         }
                     }
                 }
                 if( j-3 >=0){// 세로 - (N) B B  B <N> (N)
                     if(p_map[j-3][i] == WHITE && p_map[j-2][i] == WHITE && p_map[j-1][i] == WHITE){
                         if( (p_map[j-4][i] == PAN || p_map[j-4][i] == NON) && (p_map[j+1][i] == PAN || p_map[j+1][i] == NON)&& j+1 <= 14 && j-4 >= 0){
                             printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                             if(buf_p<10){
                                 buf_xy[buf_p][0]=j;
                                 buf_xy[buf_p][1]=i;
                                 buf_p++;
                                 find_num++;
                             }
                         }
                     }
                 }
                 // Dia 1 - "\"
                 if(i+1 <= 14 && j+3 <= 14){// Dia 1 - (N) <N> B B B (N)
                     if(p_map[j+1][i+1] == WHITE && p_map[j+2][i+2] == WHITE && p_map[j+3][i+3] == WHITE){
                         if( (p_map[j-1][i-1] == PAN || p_map[j-1][i-1] == NON) && (p_map[j+4][i+4] == PAN || p_map[j+4][i+4] == NON) && j+4 <= 14 && j-1>=0 && i+4 <= 14 && i-1>=0) // 좌 우측 검사
                         {
                             printf("\n 1-1 find connect 4 - j = %d , i = %d   ",j,i);
                             if(buf_p<10){
                                 buf_xy[buf_p][0]=j;
                                 buf_xy[buf_p][1]=i;
                                 buf_p++;
                                 find_num++;
                             }
                         }
                     }
                 }
                 if( i-1 >= 0 && i+2 <=14 && j-1 >= 0 && j+2 <=14){// Dia 1 - (N) B <N> B B (N)
                     if(p_map[j-1][i-1] == WHITE && p_map[j+1][i+1] == WHITE && p_map[j+2][i+2] == WHITE){
                         if( (p_map[j-2][i-2] == PAN || p_map[j-2][i-2] == NON) && (p_map[j+3][i+3] == PAN || p_map[j+3][i+3] == NON) && (j-2 >=0 && j+3 <= 14) && (i-2 >=0 && i+3 <= 14) ){//양쪽 모두 체크 - 중앙에 있음
                             printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                             if(buf_p<10){
                                 buf_xy[buf_p][0]=j;
                                 buf_xy[buf_p][1]=i;
                                 buf_p++;
                                 find_num++;
                             }
                         }
                     }
                 }
                 if(i-2 >=0 && i+1 <=14 && j-2 >=0 && j+1 <=14){// Dia 1 - (N) B  B <N> B (N)
                     if(p_map[j-2][i-2] == WHITE && p_map[j-1][i-1] == WHITE && p_map[j+1][i+1] == WHITE){
                         if( (p_map[j-3][i-3] == PAN || p_map[j-3][i-3] == NON) && (p_map[j+2][i+2] == PAN || p_map[j+2][i+2] == NON) && j+2 <= 14 && j-3 >= 0 && i+2 <= 14 && i-3 >= 0){
                             printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                             if(buf_p<10){
                                 buf_xy[buf_p][0]=j;
                                 buf_xy[buf_p][1]=i;
                                 buf_p++;
                                 find_num++;
                             }
                         }
                     }
                 }
                 if( i-3 >=0 && j-3 >=0){// Dia 1 - (N) B B  B <N> (N)
                     if(p_map[j-3][i-3] == WHITE && p_map[j-2][i-2] == WHITE && p_map[j-1][i-1] == WHITE){
                         if( (p_map[j-4][i-4] == PAN || p_map[j-4][i-4] == NON) && (p_map[j+1][i+1] == PAN || p_map[j+1][i+1] == NON) && j+1 <= 14 && j-4 >= 0 && i+1 <= 14 && i-4 >= 0){
                             printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                             if(buf_p<10){
                                 buf_xy[buf_p][0]=j;
                                 buf_xy[buf_p][1]=i;
                                 buf_p++;
                                 find_num++;
                             }
                         }
                     }
                 }

                 // DIa 2 - /
                 if(i+3 <= 14 && j-3 >=0 ){// DIa 2 - (N) <N> B B B (N)
                     if(p_map[j-1][i+1] == WHITE && p_map[j-2][i+2] == WHITE && p_map[j-3][i+3] == WHITE){
                         if( (p_map[j+1][i-1] == PAN || p_map[j+1][i-1] == NON) && (p_map[j-4][i+4] == PAN || p_map[j-4][i+4] == NON) && (j+1<=14 && j-4>=0) && (i+4<=14 && i-1>=0)) // 좌 우측 검사
                         {
                             printf("\n 1-1 find connect 4 - j = %d , i = %d   ",j,i);
                             if(buf_p<10){
                                 buf_xy[buf_p][0]=j;
                                 buf_xy[buf_p][1]=i;
                                 buf_p++;
                                 find_num++;
                             }
                         }
                     }
                 }
                 if( i-1>=0 && i+2<=14 && j-2>=0 && j+1<=14 ){// Dia 2 - (N) B <N> B B (N)
                     if(p_map[j+1][i-1] == WHITE && p_map[j-1][i+1] == WHITE && p_map[j-2][i+2] == WHITE){
                         if( (p_map[j+2][i-2] == PAN || p_map[j+2][i-2] == NON) && (p_map[j-3][i+3] == PAN || p_map[j-3][i+3] == NON) && (j-3 >=0 && j+2 <= 14) && (i-2 >=0 && i+3 <= 14) ){//양쪽 모두 체크 - 중앙에 있음
                             printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                             if(buf_p<10){
                                 buf_xy[buf_p][0]=j;
                                 buf_xy[buf_p][1]=i;
                                 buf_p++;
                                 find_num++;
                             }
                         }
                     }
                 }
                 if(i-2 >=0 && i+1 <=14 && j+2 >=0 && j-1 <=14){// Dia 2 - (N) B  B <N> B (N)
                     if(p_map[j+2][i-2] == WHITE && p_map[j+1][i-1] == WHITE && p_map[j-1][i+1] == WHITE){
                         if( (p_map[j+3][i-3] == PAN || p_map[j+3][i-3] == NON) && (p_map[j-2][i+2] == PAN || p_map[j-2][i+2] == NON) && j+3 <= 14 && j-2 >= 0 && i+2 <= 14 && i-3 >= 0){
                             printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                             if(buf_p<10){
                                 buf_xy[buf_p][0]=j;
                                 buf_xy[buf_p][1]=i;
                                 buf_p++;
                                 find_num++;
                             }
                         }
                     }
                 }
                 if( i-3 >=0 && j+3 <= 14){// Dia 2 - (N) B B  B <N> (N)
                     if(p_map[j+3][i-3] == WHITE && p_map[j+2][i-2] == WHITE && p_map[j+1][i-1] == WHITE){
                         if( (p_map[j+4][i-4] == PAN || p_map[j+4][i-4] == NON) && (p_map[j-1][i+1] == PAN || p_map[j-1][i+1] == NON) && j+4 <= 14 && j-1 >= 0 && i+1 <= 14 && i-4 >= 0){
                             printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                             if(buf_p<10){
                                 buf_xy[buf_p][0]=j;
                                 buf_xy[buf_p][1]=i;
                                 buf_p++;
                                 find_num++;
                             }
                         }
                     }
                 }
                 //
             }
         }
     }
      printf("\n **** ENd Full W3******");
      return find_num;

}

int Game::findHB3(std::array<std::array<int,15>,15>& p_map, std::array<std::array<int, 2>, 10> &buf_xy, int buf_size)
{
    printf("\n **** find Half B3******");
    /*
      경우의 수
      (B) (N) B B (N)
     */
    int p = 0;
    int b = 0;
    int buf_p = 10 - buf_size;
    int find_num = 0;
    for(int j = 0; j < 15; j++){
        for(int i =0; i < 15; i++){
            if(p_map[j][i] == PAN){//only PAN - Black cannot put NON
                if(i+3 <= 14){// 가로 - (N) <N> B B B (N)
                    if(p_map[j][i+1] == BLACK && p_map[j][i+2] == BLACK && p_map[j][i+3] == BLACK){
                        if( (p_map[j][i-1] == WHITE || p_map[j][i-1] == NON ) && (p_map[j][i+4] == WHITE || p_map[j][i+4] == NON ) && i+4 <= 14 && i-1>=0) // 양측 모두 막힌 경우
                        {
//                            printf("\n 1-1 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if (((p_map[j][i-1] == WHITE || p_map[j][i-1] == NON ) || (p_map[j][i+4] == WHITE || p_map[j][i+4] == NON )) && i+4 <= 14 && i-1>=0){//한쪽만 막힌 경우
                            printf("\n 1-1 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if(i-1 >= 0 && i+2 <=14){// 가로 - (N) B <N> B B (N)
                    if(p_map[j][i-1] == BLACK && p_map[j][i+1] == BLACK && p_map[j][i+2] == BLACK){
                        if( (p_map[j][i-2] == WHITE || p_map[j][i-2] == NON) && (p_map[j][i+3] == WHITE || p_map[j][i+3] == NON)  && (i-2 >=0 && i+3 <= 14) ){//양쪽 모두 체크 - 중앙에 있음
                            //printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if(((p_map[j][i-2] == WHITE || p_map[j][i-2] == NON) || (p_map[j][i+3] == WHITE || p_map[j][i+3] == NON))  && (i-2 >=0 && i+3 <= 14)){
                            printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if(i-2 >=0 && i+1 <=14){// 가로 - (N) B  B <N> B (N)
                    if(p_map[j][i-2] == BLACK && p_map[j][i-1] == BLACK && p_map[j][i+1] == BLACK){
                        if( (p_map[j][i-3] == WHITE || p_map[j][i-3] == NON) && (p_map[j][i+2] == WHITE || p_map[j][i+2] == NON)  && i+2 <= 14 && i-3 >= 0){
                            //printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if(((p_map[j][i-3] == WHITE || p_map[j][i-3] == NON) || (p_map[j][i+2] == WHITE || p_map[j][i+2] == NON))  && i+2 <= 14 && i-3 >= 0){
                            printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if( i-3 >=0 ){// 가로 - (N) B B  B <N> (N)
                    if(p_map[j][i-3] == BLACK && p_map[j][i-2] == BLACK && p_map[j][i-1] == BLACK){
                        if( (p_map[j][i-4] == WHITE || p_map[j][i-4] == NON) && (p_map[j][i+1] == WHITE || p_map[j][i+1] == NON) && i+1 <= 14 && i-4 >= 0){
                            //printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if(((p_map[j][i-4] == WHITE || p_map[j][i-4] == NON) || (p_map[j][i+1] == WHITE || p_map[j][i+1] == NON)) && i+1 <= 14 && i-4 >= 0){
                            printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                //// - 세로
                if(j+3 <= 14){// 세로 - (N) <N> B B B (N)
                    if(p_map[j+1][i] == BLACK && p_map[j+2][i] == BLACK && p_map[j+3][i] == BLACK){
                        if( (p_map[j-1][i] == WHITE || p_map[j-1][i] == NON) && (p_map[j+4][i] == WHITE || p_map[j+4][i] == NON ) && j+4 <= 14 && j-1>=0) // 좌 우측 검사
                        {
                            //printf("\n 1-1 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if(((p_map[j-1][i] == WHITE || p_map[j-1][i] == NON) || (p_map[j+4][i] == WHITE || p_map[j+4][i] == NON )) && j+4 <= 14 && j-1>=0){
                            printf("\n 1-1 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if(j-1 >= 0 && j+2 <=14){// 세로 - (N) B <N> B B (N)
                    if(p_map[j-1][i] == BLACK && p_map[j+1][i] == BLACK && p_map[j+2][i] == BLACK){
                        if( (p_map[j-2][i] == WHITE || p_map[j-2][i] == NON) && (p_map[j+3][i] == WHITE || p_map[j+3][i] == NON) && (j-2 >=0 && j+3 <= 14) ){//양쪽 모두 체크 - 중앙에 있음
                            //printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if(((p_map[j-2][i] == WHITE || p_map[j-2][i] == NON) || (p_map[j+3][i] == WHITE || p_map[j+3][i] == NON)) && (j-2 >=0 && j+3 <= 14)){
                            printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if(j-2 >=0 && j+1 <=14){// 세로 - (N) B  B <N> B (N)
                    if(p_map[j-2][i] == BLACK && p_map[j-1][i] == BLACK && p_map[j+1][i] == BLACK){
                        if( (p_map[j-3][i] == WHITE || p_map[j-3][i] == NON)  && (p_map[j+2][i] == WHITE || p_map[j+2][i] == NON) && j+2 <= 14 && j-3 >= 0){
                            //printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if(((p_map[j-3][i] == WHITE || p_map[j-3][i] == NON)  || (p_map[j+2][i] == WHITE || p_map[j+2][i] == NON)) && j+2 <= 14 && j-3 >= 0){
                            printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if( j-3 >=0){// 세로 - (N) B B  B <N> (N)
                    if(p_map[j-3][i] == BLACK && p_map[j-2][i] == BLACK && p_map[j-1][i] == BLACK){
                        if( (p_map[j-4][i] == WHITE || p_map[j-4][i] == NON) && (p_map[j+1][i] == WHITE || p_map[j+1][i] == NON) && j+1 <= 14 && j-4 >= 0){
                            //printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if(((p_map[j-4][i] == WHITE || p_map[j-4][i] == NON) || (p_map[j+1][i] == WHITE || p_map[j+1][i] == NON)) && j+1 <= 14 && j-4 >= 0){
                            printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                // Dia 1 - "\"
                if(i+1 <= 14 && j+3 <= 14){// Dia 1 - (N) <N> B B B (N)
                    if(p_map[j+1][i+1] == BLACK && p_map[j+2][i+2] == BLACK && p_map[j+3][i+3] == BLACK){
                        if( (p_map[j-1][i-1] == WHITE || p_map[j-1][i-1] == NON) && (p_map[j+4][i+4] == WHITE || p_map[j+4][i+4] == NON) && j+4 <= 14 && j-1>=0 && i+4 <= 14 && i-1>=0) // 좌 우측 검사
                        {

                        }else if(((p_map[j-1][i-1] == WHITE || p_map[j-1][i-1] == NON) || (p_map[j+4][i+4] == WHITE || p_map[j+4][i+4] == NON)) && j+4 <= 14 && j-1>=0 && i+4 <= 14 && i-1>=0){
                             printf("\n 1-1 find connect 4 - j = %d , i = %d   ",j,i);
                             if(buf_p<10){
                                 buf_xy[buf_p][0]=j;
                                 buf_xy[buf_p][1]=i;
                                 buf_p++;
                                 find_num++;
                             }
                        }
                    }
                }
                if( i-1 >= 0 && i+2 <=14 && j-1 >= 0 && j+2 <=14){// Dia 1 - (N) B <N> B B (N)
                    if(p_map[j-1][i-1] == BLACK && p_map[j+1][i+1] == BLACK && p_map[j+2][i+2] == BLACK){
                        if( (p_map[j-2][i-2] == WHITE || p_map[j-2][i-2] == NON) && (p_map[j+3][i+3] == WHITE || p_map[j+3][i+3] == NON) && (j-2 >=0 && j+3 <= 14) && (i-2 >=0 && i+3 <= 14) ){//양쪽 모두 체크 - 중앙에 있음

                        }else if( ((p_map[j-2][i-2] == WHITE || p_map[j-2][i-2] == NON) || (p_map[j+3][i+3] == WHITE || p_map[j+3][i+3] == NON)) && (j-2 >=0 && j+3 <= 14) && (i-2 >=0 && i+3 <= 14) ){
                            printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }//
                }
                if(i-2 >=0 && i+1 <=14 && j-2 >=0 && j+1 <=14){// Dia 1 - (N) B  B <N> B (N)
                    if(p_map[j-2][i-2] == BLACK && p_map[j-1][i-1] == BLACK && p_map[j+1][i+1] == BLACK){
                        if( (p_map[j-3][i-3] == WHITE || p_map[j-3][i-3] == NON) && (p_map[j+2][i+2] == WHITE || p_map[j+2][i+2] == NON) && j+2 <= 14 && j-3 >= 0 && i+2 <= 14 && i-3 >= 0){

                        }else if(((p_map[j-3][i-3] == WHITE || p_map[j-3][i-3] == NON) || (p_map[j+2][i+2] == WHITE || p_map[j+2][i+2] == NON)) && j+2 <= 14 && j-3 >= 0 && i+2 <= 14 && i-3 >= 0){
                            printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if( i-3 >=0 && j-3 >=0){// Dia 1 - (N) B B  B <N> (N)
                    if(p_map[j-3][i-3] == BLACK && p_map[j-2][i-2] == BLACK && p_map[j-1][i-1] == BLACK){
                        if( (p_map[j-4][i-4] == WHITE || p_map[j-4][i-4] == NON) && (p_map[j+1][i+1] == WHITE || p_map[j+1][i+1] == NON) && j+1 <= 14 && j-4 >= 0 && i+1 <= 14 && i-4 >= 0){

                        }else if(((p_map[j-4][i-4] == WHITE || p_map[j-4][i-4] == NON) || (p_map[j+1][i+1] == WHITE || p_map[j+1][i+1] == NON)) && j+1 <= 14 && j-4 >= 0 && i+1 <= 14 && i-4 >= 0){
                            printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }

                // DIa 2 - /
                if(i+3 <= 14 && j-3 >=0 ){// DIa 2 - (N) <N> B B B (N)
                    if(p_map[j-1][i+1] == BLACK && p_map[j-2][i+2] == BLACK && p_map[j-3][i+3] == BLACK){
                        if( (p_map[j+1][i-1] == WHITE || p_map[j+1][i-1] == NON) && (p_map[j-4][i+4] == WHITE || p_map[j-4][i+4] == NON) && (j+1<=14 && j-4>=0) && (i+4<=14 && i-1>=0)) // 좌 우측 검사
                        {

                        }else if(((p_map[j+1][i-1] == WHITE || p_map[j+1][i-1] == NON) || (p_map[j-4][i+4] == WHITE || p_map[j-4][i+4] == NON)) && (j+1<=14 && j-4>=0) && (i+4<=14 && i-1>=0)){
                            printf("\n 1-1 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if( i-1>=0 && i+2<=14 && j-2>=0 && j+1<=14 ){// Dia 2 - (N) B <N> B B (N)
                    if(p_map[j+1][i-1] == BLACK && p_map[j-1][i+1] == BLACK && p_map[j-2][i+2] == BLACK){
                        if( (p_map[j+2][i-2] == WHITE || p_map[j+2][i-2] == NON) && (p_map[j-3][i+3] == WHITE || p_map[j-3][i+3] == NON) && (j-3 >=0 && j+2 <= 14) && (i-2 >=0 && i+3 <= 14) ){//양쪽 모두 체크 - 중앙에 있음

                        }else if( ((p_map[j+2][i-2] == WHITE || p_map[j+2][i-2] == NON) || (p_map[j-3][i+3] == WHITE || p_map[j-3][i+3] == NON)) && (j-3 >=0 && j+2 <= 14) && (i-2 >=0 && i+3 <= 14) ){
                            printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if(i-2 >=0 && i+1 <=14 && j+2 >=0 && j-1 <=14){// Dia 2 - (N) B  B <N> B (N)
                    if(p_map[j+2][i-2] == BLACK && p_map[j+1][i-1] == BLACK && p_map[j-1][i+1] == BLACK){
                        if( (p_map[j+3][i-3] == WHITE || p_map[j+3][i-3] == NON) && (p_map[j-2][i+2] == WHITE || p_map[j-2][i+2] == NON) && j+3 <= 14 && j-2 >= 0 && i+2 <= 14 && i-3 >= 0){

                        }else if(((p_map[j+3][i-3] == WHITE || p_map[j+3][i-3] == NON) || (p_map[j-2][i+2] == WHITE || p_map[j-2][i+2] == NON)) && j+3 <= 14 && j-2 >= 0 && i+2 <= 14 && i-3 >= 0){
                            printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if( i-3 >=0 && j+3 <= 14){// Dia 2 - (N) B B  B <N> (N)
                    if(p_map[j+3][i-3] == BLACK && p_map[j+2][i-2] == BLACK && p_map[j+1][i-1] == BLACK){
                        if( (p_map[j+4][i-4] == WHITE || p_map[j+4][i-4] == NON) && (p_map[j-1][i+1] == WHITE || p_map[j-1][i+1] == NON) && j+4 <= 14 && j-1 >= 0 && i+1 <= 14 && i-4 >= 0){

                        }else if(((p_map[j+4][i-4] == WHITE || p_map[j+4][i-4] == NON) || (p_map[j-1][i+1] == WHITE || p_map[j-1][i+1] == NON)) && j+4 <= 14 && j-1 >= 0 && i+1 <= 14 && i-4 >= 0){
                            printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                //
            }
        }
    }
      printf("\n **** ENd Half B3******");
      return find_num;

}

int Game::findHW3(std::array<std::array<int,15>,15>& p_map, std::array<std::array<int, 2>, 10> &buf_xy, int buf_size)
{
    printf("\n **** find Half W3******");
    /*
      경우의 수
      (B) (N) B B (N)
     */
    int p = 0;
    int b = 0;
    int buf_p = 10 - buf_size;
    int find_num = 0;
    for(int j = 0; j < 15; j++){
        for(int i =0; i < 15; i++){
            if(p_map[j][i] == PAN || p_map[j][i] == NON){//only PAN - Black cannot put NON
                if(i+3 <= 14){// 가로 - (N) <N> B B B (N)
                    if(p_map[j][i+1] == WHITE && p_map[j][i+2] == WHITE && p_map[j][i+3] == WHITE){
                        if( (p_map[j][i-1] == BLACK ) && (p_map[j][i+4] == BLACK) && i+4 <= 14 && i-1>=0) // 양측 모두 막힌 경우
                        {
//                            printf("\n 1-1 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if (((p_map[j][i-1] == BLACK) || (p_map[j][i+4] == BLACK )) && i+4 <= 14 && i-1>=0){//한쪽만 막힌 경우
                            printf("\n 1-1 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if(i-1 >= 0 && i+2 <=14){// 가로 - (N) B <N> B B (N)
                    if(p_map[j][i-1] == WHITE && p_map[j][i+1] == WHITE && p_map[j][i+2] == WHITE){
                        if( (p_map[j][i-2] == BLACK ) && (p_map[j][i+3] == BLACK )  && (i-2 >=0 && i+3 <= 14) ){//양쪽 모두 체크 - 중앙에 있음
                            //printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if(((p_map[j][i-2] == BLACK ) || (p_map[j][i+3] == BLACK))  && (i-2 >=0 && i+3 <= 14)){
                            printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if(i-2 >=0 && i+1 <=14){// 가로 - (N) B  B <N> B (N)
                    if(p_map[j][i-2] == WHITE && p_map[j][i-1] == WHITE && p_map[j][i+1] == WHITE){
                        if( (p_map[j][i-3] == BLACK ) && (p_map[j][i+2] == BLACK)  && i+2 <= 14 && i-3 >= 0){
                            //printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if(((p_map[j][i-3] == BLACK) || (p_map[j][i+2] == BLACK))  && i+2 <= 14 && i-3 >= 0){
                            printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if( i-3 >=0 ){// 가로 - (N) B B  B <N> (N)
                    if(p_map[j][i-3] == WHITE && p_map[j][i-2] == WHITE && p_map[j][i-1] == WHITE){
                        if( (p_map[j][i-4] == BLACK) && (p_map[j][i+1] == BLACK) && i+1 <= 14 && i-4 >= 0){
                            //printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if(((p_map[j][i-4] == BLACK) || (p_map[j][i+1] == BLACK)) && i+1 <= 14 && i-4 >= 0){
                            printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                //// - 세로
                if(j+3 <= 14){// 세로 - (N) <N> B B B (N)
                    if(p_map[j+1][i] == WHITE && p_map[j+2][i] == WHITE && p_map[j+3][i] == WHITE){
                        if( (p_map[j-1][i] == BLACK) && (p_map[j+4][i] == BLACK ) && j+4 <= 14 && j-1>=0) // 좌 우측 검사
                        {
                            //printf("\n 1-1 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if(((p_map[j-1][i] == BLACK) || (p_map[j+4][i] == BLACK)) && j+4 <= 14 && j-1>=0){
                            printf("\n 1-1 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if(j-1 >= 0 && j+2 <=14){// 세로 - (N) B <N> B B (N)
                    if(p_map[j-1][i] == WHITE && p_map[j+1][i] == WHITE && p_map[j+2][i] == WHITE){
                        if( (p_map[j-2][i] == BLACK) && (p_map[j+3][i] == BLACK ) && (j-2 >=0 && j+3 <= 14) ){//양쪽 모두 체크 - 중앙에 있음
                            //printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if(((p_map[j-2][i] == BLACK) || (p_map[j+3][i] == BLACK )) && (j-2 >=0 && j+3 <= 14)){
                            printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if(j-2 >=0 && j+1 <=14){// 세로 - (N) B  B <N> B (N)
                    if(p_map[j-2][i] == WHITE && p_map[j-1][i] == WHITE && p_map[j+1][i] == WHITE){
                        if( (p_map[j-3][i] == BLACK)  && (p_map[j+2][i] == BLACK) && j+2 <= 14 && j-3 >= 0){
                            //printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if(((p_map[j-3][i] == BLACK)  || (p_map[j+2][i] == BLACK )) && j+2 <= 14 && j-3 >= 0){
                            printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if( j-3 >=0){// 세로 - (N) B B  B <N> (N)
                    if(p_map[j-3][i] == WHITE && p_map[j-2][i] == WHITE && p_map[j-1][i] == WHITE){
                        if( (p_map[j-4][i] == BLACK ) && (p_map[j+1][i] == BLACK) && j+1 <= 14 && j-4 >= 0){
                            //printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if(((p_map[j-4][i] == BLACK) || (p_map[j+1][i] == BLACK)) && j+1 <= 14 && j-4 >= 0){
                            printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                // Dia 1 - "\"
                if(i+1 <= 14 && j+3 <= 14){// Dia 1 - (N) <N> B B B (N)
                    if(p_map[j+1][i+1] == WHITE && p_map[j+2][i+2] == WHITE && p_map[j+3][i+3] == WHITE){
                        if( (p_map[j-1][i-1] == BLACK ) && (p_map[j+4][i+4] == BLACK) && j+4 <= 14 && j-1>=0 && i+4 <= 14 && i-1>=0) // 좌 우측 검사
                        {

                        }else if(((p_map[j-1][i-1] == BLACK) || (p_map[j+4][i+4] == BLACK )) && j+4 <= 14 && j-1>=0 && i+4 <= 14 && i-1>=0){
                             printf("\n 1-1 find connect 4 - j = %d , i = %d   ",j,i);
                             if(buf_p<10){
                                 buf_xy[buf_p][0]=j;
                                 buf_xy[buf_p][1]=i;
                                 buf_p++;
                                 find_num++;
                             }
                        }
                    }
                }
                if( i-1 >= 0 && i+2 <=14 && j-1 >= 0 && j+2 <=14){// Dia 1 - (N) B <N> B B (N)
                    if(p_map[j-1][i-1] == WHITE && p_map[j+1][i+1] == WHITE && p_map[j+2][i+2] == WHITE){
                        if( (p_map[j-2][i-2] == BLACK) && (p_map[j+3][i+3] == BLACK ) && (j-2 >=0 && j+3 <= 14) && (i-2 >=0 && i+3 <= 14) ){//양쪽 모두 체크 - 중앙에 있음

                        }else if( ((p_map[j-2][i-2] == BLACK ) || (p_map[j+3][i+3] == BLACK )) && (j-2 >=0 && j+3 <= 14) && (i-2 >=0 && i+3 <= 14) ){
                            printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }//
                }
                if(i-2 >=0 && i+1 <=14 && j-2 >=0 && j+1 <=14){// Dia 1 - (N) B  B <N> B (N)
                    if(p_map[j-2][i-2] == WHITE && p_map[j-1][i-1] == WHITE && p_map[j+1][i+1] == WHITE){
                        if( (p_map[j-3][i-3] == BLACK ) && (p_map[j+2][i+2] == BLACK) && j+2 <= 14 && j-3 >= 0 && i+2 <= 14 && i-3 >= 0){

                        }else if(((p_map[j-3][i-3] == BLACK) || (p_map[j+2][i+2] == BLACK)) && j+2 <= 14 && j-3 >= 0 && i+2 <= 14 && i-3 >= 0){
                            printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if( i-3 >=0 && j-3 >=0){// Dia 1 - (N) B B  B <N> (N)
                    if(p_map[j-3][i-3] == WHITE && p_map[j-2][i-2] == WHITE && p_map[j-1][i-1] == WHITE){
                        if( (p_map[j-4][i-4] == BLACK ) && (p_map[j+1][i+1] == BLACK ) && j+1 <= 14 && j-4 >= 0 && i+1 <= 14 && i-4 >= 0){

                        }else if(((p_map[j-4][i-4] == BLACK) || (p_map[j+1][i+1] == BLACK)) && j+1 <= 14 && j-4 >= 0 && i+1 <= 14 && i-4 >= 0){
                            printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }

                // DIa 2 - /
                if(i+3 <= 14 && j-3 >=0 ){// DIa 2 - (N) <N> B B B (N)
                    if(p_map[j-1][i+1] == WHITE && p_map[j-2][i+2] == WHITE && p_map[j-3][i+3] == WHITE){
                        if( (p_map[j+1][i-1] == BLACK ) && (p_map[j-4][i+4] == BLACK ) && (j+1<=14 && j-4>=0) && (i+4<=14 && i-1>=0)) // 좌 우측 검사
                        {

                        }else if(((p_map[j+1][i-1] == BLACK ) || (p_map[j-4][i+4] == BLACK )) && (j+1<=14 && j-4>=0) && (i+4<=14 && i-1>=0)){
                            printf("\n 1-1 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if( i-1>=0 && i+2<=14 && j-2>=0 && j+1<=14 ){// Dia 2 - (N) B <N> B B (N)
                    if(p_map[j+1][i-1] == WHITE && p_map[j-1][i+1] == WHITE && p_map[j-2][i+2] == WHITE){
                        if( (p_map[j+2][i-2] == BLACK ) && (p_map[j-3][i+3] == BLACK ) && (j-3 >=0 && j+2 <= 14) && (i-2 >=0 && i+3 <= 14) ){//양쪽 모두 체크 - 중앙에 있음

                        }else if( ((p_map[j+2][i-2] == BLACK ) || (p_map[j-3][i+3] == BLACK )) && (j-3 >=0 && j+2 <= 14) && (i-2 >=0 && i+3 <= 14) ){
                            printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if(i-2 >=0 && i+1 <=14 && j+2 >=0 && j-1 <=14){// Dia 2 - (N) B  B <N> B (N)
                    if(p_map[j+2][i-2] == WHITE && p_map[j+1][i-1] == WHITE && p_map[j-1][i+1] == WHITE){
                        if( (p_map[j+3][i-3] == BLACK ) && (p_map[j-2][i+2] == BLACK ) && j+3 <= 14 && j-2 >= 0 && i+2 <= 14 && i-3 >= 0){

                        }else if(((p_map[j+3][i-3] == BLACK ) || (p_map[j-2][i+2] == BLACK)) && j+3 <= 14 && j-2 >= 0 && i+2 <= 14 && i-3 >= 0){
                            printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if( i-3 >=0 && j+3 <= 14){// Dia 2 - (N) B B  B <N> (N)
                    if(p_map[j+3][i-3] == WHITE && p_map[j+2][i-2] == WHITE && p_map[j+1][i-1] == WHITE){
                        if( (p_map[j+4][i-4] == BLACK ) && (p_map[j-1][i+1] == BLACK ) && j+4 <= 14 && j-1 >= 0 && i+1 <= 14 && i-4 >= 0){

                        }else if(((p_map[j+4][i-4] == BLACK) || (p_map[j-1][i+1] == BLACK )) && j+4 <= 14 && j-1 >= 0 && i+1 <= 14 && i-4 >= 0){
                            printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                //
            }
        }
    }
      printf("\n **** ENd Half W3******");
      return find_num;
}

int Game::findB2(std::array<std::array<int,15>,15>& p_map, std::array<std::array<int, 2>, 10> &buf_xy, int buf_size)//will make 3
{
    printf("\n **** find B2******");
    /*
      경우의 수
      (B) (N) B B (N)
     */
    int p = 0;
    int b = 0;
    int buf_p = 10 - buf_size;
    int find_num = 0;
    for(int j = 0; j<=14;j++){
        for(int i=0; i<=14;i++){
            if(p_map[j][i] == PAN){//BLACK - PAN, WHITE - PAN + NON
                //가로
                // 1번째
                // (N) <B> B B (N)
                // <B> B (N) B (N)
                // <B> (N) B B (N)
                // <B> (N) B (N) B
                if(p_map[j][i-1] == PAN &&
                        p_map[j][i+1] == BLACK &&
                        p_map[j][i+2] == BLACK &&
                        p_map[j][i+3] == PAN &&
                        i-1>=0 && i+3<=14){// (N) <B> B B (N)
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if(p_map[j][i-1] == PAN &&
                        p_map[j][i+1] == BLACK &&
                        p_map[j][i+2] == PAN &&
                        p_map[j][i+3] == BLACK &&
                        p_map[j][i+4] == PAN &&
                        i-1 >= 0 && i+4<=14){// <B> B (N) B (N)
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if(p_map[j][i-1] == PAN &&
                        p_map[j][i+1] == PAN &&
                        p_map[j][i+2] == BLACK &&
                        p_map[j][i+3] == BLACK &&
                        p_map[j][i+4] == PAN &&
                        i-1 >=0 && i+4<=14){// <B> (N) B B (N)
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if(p_map[j][i+1] == PAN &&
                        p_map[j][i+2] == BLACK &&
                        p_map[j][i+3] == PAN &&
                        p_map[j][i+4] == BLACK &&
                        i+4<=14){// <B> (N) B (N) B
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                //2번째
                // N  B <B> B N
                // B <B> N  B N
                if(p_map[j][i-2] == PAN &&
                        p_map[j][i-1] == BLACK &&
                        p_map[j][i+1] == BLACK &&
                        p_map[j][i+2] == PAN &&
                        i-2 >=0 && i+2 <= 14){// N  B <B> B N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if(p_map[j][i-2] == PAN &&
                        p_map[j][i-1] == BLACK &&
                        p_map[j][i+1] == PAN &&
                        p_map[j][i+2] == BLACK &&
                        p_map[j][i+3] == PAN &&
                        i-2 >=0 && i+3 <= 14){  // B <B> N  B N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                //3번째
                // B N <B> B N
                // B N <B> N B
                // N B B <B> N
                if(p_map[j][i-2] == BLACK &&
                        p_map[j][i-1] == PAN &&
                        p_map[j][i+1] == BLACK &&
                        p_map[j][i+2] == PAN &&
                        i-2 >=0 && i+2 <=14){// B N <B> B N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if(p_map[j][-3] == PAN &&
                        p_map[j][i-2] == BLACK &&
                        p_map[j][i-1] == PAN &&
                        p_map[j][i+1] == PAN &&
                        p_map[j][i+2] == BLACK &&
                        i-3 >=0 && i+2 <=14){//// B N <B> N B
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if(p_map[j][i-3] == PAN &&
                        p_map[j][i-2] == BLACK &&
                        p_map[j][i-1] == BLACK &&
                        p_map[j][i+1] == PAN &&
                        i-3 >=0 && i+1 <=14){// N B B <B> N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                //4번째
                // B B N <B> N
                // B N B <B> N
                if(p_map[j][i-4] == PAN &&
                        p_map[j][i-3] == BLACK &&
                        p_map[j][i-2] == BLACK &&
                        p_map[j][i-1] == PAN &&
                        p_map[j][i+1] == PAN &&
                        i-4>=0 && i+1<=14){// B B N <B> N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if(p_map[j][i-4] == PAN &&
                        p_map[j][i-3] == BLACK &&
                        p_map[j][i-2] == PAN &&
                        p_map[j][i-1] == BLACK &&
                        p_map[j][i+1] == PAN &&
                        i-4>=0 && i+1<=14){// B N B <B> N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }

                //5번째
                // B N B N <B>
                if(p_map[j][i-4] == BLACK &&
                        p_map[j][i-3] == PAN &&
                        p_map[j][i-2] == BLACK &&
                        p_map[j][i-1] == PAN &&
                        i-4>=0){
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }

                //세로-------------
                // 1번째
                // (N) <B> B B (N)
                // <B> B (N) B (N)
                // <B> (N) B B (N)
                // <B> (N) B (N) B
                if(p_map[j-1][i] == PAN &&
                        p_map[j+1][i] == BLACK &&
                        p_map[j+2][i] == BLACK &&
                        p_map[j+3][i] == PAN &&
                        j-1>=0 && j+3<=14){// (N) <B> B B (N)
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if(p_map[j-1][i] == PAN &&
                        p_map[j+1][i] == BLACK &&
                        p_map[j+2][i] == PAN &&
                        p_map[j+3][i] == BLACK &&
                        p_map[j+4][i] == PAN &&
                        j-1 >=0 && j+4<=14){// <B> B (N) B (N)
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if(p_map[j-1][i] == PAN &&
                        p_map[j+1][i] == PAN &&
                        p_map[j+2][i] == BLACK &&
                        p_map[j+3][i] == BLACK &&
                        p_map[j+4][i] == PAN &&
                        j-1 >=0 && j+4<=14){// <B> (N) B B (N)
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if(p_map[j+1][i] == PAN &&
                        p_map[j+2][i] == BLACK &&
                        p_map[j+3][i] == PAN &&
                        p_map[j+4][i] == BLACK &&
                        j+4<=14){// <B> (N) B (N) B
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                //2번째
                // N  B <B> B N
                // B <B> N  B N
                if(p_map[j-2][i] == PAN &&
                        p_map[j-1][i] == BLACK &&
                        p_map[j+1][i] == BLACK &&
                        p_map[j+2][i] == PAN &&
                        j-2 >=0 && j+2 <= 14){// N  B <B> B N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if(p_map[j-2][i] == PAN &&
                        p_map[j-1][i] == BLACK &&
                        p_map[j+1][i] == PAN &&
                        p_map[j+2][i] == BLACK &&
                        p_map[j+3][i] == PAN &&
                        j-2 >=0 && j+3 <= 14){  // B <B> N  B N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                //3번째
                // B N <B> B N
                // B N <B> N B
                // N B B <B> N
                if(p_map[j-3][i] == PAN &&
                        p_map[j-2][i] == BLACK &&
                        p_map[j-1][i] == PAN &&
                        p_map[j+1][i] == BLACK &&
                        p_map[j+2][i] == PAN &&
                        j-3 >=0 && j+2 <=14){// B N <B> B N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if(p_map[j-2][i] == BLACK &&
                        p_map[j-1][i] == PAN &&
                        p_map[j+1][i] == PAN &&
                        p_map[j+2][i] == BLACK &&
                        j-2 >=0 && j+2 <=14){// B N <B> N B
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if(p_map[j-3][i] == PAN &&
                        p_map[j-2][i] == BLACK &&
                        p_map[j-1][i] == BLACK &&
                        p_map[j+1][i] == PAN &&
                        j-3 >=0 && j+1 <=14){// N B B <B> N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                //4번째
                // B B N <B> N
                // B N B <B> N
                if(p_map[j-4][i] == PAN &&
                        p_map[j-3][i] == BLACK &&
                        p_map[j-2][i] == BLACK &&
                        p_map[j-1][i] == PAN &&
                        p_map[j+1][i] == PAN &&
                        j-4>=0 && j+1<=14){// B B N <B> N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if(p_map[j-4][i] == PAN &&
                        p_map[j-3][i] == BLACK &&
                        p_map[j-2][i] == PAN &&
                        p_map[j-1][i] == BLACK &&
                        p_map[j+1][i] == PAN &&
                        j-4>=0 && j+1<=14){// B N B <B> N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }

                //5번째
                // B N B N <B>
                if(p_map[j-4][i] == BLACK &&
                        p_map[j-3][i] == PAN &&
                        p_map[j-2][i] == BLACK &&
                        p_map[j-1][i] == PAN &&
                        j-4>=0){
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }

                //Dia 1 - "\" ----------------
                // 1번째
                // (N) <B> B B (N)
                // <B> B (N) B (N)
                // <B> (N) B B (N)
                // <B> (N) B (N) B
                if(p_map[j-1][i-1] == PAN &&
                        p_map[j+1][i+1] == BLACK &&
                        p_map[j+2][i+2] == BLACK &&
                        p_map[j+3][i+3] == PAN &&
                        j-1>=0 && j+3<=14 && i-1>=0 && i+3<=14){// (N) <B> B B (N)
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if(p_map[j-1][i-1] == PAN &&
                        p_map[j+1][i+1] == BLACK &&
                        p_map[j+2][i+2] == PAN &&
                        p_map[j+3][i+3] == BLACK &&
                        p_map[j+4][i+4] == PAN &&
                        j-1 >=0 && i-1 >=0 && j+4<=14 && i+4<=14){// <B> B (N) B (N)
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if(p_map[j-1][i-1] == PAN &&
                        p_map[j+1][i+1] == PAN &&
                        p_map[j+2][i+2] == BLACK &&
                        p_map[j+3][i+3] == BLACK &&
                        p_map[j+4][i+4] == PAN &&
                        j+4<=14 && i+4<=14 && j-1 >=0 && i-1 >=0){// <B> (N) B B (N)
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if(p_map[j+1][i+1] == PAN &&
                        p_map[j+2][i+2] == BLACK &&
                        p_map[j+3][i+3] == PAN &&
                        p_map[j+4][i+4] == BLACK &&
                        j+4<=14 && i+4<=14){// <B> (N) B (N) B
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                //2번째
                // N  B <B> B N
                // B <B> N  B N
                if(p_map[j-2][i-2] == PAN &&
                        p_map[j-1][i-1] == BLACK &&
                        p_map[j+1][i+1] == BLACK &&
                        p_map[j+2][i+2] == PAN &&
                        j-2 >=0 && j+2 <= 14 && i-2 >=0 && i+2 <= 14){// N  B <B> B N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if(p_map[j-2][i-2] == PAN &&
                        p_map[j-1][i-1] == BLACK &&
                        p_map[j+1][i+1] == PAN &&
                        p_map[j+2][i+2] == BLACK &&
                        p_map[j+3][i+3] == PAN &&
                        j-2 >=0 && j+3 <= 14 && i-2 >=0 && i+3 <= 14){  // B <B> N  B N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                //3번째
                // B N <B> B N
                // B N <B> N B
                // N B B <B> N
                if(p_map[j-3][i-3] == PAN &&
                        p_map[j-2][i-2] == BLACK &&
                        p_map[j-1][i-1] == PAN &&
                        p_map[j+1][i+1] == BLACK &&
                        p_map[j+2][i+2] == PAN &&
                        j-3 >=0 && j+2 <=14 && i-3 >=0 && i+2 <=14){// B N <B> B N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if(p_map[j-2][i-2] == BLACK &&
                        p_map[j-1][i-1] == PAN &&
                        p_map[j+1][i+1] == PAN &&
                        p_map[j+2][i+2] == BLACK &&
                        j-2 >=0 && j+2 <=14 && i-2 >=0 && i+2 <=14){// B N <B> N B
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if(p_map[j-3][i-3] == PAN &&
                        p_map[j-2][i-2] == BLACK &&
                        p_map[j-1][i-1] == BLACK &&
                        p_map[j+1][i+1] == PAN &&
                        j-3 >=0 && j+1 <=14 && i-3 >=0 && i+1 <=14){// N B B <B> N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                //4번째
                // B B N <B> N
                // B N B <B> N
                if(p_map[j-4][i-4] == PAN &&
                        p_map[j-3][i-3] == BLACK &&
                        p_map[j-2][i-2] == BLACK &&
                        p_map[j-1][i-1] == PAN &&
                        p_map[j+1][i+1] == PAN &&
                        j-4>=0 && j+1<=14 && i-4>=0 && i+1<=14){// B B N <B> N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if(p_map[j-4][i-4] == PAN &&
                        p_map[j-3][i-3] == BLACK &&
                        p_map[j-2][i-2] == PAN &&
                        p_map[j-1][i-1] == BLACK &&
                        p_map[j+1][i+1] == PAN &&
                        j-4>=0 && j+1<=14 && i-4>=0 && i+1<=14){// B N B <B> N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }

                //5번째
                // B N B N <B>
                if(p_map[j-4][i-4] == BLACK &&
                        p_map[j-3][i-3] == PAN &&
                        p_map[j-2][i-2] == BLACK &&
                        p_map[j-1][i-1] == PAN &&
                        j-4>=0 && i-4>=0){
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                //Dia 2 = "/" ----------------
                // 1번째
                // (N) <B> B B (N)
                // <B> B (N) B (N)
                // <B> (N) B B (N)
                // <B> (N) B (N) B
                if(p_map[j+1][i-1] == PAN &&
                        p_map[j-1][i+1] == BLACK &&
                        p_map[j-2][i+2] == BLACK &&
                        p_map[j-3][i+3] == PAN &&
                        j-3>=0 && j+1<=14 && i-1>=0 && i+3<=14){// (N) <B> B B (N)
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if(p_map[j+1][i-1] == PAN &&
                        p_map[j-1][i+1] == BLACK &&
                        p_map[j-2][i+2] == PAN &&
                        p_map[j-3][i+3] == BLACK &&
                        p_map[j-4][i+4] == PAN &&
                        i-1 >=0 && j+1 <=14 && j-4>=0 && i+4<=14){// <B> B (N) B (N)
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if(p_map[j+1][i-1] == PAN &&
                        p_map[j-1][i+1] == PAN &&
                        p_map[j-2][i+2] == BLACK &&
                        p_map[j-3][i+3] == BLACK &&
                        p_map[j-4][i+4] == PAN &&
                        j+1<=14 && i-1 >=0 && j-4>=0 && i+4<=14){// <B> (N) B B (N)
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if(p_map[j-1][i+1] == PAN &&
                        p_map[j-2][i+2] == BLACK &&
                        p_map[j-3][i+3] == PAN &&
                        p_map[j-4][i+4] == BLACK &&
                        j-4>=0 && i+4<=14){// <B> (N) B (N) B
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                //2번째
                // N  B <B> B N
                // B <B> N  B N
                if(p_map[j+2][i-2] == PAN &&
                        p_map[j+1][i-1] == BLACK &&
                        p_map[j-1][i+1] == BLACK &&
                        p_map[j-2][i+2] == PAN &&
                        j-2 >=0 && j+2 <= 14 && i-2 >=0 && i+2 <= 14){// N  B <B> B N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if(p_map[j+2][i-2] == PAN &&
                        p_map[j+1][i-1] == BLACK &&
                        p_map[j-1][i+1] == PAN &&
                        p_map[j-2][i+2] == BLACK &&
                        p_map[j-3][i+3] == PAN &&
                        j-3 >=0 && j+2 <= 14 && i-2 >=0 && i+3 <= 14){  // B <B> N  B N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                //3번째
                // B N <B> B N
                // B N <B> N B
                // N B B <B> N
                if(p_map[j+3][i-3] == PAN &&
                        p_map[j+2][i-2] == BLACK &&
                        p_map[j+1][i-1] == PAN &&
                        p_map[j-1][i+1] == BLACK &&
                        p_map[j-2][i+2] == PAN &&
                        j-2 >=0 && j+3 <=14 && i-3 >=0 && i+2 <=14){// B N <B> B N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if(p_map[j+2][i-2] == BLACK &&
                        p_map[j+1][i-1] == PAN &&
                        p_map[j-1][i+1] == PAN &&
                        p_map[j-2][i+2] == BLACK &&
                        j-2 >=0 && j+2 <=14 && i-2 >=0 && i+2 <=14){// B N <B> N B
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if(p_map[j+3][i-3] == PAN &&
                        p_map[j+2][i-2] == BLACK &&
                        p_map[j+1][i-1] == BLACK &&
                        p_map[j-1][i+1] == PAN &&
                        j-1 >=0 && j+3 <=14 && i-3 >=0 && i+1 <=14){// N B B <B> N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                //4번째
                // B B N <B> N
                // B N B <B> N
                if(p_map[j+4][i-4] == PAN &&
                        p_map[j+3][i-3] == BLACK &&
                        p_map[j+2][i-2] == BLACK &&
                        p_map[j+1][i-1] == PAN &&
                        p_map[j-1][i+1] == PAN &&
                        j-1>=0 && j+4<=14 && i-4>=0 && i+1<=14){// B B N <B> N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if(p_map[j+4][i-4] == PAN &&
                        p_map[j+3][i-3] == BLACK &&
                        p_map[j+2][i-2] == PAN &&
                        p_map[j+1][i-1] == BLACK &&
                        p_map[j-1][i+1] == PAN &&
                        j-1>=0 && j+4<=14 && i-4>=0 && i+1<=14){// B N B <B> N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }

                //5번째
                // B N B N <B>
                if(p_map[j+4][i-4] == BLACK &&
                        p_map[j+3][i-3] == PAN &&
                        p_map[j+2][i-2] == BLACK &&
                        p_map[j+1][i-1] == PAN &&
                        j+4<=14 && i-4>=0){
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
            }
        }
    }

    printf("\n **** ENd B2******");
    return find_num;
}

int Game::findW2(std::array<std::array<int,15>,15>& p_map, std::array<std::array<int, 2>, 10> &buf_xy, int buf_size)
{
    printf("\n **** find W2******");
    /*
      경우의 수
      (B) (N) B B (N)
     */
    int p = 0;
    int b = 0;
    int buf_p = 10 - buf_size;
    int find_num =0;
    for(int j = 0; j<=14;j++){
        for(int i=0; i<=14;i++){
            if(p_map[j][i] == PAN || p_map[j][i] == NON){//BLACK - PAN, WHITE - PAN + NON
                //가로
                // 1번째
                // (N) <B> B B (N)
                // <B> B (N) B (N)
                // <B> (N) B B (N)
                // <B> (N) B (N) B
                if((p_map[j][i-1] == PAN || p_map[j][i-1] == NON )&&
                        p_map[j][i+1] == WHITE &&
                        p_map[j][i+2] == WHITE &&
                        (p_map[j][i+3] == PAN || p_map[j][i+3] == NON) &&
                        i-1>=0 && i+3<=14){// (N) <B> B B (N)
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if( (p_map[j][i-1] == PAN || p_map[j][i-1] == NON ) &&
                        p_map[j][i+1] == WHITE &&
                        (p_map[j][i+2] == PAN ||  p_map[j][i+2] == NON )&&
                        p_map[j][i+3] == WHITE &&
                        (p_map[j][i+4] == PAN || p_map[j][i+4] == NON) &&
                        i+4<=14 && i-1 >=0 ){// <B> B (N) B (N)
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if( (p_map[j][i-1] == PAN || p_map[j][i-1] == NON ) &&
                        (p_map[j][i+1] == PAN || p_map[j][i+1] == NON) &&
                        p_map[j][i+2] == WHITE &&
                        p_map[j][i+3] == WHITE &&
                        (p_map[j][i+4] == PAN || p_map[j][i+4] == NON)&&
                        i-1>=0 && i+4<=14){// <B> (N) B B (N)
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if((p_map[j][i+1] == PAN || p_map[j][i+1] == NON) &&
                        p_map[j][i+2] == WHITE &&
                        (p_map[j][i+3] == PAN || p_map[j][i+3] == NON) &&
                        p_map[j][i+4] == WHITE &&
                        i+4<=14){// <B> (N) B (N) B
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                //2번째
                // N  B <B> B N
                // B <B> N  B N
                if((p_map[j][i-2] == PAN || p_map[j][i-2] == NON) &&
                        p_map[j][i-1] == WHITE &&
                        p_map[j][i+1] == WHITE &&
                        (p_map[j][i+2] == PAN || p_map[j][i+2] == NON) &&
                        i-2 >=0 && i+2 <= 14){// N  B <B> B N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if((p_map[j][i-2] == PAN || p_map[j][i-2] == NON) &&
                        p_map[j][i-1] == WHITE &&
                        (p_map[j][i+1] == PAN || p_map[j][i+1] == NON) &&
                        p_map[j][i+2] == WHITE &&
                        (p_map[j][i+3] == PAN || p_map[j][i+3] == NON) &&
                        i-2 >=0 && i+3 <= 14){  // B <B> N  B N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                //3번째
                // B N <B> B N
                // B N <B> N B
                // N B B <B> N
                if((p_map[j][i-3] == PAN || p_map[j][i-3] ==NON) &&
                        p_map[j][i-2] == WHITE &&
                        (p_map[j][i-1] == PAN || p_map[j][i-1] == NON) &&
                        p_map[j][i+1] == WHITE &&
                        (p_map[j][i+2] == PAN || p_map[j][i+2] == NON) &&
                        i-3 >=0 && i+2 <=14){// B N <B> B N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if(p_map[j][i-2] == WHITE &&
                        (p_map[j][i-1] == PAN || p_map[j][i-1] == NON) &&
                        (p_map[j][i+1] == PAN || p_map[j][i+1] == NON) &&
                        p_map[j][i+2] == WHITE &&
                        i-2 >=0 && i+2 <=14){//// B N <B> N B
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if((p_map[j][i-3] == PAN || p_map[j][i-3] == NON) &&
                        p_map[j][i-2] == WHITE &&
                        p_map[j][i-1] == WHITE &&
                        (p_map[j][i+1] == PAN || p_map[j][i+1] == NON) &&
                        i-3 >=0 && i+1 <=14){// N B B <B> N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                //4번째
                // B B N <B> N
                // B N B <B> N
                if((p_map[j][i-4] == PAN || p_map[j][i-4] == NON ) &&
                        p_map[j][i-3] == WHITE &&
                        p_map[j][i-2] == WHITE &&
                        (p_map[j][i-1] == PAN || p_map[j][i-1] == NON) &&
                        (p_map[j][i+1] == PAN || p_map[j][i+1] == NON) &&
                        i-4>=0 && i+1<=14){// B B N <B> N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if((p_map[j][i-4] == PAN|| p_map[j][i-4] == NON) &&
                        p_map[j][i-3] == WHITE &&
                        (p_map[j][i-2] == PAN || p_map[j][i-2] == NON) &&
                        p_map[j][i-1] == WHITE &&
                        (p_map[j][i+1] == PAN || p_map[j][i+1] == NON) &&
                        i-4>=0 && i+1<=14){// B N B <B> N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }

                //5번째
                // B N B N <B>
                if(p_map[j][i-4] == WHITE &&
                        (p_map[j][i-3] == PAN || p_map[j][i-3] == NON) &&
                        p_map[j][i-2] == WHITE &&
                        (p_map[j][i-1] == PAN || p_map[j][i-1] == NON) &&
                        i-4>=0){
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }

                //세로-------------
                // 1번째
                // (N) <B> B B (N)
                // <B> B (N) B (N)
                // <B> (N) B B (N)
                // <B> (N) B (N) B
                if((p_map[j-1][i] == PAN || p_map[j-1][i] == NON) &&
                        p_map[j+1][i] == WHITE &&
                        p_map[j+2][i] == WHITE &&
                        (p_map[j+3][i] == PAN || p_map[j+3][i] == PAN) &&
                        j-1>=0 && j+3<=14){// (N) <B> B B (N)
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if((p_map[j-1][i] == PAN || p_map[j-1][i] == NON) &&
                        p_map[j+1][i] == WHITE &&
                        (p_map[j+2][i] == PAN || p_map[j+2][i] == NON) &&
                        p_map[j+3][i] == WHITE &&
                        (p_map[j+4][i] == PAN  || p_map[j+4][i] == NON) &&
                        j-1 >=0 && j+4<=14){// <B> B (N) B (N)
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if((p_map[j-1][i] == PAN || p_map[j-1][i] == NON) &&
                        (p_map[j+1][i] == PAN || p_map[j+1][i] == NON) &&
                        p_map[j+2][i] == WHITE &&
                        p_map[j+3][i] == WHITE &&
                        (p_map[j+4][i] == PAN || p_map[j+4][i] == NON) &&
                        j-1>=0 && j+4<=14){// <B> (N) B B (N)
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if((p_map[j+1][i] == PAN || p_map[j+1][i] == NON) &&
                        p_map[j+2][i] == WHITE &&
                        (p_map[j+3][i] == PAN || p_map[j+3][i] == NON) &&
                        p_map[j+4][i] == WHITE &&
                        j+4<=14){// <B> (N) B (N) B
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                //2번째
                // N  B <B> B N
                // B <B> N  B N
                if((p_map[j-2][i] == PAN || p_map[j-2][i] == NON) &&
                        p_map[j-1][i] == WHITE &&
                        p_map[j+1][i] == WHITE &&
                        (p_map[j+2][i] == NON || p_map[j+2][i] == PAN) &&
                        j-2 >=0 && j+2 <= 14){// N  B <B> B N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if((p_map[j-2][i] == PAN || p_map[j-2][i] == NON) &&
                        p_map[j-1][i] == WHITE &&
                        (p_map[j+1][i] == PAN || p_map[j+1][i] == NON) &&
                        p_map[j+2][i] == WHITE &&
                        (p_map[j+3][i] == PAN || p_map[j+3][i] == NON) &&
                        j-2 >=0 && j+3 <= 14){  // B <B> N  B N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                //3번째
                // B N <B> B N
                // B N <B> N B
                // N B B <B> N
                if((p_map[j-3][i] == PAN || p_map[j-3][i] == NON) &&
                        p_map[j-2][i] == WHITE &&
                        (p_map[j-1][i] == PAN || p_map[j-1][i] == NON) &&
                        p_map[j+1][i] == WHITE &&
                        (p_map[j+2][i] == PAN || p_map[j+2][i] == NON) &&
                        j-3 >=0 && j+2 <=14){// B N <B> B N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if(p_map[j-2][i] == WHITE &&
                        (p_map[j-1][i] == PAN || p_map[j-1][i] == NON) &&
                        (p_map[j+1][i] == PAN || p_map[j+1][i] == NON) &&
                        p_map[j+2][i] == WHITE &&
                        j-2 >=0 && j+2 <=14){// B N <B> N B
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if((p_map[j-3][i] == PAN || p_map[j-3][i] == NON) &&
                        p_map[j-2][i] == WHITE &&
                        p_map[j-1][i] == WHITE &&
                        (p_map[j+1][i] == PAN || p_map[j+1][i] == NON) &&
                        j-3 >=0 && j+1 <=14){// N B B <B> N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                //4번째
                // B B N <B> N
                // B N B <B> N
                if((p_map[j-4][i] == PAN || p_map[j-4][i] == NON) &&
                        p_map[j-3][i] == WHITE &&
                        p_map[j-2][i] == WHITE &&
                        (p_map[j-1][i] == PAN || p_map[j-1][i] == NON) &&
                        (p_map[j+1][i] == PAN || p_map[j+1][i] == NON) &&
                        j-4>=0 && j+1<=14){// B B N <B> N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if((p_map[j-4][i] == PAN || p_map[j-4][i] == NON) &&
                        p_map[j-3][i] == WHITE &&
                        (p_map[j-2][i] == PAN || p_map[j-2][i] == NON) &&
                        p_map[j-1][i] == WHITE &&
                        (p_map[j+1][i] == PAN || p_map[j+1][i] == NON) &&
                        j-4>=0 && j+1<=14){// B N B <B> N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }

                //5번째
                // B N B N <B>
                if(p_map[j-4][i] == WHITE &&
                        (p_map[j-3][i] == PAN || p_map[j-3][i] == NON) &&
                        p_map[j-2][i] == WHITE &&
                        (p_map[j-1][i] == PAN || p_map[j-1][i] == NON) &&
                        j-4>=0){
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }

                //Dia 1 - "\" ----------------
                // 1번째
                // (N) <B> B B (N)
                // <B> B (N) B (N)
                // <B> (N) B B (N)
                // <B> (N) B (N) B
                if((p_map[j-1][i-1] == PAN || p_map[j-1][i-1] == NON) &&
                        p_map[j+1][i+1] == WHITE &&
                        p_map[j+2][i+2] == WHITE &&
                        (p_map[j+3][i+3] == PAN || p_map[j+3][i+3] == NON) &&
                        j-1>=0 && j+3<=14 && i-1>=0 && i+3<=14){// (N) <B> B B (N)
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if((p_map[j-1][i-1] == PAN || p_map[j-1][i-1] == NON) &&
                        p_map[j+1][i+1] == WHITE &&
                        (p_map[j+2][i+2] == PAN || p_map[j+2][i+2] == NON) &&
                        p_map[j+3][i+3] == WHITE &&
                        (p_map[j+4][i+4] == PAN || p_map[j+4][i+4] == NON) &&
                        j-1>=0 && i-1>=0 && j+4<=14 && i+4<=14){// <B> B (N) B (N)
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if((p_map[j-1][i-1] == PAN || p_map[j-1][i-1] == NON) &&
                        (p_map[j+1][i+1] == PAN || p_map[j+1][i+1] == NON) &&
                        p_map[j+2][i+2] == WHITE &&
                        p_map[j+3][i+3] == WHITE &&
                        (p_map[j+4][i+4] == PAN  || p_map[j+4][i+4] == NON) &&
                        j-1>=0 && i-1>=0 && j+4<=14 && i+4<=14){// <B> (N) B B (N)
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if((p_map[j+1][i+1] == PAN || p_map[j+1][i+1] == NON) &&
                        p_map[j+2][i+2] == WHITE &&
                        (p_map[j+3][i+3] == PAN || p_map[j+3][i+3] == NON) &&
                        p_map[j+4][i+4] == WHITE &&
                        j+4<=14 && i+4<=14){// <B> (N) B (N) B
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                //2번째
                // N  B <B> B N
                // B <B> N  B N
                if((p_map[j-2][i-2] == PAN || p_map[j-2][i-2] == NON) &&
                        p_map[j-1][i-1] == WHITE &&
                        p_map[j+1][i+1] == WHITE &&
                        (p_map[j+2][i+2] == PAN || p_map[j+2][i+2] == NON) &&
                        j-2 >=0 && j+2 <= 14 && i-2 >=0 && i+2 <= 14){// N  B <B> B N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if((p_map[j-2][i-2] == PAN || p_map[j-2][i-2] == NON) &&
                        p_map[j-1][i-1] == WHITE &&
                        (p_map[j+1][i+1] == PAN || p_map[j+1][i+1] == NON) &&
                        p_map[j+2][i+2] == WHITE &&
                        (p_map[j+3][i+3] == PAN || p_map[j+3][i+3] == NON) &&
                        j-2 >=0 && j+3 <= 14 && i-2 >=0 && i+3 <= 14){  // B <B> N  B N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                //3번째
                // B N <B> B N
                // B N <B> N B
                // N B B <B> N
                if((p_map[j-3][i-3] == PAN || p_map[j-3][i-3] == NON) &&
                        p_map[j-2][i-2] == WHITE &&
                        (p_map[j-1][i-1] == PAN || p_map[j-1][i-1] == NON) &&
                        p_map[j+1][i+1] == WHITE &&
                        (p_map[j+2][i+2] == PAN || p_map[j+2][i+2] == NON) &&
                        j-3 >=0 && j+2 <=14 && i-3 >=0 && i+2 <=14){// B N <B> B N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if(p_map[j-2][i-2] == WHITE &&
                        (p_map[j-1][i-1] == PAN || p_map[j-1][i-1] == NON) &&
                        (p_map[j+1][i+1] == PAN || p_map[j+1][i+1] == NON) &&
                        p_map[j+2][i+2] == WHITE &&
                        j-2 >=0 && j+2 <=14 && i-2 >=0 && i+2 <=14){// B N <B> N B
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if((p_map[j-3][i-3] == PAN || p_map[j-3][i-3] == NON) &&
                        p_map[j-2][i-2] == WHITE &&
                        p_map[j-1][i-1] == WHITE &&
                        (p_map[j+1][i+1] == PAN || p_map[j+1][i+1] == NON) &&
                        j-3 >=0 && j+1 <=14 && i-3 >=0 && i+1 <=14){// N B B <B> N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                //4번째
                // B B N <B> N
                // B N B <B> N
                if((p_map[j-4][i-4] == PAN || p_map[j-4][i-4] == NON) &&
                        p_map[j-3][i-3] == WHITE &&
                        p_map[j-2][i-2] == WHITE &&
                        (p_map[j-1][i-1] == PAN || p_map[j-1][i-1] == NON) &&
                        (p_map[j+1][i+1] == PAN || p_map[j+1][i+1] == NON) &&
                        j-4>=0 && j+1<=14 && i-4>=0 && i+1<=14){// B B N <B> N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if((p_map[j-4][i-4] == PAN || p_map[j-4][i-4] == NON) &&
                        p_map[j-3][i-3] == WHITE &&
                        (p_map[j-2][i-2] == PAN || p_map[j-2][i-2] == NON) &&
                        p_map[j-1][i-1] == WHITE &&
                        (p_map[j+1][i+1] == PAN || p_map[j+1][i+1] == NON) &&
                        j-4>=0 && j+1<=14 && i-4>=0 && i+1<=14){// B N B <B> N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }

                //5번째
                // B N B N <B>
                if(p_map[j-4][i-4] == WHITE &&
                        (p_map[j-3][i-3] == PAN || p_map[j-3][i-3] == NON) &&
                        p_map[j-2][i-2] == WHITE &&
                        (p_map[j-1][i-1] == PAN || p_map[j-1][i-1] == NON) &&
                        j-4>=0 && i-4>=0){
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                //Dia 2 = "/" ----------------
                // 1번째
                // (N) <B> B B (N)
                // <B> B (N) B (N)
                // <B> (N) B B (N)
                // <B> (N) B (N) B
                if((p_map[j+1][i-1] == PAN || p_map[j+1][i-1] == NON) &&
                        p_map[j-1][i+1] == WHITE &&
                        p_map[j-2][i+2] == WHITE &&
                        (p_map[j-3][i+3] == PAN || p_map[j-3][i+3] == NON) &&
                        j-3>=0 && j+1<=14 && i-1>=0 && i+3<=14){// (N) <B> B B (N)
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if((p_map[j+1][i-1] == PAN || p_map[j+1][i-1] == NON) &&
                        p_map[j-1][i+1] == WHITE &&
                        (p_map[j-2][i+2] == PAN || p_map[j-2][i+2] == NON)&&
                        p_map[j-3][i+3] == WHITE &&
                        (p_map[j-4][i+4] == PAN || p_map[j-4][i+4] == NON)&&
                        j+1 <= 14 && i-1 >=0 && j-4>=0 && i+4<=14){// <B> B (N) B (N)
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if((p_map[j+1][i-1] == PAN || p_map[j+1][i-1] == NON) &&
                        (p_map[j-1][i+1] == PAN || p_map[j-1][i+1] == NON) &&
                        p_map[j-2][i+2] == WHITE &&
                        p_map[j-3][i+3] == WHITE &&
                        (p_map[j-4][i+4] == PAN || p_map[j-4][i+4] == NON) &&
                        j+1<=14 && i-1 >=0 && j-4>=0 && i+4<=14){// <B> (N) B B (N)
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if((p_map[j-1][i+1] == PAN || p_map[j-1][i+1] == NON) &&
                        p_map[j-2][i+2] == WHITE &&
                        (p_map[j-3][i+3] == PAN || p_map[j-3][i+3] == NON) &&
                        p_map[j-4][i+4] == WHITE &&
                        j-4>=0 && i+4<=14){// <B> (N) B (N) B
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                //2번째
                // N  B <B> B N
                // B <B> N  B N
                if((p_map[j+2][i-2] == PAN || p_map[j+2][i-2] == NON) &&
                        p_map[j+1][i-1] == WHITE &&
                        p_map[j-1][i+1] == WHITE &&
                        (p_map[j-2][i+2] == PAN || p_map[j-2][i+2] == NON) &&
                        j-2 >=0 && j+2 <= 14 && i-2 >=0 && i+2 <= 14){// N  B <B> B N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if((p_map[j+2][i-2] == PAN || p_map[j+2][i-2] == NON) &&
                        p_map[j+1][i-1] == WHITE &&
                        (p_map[j-1][i+1] == PAN || p_map[j-1][i+1] == NON) &&
                        p_map[j-2][i+2] == WHITE &&
                        (p_map[j-3][i+3] == PAN || p_map[j-3][i+3] == NON) &&
                        j-3 >=0 && j+2 <= 14 && i-2 >=0 && i+3 <= 14){  // B <B> N  B N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                //3번째
                // B N <B> B N
                // B N <B> N B
                // N B B <B> N
                if((p_map[j+3][i-3] == PAN || p_map[j+3][i-3] == NON) &&
                        p_map[j+2][i-2] == WHITE &&
                        (p_map[j+1][i-1] == PAN || p_map[j+1][i-1] == NON) &&
                        p_map[j-1][i+1] == WHITE &&
                        (p_map[j-2][i+2] == PAN || p_map[j-2][i+2] == NON) &&
                        j-2 >=0 && j+3 <=14 && i-3 >=0 && i+2 <=14){// B N <B> B N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if(p_map[j+2][i-2] == WHITE &&
                        (p_map[j+1][i-1] == PAN || p_map[j+1][i-1] == NON) &&
                        (p_map[j-1][i+1] == PAN || p_map[j-1][i+1] == NON) &&
                        p_map[j-2][i+2] == WHITE &&
                        j-2 >=0 && j+2 <=14 && i-2 >=0 && i+2 <=14){// B N <B> N B
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if((p_map[j+3][i-3] == PAN || p_map[j+3][i-3] == NON) &&
                        p_map[j+2][i-2] == WHITE &&
                        p_map[j+1][i-1] == WHITE &&
                        (p_map[j-1][i+1] == PAN || p_map[j-1][i+1] == NON) &&
                        j-1 >=0 && j+3 <=14 && i-3 >=0 && i+1 <=14){// N B B <B> N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                //4번째
                // B B N <B> N
                // B N B <B> N
                if((p_map[j+4][i-4] == PAN || p_map[j+4][i-4] == NON) &&
                        p_map[j+3][i-3] == WHITE &&
                        p_map[j+2][i-2] == WHITE &&
                        (p_map[j+1][i-1] == PAN  || p_map[j+1][i-1] == NON) &&
                        (p_map[j-1][i+1] == PAN || p_map[j-1][i+1] == NON) &&
                        j-1>=0 && j+4<=14 && i-4>=0 && i+1<=14){// B B N <B> N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
                if((p_map[j+4][i-4] == PAN || p_map[j+4][i-4] == NON) &&
                        p_map[j+3][i-3] == WHITE &&
                        (p_map[j+2][i-2] == PAN || p_map[j+2][i-2] == NON) &&
                        p_map[j+1][i-1] == WHITE &&
                        (p_map[j-1][i+1] == PAN || p_map[j-1][i+1] == NON) &&
                        j-1>=0 && j+4<=14 && i-4>=0 && i+1<=14){// B N B <B> N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }

                //5번째
                // B N B N <B>
                if(p_map[j+4][i-4] == WHITE &&
                        (p_map[j+3][i-3] == PAN || p_map[j+3][i-3] == NON) &&
                        p_map[j+2][i-2] == WHITE &&
                        (p_map[j+1][i-1] == PAN || p_map[j+1][i-1] == NON) &&
                        j+4<=14 && i-4>=0){
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    if(buf_p<10){
                        buf_xy[buf_p][0]=j;
                        buf_xy[buf_p][1]=i;
                        buf_p++;
                        find_num++;
                    }
                }
            }
        }
    }


    printf("\n **** ENd W2******");
    return find_num;
}

int Game::findB1(std::array<std::array<int,15>,15>& p_map, std::array<std::array<int, 2>, 10> &buf_xy,std::array<std::array<int,15>,15>& bit_map, int buf_size)
{
     printf("\n **** ENd B1******");
    for(int j=1;j<14;j++){
        for(int i=1;i<14;i++){
            int pan_num=0;
            if(p_map[j][i] == BLACK){
                for(int k=j-1;k<=j+1;k++){
                    for(int t=i-1;t<=i+1;t++){
                        if(p_map[k][t] == PAN){
                            bit_map[k][t]++;
                            pan_num++;
                        }
                    }
                }
                if(pan_num >=5){
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                }
            }
        }
    }
    printf("\nBlakc bit map\n");
    for(int j=0;j<15;j++){
        for(int i=0;i<15;i++){
            printf("%d ",bit_map[j][i]);
        }
        printf("\n");
    }
    printf("\nBlakc bit map end \n");
     printf("\n **** ENd B1******");

}

int Game::findW1(std::array<std::array<int,15>,15>& p_map, std::array<std::array<int, 2>, 10> &buf_xy,std::array<std::array<int,15>,15>& bit_map, int buf_size)
{
    printf("\n **** ENd B1******");
   for(int j=1;j<14;j++){
       for(int i=1;i<14;i++){
           int pan_num=0;
           if(p_map[j][i] == WHITE){
               for(int k=j-1;k<=j+1;k++){
                   for(int t=i-1;t<=i+1;t++){
                       if(p_map[k][t] == PAN){
                           bit_map[k][t]++;
                           pan_num++;
                       }
                   }
               }
               if(pan_num >=5){
                   printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
               }
           }
       }
   }
   printf("\White bit map\n");
   for(int j=0;j<15;j++){
       for(int i=0;i<15;i++){
           printf("%d ",bit_map[j][i]);
       }
       printf("\n");
   }
   printf("\White bit map end \n");
   printf("\n **** ENd B1******");
}

void Game::testpair(std::array<std::array<int, 2>, 10> &buf_xy)
{
    printf("\n --------test array----------\n");
    printf("buf-xy. y = %d\n",buf_xy[0][0]);
    printf("buf-xy. x = %d",buf_xy[0][1]);
    printf("\n");
    printf("buf-xy. y = %d\n",buf_xy[9][0]);
    printf("buf-xy. x = %d",buf_xy[9][1]);
    printf("\n-----------test end -----------\n");
}

int Game::findW4(std::array<std::array<int,15>,15>& p_map, std::array<std::array<int, 2>, 10> &buf_xy, int buf_size)
{
    printf("\n **** find W4******");
    int p = 0;
    int b = 0;
    int buf_p = 10 - buf_size;
    int find_num = 0;

    for(int j = 0; j < 15; j++){
        for(int i =0; i < 15; i++){
            if( p_map[j][i] == NON ||p_map[j][i] == PAN){//White - PAN, NON
                if(i+4 <= 14){ // 가로 - N B B B B
                    if(p_map[j][i+1] == WHITE && p_map[j][i+2] == WHITE && p_map[j][i+3] == WHITE && p_map[j][i+4] == WHITE){
                        if( p_map[j][i-1]  != WHITE && i-1>=0) // 좌측 검사
                        {
                            printf("\n 1-1 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                        else if( i == 0) //
                        {   //push(j,i);
                            printf("\n 1-2 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if(i-1 >= 0 && i+3 <=14){// 가로 - B N B B B
                    if(p_map[j][i-1] == WHITE && p_map[j][i+1] == WHITE && p_map[j][i+2] == WHITE && p_map[j][i+3] == WHITE){
                        if( p_map[j][i-2] != WHITE && p_map[j][i+4] != WHITE && (i-2 >=0 && i+4 <= 14) ){//양쪽 모두 체크 - 중앙에 있음
                            printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j][i-2] != WHITE && i+3 == 14){//좌측 체크 (우측은 이미 끝에 도달)
                            printf("\n 1-4 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j][i+4] != WHITE && i -1 == 0 ){//우측 체크
                            printf("\n 1-5 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if(i-2 >=0 && i+2 <=14){// 가로 - B  B N B B
                    if(p_map[j][i-2] == WHITE && p_map[j][i-1] == WHITE && p_map[j][i+1] == WHITE && p_map[j][i+2] == WHITE ){
                        if( p_map[j][i-3] != WHITE && p_map[j][i+3] != WHITE && i+3 <= 14 && i-3 >= 0){
                            printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j][i+3] != WHITE && i - 2 == 0){//좌측에 붙어있음 -> 우측만 검사
                            printf("\n 1-7 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j][i-3] != WHITE && i + 2 == 14){//우측에 붙어 있음 -> 좌측만 검사
                            printf("\n 1-8 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if( i-3 >=0 && i+1 <= 14){// 가로 - B B  B N B
                    if(p_map[j][i-3] == WHITE && p_map[j][i-2] == WHITE && p_map[j][i-1] == WHITE && p_map[j][i+1] == WHITE){
                        if( p_map[j][i+2] != WHITE && p_map[j][i-4] != WHITE && i+2 <= 14 && i-4 >= 0){
                            printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if ( p_map[j][i+2] !=WHITE && i -3 == 0){//좌측에 붙음 -> 우측만 검사
                            printf("\n 1-10 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j][i-4] != WHITE && i+1 == 14){//우측에 붙음 -> 좌측만 검사
                            printf("\n 1-11 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if( i-4 >= 0){// 가로 - B B B B N
                    if(p_map[j][i-4] == WHITE && p_map[j][i-3] == WHITE && p_map[j][i-2] == WHITE && p_map[j][i-1] == WHITE){
                        if(i == 14){//이미 끝에 도달 - 검사할것 없음(원래는 우측 검사)
                            printf("\n 1-12 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j][i+1] != WHITE && i != 14){//우측 검사
                            printf("\n 1-13 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                //// - 세로
                if(j+4 <= 14){ // 세로 - N B B B B
                    if(p_map[j+1][i] == WHITE && p_map[j+2][i] == WHITE && p_map[j+3][i] == WHITE && p_map[j+4][i] == WHITE){
                        if( p_map[j-1][i]  != WHITE && j-1>=0)//상단 검사 할거리 있을 경우
                        {
                            printf("\n 2-1 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                        else if( j== 0)//상단에 붙어있음 - 검사 할거리 없음
                        {   //push(j,i);
                            printf("\n 2-2 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if(j-1 >= 0 && j+3 <=14){// 세로 - B N B B B
                    if(p_map[j-1][i] == WHITE && p_map[j+1][i] == WHITE && p_map[j+2][i] == WHITE && p_map[j+3][i] == WHITE){
                        if( p_map[j-2][i] != WHITE && p_map[j+4][i] != WHITE && (j-2 >=0 && j+4 <= 14) ){//양쪽 모두 체크 - 중앙에 있음
                            printf("\n 2-3 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j-2][i] != WHITE && j+3 == 14){//상단 체크 (하단은 이미 끝에 도달)
                            printf("\n 2-4 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j+4][i] != WHITE && j -1 == 0 ){//하단 체크 - 상단은 이미 상단에 도달
                            printf("\n 2-5 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if(j-2 >=0 && j+2 <=14){// 세로 - B  B N B B
                    if(p_map[j-2][i] == WHITE && p_map[j-1][i] == WHITE && p_map[j+1][i] == WHITE && p_map[j+2][i] == WHITE ){
                        if( p_map[j-3][i] != WHITE && p_map[j+3][i] != WHITE && j+3 <= 14 && j-3 >= 0){
                            printf("\n 2-6 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j+3][i] != WHITE && j - 2 == 0){//상단에 붙어 있을 경우 -> 하단만 검사
                            printf("\n 2-7 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j-3][i] != WHITE && j + 2 == 14){//하단에 붙어 있을경우 -> 상단만 검사
                            printf("\n 2-8 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if( j-3 >=0 && j+1 <= 14){// 세로 - B B  B N B
                    if(p_map[j-3][i] == WHITE && p_map[j-2][i] == WHITE && p_map[j-1][i] == WHITE && p_map[j+1][i] == WHITE){
                        if( p_map[j+2][i] != WHITE && p_map[j-4][i] != WHITE && j+2 <= 14 && j-4 >= 0){
                            printf("\n 2-9 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if ( p_map[j+2][i] !=WHITE && j -3 == 0){//상단에 붙음 - 하단만 검사
                            printf("\n 2-10 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j-4][i] != WHITE && j+1 == 14){//하단에 붙음 - 상단만 검사
                            printf("\n 2-11 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if( j-4 >= 0){// 세로 - B B B B N
                    if(p_map[j-4][i] == WHITE && p_map[j-3][i] == WHITE && p_map[j-2][i] == WHITE && p_map[j-1][i] == WHITE){
                        if(j == 14){//이미 끝에 도달 - 굳이 상단 검사할 필요없음 - 5개여서
                            printf("\n 2-12 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j+1][i] != WHITE && j != 14){//하단 검사
                            printf("\n 2-13 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                // Dia 1 - "\"
                if( i+4 <= 14 && j+4 <= 14){ // dia1 - N B B B B
                    if(p_map[j+1][i+1] == WHITE && p_map[j+2][i+2] == WHITE && p_map[j+3][i+3] == WHITE && p_map[j+4][i+4] == WHITE){
                        if( p_map[j-1][i-1] != WHITE && j-1>=0 && i-1>=0)//우측에 있으면 이미 5개임 -> 검사할 필요 없음 - 좌측만 돌 없으면 4
                        {
                            printf("\n 3-1 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                        else if( i == 0 || j== 0)//좌측에 달라 붙어 있을경우 - 검사 필요 없음
                        {   //push(j,i);
                            printf("\n 3-2 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if(i-1 >= 0 && i+3 <=14 && j-1 >= 0 && j+3 <=14){// dia1 - B N B B B
                    if(p_map[j-1][i-1] == WHITE && p_map[j+1][i+1] == WHITE && p_map[j+2][i+2] == WHITE && p_map[j+3][i+3] == WHITE){
                        if( p_map[j-2][i-2] != WHITE && p_map[j+4][i+4] != WHITE && (i-2 >=0 && i+4 <= 14) && (j-2 >=0 && j+4 <= 14) ){//양쪽 모두 체큰 - 중앙에 있음
                            printf("\n 3-3 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j-2][i-2] != WHITE && (i+3 == 14 || j+3 == 14)){//좌측 체크 (우측은 이미 끝에 도달)
                            printf("\n 3-4 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j+4][i+4] != WHITE && (i -1 == 0  || j -1 == 0) ){//우측 체크
                            printf("\n 3-5 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if(i-2 >=0 && i+2 <=14 && j-2 >=0 && j+2 <=14){// dia1 - B  B N B B
                    if(p_map[j-2][i-2] == WHITE && p_map[j-1][i-1] == WHITE && p_map[j+1][i+1] == WHITE && p_map[j+2][i+2] == WHITE ){
                        if( p_map[j-3][i-3] != WHITE && p_map[j+3][i+3] != WHITE && i+3 <= 14 && i-3 >= 0 && j+3 <= 14 && j-3 >= 0){
                            printf("\n 3-6 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j+3][i+3] != WHITE && (i - 2 == 0 || j - 2 == 0)){
                            printf("\n 3-7 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j-3][i-3] != WHITE && (i + 2 == 14 || j + 2 == 14)){
                            printf("\n 3-8 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if( i-3 >=0 && i+1 <= 14 && j-3 >=0 && j+1 <= 14){// dia1 - B B  B N B
                    if(p_map[j-3][i-3] == WHITE && p_map[j-2][i-2] == WHITE && p_map[j-1][i-1] == WHITE && p_map[j+1][i+1] == WHITE){
                        if( p_map[j+2][i+2] != WHITE && p_map[j-4][i-4] != WHITE && i+2 <= 14 && i-4 >= 0 && j+2 <= 14 && j-4 >= 0){
                            printf("\n 3-9 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if ( p_map[j+2][i+2] !=WHITE && (i -3 == 0 || j -3 == 0)){
                            printf("\n 3-10 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j-4][i-4] != WHITE && (i+1 == 14 || j+1 == 14)){
                            printf("\n 3-11 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if( i-4 >= 0 && j-4 >= 0){// dia1 - B B B B N
                    if(p_map[j-4][i-4] == WHITE && p_map[j-3][i-3] == WHITE && p_map[j-2][i-2] == WHITE && p_map[j-1][i-1] == WHITE){
                        if( i == 14 || j == 14){//이미 끝에 도달 -- 좌측 검사할 필요 없음(5개니까) - 우측 검사할 칸 없음
                            printf("\n 3-12 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j+1][i+1] != WHITE && i != 14 && j != 14){
                            printf("\n 3-13 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                // DIa 2 - /
                if( j-4 >=0 && i+4 <= 14){ // dia2 - N B B B B
                    if(p_map[j-1][i+1] == WHITE && p_map[j-2][i+2] == WHITE && p_map[j-3][i+3] == WHITE && p_map[j-4][i+4] == WHITE){
                        if( p_map[j+1][i-1]  != WHITE && j+1<=14 && i-1>=0) // 좌측 검사 - 좌측이 있을 경우
                        {
                            printf("\n 4-1 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                        else if( j == 14 || i == 0)//ㄴ 라인
                        {   //push(j,i);
                            printf("\n 4-2 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if( j-3 >= 0 && j+1 <=14 && i-1 >= 0 && i+3 <=14){// dia2 - B N B B B
                    if(p_map[j+1][i-1] == WHITE && p_map[j-1][i+1] == WHITE && p_map[j-2][i+2] == WHITE && p_map[j-3][i+3] == WHITE){
                        if( p_map[j+2][i-2] != WHITE && p_map[j-4][i+4] != WHITE &&
                                (i-2 >=0 && i+4 <= 14) && (j-4 >=0 && j+2 <= 14) ){//양쪽 모두 체큰 - 중앙에 있음
                            printf("\n 4-3 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j+2][i-2] != WHITE  && (i+3 == 14 || j-3 == 0)){//좌측 체크 (우측은 이미 끝에 도달) ㄱ 형태
                            printf("\n 4-4 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j-4][i+4] != WHITE && (j + 1 == 14 || i -1 == 0 )){//우측 체크 ㄴ 형태
                            printf("\n 4-5 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if(j-2 >=0 && j+2 <=14 && i-2 >=0 && i+2 <=14){// dia2 - B  B N B B
                    if(p_map[j+2][i-2] == WHITE && p_map[j+1][i-1] == WHITE && p_map[j-1][i+1] == WHITE && p_map[j-2][i+2] == WHITE ){
                        if( p_map[j+3][i-3] != WHITE && p_map[j-3][i+3] != WHITE &&
                                (i-3 >=0 && i+3 <=14 ) && (j-3 >=0 && j+3 <= 14)){
                            printf("\n 4-6find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j+3][i-3] != WHITE && ( j == 2 || i == 12)){//하단 검사
                            printf("\n 4-7 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j-3][i+3] != WHITE && ( j == 12 || i == 2)){//상단 검사
                            printf("\n 4-8 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if( j+3 <= 14 && i-3 >=0 && j-1 >=0 && i+1 <= 14){// dia2 - B B  B N B
                    if(p_map[j+3][i-3] == WHITE && p_map[j+2][i-2] == WHITE && p_map[j+1][i-1] == WHITE && p_map[j-1][i+1] == WHITE){
                        if( p_map[j+4][i-4] != WHITE && p_map[j-2][i+2] != WHITE &&
                                (j+4 <= 14 && i-4>=0) && (j-2 >=0 && i+2 <= 14)){// 2<=j<= 10   4<=i<=12
                            printf("\n 4-9 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if ( p_map[j+4][i-4] !=WHITE && (j == 1 || i == 13)){
                            printf("\n 4-10 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j-2][i+2] != WHITE && (j == 11 || i == 3)){
                            printf("\n 4-11 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
                if( j+4 <= 14 && i-4 >= 0){// dia2 - B B B B N
                    if(p_map[j+4][i-4] == WHITE && p_map[j+3][i-3] == WHITE && p_map[j+2][i-2] == WHITE && p_map[j+1][i-1] == WHITE){
                        if(p_map[j-1][i+1] !=WHITE && (j-1>=0 && i+1<=14)){//우측 검사 - 우측이 있을 경우
                            printf("\n 4-12 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( j == 0 || i == 14){// 검사 필요 없음
                            printf("\n 4-13 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                    }
                }
            }
        }
    }
     printf("\n **** ENd W4******");
     return find_num;
}

bool Game::checkNon(std::array<std::array<int, 15>, 15> i_map)
{

}

int Game::miniMax(std::array<std::array<int, 15>, 15> &p_map, int depth, int al, int be, bool turn)
{
    if(depth == 3){//cal board
        int scor = calScore(p_map,turn);
        /*
        printf("\n ********** Last map Start ************\n");
        for(int j=0;j < 15;j++){
            for(int i =0;i < 15;i++){
                printf("%d ",p_map[j][i]);
            }
            printf("\n");
        }
        printf("\n ********** Last map End************\n");
        */
        return scor;
    }
    std::array<std::array<int, 15>, 15> my_b;
    std::array<std::array<int,2>,10> buf_xy;

    uint8_t x;
    uint8_t y;
    int xy_size = 0 ;
// copy board
    printf("\n ------Test---------\n");
    for(int j=0; j < 15; j++){//copy Board
        for(int i=0; i < 15; i++){
            my_b[j][i] = p_map[j][i];
           // my_b[j][i] = 1;
           // printf("%d ",my_b[j][i]);
        }
        printf("\n");
    }
    printf("\n ------END---------\n");
    fflush(stdout);
//

// find spot

    if(turn == BLACK){
        xy_size = findSpotB(my_b,buf_xy,10);
        printf("\n ----------- minimax BLACK test size = %d---------\n",xy_size);
        for(int i=0; i < xy_size;i++){
            printf(" %d.y = %d\n", i,buf_xy[i][0]);
            printf(" %d.x = %d\n", i, buf_xy[i][1]);
        }
        printf("\n ----------- minimax BLACK END ----------\n");
    }
    else if(turn == WHITE){
        xy_size = findSpotW(my_b,buf_xy,10);
        printf("\n ----------- minimax WHITE test size = %d---------\n",xy_size);
        for(int i=0; i < xy_size;i++){
            printf(" %d.y = %d\n", i,buf_xy[i][0]);
            printf(" %d.x = %d\n", i, buf_xy[i][1]);
        }
        printf("\n ----------- minimax WHITEtest----------\n");
    }


//

//set_stone
    int temp =0;
    int backup =-1;
    int t_y =-1;
    int t_x =-1;
    //y = buf_xy[t].
    for(int t = 0; t < xy_size; t++){
        //my_b[buf_xy[t].first][buf_xy[t].second] = turn; // set Stone
        if( depth % 2 == 0){//pick max
            int max_sc = -9999999 ;
            for(int i=0; i < xy_size; i++){
                backup = my_b[buf_xy[i][0]][buf_xy[i][1]];
                my_b[buf_xy[i][0]][buf_xy[i][1]] = turn;
                temp = miniMax(my_b,depth + 1,1,1,!turn);
                if( (temp = miniMax(my_b,depth+1,1,1,!turn)) > max_sc){//find bigger
                    max_sc = temp;
                    t_y = buf_xy[i][0];
                    t_x = buf_xy[i][1];
                }
                my_b[buf_xy[i][0]][buf_xy[i][1]] = backup;
            }
            if(depth !=0){
                return max_sc;
            }else {
                putStone(t_y,t_x);
                return true;
            }
        }else{//pick min
            int min_sc = 999999999;
            for(int i=0; i<xy_size; i++){
                backup = my_b[buf_xy[i][0]][buf_xy[i][1]];
                my_b[buf_xy[i][0]][buf_xy[i][1]] = turn;
                temp = miniMax(my_b,depth + 1,1,1,!turn);
                if( (temp = miniMax(my_b,depth+1,1,1,!turn)) < min_sc){//find mini
                    min_sc = temp;
                    t_y = buf_xy[i][0];
                    t_x = buf_xy[i][1];
                }
                my_b[buf_xy[i][0]][buf_xy[i][1]] = backup;

            }
            if(depth !=0)
                return min_sc;
            else{
                putStone(t_y,t_x);
                return true;
            }
        }
    }
}
