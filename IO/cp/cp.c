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
    if((SrcPath == NULL) || (DesPath == NULL) || (strcmp(SrcPath, DesPath) == 0)) return -1;
        
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
        printf("please input filepath\n");

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
