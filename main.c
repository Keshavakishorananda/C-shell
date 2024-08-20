#include "headers.h"
#include "prompt.c"
#include "excute.c"
#include "special2.c"
#include "special3.c"
#include "special4.c"
#include "special5.c"
#include "special6.c"
#include "special7.c"
#include "special8.c"
#include "construct.c"

int main()
{
    // Keep accepting commands
    char directory[4096] = "";
    char previous[4096];
    getcwd(directory,4096);
    getcwd(previous, 4096);
    char home[200];
    getcwd(home, 200);
    char tempdirectory[4096];
    strcpy(tempdirectory,directory);

    FILE* tempast = fopen("pastfile.txt","a");
    FILE* backup = tempast;
    if(tempast==NULL)
    {
        tempast = fopen("pastfile.txt","w");
        backup = tempast;
        fclose(tempast);
    }
    else
    {
        fclose(tempast);
    }

    
    char** commandstore;
    commandstore = (char**)malloc(sizeof(char*)*15);
    for(int i=0;i<15;i++)
    {
        commandstore[i] = (char*)malloc(100);
    }
    int startindex = 0;
    int* pointstart;
    pointstart = &startindex;

    int endindex = -1;
    int* pointend;
    pointend = &endindex;

    int elements = 0;
    int* pointelem;
    pointelem = &elements;

    char open[4096];
    strcpy(open,home);
    strcat(open,"/");
    strcat(open,"pastfile.txt");

    // Regarding pastevents
    FILE* past = fopen(open,"r");
    past = backup;
    if(past==NULL)
    {
        printf("file is not opened\n");
    }

    char line[100];
    int point = 0;
    while (fgets(line, sizeof(line), past) != NULL) 
    {
        strcpy(commandstore[point],line);
        point++;
    }
    fclose(past);
    elements = point;
    endindex = point-1;

    int signal = 0;
    int* pointsignal;
    pointsignal = &signal;


    while(1)
    {   

        // Print appropriate prompt with username, systemname and directory before accepting input
        // if(signal==1)
        // {
        //     printf("%s\n", directory);
        //     signal=0;
        // }
        prompt(home,directory);

        char input[4096];
        fgets(input, 4096, stdin);

        // Tokenisation
        char** commands;
        commands = (char**)malloc(sizeof(char*)*10);
        int* number;
        int i = 0;
        number = &i;
        special2(input,commands,number);

        char dupcomm[100];
        strcpy(dupcomm,commands[0]);

        char* dupstr = strtok(dupcomm," ");
        dupstr = strtok(NULL," ");

        if(dupstr==NULL)
        {
            if(strcmp(input,"pastevents\n")!=0 && strcmp(input,"pastevents purge\n")!=0)
            {
                endindex = (endindex+1)%15;
                if(endindex!=0 && strcmp(commandstore[endindex-1],input)!=0)
                {
                    strcpy(commandstore[endindex],input);
                    if(elements<15)
                    {
                        elements++;
                    }
                    if(endindex==startindex && elements==15)
                    {
                        startindex = (startindex+1)%15;
                    }
                }
                else if(endindex==0 && elements==15 && strcmp(commandstore[14],input)!=0)
                {
                    strcpy(commandstore[endindex],input);
                    if(elements<15)
                    {
                        elements++;
                    }
                    if(endindex==startindex && elements==15)
                    {
                        startindex = (startindex+1)%15;
                    }
                }
                else if(endindex==0 && elements==0)
                {
                    strcpy(commandstore[endindex],input);
                    if(elements<15)
                    {
                        elements++;
                    }
                    if(endindex==startindex && elements==15)
                    {
                        startindex = (startindex+1)%15;
                    }
                }
                else
                {
                    if(endindex==0)
                    {
                        endindex = 14;
                    }
                    else
                    {
                        endindex = endindex-1;
                    }
                }
            }
        }
        else
        {
            if(strcmp(input,"pastevents\n")!=0 && strcmp(input,"pastevents purge\n")!=0 && dupstr!=NULL && strcmp(dupstr,"excute")!=0)
            {
                endindex = (endindex+1)%15;
                if(endindex!=0 && strcmp(commandstore[endindex-1],input)!=0)
                {
                    strcpy(commandstore[endindex],input);
                    if(elements<15)
                    {
                        elements++;
                    }
                    if(endindex==startindex && elements==15)
                    {
                        startindex = (startindex+1)%15;
                    }
                }
                else if(endindex==0 && elements==15 && strcmp(commandstore[14],input)!=0)
                {
                    strcpy(commandstore[endindex],input);
                    if(elements<15)
                    {
                        elements++;
                    }
                    if(endindex==startindex && elements==15)
                    {
                        startindex = (startindex+1)%15;
                    }
                }
                else if(endindex==0 && elements==0)
                {
                    strcpy(commandstore[endindex],input);
                    if(elements<15)
                    {
                        elements++;
                    }
                    if(endindex==startindex && elements==15)
                    {
                        startindex = (startindex+1)%15;
                    }
                }
                else
                {
                    if(endindex==0)
                    {
                        endindex = 14;
                    }
                    else
                    {
                        endindex = endindex-1;
                    }
                }
            }
        }
        
        
        FILE* past2 = fopen(open,"w");
        past2 = backup;

        if(elements<15)
        {
            for(int i=startindex;i<=endindex;i++)
            {
                fputs(commandstore[i],past2);
            }
        }
        else
        {   int tempelem = 15;
            for(int i=startindex;;i=(i+1)%15)
            {
                if(tempelem<=0)
                {
                    break;
                }
                fputs(commandstore[i],past2);
                tempelem--;
            }
        }
        backup = past;
        fclose(past2);

        // excuting each command by checking which function we have to use.
        excute(commands,number,home,previous,directory,pointstart,pointend,pointelem,pointsignal,commandstore,tempdirectory,backup);
    }
}
