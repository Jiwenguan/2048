#ifndef G2048DIALOG_H
#define G2048DIALOG_H

#define LABEL(i,j) label_##i##j
#include <QDialog>
#include <QTime>
#include <QDebug>
#include <QKeyEvent>
#include <QVector>
#include <QLabel>
#include <QPainter>
#include <QMessageBox>
namespace Ui {
class G2048Dialog;
}

class G2048Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit G2048Dialog(QWidget *parent = 0);
    ~G2048Dialog();

private slots:
    void on_startButton_clicked();

    void on_exitButton_clicked();
private:
    void keyPressEvent(QKeyEvent *event);
    //按键抬起时打印按键代码
    void keyReleaseEvent(QKeyEvent *event);
    bool isFull(void);//判断位置是否为满
    bool isNeedMerge(void);//判断是否已经需要合并
    void produce(void);//生产点2
    void merge();//用于合并数字及移动图像的函数
    void moveOnce(QLabel*,QLabel*);//移动一个label到另一个label处
    void display();//用于在界面上显示数字的函数
    void match();//用于把存储label容器的容器和组件匹配
    QString pcolor(int);//用于通过数字计算应该显示的颜色
private:
    Ui::G2048Dialog *ui;
    QVector<QVector<int> > vector;//二维数组容器
    bool isStarted;//判断游戏是否开始
    int score;//记录分数
    int direct[2];//第一个是行i，-1,1；第二个是列j，-1,1
    QVector<QVector<QLabel*> > plabel;//二维数组容器，用来存储label组件，用来遍历
    QVector<QVector<QLabel*> > amlabel;//二维数组容器，用来存储label组件，用来遍历
};

#endif // G2048DIALOG_H
