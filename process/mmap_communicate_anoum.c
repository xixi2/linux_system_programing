//
// Created by xixi2 on 2020/3/5.
// 匿名内存映射区

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stdio.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int len = 4096;
    void *ptr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);   // 创建匿名映射区
    if (ptr == MAP_FAILED) {
        perror("mmap error");
        exit(1);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork error");
        exit(1);
    } else if (pid == 0) {
        sleep(10);
        printf("%s", (char *) ptr);   // 读内存映射区，输出到标准输出
    } else {      // 父进程
        strcpy(ptr, "hello world"); // 向内存映射区写数据
        wait(NULL);                 // 回收子进程
    }

    munmap(ptr, len);
    return 0;
}


