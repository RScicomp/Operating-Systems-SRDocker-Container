/**
 *  @title      :   sr_container.c
 *  @author     :   Shabir Abdul Samadh (shabirmean@cs.mcgill.ca)
 *  @date       :   20th Nov 2018
 *  @purpose    :   COMP310/ECSE427 Operating Systems (Assingment 3) - Phase 2
 *  @description:   A template C code to be filled in order to spawn container instances
 *  @compilation:   Use "make container" with the given Makefile
*/

/**
 * ASSIGNMENT 3
 * Partners: Leila Erbay, Richard Gao
 * IDs: 260672158, 260729805
 * Note: Have Mercy :)
 */

#include "sr_container.h"

/**
 *  The cgroup setting to add the writing task to the cgroup
 *  '0' is considered a special value and writing it to 'tasks' asks for the wrinting 
 *      process to be added to the cgroup. 
 *  You must add this to all the controls you create so that it is added to the task list.
 *  See the example 'cgroups_control' added to the array of controls - 'cgroups' - below
 **/  
struct cgroup_setting self_to_task = {
    .name = "tasks",
    .value = "0"
};

/**
 *  ------------------------ TODO ------------------------
 *  An array of different cgroup-controllers.
 *  One controller has been been added for you.
 *  You should fill this array with the additional controls from commandline flags as described 
 *      in the comments for the main() below
 *  ------------------------------------------------------
 **/ 
struct cgroups_control *cgroups[6] = {
    & (struct cgroups_control) {		//this is a pointer
        .control = CGRP_BLKIO_CONTROL,
        .settings = (struct cgroup_setting *[]) {
            & (struct cgroup_setting) {
                .name = "blkio.weight",
                .value = "64"
            },
            &self_to_task,             // must be added to all the new controls added
            NULL                       // NULL at the end of the array
        }
    },
    NULL                               // NULL at the end of the array
};


/**
 *  ------------------------ TODO ------------------------
 *  The SRContainer by default suppoprts three flags:
 *          1. m : The rootfs of the container
 *          2. u : The userid mapping of the current user inside the container
 *          3. c : The initial process to run inside the container
 *  
 *   You must extend it to support the following flags:
 *          1. C : The cpu shares weight to be set (cpu-cgroup controller)
 *          2. s : The cpu cores to which the container must be restricted (cpuset-cgroup controller)
 *          3. p : The max number of process's allowed within a container (pid-cgroup controller)
 *          4. M : The memory consuption allowed in the container (memory-cgroup controller)
 *          5. r : The read IO rate in bytes (blkio-cgroup controller)
 *          6. w : The write IO rate in bytes (blkio-cgroup controller)
 *          7. H : The hostname of the container 
 * 
 *   You can follow the current method followed to take in these flags and extend it.
 *   Note that the current implementation necessitates the "-c" flag to be the last one.
 *   For flags 1-6 you can add a new 'cgroups_control' to the existing 'cgroups' array
 *   For 7 you have to just set the hostname parameter of the 'child_config' struct in the header file
 *  ------------------------------------------------------
 **/
/*------------------------------------- Part2 Question1  ------------------------------------------*/
struct cgroups_control* init_cgroup(int num_settings){
    struct cgroups_control *init_cgroup =(struct cgroups_control*) calloc(1, sizeof(struct cgroups_control));
    init_cgroup->settings = (struct cgroup_setting**) calloc(num_settings,sizeof(struct cgroup_setting*));   //make space for num_settings pointers
    for (int i = 0; i < num_settings; i++){
        init_cgroup->settings[i] = (struct cgroup_setting*) calloc(1,sizeof(struct cgroup_setting));
    }
    return init_cgroup;
}

