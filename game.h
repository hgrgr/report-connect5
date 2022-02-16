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
    int find3(std::array<std::array<int,15>,15>* p_map);
    int find4(std::array<std::array<int,15>,15>* p_map);
    int find33(std::array<std::array<int,15>,15>* p_map);
    int searchWidth(std::array<std::array<int,15>,15> i_map,int num,bool color);
    int searchLength(std::array<std::array<int,15>,15> i_map,int num,bool color);
    int searchDia(std::array<std::array<int,15>,15> i_map,int num,bool color);
    int check5(std::array<std::array<int,15>,15> i_map,bool color);// 오목 체크
    int check4(std::array<std::array<int,15>,15> i_map);// 4 체크
    int check3(std::array<std::array<int,15>,15> i_map);// 3 체크
    int check2(std::array<std::array<int,15>,15> i_map);// 2 체크
    bool checkNon(std::array<std::array<int,15>,15> i_map);//3-3 체크
    //
    int miniMax(std::array<std::array<int,15>,15>& p_map,int depth, int al, int be, bool turn);

    int calScore(std::array<std::array<int,15>,15>& p_map);// 보드 점수 계산
    int findSpotW(std::array<std::array<int,15>,15>& p_map, std::array<std::array<int,2>,10>& buf_xy,int buf_size);
    int findSpotB(std::array<std::array<int,15>,15>& p_map, std::array<std::array<int,2>,10>& buf_xy,int buf_size);

    int findB4(std::array<std::array<int,15>,15>& p_map, std::array<std::array<int,2>,10>& buf_xy, int buf_size);
    int findW4(std::array<std::array<int,15>,15>& p_map, std::array<std::array<int,2>,10>& buf_xy, int buf_size);

    int findFB3(std::array<std::array<int,15>,15>& p_map, std::array<std::array<int,2>,10>& buf_xy, int buf_size);
    int findFW3(std::array<std::array<int,15>,15>& p_map, std::array<std::array<int,2>,10>& buf_xy, int buf_size);

    int findHB3(std::array<std::array<int,15>,15>& p_map, std::array<std::array<int,2>,10>& buf_xy, int buf_size);
    int findHW3(std::array<std::array<int,15>,15>& p_map, std::array<std::array<int,2>,10>& buf_xy, int buf_size);

    int findB2(std::array<std::array<int,15>,15>& p_map, std::array<std::array<int,2>,10>& buf_xy, int buf_size);
    int findW2(std::array<std::array<int,15>,15>& p_map, std::array<std::array<int,2>,10>& buf_xy, int buf_size);

    int findB1(std::array<std::array<int,15>,15>& p_map, std::array<std::array<int,2>,10>& buf_xy, std::array<std::array<int,15>,15>& bit_map,int buf_size);
    int findW1(std::array<std::array<int,15>,15>& p_map, std::array<std::array<int,2>,10>& buf_xy, std::array<std::array<int,15>,15>& bit_map,int buf_size);
    //
    void testpair(std::array<std::array<int,2>,10>& buf_xy);
};

#endif // GAME_H
