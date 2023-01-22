#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>

#define Size 1000000

int main(int argc, char **argv)
{
    // Checking for command line argument 
    // it must be equals to 4 1(program file name) 2 3 4(mp3,mp3,output)
    if(argc != 4){
        printf("\nError: %s required argument [File1.mp3] [File2.mp3] [output.mp3]\n\n",argv[0]);
		exit(EXIT_FAILURE);
    }

	int File1,File2,Result_File;
	char Buff[Size];
	int r,w;

    unlink(argv[3]);   // Delete out file if Exist

//	Opening File 1

	File1 = open(argv[1] , O_RDONLY);

	if(File1 < 0)
	{
		perror("Error in File 1 Opening: ");
        exit(EXIT_FAILURE);
	}

//	Opening File 2

	File2 = open(argv[2] ,O_RDONLY);

	if(File2 < 0)
	{
		perror("Error in File 2 Opening: ");
        exit(EXIT_FAILURE);
	}

//	Result File 

	Result_File = open(argv[3] ,O_WRONLY | O_CREAT,S_IRWXU | S_IRWXG);

	if(Result_File < 0)
	{
		perror("Error in Result File: ");
	}

// 	Read from File 1

	while((r = read(File1,Buff,Size))>0){
		
		if(r < 0)
		{
			perror("Error in Reading from File 1: ");
		}


		w = write(Result_File,Buff,r);
	
		if(w < 0)
		{
			perror("Error in Writing from File 1: ");
		}

		printf("File 1 Total Bytes: %d\n",r);

		if(r == 0)
		{
			break;
		}
	}

		// Clear Buffer
		memset(Buff,0,Size);

		// Write new contents at the of Result file
		lseek(Result_File,0,SEEK_END);

        close(Result_File); //close the output file
    
    // OPEN result file and append data
    Result_File = open(argv[3] ,O_WRONLY | O_APPEND,S_IRWXU | S_IRWXG);

//	Reading from File 2

	while((r = read(File2,Buff,Size))>0)
	{
		
		if(r < 0)
		{
			perror("Error in Reading from File 1: ");
		}

		w = write(Result_File,Buff,r);
	
		if(w < 0)
		{
			perror("Error in Writing from File 1: ");
		}

		printf("File 2 Total Bytes: %d\n",r);

		if(r == 0)
		{
			break;
		}
	}
    close(Result_File);
    close(File1);
    close(File2);
    printf("\nWant to play music?[y/n]\n");
    char choice;
    scanf("%s",&choice);
    while (choice!='n' || choice!='N' || choice!='q' || choice!='Q'){
        printf("\n\t<<<<<<<<<<*************>>>>>>>>>>>\n");
        printf("\ta.   Play %s\n",argv[1]);
        printf("\tb.   Play %s\n",argv[2]);
        printf("\tc.   Play %s\n",argv[3]);
        printf("\tq.   Quit\n");
        printf("\n\t<<<<<<<<<<*************>>>>>>>>>>>\n");
        printf("Enter Choice : ");
        scanf("%s",&choice);
        if(choice=='a' || choice=='A'){
            int x=fork();
            if(x==0)
                execlp("play","play",argv[1],NULL);
            else{
                printf("\n\n\t<<<<<<<<<<Enter ' s ' to stop Music : >>>>>>>>>>\n\n");
                scanf("%s",&choice);
                if(choice=='s' || choice=='S'){
                    kill(x,SIGKILL);
                }
                wait(NULL);
            }
        }
        if(choice=='b' || choice=='B'){
            int x=fork();
            if(x==0)
                execlp("play","play",argv[2],NULL);
            else{
                printf("\n\n\t<<<<<<<<<<Enter ' s ' to stop Music : >>>>>>>>>>\n\n");
                scanf("%s",&choice);
                if(choice=='s' || choice=='S'){
                    kill(x,SIGKILL);
                }
                wait(NULL);
            }
        }
        if(choice=='c' || choice=='C'){
            int x=fork();
            if(x==0)
                execlp("play","play",argv[2],NULL);
            else{
                printf("\n\n\t<<<<<<<<<<Enter ' s ' to stop Music : >>>>>>>>>>\n\n");
                scanf("%s",&choice);
                if(choice=='s' || choice=='S'){
                    kill(x,SIGKILL);
                }
                wait(NULL);
            }
        }
        if(choice=='q' || choice=='Q'){
            break;
        }
        return 0;
    }
    

	return 0;
}