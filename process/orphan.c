//
// Created by xixi2 on 2020/3/15.
// 验证父进程先于子进程死掉，子进程成为孤儿进程，被init收养


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>


int main(){
    pid_t pid = fork();
    if(pid == 0){
        printf("before sleep child pid=%d, ppid=%d\n", getpid(), getppid());
        sleep(1);       // 当子进程从sleep中醒过来时，其父进程已经结束，它将被init进程收养
        printf("child pid=%d, ppid=%d\n", getpid(), getppid());
    }else if(pid > 0){      // 父进程
        usleep(100);
        printf("==========parent\n");
        printf("parent pid=%d, ppid=%d\n", getpid(), getppid());
    }
    return 0;
}

