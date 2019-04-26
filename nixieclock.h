#ifndef NIXIECLOCK_H
#define NIXIECLOCK_H
#include <QSystemTrayIcon>
#include <QBoxLayout>
#include <QIcon>
#include <QLabel>

class NixieClock : public QWidget
{
    Q_OBJECT

public:
    NixieClock(QWidget *parent = 0);

private slots:
    void showTime();

private:
  QSystemTrayIcon *trayIcon;
  const QIcon *icon[10];
  QBoxLayout *layout;
  QLabel* labels[10];

  QLabel* nums[4];
  QImage *resultimage;//(QSize(4*45,64),QImage::Format_RGB32);
  QLabel *il;
  QImage *images[10];
};

#endif
