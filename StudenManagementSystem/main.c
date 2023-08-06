#include <stdio.h>
#include <strings.h>
#include <string.h>
#include "ms/ms.h"

struct class_node * mydrv;

extern char ms_buf[SIZE];

int main(void)
{

    drv_opt_init();

    mydrv = my_opt.init();

    while (mydrv->state)
    {

        my_opt.cmd(mydrv);

        memset(ms_buf, 0, SIZE);
   
    }

    printf("退出系统\n");

    return 0;
}