/*
 * simple-ls.c
 * Extremely low-power ls clone.
 * ./simple-ls .
 */

#include <sys/types.h>

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

#define BUFFSIZE 32768


int
main(int argc, char **argv) {

	DIR *dp;
	struct dirent *dirp;
        char *arg[64];

	if (argc != 2) {
		fprintf(stderr, "usage: %s dir_name\n", argv[0]);
		exit(1);
	}

	if ((dp = opendir(argv[1])) == NULL ) {
		fprintf(stderr, "can't open '%s'\n", argv[1]);
		exit(1);
	}

	while ((dirp = readdir(dp)) != NULL ){
		pid_t pid;
		int status;
                char *name = dirp->d_name;
                printf("%s\n",name);
                if(name[strlen(name)-2]=='.' && name[strlen(name)-1]=='c'){
			int n;
			char buf[BUFFSIZE];	
                        int file = open(name,O_RDONLY);
			printf("####Start of the file: %s #### \n\n", name);
			while ((n = read(file, buf, BUFFSIZE)) > 0) {
				if (write(STDOUT_FILENO, buf, n) != n) {
				fprintf(stderr, "write error\n");
				exit(1);
				}
			}
			printf("####End of the file: %s #### \n\n", name);
			if (n < 0) {
				fprintf(stderr, "read error\n");
				exit(1);
				}

                } 
		
	}

	closedir(dp);
	return(0);
}


