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
    void showGui();
    bool myTurn();
    bool waitTurn();
    void endGame();
    void setMyTurn();
    void putStone(uint8_t y, uint8_t x);
    bool updateBoard(uint8_t xy);
    void run();
};

#endif // GAME_H
