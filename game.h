#ifndef GAME_H
#define GAME_H
#include "pch.h"

class Game: public QThread
{
public:
    bool startBit;
    bool endBit;
    bool put_bit;
    bool turnToggle;
    std::array<std::array<int,15>,15> i_map;
    Ui::Widget *ui;
    class MyFunc *mf;
    class ConnectServer* cs;
public:
    Game(Ui::Widget *ui, class ConnectServer* cs,class MyFunc *mf);
    void gameStart(int turn);
    void initBoard();
    void setGui();
    void endGame();
    void setMyTurn();
    void putStone(uint8_t y, uint8_t x);
    bool updateBoard(uint8_t xy);
    //
    int searchWidth(std::array<std::array<int,15>,15> i_map,int num,bool color);
    int searchLength(std::array<std::array<int,15>,15> i_map,int num,bool color);
    int searchDia(std::array<std::array<int,15>,15> i_map,int num,bool color);
    int check5(std::array<std::array<int,15>,15> i_map,bool color);// 오목 체크
    int check4(std::array<std::array<int,15>,15> i_map);// 4 체크
    int check3(std::array<std::array<int,15>,15> i_map);// 3 체크
    int check2(std::array<std::array<int,15>,15> i_map);// 2 체크
    int calScore(std::array<std::array<int,15>,15> i_map);// 보드 점수 계산
    bool checkNon(std::array<std::array<int,15>,15> i_map);//3-3 체크
    std::vector<std::pair<int,int>> findSpot(std::array<std::array<int,15>,15> i_map);
    //
    int miniMax();//miniMax 알고리즘
};

#endif // GAME_H
