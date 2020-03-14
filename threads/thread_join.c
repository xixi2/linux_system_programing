//
// Created by xixi2 on 2020/3/8.
// thread_exit的作用
// pthread_exit携带返回值

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
            pthread_exit((void*)&number);
        }
    }
    return NULL;
}


int main() {
    // 创建一个子线程
    pthread_t pthd;
    int ret = pthread_create(&pthd, NULL, myfunc, NULL);
    if (ret != 0) {
        printf("error number: %d\n", ret);
        printf("%s", strerror(ret));
    }

    printf("parent thread id: %lu\n", pthread_self());

    // 阻塞等待子线程退出，并且回收其PCB
    void *ptr;
    pthread_join(pthd, &ptr);
    int *p = ptr;
    printf("number = %d\n", *p);

    int i = 0;
    while (i < 3) {
        printf("parent i = %d\n", i++);
    }
    return 0;
}