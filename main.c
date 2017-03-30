#include <stdio.h>
#include <limits.h>
#include <string.h>
/*
 * First Come First Serve and Shortest Seek First Disk Algorithm's
 * Domenic Perriccioli
 * v1.0 - 03/23/2017
 * C99 Standard
 */

void FCFS(char*); //Prints First Come First Serve Algorithm
void SSF(char*);  //Prints Shortest Seek First Algorithm

int main(int argc,char* argv[]) {
    char* file;

    if(argc > 1){
        file = argv[1];
    }else{
        return 0;
    }

    FCFS(file);
    SSF(file);

    return 0;
}
void FCFS(char* f){//first come first serve algorithm
    FILE *Sched;
    Sched = fopen(f,"r");// opens chosen file
    char buf[100];      //char array for file contents

    int pos = 11;      //initial position of disk arm
    int distance = 0;   //total distance arm travels

    printf("\nRunning FCFS Scheduling\n");

    if(!Sched){//if no file end
        printf("Error - File not found.\n");
    }

    fgets(buf,100,Sched);   //read first line - number of cylinder to read

    int num;
    sscanf(buf,"%d",&num);  //convert buffer to int

    fgets(buf,100,Sched);   //read next line - cylinders to read

    fclose(Sched);  //close file

    char *token;    //token to delimit cylinders
    token = strtok(buf,",");    //get first cylinder


    for(int i = 0; i < num; i++){   //scan and print cylinders

        int cyl;    //int for cylinder

        sscanf(token,"%d",&cyl);    //convert token to int

        printf("Seeking cylinder %d\n",cyl);    //print cylinder being seek

        if(cyl>pos) //add to distance tally for arm distance
            distance+=cyl-pos;
        else
            distance+=pos-cyl;

        pos = cyl;  //position of arm is at current cylinder

        token = strtok(NULL,",");   //get next cylinder
    }
    printf("FCFS Distance: %d\n\n",distance);   //print total distance moved
}
void SSF(char* f){
    FILE *Sched;
    Sched = fopen(f,"r");// opens chosen file
    char buf[100];

    int pos = 11;      //initial position of disk arm
    int distance = 0;   //total distance arm travels

    printf("Running SSF Scheduling\n");

    if(!Sched){//if no file end
        printf("Error - File not found.\n");
    }

    fgets(buf,100,Sched);   //get first line

    int num;
    sscanf(buf,"%d",&num);  //convert buffer to int

    fgets(buf,100,Sched);   //read next line - cylinders to read

    fclose(Sched);  //close file

    char *token;    //token to delimit cylinders
    token = strtok(buf,",");    //get first cylinder

    int cyl[num];   //array for number of cylinders

    for(int i = 0; i < num; i++){   //fill the array with the cylinders to seek
        sscanf(token,"%d",&cyl[i]); //convert token to int
        token = strtok(NULL,",");   //get next token
    }

    for(int i = 0; i < num; i++){   //print the cylinders in Shortest Seek First order
        int min = INT_MAX;  //minimum seek from arm is initially max
        int loc = 0;        //location of shortest seek
        for(int p = 0; p < num; p++){   //scan the cylinders to find closest one
            if(cyl[p]<pos){ //if cylinder is lower than the position
                if(pos-cyl[p]<min){ //if the distance from position to cylinder is lower than min
                    min = pos-cyl[p];//set this cylinder as the next one to seek
                    loc = p;
                }
            }
            else{
                if(cyl[p]-pos<min){//if the distance from position to cylinder is lower than min
                    min = cyl[p]-pos;//set this cylinder as the next one to seek
                    loc = p;
                }
            }
        }
        printf("Seeking cylinder %d\n",cyl[loc]);
        if(cyl[loc]<pos)//add to the tally of distance arm travels
            distance+=pos-cyl[loc];
        else
            distance+=cyl[loc]-pos;

        pos = cyl[loc];//set position of arm to current cylinder

        cyl[loc] = INT_MAX;//set the current cylinder to read
    }
    printf("SSF Distance: %d\n\n",distance);//print total distance
}