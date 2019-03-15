{\rtf1\ansi\ansicpg1252\cocoartf1561\cocoasubrtf600
{\fonttbl\f0\fswiss\fcharset0 Helvetica;\f1\fnil\fcharset0 Menlo-Regular;}
{\colortbl;\red255\green255\blue255;\red212\green214\blue154;\red23\green23\blue23;\red202\green202\blue202;
\red89\green138\blue67;\red23\green23\blue23;\red202\green202\blue202;\red212\green214\blue154;\red167\green197\blue152;
\red183\green111\blue179;\red140\green211\blue254;\red167\green197\blue152;\red70\green137\blue204;\red194\green126\blue101;
\red238\green46\blue56;\red205\green173\blue106;}
{\*\expandedcolortbl;;\cssrgb\c86275\c86275\c66667;\cssrgb\c11765\c11765\c11765;\cssrgb\c83137\c83137\c83137;
\cssrgb\c41569\c60000\c33333;\cssrgb\c11765\c11765\c11765;\cssrgb\c83137\c83137\c83137;\cssrgb\c86275\c86275\c66667;\cssrgb\c70980\c80784\c65882;
\cssrgb\c77255\c52549\c75294;\cssrgb\c61176\c86275\c99608;\cssrgb\c70980\c80784\c65882;\cssrgb\c33725\c61176\c83922;\cssrgb\c80784\c56863\c47059;
\cssrgb\c95686\c27843\c27843;\cssrgb\c84314\c72941\c49020;}
\margl1440\margr1440\vieww14860\viewh12280\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0\fs24 \cf0 # README \'97 A3\
# Partners: Leila Erbay and Richard Gao\
# IDs: 260672158; 260729805\
\
\
##################### Part2 Question 1 ############################\
init_cgroup(int num_settings) :\
	- function to allocate space for control_cgroup* \
	- num_settings is the number of settings that will be necessary for the particular cgroup\
	- eg. cpu_cgroup has 3 settings: cpu.shares, self_to_task, and NULL\
\
- initialized cgroup_control* for each of the cgroups: cpu, cpuset, pids, memory, blkio\
	- blkio we copied what was originally in cgroups[0] related to blkio\
\
- case H: set config.hostname to the value associated with -H\
\
- case C: fill the settings related to cpu cgroup and place in the next NULL inside cgroups**\
\
- case s: fill the settings related to cpuset cgroup and place in the next NULL inside cgroups**\
	note order of placing self_to_task after cpuset.cpus and cpuset.mems is important\
\
- case p: fill the settings related to pids cgroup and place in the next NULL inside cgroups**\
\
- case M: fill the settings related to pids cgroup and place in the next NULL inside cgroups**\
\
- case r: find the next NULL of blkio settings and place related settings there and replace cgroups[0] with the edited blkio cgroup\
\
- case w: find the next NULL of blkio settings and place related settings there and replace cgroups[0] with the edited blkio cgroup \
\
\
##################### Part2 Question 2 ############################\
\
- create the stack for the clone function and set the necessary flags for the \
\
\
##################### Part2 Question 3 ############################\
- set the child\'92s root to the new_root\
\
- 
\f1 \cf2 \cb3 \expnd0\expndtw0\kerning0
syscall\cf4 (SYS_pivot_root,new_root, put_old);\cb1 \
\
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0 \cf0 \kerning1\expnd0\expndtw0 ##################### Part2 Question 4 ############################\
- set up child capabilities\
\
- drop_caps is the caps we are selecting to drop\
\
- we drop the selected capabilities from the ambient set\
\
- clear the capabilities from the inheritable set\
\
- set the cleared set back to the process \
\
##################### Part2 Question 5 ############################\
- setup_syscall_filters\
\
- setup default behavior of filtering context\
\
- set filters on ptrace, mbind, migrate_pages, move_pages, unshare, clone, chmod - S_ISUID, chmod - S_ISGID\
\
\pard\pardeftab720\sl360\partightenfactor0

\f1 \cf5 \cb6 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \strokec5 //clone on CLONE_NEWUSER\cf7 \cb1 \strokec7 \
\cb6     \cf5 \strokec5 /*by definition of the manpage, clone's flags are it's 3 arg but according to Shabir's\cf7 \cb1 \strokec7 \
\cf5 \cb6 \strokec5     contact with the author of the libseccomp library, we may need to use SCMP_A0 with clone due\cf7 \cb1 \strokec7 \
\cf5 \cb6 \strokec5     to different architecture... odd*/\cf7 \cb1 \strokec7 \
\
\cb6 \'a0\'a0\'a0\'a0\cf5 \strokec5 /*filter_set_status = seccomp_rule_add(seccomp_ctx, SCMP_FAIL, SCMP_SYS(clone),\cf7 \cb1 \strokec7 \
\cf5 \cb6 \strokec5 \'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0 1, SCMP_A2(SCMP_CMP_MASKED_EQ, CLONE_NEWUSER, CLONE_NEWUSER) );*/\cf7 \cb1 \strokec7 \
\cb6     filter_set_status = \cf8 \strokec8 seccomp_rule_add\cf7 \strokec7 (seccomp_ctx, SCMP_FAIL, \cf8 \strokec8 SCMP_SYS\cf7 \strokec7 (clone),\cb1 \
\cb6 \'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0 \cf9 \strokec9 1\cf7 \strokec7 , \cf8 \strokec8 SCMP_A0\cf7 \strokec7 (SCMP_CMP_MASKED_EQ, CLONE_NEWUSER, CLONE_NEWUSER) );\cb1 \
\
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0 \cf0 \kerning1\expnd0\expndtw0 \outl0\strokewidth0 - Note that we initially set the filter on clone using SCMP_A2 but according to a small FB post Shabir (TA) mentioned that the\
 use of SCMP_A0 with clone may be due to architecture differences.\
\
\
##################### ADDITIONAL FILES ############################\
- memHog.c: tests our cgroup settings if it properly kills when it exceeds memory limit\
\
	NOTE: stalls when flags -r and -w were used to create the container\'85. so don\'92t use -r and/or -w when creating the container \
		if you are planning to run memHog.c\
\
- test_syscall.c: tests if our restrictions on the specific syscalls hold \'97 specifically tests chmod and clone\
\
##################### INTERESTING CASES ############################\
- for a period of time, we were unable to create a new docker container\
\
- another time, when we ran SNR_CONTAINER with bare minimum flags the program would stall at\
	
\f1 \cf10 \cb3 \expnd0\expndtw0\kerning0
if\cf4  (\cf2 execve\cf4 (config->\cf11 argv\cf4 [\cf12 0\cf4 ], config->\cf11 argv\cf4 , \cf13 NULL\cf4 ))\cb1 \
\pard\pardeftab720\sl360\partightenfactor0
\cf4 \cb3     \{\cb1 \
\cb3         \cf2 fprintf\cf4 (stderr, \cf14 "invocation to execve() failed! \cf15 %\cf14 m.\cf16 \\n\cf14 "\cf4 );\cb1 \
\cb3         \cf10 return\cf4  -\cf12 1\cf4 ;\
	\}\
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0 \cf0 \cb1 \kerning1\expnd0\expndtw0 - this situation we were not able to solve, but if you run into this problem, wait a bit of time and rerun the docker container as well as the program or try to create another docker container and follow the necessary steps. \
\

\f1 \cf4 \expnd0\expndtw0\kerning0
\
\pard\pardeftab720\sl360\partightenfactor0
\cf4 \
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0 \cf0 \kerning1\expnd0\expndtw0 \
 }