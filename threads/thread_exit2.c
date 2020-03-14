//
// Created by xixi2 on 2020/3/8.
// pthread_exit的作用


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void *myfunc(void* arg){
    // 打印子线程的ID
    printf("child thread: %lu\n", pthread_self());
    for (int i = 0; i < 5; ++i) {
        if(i == 2){
            exit(-1);
        }
        printf("child i = %d\n", i);
    }
    return NULL;
}

int main(){
    pthread_t pthd;
    int ret = pthread_create(&pthd, NULL, myfunc, NULL);
    if(ret != 0){
        printf("error number: %d\n", ret);
        // 打印错误信息
        printf("%s\n", strerror(ret));
    }
    printf("parent thread id: %lu\n", pthread_self());

    for (int i = 0; i < 5; ++i) {
        printf("parent i = %d\n", i);
    }

    // 退出主线程
    pthread_exit(NULL);
    return 0;
}