/**************************************************************************/ 
/* PROGRAM NAME: proj5.c                                                  */
/* CLASS:        CECS-326                                                 */
/* INSTRUCTOR:   Mr. Haney Williams                                       */
/* STUDENTS:     Cody Gildea                                              */
/*               Steven Le                                                */
/* DESCRIPTION: This program utilizes creating and removing semaphores	  */
/**************************************************************************/ 
# include <stdio.h> 
# include <sys/types.h> 
# include <sys/ipc.h> 
# include <sys/sem.h> 
# include <unistd.h> 
# include <stdlib.h> 
# include <time.h>
 
 
void set_sembuf_struct(struct sembuf *s, int semnum, int semop, int semflg);

int main(int argc, char *argv[]) 
{ 
	pid_t pid, ppid, childpid;                 		  // For child process
	int sem_id, sem_value, i, j;	// Semaphore ID, Semaphore value, i and j for for statement
	int N, opt, k;
	key_t ipc_key; 						// Key for Semaphore
	struct semid_ds sem_buf;			// Allows access for Semaphore set and reference to the array of type sem 			
	union semun arg; 

	int sem_init(sem_t *sem, semflg, sem_value);


	struct sembuf semwait[1]; 
 	struct sembuf semsignal[1];

 	/* Initialize semaphore element to 1 */ 
 	set_sembuf_struct(semwait, 0, -1, 0); 
 	set_sembuf_struct(semsignal, 0, 1, 0); 


	ipc_key = ftok(".", 'S'); 			// Generate a key from a pathname

	/* Check input arguments are 4 */
	if (argc != 4)
	{
		printf("Invalid input.  The number of arguments must be 4.\n");
		exit(1);
	}
	/* Create semaphore */ 
	if (strcmp(argv[2], "n") == 0) 		
	{
		childpid = 0;
		for(i = 1; i < N; ++i)
			if((childpid = fork()) == 0) break;
			printf("\ni: %d: process ID: %6ld parent ID: %6ld child ID: %6ld",i,(long)getpid(),
                	(long)getppid(), (long)childpid);
 	}
 	else if (strcmp(argv[2], "s") == 0)
 	{
 		while (( (semop_ret = semop(semid, semwait, 1) ) == -1) && (errno ==EINTR)); 
		if (semop_ret == -1) 
		printf ("%ld: semaphore decrement failed - %s\n", (long)getpid(), strerror(errno)); 
		else
	 		childpid = 0;
			for(i = 1; i < N; ++i)
				if((childpid = fork()) == 0) break;
				printf("\ni: %d: process ID: %6ld parent ID: %6ld child ID: %6ld",i,(long)getpid(),
	                	(long)getppid(), (long)childpid);
		while (((semop_ret = semop(semid, semsignal, 1)) == -1) && (errno == EINTR)); 
 		if (semop_ret == -1) 
 			printf ("%ld: semaphore increment failed - %s\n", (long)getpid(), strerror(errno)); 

 	}
 	/* Throw error if 2nd argument is not 'r' or 'n' */
 	else
	{
		printf("Invalid input for the second argument. %s should be 'n' or 's'.\n", argv[1]);
		exit(1);
	}
  exit(0);
} 
void set_sembuf_struct(struct sembuf *s, int num, int op, int flg) 
 { 
 	s *sem_num = (short) num; 
 	s *sem_op = op; 
	s *sem_flg = flg; 
 	return; 
 };
