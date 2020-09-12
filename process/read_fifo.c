//
// Created by xixi2 on 2020/3/20.
// 读fifo文件

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>


int main(int argc, char* argv[]) {
    if(argc < 2){
        printf("./a.out fifoname\n");
        exit(1);
    }

    // 判断文件是否存在
    int ret = access(argv[1], F_OK);
    if(ret == -1){
        int r = mkfifo(argv[1], 0664);
        if(r == -1){
            perror("mkfifo error");
            exit(1);
        }
        printf("命名管道%s创建成功\n", argv[1]);
    }
    int fd = open(argv[1], O_RDONLY);
    if(fd == -1){
        perror("open error");
        exit(1);
    }
    char buf[32];
    while(1){
        // 如果没数据，那么read系统调用将阻塞
        int len = read(fd, buf, sizeof(buf));
        buf[len] = 0;
        printf("buf=%s\n len=%d\n", buf, len);
    }
    close(fd);
    return 0;
}