//
// Created by xixi2 on 2020/8/9.
// 子线程抛出异常

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

using namespace std;

#define NUM_THREADS 1

void *proca(void *) {
    printf("In ProcA\n");
    sleep(5);
    printf("ProcA: Try Throw...\n");
    throw 3;
}

int main() {
    pthread_t tids[NUM_THREADS];
    printf("In Main Thread.\n");
    int ret = pthread_create(&tids[0], NULL, proca, NULL);
    printf("ProcA Started.\n");

    sleep(10);
    printf("Start joining A\n");
    pthread_join(tids[0], NULL);

    return 0;
}