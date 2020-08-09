//
// Created by xixi2 on 2020/3/10.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <pthread.h>

// typedef给类型取别名
typedef struct node {
    int data;
    struct node *next;
} ListNode;

// 永远指向链表头部的指针
// 头部插入，头部删除
ListNode *head = NULL;

// 线程同步-互斥锁，阻塞线程-条件变量
pthread_mutex_t mutex;
pthread_cond_t cond;

const int psleep_time = 5;
const int csleep_time = 2;

void *producer(void *arg) {
    while (1) {
        // 创建一个链表的节点
        ListNode *pnew = (ListNode *) malloc(sizeof(ListNode));
        pnew->data = rand() % 1000;         // 节点的初始化

        // 开始操作共享数据了，需要加锁
        pthread_mutex_lock(&mutex);
        pnew->next = head;
        head = pnew;
        // 实际过程中，应该把打印这一句放到临界区外，这里是为了方便展示
        printf("++++++++++++++ produce: %lu, %d\n", pthread_self(), head->data);

        pthread_mutex_unlock(&mutex);

        // 通知阻塞的消费者线程解除阻塞
        pthread_cond_signal(&cond);

        sleep(psleep_time);
    }
    return NULL;
}

void *customer(void *arg) {
    while (1) {
        // 开始访问共享数据（无论是读还是写）之前加锁
        pthread_mutex_lock(&mutex);

        // 如果链表为空，那么消费者阻塞
        if (head == NULL) {
            printf("====== factory is empty and costumer %lu amd gonna sleep=====\n", pthread_self());
            // 判断链表是否为空，方案一：轮询
            // 轮询检查链表是否为空，效率较低
            // continue;

            // 判断链表是否为空，方法二：使用条件变量
            // 条件不满足时，阻塞线程，并对互斥锁解锁；条件满足时，解除阻塞，并对互斥锁加锁
            pthread_cond_wait(&cond, &mutex);
        }

        // 链表不为空，删除一个头节点，模拟消费过程
        ListNode *pdel = head;
        head = head->next;

        // 下面两行是为了展示效果才放入临界区内，实际生产过程中应该保证临界区越小越好
        printf("--------------- customer: %lu, %d\n", pthread_self(), pdel->data);
        free(pdel);
        pthread_mutex_unlock(&mutex);
        sleep(csleep_time);
    }
    return NULL;
}

int main() {
    pthread_t p1, p2;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_create(&p1, NULL, producer, NULL);
    pthread_create(&p2, NULL, customer, NULL);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    return 0;
}
