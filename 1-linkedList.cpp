//
//  main.cpp
//  linkedlist
//
//  Created by 罗嘉瑞 on 17/3/13.
//  Copyright © 2017年 罗嘉瑞. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#define STOP system("pause")
using namespace std;

struct Node {
    int data;
    Node* next;
};

typedef Node* List;
typedef Node* pos;

// @brief    Create a list contain n nodes.
//
// @param    n    Size of the %list
// @return   Created %list
List creatList(int n) {
    List head, p, q;
    int num;
    head = (struct Node*)malloc(sizeof(struct Node));
    p = head;
    
    while (n--) {
        scanf("%d", &num);
        q = (struct Node*)malloc(sizeof(struct Node));
        q->data = num;
        p->next = q;
        p = q;
    }
    p->next = NULL;
    
    return head;
}

// @brief    Remove the first node where data equals %num from a %list
//
// @param    head    A %list
// @param    num     A number
List removeNode(List head, int num) {
    List p, q = NULL;
    p = head;
    while (num!=p->data && p->next!=NULL) {
        q = p;
        p = p->next;
    }
    if (num == p->data) {
        if (p == head) {
            head = p->next;
        } else {
            q->next = p->next;
        }
        free(p);
    } else {
        printf("Number %d not found.\n", num);
    }
    return head;
}

// @brief    Insert a node valuess %num in %pos th position to a %list,
//              return orginal list if the pos not in [1, len(list)+1].
//
// @param    head    A %list
// @param    num     A number
// @param    pos     A pos number
List insertNode(List head, int num, int pos) {
    if (pos < 1) {
        printf("请输入正确的插入位置！\n");
        return head;
    }
    List p, q=NULL, tmp;
    p = head;
    int nowp = 0;
    tmp = (Node*)malloc(sizeof(Node));
    tmp->data = num;
    while (p->next!=NULL && nowp<pos) {
        q = p;
        p = p->next;
        nowp++;
    }
    if (p->next == NULL) {
        if (nowp < pos - 1) {
            printf("指定插入位置超过链表长！\n");
            return head;
        } else if (nowp == pos - 1) {//插入链表尾
            tmp->next = NULL;
            p->next = tmp;
        } else {
            tmp->next = p;
            q->next = tmp;
        }
    } else {
        tmp->next = p;
        q->next = tmp;
    }
    return head;
}

// @brief   Reverse a %list
//
// @param   head    A %list
List reverseList(List head) {
    List p = head->next; List pre = NULL;
    while (p != NULL) {
        Node* pNxt = p->next; // 保存下一个节点的值
        p->next = pre; // 把当前Node的下一个节点指向Pre
        pre = p; // 此时Pre向后移动指向此时的Node
        p = pNxt; // 而Node也向后移动，指向刚才保存的Next...Notice : 这里写成p = p->next 是错的
    }
    List ret = creatList(0); // 表头
    ret->next = pre;
    return ret;
}

// @brief    Reverse a %list in [m, n]
List reverseBetween(List head, int m, int n) {
    if (head == NULL || m > n)
        return NULL;
    Node* dummyNode = new Node(); // 便于操作
    dummyNode->next = head;
    Node* pPrev = head;
    for (int i=1; i<m; i++) // pPrev指向待翻转区间的前一个节点
        if (pPrev)
            pPrev = pPrev->next;
    if (pPrev != NULL) { // 链表长度>=m
        Node* pLast = pPrev->next; // pLast指向待翻转区间的第一个节点
        List p = pPrev->next; List pre = NULL;
        while (p != NULL) {
            Node* pNxt = p->next; // 保存下一个节点的值
            p->next = pre; // 把当前Node的下一个节点指向Pre
            pre = p; // 此时Pre向后移动指向此时的Node
            p = pNxt; // 而Node也向后移动，指向刚才保存的Next...Notice : 这里写成p = p->next 是错的
        }
        pLast->next = p; // 拼接
        pPrev->next = pre;
    }
    return dummyNode->next;
}

