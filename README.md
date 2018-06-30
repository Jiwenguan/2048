# 2048
2048简易版 6*6 易入手代码 qt C++
=
- 用一张图片当做了背景版
- 初步想法是QVector<QVector<int> >来存储每个位置上的数字，方便计算
- QVector<QVector<QLabel*> > plabel;用于存储界面组件，这样遍历就可以用下标，省代码量
- 平常是隐藏的，当需要合并相邻两个或者移动某个的时候，可以将其赋值为其对应的plabel的值，然后进行move,覆盖终位置的时候，将其值赋值给终位置的plabel
- 接下来就可以隐藏了，然后再悄悄move回原位置。
- 动画用的是QPropertyAnimation类，其构造函数中第一个是组件，第二个是属性，两者都和该类对象绑定
- 设置该对象的setstartvalue和setendvalue,接下来start就可以了
- 在移动的过程中是有一个过程的，怎么样让数字和图像同步是一个很重要的问题
- 目前加的多线程并不能解决好这个问题，所以还是需要仔细考虑。
- 多线程的terminate和wait在何处加入也是一个问题
- 需解决动画显示在原先label之下的问题。

关于移动算法
=
- 已完成，目前是将四个方向分别写出，有待统一。int direction[2]

#思路及界面颜色取自[2048小游戏](http://2048game.com/)
