#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

#define Size 1000000

int main(int argc, char **argv)
{

	int File1,File2,Result_File;
	char Buff[Size];
	int r,w;

//	Opening File 1
	File1 = open(argv[1] ,O_RDWR); //O_RDWR is read write permission
	printf("File 1 Opened \n");
	if(File1 < 0)            
	{
		perror("Error in File 1 Opening: ");
		exit(0);
	}

//	Opening File 2
	File2 = open(argv[2] ,O_RDWR);  
	printf("File 2 Opened \n");
	if(File2 < 0)
	{
		perror("Error in File 2 Opening: "); 
		exit(0);
	}

//	Result File 

	Result_File = open(argv[3] ,O_RDWR| O_CREAT, S_IRWXU|S_IRWXG);
	printf("Resultant File Opened \n\n\n");

	if(Result_File < 0)
	{
		perror("Error in Result File: ");
	}

// 	Read from File 1

	while(1)
	{
		r = read(File1,Buff,Size);
		printf("Data Read from File1 \n");
		
		if(r < 0)
		{
			perror("Error in Reading from File 1: ");
		}


		w = write(Result_File,Buff,r);
		printf("Data write on resultant file from File1 \n\n\n");
	
		if(w < 0)
		{
			perror("Error in Writing from File 1: ");
		}

		printf("File 1 Total Bytes: %d \n",r);

		if(r == 0)
		{
			printf("All Data Read from File1 \n\n");
			break;
		}
	}

		// Clear Buffer
		memset(Buff,0,Size);
		printf("File1 data is clear from Buffer\n");

		// Write new contents at the of Result file
		lseek(Result_File,0,SEEK_END);   

//	Reading from File 2

	while(1)
	{
		r = read(File2,Buff,Size);
		printf("Data Read from File2 \n");

		if(r < 0)
		{
			perror("Error in Reading from File 1: ");
		}

		w = write(Result_File,Buff,r);
		printf("Data  write on resultant file from File2 \n\n\n");
	
		if(w < 0)
		{
			perror("Error in Writing from File 1: ");
		}

		printf("File 2 Total Bytes: %d \n",r);

		if(r == 0)
		{
			printf("All Data Read from File2 \n\n");
			break;
		}
	}
	
	return 0;
}
