#include <stdio.h>
#include "circle.h"

int main(void)
{
    unsigned char a=0;
    int b=0;
    put(0x11);
    put(0x22);
    put(0x33);
    b=get(&a);
    printf("%dbuf:0x%x\n",b,a);
    b=get(&a);
    printf("%dbuf:0x%x\n",b,a);
    b=get(&a);
    printf("%dbuf:0x%x\n",b,a);
    b=get(&a);
    printf("%dbuf:0x%x\n",b,a);
}