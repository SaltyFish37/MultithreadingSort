# MultithreadingSort
## 实验目的
编写一个多线程程序，它的工作如下：一个整数列表分为两个大小相等的较小子列表。两个单独线程（我们称它们为排序线程）采用你所选择的算法，对两个子列表进行排序。这两个子线程由第三个线程（称为合并线程）合并成一个已排好序的线程。<br>
这个编程项目需要传递参数给每个排序线程。特别地，有必要确定哪个线程从哪个索引开始排序。<br>
当所有排序线程退出后，父线程会输出排好序的数组（从小到大排列）。<br>
## 实现
### 1、接收参数
参数为被非数字字符间隔开的字符串，程序会读取输入并将数字部分提取出来存入int数组中。<br>
有两种方式可以接收参数：<br>
>1、在命令行运行程序的同时输入文件名读取文件；<br>
>2、在运行以后输入数据
### 2、创建子线程进行排序
创建两个子线程，分别使用快速排序对数组的前一半和后一半进行排序
### 3、父线程合并排序
使用merge对前一半和后一半各自有序的数组进行合并，合并结果保存到一个新的数组中
### 4、输出结果
分别遍历并打印排序前后的数组
## 文件说明
sort.c为源程序，data.txt为数据文件（数据由随机数生成）<br>
编译通过后可以使用命令：<br>
>./sort data.txt<br>
或者：<br>
>./sort<br>
执行程序
## 注意
由于pthread库不是Linux系统默认的库，连接时需要使用到库libpthread.a,所以如果使用pthread_create创建线程，在编译过程中要加-lpthread参数:<br>
gcc -o sort sort.c -lpthread
