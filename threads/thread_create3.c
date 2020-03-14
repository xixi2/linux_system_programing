//
// Created by xixi2 on 2020/3/8.
// 创建5个线程，并打印出每个线程创建的顺序

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pthread.h>

int count = 0;
void * myfunc(void *arg){
    // void*占四个字节，而int也占用四个字节，所以可以强制转换
    // 如果是double类型，就无法如此强转
    int num = (int)arg;
    printf("create the %d child thread %lu\n", num, pthread_self());
    return NULL;
}


int main(){
    pthread_t pthd[5];      // 创建一个线程ID数组
    for(int i=0;i<5;++i){
        // 传地址
//        pthread_create(&pthd[j], NULL, myfunc, (void*)&count);

        // 传值
        pthread_create(&pthd[i], NULL, myfunc, (void*)i);
        ++count;
    }
    sleep(5);
    return 0;
}
