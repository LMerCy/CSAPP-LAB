# cacheLab

解题思路：

解析命令 -> 初始化缓存模型 -> 获取内存读取信息 ->  缓存

### 1. 解析命令

使用getopt函数

### 2. 初始化缓存模型

首先构建和缓存相关的数据结构：cacheLine -> set -> cache

cacheline中包含标志位，有效位

set中就是cacheline的指针

cache中包含set的个数，以及每个set中cacheline的个数

初始化函数，首先从命令中获取s,E,b参数，根据三个参数分别确定Set的个数 = 1L << s;cacheline的个数 E ,因为不取数据，所以b是不需要的。初始化时使用malloc来分别分配cachline和set的内存。

### 3. 获取内存读取信息

按行读取文件内容，并对每行进行操作。注意文件中提供的地址是16进制的！

### 4. 缓存
0. 根据内存地址解析出cachline的信息。
1. 然后利用setindex来迅速定位在哪一个set，之后遍历set内部的cacheline来查看是否命中。
2. 不命中的话，首先看该set内有没有有效位为0的cacheline，有的话直接更新，不产生eviction；没有的话采取lru来选择牺牲行进行替换。
3. 实现lru的方法是在每个cacheline设置一个上一次使用的时间和一个全局的time，每次进行缓存操作时将这个time+1，并将这个time更新到对应的cacheline中。进行lru时，替换组内time最小的cacheline。

