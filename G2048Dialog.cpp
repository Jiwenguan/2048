#include "G2048Dialog.h"
#include "ui_G2048Dialog.h"

G2048Dialog::G2048Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::G2048Dialog)
{
    ui->setupUi(this);
    qsrand(QTime::currentTime().msecsSinceStartOfDay());
    direct[0]=0;direct[1]=0;
    vector.resize(6);
    for(int i=0;i<6;i++){
        vector[i].resize(6);
        vector[i].fill(0,6);
    }
//    for(int i=0;i<6;i++){
//        for(int j=0;j<6;j++){
//           qDebug()<<vector[i][j];
//        }
//    }
}
G2048Dialog::~G2048Dialog()
{
    delete ui;
}
void G2048Dialog::keyPressEvent(QKeyEvent * event)
{
    //每次按下键盘的操作：1)所有元素朝那个方向移动，如果相同则合并
    //分数+合并了那个数字。2）重复1的动作，直到没有任何合并为止
    //3）进行生产
    if(event->key()==Qt::Key_Up){
        direct[0]=0;direct[1]=0;
    }else if(event->key()==Qt::Key_Down){

    }else if(event->key()==Qt::Key_Left){

    }else if(event->key()==Qt::Key_Right){

    }
}
void G2048Dialog::keyReleaseEvent(QKeyEvent* event){
    qDebug()<<"按键代码： "<<event->key();
}
bool G2048Dialog::isFull(void){//判断位置是否为满
   for(int i=0;i<6;i++){
           for(int j=0;j<6;j++){
              if(vector[i][j]==0){
                  return false;
              }
           }
       }
   return true;
}
void G2048Dialog::produce(void){//生产数字2的点
    int a=qrand()%6;
    int b=qrand()%6;
    if(vector[a][b]==0){
        vector[a][b]=2;
        return ;
    }
    produce();
    return ;
}
void G2048Dialog::on_startButton_clicked()
{
    //vector空间置0
    for(int i=0;i<6;i++){
        vector[i].fill(0,6);
    }
    produce();
    produce();
}

void G2048Dialog::on_exitButton_clicked()
{
    isStarted=false;
    //释放vector空间
    for(int i=0;i<6;i++){
        vector[i].clear();
    }
    vector.clear();
}
