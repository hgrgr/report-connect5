#include "pch.h"

MyFunc::MyFunc(Ui::Widget *ui)
{
    this->ui = ui;
    remote = 0;
    mode = 0;//1 - 1:1, 2: 1:AI , 3: AI:AI
    turn = 2;
    pan[PAN].load(":/stone/pan.png");
    pan[BLACK].load(":/stone/black.png");
    pan[WHITE].load(":/stone/white.png");
    pan[NON].load(":/stone/pan_Non.png");
    pIcon = pan[PAN];
    bStone = pan[BLACK];
    wStone = pan[WHITE];
    nonStone = pan[NON];
}

void MyFunc::initBoard()
{
    QString temp;
    //initIBoard();//i_map init
    for(int i=0;i<15;i++){
        for(int j=0;j<15;j++){
            temp = QString("map_%1_%2").arg(QString::number(i)).arg(QString::number(j));
            my_map[temp]->setIcon(pIcon);
            my_map[temp]->setIconSize(QSize(36,36));
        }
    }
    enableBoard(false);
    ui->pBready_on->setEnabled(false);
    ui->pBready_off->setEnabled(false);
    ui->pBme->setEnabled(false);
    ui->pBai->setEnabled(false);
    ui->pBoto->setEnabled(false);
    ui->pBota->setEnabled(false);
    ui->pBata->setEnabled(false);

}




void MyFunc::enableBoard(bool bit)
{
    QString temp;
    for(int i=0;i<15;i++){
        for(int j=0;j<15;j++){
            temp = QString("map_%1_%2").arg(QString::number(i)).arg(QString::number(j));
            my_map[temp]->setEnabled(bit);
        }
    }

}

