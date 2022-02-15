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
        }



        setGui();
        //miniMax(i_map,1,1,1,1);
        //int findB4(std::array<std::array<int,15>,15>& p_map, std::array<std::array<int,2>,10>& buf_xy, int buf_size);
        std::array<std::array<int,2>,10> temp;
        findB4(i_map,temp,1);
        findW4(i_map,temp,1);
        findFB3(i_map,temp,1);
        findFW3(i_map,temp,1);
        findHB3(i_map,temp,1);
        findHW3(i_map,temp,1);
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
        return 1000000;
    }else if(searchLength(i_map,5,color)){
        return 1000000;
    }else if(searchDia(i_map,5,color)){
        return 1000000;
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

int Game::calScore(std::array<std::array<int, 15>, 15>& p_map)
{

}

int Game::findSpotW(std::array<std::array<int,15>,15>& p_map, std::array<std::array<int, 2>, 10> &buf_xy, int buf_size)
{
    int m_size = 0;
    m_size += findW4(p_map, buf_xy, buf_size);
    m_size += findB4(p_map, buf_xy, buf_size - m_size);

    m_size += findFW3(p_map, buf_xy, buf_size - m_size);
    m_size += findFB3(p_map, buf_xy, buf_size - m_size);
    //
    m_size += findHW3(p_map, buf_xy, buf_size - m_size);
    m_size += findHB3(p_map, buf_xy, buf_size - m_size);

    m_size += findW2(p_map, buf_xy, buf_size - m_size);
    m_size += findB2(p_map, buf_xy, buf_size - m_size);

    m_size += findB1(p_map, buf_xy, buf_size - m_size);

    return m_size;
}

int Game::findSpotB(std::array<std::array<int,15>,15>& p_map, std::array<std::array<int, 2>, 10> &buf_xy, int buf_size)
{
    int m_size = 0;
    m_size += findB4(p_map, buf_xy, buf_size);
    m_size += findW4(p_map, buf_xy, buf_size - m_size);
    m_size += findFB3(p_map, buf_xy, buf_size - m_size);
    m_size += findFW3(p_map, buf_xy, buf_size - m_size);
    //
    m_size += findHB3(p_map, buf_xy, buf_size - m_size);
    m_size += findHW3(p_map, buf_xy, buf_size - m_size);

    m_size += findB2(p_map, buf_xy, buf_size - m_size);
    m_size += findW2(p_map, buf_xy, buf_size - m_size);

    m_size += findB1(p_map, buf_xy, buf_size - m_size);

    return m_size;
}

int Game::findB4(std::array<std::array<int,15>,15>& p_map,std::array<std::array<int, 2>, 10> &buf_xy, int buf_size)//will make 5
{
    printf("\n **** find B4******");
    int p = 0;
    int b = 0;
    for(int j = 0; j < 15; j++){
        for(int i =0; i < 15; i++){
            if(p_map[j][i] == PAN){//only PAN
                if(i+4 <= 14){ // 가로 - N B B B B
                    if(p_map[j][i+1] == BLACK && p_map[j][i+2] == BLACK && p_map[j][i+3] == BLACK && p_map[j][i+4] == BLACK){
                        if( p_map[j][i-1]  != BLACK && i-1>=0) // 좌측 검사
                        {
                            printf("\n 1-1 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                        else if( i == 0) //
                        {   //push(j,i);
                            printf("\n 1-2 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if(i-1 >= 0 && i+3 <=14){// 가로 - B N B B B
                    if(p_map[j][i-1] == BLACK && p_map[j][i+1] == BLACK && p_map[j][i+2] == BLACK && p_map[j][i+3] == BLACK){
                        if( p_map[j][i-2] != BLACK && p_map[j][i+4] != BLACK && (i-2 >=0 && i+4 <= 14) ){//양쪽 모두 체크 - 중앙에 있음
                            printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( p_map[j][i-2] != BLACK && i+3 == 14){//좌측 체크 (우측은 이미 끝에 도달)
                            printf("\n 1-4 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( p_map[j][i+4] != BLACK && i -1 == 0 ){//우측 체크
                            printf("\n 1-5 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if(i-2 >=0 && i+2 <=14){// 가로 - B  B N B B
                    if(p_map[j][i-2] == BLACK && p_map[j][i-1] == BLACK && p_map[j][i+1] == BLACK && p_map[j][i+2] == BLACK ){
                        if( p_map[j][i-3] != BLACK && p_map[j][i+3] != BLACK && i+3 <= 14 && i-3 >= 0){
                            printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( p_map[j][i+3] != BLACK && i - 2 == 0){//좌측에 붙어있음 -> 우측만 검사
                            printf("\n 1-7 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( p_map[j][i-3] != BLACK && i + 2 == 14){//우측에 붙어 있음 -> 좌측만 검사
                            printf("\n 1-8 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if( i-3 >=0 && i+1 <= 14){// 가로 - B B  B N B
                    if(p_map[j][i-3] == BLACK && p_map[j][i-2] == BLACK && p_map[j][i-1] == BLACK && p_map[j][i+1] == BLACK){
                        if( p_map[j][i+2] != BLACK && p_map[j][i-4] != BLACK && i+2 <= 14 && i-4 >= 0){
                            printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if ( p_map[j][i+2] !=BLACK && i -3 == 0){//좌측에 붙음 -> 우측만 검사
                            printf("\n 1-10 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( p_map[j][i-4] != BLACK && i+1 == 14){//우측에 붙음 -> 좌측만 검사
                            printf("\n 1-11 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if( i-4 >= 0){// 가로 - B B B B N
                    if(p_map[j][i-4] == BLACK && p_map[j][i-3] == BLACK && p_map[j][i-2] == BLACK && p_map[j][i-1] == BLACK){
                        if(i == 14){//이미 끝에 도달 - 검사할것 없음(원래는 우측 검사)
                            printf("\n 1-12 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( p_map[j][i+1] != BLACK && i != 14){//우측 검사
                            printf("\n 1-13 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                //// - 세로
                if(j+4 <= 14){ // 세로 - N B B B B
                    if(p_map[j+1][i] == BLACK && p_map[j+2][i] == BLACK && p_map[j+3][i] == BLACK && p_map[j+4][i] == BLACK){
                        if( p_map[j-1][i]  != BLACK && j-1>=0)//상단 검사 할거리 있을 경우
                        {
                            printf("\n 2-1 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                        else if( j== 0)//상단에 붙어있음 - 검사 할거리 없음
                        {   //push(j,i);
                            printf("\n 2-2 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if(j-1 >= 0 && j+3 <=14){// 세로 - B N B B B
                    if(p_map[j-1][i] == BLACK && p_map[j+1][i] == BLACK && p_map[j+2][i] == BLACK && p_map[j+3][i] == BLACK){
                        if( p_map[j-2][i] != BLACK && p_map[j+4][i] != BLACK && (j-2 >=0 && j+4 <= 14) ){//양쪽 모두 체크 - 중앙에 있음
                            printf("\n 2-3 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( p_map[j-2][i] != BLACK && j+3 == 14){//상단 체크 (하단은 이미 끝에 도달)
                            printf("\n 2-4 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( p_map[j+4][i] != BLACK && j -1 == 0 ){//하단 체크 - 상단은 이미 상단에 도달
                            printf("\n 2-5 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if(j-2 >=0 && j+2 <=14){// 세로 - B  B N B B
                    if(p_map[j-2][i] == BLACK && p_map[j-1][i] == BLACK && p_map[j+1][i] == BLACK && p_map[j+2][i] == BLACK ){
                        if( p_map[j-3][i] != BLACK && p_map[j+3][i] != BLACK && j+3 <= 14 && j-3 >= 0){
                            printf("\n 2-6 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( p_map[j+3][i] != BLACK && j - 2 == 0){//상단에 붙어 있을 경우 -> 하단만 검사
                            printf("\n 2-7 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( p_map[j-3][i] != BLACK && j + 2 == 14){//하단에 붙어 있을경우 -> 상단만 검사
                            printf("\n 2-8 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if( j-3 >=0 && j+1 <= 14){// 세로 - B B  B N B
                    if(p_map[j-3][i] == BLACK && p_map[j-2][i] == BLACK && p_map[j-1][i] == BLACK && p_map[j+1][i] == BLACK){
                        if( p_map[j+2][i] != BLACK && p_map[j-4][i] != BLACK && j+2 <= 14 && j-4 >= 0){
                            printf("\n 2-9 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if ( p_map[j+2][i] !=BLACK && j -3 == 0){//상단에 붙음 - 하단만 검사
                            printf("\n 2-10 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( p_map[j-4][i] != BLACK && j+1 == 14){//하단에 붙음 - 상단만 검사
                            printf("\n 2-11 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if( j-4 >= 0){// 세로 - B B B B N
                    if(p_map[j-4][i] == BLACK && p_map[j-3][i] == BLACK && p_map[j-2][i] == BLACK && p_map[j-1][i] == BLACK){
                        if(j == 14){//이미 끝에 도달 - 굳이 상단 검사할 필요없음 - 5개여서
                            printf("\n 2-12 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( p_map[j+1][i] != BLACK && j != 14){//하단 검사
                            printf("\n 2-13 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                // Dia 1 - "\"
                if( i+4 <= 14 && j+4 <= 14){ // dia1 - N B B B B
                    if(p_map[j+1][i+1] == BLACK && p_map[j+2][i+2] == BLACK && p_map[j+3][i+3] == BLACK && p_map[j+4][i+4] == BLACK){
                        if( p_map[j-1][i-1] != BLACK && j-1>=0 && i-1>=0)//우측에 있으면 이미 5개임 -> 검사할 필요 없음 - 좌측만 돌 없으면 4
                        {
                            printf("\n 3-1 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                        else if( i == 0 || j== 0)//좌측에 달라 붙어 있을경우 - 검사 필요 없음
                        {   //push(j,i);
                            printf("\n 3-2 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if(i-1 >= 0 && i+3 <=14 && j-1 >= 0 && j+3 <=14){// dia1 - B N B B B
                    if(p_map[j-1][i-1] == BLACK && p_map[j+1][i+1] == BLACK && p_map[j+2][i+2] == BLACK && p_map[j+3][i+3] == BLACK){
                        if( p_map[j-2][i-2] != BLACK && p_map[j+4][i+4] != BLACK && (i-2 >=0 && i+4 <= 14) && (j-2 >=0 && j+4 <= 14) ){//양쪽 모두 체큰 - 중앙에 있음
                            printf("\n 3-3 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( p_map[j-2][i-2] != BLACK && (i+3 == 14 || j+3 == 14)){//좌측 체크 (우측은 이미 끝에 도달)
                            printf("\n 3-4 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( p_map[j+4][i+4] != BLACK && (i -1 == 0  || j -1 == 0) ){//우측 체크
                            printf("\n 3-5 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if(i-2 >=0 && i+2 <=14 && j-2 >=0 && j+2 <=14){// dia1 - B  B N B B
                    if(p_map[j-2][i-2] == BLACK && p_map[j-1][i-1] == BLACK && p_map[j+1][i+1] == BLACK && p_map[j+2][i+2] == BLACK ){
                        if( p_map[j-3][i-3] != BLACK && p_map[j+3][i+3] != BLACK && i+3 <= 14 && i-3 >= 0 && j+3 <= 14 && j-3 >= 0){
                            printf("\n 3-6 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( p_map[j+3][i+3] != BLACK && (i - 2 == 0 || j - 2 == 0)){
                            printf("\n 3-7 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( p_map[j-3][i-3] != BLACK && (i + 2 == 14 || j + 2 == 14)){
                            printf("\n 3-8 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if( i-3 >=0 && i+1 <= 14 && j-3 >=0 && j+1 <= 14){// dia1 - B B  B N B
                    if(p_map[j-3][i-3] == BLACK && p_map[j-2][i-2] == BLACK && p_map[j-1][i-1] == BLACK && p_map[j+1][i+1] == BLACK){
                        if( p_map[j+2][i+2] != BLACK && p_map[j-4][i-4] != BLACK && i+2 <= 14 && i-4 >= 0 && j+2 <= 14 && j-4 >= 0){
                            printf("\n 3-9 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if ( p_map[j+2][i+2] !=BLACK && (i -3 == 0 || j -3 == 0)){
                            printf("\n 3-10 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( p_map[j-4][i-4] != BLACK && (i+1 == 14 || j+1 == 14)){
                            printf("\n 3-11 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if( i-4 >= 0 && j-4 >= 0){// dia1 - B B B B N
                    if(p_map[j-4][i-4] == BLACK && p_map[j-3][i-3] == BLACK && p_map[j-2][i-2] == BLACK && p_map[j-1][i-1] == BLACK){
                        if( i == 14 || j == 14){//이미 끝에 도달 -- 좌측 검사할 필요 없음(5개니까) - 우측 검사할 칸 없음
                            printf("\n 3-12 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( p_map[j+1][i+1] != BLACK && i != 14 && j != 14){
                            printf("\n 3-13 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                // DIa 2 - /
                if( j-4 >=0 && i+4 <= 14){ // dia2 - N B B B B
                    if(p_map[j-1][i+1] == BLACK && p_map[j-2][i+2] == BLACK && p_map[j-3][i+3] == BLACK && p_map[j-4][i+4] == BLACK){
                        if( p_map[j+1][i-1]  != BLACK && j+1<=14 && i-1>=0) // 좌측 검사 - 좌측이 있을 경우
                        {
                            printf("\n 4-1 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                        else if( j == 14 || i == 0)//ㄴ 라인
                        {   //push(j,i);
                            printf("\n 4-2 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if( j-3 >= 0 && j+1 <=14 && i-1 >= 0 && i+3 <=14){// dia2 - B N B B B
                    if(p_map[j+1][i-1] == BLACK && p_map[j-1][i+1] == BLACK && p_map[j-2][i+2] == BLACK && p_map[j-3][i+3] == BLACK){
                        if( p_map[j+2][i-2] != BLACK && p_map[j-4][i+4] != BLACK &&
                                (i-2 >=0 && i+4 <= 14) && (j-4 >=0 && j+2 <= 14) ){//양쪽 모두 체큰 - 중앙에 있음
                            printf("\n 4-3 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( p_map[j+2][i-2] != BLACK  && (i+3 == 14 || j-3 == 0)){//좌측 체크 (우측은 이미 끝에 도달) ㄱ 형태
                            printf("\n 4-4 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( p_map[j-4][i+4] != BLACK && (j + 1 == 14 || i -1 == 0 )){//우측 체크 ㄴ 형태
                            printf("\n 4-5 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if(j-2 >=0 && j+2 <=14 && i-2 >=0 && i+2 <=14){// dia2 - B  B N B B
                    if(p_map[j+2][i-2] == BLACK && p_map[j+1][i-1] == BLACK && p_map[j-1][i+1] == BLACK && p_map[j-2][i+2] == BLACK ){
                        if( p_map[j+3][i-3] != BLACK && p_map[j-3][i+3] != BLACK &&
                                (i-3 >=0 && i+3 <=14 ) && (j-3 >=0 && j+3 <= 14)){
                            printf("\n 4-6find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( p_map[j+3][i-3] != BLACK && ( j == 2 || i == 12)){//하단 검사
                            printf("\n 4-7 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( p_map[j-3][i+3] != BLACK && ( j == 12 || i == 2)){//상단 검사
                            printf("\n 4-8 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if( j+3 <= 14 && i-3 >=0 && j-1 >=0 && i+1 <= 14){// dia2 - B B  B N B
                    if(p_map[j+3][i-3] == BLACK && p_map[j+2][i-2] == BLACK && p_map[j+1][i-1] == BLACK && p_map[j-1][i+1] == BLACK){
                        if( p_map[j+4][i-4] != BLACK && p_map[j-2][i+2] != BLACK &&
                                (j+4 <= 14 && i-4>=0) && (j-2 >=0 && i+2 <= 14)){// 2<=j<= 10   4<=i<=12
                            printf("\n 4-9 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if ( p_map[j+4][i-4] !=BLACK && (j == 1 || i == 13)){
                            printf("\n 4-10 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( p_map[j-2][i+2] != BLACK && (j == 11 || i == 3)){
                            printf("\n 4-11 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if( j+4 <= 14 && i-4 >= 0){// dia2 - B B B B N
                    if(p_map[j+4][i-4] == BLACK && p_map[j+3][i-3] == BLACK && p_map[j+2][i-2] == BLACK && p_map[j+1][i-1] == BLACK){
                        if(p_map[j-1][i+1] !=BLACK && (j-1>=0 && i+1<=14)){//우측 검사 - 우측이 있을 경우
                            printf("\n 4-12 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( j == 0 || i == 14){// 검사 필요 없음
                            printf("\n 4-13 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
            }
        }
    }
     printf("\n **** ENd B4******");
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
     for(int j = 0; j < 15; j++){
         for(int i =0; i < 15; i++){
             if(p_map[j][i] == PAN){//only PAN - Black cannot put NON
                 if(i+3 <= 14){// 가로 - (N) <N> B B B (N)
                     if(p_map[j][i+1] == BLACK && p_map[j][i+2] == BLACK && p_map[j][i+3] == BLACK){
                         if( p_map[j][i-1] == PAN && p_map[j][i+4] == PAN && i+4 <= 14 && i-1>=0) // 좌 우측 검사
                         {
                             printf("\n 1-1 find connect 4 - j = %d , i = %d   ",j,i);
                         }
                     }
                 }
                 if(i-1 >= 0 && i+2 <=14){// 가로 - (N) B <N> B B (N)
                     if(p_map[j][i-1] == BLACK && p_map[j][i+1] == BLACK && p_map[j][i+2] == BLACK){
                         if( p_map[j][i-2] == PAN && p_map[j][i+3] == PAN && (i-2 >=0 && i+3 <= 14) ){//양쪽 모두 체크 - 중앙에 있음
                             printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                         }
                     }
                 }
                 if(i-2 >=0 && i+1 <=14){// 가로 - (N) B  B <N> B (N)
                     if(p_map[j][i-2] == BLACK && p_map[j][i-1] == BLACK && p_map[j][i+1] == BLACK){
                         if( p_map[j][i-3] == PAN && p_map[j][i+2] == PAN && i+2 <= 14 && i-3 >= 0){
                             printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                         }
                     }
                 }
                 if( i-3 >=0 ){// 가로 - (N) B B  B <N> (N)
                     if(p_map[j][i-3] == BLACK && p_map[j][i-2] == BLACK && p_map[j][i-1] == BLACK){
                         if( p_map[j][i-4] == PAN && p_map[j][i+1] == PAN && i+1 <= 14 && i-4 >= 0){
                             printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                         }
                     }
                 }
                 //// - 세로
                 if(j+3 <= 14){// 세로 - (N) <N> B B B (N)
                     if(p_map[j+1][i] == BLACK && p_map[j+2][i] == BLACK && p_map[j+3][i] == BLACK){
                         if( p_map[j-1][i] == PAN && p_map[j+4][i] == PAN && j+4 <= 14 && j-1>=0) // 좌 우측 검사
                         {
                             printf("\n 1-1 find connect 4 - j = %d , i = %d   ",j,i);
                         }
                     }
                 }
                 if(j-1 >= 0 && j+2 <=14){// 세로 - (N) B <N> B B (N)
                     if(p_map[j-1][i] == BLACK && p_map[j+1][i] == BLACK && p_map[j+2][i] == BLACK){
                         if( p_map[j-2][i] == PAN && p_map[j+3][i] == PAN && (j-2 >=0 && j+3 <= 14) ){//양쪽 모두 체크 - 중앙에 있음
                             printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                         }
                     }
                 }
                 if(j-2 >=0 && j+1 <=14){// 세로 - (N) B  B <N> B (N)
                     if(p_map[j-2][i] == BLACK && p_map[j-1][i] == BLACK && p_map[j+1][i] == BLACK){
                         if( p_map[j-3][i] == PAN && p_map[j+2][i] == PAN && j+2 <= 14 && j-3 >= 0){
                             printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                         }
                     }
                 }
                 if( j-3 >=0){// 세로 - (N) B B  B <N> (N)
                     if(p_map[j-3][i] == BLACK && p_map[j-2][i] == BLACK && p_map[j-1][i] == BLACK){
                         if( p_map[j-4][i] == PAN && p_map[j+1][i] == PAN && j+1 <= 14 && j-4 >= 0){
                             printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                         }
                     }
                 }
                 // Dia 1 - "\"
                 if(i+1 <= 14 && j+3 <= 14){// Dia 1 - (N) <N> B B B (N)
                     if(p_map[j+1][i+1] == BLACK && p_map[j+2][i+2] == BLACK && p_map[j+3][i+3] == BLACK){
                         if( p_map[j-1][i-1] == PAN && p_map[j+4][i+4] == PAN && j+4 <= 14 && j-1>=0 && i+4 <= 14 && i-1>=0) // 좌 우측 검사
                         {
                             printf("\n 1-1 find connect 4 - j = %d , i = %d   ",j,i);
                         }
                     }
                 }
                 if( i-1 >= 0 && i+2 <=14 && j-1 >= 0 && j+2 <=14){// Dia 1 - (N) B <N> B B (N)
                     if(p_map[j-1][i-1] == BLACK && p_map[j+1][i+1] == BLACK && p_map[j+2][i+2] == BLACK){
                         if( p_map[j-2][i-2] == PAN && p_map[j+3][i+3] == PAN && (j-2 >=0 && j+3 <= 14) && (i-2 >=0 && i+3 <= 14) ){//양쪽 모두 체크 - 중앙에 있음
                             printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                         }
                     }
                 }
                 if(i-2 >=0 && i+1 <=14 && j-2 >=0 && j+1 <=14){// Dia 1 - (N) B  B <N> B (N)
                     if(p_map[j-2][i-2] == BLACK && p_map[j-1][i-1] == BLACK && p_map[j+1][i+1] == BLACK){
                         if( p_map[j-3][i-3] == PAN && p_map[j+2][i+2] == PAN && j+2 <= 14 && j-3 >= 0 && i+2 <= 14 && i-3 >= 0){
                             printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                         }
                     }
                 }
                 if( i-3 >=0 && j-3 >=0){// Dia 1 - (N) B B  B <N> (N)
                     if(p_map[j-3][i-3] == BLACK && p_map[j-2][i-2] == BLACK && p_map[j-1][i-1] == BLACK){
                         if( p_map[j-4][i-4] == PAN && p_map[j+1][i+1] == PAN && j+1 <= 14 && j-4 >= 0 && i+1 <= 14 && i-4 >= 0){
                             printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                         }
                     }
                 }

                 // DIa 2 - /
                 if(i+3 <= 14 && j-3 >=0 ){// DIa 2 - (N) <N> B B B (N)
                     if(p_map[j-1][i+1] == BLACK && p_map[j-2][i+2] == BLACK && p_map[j-3][i+3] == BLACK){
                         if( p_map[j+1][i-1] == PAN && p_map[j-4][i+4] == PAN && (j+1<=14 && j-4>=0) && (i+4<=14 && i-1>=0)) // 좌 우측 검사
                         {
                             printf("\n 1-1 find connect 4 - j = %d , i = %d   ",j,i);
                         }
                     }
                 }
                 if( i-1>=0 && i+2<=14 && j-2>=0 && j+1<=14 ){// Dia 2 - (N) B <N> B B (N)
                     if(p_map[j+1][i-1] == BLACK && p_map[j-1][i+1] == BLACK && p_map[j-2][i+2] == BLACK){
                         if( p_map[j+2][i-2] == PAN && p_map[j-3][i+3] == PAN && (j-3 >=0 && j+2 <= 14) && (i-2 >=0 && i+3 <= 14) ){//양쪽 모두 체크 - 중앙에 있음
                             printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                         }
                     }
                 }
                 if(i-2 >=0 && i+1 <=14 && j+2 >=0 && j-1 <=14){// Dia 2 - (N) B  B <N> B (N)
                     if(p_map[j+2][i-2] == BLACK && p_map[j+1][i-1] == BLACK && p_map[j-1][i+1] == BLACK){
                         if( p_map[j+3][i-3] == PAN && p_map[j-2][i+2] == PAN && j+3 <= 14 && j-2 >= 0 && i+2 <= 14 && i-3 >= 0){
                             printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                         }
                     }
                 }
                 if( i-3 >=0 && j+3 <= 14){// Dia 2 - (N) B B  B <N> (N)
                     if(p_map[j+3][i-3] == BLACK && p_map[j+2][i-2] == BLACK && p_map[j+1][i-1] == BLACK){
                         if( p_map[j+4][i-4] == PAN && p_map[j-1][i+1] == PAN && j+4 <= 14 && j-1 >= 0 && i+1 <= 14 && i-4 >= 0){
                             printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                         }
                     }
                 }
                 //
             }
         }
     }
      printf("\n **** ENd Full B3******");

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
     for(int j = 0; j < 15; j++){
         for(int i =0; i < 15; i++){
             if(p_map[j][i] == PAN || p_map[j][i] == NON){//only PAN, NON - White can put NON
                 if(i+3 <= 14){// 가로 - (N) <N> B B B (N)
                     if(p_map[j][i+1] == WHITE && p_map[j][i+2] == WHITE && p_map[j][i+3] == WHITE){
                         if( p_map[j][i-1] == PAN && p_map[j][i+4] == PAN && i+4 <= 14 && i-1>=0) // 좌 우측 검사
                         {
                             printf("\n 1-1 find connect 4 - j = %d , i = %d   ",j,i);
                         }
                     }
                 }
                 if(i-1 >= 0 && i+2 <=14){// 가로 - (N) B <N> B B (N)
                     if(p_map[j][i-1] == WHITE && p_map[j][i+1] == WHITE && p_map[j][i+2] == WHITE){
                         if( p_map[j][i-2] == PAN && p_map[j][i+3] == PAN && (i-2 >=0 && i+3 <= 14) ){//양쪽 모두 체크 - 중앙에 있음
                             printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                         }
                     }
                 }
                 if(i-2 >=0 && i+1 <=14){// 가로 - (N) B  B <N> B (N)
                     if(p_map[j][i-2] == WHITE && p_map[j][i-1] == WHITE && p_map[j][i+1] == WHITE){
                         if( p_map[j][i-3] == PAN && p_map[j][i+2] == PAN && i+2 <= 14 && i-3 >= 0){
                             printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                         }
                     }
                 }
                 if( i-3 >=0 ){// 가로 - (N) B B  B <N> (N)
                     if(p_map[j][i-3] == WHITE && p_map[j][i-2] == WHITE && p_map[j][i-1] == WHITE){
                         if( p_map[j][i-4] == PAN && p_map[j][i+1] == PAN && i+1 <= 14 && i-4 >= 0){
                             printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                         }
                     }
                 }
                 //// - 세로
                 if(j+3 <= 14){// 세로 - (N) <N> B B B (N)
                     if(p_map[j+1][i] == WHITE && p_map[j+2][i] == WHITE && p_map[j+3][i] == WHITE){
                         if( (p_map[j-1][i] == PAN || p_map[j-1][i] == NON) && (p_map[j+4][i] == PAN || p_map[j+4][i] == NON) && j+4 <= 14 && j-1>=0) // 좌 우측 검사
                         {
                             printf("\n 1-1 find connect 4 - j = %d , i = %d   ",j,i);
                         }
                     }
                 }
                 if(j-1 >= 0 && j+2 <=14){// 세로 - (N) B <N> B B (N)
                     if(p_map[j-1][i] == WHITE && p_map[j+1][i] == WHITE && p_map[j+2][i] == WHITE){
                         if( ( p_map[j-2][i] == NON || p_map[j-2][i] == PAN) && (p_map[j+3][i] == PAN || p_map[j+3][i] == NON) && (j-2 >=0 && j+3 <= 14) ){//양쪽 모두 체크 - 중앙에 있음
                             printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                         }
                     }
                 }
                 if(j-2 >=0 && j+1 <=14){// 세로 - (N) B  B <N> B (N)
                     if(p_map[j-2][i] == WHITE && p_map[j-1][i] == WHITE && p_map[j+1][i] == WHITE){
                         if( (p_map[j-3][i] == PAN || p_map[j-3][i] == NON) && (  p_map[j+2][i] == NON ||p_map[j+2][i] == PAN) && j+2 <= 14 && j-3 >= 0){
                             printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                         }
                     }
                 }
                 if( j-3 >=0){// 세로 - (N) B B  B <N> (N)
                     if(p_map[j-3][i] == WHITE && p_map[j-2][i] == WHITE && p_map[j-1][i] == WHITE){
                         if( (p_map[j-4][i] == PAN || p_map[j-4][i] == NON) && (p_map[j+1][i] == PAN || p_map[j+1][i] == NON)&& j+1 <= 14 && j-4 >= 0){
                             printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                         }
                     }
                 }
                 // Dia 1 - "\"
                 if(i+1 <= 14 && j+3 <= 14){// Dia 1 - (N) <N> B B B (N)
                     if(p_map[j+1][i+1] == WHITE && p_map[j+2][i+2] == WHITE && p_map[j+3][i+3] == WHITE){
                         if( (p_map[j-1][i-1] == PAN || p_map[j-1][i-1] == NON) && (p_map[j+4][i+4] == PAN || p_map[j+4][i+4] == NON) && j+4 <= 14 && j-1>=0 && i+4 <= 14 && i-1>=0) // 좌 우측 검사
                         {
                             printf("\n 1-1 find connect 4 - j = %d , i = %d   ",j,i);
                         }
                     }
                 }
                 if( i-1 >= 0 && i+2 <=14 && j-1 >= 0 && j+2 <=14){// Dia 1 - (N) B <N> B B (N)
                     if(p_map[j-1][i-1] == WHITE && p_map[j+1][i+1] == WHITE && p_map[j+2][i+2] == WHITE){
                         if( (p_map[j-2][i-2] == PAN || p_map[j-2][i-2] == NON) && (p_map[j+3][i+3] == PAN || p_map[j+3][i+3] == NON) && (j-2 >=0 && j+3 <= 14) && (i-2 >=0 && i+3 <= 14) ){//양쪽 모두 체크 - 중앙에 있음
                             printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                         }
                     }
                 }
                 if(i-2 >=0 && i+1 <=14 && j-2 >=0 && j+1 <=14){// Dia 1 - (N) B  B <N> B (N)
                     if(p_map[j-2][i-2] == WHITE && p_map[j-1][i-1] == WHITE && p_map[j+1][i+1] == WHITE){
                         if( (p_map[j-3][i-3] == PAN || p_map[j-3][i-3] == NON) && (p_map[j+2][i+2] == PAN || p_map[j+2][i+2] == NON) && j+2 <= 14 && j-3 >= 0 && i+2 <= 14 && i-3 >= 0){
                             printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                         }
                     }
                 }
                 if( i-3 >=0 && j-3 >=0){// Dia 1 - (N) B B  B <N> (N)
                     if(p_map[j-3][i-3] == WHITE && p_map[j-2][i-2] == WHITE && p_map[j-1][i-1] == WHITE){
                         if( (p_map[j-4][i-4] == PAN || p_map[j-4][i-4] == NON) && (p_map[j+1][i+1] == PAN || p_map[j+1][i+1] == NON) && j+1 <= 14 && j-4 >= 0 && i+1 <= 14 && i-4 >= 0){
                             printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                         }
                     }
                 }

                 // DIa 2 - /
                 if(i+3 <= 14 && j-3 >=0 ){// DIa 2 - (N) <N> B B B (N)
                     if(p_map[j-1][i+1] == WHITE && p_map[j-2][i+2] == WHITE && p_map[j-3][i+3] == WHITE){
                         if( (p_map[j+1][i-1] == PAN || p_map[j+1][i-1] == NON) && (p_map[j-4][i+4] == PAN || p_map[j-4][i+4] == NON) && (j+1<=14 && j-4>=0) && (i+4<=14 && i-1>=0)) // 좌 우측 검사
                         {
                             printf("\n 1-1 find connect 4 - j = %d , i = %d   ",j,i);
                         }
                     }
                 }
                 if( i-1>=0 && i+2<=14 && j-2>=0 && j+1<=14 ){// Dia 2 - (N) B <N> B B (N)
                     if(p_map[j+1][i-1] == WHITE && p_map[j-1][i+1] == WHITE && p_map[j-2][i+2] == WHITE){
                         if( (p_map[j+2][i-2] == PAN || p_map[j+2][i-2] == NON) && (p_map[j-3][i+3] == PAN || p_map[j-3][i+3] == NON) && (j-3 >=0 && j+2 <= 14) && (i-2 >=0 && i+3 <= 14) ){//양쪽 모두 체크 - 중앙에 있음
                             printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                         }
                     }
                 }
                 if(i-2 >=0 && i+1 <=14 && j+2 >=0 && j-1 <=14){// Dia 2 - (N) B  B <N> B (N)
                     if(p_map[j+2][i-2] == WHITE && p_map[j+1][i-1] == WHITE && p_map[j-1][i+1] == WHITE){
                         if( (p_map[j+3][i-3] == PAN || p_map[j+3][i-3] == NON) && (p_map[j-2][i+2] == PAN || p_map[j-2][i+2] == NON) && j+3 <= 14 && j-2 >= 0 && i+2 <= 14 && i-3 >= 0){
                             printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                         }
                     }
                 }
                 if( i-3 >=0 && j+3 <= 14){// Dia 2 - (N) B B  B <N> (N)
                     if(p_map[j+3][i-3] == WHITE && p_map[j+2][i-2] == WHITE && p_map[j+1][i-1] == WHITE){
                         if( (p_map[j+4][i-4] == PAN || p_map[j+4][i-4] == NON) && (p_map[j-1][i+1] == PAN || p_map[j-1][i+1] == NON) && j+4 <= 14 && j-1 >= 0 && i+1 <= 14 && i-4 >= 0){
                             printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                         }
                     }
                 }
                 //
             }
         }
     }
      printf("\n **** ENd Full W3******");

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
                        }
                    }
                }
                if(i-1 >= 0 && i+2 <=14){// 가로 - (N) B <N> B B (N)
                    if(p_map[j][i-1] == BLACK && p_map[j][i+1] == BLACK && p_map[j][i+2] == BLACK){
                        if( (p_map[j][i-2] == WHITE || p_map[j][i-2] == NON) && (p_map[j][i+3] == WHITE || p_map[j][i+3] == NON)  && (i-2 >=0 && i+3 <= 14) ){//양쪽 모두 체크 - 중앙에 있음
                            //printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if(((p_map[j][i-2] == WHITE || p_map[j][i-2] == NON) || (p_map[j][i+3] == WHITE || p_map[j][i+3] == NON))  && (i-2 >=0 && i+3 <= 14)){
                            printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if(i-2 >=0 && i+1 <=14){// 가로 - (N) B  B <N> B (N)
                    if(p_map[j][i-2] == BLACK && p_map[j][i-1] == BLACK && p_map[j][i+1] == BLACK){
                        if( (p_map[j][i-3] == WHITE || p_map[j][i-3] == NON) && (p_map[j][i+2] == WHITE || p_map[j][i+2] == NON)  && i+2 <= 14 && i-3 >= 0){
                            //printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if(((p_map[j][i-3] == WHITE || p_map[j][i-3] == NON) || (p_map[j][i+2] == WHITE || p_map[j][i+2] == NON))  && i+2 <= 14 && i-3 >= 0){
                            printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if( i-3 >=0 ){// 가로 - (N) B B  B <N> (N)
                    if(p_map[j][i-3] == BLACK && p_map[j][i-2] == BLACK && p_map[j][i-1] == BLACK){
                        if( (p_map[j][i-4] == WHITE || p_map[j][i-4] == NON) && (p_map[j][i+1] == WHITE || p_map[j][i+1] == NON) && i+1 <= 14 && i-4 >= 0){
                            //printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if(((p_map[j][i-4] == WHITE || p_map[j][i-4] == NON) || (p_map[j][i+1] == WHITE || p_map[j][i+1] == NON)) && i+1 <= 14 && i-4 >= 0){
                            printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
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
                        }
                    }
                }
                if(j-1 >= 0 && j+2 <=14){// 세로 - (N) B <N> B B (N)
                    if(p_map[j-1][i] == BLACK && p_map[j+1][i] == BLACK && p_map[j+2][i] == BLACK){
                        if( (p_map[j-2][i] == WHITE || p_map[j-2][i] == NON) && (p_map[j+3][i] == WHITE || p_map[j+3][i] == NON) && (j-2 >=0 && j+3 <= 14) ){//양쪽 모두 체크 - 중앙에 있음
                            //printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if(((p_map[j-2][i] == WHITE || p_map[j-2][i] == NON) || (p_map[j+3][i] == WHITE || p_map[j+3][i] == NON)) && (j-2 >=0 && j+3 <= 14)){
                            printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if(j-2 >=0 && j+1 <=14){// 세로 - (N) B  B <N> B (N)
                    if(p_map[j-2][i] == BLACK && p_map[j-1][i] == BLACK && p_map[j+1][i] == BLACK){
                        if( (p_map[j-3][i] == WHITE || p_map[j-3][i] == NON)  && (p_map[j+2][i] == WHITE || p_map[j+2][i] == NON) && j+2 <= 14 && j-3 >= 0){
                            //printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if(((p_map[j-3][i] == WHITE || p_map[j-3][i] == NON)  || (p_map[j+2][i] == WHITE || p_map[j+2][i] == NON)) && j+2 <= 14 && j-3 >= 0){
                            printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if( j-3 >=0){// 세로 - (N) B B  B <N> (N)
                    if(p_map[j-3][i] == BLACK && p_map[j-2][i] == BLACK && p_map[j-1][i] == BLACK){
                        if( (p_map[j-4][i] == WHITE || p_map[j-4][i] == NON) && (p_map[j+1][i] == WHITE || p_map[j+1][i] == NON) && j+1 <= 14 && j-4 >= 0){
                            //printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if(((p_map[j-4][i] == WHITE || p_map[j-4][i] == NON) || (p_map[j+1][i] == WHITE || p_map[j+1][i] == NON)) && j+1 <= 14 && j-4 >= 0){
                            printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
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
                        }
                    }
                }
                if( i-1 >= 0 && i+2 <=14 && j-1 >= 0 && j+2 <=14){// Dia 1 - (N) B <N> B B (N)
                    if(p_map[j-1][i-1] == BLACK && p_map[j+1][i+1] == BLACK && p_map[j+2][i+2] == BLACK){
                        if( (p_map[j-2][i-2] == WHITE || p_map[j-2][i-2] == NON) && (p_map[j+3][i+3] == WHITE || p_map[j+3][i+3] == NON) && (j-2 >=0 && j+3 <= 14) && (i-2 >=0 && i+3 <= 14) ){//양쪽 모두 체크 - 중앙에 있음

                        }else if( ((p_map[j-2][i-2] == WHITE || p_map[j-2][i-2] == NON) || (p_map[j+3][i+3] == WHITE || p_map[j+3][i+3] == NON)) && (j-2 >=0 && j+3 <= 14) && (i-2 >=0 && i+3 <= 14) ){
                            printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }//
                }
                if(i-2 >=0 && i+1 <=14 && j-2 >=0 && j+1 <=14){// Dia 1 - (N) B  B <N> B (N)
                    if(p_map[j-2][i-2] == BLACK && p_map[j-1][i-1] == BLACK && p_map[j+1][i+1] == BLACK){
                        if( (p_map[j-3][i-3] == WHITE || p_map[j-3][i-3] == NON) && (p_map[j+2][i+2] == WHITE || p_map[j+2][i+2] == NON) && j+2 <= 14 && j-3 >= 0 && i+2 <= 14 && i-3 >= 0){

                        }else if(((p_map[j-3][i-3] == WHITE || p_map[j-3][i-3] == NON) || (p_map[j+2][i+2] == WHITE || p_map[j+2][i+2] == NON)) && j+2 <= 14 && j-3 >= 0 && i+2 <= 14 && i-3 >= 0){
                            printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if( i-3 >=0 && j-3 >=0){// Dia 1 - (N) B B  B <N> (N)
                    if(p_map[j-3][i-3] == BLACK && p_map[j-2][i-2] == BLACK && p_map[j-1][i-1] == BLACK){
                        if( (p_map[j-4][i-4] == WHITE || p_map[j-4][i-4] == NON) && (p_map[j+1][i+1] == WHITE || p_map[j+1][i+1] == NON) && j+1 <= 14 && j-4 >= 0 && i+1 <= 14 && i-4 >= 0){

                        }else if(((p_map[j-4][i-4] == WHITE || p_map[j-4][i-4] == NON) || (p_map[j+1][i+1] == WHITE || p_map[j+1][i+1] == NON)) && j+1 <= 14 && j-4 >= 0 && i+1 <= 14 && i-4 >= 0){
                            printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
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
                        }
                    }
                }
                if( i-1>=0 && i+2<=14 && j-2>=0 && j+1<=14 ){// Dia 2 - (N) B <N> B B (N)
                    if(p_map[j+1][i-1] == BLACK && p_map[j-1][i+1] == BLACK && p_map[j-2][i+2] == BLACK){
                        if( (p_map[j+2][i-2] == WHITE || p_map[j+2][i-2] == NON) && (p_map[j-3][i+3] == WHITE || p_map[j-3][i+3] == NON) && (j-3 >=0 && j+2 <= 14) && (i-2 >=0 && i+3 <= 14) ){//양쪽 모두 체크 - 중앙에 있음

                        }else if( ((p_map[j+2][i-2] == WHITE || p_map[j+2][i-2] == NON) || (p_map[j-3][i+3] == WHITE || p_map[j-3][i+3] == NON)) && (j-3 >=0 && j+2 <= 14) && (i-2 >=0 && i+3 <= 14) ){
                            printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if(i-2 >=0 && i+1 <=14 && j+2 >=0 && j-1 <=14){// Dia 2 - (N) B  B <N> B (N)
                    if(p_map[j+2][i-2] == BLACK && p_map[j+1][i-1] == BLACK && p_map[j-1][i+1] == BLACK){
                        if( (p_map[j+3][i-3] == WHITE || p_map[j+3][i-3] == NON) && (p_map[j-2][i+2] == WHITE || p_map[j-2][i+2] == NON) && j+3 <= 14 && j-2 >= 0 && i+2 <= 14 && i-3 >= 0){

                        }else if(((p_map[j+3][i-3] == WHITE || p_map[j+3][i-3] == NON) || (p_map[j-2][i+2] == WHITE || p_map[j-2][i+2] == NON)) && j+3 <= 14 && j-2 >= 0 && i+2 <= 14 && i-3 >= 0){
                            printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if( i-3 >=0 && j+3 <= 14){// Dia 2 - (N) B B  B <N> (N)
                    if(p_map[j+3][i-3] == BLACK && p_map[j+2][i-2] == BLACK && p_map[j+1][i-1] == BLACK){
                        if( (p_map[j+4][i-4] == WHITE || p_map[j+4][i-4] == NON) && (p_map[j-1][i+1] == WHITE || p_map[j-1][i+1] == NON) && j+4 <= 14 && j-1 >= 0 && i+1 <= 14 && i-4 >= 0){

                        }else if(((p_map[j+4][i-4] == WHITE || p_map[j+4][i-4] == NON) || (p_map[j-1][i+1] == WHITE || p_map[j-1][i+1] == NON)) && j+4 <= 14 && j-1 >= 0 && i+1 <= 14 && i-4 >= 0){
                            printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                //
            }
        }
    }
      printf("\n **** ENd Half B3******");

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
                        }
                    }
                }
                if(i-1 >= 0 && i+2 <=14){// 가로 - (N) B <N> B B (N)
                    if(p_map[j][i-1] == WHITE && p_map[j][i+1] == WHITE && p_map[j][i+2] == WHITE){
                        if( (p_map[j][i-2] == BLACK ) && (p_map[j][i+3] == BLACK )  && (i-2 >=0 && i+3 <= 14) ){//양쪽 모두 체크 - 중앙에 있음
                            //printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if(((p_map[j][i-2] == BLACK ) || (p_map[j][i+3] == BLACK))  && (i-2 >=0 && i+3 <= 14)){
                            printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if(i-2 >=0 && i+1 <=14){// 가로 - (N) B  B <N> B (N)
                    if(p_map[j][i-2] == WHITE && p_map[j][i-1] == WHITE && p_map[j][i+1] == WHITE){
                        if( (p_map[j][i-3] == BLACK ) && (p_map[j][i+2] == BLACK)  && i+2 <= 14 && i-3 >= 0){
                            //printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if(((p_map[j][i-3] == BLACK) || (p_map[j][i+2] == BLACK))  && i+2 <= 14 && i-3 >= 0){
                            printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if( i-3 >=0 ){// 가로 - (N) B B  B <N> (N)
                    if(p_map[j][i-3] == WHITE && p_map[j][i-2] == WHITE && p_map[j][i-1] == WHITE){
                        if( (p_map[j][i-4] == BLACK) && (p_map[j][i+1] == BLACK) && i+1 <= 14 && i-4 >= 0){
                            //printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if(((p_map[j][i-4] == BLACK) || (p_map[j][i+1] == BLACK)) && i+1 <= 14 && i-4 >= 0){
                            printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
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
                        }
                    }
                }
                if(j-1 >= 0 && j+2 <=14){// 세로 - (N) B <N> B B (N)
                    if(p_map[j-1][i] == WHITE && p_map[j+1][i] == WHITE && p_map[j+2][i] == WHITE){
                        if( (p_map[j-2][i] == BLACK) && (p_map[j+3][i] == BLACK ) && (j-2 >=0 && j+3 <= 14) ){//양쪽 모두 체크 - 중앙에 있음
                            //printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if(((p_map[j-2][i] == BLACK) || (p_map[j+3][i] == BLACK )) && (j-2 >=0 && j+3 <= 14)){
                            printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if(j-2 >=0 && j+1 <=14){// 세로 - (N) B  B <N> B (N)
                    if(p_map[j-2][i] == WHITE && p_map[j-1][i] == WHITE && p_map[j+1][i] == WHITE){
                        if( (p_map[j-3][i] == BLACK)  && (p_map[j+2][i] == BLACK) && j+2 <= 14 && j-3 >= 0){
                            //printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if(((p_map[j-3][i] == BLACK)  || (p_map[j+2][i] == BLACK )) && j+2 <= 14 && j-3 >= 0){
                            printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if( j-3 >=0){// 세로 - (N) B B  B <N> (N)
                    if(p_map[j-3][i] == WHITE && p_map[j-2][i] == WHITE && p_map[j-1][i] == WHITE){
                        if( (p_map[j-4][i] == BLACK ) && (p_map[j+1][i] == BLACK) && j+1 <= 14 && j-4 >= 0){
                            //printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if(((p_map[j-4][i] == BLACK) || (p_map[j+1][i] == BLACK)) && j+1 <= 14 && j-4 >= 0){
                            printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
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
                        }
                    }
                }
                if( i-1 >= 0 && i+2 <=14 && j-1 >= 0 && j+2 <=14){// Dia 1 - (N) B <N> B B (N)
                    if(p_map[j-1][i-1] == WHITE && p_map[j+1][i+1] == WHITE && p_map[j+2][i+2] == WHITE){
                        if( (p_map[j-2][i-2] == BLACK) && (p_map[j+3][i+3] == BLACK ) && (j-2 >=0 && j+3 <= 14) && (i-2 >=0 && i+3 <= 14) ){//양쪽 모두 체크 - 중앙에 있음

                        }else if( ((p_map[j-2][i-2] == BLACK ) || (p_map[j+3][i+3] == BLACK )) && (j-2 >=0 && j+3 <= 14) && (i-2 >=0 && i+3 <= 14) ){
                            printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }//
                }
                if(i-2 >=0 && i+1 <=14 && j-2 >=0 && j+1 <=14){// Dia 1 - (N) B  B <N> B (N)
                    if(p_map[j-2][i-2] == WHITE && p_map[j-1][i-1] == WHITE && p_map[j+1][i+1] == WHITE){
                        if( (p_map[j-3][i-3] == BLACK ) && (p_map[j+2][i+2] == BLACK) && j+2 <= 14 && j-3 >= 0 && i+2 <= 14 && i-3 >= 0){

                        }else if(((p_map[j-3][i-3] == BLACK) || (p_map[j+2][i+2] == BLACK)) && j+2 <= 14 && j-3 >= 0 && i+2 <= 14 && i-3 >= 0){
                            printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if( i-3 >=0 && j-3 >=0){// Dia 1 - (N) B B  B <N> (N)
                    if(p_map[j-3][i-3] == WHITE && p_map[j-2][i-2] == WHITE && p_map[j-1][i-1] == WHITE){
                        if( (p_map[j-4][i-4] == BLACK ) && (p_map[j+1][i+1] == BLACK ) && j+1 <= 14 && j-4 >= 0 && i+1 <= 14 && i-4 >= 0){

                        }else if(((p_map[j-4][i-4] == BLACK) || (p_map[j+1][i+1] == BLACK)) && j+1 <= 14 && j-4 >= 0 && i+1 <= 14 && i-4 >= 0){
                            printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
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
                        }
                    }
                }
                if( i-1>=0 && i+2<=14 && j-2>=0 && j+1<=14 ){// Dia 2 - (N) B <N> B B (N)
                    if(p_map[j+1][i-1] == WHITE && p_map[j-1][i+1] == WHITE && p_map[j-2][i+2] == WHITE){
                        if( (p_map[j+2][i-2] == BLACK ) && (p_map[j-3][i+3] == BLACK ) && (j-3 >=0 && j+2 <= 14) && (i-2 >=0 && i+3 <= 14) ){//양쪽 모두 체크 - 중앙에 있음

                        }else if( ((p_map[j+2][i-2] == BLACK ) || (p_map[j-3][i+3] == BLACK )) && (j-3 >=0 && j+2 <= 14) && (i-2 >=0 && i+3 <= 14) ){
                            printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if(i-2 >=0 && i+1 <=14 && j+2 >=0 && j-1 <=14){// Dia 2 - (N) B  B <N> B (N)
                    if(p_map[j+2][i-2] == WHITE && p_map[j+1][i-1] == WHITE && p_map[j-1][i+1] == WHITE){
                        if( (p_map[j+3][i-3] == BLACK ) && (p_map[j-2][i+2] == BLACK ) && j+3 <= 14 && j-2 >= 0 && i+2 <= 14 && i-3 >= 0){

                        }else if(((p_map[j+3][i-3] == BLACK ) || (p_map[j-2][i+2] == BLACK)) && j+3 <= 14 && j-2 >= 0 && i+2 <= 14 && i-3 >= 0){
                            printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if( i-3 >=0 && j+3 <= 14){// Dia 2 - (N) B B  B <N> (N)
                    if(p_map[j+3][i-3] == WHITE && p_map[j+2][i-2] == WHITE && p_map[j+1][i-1] == WHITE){
                        if( (p_map[j+4][i-4] == BLACK ) && (p_map[j-1][i+1] == BLACK ) && j+4 <= 14 && j-1 >= 0 && i+1 <= 14 && i-4 >= 0){

                        }else if(((p_map[j+4][i-4] == BLACK) || (p_map[j-1][i+1] == BLACK )) && j+4 <= 14 && j-1 >= 0 && i+1 <= 14 && i-4 >= 0){
                            printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                //
            }
        }
    }
      printf("\n **** ENd Half W3******");
}

int Game::findB2(std::array<std::array<int,15>,15>& p_map, std::array<std::array<int, 2>, 10> &buf_xy, int buf_size)
{
    printf("\n **** find B2******");
    /*
      경우의 수
      (B) (N) B B (N)
     */
    int p = 0;
    int b = 0;
    for(int j = 0; j < 15; j++){
        for(int i =0; i < 15; i++){
            if(p_map[j][i] == PAN){//only PAN - Black cannot put NON
                if(i+3 <= 14){// 가로 - (N) <N> B B (N)
                    if(p_map[j][i+1] == BLACK && p_map[j][i+2] == BLACK && p_map[j][i+3] == BLACK){
                        if( (p_map[j][i-1] == WHITE || p_map[j][i-1] == NON ) && (p_map[j][i+4] == WHITE || p_map[j][i+4] == NON ) && i+4 <= 14 && i-1>=0) // 양측 모두 막힌 경우
                        {
//                            printf("\n 1-1 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if (((p_map[j][i-1] == WHITE || p_map[j][i-1] == NON ) || (p_map[j][i+4] == WHITE || p_map[j][i+4] == NON )) && i+4 <= 14 && i-1>=0){//한쪽만 막힌 경우
                            printf("\n 1-1 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if(i-1 >= 0 && i+2 <=14){// 가로 - (N) B <N> B B (N)
                    if(p_map[j][i-1] == BLACK && p_map[j][i+1] == BLACK && p_map[j][i+2] == BLACK){
                        if( (p_map[j][i-2] == WHITE || p_map[j][i-2] == NON) && (p_map[j][i+3] == WHITE || p_map[j][i+3] == NON)  && (i-2 >=0 && i+3 <= 14) ){//양쪽 모두 체크 - 중앙에 있음
                            //printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if(((p_map[j][i-2] == WHITE || p_map[j][i-2] == NON) || (p_map[j][i+3] == WHITE || p_map[j][i+3] == NON))  && (i-2 >=0 && i+3 <= 14)){
                            printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if(i-2 >=0 && i+1 <=14){// 가로 - (N) B  B <N> B (N)
                    if(p_map[j][i-2] == BLACK && p_map[j][i-1] == BLACK && p_map[j][i+1] == BLACK){
                        if( (p_map[j][i-3] == WHITE || p_map[j][i-3] == NON) && (p_map[j][i+2] == WHITE || p_map[j][i+2] == NON)  && i+2 <= 14 && i-3 >= 0){
                            //printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if(((p_map[j][i-3] == WHITE || p_map[j][i-3] == NON) || (p_map[j][i+2] == WHITE || p_map[j][i+2] == NON))  && i+2 <= 14 && i-3 >= 0){
                            printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if( i-3 >=0 ){// 가로 - (N) B B  B <N> (N)
                    if(p_map[j][i-3] == BLACK && p_map[j][i-2] == BLACK && p_map[j][i-1] == BLACK){
                        if( (p_map[j][i-4] == WHITE || p_map[j][i-4] == NON) && (p_map[j][i+1] == WHITE || p_map[j][i+1] == NON) && i+1 <= 14 && i-4 >= 0){
                            //printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if(((p_map[j][i-4] == WHITE || p_map[j][i-4] == NON) || (p_map[j][i+1] == WHITE || p_map[j][i+1] == NON)) && i+1 <= 14 && i-4 >= 0){
                            printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
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
                        }
                    }
                }
                if(j-1 >= 0 && j+2 <=14){// 세로 - (N) B <N> B B (N)
                    if(p_map[j-1][i] == BLACK && p_map[j+1][i] == BLACK && p_map[j+2][i] == BLACK){
                        if( (p_map[j-2][i] == WHITE || p_map[j-2][i] == NON) && (p_map[j+3][i] == WHITE || p_map[j+3][i] == NON) && (j-2 >=0 && j+3 <= 14) ){//양쪽 모두 체크 - 중앙에 있음
                            //printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if(((p_map[j-2][i] == WHITE || p_map[j-2][i] == NON) || (p_map[j+3][i] == WHITE || p_map[j+3][i] == NON)) && (j-2 >=0 && j+3 <= 14)){
                            printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if(j-2 >=0 && j+1 <=14){// 세로 - (N) B  B <N> B (N)
                    if(p_map[j-2][i] == BLACK && p_map[j-1][i] == BLACK && p_map[j+1][i] == BLACK){
                        if( (p_map[j-3][i] == WHITE || p_map[j-3][i] == NON)  && (p_map[j+2][i] == WHITE || p_map[j+2][i] == NON) && j+2 <= 14 && j-3 >= 0){
                            //printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if(((p_map[j-3][i] == WHITE || p_map[j-3][i] == NON)  || (p_map[j+2][i] == WHITE || p_map[j+2][i] == NON)) && j+2 <= 14 && j-3 >= 0){
                            printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if( j-3 >=0){// 세로 - (N) B B  B <N> (N)
                    if(p_map[j-3][i] == BLACK && p_map[j-2][i] == BLACK && p_map[j-1][i] == BLACK){
                        if( (p_map[j-4][i] == WHITE || p_map[j-4][i] == NON) && (p_map[j+1][i] == WHITE || p_map[j+1][i] == NON) && j+1 <= 14 && j-4 >= 0){
                            //printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if(((p_map[j-4][i] == WHITE || p_map[j-4][i] == NON) || (p_map[j+1][i] == WHITE || p_map[j+1][i] == NON)) && j+1 <= 14 && j-4 >= 0){
                            printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
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
                        }
                    }
                }
                if( i-1 >= 0 && i+2 <=14 && j-1 >= 0 && j+2 <=14){// Dia 1 - (N) B <N> B B (N)
                    if(p_map[j-1][i-1] == BLACK && p_map[j+1][i+1] == BLACK && p_map[j+2][i+2] == BLACK){
                        if( (p_map[j-2][i-2] == WHITE || p_map[j-2][i-2] == NON) && (p_map[j+3][i+3] == WHITE || p_map[j+3][i+3] == NON) && (j-2 >=0 && j+3 <= 14) && (i-2 >=0 && i+3 <= 14) ){//양쪽 모두 체크 - 중앙에 있음

                        }else if( ((p_map[j-2][i-2] == WHITE || p_map[j-2][i-2] == NON) || (p_map[j+3][i+3] == WHITE || p_map[j+3][i+3] == NON)) && (j-2 >=0 && j+3 <= 14) && (i-2 >=0 && i+3 <= 14) ){
                            printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }//
                }
                if(i-2 >=0 && i+1 <=14 && j-2 >=0 && j+1 <=14){// Dia 1 - (N) B  B <N> B (N)
                    if(p_map[j-2][i-2] == BLACK && p_map[j-1][i-1] == BLACK && p_map[j+1][i+1] == BLACK){
                        if( (p_map[j-3][i-3] == WHITE || p_map[j-3][i-3] == NON) && (p_map[j+2][i+2] == WHITE || p_map[j+2][i+2] == NON) && j+2 <= 14 && j-3 >= 0 && i+2 <= 14 && i-3 >= 0){

                        }else if(((p_map[j-3][i-3] == WHITE || p_map[j-3][i-3] == NON) || (p_map[j+2][i+2] == WHITE || p_map[j+2][i+2] == NON)) && j+2 <= 14 && j-3 >= 0 && i+2 <= 14 && i-3 >= 0){
                            printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if( i-3 >=0 && j-3 >=0){// Dia 1 - (N) B B  B <N> (N)
                    if(p_map[j-3][i-3] == BLACK && p_map[j-2][i-2] == BLACK && p_map[j-1][i-1] == BLACK){
                        if( (p_map[j-4][i-4] == WHITE || p_map[j-4][i-4] == NON) && (p_map[j+1][i+1] == WHITE || p_map[j+1][i+1] == NON) && j+1 <= 14 && j-4 >= 0 && i+1 <= 14 && i-4 >= 0){

                        }else if(((p_map[j-4][i-4] == WHITE || p_map[j-4][i-4] == NON) || (p_map[j+1][i+1] == WHITE || p_map[j+1][i+1] == NON)) && j+1 <= 14 && j-4 >= 0 && i+1 <= 14 && i-4 >= 0){
                            printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
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
                        }
                    }
                }
                if( i-1>=0 && i+2<=14 && j-2>=0 && j+1<=14 ){// Dia 2 - (N) B <N> B B (N)
                    if(p_map[j+1][i-1] == BLACK && p_map[j-1][i+1] == BLACK && p_map[j-2][i+2] == BLACK){
                        if( (p_map[j+2][i-2] == WHITE || p_map[j+2][i-2] == NON) && (p_map[j-3][i+3] == WHITE || p_map[j-3][i+3] == NON) && (j-3 >=0 && j+2 <= 14) && (i-2 >=0 && i+3 <= 14) ){//양쪽 모두 체크 - 중앙에 있음

                        }else if( ((p_map[j+2][i-2] == WHITE || p_map[j+2][i-2] == NON) || (p_map[j-3][i+3] == WHITE || p_map[j-3][i+3] == NON)) && (j-3 >=0 && j+2 <= 14) && (i-2 >=0 && i+3 <= 14) ){
                            printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if(i-2 >=0 && i+1 <=14 && j+2 >=0 && j-1 <=14){// Dia 2 - (N) B  B <N> B (N)
                    if(p_map[j+2][i-2] == BLACK && p_map[j+1][i-1] == BLACK && p_map[j-1][i+1] == BLACK){
                        if( (p_map[j+3][i-3] == WHITE || p_map[j+3][i-3] == NON) && (p_map[j-2][i+2] == WHITE || p_map[j-2][i+2] == NON) && j+3 <= 14 && j-2 >= 0 && i+2 <= 14 && i-3 >= 0){

                        }else if(((p_map[j+3][i-3] == WHITE || p_map[j+3][i-3] == NON) || (p_map[j-2][i+2] == WHITE || p_map[j-2][i+2] == NON)) && j+3 <= 14 && j-2 >= 0 && i+2 <= 14 && i-3 >= 0){
                            printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if( i-3 >=0 && j+3 <= 14){// Dia 2 - (N) B B  B <N> (N)
                    if(p_map[j+3][i-3] == BLACK && p_map[j+2][i-2] == BLACK && p_map[j+1][i-1] == BLACK){
                        if( (p_map[j+4][i-4] == WHITE || p_map[j+4][i-4] == NON) && (p_map[j-1][i+1] == WHITE || p_map[j-1][i+1] == NON) && j+4 <= 14 && j-1 >= 0 && i+1 <= 14 && i-4 >= 0){

                        }else if(((p_map[j+4][i-4] == WHITE || p_map[j+4][i-4] == NON) || (p_map[j-1][i+1] == WHITE || p_map[j-1][i+1] == NON)) && j+4 <= 14 && j-1 >= 0 && i+1 <= 14 && i-4 >= 0){
                            printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                //
            }
        }
    }
      printf("\n **** ENd Half B3******");
}

int Game::findW2(std::array<std::array<int,15>,15>& p_map, std::array<std::array<int, 2>, 10> &buf_xy, int buf_size)
{

}

int Game::findB1(std::array<std::array<int,15>,15>& p_map, std::array<std::array<int, 2>, 10> &buf_xy, int buf_size)
{

}

int Game::findW1(std::array<std::array<int,15>,15>& p_map, std::array<std::array<int, 2>, 10> &buf_xy, int buf_size)
{

}

int Game::findW4(std::array<std::array<int,15>,15>& p_map, std::array<std::array<int, 2>, 10> &buf_xy, int buf_size)
{
    printf("\n **** find W4******");
    int p = 0;
    int b = 0;
    for(int j = 0; j < 15; j++){
        for(int i =0; i < 15; i++){
            if( p_map[j][i] == NON ||p_map[j][i] == PAN){//White - PAN, NON
                if(i+4 <= 14){ // 가로 - N B B B B
                    if(p_map[j][i+1] == WHITE && p_map[j][i+2] == WHITE && p_map[j][i+3] == WHITE && p_map[j][i+4] == WHITE){
                        if( p_map[j][i-1]  != WHITE && i-1>=0) // 좌측 검사
                        {
                            printf("\n 1-1 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                        else if( i == 0) //
                        {   //push(j,i);
                            printf("\n 1-2 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if(i-1 >= 0 && i+3 <=14){// 가로 - B N B B B
                    if(p_map[j][i-1] == WHITE && p_map[j][i+1] == WHITE && p_map[j][i+2] == WHITE && p_map[j][i+3] == WHITE){
                        if( p_map[j][i-2] != WHITE && p_map[j][i+4] != WHITE && (i-2 >=0 && i+4 <= 14) ){//양쪽 모두 체크 - 중앙에 있음
                            printf("\n 1-3 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( p_map[j][i-2] != WHITE && i+3 == 14){//좌측 체크 (우측은 이미 끝에 도달)
                            printf("\n 1-4 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( p_map[j][i+4] != WHITE && i -1 == 0 ){//우측 체크
                            printf("\n 1-5 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if(i-2 >=0 && i+2 <=14){// 가로 - B  B N B B
                    if(p_map[j][i-2] == WHITE && p_map[j][i-1] == WHITE && p_map[j][i+1] == WHITE && p_map[j][i+2] == WHITE ){
                        if( p_map[j][i-3] != WHITE && p_map[j][i+3] != WHITE && i+3 <= 14 && i-3 >= 0){
                            printf("\n 1-6 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( p_map[j][i+3] != WHITE && i - 2 == 0){//좌측에 붙어있음 -> 우측만 검사
                            printf("\n 1-7 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( p_map[j][i-3] != WHITE && i + 2 == 14){//우측에 붙어 있음 -> 좌측만 검사
                            printf("\n 1-8 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if( i-3 >=0 && i+1 <= 14){// 가로 - B B  B N B
                    if(p_map[j][i-3] == WHITE && p_map[j][i-2] == WHITE && p_map[j][i-1] == WHITE && p_map[j][i+1] == WHITE){
                        if( p_map[j][i+2] != WHITE && p_map[j][i-4] != WHITE && i+2 <= 14 && i-4 >= 0){
                            printf("\n 1-9 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if ( p_map[j][i+2] !=WHITE && i -3 == 0){//좌측에 붙음 -> 우측만 검사
                            printf("\n 1-10 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( p_map[j][i-4] != WHITE && i+1 == 14){//우측에 붙음 -> 좌측만 검사
                            printf("\n 1-11 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if( i-4 >= 0){// 가로 - B B B B N
                    if(p_map[j][i-4] == WHITE && p_map[j][i-3] == WHITE && p_map[j][i-2] == WHITE && p_map[j][i-1] == WHITE){
                        if(i == 14){//이미 끝에 도달 - 검사할것 없음(원래는 우측 검사)
                            printf("\n 1-12 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( p_map[j][i+1] != WHITE && i != 14){//우측 검사
                            printf("\n 1-13 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                //// - 세로
                if(j+4 <= 14){ // 세로 - N B B B B
                    if(p_map[j+1][i] == WHITE && p_map[j+2][i] == WHITE && p_map[j+3][i] == WHITE && p_map[j+4][i] == WHITE){
                        if( p_map[j-1][i]  != WHITE && j-1>=0)//상단 검사 할거리 있을 경우
                        {
                            printf("\n 2-1 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                        else if( j== 0)//상단에 붙어있음 - 검사 할거리 없음
                        {   //push(j,i);
                            printf("\n 2-2 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if(j-1 >= 0 && j+3 <=14){// 세로 - B N B B B
                    if(p_map[j-1][i] == WHITE && p_map[j+1][i] == WHITE && p_map[j+2][i] == WHITE && p_map[j+3][i] == WHITE){
                        if( p_map[j-2][i] != WHITE && p_map[j+4][i] != WHITE && (j-2 >=0 && j+4 <= 14) ){//양쪽 모두 체크 - 중앙에 있음
                            printf("\n 2-3 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( p_map[j-2][i] != WHITE && j+3 == 14){//상단 체크 (하단은 이미 끝에 도달)
                            printf("\n 2-4 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( p_map[j+4][i] != WHITE && j -1 == 0 ){//하단 체크 - 상단은 이미 상단에 도달
                            printf("\n 2-5 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if(j-2 >=0 && j+2 <=14){// 세로 - B  B N B B
                    if(p_map[j-2][i] == WHITE && p_map[j-1][i] == WHITE && p_map[j+1][i] == WHITE && p_map[j+2][i] == WHITE ){
                        if( p_map[j-3][i] != WHITE && p_map[j+3][i] != WHITE && j+3 <= 14 && j-3 >= 0){
                            printf("\n 2-6 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( p_map[j+3][i] != WHITE && j - 2 == 0){//상단에 붙어 있을 경우 -> 하단만 검사
                            printf("\n 2-7 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( p_map[j-3][i] != WHITE && j + 2 == 14){//하단에 붙어 있을경우 -> 상단만 검사
                            printf("\n 2-8 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if( j-3 >=0 && j+1 <= 14){// 세로 - B B  B N B
                    if(p_map[j-3][i] == WHITE && p_map[j-2][i] == WHITE && p_map[j-1][i] == WHITE && p_map[j+1][i] == WHITE){
                        if( p_map[j+2][i] != WHITE && p_map[j-4][i] != WHITE && j+2 <= 14 && j-4 >= 0){
                            printf("\n 2-9 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if ( p_map[j+2][i] !=WHITE && j -3 == 0){//상단에 붙음 - 하단만 검사
                            printf("\n 2-10 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( p_map[j-4][i] != WHITE && j+1 == 14){//하단에 붙음 - 상단만 검사
                            printf("\n 2-11 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if( j-4 >= 0){// 세로 - B B B B N
                    if(p_map[j-4][i] == WHITE && p_map[j-3][i] == WHITE && p_map[j-2][i] == WHITE && p_map[j-1][i] == WHITE){
                        if(j == 14){//이미 끝에 도달 - 굳이 상단 검사할 필요없음 - 5개여서
                            printf("\n 2-12 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( p_map[j+1][i] != WHITE && j != 14){//하단 검사
                            printf("\n 2-13 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                // Dia 1 - "\"
                if( i+4 <= 14 && j+4 <= 14){ // dia1 - N B B B B
                    if(p_map[j+1][i+1] == WHITE && p_map[j+2][i+2] == WHITE && p_map[j+3][i+3] == WHITE && p_map[j+4][i+4] == WHITE){
                        if( p_map[j-1][i-1] != WHITE && j-1>=0 && i-1>=0)//우측에 있으면 이미 5개임 -> 검사할 필요 없음 - 좌측만 돌 없으면 4
                        {
                            printf("\n 3-1 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                        else if( i == 0 || j== 0)//좌측에 달라 붙어 있을경우 - 검사 필요 없음
                        {   //push(j,i);
                            printf("\n 3-2 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if(i-1 >= 0 && i+3 <=14 && j-1 >= 0 && j+3 <=14){// dia1 - B N B B B
                    if(p_map[j-1][i-1] == WHITE && p_map[j+1][i+1] == WHITE && p_map[j+2][i+2] == WHITE && p_map[j+3][i+3] == WHITE){
                        if( p_map[j-2][i-2] != WHITE && p_map[j+4][i+4] != WHITE && (i-2 >=0 && i+4 <= 14) && (j-2 >=0 && j+4 <= 14) ){//양쪽 모두 체큰 - 중앙에 있음
                            printf("\n 3-3 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( p_map[j-2][i-2] != WHITE && (i+3 == 14 || j+3 == 14)){//좌측 체크 (우측은 이미 끝에 도달)
                            printf("\n 3-4 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( p_map[j+4][i+4] != WHITE && (i -1 == 0  || j -1 == 0) ){//우측 체크
                            printf("\n 3-5 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if(i-2 >=0 && i+2 <=14 && j-2 >=0 && j+2 <=14){// dia1 - B  B N B B
                    if(p_map[j-2][i-2] == WHITE && p_map[j-1][i-1] == WHITE && p_map[j+1][i+1] == WHITE && p_map[j+2][i+2] == WHITE ){
                        if( p_map[j-3][i-3] != WHITE && p_map[j+3][i+3] != WHITE && i+3 <= 14 && i-3 >= 0 && j+3 <= 14 && j-3 >= 0){
                            printf("\n 3-6 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( p_map[j+3][i+3] != WHITE && (i - 2 == 0 || j - 2 == 0)){
                            printf("\n 3-7 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( p_map[j-3][i-3] != WHITE && (i + 2 == 14 || j + 2 == 14)){
                            printf("\n 3-8 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if( i-3 >=0 && i+1 <= 14 && j-3 >=0 && j+1 <= 14){// dia1 - B B  B N B
                    if(p_map[j-3][i-3] == WHITE && p_map[j-2][i-2] == WHITE && p_map[j-1][i-1] == WHITE && p_map[j+1][i+1] == WHITE){
                        if( p_map[j+2][i+2] != WHITE && p_map[j-4][i-4] != WHITE && i+2 <= 14 && i-4 >= 0 && j+2 <= 14 && j-4 >= 0){
                            printf("\n 3-9 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if ( p_map[j+2][i+2] !=WHITE && (i -3 == 0 || j -3 == 0)){
                            printf("\n 3-10 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( p_map[j-4][i-4] != WHITE && (i+1 == 14 || j+1 == 14)){
                            printf("\n 3-11 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if( i-4 >= 0 && j-4 >= 0){// dia1 - B B B B N
                    if(p_map[j-4][i-4] == WHITE && p_map[j-3][i-3] == WHITE && p_map[j-2][i-2] == WHITE && p_map[j-1][i-1] == WHITE){
                        if( i == 14 || j == 14){//이미 끝에 도달 -- 좌측 검사할 필요 없음(5개니까) - 우측 검사할 칸 없음
                            printf("\n 3-12 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( p_map[j+1][i+1] != WHITE && i != 14 && j != 14){
                            printf("\n 3-13 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                // DIa 2 - /
                if( j-4 >=0 && i+4 <= 14){ // dia2 - N B B B B
                    if(p_map[j-1][i+1] == WHITE && p_map[j-2][i+2] == WHITE && p_map[j-3][i+3] == WHITE && p_map[j-4][i+4] == WHITE){
                        if( p_map[j+1][i-1]  != WHITE && j+1<=14 && i-1>=0) // 좌측 검사 - 좌측이 있을 경우
                        {
                            printf("\n 4-1 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                        else if( j == 14 || i == 0)//ㄴ 라인
                        {   //push(j,i);
                            printf("\n 4-2 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if( j-3 >= 0 && j+1 <=14 && i-1 >= 0 && i+3 <=14){// dia2 - B N B B B
                    if(p_map[j+1][i-1] == WHITE && p_map[j-1][i+1] == WHITE && p_map[j-2][i+2] == WHITE && p_map[j-3][i+3] == WHITE){
                        if( p_map[j+2][i-2] != WHITE && p_map[j-4][i+4] != WHITE &&
                                (i-2 >=0 && i+4 <= 14) && (j-4 >=0 && j+2 <= 14) ){//양쪽 모두 체큰 - 중앙에 있음
                            printf("\n 4-3 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( p_map[j+2][i-2] != WHITE  && (i+3 == 14 || j-3 == 0)){//좌측 체크 (우측은 이미 끝에 도달) ㄱ 형태
                            printf("\n 4-4 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( p_map[j-4][i+4] != WHITE && (j + 1 == 14 || i -1 == 0 )){//우측 체크 ㄴ 형태
                            printf("\n 4-5 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if(j-2 >=0 && j+2 <=14 && i-2 >=0 && i+2 <=14){// dia2 - B  B N B B
                    if(p_map[j+2][i-2] == WHITE && p_map[j+1][i-1] == WHITE && p_map[j-1][i+1] == WHITE && p_map[j-2][i+2] == WHITE ){
                        if( p_map[j+3][i-3] != WHITE && p_map[j-3][i+3] != WHITE &&
                                (i-3 >=0 && i+3 <=14 ) && (j-3 >=0 && j+3 <= 14)){
                            printf("\n 4-6find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( p_map[j+3][i-3] != WHITE && ( j == 2 || i == 12)){//하단 검사
                            printf("\n 4-7 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( p_map[j-3][i+3] != WHITE && ( j == 12 || i == 2)){//상단 검사
                            printf("\n 4-8 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if( j+3 <= 14 && i-3 >=0 && j-1 >=0 && i+1 <= 14){// dia2 - B B  B N B
                    if(p_map[j+3][i-3] == WHITE && p_map[j+2][i-2] == WHITE && p_map[j+1][i-1] == WHITE && p_map[j-1][i+1] == WHITE){
                        if( p_map[j+4][i-4] != WHITE && p_map[j-2][i+2] != WHITE &&
                                (j+4 <= 14 && i-4>=0) && (j-2 >=0 && i+2 <= 14)){// 2<=j<= 10   4<=i<=12
                            printf("\n 4-9 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if ( p_map[j+4][i-4] !=WHITE && (j == 1 || i == 13)){
                            printf("\n 4-10 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( p_map[j-2][i+2] != WHITE && (j == 11 || i == 3)){
                            printf("\n 4-11 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
                if( j+4 <= 14 && i-4 >= 0){// dia2 - B B B B N
                    if(p_map[j+4][i-4] == WHITE && p_map[j+3][i-3] == WHITE && p_map[j+2][i-2] == WHITE && p_map[j+1][i-1] == WHITE){
                        if(p_map[j-1][i+1] !=WHITE && (j-1>=0 && i+1<=14)){//우측 검사 - 우측이 있을 경우
                            printf("\n 4-12 find connect 4 - j = %d , i = %d   ",j,i);
                        }else if( j == 0 || i == 14){// 검사 필요 없음
                            printf("\n 4-13 find connect 4 - j = %d , i = %d   ",j,i);
                        }
                    }
                }
            }
        }
    }
     printf("\n **** ENd W4******");
}

bool Game::checkNon(std::array<std::array<int, 15>, 15> i_map)
{

}

int Game::miniMax(std::array<std::array<int, 15>, 15> &p_map, int depth, int al, int be, bool turn)
{
    if(depth == 5){//cal board
        int scor = calScore(p_map);
        return scor;
    }
    std::array<std::array<int, 15>, 15> my_b;
    std::array<std::array<int,2>,10> buf_xy;
    uint8_t x;
    uint8_t y;
    int xy_size;
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
    }
    else if(turn == WHITE){
        xy_size = findSpotW(my_b,buf_xy,10);
    }
/*
//

//set_stone
    int temp =0;
    //y = buf_xy[t].
    for(int t = 0; t < xy_size; t++){
        //my_b[buf_xy[t].first][buf_xy[t].second] = turn; // set Stone
        if( depth % 2 == 0 && depth != 0){//pick max
            int max_sc = -1000000 ;
            for(int i=0; i<10; i++){
                temp = miniMax(my_b,1,1,1,1);
                if(max_sc < temp){
                    max_sc = temp;
                    //y = buf_xy[t].first;
                    //x = buf_xy[t].second;
                }
            }
            return max_sc;
        }else{//pick min
            int min_sc = 100000000;
            for(int i=0; i<10; i++){
                temp = miniMax(my_b,1,1,1,1);
                if(min_sc > temp){
                    min_sc = temp;
                    //y = buf_xy[t].first;
                    //x = buf_xy[t].second;
                }
            }
            return min_sc;
        }
    }
    if( depth == 0){
        //put_stone(y,x);
        return true;
    }
    */
}
