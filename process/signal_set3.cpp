//
// Created by xixi2 on 2020/3/7.
//


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>

int main() {
    sigset_t myset;
    sigemptyset(&myset);

    // 添加要阻塞的信号
    sigaddset(&myset, SIGINT);  // ctrl+c:2
    sigaddset(&myset, SIGQUIT); // ctrl+反斜杠:3
    sigaddset(&myset, SIGKILL); // 9号信号，无法被捕捉、阻塞

    // 自定义信号集合设置给内核的阻塞信号集
    sigprocmask(SIG_BLOCK, &myset, NULL);
    while(1){
        sigset_t pendset;
        sigpending(&pendset);
        for(int i=1;i<32;++i){
            if(sigismember(&pendset, i)){
                printf("1");
            }else{
                printf("0");
            }
        }
        printf("\n");
        sleep(1);
    }
    return 0;
}