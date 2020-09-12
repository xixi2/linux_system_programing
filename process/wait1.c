//
// Created by xixi2 on 2020/3/15.
//调用wait回收子进程


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(){
    pid_t pid = fork();
    if(pid == 0){
        // 如果想让子进程被信号杀死，可以让子进程while死循环，然后用kill给子进程发送一个信号
        while(1){
            sleep(1);
            printf("child pid=%d, ppid=%d\n", getpid(), getppid());
        }
    }else if(pid > 0){      // 父进程，让父进程一直或者，子进程将成为僵尸进程
        printf("parent pid=%d, ppid=%d\n", getpid(), getppid());
        int status;
        pid_t wpid = wait(&status);       // wait阻塞至子进程死掉

        // 判断子进程是否正常退出
        if(WIFEXITED(status)){
            printf("exit value: %d\n", WEXITSTATUS(status));
        }else if(WIFSIGNALED(status)){      // 子进程被信号终止
            printf("exit by signal :%d\n", WTERMSIG(status));
        }
        printf("died chilid pid: %d\n", wpid);
    }
    for(int i=0;i<2;++i){
        printf("i=%d\n", i);
    }
    return 0;
}

