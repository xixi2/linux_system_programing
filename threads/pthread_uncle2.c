//
// Created by xixi2 on 2020/3/9.
// 两个线程对同一个全局变量进行++操作，使用互斥锁保证线程同步


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pthread.h>

#define MAX 10000
int number = 0;

// 全局互斥锁，两个线程都能访问
pthread_mutex_t mutex;

void *funca_num(void *arg) {
    for (int i = 0; i < MAX; ++i) {
        // 在访问共享资源之前加锁
        // 如果mutex被锁上了，那么当前线程会被阻塞在加锁这一操作上
        pthread_mutex_lock(&mutex);
        int cur = number;
        cur++;
        number = cur;
        pthread_mutex_unlock(&mutex);

        printf("Thread A, id=%lu, number=%d\n", pthread_self(), number);
        usleep(10);
    }
    return NULL;
}

void *funcb_num(void *arg) {
    for (int i = 0; i < MAX; ++i) {
        pthread_mutex_lock(&mutex);
        int cur = number;
        cur++;
        number = cur;
        pthread_mutex_unlock(&mutex);
        printf("Thread B, id=%lu, number=%d\n", pthread_self(), number);
        usleep(10);
    }
    return NULL;
}

int main() {
    pthread_t p1, p2;

    // 对互斥锁初始化
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&p1, NULL, funca_num, NULL);
    pthread_create(&p2, NULL, funcb_num, NULL);

    pthread_join(p1, NULL); // 阻塞等待线程退出，获取线程退出状态
    pthread_join(p2, NULL); // 阻塞等待线程退出，获取线程退出状态

    // 释放互斥锁资源
    pthread_mutex_destroy(&mutex);
    return 0;
}