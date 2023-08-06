#ifndef __DLL_H_
#define __DLL_H_


typedef unsigned int DoubleLinkListData;

typedef struct DoubleLinkListNode
{

    DoubleLinkListData data;           //标志数据

    struct DoubleLinkListNode * prior; //上一个节点

    struct DoubleLinkListNode * next;  //下一个节点
    
}DLLN, * DLL;

struct DoubleLinkListOpt
{
    int (* Print)(DLL PQ);                 //打印双向链表长度及标志

    int (* GetLenth)(DLL PQ);              //打印双向链表长度

    DLL (* GetHead)(DLL PQ);               //返回值获取双向链表头节点

    DLL (* DelNode)(DLL PQ);               //删除节点 返回值获取删除节点的下一个节点

    DLL (* Init)(DoubleLinkListData data); //创建一个节点

    int (* InsertAfter)(DLL PQ, DLL PNew); //向PQ节点后方插入PNew节点

    int (* InsertBefore)(DLL PQ, DLL PNew);//向PQ节点前方插入PNew节点
 
};


struct DoubleRingListOpt
{
    int (* Print)(DLL PQ);                 //打印双向循环链表长度及标志

    DLL (* DelNode)(DLL PQ);               //删除节点 返回值获取删除节点的下一个节点, 全部删除返回空

    int (* GetLenth)(DLL PQ);              //打印双向链表长度

    DLL (* Init)(DoubleLinkListData data); //创建一个节点

    int (* InsertAfter)(DLL PQ, DLL PNew); //向PQ节点后方插入PNew节点

    int (* InsertBefore)(DLL PQ, DLL PNew);//向PQ节点前方插入PNew节点

};

//双向链表操作函数集合
struct DoubleLinkListOpt DLLOpt;

//双向循环链表操作函数集合
struct DoubleRingListOpt DRLOpt;

//初始化双向链表操作函数
void DLLoptInit(void);
//初始化双向循环链表函数
void DRLoptInit(void);

#endif