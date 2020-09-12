//
// Created by xixi2 on 2020/3/12.
// 从xia消息队列中读取消息


#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FILEPATH "/etc/passwd"
#define PROJID 1234

struct msgbuf{
    long mtype;
    char mtext[BUFSIZ];
};

int main(){
    int msgid;
    key_t key;      // key_t为__int32_t
    struct msgbuf buf;
    key = ftok(FILEPATH, PROJID);

    if(key == -1){
        perror("ftok() error");
        exit(1);
    }

    // 访问一个已经存在的消息队列，指定msgflag为0
    msgid = msgget(key, 0);
    if(msgid == -1){
        perror("msgget() error");
        exit(1);
    }
    printf("key: %d\n", key);
    printf("msgid: %d\n", msgid);

    if(msgrcv(msgid, &buf, BUFSIZ, 1, 0) == -1){
        perror("msgrcv() error");
        exit(1);
    }
    printf("mtype :%d\n", buf.mtype);
    printf("mtex: %s\n", buf.mtext);

    if(msgctl(msgid, IPC_RMID, NULL) == -1){
        perror("msgctl() error");
        exit(1);
    }
    return 0;
}