void MyFunc::mapping()
{

    my_map["map_0_0"] = ui->map_0_0;
    my_map["map_0_1"] = ui->map_0_1;
    my_map["map_0_2"] = ui->map_0_2;
    my_map["map_0_3"] = ui->map_0_3;
    my_map["map_0_4"] = ui->map_0_4;
    my_map["map_0_5"] = ui->map_0_5;
    my_map["map_0_6"] = ui->map_0_6;
    my_map["map_0_7"] = ui->map_0_7;
    my_map["map_0_8"] = ui->map_0_8;
    my_map["map_0_9"] = ui->map_0_9;
    my_map["map_0_10"] = ui->map_0_10;
    my_map["map_0_11"] = ui->map_0_11;
    my_map["map_0_12"] = ui->map_0_12;
    my_map["map_0_13"] = ui->map_0_13;
    my_map["map_0_14"] = ui->map_0_14;
    //
    my_map["map_1_0"] = ui->map_1_0;
    my_map["map_1_1"] = ui->map_1_1;
    my_map["map_1_2"] = ui->map_1_2;
    my_map["map_1_3"] = ui->map_1_3;
    my_map["map_1_4"] = ui->map_1_4;
    my_map["map_1_5"] = ui->map_1_5;
    my_map["map_1_6"] = ui->map_1_6;
    my_map["map_1_7"] = ui->map_1_7;
    my_map["map_1_8"] = ui->map_1_8;
    my_map["map_1_9"] = ui->map_1_9;
    my_map["map_1_10"] = ui->map_1_10;
    my_map["map_1_11"] = ui->map_1_11;
    my_map["map_1_12"] = ui->map_1_12;
    my_map["map_1_13"] = ui->map_1_13;
    my_map["map_1_14"] = ui->map_1_14;
    //
    my_map["map_2_0"] = ui->map_2_0;
    my_map["map_2_1"] = ui->map_2_1;
    my_map["map_2_2"] = ui->map_2_2;
    my_map["map_2_3"] = ui->map_2_3;
    my_map["map_2_4"] = ui->map_2_4;
    my_map["map_2_5"] = ui->map_2_5;
    my_map["map_2_6"] = ui->map_2_6;
    my_map["map_2_7"] = ui->map_2_7;
    my_map["map_2_8"] = ui->map_2_8;
    my_map["map_2_9"] = ui->map_2_9;
    my_map["map_2_10"] = ui->map_2_10;
    my_map["map_2_11"] = ui->map_2_11;
    my_map["map_2_12"] = ui->map_2_12;
    my_map["map_2_13"] = ui->map_2_13;
    my_map["map_2_14"] = ui->map_2_14;
    //
    my_map["map_3_0"] = ui->map_3_0;
    my_map["map_3_1"] = ui->map_3_1;
    my_map["map_3_2"] = ui->map_3_2;
    my_map["map_3_3"] = ui->map_3_3;
    my_map["map_3_4"] = ui->map_3_4;
    my_map["map_3_5"] = ui->map_3_5;
    my_map["map_3_6"] = ui->map_3_6;
    my_map["map_3_7"] = ui->map_3_7;
    my_map["map_3_8"] = ui->map_3_8;
    my_map["map_3_9"] = ui->map_3_9;
    my_map["map_3_10"] = ui->map_3_10;
    my_map["map_3_11"] = ui->map_3_11;
    my_map["map_3_12"] = ui->map_3_12;
    my_map["map_3_13"] = ui->map_3_13;
    my_map["map_3_14"] = ui->map_3_14;
    //
    my_map["map_4_0"] = ui->map_4_0;
    my_map["map_4_1"] = ui->map_4_1;
    my_map["map_4_2"] = ui->map_4_2;
    my_map["map_4_3"] = ui->map_4_3;
    my_map["map_4_4"] = ui->map_4_4;
    my_map["map_4_5"] = ui->map_4_5;
    my_map["map_4_6"] = ui->map_4_6;
    my_map["map_4_7"] = ui->map_4_7;
    my_map["map_4_8"] = ui->map_4_8;
    my_map["map_4_9"] = ui->map_4_9;
    my_map["map_4_10"] = ui->map_4_10;
    my_map["map_4_11"] = ui->map_4_11;
    my_map["map_4_12"] = ui->map_4_12;
    my_map["map_4_13"] = ui->map_4_13;
    my_map["map_4_14"] = ui->map_4_14;
    //
    my_map["map_5_0"] = ui->map_5_0;
    my_map["map_5_1"] = ui->map_5_1;
    my_map["map_5_2"] = ui->map_5_2;
    my_map["map_5_3"] = ui->map_5_3;
    my_map["map_5_4"] = ui->map_5_4;
    my_map["map_5_5"] = ui->map_5_5;
    my_map["map_5_6"] = ui->map_5_6;
    my_map["map_5_7"] = ui->map_5_7;
    my_map["map_5_8"] = ui->map_5_8;
    my_map["map_5_9"] = ui->map_5_9;
    my_map["map_5_10"] = ui->map_5_10;
    my_map["map_5_11"] = ui->map_5_11;
    my_map["map_5_12"] = ui->map_5_12;
    my_map["map_5_13"] = ui->map_5_13;
    my_map["map_5_14"] = ui->map_5_14;
    //
    my_map["map_6_0"] = ui->map_6_0;
    my_map["map_6_1"] = ui->map_6_1;
    my_map["map_6_2"] = ui->map_6_2;
    my_map["map_6_3"] = ui->map_6_3;
    my_map["map_6_4"] = ui->map_6_4;
    my_map["map_6_5"] = ui->map_6_5;
    my_map["map_6_6"] = ui->map_6_6;
    my_map["map_6_7"] = ui->map_6_7;
    my_map["map_6_8"] = ui->map_6_8;
    my_map["map_6_9"] = ui->map_6_9;
    my_map["map_6_10"] = ui->map_6_10;
    my_map["map_6_11"] = ui->map_6_11;
    my_map["map_6_12"] = ui->map_6_12;
    my_map["map_6_13"] = ui->map_6_13;
    my_map["map_6_14"] = ui->map_6_14;
    //
    my_map["map_7_0"] = ui->map_7_0;
    my_map["map_7_1"] = ui->map_7_1;
    my_map["map_7_2"] = ui->map_7_2;
    my_map["map_7_3"] = ui->map_7_3;
    my_map["map_7_4"] = ui->map_7_4;
    my_map["map_7_5"] = ui->map_7_5;
    my_map["map_7_6"] = ui->map_7_6;
    my_map["map_7_7"] = ui->map_7_7;
    my_map["map_7_8"] = ui->map_7_8;
    my_map["map_7_9"] = ui->map_7_9;
    my_map["map_7_10"] = ui->map_7_10;
    my_map["map_7_11"] = ui->map_7_11;
    my_map["map_7_12"] = ui->map_7_12;
    my_map["map_7_13"] = ui->map_7_13;
    my_map["map_7_14"] = ui->map_7_14;
    //
    my_map["map_8_0"] = ui->map_8_0;
    my_map["map_8_1"] = ui->map_8_1;
    my_map["map_8_2"] = ui->map_8_2;
    my_map["map_8_3"] = ui->map_8_3;
    my_map["map_8_4"] = ui->map_8_4;
    my_map["map_8_5"] = ui->map_8_5;
    my_map["map_8_6"] = ui->map_8_6;
    my_map["map_8_7"] = ui->map_8_7;
    my_map["map_8_8"] = ui->map_8_8;
    my_map["map_8_9"] = ui->map_8_9;
    my_map["map_8_10"] = ui->map_8_10;
    my_map["map_8_11"] = ui->map_8_11;
    my_map["map_8_12"] = ui->map_8_12;
    my_map["map_8_13"] = ui->map_8_13;
    my_map["map_8_14"] = ui->map_8_14;
    //
    my_map["map_9_0"] = ui->map_9_0;
    my_map["map_9_1"] = ui->map_9_1;
    my_map["map_9_2"] = ui->map_9_2;
    my_map["map_9_3"] = ui->map_9_3;
    my_map["map_9_4"] = ui->map_9_4;
    my_map["map_9_5"] = ui->map_9_5;
    my_map["map_9_6"] = ui->map_9_6;
    my_map["map_9_7"] = ui->map_9_7;
    my_map["map_9_8"] = ui->map_9_8;
    my_map["map_9_9"] = ui->map_9_9;
    my_map["map_9_10"] = ui->map_9_10;
    my_map["map_9_11"] = ui->map_9_11;
    my_map["map_9_12"] = ui->map_9_12;
    my_map["map_9_13"] = ui->map_9_13;
    my_map["map_9_14"] = ui->map_9_14;
    //
    my_map["map_10_0"] = ui->map_10_0;
    my_map["map_10_1"] = ui->map_10_1;
    my_map["map_10_2"] = ui->map_10_2;
    my_map["map_10_3"] = ui->map_10_3;
    my_map["map_10_4"] = ui->map_10_4;
    my_map["map_10_5"] = ui->map_10_5;
    my_map["map_10_6"] = ui->map_10_6;
    my_map["map_10_7"] = ui->map_10_7;
    my_map["map_10_8"] = ui->map_10_8;
    my_map["map_10_9"] = ui->map_10_9;
    my_map["map_10_10"] = ui->map_10_10;
    my_map["map_10_11"] = ui->map_10_11;
    my_map["map_10_12"] = ui->map_10_12;
    my_map["map_10_13"] = ui->map_10_13;
    my_map["map_10_14"] = ui->map_10_14;
    //
    my_map["map_11_0"] = ui->map_11_0;
    my_map["map_11_1"] = ui->map_11_1;
    my_map["map_11_2"] = ui->map_11_2;
    my_map["map_11_3"] = ui->map_11_3;
    my_map["map_11_4"] = ui->map_11_4;
    my_map["map_11_5"] = ui->map_11_5;
    my_map["map_11_6"] = ui->map_11_6;
    my_map["map_11_7"] = ui->map_11_7;
    my_map["map_11_8"] = ui->map_11_8;
    my_map["map_11_9"] = ui->map_11_9;
    my_map["map_11_10"] = ui->map_11_10;
    my_map["map_11_11"] = ui->map_11_11;
    my_map["map_11_12"] = ui->map_11_12;
    my_map["map_11_13"] = ui->map_11_13;
    my_map["map_11_14"] = ui->map_11_14;
    //
    my_map["map_12_0"] = ui->map_12_0;
    my_map["map_12_1"] = ui->map_12_1;
    my_map["map_12_2"] = ui->map_12_2;
    my_map["map_12_3"] = ui->map_12_3;
    my_map["map_12_4"] = ui->map_12_4;
    my_map["map_12_5"] = ui->map_12_5;
    my_map["map_12_6"] = ui->map_12_6;
    my_map["map_12_7"] = ui->map_12_7;
    my_map["map_12_8"] = ui->map_12_8;
    my_map["map_12_9"] = ui->map_12_9;
    my_map["map_12_10"] = ui->map_12_10;
    my_map["map_12_11"] = ui->map_12_11;
    my_map["map_12_12"] = ui->map_12_12;
    my_map["map_12_13"] = ui->map_12_13;
    my_map["map_12_14"] = ui->map_12_14;
    //
    my_map["map_13_0"] = ui->map_13_0;
    my_map["map_13_1"] = ui->map_13_1;
    my_map["map_13_2"] = ui->map_13_2;
    my_map["map_13_3"] = ui->map_13_3;
    my_map["map_13_4"] = ui->map_13_4;
    my_map["map_13_5"] = ui->map_13_5;
    my_map["map_13_6"] = ui->map_13_6;
    my_map["map_13_7"] = ui->map_13_7;
    my_map["map_13_8"] = ui->map_13_8;
    my_map["map_13_9"] = ui->map_13_9;
    my_map["map_13_10"] = ui->map_13_10;
    my_map["map_13_11"] = ui->map_13_11;
    my_map["map_13_12"] = ui->map_13_12;
    my_map["map_13_13"] = ui->map_13_13;
    my_map["map_13_14"] = ui->map_13_14;
    //
    my_map["map_14_0"] = ui->map_14_0;
    my_map["map_14_1"] = ui->map_14_1;
    my_map["map_14_2"] = ui->map_14_2;
    my_map["map_14_3"] = ui->map_14_3;
    my_map["map_14_4"] = ui->map_14_4;
    my_map["map_14_5"] = ui->map_14_5;
    my_map["map_14_6"] = ui->map_14_6;
    my_map["map_14_7"] = ui->map_14_7;
    my_map["map_14_8"] = ui->map_14_8;
    my_map["map_14_9"] = ui->map_14_9;
    my_map["map_14_10"] = ui->map_14_10;
    my_map["map_14_11"] = ui->map_14_11;
    my_map["map_14_12"] = ui->map_14_12;
    my_map["map_14_13"] = ui->map_14_13;
    my_map["map_14_14"] = ui->map_14_14;
}

