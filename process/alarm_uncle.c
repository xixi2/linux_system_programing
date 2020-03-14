//
// Created by xixi2 on 2020/3/6.
//

#include <unistd.h>
#include <stdio.h>

int main(){
    // 设定定时器
    alarm(1);
    int i = 0;
    while(1){
        printf("%d\n", i++);
    }
    return 0;
}