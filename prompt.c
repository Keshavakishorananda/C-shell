#include "headers.h"

void prompt(char* home,char* directory) 
{
    // Do not hardcode the prompt
    struct utsname uname_data;
    uname(&uname_data);

    char* newname;
    newname = (char*)calloc(4096,1);

    if(strcmp(home, directory)==0)
    {
        strcpy(newname, "~");
    }
    else
    {
        int homelen = strlen(home);
        int direclen = strlen(directory);

        if(homelen < direclen)
        {
            strcpy(newname, "~");
            for(int i=homelen;i<direclen;i++)
            {
                newname[i-homelen+1] = directory[i];
            }
            newname[direclen] = 0;
            newname[direclen+1]=0;
        }
        else
        {
            getcwd(newname, 4096);
        }
    }

    printf("<%s@%s:%s> ",getlogin(),uname_data.nodename,newname);

    free(newname);

}