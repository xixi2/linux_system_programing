//
// Created by xixi2 on 2020/3/9.
// 两个线程对同一个全局变量进行++操作


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pthread.h>

#define MAX 10000
int number = 0;

void *funca_num(void *arg) {
    for(int i=0;i<MAX;++i){
        int cur = number;
        cur++;
        number = cur;
        printf("Thread A, id=%lu, number=%d\n", pthread_self(), number);
        usleep(10);
    }
    return NULL;
}

void *funcb_num(void *arg) {
    for(int i=0;i<MAX;++i){
        int cur = number;
        cur++;
        number = cur;
        printf("Thread B, id=%lu, number=%d\n", pthread_self(), number);
        usleep(10);
    }
    return NULL;
}

int main() {
    pthread_t p1, p2;
    pthread_create(&p1, NULL, funca_num, NULL);
    pthread_create(&p2, NULL, funcb_num, NULL);

    pthread_join(p1, NULL); // 阻塞等待线程退出，获取线程退出状态
    pthread_join(p2, NULL); // 阻塞等待线程退出，获取线程退出状态
    return 0;
}