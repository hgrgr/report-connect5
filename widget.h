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

private:
    Ui::Widget *ui;
    QPixmap pan[3];

};
#endif // WIDGET_H
