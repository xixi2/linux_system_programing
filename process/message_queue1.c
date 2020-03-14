//
// Created by xixi2 on 2020/3/12.
// 向消息队列中发送消息

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FILEPATH "/etc/passwd"
#define PROJID 1234
#define MSG "hello world!"

struct msgbuf{
    long mtype;
    char mtext[BUFSIZ];
};


int main(){
    int msgid;
    key_t key;
    struct msgbuf buf;
    key = ftok(FILEPATH, PROJID);
    if(key == -1){
        perror("ftok() error");
        exit(1);
    }

    // 使用msgget访问一个已经存在的消息队列，msgflag指定为0
    msgid = msgget(key, 0);
    if(msgid == -1){
        perror("msgget() error");
        exit(1);
    }
    printf("key: %d\n", key);
    printf("msgid: %d\n", msgid);

    buf.mtype = 1;
    strncpy(buf.mtext, MSG, strlen(MSG));
    if(msgsnd(msgid, &buf, strlen(buf.mtext), 0) == -1){
        perror("msgsnd() error");
        exit(1);
    }
    return 0;
}