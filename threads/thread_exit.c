//
// Created by xixi2 on 2020/3/8.
// pthread_exit让主线程退出


#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

void *myfunc(void* arg){
    // 打印子线程的ID
    printf("child thread: %lu\n", pthread_self());
    for (int i = 0; i < 5; ++i) {
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

    // 退出主线程
    // 后续的代码无法被执行到
    pthread_exit(NULL);

    for (int i = 0; i < 5; ++i) {
        printf("parent i = %d\n", i);
    }
    return 0;
}