int main(int argc, char **argv)
{
    struct child_config config = {0};
    int option = 0;
    int sockets[2] = {0};
    pid_t child_pid = 0;
    int last_optind = 0;
    bool found_cflag = false;
     int empty_index = 0;

    //MALLOCs for each cgroups: blkio, cpu, cpuset, pids, memory/

        //INIT CGROUPS
        struct cgroups_control* cpu_cgroup = init_cgroup(3);    //init cgroup --cpu_cgroup
        struct cgroups_control* cpuset_cgroup = init_cgroup(4);     //init cgroup -- cpuset_cgroup
        struct cgroups_control* pids_cgroup = init_cgroup(3);       //init cgroup -- pids_cgroup
        struct cgroups_control* memory_cgroup = init_cgroup(3);     //init cgroup -- memory_cgroup
		

        
      	struct cgroups_control *blkio_cgroup= init_cgroup(5);   //init cgroup -- blkio cgroup

      	strcpy(blkio_cgroup->control, cgroups[0]->control);     //copy original values
      	blkio_cgroup->settings[0] = cgroups[0]->settings[0];
        blkio_cgroup->settings[1] = &self_to_task;

        blkio_cgroup->settings[2] = NULL;
        blkio_cgroup->settings[3] = NULL;
        blkio_cgroup->settings[4] = NULL;
		


    while ((option = getopt(argc, argv, "c:m:u:C:s:p:M:r:w:H:")))
    {
        if (found_cflag)
            break;

        switch (option)
        {

        /************************ CONFIGURATION SETTINGS *******************************/
        case 'c':   //initial process (ie /bin/bash)
            config.argc = argc - last_optind - 1;
            config.argv = &argv[argc - config.argc];
            found_cflag = true;
            break;

        case 'm':   //root fs (ie rootfs)
            config.mount_dir = optarg;
            break;

        case 'u':   //userid of spawned container (ie 0)
            if (sscanf(optarg, "%d", &config.uid) != 1) {
                fprintf(stderr, "UID not as expected: %s\n", optarg);
                cleanup_stuff(argv, sockets);
                return EXIT_FAILURE;
            }
            break;

        case 'H':   //hostname (eg MickeyMouse)
            config.hostname = optarg;
            break;
        /************************ CPU CGROUP *******************************/     
        case 'C':               //cpu-cgroup cpu_shares setting (ie 7 )
            //setup cgroup
            strcpy(cpu_cgroup->control,CGRP_CPU_CONTROL);

            //SETTINGS
            strcpy(cpu_cgroup->settings[0]-> name , "cpu.shares");
            strcpy(cpu_cgroup->settings[0]-> value, optarg);
            cpu_cgroup->settings[1] = &self_to_task;
            cpu_cgroup->settings[2]= NULL;
        
            for (int i = 0; i < 6; i++){    //find empty space in cgroups and place init cgroup there
                if (cgroups[i] == NULL){
                  cgroups[i] = cpu_cgroup;
                  cgroups[i+1] =NULL;       //make the next spot null for consistency
                  break;
                }
            }
        
            break;

        /*************************** CPUSET CGROUP ***************************/ 
        case 's':   //cpuset-cgroup which core to restrict to (ie 0)
            //setup cgroup
            strcpy(cpuset_cgroup->control,CGRP_CPU_SET_CONTROL);

            //SETTINGS
            strcpy(cpuset_cgroup->settings[0]-> name , "cpuset.cpus");
            strcpy(cpuset_cgroup->settings[0]-> value, optarg);
            strcpy(cpuset_cgroup->settings[1]-> name, "cpuset.mems");       //maybe place in spot 0 and cpus in spot 1 -- shouldn't matter
            strcpy(cpuset_cgroup->settings[1]-> value, "0-1");
            cpuset_cgroup->settings[2] = &self_to_task;
            cpuset_cgroup->settings[3]= NULL;
        
            for (int i = 0; i < 6; i++){        //find empty space in cgroups and place init cgroup there
                if (cgroups[i] == NULL){
                  cgroups[i] = cpuset_cgroup;
                  cgroups[i+1] =NULL;           //make the next spot null for consistency
                  break;
                }
            }

            break;

        /***************************** PIDS CGROUP *******************************/    
        case 'p':   //pid-cgroup number of processes allowed to run before being killed  (ie 50)
             strcpy(pids_cgroup->control,CGRP_PIDS_CONTROL);

            //SETTINGS
            strcpy(pids_cgroup->settings[0]-> name , "pids.max");
            strcpy(pids_cgroup->settings[0]-> value, optarg);
            pids_cgroup->settings[1] = &self_to_task;
            pids_cgroup->settings[2]= NULL;
        
            for (int i = 0; i < 6; i++){    //find empty space in cgroups and place init cgroup there
                if (cgroups[i] == NULL){
                  cgroups[i] = pids_cgroup;
                  cgroups[i+1] =NULL;       //make the next spot null for consistency
                  break;
                }
            }

            break;

        /***************************** MEMORY CGROUP *******************************/     
        case 'M':   //memory-cgroup amount of allowance of memory use for this container (ie  10485760 (10mb))
            strcpy(memory_cgroup->control,CGRP_MEMORY_CONTROL);

            //SETTINGS
            strcpy(memory_cgroup->settings[0]-> name , "memory.limit_in_bytes");
            strcpy(memory_cgroup->settings[0]-> value, optarg);
            memory_cgroup->settings[1] = &self_to_task;
            memory_cgroup->settings[2]= NULL;
        
            for (int i = 0; i < 6; i++){             //find empty space in cgroups and place init cgroup there
                if (cgroups[i] == NULL){
                  cgroups[i] = memory_cgroup;
                  cgroups[i+1] =NULL;           //make the next spot null for consistency
                  break;
                }
            }
            break;

        /***************************** BLKIO CGROUP - READ *******************************/     
        case 'r':   //blkio-cgroup  limit number of read bytes per second (ie "8:0 10m")
            
            //SETTINGS
            empty_index = 0;
            for (int i = 0; i < 5; i++){
            	if (blkio_cgroup->settings[i] == NULL ){
            		empty_index = i;			//find empty spot in blkio settings
            		break;
            	}
            }
            
            blkio_cgroup->settings[empty_index] = (struct cgroup_setting*) calloc(1,sizeof(struct cgroup_setting));
            strcpy(blkio_cgroup->settings[empty_index]-> name , "blkio.throttle.read_bps_device");
            strcpy(blkio_cgroup->settings[empty_index]-> value, optarg);
            blkio_cgroup->settings[empty_index+1] = NULL;	

          	cgroups[0] = blkio_cgroup;      //replace what exists in cgroups[0]
            

            break;

        /***************************** BLKIO CGROUP  - WRITE *******************************/     
        case 'w':   //blkio-cgroup  limit number of write bytes per second (ie "8:0 5m")
        	empty_index = 0;
            for (int i = 0; i < 5; i++){
            	if (blkio_cgroup->settings[i] == NULL){
            		empty_index = i;    //find empty spot in blkio settings
            		break;
            	}
            }

            blkio_cgroup->settings[empty_index] = (struct cgroup_setting*) calloc(1,sizeof(struct cgroup_setting));
            strcpy(blkio_cgroup->settings[empty_index]-> name , "blkio.throttle.write_bps_device");
            strcpy(blkio_cgroup->settings[empty_index]-> value, optarg);
            blkio_cgroup->settings[empty_index+1] = NULL;		

            cgroups[0] = blkio_cgroup;          //replace what exists in cgroups[0]
            break;

        
        default:
            cleanup_stuff(argv, sockets);
            return EXIT_FAILURE;
        }
        last_optind = optind;
    }

/********************************* TA CODE  ***************************************************/
    if (!config.argc || !config.mount_dir){
        cleanup_stuff(argv, sockets);
        return EXIT_FAILURE;
    }

    fprintf(stderr, "####### > Checking if the host Linux version is compatible...");
    struct utsname host = {0};
    if (uname(&host))
    {
        fprintf(stderr, "invocation to uname() failed: %m\n");
        cleanup_sockets(sockets);
        return EXIT_FAILURE;
    }
    int major = -1;
    int minor = -1;
    if (sscanf(host.release, "%u.%u.", &major, &minor) != 2)
    {
        fprintf(stderr, "major minor version is unknown: %s\n", host.release);
        cleanup_sockets(sockets);
        return EXIT_FAILURE;
    }
    if (major != 4 || (minor < 7))
    {
        fprintf(stderr, "Linux version must be 4.7.x or minor version less than 7: %s\n", host.release);
        cleanup_sockets(sockets);
        return EXIT_FAILURE;
    }
    if (strcmp(ARCH_TYPE, host.machine))
    {
        fprintf(stderr, "architecture must be x86_64: %s\n", host.machine);
        cleanup_sockets(sockets);
        return EXIT_FAILURE;
    }
    fprintf(stderr, "%s on %s.\n", host.release, host.machine);

    if (socketpair(AF_LOCAL, SOCK_SEQPACKET, 0, sockets))
    {
        fprintf(stderr, "invocation to socketpair() failed: %m\n");
        cleanup_sockets(sockets);
        return EXIT_FAILURE;
    }
    if (fcntl(sockets[0], F_SETFD, FD_CLOEXEC))
    {
        fprintf(stderr, "invocation to fcntl() failed: %m\n");
        cleanup_sockets(sockets);
        return EXIT_FAILURE;
    }
    config.fd = sockets[1];

/********************************* TA CODE  ***************************************************/
    /**
     * ------------------------ TODO ------------------------
     * This method here is creating the control groups using the 'cgroups' array
     * Make sure you have filled in this array with the correct values from the command line flags 
     * Nothing to write here, just caution to ensure the array is filled
     * ------------------------------------------------------
     **/
    if (setup_cgroup_controls(&config, cgroups))
    {
        clean_child_structures(&config, cgroups, NULL);
        cleanup_sockets(sockets);
        return EXIT_FAILURE;
    }

//*---------------------------------------- Part2 Question2  ---------------------------------------------*//
    /**
     * ------------------------ TODO ------------------------
     * Setup a stack and create a new child process using the clone() system call
     * Ensure you have correct flags for the following namespaces:
     *      Network, Cgroup, PID, IPC, Mount, UTS (You don't need to add user namespace)
     * Set the return value of clone to 'child_pid'
     * Ensure to add 'SIGCHLD' flag to the clone() call
     * You can use the 'child_function' given below as the function to run in the cloned process
     * HINT: Note that the 'child_function' expects struct of type child_config.
     * ------------------------------------------------------
     **/
     char *stack = malloc(STACK_SIZE);

     if (stack == NULL) {
     	perror("malloc");
     	return EXIT_FAILURE;
     }

     char *stackTop = stack + STACK_SIZE;

     int ns_flags = CLONE_NEWNET | CLONE_NEWCGROUP | CLONE_NEWPID |  CLONE_NEWIPC | CLONE_NEWNS | CLONE_NEWUTS;

      child_pid = clone(child_function, stackTop, ns_flags | SIGCHLD, &config );


    /**
     *  ------------------------------------------------------
     **/ 

/********************************* TA CODE  ***************************************************/
    if (child_pid == -1)
    {
        fprintf(stderr, "####### > child creation failed! %m\n");
        clean_child_structures(&config, cgroups, stack);
        cleanup_sockets(sockets);
        return EXIT_FAILURE;
    }
    close(sockets[1]);
    sockets[1] = 0;

    if (setup_child_uid_map(child_pid, sockets[0]))
    {
        if (child_pid)
            kill(child_pid, SIGKILL);
    }

    int child_status = 0;
    waitpid(child_pid, &child_status, 0);
    int exit_status = WEXITSTATUS(child_status);

    clean_child_structures(&config, cgroups, stack);
    cleanup_sockets(sockets);
    return exit_status;
}


int child_function(void *arg)
{
    struct child_config *config = arg;
    if (sethostname(config->hostname, strlen(config->hostname)) || \
                setup_child_mounts(config) || \
                setup_child_userns(config) || \
                setup_child_capabilities() || \
                setup_syscall_filters()
        )
    {
        close(config->fd);
        return -1;
    }
    if (close(config->fd))
    {
        fprintf(stderr, "invocation to close() failed: %m\n");
        return -1;
    }
    if (execve(config->argv[0], config->argv, NULL))
    {
        fprintf(stderr, "invocation to execve() failed! %m.\n");
        return -1;
    }
    return 0;
}