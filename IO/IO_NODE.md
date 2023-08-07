# IO 笔记

## 标准IO

### 概念

在C库中定义的一组用于输入输出的函数接口

### 特点

1. 通过缓冲机制减少系统调用，提高效率
2. 围绕流进行操作，流用FILE *表示
3. 标准IO默认打开了三个流，分别是stdin（标准输入） stdout（标准输出） stderr（标准错误）

### 缓冲机制

#### 全缓冲：跟文件相关

刷新缓冲的条件：

1. 程序正常退出
2. 缓冲区满
3. 强制刷新fflush

#### 行缓冲：跟终端相关

刷新缓冲的条件：

1. \n
2. 程序正常退出
3. 缓冲区满
4. 强制刷新fflush

#### 不缓冲：没有缓冲区，标准错误

### 标准IO函数接口

#### FILE * fopen(const char * path, const char * mode)

##### 功能：打开文件

##### 参数

1. path：打开的文件
2. mode：打开的方式

|打开方式|功能|
|:-:|:-:|
|r|只读，当文件不存在时报错，文件流定位到文件开头|
|r+|可读可写，当文件不存在时报错，文件流定位到文件开头|
|w|只写，文件不存在创建，存在清空|
|w+|可读可写，文件不存在创建，存在清空|
|a|追加(在末尾写),文件不存在创建，存在追加，文件流定位到文件末尾|
|a+|读和追加，文件不存在创建，存在追加，读文件流定位到文件开头，写文件流定位到文件末尾|


#### void perror(const char *s)

1. 功能: 根据errno值打印对应的错误信息
2. 参数：s:提示语句
3. 返回值：NULL

#### int fgetc(FILE * stream)

1. 功能：从文件中读取一个字符
2. 参数：stream：文件流
3. 返回值：成功：读到的字符 失败：读到文件末尾：EOF(-1)

#### int fputc(int c, FILE * stream)

1. 功能：向文件中写入一个字符
2. 参数：c：要写的字符  stream：文件流
3. 返回值：成功：写的字符的ASCII 失败：EOF

#### int feof(FILE * stream)

1. 功能：判断文件有没有到结尾
2. 参数：stream：文件流
3. 返回值：到达文件末尾，返回非零值

#### int ferror(FILE * stream)

1. 功能:检测文件有没有出错
2. 参数：stream：文件流
3. 返回：文件出错，返回非零值

#### char * fgets(char *s,  int size,  FILE * stream)

1. 功能：从文件中每次读取一行字符串
2. 参数：s：存放字符串的地址 size：一次读取的字符个数 stream：文件流
3. 返回值：成功：s的地址  失败或读到文件末尾：NULL
4. 特性：每次实际读取的字符个数为size-1个，会在末尾自动添加\0 每次读一行，遇到\n后不再继续读下一行

#### int fputs(const char * s,  FILE * stream)

1. 功能：向文件中写字符串
2. 参数：s：要写的内容 stream：文件流
3. 返回值：成功：非负整数 失败：EOF

#### size_t fread(void * ptr, size_t size, size_t nmemb, FILE * stream)

1. 功能：从文件流读取多个元素
2. 参数： ptr ：用来存放读取元素 size ：元素大小  sizeof(数据类型) nmemb ：读取元素的个数 stream ：要读取的文件
3. 返回值：成功：读取的元素的个数；读到文件尾： 0 失败： -1

#### size_t fwrite(const void * ptr, size_t size, size_t nmemb, FILE * stream);

1. 功能：按对象写
2. 参数： ptr ：用来存放读取元素 size ：元素大小  sizeof(数据类型) nmemb ：读取元素的个数 stream ：要读取的文件
3. 返回值：成功：写的元素个数 失败 ：-1

#### void rewind(FILE * stream)

1. 功能：将文件流指向文件开头
2. 参数：stream : 文件流

#### int fseek(FILE * stream, long offset, int whence)

1. 功能：文件的定位操作
2. 参数：stream：文件流 offset：偏移量：正数表示向后文件尾部偏移，负数表示向文件开头偏移 whence：相对位置：SEEK_SET:相对于文件开头 SEEK_CUR:相对于文件当前位置 SEEK_END:相对于文件末尾
3. 返回值：成功：0 失败：-1
4. 注：当打开文件的方式为a或a+时，fseek不起作用

