# MultithreadingSort
## 实验目的
编写一个多线程程序，它的工作如下：一个整数列表分为两个大小相等的较小子列表。两个单独线程（我们称它们为排序线程）采用你所选择的算法，对两个子列表进行排序。这两个子线程由第三个线程（称为合并线程）合并成一个已排好序的线程。<br>
这个编程项目需要传递参数给每个排序线程。特别地，有必要确定哪个线程从哪个索引开始排序。<br>
当所有排序线程退出后，父线程会输出排好序的数组（从小到大排列）。<br>
## 实现
### 1、接收参数
参数为被非数字字符间隔开的字符串，程序会读取输入并将数字部分提取出来存入int数组中。<br>
有两种方式可以接收参数：1、在命令行运行程序的同时输入文件名读取文件；<br>
       2、在运行以后输入数据
### 2、创建子线程调用快排

