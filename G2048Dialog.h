#ifndef G2048DIALOG_H
#define G2048DIALOG_H

#include <QDialog>
#include <QTime>
#include <QDebug>
#include <QKeyEvent>
#include <QVector>
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
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent*);
    bool isFull(void);//判断位置是否为满
    void produce(void);//生产点2
    void merge();//用于合并数字及移动图像的函数
private:
    Ui::G2048Dialog *ui;
    QVector<QVector<int> > vector;//二维数组容器
    bool isStarted;//判断游戏是否开始
    int score;//记录分数
    int direct[2];
};

#endif // G2048DIALOG_H
