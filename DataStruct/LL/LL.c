#include <stdio.h>
#include <stdlib.h>
#include "LL.h"


//=============================单向链表================================

static LL Init(LinkListData data)
{
    LL PNew = (LL)malloc(sizeof(LLN));

    if(!PNew)
    {
        printf("LL Init PNew failed\n");

        return NULL;
    }

    PNew->data = data;

    PNew->next = NULL;

    return PNew;
}


static int Insert(LL PQ, LL PNew)
{
    if((PQ == NULL) || (PNew == NULL)) return -1;

    if(PQ->next)
    {
        PNew->next = PQ->next;

        PQ->next = PNew;
    }
    else PQ->next = PNew;

    return 0;
}

static int DelNode(LL PQ)
{
    if((PQ == NULL) || (PQ->next == NULL)) return -1;

    LL H = PQ->next;

    if(H->next) 
    {
        PQ->next = H->next;

        H->next = NULL;
    }
    else PQ->next = NULL;

    free(H);

    H = NULL;

    return 0;
}

static int GetLenth(LL PQ)
{
    if(PQ == NULL) return -1;

    int len = 0;

    while (PQ->next)
    {
        len++;

        PQ = PQ->next;
    }

    return len;   
}

static void Print(LL PQ)
{
    printf("list len = %d\n", GetLenth);

    if(PQ == NULL) return;

    while (PQ->next)
    {
        printf("%d ", PQ->next->data);

        PQ = PQ->next;
    }

    printf("\n");
    
}

void LLNoptInit(void)
{
    LLNOpt.Init = Init;

    LLNOpt.Print = Print;

    LLNOpt.Insert = Insert;

    LLNOpt.DelNode = DelNode;

    LLNOpt.GetLenth = GetLenth;
}


//=============================单向循环链表=============================

static LL InitRing(LinkListData data)
{
    LL PNew = (LL)malloc(sizeof(LLN));

    if(!PNew)
    {
        printf("LR Init failed\n");

        return NULL;
    }

    PNew->data = data;

    PNew->next = PNew;

    return PNew;
}

static int InsertRing(LL PQ, LL PNew)
{
    if((PQ == NULL) || (PNew == NULL))return -1;

    PNew->next = PQ->next;

    PQ->next = PNew;

    return 0;
}

static int DelNodeRing(LL PQ)
{
    if((PQ == NULL)) return -1;

    if(PQ->next == PQ) 
    {
        PQ->next = NULL;

        free(PQ);
    }
    else
    {
        LL H = PQ->next;

        PQ->next = PQ->next->next;

        H->next = NULL;

        free(H);

        H = NULL;
    }

    return 0;
    
}


static int GetLenthRing(LL PQ)
{
    if(PQ == NULL) return 0;

    int len = 0;

    LL H = PQ->next;

    while (H != PQ)
    {
        len++;

        H = H->next;
    }

    H = NULL;

    return len;    
}


static void PrintRing(LL PQ)
{
    printf("LL list len = %d\n", GetLenthRing(PQ));

    if(PQ == NULL) return;

    while (PQ)
    {
        printf("%d ", PQ->data);

        PQ = PQ->next;
    }

    printf("\n");
    
}


