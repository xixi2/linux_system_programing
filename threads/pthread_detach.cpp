//
// Created by xixi2 on 2020/8/8.
//


#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

void *print_message_function(void *ptr);

int main() {
    pthread_t thread1;
    pthread_create(&thread1, NULL, print_message_function, NULL);
    printf("main thread \n");
    pthread_exit(0);
}

void *print_message_function(void *ptr) {
    pthread_detach(pthread_self());
    static int g;
    printf("spawning thread start, g: %d\n", g++);
    sleep(10);
    printf("spawning thread end\n");
    exit(0);
}