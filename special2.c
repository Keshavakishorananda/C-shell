#include "headers.h"

void special2(char* string,char** commands,int* number)
{
    char* str = strtok(string, ";,&");

    while(str!=NULL)
    {
        commands[*(number)] = str;
        (*(number))++;
        str = strtok(NULL, ";,&");
    }
}