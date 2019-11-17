/* use_malloc.c */
#include "stdlib.h"
#include "stdio.h"

void use_malloc()
{
    int *ptr = (int *)malloc(sizeof(int));
    printf("ptr = %p\n", ptr);
    free(ptr);
}
