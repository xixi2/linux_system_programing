//
// Created by xixi2 on 2020/3/7.
// 创建守护进程

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <fcntl.h>

void dowork(){
    // 获取当前时间，将时间写入文件
    time_t cur_time;
    time(&cur_time);

    // 格式化时间
    char *pt = ctime(&cur_time);

    // 0664是给新产生的文件的权限
    int fd = open("/Users/xixi2/Desktop/temp11.txt", O_CREAT | O_WRONLY | O_APPEND, 0664);

    // 把时间数据写入到文件中，写入长度为字符串长度+1，把字符串末尾的0也写入
    write(fd, pt, strlen(pt)+1);
    close(fd);
}

int main() {
    // 创建一个会话
    // 创建子进程，会长
    pid_t pid = fork();
    if (pid > 0) {
        printf("son %d\n", pid);
        // 多种让父进程死去的方法
        exit(1);
        // kill(getpid(), SIGKILL);
        // raise(SIGKILL);
        // abort();
    } else if (pid == 0) {
        //变成会长
        setsid();

        // 改变进程的工作目录
        chdir("/Users/xixi2/Desktop");
        // 重制文件掩码
        umask(0);

        // 关闭文件描述符
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);

        struct sigaction act;
        act.sa_flags = 0;
        act.sa_handler = dowork;
        sigemptyset(&act.sa_mask);
        sigaction(SIGALRM, &act, NULL);

        // 创建一个定时器
        struct itimerval new_value;
        new_value.it_value.tv_sec = 2;      // 第一次触发时间是2秒后
        new_value.it_value.tv_usec = 0;
        new_value.it_interval.tv_sec = 1;   // 周期性触发时间为1秒一次
        new_value.it_interval.tv_usec = 0;
        setitimer(ITIMER_REAL, &new_value, NULL);

        while (1);           // 让子进程一直活着
    }
    return 0;
}