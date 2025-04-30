#include <stdio.h>
#include <stdlib.h>
#include <spawn.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define N 12

extern char **environ;

char *allowed[N] = {"cp","touch","mkdir","ls","pwd","cat","grep","chmod","diff","cd","exit","help"};

int isAllowed(const char*cmd) {
	// TODO
	// return 1 if cmd is one of the allowed commands
	// return 0 otherwise
	char* temp = malloc(strlen(cmd));
	strcpy(temp, cmd);
	for(int i = 0; i < 12; i++){
		if (strcmp(strtok(temp, " "), allowed[i]) == 0) {
			return 1;
		}
	}
	
	return 0;
}

int main() {

    // TODO
    // Add variables as needed

    char line[256];

    while (1) {

	fprintf(stderr,"rsh>");

	if (fgets(line,256,stdin)==NULL) continue;

	if (strcmp(line,"\n")==0) continue;

	line[strlen(line)-1]='\0';

	// TODO
	// Add code to spawn processes for the first 9 commands
	// And add code to execute cd, exit, help commands
	// Use the example provided in myspawn.c

	if(isAllowed(line) == 0){
		printf("NOT ALLOWED!\n");
	}

	char* arg0 = strtok(line, " ");
	char *args[13];
	size_t num_in_arr = 1;
	args[0] = arg0;

	while ((args[num_in_arr] = strtok(NULL, " ")) != NULL) {
		num_in_arr++;
	}

	if(strcmp(arg0, "cd") == 0){
		if(args[2] != NULL){
			printf("-rsh: cd: too many arguments");
		}else{
			chdir(args[1]);
		}
	}else if(strcmp(arg0, "exit") == 0){
		return 0;
	}else if(strcmp(arg0, "help") == 0){
		printf("1: cp\n2: touch\n3: mkdir\n4: ls\n5: pwd\n6: cat\n7: grep\n8: chmod\n9: diff\n10: cd\n11: exit\n12: help\n");
	}else{
		posix_spawnattr_t attr;
    	posix_spawnattr_init(&attr);

		pid_t pid;
		int status = posix_spawnp(&pid, arg0, NULL, NULL, args, environ);
		waitpid(pid, &status, 0);

		posix_spawnattr_destroy(&attr);
	}
}

    return 0;
}
