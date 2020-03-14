//
// Created by xixi2 on 2020/3/8.
// 创建一个子线程

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <pthread.h>

void *myfunc(void *arg) {
    // 打印子线程的ID
    printf("child thread: %lu\n", pthread_self());
    return NULL;
}

int main() {
    // 创建一个子进程
    pthread_t pthd;
    pthread_create(&pthd, NULL, myfunc, NULL);
    printf("parent thread id: %lu\n", pthread_self());

    // 如果这里不进行处理，而主线程首先执行完毕，子线程将不会执行
    // 让主线程睡眠一会可以让子线程得到机会执行
    sleep(5);

    // 验证子线程是否打印这段代码
    // 结果: 子线程不会运行这段代码
    for (int i = 0; i < 5; ++i) {
        printf("i = %d\n", i);
    }
    return 0;
}
