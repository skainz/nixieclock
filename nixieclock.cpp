#include <QtWidgets>
#include "nixieclock.h"

#define WIDTH 200
#define HEIGHT 200
#define SPACE_DIGITS 25
#define SPACE_HMS 50

NixieClock::NixieClock(QWidget *parent) : QWidget(parent,Qt::FramelessWindowHint | Qt::WindowSystemMenuHint)
{
  
  resultimage=new QImage(QSize(6*WIDTH+2*SPACE_HMS+3*SPACE_DIGITS,HEIGHT),QImage::Format_RGB32);
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
  QTime time = QTime::currentTime();
  
  QPainter painter(resultimage);;
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
  
  


}
