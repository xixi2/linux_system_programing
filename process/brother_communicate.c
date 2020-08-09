//
// Created by xixi2 on 2020/3/20.
// 兄弟进程间通信实现 ps aux | grep bash

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

typedef unsigned int uint;

int main() {
    // 创建一个管道
    int fd[2];
    int ret = pipe(fd);
    if (ret == -1) {
        perror("pipe error");
        exit(1);
    }
    pid_t pid;
    uint i = 0;
    for (; i < 2; ++i) {
        pid = fork();
        if (pid == -1) {
            perror("fork error");
            exit(1);
        }
        if (pid == 0) {
            break;
        }
    }
    if (i == 0) {     // 子进程1，写操作
        close(fd[0]);   // 关闭fd[0]，管道读端
        printf("child write = %d\n", getpid());

        dup2(fd[1], STDOUT_FILENO);
        execlp("ps", "ps", "aux", NULL);
        perror("ps error");
        exit(1);
    } else if (i == 1) { // 子进程2，读操作
        close(fd[1]);   // 关闭fd[1]，管道写端
        printf("child read = %d\n", getpid());

        dup2(fd[0], STDIN_FILENO);
        execlp("grep", "grep", "bash", NULL);
        perror("ps error");
        exit(1);
    } else {          // 父进程
        close(fd[0]);
        close(fd[1]);

        // 回收子进程
        pid_t wpid;
        // waitpid的返回值为-1表示，父进程无子进程
        // WNOHANG表示非阻塞回收
        while ((wpid = waitpid(-1, NULL, WNOHANG)) != -1) {
            if (wpid == 0) {
                continue;
            }
            printf("child died pid=%d\n", wpid);
        }
    }
    return 0;
}