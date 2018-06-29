#include "movethread.h"

WorkerThread::WorkerThread()
{
}

WorkerThread::~WorkerThread()
{
}
//2)重写run函数
void WorkerThread::run(void)
{

    myWidget.setText(QString("AAAAAAAAAAAAA"));
    myWidget.setFrameRect(QRect(1,1,82,82));
    myWidget.setAutoFillBackground(true);
    //myWidget.setPixmap(QString("./hello.jpg"));
    myWidget.show();
    qDebug()<<p_src->geometry().x();
    qDebug()<<p_src->geometry().y();
    qDebug()<<p_src->geometry().height();
    qDebug()<<p_src->geometry().width();
    qDebug()<<p_des->geometry().x();
    qDebug()<<p_des->geometry().y();
    qDebug()<<p_des->geometry().height();
    qDebug()<<p_des->geometry().width();
    QPropertyAnimation *animation = new QPropertyAnimation(&myWidget,"geometry");
    animation->setDuration(1000);
//    animation->setStartValue(p_src->geometry());
//    animation->setEndValue(p_des->geometry());
    animation->setStartValue(QRect(1,1,400,400));
    animation->setEndValue(QRect(400,400,200,200));
    animation->start();
}




