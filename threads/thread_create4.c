//
// Created by xixi2 on 2020/3/8.
// pthread_create的返回值是一个error number（错误号），如何打印出错误信息

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pthread.h>

void* myfunc(void* arg){
    // 打印子线程的ID
    printf("child thread: %lu\n", pthread_self());
    return NULL;
}
int main(){
    pthread_t pthd;
    int ret = pthread_create(&pthd, NULL, myfunc, NULL);
    if(ret !=0){
        printf("error number: %d\n", ret);
        // 打印错误信息
        printf("%s\n", strerror(ret));
    }
    printf("parent thread id: %lu\n", pthread_self());

    sleep(2);
    return 0;
}