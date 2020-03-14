//
// Created by xixi2 on 2020/3/6.
//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/time.h>


void signalHandler(int signo) {
    switch (signo) {
        case SIGALRM:
            printf("caught the SIGALRM signal\n");
            break;
    }
}

int main() {
    // 捕获SIGALRM信号，设置事件处理器
    signal(SIGALRM, signalHandler);

    // 设置定时器
    struct itimerval new_val;

    // 第一次触发的时间
    new_val.it_value.tv_sec = 2;        // tv_sec的单位是秒
    new_val.it_value.tv_usec = 0;       // tv_usec的单位是毫秒

    // 周期性定时
    new_val.it_interval.tv_sec = 1;
    new_val.it_interval.tv_usec = 0;

    // 参数ITIMER_REAL，表示以real-time方式减少timer
    // 在timeout时会送出SIGALRM signal
    // ITIMER_VIRTUAL：以该进程在用户态下花费的时间来计算，它送出SIGVTALRM信号
    setitimer(ITIMER_REAL, &new_val, NULL);

    while (1) {
        printf("hello world\n");
        sleep(1);
    }

    return 0;
}


