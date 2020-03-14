//
// Created by xixi2 on 2020/3/6.
//
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>

int main() {
    pid_t pid = fork();
    if (pid > 0) {
        // 父进程，回收子进程资源
        int s;      // s中保存子进程的结束状态
        pid_t wpid = wait(&s);
        if (WIFSIGNALED(s)) {     // 判断子进程是否由于某个信号结束
            printf("child died pid = %d\n", wpid);
        }
    } else if (pid == 0) {     // 子进程，给自己发送一个SIGINT信号终止自己
        raise(SIGINT);
    }
    return 0;
}
