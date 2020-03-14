//
// Created by xixi2 on 2020/3/9.
// 8个线程，其中5个读全局变量，另外3个写全局变量

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <pthread.h>

int number = 0;
pthread_rwlock_t rwlock;

void *write_func(void *arg) {
    // 循环写
    while (1) {
        // 临界区应该越小越好
        pthread_rwlock_wrlock(&rwlock);
        number++;
        printf("== write: %lu, %d\n", pthread_self(), number);
        pthread_rwlock_unlock(&rwlock);

        usleep(50000);
    }
    return NULL;
}

void *read_func(void *arg) {
    while (1) {
        pthread_rwlock_rdlock(&rwlock);
        printf("== read: %lu, %d\n", pthread_self(), number);
        pthread_rwlock_unlock(&rwlock);
        usleep(50000);
    }
    return NULL;
}

int main() {
    pthread_t p[8];
    pthread_rwlock_init(&rwlock, NULL);     // 初始化读写锁

    // 创建3个子线程
    for (int i = 0; i < 3; ++i) {
        pthread_create(&p[i], NULL, write_func, NULL);
    }
    // 创建5个子线程
    for (int i = 3; i < 8; ++i) {
        pthread_create(&p[i], NULL, read_func, NULL);
    }

    for (int i = 0; i < 8; ++i) {
        pthread_join(p[i], NULL);
    }

    // 释放读写锁资源
    pthread_rwlock_destroy(&rwlock);
    return 0;
}