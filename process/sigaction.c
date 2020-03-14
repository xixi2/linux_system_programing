//
// Created by xixi2 on 2020/3/7.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>

void myfunc(int no){
    printf("hello world\n");
    sleep(3);
    printf("wake up\n");
}

int main(){
    struct sigaction act;
    // 初始化act
    act.sa_flags = 0;

    sigemptyset(&act.sa_mask);  // 当没有要阻塞的信号时，直接情况sa_mask
    sigaddset(&act.sa_mask, SIGQUIT);    // 加入临时屏蔽信号ctrl+反斜杠

    act.sa_handler = myfunc;

    sigaction(SIGINT, &act, NULL);
    while(1);
    return 0;
}