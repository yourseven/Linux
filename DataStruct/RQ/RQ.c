#include <stdio.h>
#include <stdlib.h>
#include "RQ.h"

static RQ Init(void * buffer, unsigned int size)
{
    RQ PNew = (RQ)malloc(sizeof(RQN));

    if(!PNew)
    {
        printf("RQ Init malloc failer\n");

        return NULL;
    }

    PNew->buffer = buffer;

    PNew->size   = size;

    PNew->front  = 0;

    PNew->rear   = 0;

    return PNew;
}

static unsigned int GetReadLenth(RQ PQ)
{
    return (PQ->rear + PQ->size - PQ->front) % PQ->size;
}

static unsigned int GetWriteLenth(RQ PQ)
{
    return (PQ->front + PQ->size - PQ->rear) % PQ->size;
}


static int Read(RQ PQ, char * buf)
{
    if((PQ == NULL) || (buf == NULL)) return -1;

    int len = GetReadLenth(PQ);


}



