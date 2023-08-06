#include <stdio.h>
#include <stdlib.h>
#include "LQ.h"

static LQ * Init(void)
{
    LQ * PNew = (LQ *)malloc(sizeof(LQ));

    if(PNew == NULL)
    {
        printf("LQInit failed, PQmalloc err.\n");

        return NULL;
    }

    PNew->front = PNew->rear = (LL)malloc(sizeof(LLN));

    if(PNew->front == NULL)
    {
        printf("LQInit failed, PQmalloc err.\n");

        free(PNew);

        return NULL;
    }

    PNew->front->next = NULL;

    return PNew;

}

static int Push(LQ * PQ, int data)
{
    if(PQ == NULL)

    return -1;

    LL PNew = (LL)malloc(sizeof(LLN));

    if(PNew == NULL)
    {
        printf("LQPush failed, PNew malloc err.\n");

        return -1;
    }

    PNew->data = data;

    PNew->next = NULL;

    PQ->rear->next = PNew;

    PQ->rear = PNew;

    return 0;
}


static int Pop(LQ * PQ)
{
    if((PQ == NULL) || (!PQ->front->next))
        
    return -1;

    LL PNew = PQ->front;

    PQ->front = PQ->front->next;

    free(PNew);

    PNew = NULL;

    return PQ->front->data;

}


static void Print(LQ * PQ)
{
    if(PQ)
    {
        LL H = PQ->front;

        while(H->next)
        {
            H = H->next;

            printf("%d\t", H->data);
        }

        printf("\n");
    }

    
}

static int GetLenth(LQ * PQ)
{
    if(PQ == NULL)
    
    return -1;

    int len = 0;

    LL H = PQ->front;

    while(H->next != NULL)
    {
        len++;

        H = H->next;
    }

    H = NULL;

    return len;
}


static void Clear(LQ * PQ)
{

    if(PQ)
    {
        LL H = NULL;

        while(PQ->front->next)
        {
            H = PQ->front;

            PQ->front = PQ->front->next;

            free(H);
        }

        H = NULL;
    }

    
}

static void Close(LQ ** PQ)
{
    Clear(*PQ);

    free((*PQ)->front);

    (*PQ)->front = NULL;

    free(*PQ);

    *PQ = NULL;
}

void LQInit(void)
{
    LQOpt.init = Init;

    LQOpt.push = Push;

    LQOpt.pop = Pop;

    LQOpt.print = Print;

    LQOpt.getlen = GetLenth;

    LQOpt.clear = Clear;

    LQOpt.close = Close;
}


