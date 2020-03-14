//
// Created by xixi2 on 2020/3/4.
// 验证父子进程对数据的读时共享，写时复制
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

int counter = 200;



// 为什么写时复制，不同变量的地址是一样的？
// https://blog.csdn.net/tab_tab_tab/article/details/51261145
intptr_t Mytop(uintptr_t vaddr)
{
    FILE *pagemap;
    intptr_t paddr = 0;
    int offset = (vaddr / sysconf(_SC_PAGESIZE)) * sizeof(uint64_t);
    uint64_t e;
    // https://www.kernel.org/doc/Documentation/vm/pagemap.txt
    if ((pagemap = fopen("/proc/self/pagemap", "r"))) {
        if (lseek(fileno(pagemap), offset, SEEK_SET) == offset) {
            if (fread(&e, sizeof(uint64_t), 1, pagemap)) {
                if (e & (1ULL << 63)) { // page present ?
                    paddr = e & ((1ULL << 54) - 1); // pfn mask
                    paddr = paddr * sysconf(_SC_PAGESIZE);
                    // add offset within page
                    paddr = paddr | (vaddr & (sysconf(_SC_PAGESIZE) - 1));
                }
            }
        }
        fclose(pagemap);
    }
    return paddr;
}

void TestShow(void *x)
{
    printf("Virtual Address:%u  Physical Address:%u\n",x,Mytop((uintptr_t)x));
}



int main(int argc, const char *argv[]) {
    int i = 0;
    int number = 3;
    pid_t pid;
    for (i = 0; i < number; ++i) {
        pid = fork();
        if (pid == 0) {       // 子进程
            break;
        }
    }

    // 第1个孩子
    if (i == 0) {
        counter += 200;
        printf("first process, pid=%d\n", getpid());
        printf("counter:%d\n", counter);
    }

    // 第2个孩子
    if (i == 1) {
        counter += 200;
        printf("second process, pid=%d\n", getpid());
        printf("counter:%d\n", counter);
    }

    // 第3个孩子
    if (i == 2) {
        counter += 200;
        printf("third process, pid=%d\n", getpid());
        printf("counter:%d\n", counter);
    }

    // 父进程
    if (i == number) {
        counter += 400;
        printf("parent process, pid=%d\n", getpid());
        printf("counter:%d\n", counter);
    }
    return 0;
}
