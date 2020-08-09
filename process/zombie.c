//
// Created by xixi2 on 2020/3/15.
// 父进程一直活着，子进程将成为僵尸进程，一直存在于系统中


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>


int main(){
    pid_t pid = fork();
    if(pid == 0){
        printf("child pid=%d, ppid=%d\n", getpid(), getppid());
    }else if(pid > 0){      // 父进程，让父进程一直或者，子进程将成为僵尸进程
        while(1){
            sleep(5);
            printf("==========parent\n");
            printf("parent pid=%d, ppid=%d\n", getpid(), getppid());
        }
    }
    return 0;
}

