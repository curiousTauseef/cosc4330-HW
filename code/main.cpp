#include<stdio.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<stdlib.h>
int mysem;
#define KEY 1195965

int get_sem(int i){
	short semarr[30];
	union semnu{
		int val;
		struct semid_ds *buf;
		short * array;
	} arg;

	arg.array = semarr;
	semctl(mysem, i, GETALL, arg);
	return semarr[i];
}

void show_sem(int i){
	int val;
	val = get_sem(i);
	printf("semaphore [%d] = [%d]\n", i, val);
}

void create_sem(int N){
	printf("Create %d semapores \n", N);
	mysem = semget(KEY, N, 0666|IPC_CREAT);
	printf("mysem = %d\n", mysem);
	if(mysem <0){
		//error_msg();
		printf("Error in create semaphore \n");
		exit(0);
	}
}

void init_sem(int N){
	int j;
	int retval;
	union semun{
		int val;
		struct semid_ds *buf;
		short * array;
	} arg;

	arg.val = 1;
	for (j=0; j<N; j++)
	{
		retval = semctl(mysem, j, SETVAL, arg);
		if(retval <0){
			printf("Error in create semaphore \n");
			exit(0);
		}

		show_sem(j);
	}

}

void PV(int i, int act){
	struct sembuf op;
	int retval;
	op.sem_num = i;
	op.sem_op = act;
	op.sem_flg = 0;
	retval = semop(mysem, &op, 1);
	if(retval != 0)
	{
		printf("Error in create semaphore \n");
		exit(0);
	}
		//error2("Error: semop: ", act);
	show_sem(i);
}

void P(int i){
	PV(i, -1);
}

void V(int i)
{
	PV(i, 1);
}


int main(int argc, char * argv[]){
	int RoomNUmebr = 10;
	//some problem here, should try pon real linux mechine
	//create_sem(RoomNUmebr);
	//
	//Step 1:read the action file input herer!!!
	

	//Step 2: create the semaphore
	int custom_num = 10;
	//Step 3: create child processes
	int custom_id = -1;
	for(int i=0; i<custom_num; ++i){
		int pid = fork();
		if(pid <0){
			printf("Error to fork!!\n");
			exit(1);
		}
		if(pid == 0){
			custom_id = pid;
			break;
		}
	}


	if(custom_id <0){
		//code for main process
	}

	else{
		for(int custom_index = 0; custom_index <custom_num; ++custom_index)
			if(custom_index = custom_id)
			{
				//do some thing in the input file
			}
	
	}





	return 0;
}



