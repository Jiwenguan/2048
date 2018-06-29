# 2048
##2048简易版 6*6 易入手代码 qt C++
- 初步想法是QVector<QVector<int> >来存储每个位置上的数字，方便计算
- QVector<QVector<QLabel*> > plabel;用于存储界面组件，这样遍历就可以用下标，省代码量
- 还需要一个QVector<QVector<QLabel*> > amlabel;来控制动画效果
- 平常是隐藏的，当需要合并相邻两个或者移动某个的时候，可以将其赋值为其对应的plabel的值，然后进行move,覆盖终位置的时候，将其值赋值给终位置的plabel
- 接下来就可以隐藏了，然后再悄悄move回原位置。

#关于移动算法
- 目前仍在思考中。

##思路及界面颜色取自[2048小游戏](http://2048game.com/)
