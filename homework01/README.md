# 作业1说明文档

备注：所有文件包括注释所使用的编码是utf-8

## 第1题
建议在终端输入命令行为

g++ main.cpp Member.cpp MemberList.cpp -o main

生成main可执行文件，然后再运行：

./main

输出结果：
```
Zhang San, 22
Li Si, 19
Wang Wu, 18
Zhao Liu, 24
?, 0
22
19
18
24
0
```
这里的默认构造函数：根据题意，剩下一个人不知道名字和年龄，从而将name初始化为"?"，年龄初始化为0
第二部分，由于"Pin Yin"在map中查不到此字符串的数据，从而输出为0

## 第2题
可以直接编译运行，因为只有一个cpp文件。也可命令行输入

g++ main.cpp -o main

然后运行main

./main

输出结果为：
```
Area is 12.5664
Area is 12
Area is 25
Area is 16
```
与题目要求相符

## 第3题
可直接编译运行，因为只有一个cpp文件。也可命令行输入

g++ main.cpp -o main

然后运行main

输出结果为
```
Max(i, j): 2
Max(f1, f2): 22.2
Max(s1, s2): BBBBB
```

