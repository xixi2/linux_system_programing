//
// Created by xixi2 on 2020/3/8.
// 创建5个线程，并打印出每个线程创建的顺序，结果不如人意，正确方法见thread_create3.c

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pthread.h>

int count = 0;
void * myfunc(void *arg){
    int num = *(int*)arg;
    printf("create the %d child thread %lu\n", num, pthread_self());
    return NULL;
}


int main(){
    pthread_t pthd[5];      // 创建一个线程ID数组
    for(int j=0;j<5;++j){
        pthread_create(&pthd[j], NULL, myfunc, (void*)&count);
        ++count;
    }
    sleep(5);
    return 0;
}
