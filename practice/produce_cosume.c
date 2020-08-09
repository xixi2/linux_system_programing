//
// Created by xixi2 on 2020/3/21.
//

#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#define BUFF_SIZE  3        // 缓冲区大小
//#define PRODUCE_THREAD_SIZE 5
#define PRODUCE_THREAD_SIZE 1

typedef struct node {
    int data;
    struct node *next;
} ListNode;

ListNode *head = NULL;

sem_t lock;
sem_t consume_sem;// 产品个数，消费者需要的资源
sem_t produce_sem;// 空缓冲区个数，生产者需要的资源


void *produce(void *ptr) {
    int idx = *(int *) ptr;
    while (1) {
        try{
            ListNode *pnew = (ListNode *) malloc(sizeof(ListNode));
            pnew->data = rand() % 1000;
        }catch(Exception &e){
            e.w
        }

        sem_wait(&produce_sem);//  限制了生产者并发的数目
        sem_wait(&lock); // 对临界区的访问要加锁
        pnew->next = head;
        head = pnew;
        printf("+++++ producer: %lu, %d\n", pthread_self(), pnew->data);
        sem_post(&lock);
        sem_post(&consume_sem);
        printf("producer tip customer, full: %d\n", consume_sem);

        sleep(5);
    }
    return NULL;
}

void *consume(void *ptr) {
    while (1) {
        sem_wait(&consume_sem);
        sem_wait(&lock);
        ListNode *pdel = head;
        if (pdel == NULL) {
            printf("empty linkedlist\n");
        } else {
            printf("head : %d\n", head->data);
        }
        head = head->next;
        printf("----- customer: %lu custom %d\n", pthread_self(), pdel->data);
        pthread_mutex_unlock(&lock);
        sem_post(&lock);
        sem_post(&produce_sem);
        free(pdel);
        printf("customer, empty: %d\n", produce_sem);
        sleep(5);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t con;
    pthread_t pros[PRODUCE_THREAD_SIZE];
    sem_init(&lock, 0, 1);
    sem_init(&consume_sem, 0, 0);
    sem_init(&produce_sem, 0, BUFF_SIZE);

    pthread_create(&con, NULL, consume, NULL);
    int thread_args[PRODUCE_THREAD_SIZE];
    for (int i = 0; i < PRODUCE_THREAD_SIZE; i++) {
        thread_args[i] = i + 1;
        pthread_create(&pros[i], NULL, produce, (thread_args + i));
    }

    pthread_join(con, 0);
    for (int i = 0; i < PRODUCE_THREAD_SIZE; i++)
        pthread_join(pros[i], 0);

    sem_destroy(&lock);
    sem_destroy(&consume_sem);
    sem_destroy(&produce_sem);

    return 0;
}