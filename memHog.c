/**
 * /**
 * ASSIGNMENT 3
 * Partners: Leila Erbay, Richard Gao
 * IDs: 260672158, 260729805
 * Note: Have Mercy :)
 */

/**
 * @Purpose: Memory Hogging Program to test in container -- from part 1 of A3
 */


#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>

int main(){
 int i;
 long sz = 100000;
 mlockall(MCL_FUTURE|MCL_ONFAULT);

 for(int i =0 ; i < 1000; i++){
    printf("Allocating block %d \n",i);
    fflush(stdout);
    char *p = malloc(sz);
    if (p == NULL){
       printf("Allocate block %d \n",i);
       fflush(stdout);
    } else{
       printf("Success..\n");
       fflush(stdout);
    }
    memset(p,0,sz);
    usleep(10000);
 }
 return EXIT_SUCCESS;

}