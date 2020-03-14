//
// Created by xixi2 on 2020/3/12.
//

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>

#define FILEPATH "/etc/passwd"
#define PROJID 1234

int main(){
    int msgid;
    key_t key;
    struct msqid_ds msg_buf;
    key = ftok(FILEPATH, PROJID);
    if(key == -1){
        perror("ftok()");
        exit(1);
    }

    msgid = msgget(key, IPC_CREAT | IPC_EXCL | 0600);
    if(msgid == -1){
        perror("msgget()");
        exit(1);
    }

    if(msgctl(msgid, IPC_STAT, &msg_buf) == -1){
        perror("msgctl()");
        exit(1);
    }

    // 删除消息队列
    if(msgctl(msgid, IPC_RMID, NULL) == -1){
        perror("msgctl()");
        exit(1);
    }

    printf("msgid: %d\n", msgid);
    printf("msg_perm.uid: %d\n", msg_buf.msg_perm.uid);
    printf("msg_perm.gid: %d\n", msg_buf.msg_perm.gid);
    printf("msg_stime: %d\n", msg_buf.msg_stime);
    printf("msg_rtime: %d\n", msg_buf.msg_rtime);
    printf("msg_qnum: %d\n", msg_buf.msg_qnum);
    printf("msg_qbytes: %d\n", msg_buf.msg_qbytes);
    return 0;
}