# 简介

一个Qt培训课程，小组做的项目。

从 https://github.com/verynewabie/sudoku fork过来的。

使用 Qt 5.15.2 (MSVC 2019 32-bit)

# 项目笔记

## 220805_shuffle

这个参考《编程之美》的数独生成算法太有规律了

![](pics/algo-pic.png)

甚至按照模式很快就能找到答案。

![](pics/algo-manner.jpg)

因此加了一个打乱函数：

前三列，中三列，后三列内部可以随意整列交换。

上三行，中三行，下三行内部可以随意整列交换。

## 220806_sudoku-SQLiteDemo

参考了 https://www.cnblogs.com/linuxAndMcu/p/11364071.html#_label2 的代码，其测试语句见 SQLite-refrence 目录。

照着简单改了下数据结构以及SQL语句，就拿过来用了。

按照学到的 Qt 知识，写了简单的数据生成功能，存入数据库，并展示。

如下图：

![](pics/sqlite_01.png)

![](pics/sqlite_02.png)

![](pics/sqlite_03.png)