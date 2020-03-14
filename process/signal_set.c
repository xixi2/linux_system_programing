//
// Created by xixi2 on 2020/3/7.
// 读取当前进程的未决信号集

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>

int main(){
    // 每隔1秒读一次内存的未决信号集
    sigset_t *set;
    while(1){
        sigpending(set);
        // 循环31次
        for(int i=1;i<32;++i){
            // 对每一个信号一次判断
            if(sigismember(set, i)){
                printf("1");
            }else{
                printf("0");
            }
        }
        printf("\n");
        sleep(1);
    }
    return 0;
}