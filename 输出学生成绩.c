#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define QElemType int

typedef enum {
    ERROR,
    OK,
    OVERFLOW,
    TRUE = 1,
    FALSE = 0
}Status;

/* c3-2.h 单链队列－－队列的链式存储结构 */
typedef struct QNode
{
    QElemType data;
    struct QNode *next;
}QNode,*QueuePtr;

typedef struct
{
    QueuePtr front,rear; /* 队头、队尾指针 */
}LinkQueue;


/*API*/
Status InitQueue(LinkQueue *Q);
Status QueueEmpty(LinkQueue Q);
Status EnQueue(LinkQueue *Q,QElemType e);
Status DeQueue(LinkQueue *Q,QElemType *e);

/*主函数*/
int main()
{
    LinkQueue queue_1,queue_2,queue_3;
    InitQueue(&queue_1);
    InitQueue(&queue_2);
    InitQueue(&queue_3);
    int length,data;
    scanf("%d",&length);
    while(length)
    {
        scanf("%d",&data);
        getchar();
        length--;
        if(data < 60)
            EnQueue(&queue_1,data);
        else if(data <100)
            EnQueue(&queue_2,data);
        else
            EnQueue(&queue_3,data);
    }

    printf("60>x:");
    while(!QueueEmpty(queue_1))
    {
        DeQueue(&queue_1,&data);
        printf("%d ",data);
    }
    printf("\n");

    printf("60<=x<100:");
    while(!QueueEmpty(queue_2))
    {
        DeQueue(&queue_2,&data);
        printf("%d ",data);
    }
    printf("\n");

    printf("x>=100:");
    while(!QueueEmpty(queue_3))
    {
        DeQueue(&queue_3,&data);
        printf("%d ",data);
    }
    printf("\n");

    return 0;
}

/*函数实现*/
Status InitQueue(LinkQueue *Q)
{ /* 构造一个空队列Q */
    (*Q).front=(*Q).rear=(QueuePtr)malloc(sizeof(QNode));
    if(!(*Q).front)
        exit(OVERFLOW);
    (*Q).front->next=NULL;
    return OK;
}

Status QueueEmpty(LinkQueue Q)
{ /* 若Q为空队列,则返回TRUE,否则返回FALSE */
    if(Q.front==Q.rear)
        return TRUE;
    else
        return FALSE;
}

Status EnQueue(LinkQueue *Q,QElemType e)
{ /* 插入元素e为Q的新的队尾元素 */
    QueuePtr p=(QueuePtr)malloc(sizeof(QNode));
    if(!p) /* 存储分配失败 */
        exit(OVERFLOW);
    p->data=e;
    p->next=NULL;
    (*Q).rear->next=p;
    (*Q).rear=p;
    return OK;
}

Status DeQueue(LinkQueue *Q,QElemType *e)
{ /* 若队列不空,删除Q的队头元素,用e返回其值,并返回OK,否则返回ERROR */
    QueuePtr p;
    if((*Q).front==(*Q).rear)
        return ERROR;
    p=(*Q).front->next;
    *e=p->data;
    (*Q).front->next=p->next;
    if((*Q).rear==p)
        (*Q).rear=(*Q).front;
    free(p);
    return OK;
}