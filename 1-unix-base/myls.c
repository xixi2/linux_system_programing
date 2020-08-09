//
// Created by xixi2 on 2020/5/2.
// myls程序列出的目录项不是以字母顺序排列的，而ls命令在打印目录项前一般按字母顺序将名字排序

#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    DIR *dp;
    struct dirent *dirp;

    if (argc != 2) {
        perror("usage: ls directory_name");
        exit(1);
    }
    if ((dp = opendir(argv[1])) == NULL) {
        printf("can not open %s", argv[1]);
        exit(1);
    }
    while ((dirp = readdir(dp)) != NULL) {
        printf("%s\n", dirp->d_name);
    }
    closedir(dp);
    return 0;
}