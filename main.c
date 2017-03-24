#include <stdio.h>
#include <limits.h>
#include <string.h>


void FCFS(char*); //Prints First Come First Serve Algorithm
void SSF(char*);  //Prints Shortest Seek First Algorithm

int main() {
    char S1[27] = "InputFiles/scheduling1.txt";
    char S2[27] = "InputFiles/scheduling2.txt";
    char S3[27] = "InputFiles/scheduling3.txt";

    int input;

    printf("Enter 1, 2, or 3 to run Scheduling on File 1, 2, or 3:");
    scanf("%d",&input);
    

    if(input==1){
        FCFS(S1);
        SSF(S1);
        return 0;
    }else if(input==2){
        FCFS(S2);
        SSF(S2);
        return 0;
    }else if(input==3){
        FCFS(S3);
        SSF(S3);
        return 0;
    }
    else{
        printf("Error - Incorrect input.");
        return 1;
    }
}
void FCFS(char* f){
    FILE *Sched;
    Sched = fopen(f,"r");// opens chosen file
    char buf[100];

    int pos = 11;      //initial position of disk arm
    int distance = 0;   //total distance arm travels

    printf("Running FCFS Scheduling\n");

    if(!Sched)
        return;

    fgets(buf,100,Sched);

    int num = buf[0] - '0';

    fgets(buf,100,Sched);

    fclose(Sched);

    char *token;
    token = strtok(buf,",");


    for(int i = 0; i < num; i++){

        int cyl;

        sscanf(token,"%d",&cyl);

        printf("Seeking cylinder %d\n",cyl);

        if(cyl>pos)
            distance+=cyl-pos;
        else
            distance+=pos-cyl;

        pos = cyl;

        token = strtok(NULL,",");
    }
    printf("FCFS Distance: %d\n\n",distance);
}
void SSF(char* f){
    FILE *Sched;
    Sched = fopen(f,"r");// opens chosen file
    char buf[100];

    int pos = 11;      //initial position of disk arm
    int distance = 0;   //total distance arm travels

    printf("Running SSF Scheduling\n");

    if(!Sched)
        return;

    fgets(buf,100,Sched);

    int num = buf[0] - '0';

    fgets(buf,100,Sched);

    fclose(Sched);

    char *token;
    token = strtok(buf,",");

    int cyl[num];

    for(int i = 0; i < num; i++){
        sscanf(token,"%d",&cyl[i]);
        token = strtok(NULL,",");
    }

    for(int i = 0; i < num; i++){
        int min = INT_MAX;
        int loc = 0;
        for(int p = 0; p < num; p++){
            if(cyl[p]<pos){
                if(pos-cyl[p]<min){
                    min = pos-cyl[p];
                    loc = p;
                }
            }
            else{
                if(cyl[p]-pos<min){
                    min = cyl[p]-pos;
                    loc = p;
                }
            }
        }
        printf("Seeking cylinder %d\n",cyl[loc]);
        if(cyl[loc]<pos)
            distance+=pos-cyl[loc];
        else
            distance+=cyl[loc]-pos;

        pos = cyl[loc];

        cyl[loc] = INT_MAX;
    }
    printf("SSF Distance: %d\n\n",distance);
}