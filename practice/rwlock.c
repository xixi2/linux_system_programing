//
// Created by xixi2 on 2020/3/12.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/lock.h>
#include <unistd.h>

int number = 0;
pthread_rwlock_t rwlock;

void *read_func(void *arg) {
    while(1){
        pthread_rwlock_rdlock(&rwlock);
        printf("== read: %lu, %d\n", pthread_self(), number);
        pthread_rwlock_unlock(&rwlock);
        usleep(500);
    }
    return NULL;
}

void *write_func(void *arg) {
    while (1){
        pthread_rwlock_wrlock(&rwlock);
        ++number;
        printf("== write: %lu, %d\n", pthread_self(), number);
        pthread_rwlock_unlock(&rwlock);
        usleep(500);
    }
    return NULL;
}

int main() {
    pthread_t p[8];
    pthread_rwlock_init(&rwlock, NULL);
    for (int i = 0; i < 3; ++i) {
        pthread_create(&p[i], NULL, write_func, NULL);
    }

    for (int i = 3; i < 8; ++i) {
        pthread_create(&p[i], NULL, read_func, NULL);
    }
    for (int i = 0; i < 8; ++i) {
        pthread_join(p[i], NULL);
    }
    pthread_rwlock_destroy(&rwlock);
    return 0;
}