|类型|相对位置|
|:-:|:-:|
|SEEK_SET|文件开头|
|SEEK_CUR|文件当前位置|
|SEEK_END|文件末|

#### long ftell(FILE *stream)

1. 功能：获取当前的文件位置
2. 参数：要检测的文件流
3. 返回值：成功：当前的文件位置，出错：-1

## 文件IO

### 概念

系统中（posix）定义的一组用于输入输出的函数接口

### 特点

1. 没有缓冲机制，每次调用都会引起系统调用
2. 围绕文件描述符进行操作，文件描述符是非负整数，依次分配
3. 文件IO默认打开三个文件描述符，0（标准输入），1（标准输出），2（标准错误）
4. 可以操作除目录文件外的任意类型文件。

### 文件IO函数接口

#### int open(const char * pathname, int flags)

1. 功能：打开除文件夹外的一切文件类型
2. 参数： pathname:文件路径 flags:打开方式
3. 返回值：文件描述符

|打开方式|功能|
|:-:|:-:|
|O_RDONLY|只读|
|O_WRONLY|只写|
|O_RDWR|可读可写|
|O_CREAT|创建|
|O_APPEND|追加|
|O_TRUNC|清空|

#### int open(const char * pathname, int flags， mode_t mode)

1. 功能：打开除文件夹外的一切文件类型
2. 参数： pathname:文件路径 flags:打开方式 mode:文件权限 0777
3. 返回值：文件描述符

#### int close(int fd)

1. 功能：关闭文件描述符
2. 参数：要关闭的文件描述符
3. 返回值：成功返回0 失败返回-1

#### ssize_t read(int fd, void * buf, size_t count)

1. 功能：读取文件描述符中的数据
2. fd:文件描述符 buf:缓存区 count:读取数据的长度
3. 返回值：返回值：成功：实际读到的个数 返回-1：表示出错,并设置errno号 返回0：表示读到文件结尾

#### ssize_t write(int fd, void * buf, size_t count)

1. 功能：写入文件描述符中的数据
2. fd:文件描述符 buf:缓存区 count:写入数据的长度
3. 返回值：返回值：成功：实际读到的个数 返回-1：表示出错,并设置errno号

#### int lseek(int fd, off_t offset, int whence)

1. 功能：设定文件的偏移位置
2. 参数：fd：文件描述符 offset偏移量 正数：向文件结尾位置移动 负数：向文件开始位置 whence  相对位置
3. 返回值：成功：文件的当前位置 失败：-1

|类型|相对位置|
|:-:|:-:|
|SEEK_SET|文件开头|
|SEEK_CUR|文件当前位置|
|SEEK_END|文件末|

## 练习

### 用文件IO实现cp功能

```c
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int  main(int argc, const char * argv[])
{
    int fd = open(argv[1], O_RDONLY);

    if(fd < 0)
    {
        perror("open err\n");

        return -1;
    }

    int fd1 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0777);

    if(fd1 < 0)
    {
        perror("open err\n");

        exit(1);
    }

    char buf[32] = {0};

    int len;

    while((len = read(fd, buf, sizeof(buf))) > 0)

    write(fd1, buf, len);

    close(fd);

    close(fd1);

    return 0;
}

```

### 实现“head -n 文件名”命令的功能 （显示文件前n行）

```C
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


static void Head(const char * opt, const char * filename)
{
    char * p = (char *)&opt[1];

    int rowNum = atoi(p);

    int len = 0;

    int fd = open(filename, O_RDONLY);

    if(fd < 0)
    {
        perror("open err");

        return;
    }

    char buf[32] = {0};

    while(((len = read(fd, buf, sizeof(buf))) > 0) && (rowNum > 0))
    {
        if(p = strchr(buf, '\n'))
        {
            p[1] = 0;

            p = p + 2;

            lseek(fd, -(strlen(p) + 1), SEEK_CUR);

            write(1, buf, strlen(buf));

            rowNum--;
        }
        else write(1, buf, len);
        

    }

    close(fd);


}

int main(int argc, char const *argv[])
{
    Head(argv[2], argv[1]);

    return 0;
}



```
