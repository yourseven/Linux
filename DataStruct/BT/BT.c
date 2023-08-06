#include <stdio.h>
#include <stdlib.h>
#include "BT.h"

static BT Init(int n, int i)
{
    BT root = (BT)malloc(sizeof(BTN));

    if(!root)
    {
        printf("Init malloc root fialed\n");

        return NULL;
    }

    root->data = i;

    if(2 * i + 1 <= n)
    {
        root->RChild = Init(n, 2 * i + 1);

        root->LChild = Init(n, 2 * i);
    }
    else if(2 * i <= n)
    {
        root->RChild = NULL;

        root->LChild = Init(n, 2 * i);
    }
    else
    {
        root->RChild = NULL;

        root->LChild = NULL;
    }

    return root;
}

//前序遍历
static void PreOrder(BT root)
{
    if(!root) return;

    printf("%d ", root->data);

    if(root->LChild) PreOrder(root->LChild);

    if(root->RChild) PreOrder(root->RChild);
}

//中序遍历
static void InOrder(BT root)
{
    if(!root) return;

    if(root->LChild) InOrder(root->LChild);

    printf("%d ", root->data);

    if(root->RChild) InOrder(root->RChild);
}

//后序遍历
static void PostOrder(BT root)
{
    if(!root) return;

    if(root->LChild) PostOrder(root->LChild);

    if(root->RChild) PostOrder(root->RChild);

    printf("%d ", root->data);
}

int main(int argc, const char * argv[])
{
    

    return 0;
}

