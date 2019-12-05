/**
 * author:nejidev
 * date:2019-12-05
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "sram.h"

int mem_test()
{
    printf("str1 malloc \n");
    char *str1 = (char *)sram_malloc(10);
    if ( ! str1 ) {
        printf("str1 malloc failed \n");
    }
    else {
        memset(str1, 0, 10);
        strcpy(str1, "12345678 \n");
    }
    sram_pools_dump();

    printf("str2 malloc \n");
    char *str2 = (char *)sram_malloc(10);
    if ( ! str2 ) {
        printf("str2 malloc failed \n");
    }
    else {
        memset(str2, 0, 10);
        strcpy(str2, "12345678 \n");
    }
    sram_pools_dump();

    printf("str3 malloc \n");
    char *str3 = (char *)sram_malloc(10);
    if ( ! str3 ) {
        printf("str3 malloc failed \n");
    }
    else {
        memset(str3, 0, 10);
        strcpy(str3, "12345678 \n");
    }
    sram_pools_dump();

    printf("str4 malloc \n");
    char *str4 = (char *)sram_malloc(10);
    if ( ! str4 ) {
        printf("str4 malloc failed \n");
    }
    sram_pools_dump();

    printf("str3 free \n");
    sram_free(str3);
    sram_pools_dump();

    printf("str2 free \n");
    sram_free(str2);
    sram_pools_dump();

    printf("str1 free \n");
    sram_free(str1);
    sram_pools_dump();

    return 0;
}

int mem_test2()
{
    printf("str1 malloc \n");
    char *str1 = (char *)sram_malloc(1024);
    if ( ! str1 ) {
        printf("str1 malloc failed \n");
    }
    else {
        memset(str1, 0, 12);
        strcpy(str1, "12345678 \n");
    }
    sram_pools_dump();

    printf("str2 malloc \n");
    char *str2 = (char *)sram_malloc(500);
    if ( ! str2 ) {
        printf("str2 malloc failed \n");
    }
    else {
        memset(str2, 0, 10);
        strcpy(str2, "12345678 \n");
    }
    sram_pools_dump();

    if ( str2 ) {
        printf("str2 free \n");
        sram_free(str2);
        sram_pools_dump();
    }

    return 0;
}

int mem_test3()
{
    printf("str1 malloc \n");
    char *str1 = (char *)sram_malloc(600);
    if ( ! str1 ) {
        printf("str1 malloc failed \n");
    }
    else {
        memset(str1, 0, 12);
        strcpy(str1, "12345678 \n");
    }
    sram_pools_dump();

    if ( str1 ) {
        printf("str1 free \n");
        sram_free(str1);
        sram_pools_dump();
    }

    return 0;
}

int main(int argc, char **argv)
{
    while(1)
    {
        mem_test();
        mem_test2();
        mem_test3();
        usleep(100);
    }
    return 0;
}
