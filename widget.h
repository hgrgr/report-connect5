#ifndef WIDGET_H
#define WIDGET_H

//#include <QWidget>
#include "pch.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    Ui::Widget *ui;
    QPixmap pan[3];

private slots:

    void on_pBconnect_clicked();

    void on_pBready_on_clicked();

    void on_pBready_off_clicked();

    void on_pBdiscon_clicked();

    void on_pBlocal_clicked();

    void on_pBme_clicked();

    void on_pBai_clicked();

    void on_pBoto_clicked();

    void on_pBota_clicked();

    void on_pBata_clicked();

    void on_map_0_0_clicked();
    void on_map_0_1_clicked();
    void on_map_0_2_clicked();
    void on_map_0_3_clicked();
    void on_map_0_4_clicked();
    void on_map_0_5_clicked();
    void on_map_0_6_clicked();
    void on_map_0_7_clicked();
    void on_map_0_8_clicked();
    void on_map_0_9_clicked();
    void on_map_0_10_clicked();
    void on_map_0_11_clicked();
    void on_map_0_12_clicked();
    void on_map_0_13_clicked();
    void on_map_0_14_clicked();
    void on_map_1_0_clicked();
    void on_map_1_1_clicked();
    void on_map_1_2_clicked();
    void on_map_1_3_clicked();
    void on_map_1_4_clicked();
    void on_map_1_5_clicked();
    void on_map_1_6_clicked();
    void on_map_1_7_clicked();
    void on_map_1_8_clicked();
    void on_map_1_9_clicked();
    void on_map_1_10_clicked();
    void on_map_1_11_clicked();
    void on_map_1_12_clicked();
    void on_map_1_13_clicked();
    void on_map_1_14_clicked();
    void on_map_2_0_clicked();
    void on_map_2_1_clicked();
    void on_map_2_2_clicked();
    void on_map_2_3_clicked();
    void on_map_2_4_clicked();
    void on_map_2_5_clicked();
    void on_map_2_6_clicked();
    void on_map_2_7_clicked();
    void on_map_2_8_clicked();
    void on_map_2_9_clicked();
    void on_map_2_10_clicked();
    void on_map_2_11_clicked();
    void on_map_2_12_clicked();
    void on_map_2_13_clicked();
    void on_map_2_14_clicked();
    void on_map_3_0_clicked();
    void on_map_3_1_clicked();
    void on_map_3_2_clicked();
    void on_map_3_3_clicked();
    void on_map_3_4_clicked();
    void on_map_3_5_clicked();
    void on_map_3_6_clicked();
    void on_map_3_7_clicked();
    void on_map_3_8_clicked();
    void on_map_3_9_clicked();
    void on_map_3_10_clicked();
    void on_map_3_11_clicked();
    void on_map_3_12_clicked();
    void on_map_3_13_clicked();
    void on_map_3_14_clicked();
    void on_map_4_0_clicked();
    void on_map_4_1_clicked();
    void on_map_4_2_clicked();
    void on_map_4_3_clicked();
    void on_map_4_4_clicked();
    void on_map_4_5_clicked();
    void on_map_4_6_clicked();
    void on_map_4_7_clicked();
    void on_map_4_8_clicked();
    void on_map_4_9_clicked();
    void on_map_4_10_clicked();
    void on_map_4_11_clicked();
    void on_map_4_12_clicked();
    void on_map_4_13_clicked();
    void on_map_4_14_clicked();
    void on_map_5_0_clicked();
    void on_map_5_1_clicked();
    void on_map_5_2_clicked();
    void on_map_5_3_clicked();
    void on_map_5_4_clicked();
    void on_map_5_5_clicked();
    void on_map_5_6_clicked();
    void on_map_5_7_clicked();
    void on_map_5_8_clicked();
    void on_map_5_9_clicked();
    void on_map_5_10_clicked();
    void on_map_5_11_clicked();
    void on_map_5_12_clicked();
    void on_map_5_13_clicked();
    void on_map_5_14_clicked();
    void on_map_6_0_clicked();
    void on_map_6_1_clicked();
    void on_map_6_2_clicked();
    void on_map_6_3_clicked();
    void on_map_6_4_clicked();
    void on_map_6_5_clicked();
    void on_map_6_6_clicked();
    void on_map_6_7_clicked();
    void on_map_6_8_clicked();
    void on_map_6_9_clicked();
    void on_map_6_10_clicked();
    void on_map_6_11_clicked();
    void on_map_6_12_clicked();
    void on_map_6_13_clicked();
    void on_map_6_14_clicked();
    void on_map_7_0_clicked();
    void on_map_7_1_clicked();
    void on_map_7_2_clicked();
    void on_map_7_3_clicked();
    void on_map_7_4_clicked();
    void on_map_7_5_clicked();
    void on_map_7_6_clicked();
    void on_map_7_7_clicked();
    void on_map_7_8_clicked();
    void on_map_7_9_clicked();
    void on_map_7_10_clicked();
    void on_map_7_11_clicked();
    void on_map_7_12_clicked();
    void on_map_7_13_clicked();
    void on_map_7_14_clicked();
    void on_map_8_0_clicked();
    void on_map_8_1_clicked();
    void on_map_8_2_clicked();
    void on_map_8_3_clicked();
    void on_map_8_4_clicked();
    void on_map_8_5_clicked();
    void on_map_8_6_clicked();
    void on_map_8_7_clicked();
    void on_map_8_8_clicked();
    void on_map_8_9_clicked();
    void on_map_8_10_clicked();
    void on_map_8_11_clicked();
    void on_map_8_12_clicked();
    void on_map_8_13_clicked();
    void on_map_8_14_clicked();
    void on_map_9_0_clicked();
    void on_map_9_1_clicked();
    void on_map_9_2_clicked();
    void on_map_9_3_clicked();
    void on_map_9_4_clicked();
    void on_map_9_5_clicked();
    void on_map_9_6_clicked();
    void on_map_9_7_clicked();
    void on_map_9_8_clicked();
    void on_map_9_9_clicked();
    void on_map_9_10_clicked();
    void on_map_9_11_clicked();
    void on_map_9_12_clicked();
    void on_map_9_13_clicked();
    void on_map_9_14_clicked();
    void on_map_10_0_clicked();
    void on_map_10_1_clicked();
    void on_map_10_2_clicked();
    void on_map_10_3_clicked();
    void on_map_10_4_clicked();
    void on_map_10_5_clicked();
    void on_map_10_6_clicked();
    void on_map_10_7_clicked();
    void on_map_10_8_clicked();
    void on_map_10_9_clicked();
    void on_map_10_10_clicked();
    void on_map_10_11_clicked();
    void on_map_10_12_clicked();
    void on_map_10_13_clicked();
    void on_map_10_14_clicked();
    void on_map_11_0_clicked();
    void on_map_11_1_clicked();
    void on_map_11_2_clicked();
    void on_map_11_3_clicked();
    void on_map_11_4_clicked();
    void on_map_11_5_clicked();
    void on_map_11_6_clicked();
    void on_map_11_7_clicked();
    void on_map_11_8_clicked();
    void on_map_11_9_clicked();
    void on_map_11_10_clicked();
    void on_map_11_11_clicked();
    void on_map_11_12_clicked();
    void on_map_11_13_clicked();
    void on_map_11_14_clicked();
    void on_map_12_0_clicked();
    void on_map_12_1_clicked();
    void on_map_12_2_clicked();
    void on_map_12_3_clicked();
    void on_map_12_4_clicked();
    void on_map_12_5_clicked();
    void on_map_12_6_clicked();
    void on_map_12_7_clicked();
    void on_map_12_8_clicked();
    void on_map_12_9_clicked();
    void on_map_12_10_clicked();
    void on_map_12_11_clicked();
    void on_map_12_12_clicked();
    void on_map_12_13_clicked();
    void on_map_12_14_clicked();
    void on_map_13_0_clicked();
    void on_map_13_1_clicked();
    void on_map_13_2_clicked();
    void on_map_13_3_clicked();
    void on_map_13_4_clicked();
    void on_map_13_5_clicked();
    void on_map_13_6_clicked();
    void on_map_13_7_clicked();
    void on_map_13_8_clicked();
    void on_map_13_9_clicked();
    void on_map_13_10_clicked();
    void on_map_13_11_clicked();
    void on_map_13_12_clicked();
    void on_map_13_13_clicked();
    void on_map_13_14_clicked();
    void on_map_14_0_clicked();
    void on_map_14_1_clicked();
    void on_map_14_2_clicked();
    void on_map_14_3_clicked();
    void on_map_14_4_clicked();
    void on_map_14_5_clicked();
    void on_map_14_6_clicked();
    void on_map_14_7_clicked();
    void on_map_14_8_clicked();
    void on_map_14_9_clicked();
    void on_map_14_10_clicked();
    void on_map_14_11_clicked();
    void on_map_14_12_clicked();
    void on_map_14_13_clicked();
    void on_map_14_14_clicked();
};
#endif // WIDGET_H
