#ifndef __LL_H_
#define __LL_H_

typedef int LinkListData;

typedef struct LinkListNode
{

    LinkListData data;          //节点标志

    struct LinkListNode * next; //下一个节点
    
}LLN, * LL;


struct LinkListNodeOpt
{
    void (* Print)(LL PQ);          //打印单向链表长度及标志     

    int (* DelNode)(LL PQ);         //删除PQ的下一个节点

    int (* GetLenth)(LL PQ);        //获取PQ链表长度 -1无头 0只有头 >0 长度

    LL  (* Init)(LinkListData data);//初始化一个节点

    int (* Insert)(LL PQ, LL PNew); //向PQ节点后插入一个PNew节点

};

struct LinkListNodeOpt LLNOpt;      ////单向链表操作函数集合

//初始化单向链表操作函数
void LLNoptInit(void);


#endif