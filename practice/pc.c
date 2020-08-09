//
// Created by xixi2 on 2020/3/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>


#define BUF_SIZE 10
#define PRODUCE_THREAD_SIZE 2
#define COSTOMER_THREAD_SIZE 3

typedef struct node {
    int data;
    struct node *next;
} ListNode;

typedef struct list {
    ListNode *head;
    int size;
} LinkedList;

LinkedList *factory;         // 工厂
pthread_mutex_t mutex;      // 互斥访问缓冲区
sem_t consume_sem;          // 产品个数个数，消费者需要的资源
sem_t produce_sem;          // 空缓冲区个数，生产者需要的资源

const int produce_sleep_time = 10;
const int customer_sleep_time = 1;

void *producer(void *arg) {
    while (1) {
        // 产生产品
        ListNode *pnew = (ListNode *) malloc(sizeof(ListNode));
        pnew->next = NULL;
        pnew->data = rand() % 1000;

        // 把产品放入缓冲区
        sem_wait(&produce_sem);
        pthread_mutex_lock(&mutex);
        printf("**************producer factory size: %d**************\n", factory->size);

        pnew->next = factory->head;
        factory->head = pnew;
        factory->size += 1;

        printf("++++++++++++++ produce: %lu, %d\n", pthread_self(), factory->head->data);
        pthread_mutex_unlock(&mutex);
        sem_post(&consume_sem);

        sleep(produce_sleep_time);
    }
    return NULL;
}

void *costomer(void *arg) {
    while (1) {
        sem_wait(&consume_sem);
        pthread_mutex_lock(&mutex);
        // 缓冲区为空，无产品可以消费
        printf("**************costumer factory size: %d**************\n", factory->size);

        // 消费产品
        ListNode *pdel = factory->head;
        factory->head = pdel->next;
        factory->size -= 1;

        printf("--------------- customer: %lu, consume %d\n", pthread_self(), pdel->data);
        pthread_mutex_unlock(&mutex);
        sem_post(&produce_sem);

        free(pdel);
        sleep(customer_sleep_time);
        printf("\n");
    }
    return NULL;
}


int main() {
    factory = (LinkedList *) malloc(sizeof(LinkedList));
    factory->size = 0;
    factory->head = NULL;

    pthread_t p1[PRODUCE_THREAD_SIZE];
    pthread_t p2[COSTOMER_THREAD_SIZE];
    pthread_mutex_init(&mutex, NULL);

    sem_init(&produce_sem, 0, BUF_SIZE);
    sem_init(&consume_sem, 0, 0);
    for (int i = 0; i < PRODUCE_THREAD_SIZE; ++i) {
        pthread_create(&p1[i], NULL, producer, NULL);
    }
    for (int i = 0; i < COSTOMER_THREAD_SIZE; ++i) {
        pthread_create(&p2[i], NULL, costomer, NULL);
    }
    for (int i = 0; i < PRODUCE_THREAD_SIZE; ++i) {
        pthread_join(p1[i], NULL);
    }
    for (int i = 0; i < COSTOMER_THREAD_SIZE; ++i) {
        pthread_join(p2[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    sem_destroy(&produce_sem);
    sem_destroy(&consume_sem);
    return 0;
}
