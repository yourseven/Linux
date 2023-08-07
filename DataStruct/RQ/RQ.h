#ifndef __RQ_H_
#define __RQ_H_


typedef struct RingQueue
{
    
    void * buffer;

    unsigned int size;

    unsigned int front;

    unsigned int rear;

}RQN, * RQ;





#endif