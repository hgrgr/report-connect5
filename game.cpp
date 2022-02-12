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
    }else if(mf->remote == LOCAL){//local
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
        for(int i=0; i < 15; i++){
            for(int j=0; j < 11; j++){
                   if(i_map[i][j] == color && i_map[i][j+1] == color && i_map[i][j+2] == color && i_map[i][j+3] == color && i_map[i][j+4] == color)
                       return 1;
            }
        }
    }
    return 0;
}

int Game::searchLength(std::array<std::array<int, 15>, 15> i_map, int num, bool color)
{
    if(num == 5){//find connect5 - sp case
        for(int i=0; i < 11; i++){
            for(int j=0; j < 15; j++){
                   if(i_map[i][j] == color && i_map[i+1][j] == color && i_map[i+2][j] == color && i_map[i+3][j] == color && i_map[i+4][j] == color)
                       return 1;
            }
        }
    }
    return 0;
}

int Game::searchDia(std::array<std::array<int, 15>, 15> i_map, int num, bool color)
{
    if(num == 5){//find connect5 - sp case
        for(int i=0; i < 11; i++){
            for(int j=0; j < 11; j++){
                   if((i_map[i+4][j] == color && i_map[i+3][j+1] == color && i_map[i+2][j+2] == color && i_map[i+1][j+3] == color && i_map[i][j+4] == color) || (i_map[i][j] == color && i_map[i+1][j+1] == color && i_map[i+2][j+2] == color && i_map[i+3][j+3] == color && i_map[i+4][j+4] == color))
                       return 1;
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

int Game::calScore(std::array<std::array<int, 15>, 15> i_map)
{

}

bool Game::checkNon(std::array<std::array<int, 15>, 15> i_map)
{

}

std::vector<std::pair<int, int> > Game::findSpot(std::array<std::array<int, 15>, 15> i_map)
{

}

