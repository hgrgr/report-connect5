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
                            ui->turn->setText(" ??? ");
                        else if(turnToggle == WHITE)
                            ui->turn->setText(" ??? ");
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
                            ui->turn->setText(" ??? ");
                        else if(turnToggle == WHITE)
                            ui->turn->setText(" ??? ");
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
                                ui->turn->setText(" ??? ");
                            else if(turnToggle == WHITE)
                                ui->turn->setText(" ??? ");
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
                                ui->turn->setText(" ??? ");
                            else if(turnToggle == WHITE)
                                ui->turn->setText(" ??? ");
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
                                ui->turn->setText(" ??? ");
                            else if(turnToggle == WHITE)
                                ui->turn->setText(" ??? ");
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
                                ui->turn->setText(" ??? ");
                            else if(turnToggle == WHITE)
                                ui->turn->setText(" ??? ");
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
                            ui->turn->setText(" ??? ");
                        else if(turnToggle == WHITE)
                            ui->turn->setText(" ??? ");
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
                            ui->turn->setText(" ??? ");
                        else if(turnToggle == WHITE)
                            ui->turn->setText(" ??? ");
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
    turnToggle = BLACK;//update ????????? ?????? toggle?????????. - ????????? ?????? Black
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
    for(int i=1;i<14;i++)//15 - 2??? ??????
    {
        if(i == 1 || i == 13){//?????????
            printf("\nTest 0");
            fflush(stdout);
            if((*p_map)[1][1] == NON || (*p_map)[1][1] == PAN ){//????????? ??????
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
        }else if(i == 2 || i == 12){//??????????????? ????????? ????????? ?????? ??????
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
        }else{//????????? ?????? - ?????? ????????? ?????? ?????? ??????
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
    for(int i=2;i<13;i++){//15 - 4??? ??????
        if(i == 2 || i == 12){//?????????
            if((*p_map)[2][2] == 2){

            }
            if((*p_map)[2][12] == 2){

            }
            if((*p_map)[12][2] == 2){

            }
            if((*p_map)[12][12] == 2){

            }
        }else{//???????????? ??????
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
    for(int i=3; i < 12; i++){//15 - 6??? ?????? -- ?????? ?????? ??????
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
                    if( i_map[j+5][i+5] !=color && i_map[j-1][i-1] != color &&//?????? ?????? ??????
                            (j+5 <= 14 && j-1 >= 0 ) && (i+5 <= 14 && i-1>=0 ))
                        {printf("\n con5 1 "); return 1;}
                    else if( (i == 0 && j == 10) ||(i == 10 && j == 0))
                        {printf("\n con5 4 "); return 1;}
                    else if( i_map[j+5][i+5] != color && (i==0 || j == 0) )//?????? ??????
                        {printf("\n con5 2 "); return 1;}
                    else if( i_map[j-1][i-1] !=color && (i == 10 || j == 10))//?????? ??????
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
                    else if( i_map[j-5][i+5] != color && (i == 0 || j == 14 ) )//?????? +5???
                        {printf("\n con5 2 "); return 1;}
                    else if(i_map[j+1][i-1] != color && (j == 4 || i == 10) )//?????? -1 ???
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
    std::array<std::array<int, 15>, 15> bit_map;

    for(int j=0;j<15;j++){//set bit-map 0;
        for(int i=0;i<15;i++){
            bit_map[j][i] =0;
        }
    }
    int sc = 0;
    sc = rand() % 10;
    int temp=0;
    if(check5(p_map,!turn) == 1)//5??? ????????? ?????? (?????? ?????? ??? ???????????? ?????? ????????????)
        return 99999999;//0??? 5???
    if((!turn) == BLACK){//?????? ?????? ??????????????? (?????? 5?????? ?????? ?????? ??????)
        //?????? ?????? ????????? ?????? ????????? b4?????? w4????????? ???????????????
        if(findW4(p_map,buf_xy,1) >0 ){//white 4 ??? ?????????
            return -900000;//????????? - ?????? ??? ??????
        }
        if(findB44(p_map,bit_map) > 0 ){//find Black 44
            sc += 2000*temp;// 0??? 4???
        }
        if((temp = findFW3(p_map,buf_xy,10)) > 0)//?????? white 3 ?????????
        {
            sc -= 1000*temp;// 0??? 3???
        }
        if((temp = findFB3(p_map,buf_xy,10)) >0 )//?????? black ????????? -> ???????????? ????????????
        {
            sc += 310*temp;
         }
        if((temp = findHW3(p_map,buf_xy,10) > 0)){// ?????? white 3 ?????????
            sc -= 150*temp;
        }
        if((temp = findHB3(p_map,buf_xy,10)) >0){// ?????? black 3 ?????????
           sc += 70*temp;
        }
        if((temp = findW2(p_map,buf_xy,10))>0){//?????? white2 ?????????
            sc -= 50*temp;
        }
        return sc;
    }else if((!turn) == WHITE){//?????? ?????? ???????????? ?????? (?????? 5?????? ?????? ?????? ??????)
        //?????? ?????? ????????? ?????? ????????? b4?????? w4????????? ???????????????
        if(findB4(p_map,buf_xy,1) >0 ){//Black 4 ??? ?????????
            return -900000;//????????? - ?????? ??? ??????
        }
        if((temp = findW4(p_map,buf_xy,10)) > 0 ){//black4 ?????? white 4??? ????????? ??????
            sc += 2000*temp;// 0??? 4???
        }
        if((temp = findFB3(p_map,buf_xy,10)) > 0)//?????? Black 3 ?????????
        {
            sc -= 1000*temp;// 0??? 3???
        }
        if((temp = findFW3(p_map,buf_xy,10)) >0 )//?????? White ????????? -> ????????? ????????????
        {
            sc += 310*temp;
         }
        if((temp = findHB3(p_map,buf_xy,10) > 0)){// ?????? BLack 3 ?????????
            sc -= 150*temp;
        }
        if((temp = findHW3(p_map,buf_xy,10)) >0){// ?????? White 3 ?????????
           sc += 70*temp;
        }
        if((temp = findB2(p_map,buf_xy,10))>0){//?????? Black2 ?????????
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
    m_size += findW4(p_map, buf_xy, buf_size);//????????? ????????????

    if(m_size < buf_size){
        m_size += findB4(p_map, buf_xy, buf_size - m_size);//????????? ????????????
    }
    if(m_size < buf_size){
        m_size += findFW3(p_map, buf_xy, buf_size - m_size);//????????? ??? ?????? ?????? // 44 - 43 ?????? ??? ??????????????? ????????????
    }
    if(m_size < buf_size){
        m_size += findFB3(p_map, buf_xy, buf_size - m_size);//????????? ??? ?????? ??????//43 ????????? ?????? ??????
    }
    if(m_size < buf_size){
        m_size += findHW3(p_map, buf_xy, buf_size - m_size);//????????? ??? ?????? ?????? // ?????? 43, 44 ??????????????? ????????????
    }
    if(m_size < buf_size){
        m_size += findHB3(p_map, buf_xy, buf_size - m_size);//??? ?????? ?????? - ?????? 43, ?????? 44 ????????? ????????????
    }
    if(m_size < buf_size){
        m_size += findW2(p_map, buf_xy, buf_size - m_size);//??? ?????? ?????? - 33 ??????????????? ????????????
    }
    if(m_size < buf_size){
        m_size += findB2(p_map, buf_xy, buf_size - m_size);//??? ?????? ?????? ?????? ?????? 33 ????????? ?????? ??????
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
            bit_map[t_y][t_x] = 0;//????????????.
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
            bit_map[t_y][t_x] = 0;//????????????.
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
    std::array<std::array<int,2>,15> pairoo44;
    std::array<std::array<int,2>,15> pairco44;
    std::array<std::array<int,2>,15> paircc44;
    std::array<std::array<int,2>,15> pairoo43;
    std::array<std::array<int,2>,15> pairco43;
    std::array<std::array<int,2>,15> pairoo33;
    std::array<std::array<int,2>,15> pair4;
    std::array<std::array<int,2>,15> pair3;
    int numoo44 = 0;
    int numco44 = 0;
    int numcc44 = 0;
    int numoo43 = 0;
    int numco43 = 0;
    int numoo33 = 0;
    int num4 = 0;
    int num3 = 0;
    for(int i=0;i<15;i++){//init bit_map;
        for(int j=0; j <15;j++){
            bit_map[i][j]=0;
        }
    }
    int m_size = 0;
    m_size += findB4(p_map, buf_xy, buf_size);//buf_size = 10 - ????????? ????????????
    printf("m_size = %d \n",m_size);
    if(m_size < buf_size){
        m_size += findW4(p_map, buf_xy, buf_size - m_size);//????????? ????????????
        printf("m_size = %d \n",m_size);
    }
    if(m_size < buf_size){
        m_size += wfindFB3(p_map, bit_map);//?????? 44,34 ?????? ????????? ?????????
        m_size += wfindHB3(p_map, bit_map);
        m_size += wfindB2(p_map, bit_map);
        for(int j=0;j<15;j++){
            for(int i=0;i<15;i++){
                if(bit_map[j][i] >= 200){//find open open 44
                    pairoo44[numoo44][0] = j;
                    pairoo44[numoo44][1] = i;
                    numoo44++;
                }else if(bit_map[j][i] >= 160){//find open close 44
                    pairco44[numco44][0] = j;
                    pairco44[numco44][1] = i;
                    numco44++;
                }
                else if(bit_map[j][i] >= 120){//find 1 close close 44
                    paircc44[numcc44][0] = j;
                    paircc44[numcc44][1] = i;
                    numcc44++;
                }
                else if(bit_map[j][i] >= 105){//find 1 close close 44
                    pairoo43[numoo43][0] = j;
                    pairoo43[numoo43][1] = i;
                    numoo43++;
                }else if(bit_map[j][i] >= 75){//find 1 close close 44
                    pairco43[numco43][0] = j;
                    pairco43[numco43][1] = i;
                    numco43++;
                }
                else if(bit_map[j][i] >= 10){//find 33
                    pairoo33[numoo33][0] = j;
                    pairoo33[numoo33][0] = i;
                    numoo33++;
                }
            }
        }
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
            bit_map[t_y][t_x] = 0;//????????????.
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
            bit_map[t_y][t_x] = 0;//????????????.
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
                if(i+4 <= 14){ // ?????? - N B B B B
                    if(p_map[j][i+1] == BLACK && p_map[j][i+2] == BLACK && p_map[j][i+3] == BLACK && p_map[j][i+4] == BLACK){
                        if( p_map[j][i-1]  != BLACK && i-1>=0) // ?????? ??????
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
                if(i-1 >= 0 && i+3 <=14){// ?????? - B N B B B
                    if(p_map[j][i-1] == BLACK && p_map[j][i+1] == BLACK && p_map[j][i+2] == BLACK && p_map[j][i+3] == BLACK){
                        if( p_map[j][i-2] != BLACK && p_map[j][i+4] != BLACK && (i-2 >=0 && i+4 <= 14) ){//?????? ?????? ?????? - ????????? ??????
                            printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j][i-2] != BLACK && i+3 == 14){//?????? ?????? (????????? ?????? ?????? ??????)
                            printf("\n 1-4 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j][i+4] != BLACK && i -1 == 0 ){//?????? ??????
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
                if(i-2 >=0 && i+2 <=14){// ?????? - B  B N B B
                    if(p_map[j][i-2] == BLACK && p_map[j][i-1] == BLACK && p_map[j][i+1] == BLACK && p_map[j][i+2] == BLACK ){
                        if( p_map[j][i-3] != BLACK && p_map[j][i+3] != BLACK && i+3 <= 14 && i-3 >= 0){
                            printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j][i+3] != BLACK && i - 2 == 0){//????????? ???????????? -> ????????? ??????
                            printf("\n 1-7 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j][i-3] != BLACK && i + 2 == 14){//????????? ?????? ?????? -> ????????? ??????
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
                if( i-3 >=0 && i+1 <= 14){// ?????? - B B  B N B
                    if(p_map[j][i-3] == BLACK && p_map[j][i-2] == BLACK && p_map[j][i-1] == BLACK && p_map[j][i+1] == BLACK){
                        if( p_map[j][i+2] != BLACK && p_map[j][i-4] != BLACK && i+2 <= 14 && i-4 >= 0){
                            printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if ( p_map[j][i+2] !=BLACK && i -3 == 0){//????????? ?????? -> ????????? ??????
                            printf("\n 1-10 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j][i-4] != BLACK && i+1 == 14){//????????? ?????? -> ????????? ??????
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
                if( i-4 >= 0){// ?????? - B B B B N
                    if(p_map[j][i-4] == BLACK && p_map[j][i-3] == BLACK && p_map[j][i-2] == BLACK && p_map[j][i-1] == BLACK){
                        if(i == 14){//?????? ?????? ?????? - ???????????? ??????(????????? ?????? ??????)
                            printf("\n 1-12 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j][i+1] != BLACK && i != 14){//?????? ??????
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
                //// - ??????
                if(j+4 <= 14){ // ?????? - N B B B B
                    if(p_map[j+1][i] == BLACK && p_map[j+2][i] == BLACK && p_map[j+3][i] == BLACK && p_map[j+4][i] == BLACK){
                        if( p_map[j-1][i]  != BLACK && j-1>=0)//?????? ?????? ????????? ?????? ??????
                        {
                            printf("\n 2-1 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                        else if( j== 0)//????????? ???????????? - ?????? ????????? ??????
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
                if(j-1 >= 0 && j+3 <=14){// ?????? - B N B B B
                    if(p_map[j-1][i] == BLACK && p_map[j+1][i] == BLACK && p_map[j+2][i] == BLACK && p_map[j+3][i] == BLACK){
                        if( p_map[j-2][i] != BLACK && p_map[j+4][i] != BLACK && (j-2 >=0 && j+4 <= 14) ){//?????? ?????? ?????? - ????????? ??????
                            printf("\n 2-3 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j-2][i] != BLACK && j+3 == 14){//?????? ?????? (????????? ?????? ?????? ??????)
                            printf("\n 2-4 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j+4][i] != BLACK && j -1 == 0 ){//?????? ?????? - ????????? ?????? ????????? ??????
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
                if(j-2 >=0 && j+2 <=14){// ?????? - B  B N B B
                    if(p_map[j-2][i] == BLACK && p_map[j-1][i] == BLACK && p_map[j+1][i] == BLACK && p_map[j+2][i] == BLACK ){
                        if( p_map[j-3][i] != BLACK && p_map[j+3][i] != BLACK && j+3 <= 14 && j-3 >= 0){
                            printf("\n 2-6 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j+3][i] != BLACK && j - 2 == 0){//????????? ?????? ?????? ?????? -> ????????? ??????
                            printf("\n 2-7 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j-3][i] != BLACK && j + 2 == 14){//????????? ?????? ???????????? -> ????????? ??????
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
                if( j-3 >=0 && j+1 <= 14){// ?????? - B B  B N B
                    if(p_map[j-3][i] == BLACK && p_map[j-2][i] == BLACK && p_map[j-1][i] == BLACK && p_map[j+1][i] == BLACK){
                        if( p_map[j+2][i] != BLACK && p_map[j-4][i] != BLACK && j+2 <= 14 && j-4 >= 0){
                            printf("\n 2-9 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if ( p_map[j+2][i] !=BLACK && j -3 == 0){//????????? ?????? - ????????? ??????
                            printf("\n 2-10 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j-4][i] != BLACK && j+1 == 14){//????????? ?????? - ????????? ??????
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
                if( j-4 >= 0){// ?????? - B B B B N
                    if(p_map[j-4][i] == BLACK && p_map[j-3][i] == BLACK && p_map[j-2][i] == BLACK && p_map[j-1][i] == BLACK){
                        if(j == 14){//?????? ?????? ?????? - ?????? ?????? ????????? ???????????? - 5?????????
                            printf("\n 2-12 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j+1][i] != BLACK && j != 14){//?????? ??????
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
                        if( p_map[j-1][i-1] != BLACK && j-1>=0 && i-1>=0)//????????? ????????? ?????? 5?????? -> ????????? ?????? ?????? - ????????? ??? ????????? 4
                        {
                            printf("\n 3-1 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                        else if( i == 0 || j== 0)//????????? ?????? ?????? ???????????? - ?????? ?????? ??????
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
                        if( p_map[j-2][i-2] != BLACK && p_map[j+4][i+4] != BLACK && (i-2 >=0 && i+4 <= 14) && (j-2 >=0 && j+4 <= 14) ){//?????? ?????? ?????? - ????????? ??????
                            printf("\n 3-3 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j-2][i-2] != BLACK && (i+3 == 14 || j+3 == 14)){//?????? ?????? (????????? ?????? ?????? ??????)
                            printf("\n 3-4 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j+4][i+4] != BLACK && (i -1 == 0  || j -1 == 0) ){//?????? ??????
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
                        if( i == 14 || j == 14){//?????? ?????? ?????? -- ?????? ????????? ?????? ??????(5?????????) - ?????? ????????? ??? ??????
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
                        if( p_map[j+1][i-1]  != BLACK && j+1<=14 && i-1>=0) // ?????? ?????? - ????????? ?????? ??????
                        {
                            printf("\n 4-1 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                        else if( j == 14 || i == 0)//??? ??????
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
                                (i-2 >=0 && i+4 <= 14) && (j-4 >=0 && j+2 <= 14) ){//?????? ?????? ?????? - ????????? ??????
                            printf("\n 4-3 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j+2][i-2] != BLACK  && (i+3 == 14 || j-3 == 0)){//?????? ?????? (????????? ?????? ?????? ??????) ??? ??????
                            printf("\n 4-4 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j-4][i+4] != BLACK && (j + 1 == 14 || i -1 == 0 )){//?????? ?????? ??? ??????
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
                        }else if( p_map[j+3][i-3] != BLACK && ( j == 2 || i == 12)){//?????? ??????
                            printf("\n 4-7 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j-3][i+3] != BLACK && ( j == 12 || i == 2)){//?????? ??????
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
                        if(p_map[j-1][i+1] !=BLACK && (j-1>=0 && i+1<=14)){//?????? ?????? - ????????? ?????? ??????
                            printf("\n 4-12 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( j == 0 || i == 14){// ?????? ?????? ??????
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

int Game::findB44(std::array<std::array<int, 15>, 15> &p_map, std::array<std::array<int, 15>, 15>& bit_map)
{
    printf("\n **** find B44******");
    int p = 0;
    int b = 0;
    int find_num =0;

    for(int j = 0; j < 15; j++){
        for(int i =0; i < 15; i++){
            if(p_map[j][i] == PAN){//only PAN
                if(i+4 <= 14){ // ?????? - N B B B B
                    if(p_map[j][i+1] == BLACK && p_map[j][i+2] == BLACK && p_map[j][i+3] == BLACK && p_map[j][i+4] == BLACK){
                        if( p_map[j][i-1]  != BLACK && i-1>=0) // ?????? ??????
                        {
                            printf("\n 1-1 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }
                        else if( i == 0) //
                        {   //push(j,i);
                            find_num++;
                            bit_map[j][i]++;

                            printf("\n 1-2 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if(i-1 >= 0 && i+3 <=14){// ?????? - B N B B B
                    if(p_map[j][i-1] == BLACK && p_map[j][i+1] == BLACK && p_map[j][i+2] == BLACK && p_map[j][i+3] == BLACK){
                        if( p_map[j][i-2] != BLACK && p_map[j][i+4] != BLACK && (i-2 >=0 && i+4 <= 14) ){//?????? ?????? ?????? - ????????? ??????
                            printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }else if( p_map[j][i-2] != BLACK && i+3 == 14){//?????? ?????? (????????? ?????? ?????? ??????)
                            printf("\n 1-4 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }else if( p_map[j][i+4] != BLACK && i -1 == 0 ){//?????? ??????
                            printf("\n 1-5 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }
                    }
                }
                if(i-2 >=0 && i+2 <=14){// ?????? - B  B N B B
                    if(p_map[j][i-2] == BLACK && p_map[j][i-1] == BLACK && p_map[j][i+1] == BLACK && p_map[j][i+2] == BLACK ){
                        if( p_map[j][i-3] != BLACK && p_map[j][i+3] != BLACK && i+3 <= 14 && i-3 >= 0){
                            printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }else if( p_map[j][i+3] != BLACK && i - 2 == 0){//????????? ???????????? -> ????????? ??????
                            printf("\n 1-7 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }else if( p_map[j][i-3] != BLACK && i + 2 == 14){//????????? ?????? ?????? -> ????????? ??????
                            printf("\n 1-8 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }
                    }
                }
                if( i-3 >=0 && i+1 <= 14){// ?????? - B B  B N B
                    if(p_map[j][i-3] == BLACK && p_map[j][i-2] == BLACK && p_map[j][i-1] == BLACK && p_map[j][i+1] == BLACK){
                        if( p_map[j][i+2] != BLACK && p_map[j][i-4] != BLACK && i+2 <= 14 && i-4 >= 0){
                            printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }else if ( p_map[j][i+2] !=BLACK && i -3 == 0){//????????? ?????? -> ????????? ??????
                            printf("\n 1-10 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }else if( p_map[j][i-4] != BLACK && i+1 == 14){//????????? ?????? -> ????????? ??????
                            printf("\n 1-11 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }
                    }
                }
                if( i-4 >= 0){// ?????? - B B B B N
                    if(p_map[j][i-4] == BLACK && p_map[j][i-3] == BLACK && p_map[j][i-2] == BLACK && p_map[j][i-1] == BLACK){
                        if(i == 14){//?????? ?????? ?????? - ???????????? ??????(????????? ?????? ??????)
                            printf("\n 1-12 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }else if( p_map[j][i+1] != BLACK && i != 14){//?????? ??????
                            printf("\n 1-13 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }
                    }
                }
                //// - ??????
                if(j+4 <= 14){ // ?????? - N B B B B
                    if(p_map[j+1][i] == BLACK && p_map[j+2][i] == BLACK && p_map[j+3][i] == BLACK && p_map[j+4][i] == BLACK){
                        if( p_map[j-1][i]  != BLACK && j-1>=0)//?????? ?????? ????????? ?????? ??????
                        {
                            printf("\n 2-1 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }
                        else if( j== 0)//????????? ???????????? - ?????? ????????? ??????
                        {   //push(j,i);
                            printf("\n 2-2 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }
                    }
                }
                if(j-1 >= 0 && j+3 <=14){// ?????? - B N B B B
                    if(p_map[j-1][i] == BLACK && p_map[j+1][i] == BLACK && p_map[j+2][i] == BLACK && p_map[j+3][i] == BLACK){
                        if( p_map[j-2][i] != BLACK && p_map[j+4][i] != BLACK && (j-2 >=0 && j+4 <= 14) ){//?????? ?????? ?????? - ????????? ??????
                            printf("\n 2-3 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }else if( p_map[j-2][i] != BLACK && j+3 == 14){//?????? ?????? (????????? ?????? ?????? ??????)
                            printf("\n 2-4 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }else if( p_map[j+4][i] != BLACK && j -1 == 0 ){//?????? ?????? - ????????? ?????? ????????? ??????
                            printf("\n 2-5 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }
                    }
                }
                if(j-2 >=0 && j+2 <=14){// ?????? - B  B N B B
                    if(p_map[j-2][i] == BLACK && p_map[j-1][i] == BLACK && p_map[j+1][i] == BLACK && p_map[j+2][i] == BLACK ){
                        if( p_map[j-3][i] != BLACK && p_map[j+3][i] != BLACK && j+3 <= 14 && j-3 >= 0){
                            printf("\n 2-6 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }else if( p_map[j+3][i] != BLACK && j - 2 == 0){//????????? ?????? ?????? ?????? -> ????????? ??????
                            printf("\n 2-7 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }else if( p_map[j-3][i] != BLACK && j + 2 == 14){//????????? ?????? ???????????? -> ????????? ??????
                            printf("\n 2-8 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }
                    }
                }
                if( j-3 >=0 && j+1 <= 14){// ?????? - B B  B N B
                    if(p_map[j-3][i] == BLACK && p_map[j-2][i] == BLACK && p_map[j-1][i] == BLACK && p_map[j+1][i] == BLACK){
                        if( p_map[j+2][i] != BLACK && p_map[j-4][i] != BLACK && j+2 <= 14 && j-4 >= 0){
                            printf("\n 2-9 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }else if ( p_map[j+2][i] !=BLACK && j -3 == 0){//????????? ?????? - ????????? ??????
                            printf("\n 2-10 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }else if( p_map[j-4][i] != BLACK && j+1 == 14){//????????? ?????? - ????????? ??????
                            printf("\n 2-11 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }
                    }
                }
                if( j-4 >= 0){// ?????? - B B B B N
                    if(p_map[j-4][i] == BLACK && p_map[j-3][i] == BLACK && p_map[j-2][i] == BLACK && p_map[j-1][i] == BLACK){
                        if(j == 14){//?????? ?????? ?????? - ?????? ?????? ????????? ???????????? - 5?????????
                            printf("\n 2-12 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }else if( p_map[j+1][i] != BLACK && j != 14){//?????? ??????
                            printf("\n 2-13 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }
                    }
                }
                // Dia 1 - "\"
                if( i+4 <= 14 && j+4 <= 14){ // dia1 - N B B B B
                    if(p_map[j+1][i+1] == BLACK && p_map[j+2][i+2] == BLACK && p_map[j+3][i+3] == BLACK && p_map[j+4][i+4] == BLACK){
                        if( p_map[j-1][i-1] != BLACK && j-1>=0 && i-1>=0)//????????? ????????? ?????? 5?????? -> ????????? ?????? ?????? - ????????? ??? ????????? 4
                        {
                            printf("\n 3-1 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }
                        else if( i == 0 || j== 0)//????????? ?????? ?????? ???????????? - ?????? ?????? ??????
                        {   //push(j,i);
                            printf("\n 3-2 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }
                    }
                }
                if(i-1 >= 0 && i+3 <=14 && j-1 >= 0 && j+3 <=14){// dia1 - B N B B B
                    if(p_map[j-1][i-1] == BLACK && p_map[j+1][i+1] == BLACK && p_map[j+2][i+2] == BLACK && p_map[j+3][i+3] == BLACK){
                        if( p_map[j-2][i-2] != BLACK && p_map[j+4][i+4] != BLACK && (i-2 >=0 && i+4 <= 14) && (j-2 >=0 && j+4 <= 14) ){//?????? ?????? ?????? - ????????? ??????
                            printf("\n 3-3 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }else if( p_map[j-2][i-2] != BLACK && (i+3 == 14 || j+3 == 14)){//?????? ?????? (????????? ?????? ?????? ??????)
                            printf("\n 3-4 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }else if( p_map[j+4][i+4] != BLACK && (i -1 == 0  || j -1 == 0) ){//?????? ??????
                            printf("\n 3-5 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }
                    }
                }
                if(i-2 >=0 && i+2 <=14 && j-2 >=0 && j+2 <=14){// dia1 - B  B N B B
                    if(p_map[j-2][i-2] == BLACK && p_map[j-1][i-1] == BLACK && p_map[j+1][i+1] == BLACK && p_map[j+2][i+2] == BLACK ){
                        if( p_map[j-3][i-3] != BLACK && p_map[j+3][i+3] != BLACK && i+3 <= 14 && i-3 >= 0 && j+3 <= 14 && j-3 >= 0){
                            printf("\n 3-6 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }else if( p_map[j+3][i+3] != BLACK && (i - 2 == 0 || j - 2 == 0)){
                            printf("\n 3-7 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }else if( p_map[j-3][i-3] != BLACK && (i + 2 == 14 || j + 2 == 14)){
                            printf("\n 3-8 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }
                    }
                }
                if( i-3 >=0 && i+1 <= 14 && j-3 >=0 && j+1 <= 14){// dia1 - B B  B N B
                    if(p_map[j-3][i-3] == BLACK && p_map[j-2][i-2] == BLACK && p_map[j-1][i-1] == BLACK && p_map[j+1][i+1] == BLACK){
                        if( p_map[j+2][i+2] != BLACK && p_map[j-4][i-4] != BLACK && i+2 <= 14 && i-4 >= 0 && j+2 <= 14 && j-4 >= 0){
                            printf("\n 3-9 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }else if ( p_map[j+2][i+2] !=BLACK && (i -3 == 0 || j -3 == 0)){
                            printf("\n 3-10 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }else if( p_map[j-4][i-4] != BLACK && (i+1 == 14 || j+1 == 14)){
                            printf("\n 3-11 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }
                    }
                }
                if( i-4 >= 0 && j-4 >= 0){// dia1 - B B B B N
                    if(p_map[j-4][i-4] == BLACK && p_map[j-3][i-3] == BLACK && p_map[j-2][i-2] == BLACK && p_map[j-1][i-1] == BLACK){
                        if( i == 14 || j == 14){//?????? ?????? ?????? -- ?????? ????????? ?????? ??????(5?????????) - ?????? ????????? ??? ??????
                            printf("\n 3-12 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }else if( p_map[j+1][i+1] != BLACK && i != 14 && j != 14){
                            printf("\n 3-13 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }
                    }
                }
                // DIa 2 - /
                if( j-4 >=0 && i+4 <= 14){ // dia2 - N B B B B
                    if(p_map[j-1][i+1] == BLACK && p_map[j-2][i+2] == BLACK && p_map[j-3][i+3] == BLACK && p_map[j-4][i+4] == BLACK){
                        if( p_map[j+1][i-1]  != BLACK && j+1<=14 && i-1>=0) // ?????? ?????? - ????????? ?????? ??????
                        {
                            printf("\n 4-1 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }
                        else if( j == 14 || i == 0)//??? ??????
                        {   //push(j,i);
                            printf("\n 4-2 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }
                    }
                }
                if( j-3 >= 0 && j+1 <=14 && i-1 >= 0 && i+3 <=14){// dia2 - B N B B B
                    if(p_map[j+1][i-1] == BLACK && p_map[j-1][i+1] == BLACK && p_map[j-2][i+2] == BLACK && p_map[j-3][i+3] == BLACK){
                        if( p_map[j+2][i-2] != BLACK && p_map[j-4][i+4] != BLACK &&
                                (i-2 >=0 && i+4 <= 14) && (j-4 >=0 && j+2 <= 14) ){//?????? ?????? ?????? - ????????? ??????
                            printf("\n 4-3 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }else if( p_map[j+2][i-2] != BLACK  && (i+3 == 14 || j-3 == 0)){//?????? ?????? (????????? ?????? ?????? ??????) ??? ??????
                            printf("\n 4-4 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }else if( p_map[j-4][i+4] != BLACK && (j + 1 == 14 || i -1 == 0 )){//?????? ?????? ??? ??????
                            printf("\n 4-5 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }
                    }
                }
                if(j-2 >=0 && j+2 <=14 && i-2 >=0 && i+2 <=14){// dia2 - B  B N B B
                    if(p_map[j+2][i-2] == BLACK && p_map[j+1][i-1] == BLACK && p_map[j-1][i+1] == BLACK && p_map[j-2][i+2] == BLACK ){
                        if( p_map[j+3][i-3] != BLACK && p_map[j-3][i+3] != BLACK &&
                                (i-3 >=0 && i+3 <=14 ) && (j-3 >=0 && j+3 <= 14)){
                            printf("\n 4-6find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }else if( p_map[j+3][i-3] != BLACK && ( j == 2 || i == 12)){//?????? ??????
                            printf("\n 4-7 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }else if( p_map[j-3][i+3] != BLACK && ( j == 12 || i == 2)){//?????? ??????
                            printf("\n 4-8 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }
                    }
                }
                if( j+3 <= 14 && i-3 >=0 && j-1 >=0 && i+1 <= 14){// dia2 - B B  B N B
                    if(p_map[j+3][i-3] == BLACK && p_map[j+2][i-2] == BLACK && p_map[j+1][i-1] == BLACK && p_map[j-1][i+1] == BLACK){
                        if( p_map[j+4][i-4] != BLACK && p_map[j-2][i+2] != BLACK &&
                                (j+4 <= 14 && i-4>=0) && (j-2 >=0 && i+2 <= 14)){// 2<=j<= 10   4<=i<=12
                            printf("\n 4-9 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }else if ( p_map[j+4][i-4] !=BLACK && (j == 1 || i == 13)){
                            printf("\n 4-10 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }else if( p_map[j-2][i+2] != BLACK && (j == 11 || i == 3)){
                            printf("\n 4-11 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }
                    }
                }
                if( j+4 <= 14 && i-4 >= 0){// dia2 - B B B B N
                    if(p_map[j+4][i-4] == BLACK && p_map[j+3][i-3] == BLACK && p_map[j+2][i-2] == BLACK && p_map[j+1][i-1] == BLACK){
                        if(p_map[j-1][i+1] !=BLACK && (j-1>=0 && i+1<=14)){//?????? ?????? - ????????? ?????? ??????
                            printf("\n 4-12 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }else if( j == 0 || i == 14){// ?????? ?????? ??????
                            printf("\n 4-13 find connect 4 - j = %d , i = %d   ",j,i);
                            find_num++;
                            bit_map[j][i]++;

                        }
                    }
                }
            }
        }
    }
     printf("\n **** ENd B44******");
     return find_num;
}
int Game::findFB3(std::array<std::array<int,15>,15>& p_map, std::array<std::array<int, 2>, 10> &buf_xy, int buf_size)//?????? ?????? 3 - will make 4
{
    printf("\n **** find Full B3******");
    /*
      ????????? ???
      (B) (N) B B (N)
     */
     int p = 0;
     int b = 0;
     int buf_p = 10 - buf_size;
     int find_num =0;
     for(int j = 0; j < 15; j++){
         for(int i =0; i < 15; i++){
             if(p_map[j][i] == PAN){//only PAN - Black cannot put NON
                 if(i+3 <= 14){// ?????? - (N) <N> B B B (N)
                     if(p_map[j][i+1] == BLACK && p_map[j][i+2] == BLACK && p_map[j][i+3] == BLACK){
                         if( p_map[j][i-1] == PAN && p_map[j][i+4] == PAN && i+4 <= 14 && i-1>=0) // ??? ?????? ??????
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
                 if(i-1 >= 0 && i+2 <=14){// ?????? - (N) B <N> B B (N)
                     if(p_map[j][i-1] == BLACK && p_map[j][i+1] == BLACK && p_map[j][i+2] == BLACK){
                         if( p_map[j][i-2] == PAN && p_map[j][i+3] == PAN && (i-2 >=0 && i+3 <= 14) ){//?????? ?????? ?????? - ????????? ??????
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
                 if(i-2 >=0 && i+1 <=14){// ?????? - (N) B  B <N> B (N)
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
                 if( i-3 >=0 ){// ?????? - (N) B B  B <N> (N)
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
                 //// - ??????
                 if(j+3 <= 14){// ?????? - (N) <N> B B B (N)
                     if(p_map[j+1][i] == BLACK && p_map[j+2][i] == BLACK && p_map[j+3][i] == BLACK){
                         if( p_map[j-1][i] == PAN && p_map[j+4][i] == PAN && j+4 <= 14 && j-1>=0) // ??? ?????? ??????
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
                 if(j-1 >= 0 && j+2 <=14){// ?????? - (N) B <N> B B (N)
                     if(p_map[j-1][i] == BLACK && p_map[j+1][i] == BLACK && p_map[j+2][i] == BLACK){
                         if( p_map[j-2][i] == PAN && p_map[j+3][i] == PAN && (j-2 >=0 && j+3 <= 14) ){//?????? ?????? ?????? - ????????? ??????
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
                 if(j-2 >=0 && j+1 <=14){// ?????? - (N) B  B <N> B (N)
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
                 if( j-3 >=0){// ?????? - (N) B B  B <N> (N)
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
                         if( p_map[j-1][i-1] == PAN && p_map[j+4][i+4] == PAN && j+4 <= 14 && j-1>=0 && i+4 <= 14 && i-1>=0) // ??? ?????? ??????
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
                         if( p_map[j-2][i-2] == PAN && p_map[j+3][i+3] == PAN && (j-2 >=0 && j+3 <= 14) && (i-2 >=0 && i+3 <= 14) ){//?????? ?????? ?????? - ????????? ??????
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
                         if( p_map[j+1][i-1] == PAN && p_map[j-4][i+4] == PAN && (j+1<=14 && j-4>=0) && (i+4<=14 && i-1>=0)) // ??? ?????? ??????
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
                         if( p_map[j+2][i-2] == PAN && p_map[j-3][i+3] == PAN && (j-3 >=0 && j+2 <= 14) && (i-2 >=0 && i+3 <= 14) ){//?????? ?????? ?????? - ????????? ??????
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

int Game::wfindFB3(std::array<std::array<int, 15>, 15> &p_map, std::array<std::array<int, 15>, 15> &bit_map)
{
    printf("\n **** find Full B3******");

     for(int j = 0; j < 15; j++){
         for(int i =0; i < 15; i++){
             if(p_map[j][i] == PAN){//only PAN - Black cannot put NON
                 if(i+3 <= 14){// ?????? - (N) <N> B B B (N)
                     if(p_map[j][i+1] == BLACK && p_map[j][i+2] == BLACK && p_map[j][i+3] == BLACK){
                         if( p_map[j][i-1] == PAN && p_map[j][i+4] == PAN && i+4 <= 14 && i-1>=0) // ??? ?????? ??????
                         {
                             printf("\n 1-1 find connect 4 - j = %d , i = %d   ",j,i);
                             bit_map[j][i] += 100;

                         }
                     }
                 }
                 if(i-1 >= 0 && i+2 <=14){// ?????? - (N) B <N> B B (N)
                     if(p_map[j][i-1] == BLACK && p_map[j][i+1] == BLACK && p_map[j][i+2] == BLACK){
                         if( p_map[j][i-2] == PAN && p_map[j][i+3] == PAN && (i-2 >=0 && i+3 <= 14) ){//?????? ?????? ?????? - ????????? ??????
                             printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                             bit_map[j][i] += 100;
                         }
                     }
                 }
                 if(i-2 >=0 && i+1 <=14){// ?????? - (N) B  B <N> B (N)
                     if(p_map[j][i-2] == BLACK && p_map[j][i-1] == BLACK && p_map[j][i+1] == BLACK){
                         if( p_map[j][i-3] == PAN && p_map[j][i+2] == PAN && i+2 <= 14 && i-3 >= 0){
                             printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                             bit_map[j][i] += 100;
                         }
                     }
                 }
                 if( i-3 >=0 ){// ?????? - (N) B B  B <N> (N)
                     if(p_map[j][i-3] == BLACK && p_map[j][i-2] == BLACK && p_map[j][i-1] == BLACK){
                         if( p_map[j][i-4] == PAN && p_map[j][i+1] == PAN && i+1 <= 14 && i-4 >= 0){
                             printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                             bit_map[j][i] += 100;
                         }
                     }
                 }
                 //// - ??????
                 if(j+3 <= 14){// ?????? - (N) <N> B B B (N)
                     if(p_map[j+1][i] == BLACK && p_map[j+2][i] == BLACK && p_map[j+3][i] == BLACK){
                         if( p_map[j-1][i] == PAN && p_map[j+4][i] == PAN && j+4 <= 14 && j-1>=0) // ??? ?????? ??????
                         {
                             printf("\n 1-1 find connect 4 - j = %d , i = %d   ",j,i);
                             bit_map[j][i] += 100;
                         }
                     }
                 }
                 if(j-1 >= 0 && j+2 <=14){// ?????? - (N) B <N> B B (N)
                     if(p_map[j-1][i] == BLACK && p_map[j+1][i] == BLACK && p_map[j+2][i] == BLACK){
                         if( p_map[j-2][i] == PAN && p_map[j+3][i] == PAN && (j-2 >=0 && j+3 <= 14) ){//?????? ?????? ?????? - ????????? ??????
                             printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                             bit_map[j][i] += 100;
                         }
                     }
                 }
                 if(j-2 >=0 && j+1 <=14){// ?????? - (N) B  B <N> B (N)
                     if(p_map[j-2][i] == BLACK && p_map[j-1][i] == BLACK && p_map[j+1][i] == BLACK){
                         if( p_map[j-3][i] == PAN && p_map[j+2][i] == PAN && j+2 <= 14 && j-3 >= 0){
                             printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                             bit_map[j][i] += 100;
                         }
                     }
                 }
                 if( j-3 >=0){// ?????? - (N) B B  B <N> (N)
                     if(p_map[j-3][i] == BLACK && p_map[j-2][i] == BLACK && p_map[j-1][i] == BLACK){
                         if( p_map[j-4][i] == PAN && p_map[j+1][i] == PAN && j+1 <= 14 && j-4 >= 0){
                             printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                             bit_map[j][i] += 100;
                         }
                     }
                 }
                 // Dia 1 - "\"
                 if(i+1 <= 14 && j+3 <= 14){// Dia 1 - (N) <N> B B B (N)
                     if(p_map[j+1][i+1] == BLACK && p_map[j+2][i+2] == BLACK && p_map[j+3][i+3] == BLACK){
                         if( p_map[j-1][i-1] == PAN && p_map[j+4][i+4] == PAN && j+4 <= 14 && j-1>=0 && i+4 <= 14 && i-1>=0) // ??? ?????? ??????
                         {
                             printf("\n 1-1 find connect 4 - j = %d , i = %d   ",j,i);
                             bit_map[j][i] += 100;
                         }
                     }
                 }
                 if( i-1 >= 0 && i+2 <=14 && j-1 >= 0 && j+2 <=14){// Dia 1 - (N) B <N> B B (N)
                     if(p_map[j-1][i-1] == BLACK && p_map[j+1][i+1] == BLACK && p_map[j+2][i+2] == BLACK){
                         if( p_map[j-2][i-2] == PAN && p_map[j+3][i+3] == PAN && (j-2 >=0 && j+3 <= 14) && (i-2 >=0 && i+3 <= 14) ){//?????? ?????? ?????? - ????????? ??????
                             printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                             bit_map[j][i] += 100;
                         }
                     }
                 }
                 if(i-2 >=0 && i+1 <=14 && j-2 >=0 && j+1 <=14){// Dia 1 - (N) B  B <N> B (N)
                     if(p_map[j-2][i-2] == BLACK && p_map[j-1][i-1] == BLACK && p_map[j+1][i+1] == BLACK){
                         if( p_map[j-3][i-3] == PAN && p_map[j+2][i+2] == PAN && j+2 <= 14 && j-3 >= 0 && i+2 <= 14 && i-3 >= 0){
                             printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                             bit_map[j][i] += 100;
                         }
                     }
                 }
                 if( i-3 >=0 && j-3 >=0){// Dia 1 - (N) B B  B <N> (N)
                     if(p_map[j-3][i-3] == BLACK && p_map[j-2][i-2] == BLACK && p_map[j-1][i-1] == BLACK){
                         if( p_map[j-4][i-4] == PAN && p_map[j+1][i+1] == PAN && j+1 <= 14 && j-4 >= 0 && i+1 <= 14 && i-4 >= 0){
                             printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                             bit_map[j][i] += 100;
                         }
                     }
                 }

                 // DIa 2 - /
                 if(i+3 <= 14 && j-3 >=0 ){// DIa 2 - (N) <N> B B B (N)
                     if(p_map[j-1][i+1] == BLACK && p_map[j-2][i+2] == BLACK && p_map[j-3][i+3] == BLACK){
                         if( p_map[j+1][i-1] == PAN && p_map[j-4][i+4] == PAN && (j+1<=14 && j-4>=0) && (i+4<=14 && i-1>=0)) // ??? ?????? ??????
                         {
                             printf("\n 1-1 find connect 4 - j = %d , i = %d   ",j,i);
                             bit_map[j][i] += 100;
                         }
                     }
                 }
                 if( i-1>=0 && i+2<=14 && j-2>=0 && j+1<=14 ){// Dia 2 - (N) B <N> B B (N)
                     if(p_map[j+1][i-1] == BLACK && p_map[j-1][i+1] == BLACK && p_map[j-2][i+2] == BLACK){
                         if( p_map[j+2][i-2] == PAN && p_map[j-3][i+3] == PAN && (j-3 >=0 && j+2 <= 14) && (i-2 >=0 && i+3 <= 14) ){//?????? ?????? ?????? - ????????? ??????
                             printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                             bit_map[j][i] += 100;
                         }
                     }
                 }
                 if(i-2 >=0 && i+1 <=14 && j+2 >=0 && j-1 <=14){// Dia 2 - (N) B  B <N> B (N)
                     if(p_map[j+2][i-2] == BLACK && p_map[j+1][i-1] == BLACK && p_map[j-1][i+1] == BLACK){
                         if( p_map[j+3][i-3] == PAN && p_map[j-2][i+2] == PAN && j+3 <= 14 && j-2 >= 0 && i+2 <= 14 && i-3 >= 0){
                             printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                             bit_map[j][i] += 100;
                         }
                     }
                 }
                 if( i-3 >=0 && j+3 <= 14){// Dia 2 - (N) B B  B <N> (N)
                     if(p_map[j+3][i-3] == BLACK && p_map[j+2][i-2] == BLACK && p_map[j+1][i-1] == BLACK){
                         if( p_map[j+4][i-4] == PAN && p_map[j-1][i+1] == PAN && j+4 <= 14 && j-1 >= 0 && i+1 <= 14 && i-4 >= 0){
                             printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                             bit_map[j][i] += 100;
                         }
                     }
                 }
                 //
             }
         }
     }
      printf("\n **** ENd Full B3******");
      return 1;
}
int Game::findFW3(std::array<std::array<int,15>,15>& p_map, std::array<std::array<int, 2>, 10> &buf_xy, int buf_size)
{
    printf("\n **** find Full W3******");
    /*
      ????????? ???
      (B) (N) B B (N)
     */
     int p = 0;
     int b = 0;
     int buf_p = 10 - buf_size;
     int find_num = 0;
     for(int j = 0; j < 15; j++){
         for(int i =0; i < 15; i++){
             if(p_map[j][i] == PAN || p_map[j][i] == NON){//only PAN, NON - White can put NON
                 if(i+3 <= 14){// ?????? - (N) <N> B B B (N)
                     if(p_map[j][i+1] == WHITE && p_map[j][i+2] == WHITE && p_map[j][i+3] == WHITE){
                         if( p_map[j][i-1] == PAN && p_map[j][i+4] == PAN && i+4 <= 14 && i-1>=0) // ??? ?????? ??????
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
                 if(i-1 >= 0 && i+2 <=14){// ?????? - (N) B <N> B B (N)
                     if(p_map[j][i-1] == WHITE && p_map[j][i+1] == WHITE && p_map[j][i+2] == WHITE){
                         if( p_map[j][i-2] == PAN && p_map[j][i+3] == PAN && (i-2 >=0 && i+3 <= 14) ){//?????? ?????? ?????? - ????????? ??????
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
                 if(i-2 >=0 && i+1 <=14){// ?????? - (N) B  B <N> B (N)
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
                 if( i-3 >=0 ){// ?????? - (N) B B  B <N> (N)
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
                 //// - ??????
                 if(j+3 <= 14){// ?????? - (N) <N> B B B (N)
                     if(p_map[j+1][i] == WHITE && p_map[j+2][i] == WHITE && p_map[j+3][i] == WHITE){
                         if( (p_map[j-1][i] == PAN || p_map[j-1][i] == NON) && (p_map[j+4][i] == PAN || p_map[j+4][i] == NON) && j+4 <= 14 && j-1>=0) // ??? ?????? ??????
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
                 if(j-1 >= 0 && j+2 <=14){// ?????? - (N) B <N> B B (N)
                     if(p_map[j-1][i] == WHITE && p_map[j+1][i] == WHITE && p_map[j+2][i] == WHITE){
                         if( ( p_map[j-2][i] == NON || p_map[j-2][i] == PAN) && (p_map[j+3][i] == PAN || p_map[j+3][i] == NON) && (j-2 >=0 && j+3 <= 14) ){//?????? ?????? ?????? - ????????? ??????
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
                 if(j-2 >=0 && j+1 <=14){// ?????? - (N) B  B <N> B (N)
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
                 if( j-3 >=0){// ?????? - (N) B B  B <N> (N)
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
                         if( (p_map[j-1][i-1] == PAN || p_map[j-1][i-1] == NON) && (p_map[j+4][i+4] == PAN || p_map[j+4][i+4] == NON) && j+4 <= 14 && j-1>=0 && i+4 <= 14 && i-1>=0) // ??? ?????? ??????
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
                         if( (p_map[j-2][i-2] == PAN || p_map[j-2][i-2] == NON) && (p_map[j+3][i+3] == PAN || p_map[j+3][i+3] == NON) && (j-2 >=0 && j+3 <= 14) && (i-2 >=0 && i+3 <= 14) ){//?????? ?????? ?????? - ????????? ??????
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
                         if( (p_map[j+1][i-1] == PAN || p_map[j+1][i-1] == NON) && (p_map[j-4][i+4] == PAN || p_map[j-4][i+4] == NON) && (j+1<=14 && j-4>=0) && (i+4<=14 && i-1>=0)) // ??? ?????? ??????
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
                         if( (p_map[j+2][i-2] == PAN || p_map[j+2][i-2] == NON) && (p_map[j-3][i+3] == PAN || p_map[j-3][i+3] == NON) && (j-3 >=0 && j+2 <= 14) && (i-2 >=0 && i+3 <= 14) ){//?????? ?????? ?????? - ????????? ??????
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
      ????????? ???
      (B) (N) B B (N)
     */
    int p = 0;
    int b = 0;
    int buf_p = 10 - buf_size;
    int find_num = 0;
    for(int j = 0; j < 15; j++){
        for(int i =0; i < 15; i++){
            if(p_map[j][i] == PAN){//only PAN - Black cannot put NON
                if(i+3 <= 14){// ?????? - (N) <N> B B B (N)
                    if(p_map[j][i+1] == BLACK && p_map[j][i+2] == BLACK && p_map[j][i+3] == BLACK){
                        if( (p_map[j][i-1] == WHITE || p_map[j][i-1] == NON ) && (p_map[j][i+4] == WHITE || p_map[j][i+4] == NON ) && i+4 <= 14 && i-1>=0) // ?????? ?????? ?????? ??????
                        {
//                            printf("\n 1-1 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if (((p_map[j][i-1] == WHITE || p_map[j][i-1] == NON ) || (p_map[j][i+4] == WHITE || p_map[j][i+4] == NON )) && i+4 <= 14 && i-1>=0){//????????? ?????? ??????
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
                if(i-1 >= 0 && i+2 <=14){// ?????? - (N) B <N> B B (N)
                    if(p_map[j][i-1] == BLACK && p_map[j][i+1] == BLACK && p_map[j][i+2] == BLACK){
                        if( (p_map[j][i-2] == WHITE || p_map[j][i-2] == NON) && (p_map[j][i+3] == WHITE || p_map[j][i+3] == NON)  && (i-2 >=0 && i+3 <= 14) ){//?????? ?????? ?????? - ????????? ??????
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
                if(i-2 >=0 && i+1 <=14){// ?????? - (N) B  B <N> B (N)
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
                if( i-3 >=0 ){// ?????? - (N) B B  B <N> (N)
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
                //// - ??????
                if(j+3 <= 14){// ?????? - (N) <N> B B B (N)
                    if(p_map[j+1][i] == BLACK && p_map[j+2][i] == BLACK && p_map[j+3][i] == BLACK){
                        if( (p_map[j-1][i] == WHITE || p_map[j-1][i] == NON) && (p_map[j+4][i] == WHITE || p_map[j+4][i] == NON ) && j+4 <= 14 && j-1>=0) // ??? ?????? ??????
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
                if(j-1 >= 0 && j+2 <=14){// ?????? - (N) B <N> B B (N)
                    if(p_map[j-1][i] == BLACK && p_map[j+1][i] == BLACK && p_map[j+2][i] == BLACK){
                        if( (p_map[j-2][i] == WHITE || p_map[j-2][i] == NON) && (p_map[j+3][i] == WHITE || p_map[j+3][i] == NON) && (j-2 >=0 && j+3 <= 14) ){//?????? ?????? ?????? - ????????? ??????
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
                if(j-2 >=0 && j+1 <=14){// ?????? - (N) B  B <N> B (N)
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
                if( j-3 >=0){// ?????? - (N) B B  B <N> (N)
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
                        if( (p_map[j-1][i-1] == WHITE || p_map[j-1][i-1] == NON) && (p_map[j+4][i+4] == WHITE || p_map[j+4][i+4] == NON) && j+4 <= 14 && j-1>=0 && i+4 <= 14 && i-1>=0) // ??? ?????? ??????
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
                        if( (p_map[j-2][i-2] == WHITE || p_map[j-2][i-2] == NON) && (p_map[j+3][i+3] == WHITE || p_map[j+3][i+3] == NON) && (j-2 >=0 && j+3 <= 14) && (i-2 >=0 && i+3 <= 14) ){//?????? ?????? ?????? - ????????? ??????

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
                        if( (p_map[j+1][i-1] == WHITE || p_map[j+1][i-1] == NON) && (p_map[j-4][i+4] == WHITE || p_map[j-4][i+4] == NON) && (j+1<=14 && j-4>=0) && (i+4<=14 && i-1>=0)) // ??? ?????? ??????
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
                        if( (p_map[j+2][i-2] == WHITE || p_map[j+2][i-2] == NON) && (p_map[j-3][i+3] == WHITE || p_map[j-3][i+3] == NON) && (j-3 >=0 && j+2 <= 14) && (i-2 >=0 && i+3 <= 14) ){//?????? ?????? ?????? - ????????? ??????

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

int Game::wfindHB3(std::array<std::array<int, 15>, 15> &p_map, std::array<std::array<int, 15>, 15> &bit_map)
{
    printf("\n **** find Half B3******");
    /*
      ????????? ???
      (B) (N) B B (N)
     */
    int find_num = 0;
    for(int j = 0; j < 15; j++){
        for(int i =0; i < 15; i++){
            if(p_map[j][i] == PAN){//only PAN - Black cannot put NON
                if(i+3 <= 14){// ?????? - (N) <N> B B B (N)
                    if(p_map[j][i+1] == BLACK && p_map[j][i+2] == BLACK && p_map[j][i+3] == BLACK){
                        if( (p_map[j][i-1] == WHITE || p_map[j][i-1] == NON ) && (p_map[j][i+4] == WHITE || p_map[j][i+4] == NON ) && i+4 <= 14 && i-1>=0) // ?????? ?????? ?????? ??????
                        {
//                            printf("\n 1-1 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if (((p_map[j][i-1] == WHITE || p_map[j][i-1] == NON ) || (p_map[j][i+4] == WHITE || p_map[j][i+4] == NON )) && i+4 <= 14 && i-1>=0){//????????? ?????? ??????
                            printf("\n 1-1 find connect 4 - j = %d , i = %d   ",j,i);
                            bit_map[j][i] += 60;
                            find_num++;
                        }
                    }
                }
                if(i-1 >= 0 && i+2 <=14){// ?????? - (N) B <N> B B (N)
                    if(p_map[j][i-1] == BLACK && p_map[j][i+1] == BLACK && p_map[j][i+2] == BLACK){
                        if( (p_map[j][i-2] == WHITE || p_map[j][i-2] == NON) && (p_map[j][i+3] == WHITE || p_map[j][i+3] == NON)  && (i-2 >=0 && i+3 <= 14) ){//?????? ?????? ?????? - ????????? ??????
                            //printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if(((p_map[j][i-2] == WHITE || p_map[j][i-2] == NON) || (p_map[j][i+3] == WHITE || p_map[j][i+3] == NON))  && (i-2 >=0 && i+3 <= 14)){
                            printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                            bit_map[j][i] += 60;
                            find_num++;
                        }
                    }
                }
                if(i-2 >=0 && i+1 <=14){// ?????? - (N) B  B <N> B (N)
                    if(p_map[j][i-2] == BLACK && p_map[j][i-1] == BLACK && p_map[j][i+1] == BLACK){
                        if( (p_map[j][i-3] == WHITE || p_map[j][i-3] == NON) && (p_map[j][i+2] == WHITE || p_map[j][i+2] == NON)  && i+2 <= 14 && i-3 >= 0){
                            //printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if(((p_map[j][i-3] == WHITE || p_map[j][i-3] == NON) || (p_map[j][i+2] == WHITE || p_map[j][i+2] == NON))  && i+2 <= 14 && i-3 >= 0){
                            printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                            bit_map[j][i] += 60;
                            find_num++;
                        }
                    }
                }
                if( i-3 >=0 ){// ?????? - (N) B B  B <N> (N)
                    if(p_map[j][i-3] == BLACK && p_map[j][i-2] == BLACK && p_map[j][i-1] == BLACK){
                        if( (p_map[j][i-4] == WHITE || p_map[j][i-4] == NON) && (p_map[j][i+1] == WHITE || p_map[j][i+1] == NON) && i+1 <= 14 && i-4 >= 0){
                            //printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if(((p_map[j][i-4] == WHITE || p_map[j][i-4] == NON) || (p_map[j][i+1] == WHITE || p_map[j][i+1] == NON)) && i+1 <= 14 && i-4 >= 0){
                            printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                            bit_map[j][i] += 60;
                            find_num++;
                        }
                    }
                }
                //// - ??????
                if(j+3 <= 14){// ?????? - (N) <N> B B B (N)
                    if(p_map[j+1][i] == BLACK && p_map[j+2][i] == BLACK && p_map[j+3][i] == BLACK){
                        if( (p_map[j-1][i] == WHITE || p_map[j-1][i] == NON) && (p_map[j+4][i] == WHITE || p_map[j+4][i] == NON ) && j+4 <= 14 && j-1>=0) // ??? ?????? ??????
                        {
                            //printf("\n 1-1 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if(((p_map[j-1][i] == WHITE || p_map[j-1][i] == NON) || (p_map[j+4][i] == WHITE || p_map[j+4][i] == NON )) && j+4 <= 14 && j-1>=0){
                            printf("\n 1-1 find connect 4 - j = %d , i = %d   ",j,i);
                            bit_map[j][i] += 60;
                            find_num++;
                        }
                    }
                }
                if(j-1 >= 0 && j+2 <=14){// ?????? - (N) B <N> B B (N)
                    if(p_map[j-1][i] == BLACK && p_map[j+1][i] == BLACK && p_map[j+2][i] == BLACK){
                        if( (p_map[j-2][i] == WHITE || p_map[j-2][i] == NON) && (p_map[j+3][i] == WHITE || p_map[j+3][i] == NON) && (j-2 >=0 && j+3 <= 14) ){//?????? ?????? ?????? - ????????? ??????
                            //printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if(((p_map[j-2][i] == WHITE || p_map[j-2][i] == NON) || (p_map[j+3][i] == WHITE || p_map[j+3][i] == NON)) && (j-2 >=0 && j+3 <= 14)){
                            printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                            bit_map[j][i] += 60;
                            find_num++;
                        }
                    }
                }
                if(j-2 >=0 && j+1 <=14){// ?????? - (N) B  B <N> B (N)
                    if(p_map[j-2][i] == BLACK && p_map[j-1][i] == BLACK && p_map[j+1][i] == BLACK){
                        if( (p_map[j-3][i] == WHITE || p_map[j-3][i] == NON)  && (p_map[j+2][i] == WHITE || p_map[j+2][i] == NON) && j+2 <= 14 && j-3 >= 0){
                            //printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if(((p_map[j-3][i] == WHITE || p_map[j-3][i] == NON)  || (p_map[j+2][i] == WHITE || p_map[j+2][i] == NON)) && j+2 <= 14 && j-3 >= 0){
                            printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                            bit_map[j][i] += 60;
                            find_num++;
                        }
                    }
                }
                if( j-3 >=0){// ?????? - (N) B B  B <N> (N)
                    if(p_map[j-3][i] == BLACK && p_map[j-2][i] == BLACK && p_map[j-1][i] == BLACK){
                        if( (p_map[j-4][i] == WHITE || p_map[j-4][i] == NON) && (p_map[j+1][i] == WHITE || p_map[j+1][i] == NON) && j+1 <= 14 && j-4 >= 0){
                            //printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if(((p_map[j-4][i] == WHITE || p_map[j-4][i] == NON) || (p_map[j+1][i] == WHITE || p_map[j+1][i] == NON)) && j+1 <= 14 && j-4 >= 0){
                            printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                            bit_map[j][i] += 60;
                            find_num++;
                        }
                    }
                }
                // Dia 1 - "\"
                if(i+1 <= 14 && j+3 <= 14){// Dia 1 - (N) <N> B B B (N)
                    if(p_map[j+1][i+1] == BLACK && p_map[j+2][i+2] == BLACK && p_map[j+3][i+3] == BLACK){
                        if( (p_map[j-1][i-1] == WHITE || p_map[j-1][i-1] == NON) && (p_map[j+4][i+4] == WHITE || p_map[j+4][i+4] == NON) && j+4 <= 14 && j-1>=0 && i+4 <= 14 && i-1>=0) // ??? ?????? ??????
                        {

                        }else if(((p_map[j-1][i-1] == WHITE || p_map[j-1][i-1] == NON) || (p_map[j+4][i+4] == WHITE || p_map[j+4][i+4] == NON)) && j+4 <= 14 && j-1>=0 && i+4 <= 14 && i-1>=0){
                             printf("\n 1-1 find connect 4 - j = %d , i = %d   ",j,i);
                            bit_map[j][i] += 60;
                             find_num++;
                        }
                    }
                }
                if( i-1 >= 0 && i+2 <=14 && j-1 >= 0 && j+2 <=14){// Dia 1 - (N) B <N> B B (N)
                    if(p_map[j-1][i-1] == BLACK && p_map[j+1][i+1] == BLACK && p_map[j+2][i+2] == BLACK){
                        if( (p_map[j-2][i-2] == WHITE || p_map[j-2][i-2] == NON) && (p_map[j+3][i+3] == WHITE || p_map[j+3][i+3] == NON) && (j-2 >=0 && j+3 <= 14) && (i-2 >=0 && i+3 <= 14) ){//?????? ?????? ?????? - ????????? ??????

                        }else if( ((p_map[j-2][i-2] == WHITE || p_map[j-2][i-2] == NON) || (p_map[j+3][i+3] == WHITE || p_map[j+3][i+3] == NON)) && (j-2 >=0 && j+3 <= 14) && (i-2 >=0 && i+3 <= 14) ){
                            printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                            bit_map[j][i] += 60;
                            find_num++;
                        }
                    }//
                }
                if(i-2 >=0 && i+1 <=14 && j-2 >=0 && j+1 <=14){// Dia 1 - (N) B  B <N> B (N)
                    if(p_map[j-2][i-2] == BLACK && p_map[j-1][i-1] == BLACK && p_map[j+1][i+1] == BLACK){
                        if( (p_map[j-3][i-3] == WHITE || p_map[j-3][i-3] == NON) && (p_map[j+2][i+2] == WHITE || p_map[j+2][i+2] == NON) && j+2 <= 14 && j-3 >= 0 && i+2 <= 14 && i-3 >= 0){

                        }else if(((p_map[j-3][i-3] == WHITE || p_map[j-3][i-3] == NON) || (p_map[j+2][i+2] == WHITE || p_map[j+2][i+2] == NON)) && j+2 <= 14 && j-3 >= 0 && i+2 <= 14 && i-3 >= 0){
                            printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                            bit_map[j][i] += 60;
                            find_num++;
                        }
                    }
                }
                if( i-3 >=0 && j-3 >=0){// Dia 1 - (N) B B  B <N> (N)
                    if(p_map[j-3][i-3] == BLACK && p_map[j-2][i-2] == BLACK && p_map[j-1][i-1] == BLACK){
                        if( (p_map[j-4][i-4] == WHITE || p_map[j-4][i-4] == NON) && (p_map[j+1][i+1] == WHITE || p_map[j+1][i+1] == NON) && j+1 <= 14 && j-4 >= 0 && i+1 <= 14 && i-4 >= 0){

                        }else if(((p_map[j-4][i-4] == WHITE || p_map[j-4][i-4] == NON) || (p_map[j+1][i+1] == WHITE || p_map[j+1][i+1] == NON)) && j+1 <= 14 && j-4 >= 0 && i+1 <= 14 && i-4 >= 0){
                            printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                            bit_map[j][i] += 60;
                            find_num++;
                        }
                    }
                }

                // DIa 2 - /
                if(i+3 <= 14 && j-3 >=0 ){// DIa 2 - (N) <N> B B B (N)
                    if(p_map[j-1][i+1] == BLACK && p_map[j-2][i+2] == BLACK && p_map[j-3][i+3] == BLACK){
                        if( (p_map[j+1][i-1] == WHITE || p_map[j+1][i-1] == NON) && (p_map[j-4][i+4] == WHITE || p_map[j-4][i+4] == NON) && (j+1<=14 && j-4>=0) && (i+4<=14 && i-1>=0)) // ??? ?????? ??????
                        {

                        }else if(((p_map[j+1][i-1] == WHITE || p_map[j+1][i-1] == NON) || (p_map[j-4][i+4] == WHITE || p_map[j-4][i+4] == NON)) && (j+1<=14 && j-4>=0) && (i+4<=14 && i-1>=0)){
                            printf("\n 1-1 find connect 4 - j = %d , i = %d   ",j,i);
                            bit_map[j][i] += 60;
                            find_num++;
                        }
                    }
                }
                if( i-1>=0 && i+2<=14 && j-2>=0 && j+1<=14 ){// Dia 2 - (N) B <N> B B (N)
                    if(p_map[j+1][i-1] == BLACK && p_map[j-1][i+1] == BLACK && p_map[j-2][i+2] == BLACK){
                        if( (p_map[j+2][i-2] == WHITE || p_map[j+2][i-2] == NON) && (p_map[j-3][i+3] == WHITE || p_map[j-3][i+3] == NON) && (j-3 >=0 && j+2 <= 14) && (i-2 >=0 && i+3 <= 14) ){//?????? ?????? ?????? - ????????? ??????

                        }else if( ((p_map[j+2][i-2] == WHITE || p_map[j+2][i-2] == NON) || (p_map[j-3][i+3] == WHITE || p_map[j-3][i+3] == NON)) && (j-3 >=0 && j+2 <= 14) && (i-2 >=0 && i+3 <= 14) ){
                            printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                            bit_map[j][i] += 60;
                            find_num++;
                        }
                    }
                }
                if(i-2 >=0 && i+1 <=14 && j+2 >=0 && j-1 <=14){// Dia 2 - (N) B  B <N> B (N)
                    if(p_map[j+2][i-2] == BLACK && p_map[j+1][i-1] == BLACK && p_map[j-1][i+1] == BLACK){
                        if( (p_map[j+3][i-3] == WHITE || p_map[j+3][i-3] == NON) && (p_map[j-2][i+2] == WHITE || p_map[j-2][i+2] == NON) && j+3 <= 14 && j-2 >= 0 && i+2 <= 14 && i-3 >= 0){

                        }else if(((p_map[j+3][i-3] == WHITE || p_map[j+3][i-3] == NON) || (p_map[j-2][i+2] == WHITE || p_map[j-2][i+2] == NON)) && j+3 <= 14 && j-2 >= 0 && i+2 <= 14 && i-3 >= 0){
                            printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                            bit_map[j][i] += 60;
                            find_num++;
                        }
                    }
                }
                if( i-3 >=0 && j+3 <= 14){// Dia 2 - (N) B B  B <N> (N)
                    if(p_map[j+3][i-3] == BLACK && p_map[j+2][i-2] == BLACK && p_map[j+1][i-1] == BLACK){
                        if( (p_map[j+4][i-4] == WHITE || p_map[j+4][i-4] == NON) && (p_map[j-1][i+1] == WHITE || p_map[j-1][i+1] == NON) && j+4 <= 14 && j-1 >= 0 && i+1 <= 14 && i-4 >= 0){

                        }else if(((p_map[j+4][i-4] == WHITE || p_map[j+4][i-4] == NON) || (p_map[j-1][i+1] == WHITE || p_map[j-1][i+1] == NON)) && j+4 <= 14 && j-1 >= 0 && i+1 <= 14 && i-4 >= 0){
                            printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                            bit_map[j][i] += 60;
                            find_num++;
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
      ????????? ???
      (B) (N) B B (N)
     */
    int p = 0;
    int b = 0;
    int buf_p = 10 - buf_size;
    int find_num = 0;
    for(int j = 0; j < 15; j++){
        for(int i =0; i < 15; i++){
            if(p_map[j][i] == PAN || p_map[j][i] == NON){//only PAN - Black cannot put NON
                if(i+3 <= 14){// ?????? - (N) <N> B B B (N)
                    if(p_map[j][i+1] == WHITE && p_map[j][i+2] == WHITE && p_map[j][i+3] == WHITE){
                        if( (p_map[j][i-1] == BLACK ) && (p_map[j][i+4] == BLACK) && i+4 <= 14 && i-1>=0) // ?????? ?????? ?????? ??????
                        {
//                            printf("\n 1-1 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if (((p_map[j][i-1] == BLACK) || (p_map[j][i+4] == BLACK )) && i+4 <= 14 && i-1>=0){//????????? ?????? ??????
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
                if(i-1 >= 0 && i+2 <=14){// ?????? - (N) B <N> B B (N)
                    if(p_map[j][i-1] == WHITE && p_map[j][i+1] == WHITE && p_map[j][i+2] == WHITE){
                        if( (p_map[j][i-2] == BLACK ) && (p_map[j][i+3] == BLACK )  && (i-2 >=0 && i+3 <= 14) ){//?????? ?????? ?????? - ????????? ??????
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
                if(i-2 >=0 && i+1 <=14){// ?????? - (N) B  B <N> B (N)
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
                if( i-3 >=0 ){// ?????? - (N) B B  B <N> (N)
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
                //// - ??????
                if(j+3 <= 14){// ?????? - (N) <N> B B B (N)
                    if(p_map[j+1][i] == WHITE && p_map[j+2][i] == WHITE && p_map[j+3][i] == WHITE){
                        if( (p_map[j-1][i] == BLACK) && (p_map[j+4][i] == BLACK ) && j+4 <= 14 && j-1>=0) // ??? ?????? ??????
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
                if(j-1 >= 0 && j+2 <=14){// ?????? - (N) B <N> B B (N)
                    if(p_map[j-1][i] == WHITE && p_map[j+1][i] == WHITE && p_map[j+2][i] == WHITE){
                        if( (p_map[j-2][i] == BLACK) && (p_map[j+3][i] == BLACK ) && (j-2 >=0 && j+3 <= 14) ){//?????? ?????? ?????? - ????????? ??????
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
                if(j-2 >=0 && j+1 <=14){// ?????? - (N) B  B <N> B (N)
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
                if( j-3 >=0){// ?????? - (N) B B  B <N> (N)
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
                        if( (p_map[j-1][i-1] == BLACK ) && (p_map[j+4][i+4] == BLACK) && j+4 <= 14 && j-1>=0 && i+4 <= 14 && i-1>=0) // ??? ?????? ??????
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
                        if( (p_map[j-2][i-2] == BLACK) && (p_map[j+3][i+3] == BLACK ) && (j-2 >=0 && j+3 <= 14) && (i-2 >=0 && i+3 <= 14) ){//?????? ?????? ?????? - ????????? ??????

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
                        if( (p_map[j+1][i-1] == BLACK ) && (p_map[j-4][i+4] == BLACK ) && (j+1<=14 && j-4>=0) && (i+4<=14 && i-1>=0)) // ??? ?????? ??????
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
                        if( (p_map[j+2][i-2] == BLACK ) && (p_map[j-3][i+3] == BLACK ) && (j-3 >=0 && j+2 <= 14) && (i-2 >=0 && i+3 <= 14) ){//?????? ?????? ?????? - ????????? ??????

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
      ????????? ???
      (B) (N) B B (N)
     */
    int p = 0;
    int b = 0;
    int buf_p = 10 - buf_size;
    int find_num = 0;
    for(int j = 0; j<=14;j++){
        for(int i=0; i<=14;i++){
            if(p_map[j][i] == PAN){//BLACK - PAN, WHITE - PAN + NON
                //??????
                // 1??????
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
                //2??????
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
                //3??????
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
                //4??????
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

                //5??????
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

                //??????-------------
                // 1??????
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
                //2??????
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
                //3??????
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
                //4??????
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

                //5??????
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
                // 1??????
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
                //2??????
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
                //3??????
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
                //4??????
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

                //5??????
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
                // 1??????
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
                //2??????
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
                //3??????
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
                //4??????
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

                //5??????
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

int Game::wfindB2(std::array<std::array<int, 15>, 15> &p_map, std::array<std::array<int, 15>, 15> &bit_map)
{
    printf("\n **** find B2******");
    /*
      ????????? ???
      (B) (N) B B (N)
     */
    int p = 0;
    int b = 0;
    int find_num = 0;
    for(int j = 0; j<=14;j++){
        for(int i=0; i<=14;i++){
            if(p_map[j][i] == PAN){//BLACK - PAN, WHITE - PAN + NON
                //??????
                // 1??????
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
                    find_num++;
                    bit_map[j][i ]+=5;

                }
                if(p_map[j][i-1] == PAN &&
                        p_map[j][i+1] == BLACK &&
                        p_map[j][i+2] == PAN &&
                        p_map[j][i+3] == BLACK &&
                        p_map[j][i+4] == PAN &&
                        i-1 >= 0 && i+4<=14){// <B> B (N) B (N)
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    find_num++;
                    bit_map[j][i ]+=5;
                }
                if(p_map[j][i-1] == PAN &&
                        p_map[j][i+1] == PAN &&
                        p_map[j][i+2] == BLACK &&
                        p_map[j][i+3] == BLACK &&
                        p_map[j][i+4] == PAN &&
                        i-1 >=0 && i+4<=14){// <B> (N) B B (N)
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    find_num++;
                    bit_map[j][i ]+=5;
                }
                if(p_map[j][i+1] == PAN &&
                        p_map[j][i+2] == BLACK &&
                        p_map[j][i+3] == PAN &&
                        p_map[j][i+4] == BLACK &&
                        i+4<=14){// <B> (N) B (N) B
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    find_num++;
                    bit_map[j][i ]+=5;
                }
                //2??????
                // N  B <B> B N
                // B <B> N  B N
                if(p_map[j][i-2] == PAN &&
                        p_map[j][i-1] == BLACK &&
                        p_map[j][i+1] == BLACK &&
                        p_map[j][i+2] == PAN &&
                        i-2 >=0 && i+2 <= 14){// N  B <B> B N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    find_num++;
                    bit_map[j][i ]+=5;
                }
                if(p_map[j][i-2] == PAN &&
                        p_map[j][i-1] == BLACK &&
                        p_map[j][i+1] == PAN &&
                        p_map[j][i+2] == BLACK &&
                        p_map[j][i+3] == PAN &&
                        i-2 >=0 && i+3 <= 14){  // B <B> N  B N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    find_num++;
                    bit_map[j][i ]+=5;
                }
                //3??????
                // B N <B> B N
                // B N <B> N B
                // N B B <B> N
                if(p_map[j][i-2] == BLACK &&
                        p_map[j][i-1] == PAN &&
                        p_map[j][i+1] == BLACK &&
                        p_map[j][i+2] == PAN &&
                        i-2 >=0 && i+2 <=14){// B N <B> B N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    find_num++;
                    bit_map[j][i ]+=5;
                }
                if(p_map[j][-3] == PAN &&
                        p_map[j][i-2] == BLACK &&
                        p_map[j][i-1] == PAN &&
                        p_map[j][i+1] == PAN &&
                        p_map[j][i+2] == BLACK &&
                        i-3 >=0 && i+2 <=14){//// B N <B> N B
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    find_num++;
                    bit_map[j][i]+=5;
                }
                if(p_map[j][i-3] == PAN &&
                        p_map[j][i-2] == BLACK &&
                        p_map[j][i-1] == BLACK &&
                        p_map[j][i+1] == PAN &&
                        i-3 >=0 && i+1 <=14){// N B B <B> N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    find_num++;
                    bit_map[j][i]+=5;
                }
                //4??????
                // B B N <B> N
                // B N B <B> N
                if(p_map[j][i-4] == PAN &&
                        p_map[j][i-3] == BLACK &&
                        p_map[j][i-2] == BLACK &&
                        p_map[j][i-1] == PAN &&
                        p_map[j][i+1] == PAN &&
                        i-4>=0 && i+1<=14){// B B N <B> N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    find_num++;
                    bit_map[j][i]+=5;
                }
                if(p_map[j][i-4] == PAN &&
                        p_map[j][i-3] == BLACK &&
                        p_map[j][i-2] == PAN &&
                        p_map[j][i-1] == BLACK &&
                        p_map[j][i+1] == PAN &&
                        i-4>=0 && i+1<=14){// B N B <B> N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    find_num++;
                    bit_map[j][i]+=5;
                }

                //5??????
                // B N B N <B>
                if(p_map[j][i-4] == BLACK &&
                        p_map[j][i-3] == PAN &&
                        p_map[j][i-2] == BLACK &&
                        p_map[j][i-1] == PAN &&
                        i-4>=0){
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    find_num++;
                    bit_map[j][i]+=5;
                }

                //??????-------------
                // 1??????
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
                    find_num++;
                    bit_map[j][i]+=5;
                }
                if(p_map[j-1][i] == PAN &&
                        p_map[j+1][i] == BLACK &&
                        p_map[j+2][i] == PAN &&
                        p_map[j+3][i] == BLACK &&
                        p_map[j+4][i] == PAN &&
                        j-1 >=0 && j+4<=14){// <B> B (N) B (N)
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    find_num++;
                    bit_map[j][i]+=5;
                }
                if(p_map[j-1][i] == PAN &&
                        p_map[j+1][i] == PAN &&
                        p_map[j+2][i] == BLACK &&
                        p_map[j+3][i] == BLACK &&
                        p_map[j+4][i] == PAN &&
                        j-1 >=0 && j+4<=14){// <B> (N) B B (N)
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    find_num++;
                    bit_map[j][i]+=5;
                }
                if(p_map[j+1][i] == PAN &&
                        p_map[j+2][i] == BLACK &&
                        p_map[j+3][i] == PAN &&
                        p_map[j+4][i] == BLACK &&
                        j+4<=14){// <B> (N) B (N) B
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    find_num++;
                    bit_map[j][i]+=5;
                }
                //2??????
                // N  B <B> B N
                // B <B> N  B N
                if(p_map[j-2][i] == PAN &&
                        p_map[j-1][i] == BLACK &&
                        p_map[j+1][i] == BLACK &&
                        p_map[j+2][i] == PAN &&
                        j-2 >=0 && j+2 <= 14){// N  B <B> B N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    find_num++;
                    bit_map[j][i]+=5;
                }
                if(p_map[j-2][i] == PAN &&
                        p_map[j-1][i] == BLACK &&
                        p_map[j+1][i] == PAN &&
                        p_map[j+2][i] == BLACK &&
                        p_map[j+3][i] == PAN &&
                        j-2 >=0 && j+3 <= 14){  // B <B> N  B N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    find_num++;
                    bit_map[j][i]+=5;
                }
                //3??????
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
                    find_num++;
                    bit_map[j][i]+=5;
                }
                if(p_map[j-2][i] == BLACK &&
                        p_map[j-1][i] == PAN &&
                        p_map[j+1][i] == PAN &&
                        p_map[j+2][i] == BLACK &&
                        j-2 >=0 && j+2 <=14){// B N <B> N B
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    find_num++;
                    bit_map[j][i]+=5;
                }
                if(p_map[j-3][i] == PAN &&
                        p_map[j-2][i] == BLACK &&
                        p_map[j-1][i] == BLACK &&
                        p_map[j+1][i] == PAN &&
                        j-3 >=0 && j+1 <=14){// N B B <B> N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    find_num++;
                    bit_map[j][i]+=5;
                }
                //4??????
                // B B N <B> N
                // B N B <B> N
                if(p_map[j-4][i] == PAN &&
                        p_map[j-3][i] == BLACK &&
                        p_map[j-2][i] == BLACK &&
                        p_map[j-1][i] == PAN &&
                        p_map[j+1][i] == PAN &&
                        j-4>=0 && j+1<=14){// B B N <B> N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    find_num++;
                    bit_map[j][i]+=5;
                }
                if(p_map[j-4][i] == PAN &&
                        p_map[j-3][i] == BLACK &&
                        p_map[j-2][i] == PAN &&
                        p_map[j-1][i] == BLACK &&
                        p_map[j+1][i] == PAN &&
                        j-4>=0 && j+1<=14){// B N B <B> N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    find_num++;
                    bit_map[j][i]+=5;
                }

                //5??????
                // B N B N <B>
                if(p_map[j-4][i] == BLACK &&
                        p_map[j-3][i] == PAN &&
                        p_map[j-2][i] == BLACK &&
                        p_map[j-1][i] == PAN &&
                        j-4>=0){
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    find_num++;
                    bit_map[j][i]+=5;
                }

                //Dia 1 - "\" ----------------
                // 1??????
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
                    find_num++;
                    bit_map[j][i]+=5;
                }
                if(p_map[j-1][i-1] == PAN &&
                        p_map[j+1][i+1] == BLACK &&
                        p_map[j+2][i+2] == PAN &&
                        p_map[j+3][i+3] == BLACK &&
                        p_map[j+4][i+4] == PAN &&
                        j-1 >=0 && i-1 >=0 && j+4<=14 && i+4<=14){// <B> B (N) B (N)
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    find_num++;
                    bit_map[j][i]+=5;
                }
                if(p_map[j-1][i-1] == PAN &&
                        p_map[j+1][i+1] == PAN &&
                        p_map[j+2][i+2] == BLACK &&
                        p_map[j+3][i+3] == BLACK &&
                        p_map[j+4][i+4] == PAN &&
                        j+4<=14 && i+4<=14 && j-1 >=0 && i-1 >=0){// <B> (N) B B (N)
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    find_num++;
                    bit_map[j][i]+=5;
                }
                if(p_map[j+1][i+1] == PAN &&
                        p_map[j+2][i+2] == BLACK &&
                        p_map[j+3][i+3] == PAN &&
                        p_map[j+4][i+4] == BLACK &&
                        j+4<=14 && i+4<=14){// <B> (N) B (N) B
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    find_num++;
                    bit_map[j][i]+=5;
                }
                //2??????
                // N  B <B> B N
                // B <B> N  B N
                if(p_map[j-2][i-2] == PAN &&
                        p_map[j-1][i-1] == BLACK &&
                        p_map[j+1][i+1] == BLACK &&
                        p_map[j+2][i+2] == PAN &&
                        j-2 >=0 && j+2 <= 14 && i-2 >=0 && i+2 <= 14){// N  B <B> B N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    find_num++;
                    bit_map[j][i]+=5;
                }
                if(p_map[j-2][i-2] == PAN &&
                        p_map[j-1][i-1] == BLACK &&
                        p_map[j+1][i+1] == PAN &&
                        p_map[j+2][i+2] == BLACK &&
                        p_map[j+3][i+3] == PAN &&
                        j-2 >=0 && j+3 <= 14 && i-2 >=0 && i+3 <= 14){  // B <B> N  B N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    find_num++;
                    bit_map[j][i]+=5;
                }
                //3??????
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
                    find_num++;
                    bit_map[j][i]+=5;
                }
                if(p_map[j-2][i-2] == BLACK &&
                        p_map[j-1][i-1] == PAN &&
                        p_map[j+1][i+1] == PAN &&
                        p_map[j+2][i+2] == BLACK &&
                        j-2 >=0 && j+2 <=14 && i-2 >=0 && i+2 <=14){// B N <B> N B
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    find_num++;
                    bit_map[j][i]+=5;
                }
                if(p_map[j-3][i-3] == PAN &&
                        p_map[j-2][i-2] == BLACK &&
                        p_map[j-1][i-1] == BLACK &&
                        p_map[j+1][i+1] == PAN &&
                        j-3 >=0 && j+1 <=14 && i-3 >=0 && i+1 <=14){// N B B <B> N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    find_num++;
                    bit_map[j][i]+=5;
                }
                //4??????
                // B B N <B> N
                // B N B <B> N
                if(p_map[j-4][i-4] == PAN &&
                        p_map[j-3][i-3] == BLACK &&
                        p_map[j-2][i-2] == BLACK &&
                        p_map[j-1][i-1] == PAN &&
                        p_map[j+1][i+1] == PAN &&
                        j-4>=0 && j+1<=14 && i-4>=0 && i+1<=14){// B B N <B> N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    find_num++;
                    bit_map[j][i]+=5;
                }
                if(p_map[j-4][i-4] == PAN &&
                        p_map[j-3][i-3] == BLACK &&
                        p_map[j-2][i-2] == PAN &&
                        p_map[j-1][i-1] == BLACK &&
                        p_map[j+1][i+1] == PAN &&
                        j-4>=0 && j+1<=14 && i-4>=0 && i+1<=14){// B N B <B> N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    find_num++;
                    bit_map[j][i]+=5;
                }

                //5??????
                // B N B N <B>
                if(p_map[j-4][i-4] == BLACK &&
                        p_map[j-3][i-3] == PAN &&
                        p_map[j-2][i-2] == BLACK &&
                        p_map[j-1][i-1] == PAN &&
                        j-4>=0 && i-4>=0){
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    find_num++;
                    bit_map[j][i]+=5;
                }
                //Dia 2 = "/" ----------------
                // 1??????
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
                    find_num++;
                    bit_map[j][i]+=5;
                }
                if(p_map[j+1][i-1] == PAN &&
                        p_map[j-1][i+1] == BLACK &&
                        p_map[j-2][i+2] == PAN &&
                        p_map[j-3][i+3] == BLACK &&
                        p_map[j-4][i+4] == PAN &&
                        i-1 >=0 && j+1 <=14 && j-4>=0 && i+4<=14){// <B> B (N) B (N)
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    find_num++;
                    bit_map[j][i]+=5;
                }
                if(p_map[j+1][i-1] == PAN &&
                        p_map[j-1][i+1] == PAN &&
                        p_map[j-2][i+2] == BLACK &&
                        p_map[j-3][i+3] == BLACK &&
                        p_map[j-4][i+4] == PAN &&
                        j+1<=14 && i-1 >=0 && j-4>=0 && i+4<=14){// <B> (N) B B (N)
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    find_num++;
                    bit_map[j][i]+=5;
                }
                if(p_map[j-1][i+1] == PAN &&
                        p_map[j-2][i+2] == BLACK &&
                        p_map[j-3][i+3] == PAN &&
                        p_map[j-4][i+4] == BLACK &&
                        j-4>=0 && i+4<=14){// <B> (N) B (N) B
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    find_num++;
                    bit_map[j][i]+=5;
                }
                //2??????
                // N  B <B> B N
                // B <B> N  B N
                if(p_map[j+2][i-2] == PAN &&
                        p_map[j+1][i-1] == BLACK &&
                        p_map[j-1][i+1] == BLACK &&
                        p_map[j-2][i+2] == PAN &&
                        j-2 >=0 && j+2 <= 14 && i-2 >=0 && i+2 <= 14){// N  B <B> B N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    find_num++;
                    bit_map[j][i]+=5;
                }
                if(p_map[j+2][i-2] == PAN &&
                        p_map[j+1][i-1] == BLACK &&
                        p_map[j-1][i+1] == PAN &&
                        p_map[j-2][i+2] == BLACK &&
                        p_map[j-3][i+3] == PAN &&
                        j-3 >=0 && j+2 <= 14 && i-2 >=0 && i+3 <= 14){  // B <B> N  B N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    find_num++;
                    bit_map[j][i]+=5;
                }
                //3??????
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
                    find_num++;
                    bit_map[j][i]+=5;
                }
                if(p_map[j+2][i-2] == BLACK &&
                        p_map[j+1][i-1] == PAN &&
                        p_map[j-1][i+1] == PAN &&
                        p_map[j-2][i+2] == BLACK &&
                        j-2 >=0 && j+2 <=14 && i-2 >=0 && i+2 <=14){// B N <B> N B
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    find_num++;
                    bit_map[j][i]+=5;
                }
                if(p_map[j+3][i-3] == PAN &&
                        p_map[j+2][i-2] == BLACK &&
                        p_map[j+1][i-1] == BLACK &&
                        p_map[j-1][i+1] == PAN &&
                        j-1 >=0 && j+3 <=14 && i-3 >=0 && i+1 <=14){// N B B <B> N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    find_num++;
                    bit_map[j][i]+=5;
                }
                //4??????
                // B B N <B> N
                // B N B <B> N
                if(p_map[j+4][i-4] == PAN &&
                        p_map[j+3][i-3] == BLACK &&
                        p_map[j+2][i-2] == BLACK &&
                        p_map[j+1][i-1] == PAN &&
                        p_map[j-1][i+1] == PAN &&
                        j-1>=0 && j+4<=14 && i-4>=0 && i+1<=14){// B B N <B> N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    find_num++;
                    bit_map[j][i]+=5;
                }
                if(p_map[j+4][i-4] == PAN &&
                        p_map[j+3][i-3] == BLACK &&
                        p_map[j+2][i-2] == PAN &&
                        p_map[j+1][i-1] == BLACK &&
                        p_map[j-1][i+1] == PAN &&
                        j-1>=0 && j+4<=14 && i-4>=0 && i+1<=14){// B N B <B> N
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    find_num++;
                    bit_map[j][i]+=5;
                }

                //5??????
                // B N B N <B>
                if(p_map[j+4][i-4] == BLACK &&
                        p_map[j+3][i-3] == PAN &&
                        p_map[j+2][i-2] == BLACK &&
                        p_map[j+1][i-1] == PAN &&
                        j+4<=14 && i-4>=0){
                    printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                    find_num++;
                    bit_map[j][i]+=5;
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
      ????????? ???
      (B) (N) B B (N)
     */
    int p = 0;
    int b = 0;
    int buf_p = 10 - buf_size;
    int find_num =0;
    for(int j = 0; j<=14;j++){
        for(int i=0; i<=14;i++){
            if(p_map[j][i] == PAN || p_map[j][i] == NON){//BLACK - PAN, WHITE - PAN + NON
                //??????
                // 1??????
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
                //2??????
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
                //3??????
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
                //4??????
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

                //5??????
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

                //??????-------------
                // 1??????
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
                //2??????
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
                //3??????
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
                //4??????
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

                //5??????
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
                // 1??????
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
                //2??????
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
                //3??????
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
                //4??????
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

                //5??????
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
                // 1??????
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
                //2??????
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
                //3??????
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
                //4??????
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

                //5??????
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
                if(i+4 <= 14){ // ?????? - N B B B B
                    if(p_map[j][i+1] == WHITE && p_map[j][i+2] == WHITE && p_map[j][i+3] == WHITE && p_map[j][i+4] == WHITE){
                        if( p_map[j][i-1]  != WHITE && i-1>=0) // ?????? ??????
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
                if(i-1 >= 0 && i+3 <=14){// ?????? - B N B B B
                    if(p_map[j][i-1] == WHITE && p_map[j][i+1] == WHITE && p_map[j][i+2] == WHITE && p_map[j][i+3] == WHITE){
                        if( p_map[j][i-2] != WHITE && p_map[j][i+4] != WHITE && (i-2 >=0 && i+4 <= 14) ){//?????? ?????? ?????? - ????????? ??????
                            printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j][i-2] != WHITE && i+3 == 14){//?????? ?????? (????????? ?????? ?????? ??????)
                            printf("\n 1-4 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j][i+4] != WHITE && i -1 == 0 ){//?????? ??????
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
                if(i-2 >=0 && i+2 <=14){// ?????? - B  B N B B
                    if(p_map[j][i-2] == WHITE && p_map[j][i-1] == WHITE && p_map[j][i+1] == WHITE && p_map[j][i+2] == WHITE ){
                        if( p_map[j][i-3] != WHITE && p_map[j][i+3] != WHITE && i+3 <= 14 && i-3 >= 0){
                            printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j][i+3] != WHITE && i - 2 == 0){//????????? ???????????? -> ????????? ??????
                            printf("\n 1-7 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j][i-3] != WHITE && i + 2 == 14){//????????? ?????? ?????? -> ????????? ??????
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
                if( i-3 >=0 && i+1 <= 14){// ?????? - B B  B N B
                    if(p_map[j][i-3] == WHITE && p_map[j][i-2] == WHITE && p_map[j][i-1] == WHITE && p_map[j][i+1] == WHITE){
                        if( p_map[j][i+2] != WHITE && p_map[j][i-4] != WHITE && i+2 <= 14 && i-4 >= 0){
                            printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if ( p_map[j][i+2] !=WHITE && i -3 == 0){//????????? ?????? -> ????????? ??????
                            printf("\n 1-10 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j][i-4] != WHITE && i+1 == 14){//????????? ?????? -> ????????? ??????
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
                if( i-4 >= 0){// ?????? - B B B B N
                    if(p_map[j][i-4] == WHITE && p_map[j][i-3] == WHITE && p_map[j][i-2] == WHITE && p_map[j][i-1] == WHITE){
                        if(i == 14){//?????? ?????? ?????? - ???????????? ??????(????????? ?????? ??????)
                            printf("\n 1-12 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j][i+1] != WHITE && i != 14){//?????? ??????
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
                //// - ??????
                if(j+4 <= 14){ // ?????? - N B B B B
                    if(p_map[j+1][i] == WHITE && p_map[j+2][i] == WHITE && p_map[j+3][i] == WHITE && p_map[j+4][i] == WHITE){
                        if( p_map[j-1][i]  != WHITE && j-1>=0)//?????? ?????? ????????? ?????? ??????
                        {
                            printf("\n 2-1 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                        else if( j== 0)//????????? ???????????? - ?????? ????????? ??????
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
                if(j-1 >= 0 && j+3 <=14){// ?????? - B N B B B
                    if(p_map[j-1][i] == WHITE && p_map[j+1][i] == WHITE && p_map[j+2][i] == WHITE && p_map[j+3][i] == WHITE){
                        if( p_map[j-2][i] != WHITE && p_map[j+4][i] != WHITE && (j-2 >=0 && j+4 <= 14) ){//?????? ?????? ?????? - ????????? ??????
                            printf("\n 2-3 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j-2][i] != WHITE && j+3 == 14){//?????? ?????? (????????? ?????? ?????? ??????)
                            printf("\n 2-4 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j+4][i] != WHITE && j -1 == 0 ){//?????? ?????? - ????????? ?????? ????????? ??????
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
                if(j-2 >=0 && j+2 <=14){// ?????? - B  B N B B
                    if(p_map[j-2][i] == WHITE && p_map[j-1][i] == WHITE && p_map[j+1][i] == WHITE && p_map[j+2][i] == WHITE ){
                        if( p_map[j-3][i] != WHITE && p_map[j+3][i] != WHITE && j+3 <= 14 && j-3 >= 0){
                            printf("\n 2-6 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j+3][i] != WHITE && j - 2 == 0){//????????? ?????? ?????? ?????? -> ????????? ??????
                            printf("\n 2-7 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j-3][i] != WHITE && j + 2 == 14){//????????? ?????? ???????????? -> ????????? ??????
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
                if( j-3 >=0 && j+1 <= 14){// ?????? - B B  B N B
                    if(p_map[j-3][i] == WHITE && p_map[j-2][i] == WHITE && p_map[j-1][i] == WHITE && p_map[j+1][i] == WHITE){
                        if( p_map[j+2][i] != WHITE && p_map[j-4][i] != WHITE && j+2 <= 14 && j-4 >= 0){
                            printf("\n 2-9 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if ( p_map[j+2][i] !=WHITE && j -3 == 0){//????????? ?????? - ????????? ??????
                            printf("\n 2-10 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j-4][i] != WHITE && j+1 == 14){//????????? ?????? - ????????? ??????
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
                if( j-4 >= 0){// ?????? - B B B B N
                    if(p_map[j-4][i] == WHITE && p_map[j-3][i] == WHITE && p_map[j-2][i] == WHITE && p_map[j-1][i] == WHITE){
                        if(j == 14){//?????? ?????? ?????? - ?????? ?????? ????????? ???????????? - 5?????????
                            printf("\n 2-12 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j+1][i] != WHITE && j != 14){//?????? ??????
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
                        if( p_map[j-1][i-1] != WHITE && j-1>=0 && i-1>=0)//????????? ????????? ?????? 5?????? -> ????????? ?????? ?????? - ????????? ??? ????????? 4
                        {
                            printf("\n 3-1 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                        else if( i == 0 || j== 0)//????????? ?????? ?????? ???????????? - ?????? ?????? ??????
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
                        if( p_map[j-2][i-2] != WHITE && p_map[j+4][i+4] != WHITE && (i-2 >=0 && i+4 <= 14) && (j-2 >=0 && j+4 <= 14) ){//?????? ?????? ?????? - ????????? ??????
                            printf("\n 3-3 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j-2][i-2] != WHITE && (i+3 == 14 || j+3 == 14)){//?????? ?????? (????????? ?????? ?????? ??????)
                            printf("\n 3-4 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j+4][i+4] != WHITE && (i -1 == 0  || j -1 == 0) ){//?????? ??????
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
                        if( i == 14 || j == 14){//?????? ?????? ?????? -- ?????? ????????? ?????? ??????(5?????????) - ?????? ????????? ??? ??????
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
                        if( p_map[j+1][i-1]  != WHITE && j+1<=14 && i-1>=0) // ?????? ?????? - ????????? ?????? ??????
                        {
                            printf("\n 4-1 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }
                        else if( j == 14 || i == 0)//??? ??????
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
                                (i-2 >=0 && i+4 <= 14) && (j-4 >=0 && j+2 <= 14) ){//?????? ?????? ?????? - ????????? ??????
                            printf("\n 4-3 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j+2][i-2] != WHITE  && (i+3 == 14 || j-3 == 0)){//?????? ?????? (????????? ?????? ?????? ??????) ??? ??????
                            printf("\n 4-4 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j-4][i+4] != WHITE && (j + 1 == 14 || i -1 == 0 )){//?????? ?????? ??? ??????
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
                        }else if( p_map[j+3][i-3] != WHITE && ( j == 2 || i == 12)){//?????? ??????
                            printf("\n 4-7 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( p_map[j-3][i+3] != WHITE && ( j == 12 || i == 2)){//?????? ??????
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
                        if(p_map[j-1][i+1] !=WHITE && (j-1>=0 && i+1<=14)){//?????? ?????? - ????????? ?????? ??????
                            printf("\n 4-12 find connect 4 - j = %d , i = %d   ",j,i);
                            if(buf_p<10){
                                buf_xy[buf_p][0]=j;
                                buf_xy[buf_p][1]=i;
                                buf_p++;
                                find_num++;
                            }
                        }else if( j == 0 || i == 14){// ?????? ?????? ??????
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
