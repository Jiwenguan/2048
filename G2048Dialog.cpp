#include "G2048Dialog.h"
#include "ui_G2048Dialog.h"

G2048Dialog::G2048Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::G2048Dialog)
{
    ui->setupUi(this);
    //将数组和label匹配
    match();
    //方向数组赋初值
    direct[0]=0;direct[1]=0;
    //int数组赋初值
    vector.resize(6);
    for(int i=0;i<6;i++){
        vector[i].resize(6);
        vector[i].fill(0,6);
    }
    //画背景图
    QPainter painter(this);
    QImage image("./background.PNG");
    QRect rect(1,1,441+81,454+81);
    painter.drawImage(QPoint(1,1),image);


    score=0;
    display();
    this->grabKeyboard();
}
G2048Dialog::~G2048Dialog()
{
    delete ui;
}
void G2048Dialog::keyReleaseEvent(QKeyEvent* event){
    qDebug()<<"按键代码： "<<event->key();
}
void G2048Dialog::keyPressEvent(QKeyEvent *event){
    //每次按下键盘的操作：1)所有元素朝那个方向移动，如果相同则合并
    //分数+合并了那个数字。2）重复1的动作，直到没有任何合并为止
    //3）进行生产
    qDebug()<<"keyPressEvent";
    if(event->key()==Qt::Key_Up){
        direct[0]=-1;direct[1]=0;
    }else if(event->key()==Qt::Key_Down){
        direct[0]=+1;direct[1]=0;
    }else if(event->key()==Qt::Key_Left){
        direct[0]=0;direct[1]=-1;
    }else if(event->key()==Qt::Key_Right){
        direct[0]=0;direct[1]=+1;
    }
    merge();

    produce();
    if(!isFull())produce();
}
//用于合并数字及移动图像的函数
void G2048Dialog::merge(void)
{
    qDebug()<<"merge()";
    if(direct[0]==0&&direct[1]==+1){//right
    for(int i=0;i<6;i++){//
            for(int j=5;j>0;j--){//不需判断越界比较，就比较五次即可
               if((vector[i][j-1]!=0)&&
                       (vector[i][j]==vector[i][j-1]||
                        vector[i][j]==0)){
                   vector[i][j]+=vector[i][j-1];
                   vector[i][j-1]=0;
                   display();
               }
            }
        }
    }
    if(direct[0]==0&&direct[1]==-1){//left
    for(int i=0;i<6;i++){//
            for(int j=0;j<5;j++){//不需判断越界比较，就比较五次即可
               //两者相同且不为0则moveOnce
               if((vector[i][j+1]!=0)&&
                       (vector[i][j]==vector[i][j+1]||
                        vector[i][j]==0)){
                   vector[i][j]+=vector[i][j+1];
                   vector[i][j+1]=0;
                   display();
               }
            }
        }
    }
    if(direct[0]==-1&&direct[1]==0){//up
    for(int j=0;j<6;j++){//
            for(int i=0;i<5;i++){//不需判断越界比较，就比较五次即可
               //两者相同且不为0则moveOnce
               if((vector[i+1][j]!=0)&&
                       (vector[i][j]==vector[i+1][j]||
                        vector[i][j]==0)){
                   vector[i][j]+=vector[i+1][j];
                   vector[i+1][j]=0;
                   display();
               }
            }
        }
    }
    if(direct[0]==+1&&direct[1]==0){//down
    for(int j=0;j<6;j++){//
            for(int i=5;i>0;i--){//不需判断越界比较，就比较五次即可
               //两者相同且不为0则moveOnce
               if((vector[i-1][j]!=0)&&
                       (vector[i][j]==vector[i-1][j]||
                        vector[i][j]==0)){
                   vector[i][j]+=vector[i-1][j];
                   vector[i-1][j]=0;
                   display();
               }
            }
        }
    }
    if(isNeedMerge(direct[0],direct[1]))//递归调用merge
       merge();
    return ;
}
#if 0
//移动一个label到另一个label处
void G2048Dialog::moveOnce(QLabel* msrc,QLabel* mdes)
{
    qDebug()<<"moveOnce()";
    //调用多线程msrc移动到mdes的位置
    WorkerThread *threadA=new WorkerThread;
    threadA->p_src=msrc;
    threadA->p_des=mdes;
    threadA->myWidget.setParent(this);
    threadA->start();
    //考虑在哪个地方加terminate和wait
}
#endif
bool G2048Dialog::isFull(void){//判断位置是否为满
    qDebug()<<"isFull()";
    for(int i=0;i<6;i++){
           for(int j=0;j<6;j++){
              if(vector[i][j]==0){
                  return false;//还有空位
              }
           }
       }
   return true;//代表满了
}
void G2048Dialog::produce(void){//生产数字2的点
    if(isFull()==false){
        int a=qrand()%6;
        int b=qrand()%6;
        if(vector[a][b]==0){
            qDebug()<<"produce()";
            vector[a][b]=2;
            display();
        }else
            produce();
    }else if(isNeedMerge(1,0)||isNeedMerge(-1,0)||isNeedMerge(0,1)||isNeedMerge(0,-1)){}
    else{

        QMessageBox msg(QMessageBox::Information,
                        QString("full"),QString("已经满啦"),
                        QMessageBox::Ok,this);
        msg.exec();
        this->close();
    }
    return ;
}
void G2048Dialog::on_startButton_clicked()
{
    qDebug()<<"startButton_clicked";
    score=0;
    //vector空间置0
    for(int i=0;i<6;i++){
        vector[i].fill(0,6);
    }
    produce();
    produce();
}

