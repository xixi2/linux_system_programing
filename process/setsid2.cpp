//
// Created by xixi2 on 2020/3/8.
// 创建另一个子进程

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>

static bool flag = true;
void create_daemon(){
    pid_t pid;
    pid = fork();
    if(pid ==-1){
        printf("fork error\n");
        exit(1);
    }else if(pid > 0){  // 父进程
        exit(1);
    }

    // 子进程
    // 创建守护进程
    if(setsid() == -1){
        printf("setsid error\n");
        exit(1);
    }

    // 创建子进程
    pid = fork();
    if(pid == 01){
        printf("fork error\n");
        exit(1);
    }else if(pid > 0){
        exit(0);
    }
    chdir("/Users/xixi2/Desktop");
    for(int i=0;i<3;++i){
        close(i);
    }
    umask(0);
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}

void handler(int){
    printf("I got a signal %d\n");
    flag = false;
}

int main(){

    return 0;
}