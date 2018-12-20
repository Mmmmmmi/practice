#ifndef __HEAD_H__
#define __HEAD_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//数据类型
struct memeryNode {
    size_t _begin;
    size_t _end;
    size_t _size;
};

typedef struct memeryNode DataType;

//节点结构体
struct Node {
    struct memeryNode _data;
    struct Node* _next;
    struct Node* _prev;
};

//链表结构体
struct LinkList {
    struct Node* _head;
    struct Node* _tail;
};

//内存链表
struct memLinkList {
    struct LinkList _emptylist;
    struct LinkList _usedlist;
};

//创建节点
//每个节点里面的数据域应该是起始地址和大小
//
// struct Node {
//    struct memeryNode _data;
//    struct Node* _next;
//    struct Node* _prev;
//};
struct Node* creatNode(size_t begin, size_t size)
{
    struct Node *temp = (struct Node*) malloc (sizeof(struct Node));
    //确保malloc 成功
    assert(temp != NULL);
    temp->_data._begin = begin;
    temp->_data._size = size;
    temp->_data._end = begin + size;
    temp->_next = NULL;
    temp->_prev = NULL;
    return temp;
}

//输出链表
void printList(struct memLinkList *pmemlist)
{
    assert(pmemlist != NULL);
    struct Node *cur = NULL;
    //输出空闲链表
    cur = pmemlist->_emptylist._head;
    printf("空闲内存链表为：\n");
    while (cur != NULL) {
        printf("begin:%lu    ", cur->_data._begin);
        cur = cur->_next;
    }
    printf("\n");
    cur = pmemlist->_emptylist._head;
    while (cur != NULL) {
        printf("size :%lu", cur->_data._size);
        cur = cur->_next;
        if (cur != NULL) {
            printf("----->");
        }
    }
    printf("\n");
    cur = pmemlist->_emptylist._head;
    while (cur != NULL) {
        printf("end  :%lu    ", cur->_data._end);
        cur = cur->_next;
    }
    printf("\n");
    //输出已分配内存链表
    cur = pmemlist->_usedlist._head;
    printf("已分配内存链表为：\n");
    while (cur != NULL) {
        printf("begin:%lu", cur->_data._begin);
        cur = cur->_next;
    }
    printf("\n");
    cur = pmemlist->_usedlist._head;
    while (cur != NULL) {
        printf("size :%lu\n", cur->_data._size);
        cur = cur->_next;
        if (cur != NULL) {
            printf("----->");
        }
    }
    printf("\n");
    cur = pmemlist->_usedlist._head;
    while (cur != NULL) {
        printf("end  :%lu\n", cur->_data._end);
        cur = cur->_next;
    }
    printf("\n");
}

//初始化 
//需要初始化　内存的开始地址　和 大小
void memListInit(struct memLinkList *pmemlist, size_t begin, size_t size)
{
    assert(pmemlist != NULL);
    pmemlist->_emptylist._head = NULL;
    pmemlist->_emptylist._tail = NULL;
    pmemlist->_usedlist._head = NULL;
    pmemlist->_usedlist._tail = NULL;
    //先把第一个空的挂在空闲内存链表的第一个
    struct Node *ret = creatNode(begin, size);
    pmemlist->_emptylist._head = ret;
    pmemlist->_emptylist._tail = ret;
}

void Swap(struct Node *pnode1, struct Node *pnode2) 
{
    assert(pnode1 != NULL);
    assert(pnode2 != NULL);
    struct memeryNode temp;
    temp = pnode1->_data;
    pnode1->_data = pnode2->_data;
    pnode2->_data = temp;
}

//地址升序排序
void sortAscAdr(struct memLinkList *pmemlist)
{
    assert(pmemlist != NULL); 
    struct Node *cur = NULL;
    cur = pmemlist->_emptylist._head;
    while(cur->_next != NULL) {
        if (cur->_data._begin > cur->_next->_data._begin) {
            Swap(cur, cur->_next);
        }
       cur = cur->_next; 
    }
}

//内存块大小升序
void sortAscSize(struct memLinkList *pmemlist)
{
    assert(pmemlist != NULL);
    struct Node *cur = NULL;
    cur = pmemlist->_emptylist._head;
    while(cur->_next != NULL) {
        if (cur->_data._size > cur->_next->_data._size) {
            Swap(cur, cur->_next);
        }
       cur = cur->_next; 
    }
}


//内存块大小降序
void sortDescSize(struct memLinkList *pmemlist)
{
    assert(pmemlist != NULL);
    struct Node *cur = NULL;
    cur = pmemlist->_emptylist._head;
    while(cur->_next != NULL) {
        if (cur->_data._size < cur->_next->_data._size) {
            Swap(cur, cur->_next);
        }
       cur = cur->_next; 
    }
}

//回收占用的内存块
//传进来一个  memeryNode  包含起始地址　大小　和结束地址
void emptyMemeryPushBack(struct memLinkList *pmemlist, struct memeryNode *pmemnode)
{
    assert(pmemlist != NULL);
    struct Node *retnode = creatNode(pmemnode->_begin, pmemnode->_size);
    pmemlist->_emptylist._tail->_next = retnode;
    pmemlist->_emptylist._tail = retnode;
}


#endif
