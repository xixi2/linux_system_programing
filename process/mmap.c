//
// Created by xixi2 on 2020/3/5.
// 把文件english.txt映射到内存中

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int fd = open("english.txt", O_RDWR);    // 打开一个文件

    // lseek显式地为一个打开文件设置偏移量
    // lseek(fd, offset, whence)，当whence为SEEK_END时，该文件的文件偏移量设置为文件长度加offset
    // lseek的返回值是新的文件偏移量
    int len = lseek(fd, 0, SEEK_END);        // 获取一个文件的大小

    // 创建内存映射区
    void *ptr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap error");
        exit(1);
    }
    printf("%s", (char *) ptr);   // 打印出内存映射区中的内容
    munmap(ptr, len);
    close(fd);                    // 关闭文件
    return 0;
}
