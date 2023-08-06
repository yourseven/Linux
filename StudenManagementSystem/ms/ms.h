#ifndef _MS_H_
#define _MS_H_

//#include <stdio.h>

#define TIAOSHI 0

#define SIZE 30

typedef unsigned char uint8_t;
typedef unsigned int  uint32_t;

struct grades_node
{
    int id;          //学号

    float Language;  //语文

    float Math;      //数学

    float English;   //英语

    float Grage;     //总成绩

    float Average;   //平均分

    struct grades_node * node; //下一个节点

};

struct class_node
{
    int num;                    //学生数量

    int state;

    uint8_t * buf;             

    struct grades_node * node; //学号链表

};


struct class_opt
{
    struct class_node * (* init)(void);

    void (* cmd)(struct class_node * class);
};

struct class_opt my_opt;

void drv_opt_init(void);

#endif