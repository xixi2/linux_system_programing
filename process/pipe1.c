//
// Created by xixi2 on 2020/3/12.
// 管道实现父子进程通信，ps aux | grep bash

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main(){
    int fd[2];
    int ret = pipe(fd);     // fd[0]读端
    if(ret == -1){
        perror("pipe error");
        exit(1);
    }
    printf("pipe[0] = %d\n", fd[0]);
    printf("pipe[1] = %d\n", fd[1]);

    pid_t pid = fork();
    if(pid == -1){
        perror("fork() error");
        exit(1);
    }else if(pid > 0){  // 父进程，执行ps aux
        // 写管道操作
        close(fd[0]);   // 关闭读端

        // 将标准输出指向管道的写端
        // 修改文件描述符1指向的文件，原来指向/dev/tty，现在指向管道的写端
        dup2(fd[1], STDOUT_FILENO);
        execlp("ps", "ps", "aux", NULL);

        // 如果execlp成功执行，就不会运行到这里
        perror("execlp");
        exit(1);
    }else{              // 子进程，执行grep bash
        close(fd[1]);   // 关闭写端

        // 让标准输入指向管道的读端
        dup2(fd[0], STDIN_FILENO);
        execlp("grep", "grep", "--color=auto", "bash", NULL);
        perror("execlp");
    }

    close(fd[0]);       // 关闭读端
    close(fd[1]);       // 关闭写端
    return 0;
}