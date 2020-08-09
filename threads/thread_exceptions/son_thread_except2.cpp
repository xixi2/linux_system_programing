//
// Created by xixi2 on 2020/8/9.
//

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstring>
#include <climits>
#include <cstdio>
#include<pthread.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

void signalHandler(int signum) {
    cout << "enter signalHandler, signum:" << signum << endl;
    pthread_exit(&signum);
}

void *sigsegv_func(void *data) {
    signal(SIGSEGV, signalHandler);
    cout << "Calling func" << (long) (data) << endl;
    int *a = NULL;
    cout << a[2] << endl;
    pthread_exit(0);
}


void *sigabort_func(void *ptr) {
    signal(SIGABRT, signalHandler);
    printf("son thread\n");
    string *s = new string(1000000000000000, 'a');
    pthread_exit(0);
}

int main() {
    pthread_t thread1;
    pthread_create(&thread1, 0, &sigsegv_func, (void *) 2);
//    pthread_create(&thread1, 0, &sigabort_func, nullptr);
    pthread_join(thread1, NULL);
    sleep(1);
    cout << "complete" << endl;
    return 0;
}