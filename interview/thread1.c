//
// Created by xixi2 on 2020/3/10.
// 两个线程，同时对一个全局变化执行++操作（前置++）


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

int number = 0;

void *count_number(void *arg) {
    while (1) {
        int tmp = number;
        number = tmp + 1;
        printf("thread %lu, add number to: %d\n", pthread_self(), number);
//        sleep(rand() % 15);
//        sleep(rand()%6);
        usleep(5);
    }
    return NULL;
}

void *count_number1(void *arg) {
    while (1) {
        ++number;
        printf("thread %lu, add number to: %d\n", pthread_self(), number);
//        sleep(rand() % 3);
        usleep(500);
    }
    return NULL;
}

int main() {
    pthread_t p1, p2;
    pthread_create(&p1, NULL, count_number, NULL);
    pthread_create(&p2, NULL, count_number, NULL);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    return 0;
}