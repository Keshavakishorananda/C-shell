#include "headers.h"

void pastevents(FILE* backup)
{
    FILE* storefile;

    storefile = fopen("pastfile.txt","r");
    storefile = backup;

    char line[100];
    while (fgets(line, sizeof(line), storefile) != NULL) 
    {
        printf("%s",line);
    }

    fclose(storefile);
}

void pasteventsflag(int count,int*number,int* pointstart,int* pointend,int* pointelem,char** commands,char* argu,char* home,char* previous,char* directory,int* pointsignal,char** commandstore,char* tempdirectory,FILE* backup)
{
    if(count==1 && strcmp(argu,"purge")==0)
    {
        FILE *noerro = fopen("pastfile.txt", "w");
    
        if(noerro == NULL) 
        {
            perror("Unable to open the file");
        }
        
        fclose(noerro);

        *pointstart = 0;
        *pointend = -1;
        *pointelem = 0;
    }
    else if(count=2)
    {
        int pos;
        pos = argu[0]-48;

        char** newcomm;
        newcomm =(char**)malloc(sizeof(char*)*10);
        for(int i=0;i<10;i++)
        {
            newcomm[i] = (char*)malloc(100);
        }

        int new = 1;
        int* newnum;
        newnum = &new;

        int ref = ((*pointstart)+(*pointelem)-pos)%15;
        
        strcpy(newcomm[0],commandstore[ref]);

        excute(newcomm,newnum,home,previous,directory,pointstart,pointend,pointelem,pointsignal,commandstore,tempdirectory,backup);
        free(newcomm);
    }
}