//
// Created by xixi2 on 2020/3/7.
//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>

void myfunc(int signo){
    printf("catch you signal: %d\n", signo);
}


int main(){
    signal(SIGINT, myfunc);
    while(1){
        printf("hello world\n");
        sleep(2);
    }
    return 0;
}