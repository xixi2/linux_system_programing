//
// Created by xixi2 on 2020/5/2.
// 从标准输入读命令并执行 P9

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

#define MAXLINE 4096

int main() {
    char buf[MAXLINE];
    pid_t pid;
    int status;

    printf("%% ");
    // fgets从标准输入一次读一行，当键入文件结束符（通常是ctrl+d）作为行的第1个字符时，fgets返回一个null指针，于是循环终止，进程也就终止
    // 当键入文件结束符，表示到达文件末尾，返回一个空指针
    while (fgets(buf, MAXLINE, stdin) != NULL) {
        // fgets会把遇到的回车符也记录到buf中，如果最后一个字符是回车，就将其置为空字符
        if (buf[strlen(buf) - 1] == '\n') {
            buf[strlen(buf) - 1] = 0;
        }
        if ((pid = fork()) < 0) {
            perror("fork error");
            exit(1);
        } else if (pid == 0) {
            // execlp执行的命令没有参数，arg部分以NULL结束，(char*)0
            // 当前版本不支持execlp执行的命令有参数。加强版：给execlp传递参数，使该程序能支持cat类需要参数的命令
            execlp(buf, buf, (char *) 0);
            printf("could not execute: %s", buf);
            exit(127);
        }

        if ((pid = waitpid(pid, &status, 0)) < 0) {
            perror("waitpid error");
            exit(1);
        }
        printf("%% ");
    }

    return 0;
}