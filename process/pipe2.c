//
// Created by xixi2 on 2020/3/15.
// 管道实现兄弟进程通信 实现ps aux | grep bash



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>


int main() {
    // 创建一个管道
    int fd[2];      //fd[0]读端，fd[1]写端
    int ret = pipe(fd);
    if (ret == -1) {
        perror("pipe() error");
        exit(1);
    }
    // 创建两个子进程
    int i;
    for (i = 0; i < 2; ++i) {
        pid_t pid = fork();
        if (pid < 0) {        // 出错
            perror("fork() error");
            exit(1);
        } else if (pid == 0) { // 子进程
            // 如果不break出去，那么子进程会继续执行i=1并fork出一个子进程
            break;
        }
    }
    if (i == 2) {     // 父进程 会执行完循环
        close(fd[0]);
        close(fd[1]);

        // 回收两个子进程
        pid_t wpid;
        int status;
        while ((wpid = waitpid(-1, &status, WNOHANG))!=-1){
            if(wpid == 0){      // 当waitpid的第三个参数是WNOHANG时，wpid==0说明，子进程正在运行
                continue;
            }
            // 判断子进程退出状态
            if(WIFEXITED(status)){      // WIFEXITED(status)为非0说明进程正常结束
                printf("exit value: %d\n", WEXITSTATUS(status));
            }else if(WIFSIGNALED(status)){
                printf("exit by signal :%d\n", WTERMSIG(status));
            }
        }
    } else if (i == 0) {   // 读进程
        close(fd[1]);
        printf("child write = %d\n", getpid());

        dup2(fd[0], STDIN_FILENO);  // 让读进程的标准输入连接到管道的读端
        execlp("grep", "grep", "--color", "bash", NULL);
        perror("grep error");
        exit(1);
    } else {              // 写进程
        close(fd[0]);
        printf("child write = %d\n", getpid());

        dup2(fd[1], STDOUT_FILENO);// 让写进程的标准输出连接到管道的写端
        execlp("ps", "ps", "aux", NULL);
        perror("ps error");
        exit(1);
    }
    return 0;
}