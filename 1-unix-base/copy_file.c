//
// Created by xixi2 on 2020/5/2.
// 用不带缓冲的IO复制文件

#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFSIZE 4096

int main(void) {
    int n;
    char buf[BUFFSIZE];
    // read函数返回读得得字节数。当达到文件末尾时，返回0
    // 如果发生读错误，read返回-1
    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0) {
        if (write(STDOUT_FILENO, buf, n) != n) {
            perror("write error");
            exit(1);
        }
    }
    if (n < 0) {
        perror("read error");
        exit(1);
    }
    return 0;
}