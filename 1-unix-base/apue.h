//
// Created by xixi2 on 2020/5/2.
//

#ifndef LINUX_SYSTEM_PROGRAMING_APUE_H
#define LINUX_SYSTEM_PROGRAMING_APUE_H

#define _XOPEN_SOURCE 600

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/termios.h>

#ifndef TIOCGWINSZ

#include <sys/ioctl.h>

#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#define MAXLINE 4096


#endif //LINUX_SYSTEM_PROGRAMING_APUE_H
