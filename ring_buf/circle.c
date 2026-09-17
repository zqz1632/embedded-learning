#include <stdio.h>
#include "circle.h"

static unsigned char head=0;
static unsigned char tail=0;
static unsigned char buf[8]={0};

int put(unsigned char x)
{
    if ((head+1)%buf_N==tail)
    {
        printf("无法写入\n");
        return -1;
    }
    else{
        buf[head]=x;
        head = (head+1) % buf_N;
        return 0;
    }
}

int get(unsigned char *p)
{
    if(head==tail)
    {
        printf("不能读取\n");
        return -1;
    }
    else
    {
        *p=buf[tail];
        tail = (tail+1)%buf_N;
        return 0;
    }
    
}