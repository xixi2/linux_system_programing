//
// Created by xixi2 on 2020/5/2.
// 用不带缓冲的IO复制文件

#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


int main(void) {
    int c;

    // read函数返回读得得字节数。当达到文件末尾时，返回0
    // 如果发生读错误，read返回-1
    while ((c = getc(stdin)) != EOF) {
        if (putc(c, stdout) == EOF) {
            perror("write error");
            exit(1);
        }
    }
    if (ferror(stdin)) {
        perror("read error");
        exit(1);
    }
    return 0;
}