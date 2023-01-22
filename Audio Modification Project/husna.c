#include <stdlib.h> // standard library (function involve memory allocation)
#include <unistd.h> // that provides access to the POSIX operating system 
#include <stdio.h> // stands for Standard Input Output
#include <errno.h> //some library functions in the event of an error to indicate what went wrong. 
#include <fcntl.h>
#include <sys/types.h> // file defines data types used in system source code. 
#include <string.h>
#include <sys/wait.h>

#define Size 1000000 // file almost size

int main(int argc, char **argv) // we use it here mean hum run karty waqt input dy rahy hai
{

	int File1,File2,Result_File;
	char Buff[Size]; // to store data of audio file
	int r,w; // not predefine

//	Opening File 1
	File1 = open(argv[1] ,O_RDWR); //O_RDWR is read write permission // argv[1] will open first file// pipe in dono ko communicate kar raha hai 
	printf("File 1 Opened \n");
	if(File1 < 0)            //if file not open file value become less than zero in negative and it give error
	{
		perror("Error in File 1 Opening: ");
		exit(0);
	}

//	Opening File 2
	File2 = open(argv[2] ,O_RDWR);  //O_RDWR is read write permission
	printf("File 2 Opened \n");
	if(File2 < 0)
	{
		perror("Error in File 2 Opening: ");   //if file not open file value become less than zero and it give error
		exit(0);
	}

//	Result File 

	Result_File = open(argv[3] ,O_RDWR| O_CREAT, S_IRWXU|S_IRWXG); // if file already not exit it will create // and if already exit then it does not create (o_TRUNC)
	printf("Resultant File Opened \n\n\n");

	if(Result_File < 0)
	{
		perror("Error in Result File: ");
	}

// 	Read from File 1

	while(1) // infinite jub tak koi condition ghalat na ho wo chalty jaye gy
	{
		r = read(File1,Buff,Size); // buffer us key andar music ko read kary ga
		printf("Data Read from File1 \n");
		
		if(r < 0) // agr data read nhe karta tou -1 a jaye ga
		{
			perror("Error in Reading from File 1: ");
		}


		w = write(Result_File,Buff,r);
		printf("Data write on resultant file from File1 \n\n\n");
	
		if(w < 0)
		{
			perror("Error in Writing from File 1: ");
		}

		printf("File 1 Total Bytes: %d \n",r); // %d mean integer play karwa rahy hai

		if(r == 0)// no data exist 
		{
			printf("All Data Read from File1 \n\n");
			break;
		}
	}

		// Clear Buffer // buffer clear kar ly gy phr us mei dusre file key data store kary gy
		memset(Buff,0,Size); // buffer empty ho jata hai
		printf("File1 data is clear from Buffer\n");

		// Write new contents at the of Result file
		lseek(Result_File,0,SEEK_END);   // (jo pehly file copy huy )move cursor at the end of resultant file for writing new data

//	Reading from File 2 

	while(1)
	{
		r = read(File2,Buff,Size);
		printf("Data Read from File2 \n");

		if(r < 0) // file open karty hai magr us mei koi data hai he nhe
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

		if(r == 0) //reading key leay open ho gahe magr data zero hai
		{
			printf("All Data Read from File2 \n\n");
			break;
		}
	}
	
	return 0;
}
