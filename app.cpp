
#include <QApplication>
#include <QDebug>
#include <QListWidget>
#include <QProcess>
#include <locale>
#include <QResource>

#include "nixieclock.h"


int main(int argc, char **argv)
{
QApplication a(argc, argv);
// QResource::registerResource("myres.rcc");
//setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

 NixieClock clock;
 clock.show();
 a.exec();
 

}

