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

int main(){
    int shmid;
    int ret;
    key_t key;
    // 创建key值
    key = ftok("../", 2015);
    if(key == -1){
        perror("ftok");
        exit(1);
    }

    // 创建共享内存
    shmid = shmget(key, BUFSZ, IPC_CREAT|0666);
    if(shmid < 0){
        perror("shmget");
        exit(-1);
    }

    // 映射
    char *shmadd;
    shmadd = shmat(shmid, NULL, 0);
    if(shmadd < 0){
        perror("shmat");
        _exit(-1);
    }

    // 拷贝数据至共享内存区
    printf("copy data to shared-memory\n");
//    bzero(shmadd, BUFSZ);       // 清空共享内存
//    strcpy(shmadd, "how are you, lh");
    char *ch = {"one","two","three", "four", "five"};
    int i = 0;
    while(1){
        bzero(shmadd, BUFSZ);       // 清空共享内存
        char* s = ch[i%5];
        ++i;
        strcpy(shmadd, s);
        usleep(100);
    }
    return 0;
}