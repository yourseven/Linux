#ifndef _SHOW_H_
#define _SHOW_H_

#include "ms.h"

#define grades1_1 24
#define grades1_2 35
#define grades1_3 47
#define grades1_4 58

uint8_t show_mian[] = {
    "\n\n\n\n"\
    "                 ***************************************************         \n"\
    "                   *              学生成绩管理系统               *   \n"\
    "                 ***************************************************         \n"\
    "                   *             H = 显示帮助菜单                *     \n"\
    "                   *             T = 成绩录入                    *       \n"\
    "                   *             P = 按成绩由高到底排序         *\n"\
    "                   *             S = 按学号查询学生成绩          *  \n"\
    "                   *             Q = 退出系统                    *       \n\n\n\n"
    "                                                  当前以录入学生人数为  人\n\n\n"
    "        请输入命令="
};


const uint8_t show_null[] = {
    "\n\n\n\n\n\n"\
    "                      成绩表为空！请先使用T录入学生成绩\n"
};


const uint8_t cmd_G[] = "\n\n                   学号    语文   数学   英语   总成绩\n";

const uint8_t cmd_T[] = "\n\n\n            返回：H  录入成绩：w  列出成绩单：L  修改成绩：X\n\n            请输入命令=";

const uint8_t grahead1[] = "\n\n                   学号    语文     数学    英语     总成绩\n";

const uint8_t grahead2[] = "\n\n                      学号       语文        数学       英语\n";

uint8_t grahead3[] = "\n\n                   学号    语文     数学    英语    平均分   总成绩\n";

uint8_t grades1[] = "\n                                                                       \n";
uint8_t grades2[] = "\n                                                                       \n";

struct intput_grages_list
{
    int id;

    char data[100];

    struct intput_grages_list * node;
};


#endif