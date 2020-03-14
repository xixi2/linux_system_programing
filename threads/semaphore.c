//
// Created by xixi2 on 2020/3/10.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>


typedef struct node {
    int data;
    struct node *next;
} ListNode;

ListNode *head = NULL;
pthread_mutex_t mutex;
sem_t empty = 4;            // 空缓冲区个数，生产者需要的资源
sem_t full = 0;             // 产品个数，消费者需要的资源
//sem_t empty;
//sem_t full;

void *producer(void *arg) {
    while (1) {
        sem_wait(&empty);
        ListNode *pnew = (ListNode *) malloc(sizeof(ListNode));
        pnew->data = rand() % 1000;
        pthread_mutex_lock(&mutex);
        pnew->next = head;
        head = pnew;
        printf("+++++ producer: %lu, %d\n", pthread_self(), pnew->data);
        usleep(5);
        pthread_mutex_unlock(&mutex);
        printf("add full: %d\n", full);
        sem_post(&full);
        sleep(rand() % 15);
    }
    return NULL;
}

void *customer(void *arg) {
    while (1) {
//        printf("customer, full: %d\n", full);

        sem_wait(&full);                // 如果full==0,线程阻塞，--full
        pthread_mutex_lock(&mutex);
        ListNode *pdel = head;
        if (pdel == NULL) {
            printf("empty linkedlist\n");
        } else {
            printf("head : %d\n", head->data);
        }
        head = head->next;
        printf("----- customer: %lu custom %d\n", pthread_self(), pdel->data);
        pthread_mutex_unlock(&mutex);
        free(pdel);
        sem_post(&empty);
        sleep(rand() % 10);
    }
    return NULL;
}

int main() {
    pthread_t p1, p2;
//    sem_init(&empty, 0, 4);
//    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);
    printf("empty: %d,  full: %d\n", empty, full);

    pthread_create(&p1, NULL, producer, NULL);
    pthread_create(&p2, NULL, customer, NULL);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    return 0;
}