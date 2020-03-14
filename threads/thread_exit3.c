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

void *myfunc(void *arg) {
    printf("child thread: %lu\n", pthread_self());
    for(int i=0;i<5;i++){
        printf("child i = %d\n", i);
        if(i == 2){
            // 如果使用exit子线程退出时，主线程也被强制退出了
            //exit(2);

            //使用pthread_exit让子线程退出退出，不影响主线程
//            pthread_exit(NULL);
            // 使用return也可以
//            return NULL;
        }
    }
    return NULL;
}

void *myfunc1(void *arg) {
    printf("child thread: %lu\n", pthread_self());
    for(int i=0;i<5;i++){
        printf("child i = %d\n", i);
        if(i == 2){
            // pthread_exit退出时，携带一个局部变量的值
            // 这个被携带的值可以是一个局部变量吗？可以
            int number = 100;
            pthread_exit(&number);
        }
    }
    return NULL;
}


int main() {
    // 创建一个子线程
    pthread_t pthd;
    int ret = pthread_create(&pthd, NULL, myfunc1, NULL);
    if (ret != 0) {
        printf("error number: %d\n", ret);
        printf("%s", strerror(ret));
    }

    sleep(2);
    printf("parent thread id: %lu\n", pthread_self());
    int i = 0;
    while(1){
        printf("parent i = %d\n", i++);
    }
    pthread_exit(NULL);
    return 0;
}