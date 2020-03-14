//
// Created by xixi2 on 2020/3/8.
//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <pthread.h>


void* myfunc(void* arg){
    printf("child thread id: %d\n", pthread_self());
    while(1){
        int i, j, k;
        i = 10, j = 20;
        k = i + j;
        printf("k = %d\n", k);

        // 测试取消点
        pthread_testcancel();
    }
    return NULL;
}

int main(){
    pthread_t pthd;

    //
    int ret = pthread_create(&pthd, NULL, myfunc, NULL);
    if(ret != 0){
        printf("error number: %d\n", ret);
        printf("%s\n", strerror(ret));
    }

    printf("parent thread id: %lu\n", pthread_self());

    return 0;
}