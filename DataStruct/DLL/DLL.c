#include <stdio.h>
#include <stdlib.h>
#include "DLL.h"
#include "../list.h"

//=======================双向链表====================================


static DLL Init(DoubleLinkListData data)
{
    DLL PNew = (DLL)malloc(sizeof(DLLN));

    if(PNew == NULL)
    {
        printf("DLL PNew Init failed\n");

        return NULL;
    }

    PNew->data = data;

    PNew->next  = NULL;

    PNew->prior = NULL;

    return PNew;

}


static int InsertAfter(DLL PQ, DLL PNew)
{
    if((PQ == NULL) || (PNew == NULL)) return -1;

    if(PQ->next)
    {
        PQ->next->prior = PNew;

        PNew->next = PQ->next;

        PNew->next->prior = PQ;

        PQ->next = PNew;
    }
    else
    {
        PQ->next = PNew;

        PNew->prior = PQ;    
    }

    return 0;
}


static int InsertBefore(DLL PQ, DLL PNew)
{
    if((PQ == NULL) || (PNew == NULL))

    return -1;

    if(PQ->prior)
    {
        PQ->prior->next = PNew;

        PNew->prior = PQ->prior;

        PNew->next = PQ;

        PQ->prior  = PNew;
    }
    else
    {
        PQ->prior  = PNew;

        PNew->next = PQ;    
    }

    return 0;
}



static DLL DelNode(DLL PQ)
{
    if(PQ == NULL) return NULL;

    DLL Q = NULL;

    DLL H = PQ;

    if(!PQ->prior)
    {
        Q = PQ->next;

        H->next = NULL;

        Q->prior = NULL;
    }
    else if(!PQ->next)
    {
        Q = PQ->prior;

        H->prior = NULL;

        Q->next = NULL;
    }
    else
    {
        PQ->next->prior = PQ->prior;

        PQ->prior->next = PQ->next;

        Q = PQ->next;

        H->next = NULL;

        H->prior = NULL;
    }

    free(H);

    H = NULL;

    return Q;
}

static DLL GetHead(DLL PQ)
{
    if(!PQ) return NULL;

    while (PQ->prior) PQ = PQ->prior;

    return PQ;  
}


static int GetLenth(DLL PQ)
{
    if(PQ == NULL) return 0;

    int len = 1;

    DLL H = PQ;

    while (H->prior) H = H->prior;

    while (H->next)
    {
        len++;

        H = H->next;
    }

    return len;
}


static int Print(DLL PQ)
{
    if(!PQ) return -1;

    printf("list len = %d\n", GetLenth(PQ));

    DLL H = PQ;

    while(H->prior) H = H->prior;

    while (H)
    {
        printf("%d ", H->data);

        H = H->next;
    }

    return 0;
}

void DLLoptInit(void)
{
    DLLOpt.Init     = Init;
 
    DLLOpt.Print    = Print;

    DLLOpt.GetHead  = GetHead;

    DLLOpt.DelNode  = DelNode;

    DLLOpt.GetLenth = GetLenth;

    DLLOpt.InsertAfter  = InsertAfter;

    DLLOpt.InsertBefore = InsertBefore;
}

//=========================环形双向链表================================//

static DLL InitRing(DoubleLinkListData data)
{
    DLL PNew = (DLL)malloc(sizeof(DLLN));

    if(PNew == NULL)
    {
        printf("DLL InitRing failed\n");

        return NULL;
    }

    PNew->data = data;

    PNew->next  = PNew;

    PNew->prior = PNew;

    return PNew;
}


static int InsertRingAfter(DLL PQ, DLL PNew)
{
    if((PQ == NULL) || (PNew == NULL))

    return -1;

    PQ->next->prior = PNew;

    PNew->next = PQ->next;

    PNew->prior = PQ;

    PQ->next = PNew;
    
    return 0;
}


static int InsertRingBefore(DLL PQ, DLL PNew)
{
    if((PQ == NULL) || (PNew == NULL)) return -1;

    PQ->prior->next = PNew;

    PNew->prior = PQ->prior;

    PNew->next = PQ;

    PQ->prior = PNew;
    
    return 0;
}

static DLL DelRingNode(DLL PQ)
{
    if(PQ == NULL) return NULL;

    if(PQ == PQ->next) 
    {
        PQ->prior = PQ->next = NULL;

        free(PQ);

        return NULL;
    }

    DLL H = PQ->next;

    PQ->next->prior = PQ->prior;

    PQ->prior->next = PQ->next;

    PQ->next = NULL;

    PQ->prior = NULL;

    free(PQ);

    return H;
}


static int GetLenthRing(DLL PQ)
{
    if(PQ == NULL) return 0;

    int len = 1;

    DLL H = PQ;

    while (H->next != PQ)
    {
        len++;

        H = H->next;
    }

    H = NULL;

    return len;
}

static int PrintRing(DLL PQ)
{
    if (PQ == NULL) return -1;

    printf("ringlist len = %d\n", GetLenthRing(PQ));

    DLL H = PQ;

    printf("%d ", H->data);

    while (H->next != PQ)
    {
        H = H->next;

        printf("%d ", H->data);
    }

    printf("\n");

    H = NULL;

    return 0;
}

void DRLoptInit(void)
{
    DRLOpt.Init     = InitRing;

    DRLOpt.Print    = PrintRing;

    DRLOpt.DelNode  = DelRingNode;

    DRLOpt.GetLenth = GetLenthRing;

    DRLOpt.InsertAfter  = InsertRingAfter;

    DRLOpt.InsertBefore = InsertRingBefore; 
}


//================================================================

#if 1

#if 0
int main(int argc, const char * argv[])
{
    DLL PQ = Init(1);

    DLL PQ1 = Init(2);

    DLL PQ2 = Init(3);

    DLL PQ3 = Init(4);

    InsertAfter(PQ, PQ1);

    InsertAfter(PQ, PQ2);

    InsertBefore(PQ, PQ3);

    Print(PQ);

    return 0;
}

#else

int main(int argc, const char * argv[])
{
    DLL PQ = InitRing(1);

    DLL PQ1 = InitRing(2);

    DLL PQ2 = InitRing(3);

    DLL PQ3 = InitRing(4);

    InsertRingAfter(PQ, PQ1);

    InsertRingAfter(PQ, PQ2);

    InsertRingBefore(PQ, PQ3);

    PrintRing(PQ);

    DelRingNode(PQ2);

    printf("PQ2->data = %d\n", PQ2->next->data);

    PrintRing(PQ);

    return 0;
}

#endif

#endif