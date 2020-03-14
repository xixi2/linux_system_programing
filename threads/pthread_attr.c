//
// Created by xixi2 on 2020/3/8.
// 设置线程分离

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pthread.h>

int number = 100;

void *myfunc(void *arg) {
    printf("child thread: %lu\n", pthread_self());
    for (int i = 0; i < 5; i++) {
        printf("child i = %d\n", i);
        if (i == 2) {
            pthread_exit((void *) &number);
        }
    }
    return NULL;
}


int main() {
    // 创建一个子线程
    pthread_t pthd;
    pthread_attr_t attr;
    pthread_attr_init(&attr);       // 初始化线程属性

    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    int ret = pthread_create(&pthd, &attr, myfunc, NULL);
    if (ret != 0) {
        printf("error number: %d\n", ret);
        printf("%s", strerror(ret));
    }

    printf("parent thread id: %lu\n", pthread_self());
    for (int i = 0; i < 5; ++i) {
        printf("parent i = %d\n", i);
    }
    sleep(2);
    pthread_attr_destroy(&attr);
    return 0;
}