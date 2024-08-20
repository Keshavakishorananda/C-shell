#include "headers.h"

char* warp(char* home,char* folder,char* previous,char* string,const char* Path)
{

    if(strcmp(Path,"~")==0)
    {
        strcpy(string,home);
        strcpy(previous, folder);
        chdir(string);
    }
    else if(strcmp(Path,"-")==0)
    {
        strcpy(string, previous);
        strcpy(previous, folder);
        chdir(string);
    }
    else if(strcmp(Path,".")==0)
    {
        strcpy(string, folder);
        strcpy(previous, folder);
    }
    else if(strcmp(Path,"..")==0)
    {
        int len;
        for(int i=strlen(folder)-1;i>=0;i--)
        {
            if(folder[i]==47)
            {
                len = i;
                break;
            }
        }

        for(int i=0;i<len;i++)
        {
            string[i] = folder[i];
        }
        string[len] = 0;

        strcpy(previous, folder);

        chdir(string);
    }
    else if(Path==NULL)
    {
        strcpy(string,home);
        strcpy(previous, folder);
        chdir(string);
    }
    else
    {
        if(Path[0]!=126)
        {
            int check = chdir(Path);

            if(check==-1)
            {
                printf("This directory is not present\n");
                strcpy(string, folder);
            }
            else
            {
                getcwd(string, 200);
                strcpy(previous, folder);
            }
        }
        else
        {
            char* dup;
            dup = (char*)malloc(4096);

            strcat(dup, home);
            int len = strlen(dup);
            for(int i=0;i<strlen(Path);i++)
            {
                dup[len+i] = Path[i+1];
            }

            int check = chdir(dup);
            free(dup);

            if(check==-1)
            {
                printf("This directory is not present\n");
                strcpy(string, folder);
            }
            else
            {
                getcwd(string, 200);
                strcpy(previous, folder);
            }
        }
    }

    return string;
}