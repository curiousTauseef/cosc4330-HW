#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/wait.h>
#include <sys/types.h>
#include <sys/shm.h>
#include<stdlib.h>
#include<iostream>

#define EXIT_FAILURE -1
using namespace std;

struct stat_result
{
	double conn_rate;
	double conn_time;
	double reply_rate;
	double reply_time;
	double net_io;
};

int main2()
{
	int i;
	pid_t pid;
	int status;
	void *share_memory=(void *)0;
	struct stat_result *result;
	int shmid;

	if((shmid=shmget((key_t)1234,sizeof(struct stat_result),0666 | IPC_CREAT))==-1)
	{
		perror("shmget failed!");
		exit(EXIT_FAILURE);
	}

	if((share_memory=shmat(shmid,(void *)0,0))==(void *)-1)
	{
		perror("shmat failed!");
		exit(EXIT_FAILURE);
	}

	cout<<"the memory is "<<share_memory<<endl;

	result=(struct stat_result *)share_memory;

	result->conn_rate=0.0;
	result->conn_time=0.0;
	result->reply_time=0.0;
	result->reply_rate=0.0;
	result->net_io=0.0;

	for(i=0;i<3;i++)
	{
		if((pid=fork())==0)
		{
			if((shmid=shmget((key_t)1234,sizeof(struct stat_result),0666 | IPC_CREAT))==-1)
			{
				perror("shmget failed!");
				exit(EXIT_FAILURE);
			}

			if((share_memory=shmat(shmid,(void *)0,0))==(void *)-1)
			{
				perror("shmat failed!");
				exit(EXIT_FAILURE);
			}

			result=(struct stat_result *)share_memory;

			result->conn_rate+=1.0;
			result->conn_time+=2.0;
			result->reply_time+=3.0;
			result->reply_rate+=4.0;
			result->net_io+=5.0;

			if(shmdt(share_memory)==-1)
			{
				perror("shmdt failed!");
				exit(EXIT_FAILURE);
			}

			exit(0);
		}
	}

	for(i=0;i<3;i++)
	{
		pid=wait(&status);

		printf("conn_rate: %f conn_time: %f reply_time: %f reply_rate: %f net_io: %f ",result->conn_rate,result->conn_time,result->reply_time,result->reply_rate,result->net_io);
	}

	if(shmdt(share_memory)==-1)
	{
		perror("shmdt failed!");
		exit(EXIT_FAILURE);
	}

	if(shmctl(shmid,IPC_RMID,0)==-1)
	{
		perror("shmctl(IPC_RMID) failed!");
		exit(EXIT_FAILURE);
	}
	exit(0);
}
