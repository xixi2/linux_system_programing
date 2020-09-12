//
// Created by xixi2 on 2020/3/16.
//


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define BUFSZ 512

int main() {
    int shmid;
    int ret;
    key_t key = ftok("../", 2015);
    if (key == -1) {
        perror("ftok");
        exit(-1);
    }
    system("ipcs -m");  // 共享内存
    shmid = shmget(key, BUFSZ, IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(-1);
    }

    // 映射
    char *shmadd = shmat(shmid, NULL, 0);
    if (shmadd < 0) {
        perror("shmat");
        exit(-1);
    }

    // 读共享内存区数据
    while (1) {
        printf("data=[%s]\n", shmadd);
        usleep(100);

        // 什么时候退出循环呢？
        break;
    }

    // 分离共享内存和当前进程
    ret = shmdt(shmadd);
    if (ret < 0) {
        perror("shmdt");
        exit(1);
    } else {
        printf("deleted shared-memory\n");
    }

    // 删除共享内存
    shmctl(shmid, IPC_RMID, NULL);

    system("ipcs -m");      // 查看共享内存
    return 0;
}