List getFirstNodeInCircle(List head) {
    if (head == NULL || head->next == NULL) {
        return NULL;
    }
    List pFast = head, pSlow = head;
    while (pFast != NULL && pFast->next != NULL) {
        pSlow = pSlow->next;
        pFast = pFast->next->next;
        if (pFast == pSlow) {
            break;
        }
    }
    if (pFast == NULL || pFast->next == NULL) { // 判定无环
        return NULL;
    }
    List pTail = pFast; // 假设此点为尾结点， 从此断开展成一个新的链表
    
    List pHead1 = head, pHead2 = pTail->next;
    int len1 = 1, len2 = 1;
    for (List i=pHead1; i!=pTail; i=i->next)
        len1++;
    for (List i=pHead2; i!=pTail; i=i->next)
        len2++;
    // 先对齐两个链表
    List pNode1 = pHead1, pNode2 = pHead2;
    for (int i=len2; i<len1; i++)
        pNode1 = pNode1->next;
    for (int i=len1; i<len2; i++)
        pNode2 = pNode2->next;
    // 遍历寻找交点
    for(; pNode2 != pNode1 && pNode1 != pTail; pNode1 = pNode1->next, pNode2 = pNode2->next)
        ;
    return pNode2;
}
/*
void DeleteNode(LisNode** pListHead, ListNode* pToDeleted) {
    if(!pListHead || !pToBeDeleted) {
        return;
    }
    
    if(pToBeDeleted->m_pNext != NULL) {
        ListNode* pNext = pToBeDeleted->m_pNext;
        pToBeDeleted->m_nValue = pNext->m_nValue;
        pToBeDeleted->m_pNext = pNext->m_pNext;
        
        delete pNext;
        pNext = NULL;
    } else if(*pListHead == pToBeDeleted) {
        delete pToBeDeleted;
        pToBeDeleted = NULL;
        *pListHead = NULL;
    } else {
        ListNode* pNode = *pListHead;
        while(pNode->m_pNext != pToBeDeleted) {
            pNode = pNode->m_pNext;
        }
        
        pNode->m_pNext = NULL;
        delete pToBeDeleted;
        pToBeDeleted = NULL;
    }
}*/

void Quicksort(List &head, List &end){
    List head1, head2, end1, end2;  // 记录分割后前后两个链表的头尾节点
    head1 = head2 = end1 = end2  = NULL;
    
    if (NULL == head) return;  // 如果当前节点为空，返回
    
    List p, pre1, pre2;  // 用于遍历链表将链表中的元素分成大于key和小于key两个部分
    p = pre1 = pre2 = NULL;
    
    int key = head->data;
    p = head->next; head->next = NULL;    // 取头结点的值作为分界线
    while (p != NULL) {
        if (p->data < key) { // 小于key的链表
            if (!head1) {
                head1 = pre1 = p;
            } else {
                pre1 = pre1->next = p;
            }
        } else { // 大于等于key的链表
            if (!head2) {
                head2 = pre2 = p;
            } else {
                pre2 = pre2->next = p;
            }
        }
        p = p->next;
    }
    
    if (pre1) pre1->next = NULL;
    if (pre2) pre2->next = NULL;
    
    end1 = pre1; end2 = pre2;   // 给新链表赋尾节点
    
    // 对左右两个链表进行递归快排
    Quicksort(head1, end1);
    Quicksort(head2, end2);
    
    // 将key节点和左右两个链表连起来
    if (end1 && head2) { // 左右链表都存在
        end1->next = head;
        head->next = head2;
        head = head1;
        end = end2;
    } else if (end1) { // 只有左链表
        end1->next = head;
        end = head;
        head = head1;
    } else if (head2) {  // 只有右链表
        head->next = head2;
        end = end2;
    }
}

int getRandom(List head) {
    List p = head->next;
    int ret = p->data;
    int n = 2;
    p = p->next;
    while (p) {
        if (rand() % n == 0)
            ret = p->data;
        ++n;
        p = p->next;
    }
    return ret;
}

// @brief    Print a %list one by one
//
// @param    L    A %list
void printList(List L) {
    List p;
    p = L->next;
    if(p == NULL)
        printf("NULL");
    while(p != NULL) {
        printf("%d ",p->data);
        p = p->next;
    }
    printf("\n");
}

int main() {
    int n;
    List L;
    
    scanf("%d",&n);
    L = creatList(n);
    // removeNode(L, 3);
    
    // insertNode(L, 3, 1);
    
    // L = reverseList(L);
    
    /*List tail;
    for (tail=L; tail->next; tail=tail->next)
        ;
    Quicksort(L, tail);*/
    
    /*srand(time(NULL));
    int cnt[4]={0};
    for (int i=0; i<10000; i++) {int tmp=getRandom(L); cnt[tmp]++;}
    printf("%d %d %d\n", cnt[1], cnt[2], cnt[3]);*/
    
    //printList(L);
    
    return 0;
}
