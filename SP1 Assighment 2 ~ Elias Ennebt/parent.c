#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int Child1();
void Child2(int argc, char const *argv[]);
void replaceAll(char *str, const char *oldWord, const char *newWord);
void Child3(int argc, char const *argv[]);




#define BUFFER_SIZE 256



int main(int argc, char const *argv[])
{
    int pid, pid1, pid2;

    if( argc == 3 ) {
        printf("The Files suplied are  %s, %s \n", argv[1], argv[2]);
    }
    else if( argc > 3 ) {
        printf("Too many arguments supplied.\n");
        exit(1);
    }
    else {
        printf(" 2  files expected .\n");
        exit(1);
    }






    pid = fork();
    if(pid < 0){
        printf(" \n Child[1], could not create a proccess \n ");
        exit(1);

    }
    else if (pid == 0) {
        printf("child[1] --> pid = %d and ppid = %d\n", getpid(), getppid());
        Child1();
        exit(0);
    }

    else {
        pid1 = fork();
        if(pid1 < 0){
            printf(" \n Child[2], could not create a proccess \n");
            exit(1);

        }
        else if (pid1 == 0) {
            printf("child[2] --> pid = %d and ppid = %d \n",getpid(), getppid());
            Child2(argc, argv);
            exit(0);
        }
        else {

            pid2 = fork();
            if(pid2 < 0){
                printf("\n Child[3] process could not be created \n");
                exit(1);
            }
            else  if (pid2 == 0) {
                printf("child[3] --> pid = %d and ppid = %d \n", getpid(), getppid());
                Child3(argc, argv);
                exit(0);
            }
            else {
                int returnStatus;
                int returnStatus1;
                int returnStatus2;
                waitpid(pid, &returnStatus, 0);
                waitpid(pid2, &returnStatus1, 0);
                waitpid(pid1, &returnStatus2, 0);

                if (returnStatus == 0)
                {
                    printf(" \n The Parent process  terminated normally exit status for \n Child 1 = %d , Child 2 = %d, Child 3 = %d ", &returnStatus, &returnStatus1, &returnStatus2);
                }

                if (returnStatus == 1)
                {
                    printf(" \n The Parent process terminated with an error!  exit status for \n Child 1 = %d , Child 2 = %d, Child 3 = %d ", &returnStatus, &returnStatus1, &returnStatus2);
                }

            }
        }
    }


    return 0;
}


int Child1() {

    int i, n, sum = 0, j;
    float avg;
    int big;
    big = 0;
    int small;
    small = 0;    
    j = 10;
    
for(i = 0; i < j;--j){
        printf("\n ENTER %d Grades  \n", j);
        scanf("%d", &n);
        sum+=n;

        if(n > big){
            big = n;
        }
        if((n < small) || (small == 0)){
            small = n;
        }


    }
    avg = sum/10.0;
    printf("The sum of 10 no is : %d \n The Average Grade is : %f \n",sum,avg);
    printf("The Highest Grade was  =  %d , The lowest grade was =  %d ",big,small);
}

void Child2(int argc, char const *argv[]){

 char* args[] = {"wc", "-w",argv[1],NULL};
    execv("/usr/bin/wc",args);
    printf("is the word count of afile "); 
    exit(0);

}
void Child3(int argc, char const *argv[]){
    FILE *fr;
    FILE * fr1;
    char buffer[BUFFER_SIZE];
    fr = fopen(argv[1], "r");

    fr1 = fopen(argv[2], "w");
    fprintf(fr1, "UPDATE VERSION OF FILE ");

    while((fgets(buffer,BUFFER_SIZE,fr)) != NULL)
    {
        replaceAll(buffer,"execute","run");
        replaceAll(buffer,"study","examine");

        fputs(buffer,fr1);
    }

    printf("\n CONTENTS COPIED AND UPDATED  %s  \n ", argv[2]);
    fclose(fr);
    fclose(fr1);

    exit(1);
}


void replaceAll(char *str, const char *oldWord, const char *newWord)
{
    char *pos, temp[BUFFER_SIZE];
    int index = 0;
    int OWLength;

    OWLength = strlen(oldWord);

    while ((pos = strstr(str, oldWord)) != NULL)
    {
        strcpy(temp, str);
        index = pos - str;
        str[index] = '\0';
        strcat(str, newWord);
        strcat(str, temp + index + OWLength);
    }
}
