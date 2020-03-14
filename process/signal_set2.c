//
// Created by xixi2 on 2020/3/7.
// 通过定时器来读取当前进程的未决信号集

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <sys/time.h>

void signalHandler() {
    sigset_t *set;
    sigpending(set);    // 读取当前进程的未决信号集
    for (int i = 1; i < 32; ++i) {
        if (sigismember(set, i)) {
            printf("1");
        } else {
            printf("0");
        }
    }
    printf("\n");
}

int main() {
    signal(SIGALRM, signalHandler);

    struct itimerval new_value;
    // 首次触发的时间是2秒后
    new_value.it_value.tv_sec = 2;
    new_value.it_value.tv_usec = 0;

    // 定时触发的时间是每1秒执行一次
    new_value.it_interval.tv_sec = 1;
    new_value.it_interval.tv_usec = 0;

    setitimer(ITIMER_REAL, &new_value, NULL);
    while (1){
        for(int i=0;i<10000;++i);
        sleep(1);
    }
    return 0;
}