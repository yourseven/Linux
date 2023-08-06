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

### 函数接口

#### FILE * fopen(const char * path, const char * mode)

##### 功能：打开文件

##### 参数

1. path：打开的文件
2. mode：打开的方式

r：只读，当文件不存在时报错，文件流定位到文件开头
r+：可读可写，当文件不存在时报错，文件流定位到文件开头
w：只写，文件不存在创建，存在清空
w+：可读可写，文件不存在创建，存在清空
a：追加(在末尾写),文件不存在创建，存在追加，文件流定位到文件末尾
a+：读和追加，文件不存在创建，存在追加，读文件流定位到文件开头，写文件流定位到文件末尾

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

#### int  fputs(const char * s,  FILE * stream)

1. 功能：向文件中写字符串
2. 参数：s：要写的内容 stream：文件流
3. 返回值：成功：非负整数 失败：EOF

## 作业

### 通过fgets实现"wc -l 文件名"命令功能（计算文件行数）

```c
#include <stdio.h>

int main(int argc, const char * argv[])
{
    if(argc != 2)
    {
        printf("please input filename\n");

        return 0;
    }

    FILE * fp = fopen(argv[1], "r");

    if(fp == NULL)
    {
        printf("file fopen failed\n");

        return -1;
    }

    char buf[1000];

    int len = 0;

    while(fgets(buf, sizeof(buf) - 1, fp)) len++;

    fclose(fp);

    printf("%d %s\n", len, argv[1]);

    return 0;
}


```

### 用标准IO实现cp功能

```C
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

static void Printerr(const char *  str1, char * str2)
{
    if((str1 == NULL) || (str2 == NULL)) return;

    printf(str1, str2);

    exit(1);
}

//从地址中获取文件名或目录名
static char * GetFileNameForPath(char * DesPath)
{
    if(DesPath == NULL) return NULL;

    if(DesPath[strlen(DesPath) - 1] == '/') DesPath[strlen(DesPath) - 1] = 0;

    char * p = strrchr(DesPath, '/');

    if(!p) p = DesPath;

    while ((*p == '.') || (*p == '/')) p++;

    return p;
}

//将文件名或目录名添加到目标地址中
static char * AddFilePath(char * SrcPath, char * DesPath)
{

    if((SrcPath == NULL) || (DesPath == NULL)) return NULL;

    char * name = GetFileNameForPath(SrcPath);

    char * str = (char *)malloc(strlen(DesPath) + strlen(name) + 2);

    if(str == NULL) Printerr("AddFilePath malloc failed, SrcPath = %s\n", SrcPath);

    memset(str, 0, strlen(DesPath) + strlen(name) + 2);

    strcpy(str, DesPath);

    if(str[strlen(str) - 1] != '/') str[strlen(str)] = '/';

    strcat(str, name);
  
    return str;
}

//CP功能
static void MyCP(char * SrcPath, char * DesPath)
{
    if((SrcPath == NULL) || (DesPath == NULL)) return;

    DIR * dir = opendir(SrcPath);

    if(dir) Printerr("cp: 略过目录'%s'\n", SrcPath);

    else closedir(dir);

    FILE * fp = fopen(SrcPath, "r");

    if(fp == NULL) Printerr("cp: 无法获取'%s' 的文件状态(stat): 没有那个文件或目录\n", SrcPath);

    char * str = AddFilePath(SrcPath, DesPath);
  
    FILE * fp1 = fopen(str, "w");

    if(fp1 == NULL) Printerr("cp: 无法获取'%s' 的文件状态(stat): 没有那个文件或目录\n", str);

    char buf[30] = {0};

    while(fgets(buf, sizeof(buf) - 1, fp)) fputs(buf, fp1);

    fclose(fp);

    fclose(fp1);

    free(str);

}

//创建文件夹
static void CreatFolder(char * DesPath)
{
    if(DesPath == NULL) printf("Path does not exist\n");
    
    else if(access(DesPath, 0) == -1) mkdir(DesPath, 0777);
}

//cp -r 功能
static int MyCP_R(char * SrcPath, char * DesPath)
{
    if((SrcPath == NULL) || (DesPath == NULL) || strcmp(SrcPath, DesPath) == 0) return -1;
        
    DIR * dir  = opendir(SrcPath);

    if(dir == NULL) Printerr("cp: 无法获取'%s' 的文件状态(stat): 没有那个文件或目录\n", SrcPath);

    char * str = AddFilePath(SrcPath, DesPath);

    CreatFolder(str);

    struct dirent * emtry;

    char strSrc[256], strDes[256];

    while((emtry = readdir(dir)) != NULL)
    {
        if(strncmp(emtry->d_name, ".", 1) == 0)continue;

        memset(strSrc, 0, sizeof(strSrc));

        memset(strDes, 0, sizeof(strDes));

        strcpy(strSrc, SrcPath);

        strcpy(strDes, str);

        strSrc[strlen(strSrc)] = '/';   

        strcat(strSrc, emtry->d_name); 

        if(emtry->d_type == 4) 
        {
            if(MyCP_R(strSrc, strDes))

            printf("cp: 无法将目录'%s' 复制到自己'%s'\n", SrcPath, DesPath);
        }
   
        else MyCP(strSrc, strDes);  
    }

    closedir(dir);

    free(str);

    return 0;
}

static void Choose(char * Opt, char * SrcPath, char * DesPath)
{
    if((Opt[0] != '-') || (strlen(Opt) != 2))
    {
        printf("Try 'cp --help' for more information.\n");

        return;
    }
    switch (Opt[1])
    {
    case 'r':
        MyCP_R(SrcPath, DesPath);
        break;
    case 'd':
        //MyCP_D(SrcPath, DesPath);
        break;
    case 'i':
        //MyCP_I(SrcPath, DesPath);
        break;
    case 'a':
        //MyCP_A(SrcPath, DesPath);
        break;
    default:
        printf("Try 'cp --help' for more information.\n");
        break;
    }
}


int main(int argc, const char * argv[])
{
    if((argc != 3) && (argc != 4))
    {
        printf("please input file or folder path\n");

        return 0;
    }

    if(argc == 3) MyCP((char *)argv[1], (char *)argv[2]);
    
    else if(argc == 4)
    {
        if(strcmp(argv[2], argv[3]) == 0)

        printf("cp: 无法将目录'%s' 复制到自己'%s'\n", argv[2], argv[3]);

        else Choose((char *)argv[1], (char *)argv[2], (char *)argv[3]);
    }

    return 0;
}



```
