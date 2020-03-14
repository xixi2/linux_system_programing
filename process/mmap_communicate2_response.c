//
// Created by xixi2 on 2020/3/5.
// 本文件和mmap_communicate2.c对应，mmap_communicate2.c是读内存映射区，而本文件写内存映射区
// 这个程序还有些问题

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    int fd = open("temp.txt", O_RDWR, 0664);  // 创建一个临时文件，借助于这个临时文件创建内存映射区

    int len = lseek(fd, 0, SEEK_END);
    void *ptr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap error");
        exit(1);
    }

    int i = 0;
    while (1) {
        char *p = (char *) ptr;
        p += 1024;
        printf("ready to write: %d", i++);
        strcpy(p, "hello parent, I am your friend!\n");
        sleep(20);
//        if (i++ == 10) {
//            break;
//        }
    }

    close(fd);
    munmap(ptr, len);
    return 0;
}