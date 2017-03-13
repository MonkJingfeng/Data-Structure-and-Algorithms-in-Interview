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
    printList(L);
    //removeNode(L, 3);
    insertNode(L, 3, 5);
    printList(L);
    
    return 0;
}
