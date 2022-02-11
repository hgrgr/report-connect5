#ifndef PCH_H
#define PCH_H
#include <stdio.h>
#include <QThread>
#include <QDebug>
#include <QApplication>
#include <QtNetwork>
#include <QString>
#include <typeinfo>
#include <map>
#include <vector>
#include <array>
#include <qobjectdefs.h>
#include "ui_widget.h"
#include "connectserver.h"
#include "my_dataformat.h"
#include "widget.h"
#include "myfunc.h"
#include "game.h"

#define BUFSIZE 4

#define BLACK 0
#define WHITE 1

#define ME 1
#define AI 2

#define OTO 3
#define OTA 4
#define ATA 5

#define XMASK 0xF0
#define YMASK 0x0F
#define REMOTE 1
#define LOCAL 2

typedef unsigned char uint8_t;

#endif // PCH_H
