//
// Created by xixi2 on 2020/4/20.
//

/* fork和write、printf
 * 面试中遇到的一道题
 * */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>


int main() {
    for (int i = 0; i < 2; ++i) {
        pid_t pid = fork();
        if (pid == -1) {
            exit(1);
        }
//        write(STDOUT_FILENO, "-", 1); // 输出6个-
        printf("-");            // 输出8个-
        if (pid > 0) {
            wait(&pid);
        }
    }
    return 0;
}