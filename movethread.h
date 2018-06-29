#ifndef MOVETHREAD
#define MOVETHREAD

#include <QThread>
#include <QObject>
#include <QVector>
#include <QLabel>
#include <QDebug>
#include <QPropertyAnimation>
//1)继承QThread
class WorkerThread:public QThread
{
public:
    WorkerThread();
    ~WorkerThread();
protected:
    //2)重写run函数
    void run(void);
public:
    QLabel * p_src;//源位置
    QLabel * p_des;//终位置
    QLabel  myWidget;//负责移动的那个label
};

#endif // MOVETHREAD

