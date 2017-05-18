/**
  * SO, 2016
  * Lab #12
  *
  * Task 01 - mini.c
  * Implementing a minimal comand line file utility
  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
  #include <dirent.h>

#include "utils.h"

#define MAX_LINE_SIZE		256

const char *delim = " \t\n";
char *prompt = "so-lab12";

#define TODO2
#define TODO3
#define TODO4
#define TODO5
#define TODO6
#define TODO7

int main(void)
{
	char line[MAX_LINE_SIZE];
	char *cmd, *arg1, *arg2, *arg3;
	int ret; /* to be used for function calls return code */

	while (1) {
		printf("<%s>", prompt);
		fflush(stdout);

		memset(line, 0, MAX_LINE_SIZE);

		if (fgets(line, sizeof(line), stdin) == NULL)
			exit(EXIT_SUCCESS);

		cmd = strtok(line, delim);
#ifdef DEBUG
		printf("Executing command: %s\n", cmd);
#endif
		if (strncmp(cmd, "quit", 4) == 0)
			break;
#ifdef TODO2
		/* TODO2: implement list <device_node>
		 * Output: <c|b> <major>:<minor>
		 * e.g: list /dev/zero
		 * Output: /dev/zero: <c> 1:5
		 */
		 struct stat ident;
		 int rc;
		 int minor, major;
		if (strncmp(cmd, "list", 4) == 0) {
			arg1 = strtok(NULL, delim); /* device_node name */
			if (!arg1)
				continue;
			rc = stat(arg1, &ident);
			minor = ident.st_rdev;
			major = ident.st_rdev;
			int type = S_ISDIR(ident.st_mode);
			if(type > 0){
				printf("%s: <%c> %d:%d\n",
			       arg1, 'c', minor, major);

			}
			else if(type == 0){
				printf("%s: <%c> %d:%d\n",
			       arg1, 'b', minor, major);

			}
			else
				return 0;
			
		}
#endif

#ifdef TODO3
		/* TODO3: implement mount source target fs_type
		 * e.g: mount /dev/sda1 /mnt/disk2 ext3
		 */
		
		if (strncmp(cmd, "mount", 5) == 0) {
			arg1 = strtok(NULL, delim); /* source */
			arg2 = strtok(NULL, delim); /* target */
			arg3 = strtok(NULL, delim);/* fs_type (e.g: ext2) */

			rc = mount(arg1, arg2,
                 arg3, 0,
                 NULL);
			DIE(rc, "ERR");

		}
		if (strncmp(cmd, "umount", 6) == 0) {
			/* TODO3: implement umount */
			arg1 = strtok(NULL, delim); /* target */
			rc = umount(arg1);
			DIE(rc, "ERR");
		}
#endif

#ifdef TODO4
		/* TODO4: implement symlink oldpath newpath
		 * e.g: symlink a.txt b.txt
		 */
		if (strncmp(cmd, "symlink", 7) == 0) {
			arg1 = strtok(NULL, delim); /* oldpath */
			arg2 = strtok(NULL, delim); /* newpath */
			symlink(arg1, arg2);
		}

		
		if (strncmp(cmd, "unlink", 6) == 0) {
			/* TODO4: implement unlink */
			arg1 = strtok(NULL, delim); /* pathname */
			unlink(arg2); 
		}
#endif

#ifdef TODO5
		/* TODO5: implement mkdir pathname mode
		 * e.g: mkdir food 0777
		 */
		if (strncmp(cmd, "mkdir", 5) == 0) {
			arg1 = strtok(NULL, delim); /* pathname */
			arg2 = strtok(NULL, delim); /* mode */
			mkdir(arg1, arg2);
		}
		if (strncmp(cmd, "rmdir", 5) == 0) {
			/* TODO5: implement rmdir pathname */
			arg1 = strtok(NULL, delim); /* pathname */
			rmdir(arg1);
		}
#endif

#ifdef TODO6

		/* TODO6: implement ls dirname */
		if (strncmp(cmd, "ls", 2) == 0) {
			DIR *dirp;
			int level = 0, i;
			struct dirent *de;
			/* Recursively print files starting with arg1 */
			arg1 = strtok(NULL, delim);
recursive:
			level++;
			dirp = opendir(arg1);	
			DIE(dirp == NULL, "dirname");

			printf("-- Reading directory %s\n\n", arg1);

			while (1) {

				de = readdir(dirp);
				if (de == NULL)
					break;
				else if( opendir(arg1) == 0){

					goto recursive;
				}
				printf("	%s \n", de->d_name);
				
				}
			}
#endif


#ifdef TODO7
		if (strncmp(cmd, "chdir", 5) == 0) {
			/* TODO7: implement chdir <dir>
			 * e.g: chdir bar
			 */
			arg1 = strtok(NULL, delim); /* pathname */
			rc = chdir(arg1);
			DIE(rc, "ERROR:");
		}

		if (strncmp(cmd, "pwd", 3) == 0) {
			/* TODO7: implement pwdir
			 * e.g: pwd
			 */
			/* print workding directory */
			 
			 //printf(getcwd(buf,BUFSIZ));
		}
#endif
	}

	return 0;
}
