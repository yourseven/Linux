#include <stdio.h>
#include <stdlib.h>
#include "DLLN.h"

static DLLO * Init(void)
{
    DLLO * PNew = (DLLO *)malloc(sizeof(DLLO));

    if(!PNew)
    {
        printf("Init creat PNew failed\n");

        return NULL;
    }

    PNew->tail = PNew->head = (DLL)malloc(sizeof(DLLN));

    if(!PNew->tail)
    {
        printf("Init creat PNew->tail failed\n");

        free(PNew);

        return NULL;
    }

    PNew->head->prior = PNew->tail->next = NULL;

    PNew->len = 0;

    return PNew;

}

static int Insert(DLLO * PQ, int post, int data)
{
    if(!PQ) return -1;

    if((post < 0) || (post > PQ->len))
    {
        printf("Insert post err\n");

        return -1;
    }

    DLL PNew = (DLL)malloc(sizeof(DLLN));

    if(!PNew)
    {
        printf("Insert creat PNew failed\n");

        return -1;
    }

    PNew->data = data;

    PNew->next = NULL;

    PNew->prior = NULL;

    if(post == PQ->len)
    {
        PQ->tail->next = PNew;

        PNew->prior = PQ->tail;

        PQ->tail = PNew;
    }
    else
    {
        DLL H = NULL;

        if(post <= (PQ->len / 2))
        {
            H = PQ->head;

            for(int i = 0; i <= post; i++)

            H = H->next;
        }
        else
        {
            H = PQ->tail;

            for(int i = 0; i < PQ->len - post - 1; i++)
            
            H = H->prior;
        }

        H->prior->next = PNew;

        PNew->prior = H->prior;

        PNew->next = H;

        H->prior = PNew;

        H = NULL;

    }

    PQ->len++;


}


static void Print(DLLO * PQ)
{
    DLL H = PQ->head;

    while(H->next)
    {
        H = H->next;

        printf("%d\t", H->data);
    }

    printf("\n");
}


static int DeletPost(DLLO * PQ, int post)
{
    if((post < 0) || (post > PQ->len - 1)) return -1;

    DLL H = NULL;

    if(post == PQ->len - 1)
    {
        H = PQ->tail;

        PQ->tail = PQ->tail->prior;

        free(H);

        PQ->tail->next = NULL;

        H = NULL;
    }
    else
    {
        if(post <= (PQ->len / 2))
        {
            H = PQ->head;

            for(int i = 0; i <= post; i++)

            H = H->next;
        }
        else
        {
            H = PQ->tail;

            for(int i = 0; i < PQ->len - post - 1; i++)

            H = H->prior;
        }

        H->next->prior = H->prior;

        H->prior->next = H->next;

        H->prior = NULL;

        H->next = NULL;

        free(H);

        H = NULL;
    }

    PQ->len--;

    return 0;
}

static int FindPost(DLLO * PQ, int data)
{
    DLL H = PQ->head;

    int post = 0;

    while (H->next)
    {
        H = H->next;

        if(H->data == data)return post;

        post++;
    }
    
    return -1;

}

static int Modify(DLLO * PQ, int post, int data)
{
    if((post < 0) || (post > PQ->len - 1)) return -1;

    DLL H = NULL;

    if(post <= (PQ->len) / 2)
    {
        H = PQ->head;

        for(int i = 0; i <= post; i++) H = H->next;
            
    }
    else
    {
        H = PQ->tail;

        for(int i = 0; i < PQ->len - post - 1; i++) H = H->prior;
    }

    H->data = data;

    H = NULL;

    return 0;
}

static void DeleteData(DLLO * PQ, int data)
{
    DLL H = PQ->head;

    while (H->next)
    {
        H = H->next;

        if(H->data == data)
        {
            if(H->next)
            {
                DLL Del = H;

                H->prior->next = H->next;

                H->next->prior = H->prior;

                H = H->prior;

                free(Del);

                Del = NULL;
            }
            else
            {
                PQ->tail = PQ->tail->prior;

                PQ->tail->next = NULL;

                free(H);
            }
        }
        
    }

    H = NULL;


    
}

int main(int argc, const char * argv[])
{
    DLLO * PQ = Init();

    Insert(PQ, 0, 101);

    Insert(PQ, 0, 102);

    Insert(PQ, 1, 103);

    Insert(PQ, 2, 104);

    Insert(PQ, 4, 105);

    Insert(PQ, 5, 106);

    Insert(PQ, 4, 107);

    Print(PQ);

    DeletPost(PQ, 3);

    Print(PQ);

    Modify(PQ, 3, 108);

    Print(PQ);

    Insert(PQ, 3, 101);

    Insert(PQ, 5, 101);

    Insert(PQ, 7, 101);

    Print(PQ);

    DeleteData(PQ, 101);

    Print(PQ);

    //getchar();

    return 0;
}