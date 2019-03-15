/**
 * /**
 * ASSIGNMENT 3
 * Partners: Leila Erbay, Richard Gao
 * IDs: 260672158, 260729805
 * Note: Have Mercy :)
 */


#define _GNU_SOURCE
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/utsname.h>
#include <sched.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/********************************* TA CODE--from Comp 310 Facebook ***************/

int clone_function(void *arg){
   printf("\nINFO: This code is running under child process.\n");
   int i =0;
   int n = atoi(arg);
   for (i = 1; i <=10;i++){
     printf("%d * %d = %d\n", n,i,(n*i));
   }
   printf("\n");
   return 0;
}
void main(int argc, char *argv[]){
   printf("Hello,World!\n");
   printf("chmod on %s\n", argv[1]);
   if(chmod(argv[1], S_ISUID) < 0){            //Set by Richard G. 
        printf("chmod S_ISUID failed\n");
   }
   if(chmod(argv[1], S_ISGID) < 0){            //Set by Richard G.
        printf("chmod S_ISGID failed\n");
   }
   if(chmod(argv[1], S_ISGID|S_ISUID) < 0){            //Set by Richard G.
        printf("chmod S_ISGID|S_ISUID failed\n");
   }

   if(chmod(argv[1], S_IRUSR) < 0){            //Set by Leila E.
        printf("chmod should work... shit\n");
   }



   void *pchild_stack = malloc(1024*1024);
   if(pchild_stack == NULL){
       printf("Error: unable to allocate memory.\n");
       exit(EXIT_FAILURE);
   }
   int pid;
   pid = clone(clone_function, pchild_stack+(1024*1024),CLONE_NEWUSER|SIGCHLD, argv[1]);
   if (pid < 0){
      printf("ERROR: Unable to create the child process.\n");
      //exit(EXIT_FAILURE);
   }

   pid = clone(clone_function, pchild_stack+(1024*1024),CLONE_VFORK, argv[1]);  //Set by Leila E.
   if (pid < 0){
      printf("ERROR: Unable to create the child process.\n");
      exit(EXIT_FAILURE);
   }

   wait(NULL);
   free(pchild_stack);
   printf("INFO: CHILD PROCESS TERMINATED.\n");
}