void G2048Dialog::on_exitButton_clicked()
{
    qDebug()<<"exitButton_clicked";
    //释放vector空间
    for(int i=0;i<6;i++){
        vector[i].clear();
    }
    vector.clear();
    QMessageBox msg(QMessageBox::Information,
          QString("close"),QString("您的分数为%1").arg(score),
          QMessageBox::Ok,this);
    msg.exec();
    this->close();
}
//用于在界面上显示数字的函数
void G2048Dialog::display(){
    score=0;
    for(int i=0;i<6;i++){//
         for(int j=0;j<6;j++){
             score+=vector[i][j];
         }
    }
    ui->scorelabel->setNum(score);
    qDebug()<<"display()...";
    //不同的数字按照不同的颜色显示出来。
    for(int i=0;i<6;i++){
        for(int j=0;j<6;j++){
            plabel[i][j]->setText(vector[i][j]?
                      QString("<h1 style = 'color:%1'>%2</h1>"
                      ).arg(pcolor(vector[i][j])).arg(vector[i][j]):"");

         }
    }
}
//判断是否已经需要合并,true代表需要，false代表不需要
bool G2048Dialog::isNeedMerge(int dir0, int dir1)
{
    qDebug()<<"isNeedMerge";
    if(dir0==0&&dir1==+1){//right
    for(int i=0;i<6;i++){//
            for(int j=5;j>0;j--){//不需判断越界比较，就比较五次即可
               //两者相同且不为0则moveOnce
               if((vector[i][j-1]!=0)&&
                       (vector[i][j]==vector[i][j-1]||
                        vector[i][j]==0)){
                   return true;
               }
            }
        }
    }
    if(dir0==0&&dir1==-1){//left
    for(int i=0;i<6;i++){//
            for(int j=0;j<5;j++){//不需判断越界比较，就比较五次即可
               //两者相同且不为0则moveOnce
               if((vector[i][j+1]!=0)&&
                       (vector[i][j]==vector[i][j+1]||
                        vector[i][j]==0)){
                  return true;
               }
            }
        }
    }
    if(dir0==-1&&dir1==0){//up
    for(int j=0;j<6;j++){//
            for(int i=0;i<5;i++){//不需判断越界比较，就比较五次即可
               //两者相同且不为0则moveOnce
               if((vector[i+1][j]!=0)&&
                       (vector[i][j]==vector[i+1][j]||
                        vector[i][j]==0)){
                  return true;
               }
            }
        }
    }
    if(dir0==+1&&dir1==0){//down
    for(int j=0;j<6;j++){//
            for(int i=5;i>0;i--){//不需判断越界比较，就比较五次即可
               //两者相同且不为0则moveOnce
               if((vector[i-1][j]!=0)&&
                       (vector[i][j]==vector[i-1][j]||
                        vector[i][j]==0)){
                   return true;
               }
            }
        }
    }
    return false;
}
//用于把存储label容器的容器和组件匹配
void G2048Dialog::match(){
//    注释的这种方法也是可以的
//    plabel.resize(6);
//    for(int i=0;i<6;i++){
//        plabel[i].resize(6);
//    }
//    plabel[0][0] =ui->label_00;
    qDebug()<<"match()";
    QVector<QLabel*> pl;
    pl.push_back(ui->label_00);
    pl.push_back(ui->label_01);
    pl.push_back(ui->label_02);
    pl.push_back(ui->label_03);
    pl.push_back(ui->label_04);
    pl.push_back(ui->label_05);
    plabel.push_back(pl);
    pl.clear();
    pl.push_back(ui->label_10);
    pl.push_back(ui->label_11);
    pl.push_back(ui->label_12);
    pl.push_back(ui->label_13);
    pl.push_back(ui->label_14);
    pl.push_back(ui->label_15);
    plabel.push_back(pl);
    pl.clear();
    pl.push_back(ui->label_20);
    pl.push_back(ui->label_21);
    pl.push_back(ui->label_22);
    pl.push_back(ui->label_23);
    pl.push_back(ui->label_24);
    pl.push_back(ui->label_25);
    plabel.push_back(pl);
    pl.clear();
    pl.push_back(ui->label_30);
    pl.push_back(ui->label_31);
    pl.push_back(ui->label_32);
    pl.push_back(ui->label_33);
    pl.push_back(ui->label_34);
    pl.push_back(ui->label_35);
    plabel.push_back(pl);
    pl.clear();
    pl.push_back(ui->label_40);
    pl.push_back(ui->label_41);
    pl.push_back(ui->label_42);
    pl.push_back(ui->label_43);
    pl.push_back(ui->label_44);
    pl.push_back(ui->label_45);
    plabel.push_back(pl);
    pl.clear();
    pl.push_back(ui->label_50);
    pl.push_back(ui->label_51);
    pl.push_back(ui->label_52);
    pl.push_back(ui->label_53);
    pl.push_back(ui->label_54);
    pl.push_back(ui->label_55);
    plabel.push_back(pl);
    pl.clear();
}

QString G2048Dialog::pcolor(int number){
    qDebug()<<"pcolor";
    QString str;
    switch(number){
    case 2:
        str=QString("#EE9A00");break;
    case 4:
        str=QString("#EE8262");break;
    case 8:
        str=QString("#FF8C69");break;
    case 16:
        str=QString("#FF8247");break;
    case 32:
        str=QString("#FF7256");break;
    case 64:
        str=QString("#FF6347");break;
    case 128:
        str=QString("#FF34B3");break;
    case 256:
        str=QString("#FF0000");break;
    case 512:
        str=QString("#8B4513");break;
    case 1024:
        str=QString("#8B3626");break;
    case 2048:
        str=QString("#492020");break;
    case 4096:
        str=QString("#8B0A50");break;
    case 8192:
        str=QString("##87CEEB");break;
    case 16384:
        str=QString("#492020");break;

    }
    return str;
}























