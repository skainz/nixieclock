#include <QtWidgets>
#include "nixieclock.h"
#include <QDesktopWidget>
// #include <QX11Info>
#include <QtX11Extras/QX11Info>
#include<X11/Xlib.h>
#include <X11/Xutil.h>

#define WIDTH 200
#define HEIGHT 200
#define SPACE_DIGITS 25
#define SPACE_HMS 50


NixieClock::NixieClock(QWidget *parent) : QWidget(parent,Qt::FramelessWindowHint | Qt::WindowSystemMenuHint)
{
  
    data = (char*)malloc(256*256*4);
  resultimage=new QImage(QSize(6*WIDTH+2*SPACE_HMS+3*SPACE_DIGITS,HEIGHT),QImage::Format_RGB32);


/*
    QDesktopWidget *qdw=QApplication::desktop();
    Display * x11 = QX11Info::display();
    Window root;
    GC g;
    root = DefaultRootWindow (x11);
    g = XCreateGC (x11, root, 0, NULL);
*/
  il=new QLabel();
  layout= new QBoxLayout(QBoxLayout::LeftToRight,this);
  
  for (int i=0;i<10;i++)
    {
      QString fn=QString().sprintf(":/digit%d",i);
      images[i]=new QImage(fn);
    }
  
  
  QPixmap *qp = new QPixmap();
  layout->setMargin(0);
  layout->setSpacing(0);
  layout->setContentsMargins(0,0,0,0);
  layout->addWidget(il);
  
  QTimer *timer= new QTimer(this);
  connect(timer, &QTimer::timeout, this, &NixieClock::showTime);
  timer->start(1000);
     showTime();
    
}

void NixieClock::showTime()
{

 QDesktopWidget *qdw=QApplication::desktop();
    Display * x11 = QX11Info::display();
    int screen_num = DefaultScreen(x11);
    Window root;
    GC g;
    root = DefaultRootWindow (x11);
    g = XCreateGC (x11, root, 0, NULL);

    Visual *visual = DefaultVisual(x11,DefaultScreen(x11));

     XSetForeground(x11, g, WhitePixelOfScreen(DefaultScreenOfDisplay(x11)) );
    ximage=XCreateImage(x11,visual,DefaultDepth(x11,DefaultScreen(x11)),ZPixmap,0,data,256,256,32,0);

  XFillRectangle (x11, root, g, random()%500, random()%500, 50, 40);




  QTime time = QTime::currentTime();
  
  QPainter painter(resultimage);;
//    painter.beginNativePainting();// begin(QApplication::desktop()->screen( 0 ));
    painter.fillRect(0,0,6*WIDTH+2*SPACE_HMS+3*SPACE_DIGITS,HEIGHT,Qt::black);
  //hours
  painter.drawImage(0,0,*images[time.hour() /10]);
  painter.drawImage(WIDTH+SPACE_DIGITS,0,*images[time.hour() % 10]);

  //minutes
  painter.drawImage(WIDTH*2+SPACE_DIGITS+SPACE_HMS,0,*images[time.minute() /10]);
  painter.drawImage(WIDTH*3+SPACE_DIGITS*2+SPACE_HMS,0,*images[time.minute() % 10]);

  //seconds
  painter.drawImage(WIDTH*4+SPACE_DIGITS*2+SPACE_HMS*2,0,*images[time.second() /10]);
  painter.drawImage(WIDTH*5+SPACE_DIGITS*3+SPACE_HMS*2,0,*images[time.second() % 10]);

  painter.end();
  
    il->setPixmap(QPixmap::fromImage(*resultimage));
  

 for (int x=0;x<200;x++)
    {
    for (int y=0;y<200;y++)
    {
    QColor p=resultimage->pixelColor(x+1000,y);
    int red=p.red()<<16|(p.green()<<8)|p.blue();
        XPutPixel(ximage,x,y,red);

    }
    }


   XPutImage(x11,root,DefaultGC(x11,screen_num),ximage,0,0,0,0,256,256);

    XFlush(x11);


  


}
