//
// Created by xixi2 on 2020/3/5.
//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main(int argc, char *argv[]) {
    int fd = open("english.txt", O_RDWR);
    int len = lseek(fd, 0, SEEK_END);
    void *ptr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap error");
        exit(1);
    }
    printf("%s", (char *) ptr);

    char *p = (char *) ptr;
    ++p;
    printf("%s", p);

    // 释放内存映射区
    int ret = munmap(ptr, len);
    if (ret == -1) {
        perror("munmap error");
        exit(1);
    }
    close(fd);
    return 0;
}