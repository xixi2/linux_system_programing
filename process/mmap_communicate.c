//
// Created by xixi2 on 2020/3/5.
// 使用内存映射区来使父子进程间通信
// 为什么不直接使用文件而使用内存映射区

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    int fd = open("1.txt", O_RDWR);
    int len = lseek(fd, 0, SEEK_END);
    printf("len:%d", len);
    void *ptr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
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

    close(fd);
    munmap(ptr, len);
    return 0;
}