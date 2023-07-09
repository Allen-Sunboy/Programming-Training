# 作业4说明文档

四个文件夹，problem1是第一题的源文件，problem1_release是第一题的release，其中有problem1.exe以及所需的dll文件，problem2同理。

## 第1题
按照题目要求，参考了课件所说的QSignalMapper方法。

程序主体是主窗口，给出键盘和clear键。

显示文本用的是QTextBrowser，好处在于一行内容满了会自动换下一行，且空间不够了会自带滚动条。

## 第2题
按照题目的要求，通过课件所给出的思路和信号槽的安排进行设置。

程序主体是主窗口，子对象有2个QGroupBox类和1个TempConverter类，2个groupbox又各自有2个子对象，是1个QDial类和1个QLCDNumber类。

关于群里说的华氏度的调节会导致摄氏度可能以5度5度变化的问题，在摄氏度和华氏度的转换时，使用了round()函数，四舍五入，
而不是直接强制将double转化为int，否则会直接舍去小数点后的内容而导致误差。
round()函数是在<cmath>中，但是在qt编译运行后是自带，直接使用。