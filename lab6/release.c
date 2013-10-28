/*********************************************************************/
/* Cody Gildea 008933663 CECS 326                                    */
/* PROGRAM: release.c                                                */
/* DESCRIPTION: This program demonstrates the use of locks when	     */ 
/* running multiple processes. 			                     */
/*********************************************************************/
# include<sys/types.h>
# include<sys/stat.h>
# include<fcntl.h>
# include<stdio.h>
# include<stdlib.h>
# include<errno.h>

void main(int argc, char *argv[])
{
	char *fname;
	int fd, sleeptime, n_try, count = 0;
	pid_t pid;
	if (argc != 4) // If arguments are not 4 inputs
        {
                printf("Invalid inputs, requires 4 arguments.\n", argv[0]);
                exit(1);
        }
	pid = getpid();
	srand((unsigned)pid);
	fname = argv[1];
	sleeptime = atoi(argv[2]);
	n_try = atoi(argv[3]);

	if (sleeptime <= 0)   // If argument sleeptime is less than or equal to 0, throw exception
        {
                printf("Input error.\n");
                printf("Sleeptime must be > 0\n");
                exit(1);
        }
	if (n_try <= 0)   // If argument n_try is less than or equal to 0, throw exception
        {
                printf("Input error.\n");
                printf("Number of tries must be > 0\n");
                exit(1);
        }
	while (unlink(fname) != 0)
		if(++count < n_try) 
			sleep(sleeptime);
		else 
		{
			printf("\nCannot release file\n");
			exit(-1);
		}
		printf("\nFile is released\n");
}