//
// Created by xixi2 on 2020/9/7.
// 有问题

#include <iostream>
#include <pthread.h>
#include <condition_variable>
#include <mutex>

using namespace std;
#define MAX 5

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t notfull = PTHREAD_COND_INITIALIZER;  // 队列是否已满
pthread_cond_t notempty = PTHREAD_COND_INITIALIZER; // 队列是否已空
int top = 0, bottom = 0;

void *produce(void *arg) {
    for (int i = 0; i < MAX * 2; ++i) {
        pthread_mutex_lock(&mutex);
        while ((top + 1) % MAX == bottom) { // top == MAX - 1
            cout << "full! producer is waiting" << endl;

            // 等待队列不满
            pthread_cond_wait(notfull, &mutex);
        }
        top = (top + 1) % MAX;
        // 通知消费者队列不空
        pthread_cond_signal(notempty);
        pthread_mutex_unlock(&mutex);
    }
    int a = 1;
    int *p = &a;
    return static_cast<void *>(p);
}

void *consumer(void *arg) {
    for (int i = 0; i < MAX * 2; ++i) {
        pthread_mutex_lock(&mutex);
        while (top % MAX == bottom) {
            pthread_cond_wait(notempty, &mutex);
        }
        bottom = (bottom + 1) % MAX;

        // 通知生产者队列不满了
        pthread_cond_signal(notfull);
        pthread_mutex_unlock(&mutex);
    }
    int a = 2;
    int *p = &a;
    return static_cast<void *>(p);
}

int main() {
    produce(static_cast<void *>(0));
    consumer(static_cast<void *>(0));
    return 0;
}