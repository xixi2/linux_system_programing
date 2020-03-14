//
// Created by xixi2 on 2020/3/6.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

int main(){
    int ret = alarm(5);
    printf("ret:%d\n", ret);    // 距离上一个定时器可以发信号还有多久
    sleep(2);
    ret = alarm(2);
    printf("ret=%d\n", ret);
    while(1){
        printf("hello, world\n");
        sleep(1);
    }

    // 返回值Alarm clock: 14表示进程是被定时器对应的信号杀死的
    return 0;
}