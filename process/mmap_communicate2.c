//
// Created by xixi2 on 2020/3/5.
//

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    int fd = open("temp.txt", O_RDWR | O_CREAT, 0664);  // 创建一个临时文件，借助于这个临时文件创建内存映射区
    ftruncate(fd, 4096);                                 // 因为临时文件的大小为0，所以扩展该文件的大小为4k
    int len = lseek(fd, 0, SEEK_END);
    void *ptr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap error");
        exit(1);
    }

//    int i = 0;
    while (1) {
        sleep(10);
        printf("%s", (char *) ptr + 1024);
//        if (i++ == 10) {
//            break;
//        }
    }

    close(fd);
    munmap(ptr, len);
    return 0;
}