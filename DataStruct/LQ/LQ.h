#ifndef __LQ_H_
#define __LQ_H_

#include "../LL/LL.h"

typedef struct LinkQueue
{
    LL front;

    LL rear;
}LQ;


struct LinkQueueOpt
{
    LQ * (* init)(void);

    int (*push)(LQ * PQ, int data);

    int (*pop)(LQ * PQ);

    void (*print)(LQ * PQ);

    int (*getlen)(LQ * PQ);

    void (*clear)(LQ * PQ);

    void (*close)(LQ ** PQ);

};


struct  LinkQueueOpt LQOpt;

void LQInit(void);

#endif