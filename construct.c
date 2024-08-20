#include "headers.h"

char* constructpath(char* abstract,char* actual,char* home)
{
    if(strcmp(abstract,".")!=0 && abstract[0]==46 && abstract[1]!=46)
    {
        int len = strlen(abstract);

        char* tempabst = (char*)calloc(len+2,sizeof(char));
        for(int i=0;i<len-2;i++)
        {
            tempabst[i]=abstract[i+2];
        }
        tempabst[len-2] = 0;
        strcpy(abstract,tempabst);
        free(tempabst);

        constructpath(abstract,actual,home);
    }
    else if(strcmp(abstract,"..")!=0 && abstract[0]==46 && abstract[1]==46)
    {
        int len = strlen(abstract);
        char* tempabst = (char*)calloc(len+2,sizeof(char));
        for(int i=0;i<len-3;i++)
        {
            tempabst[i]=abstract[i+3];
        }
        tempabst[len-2] = 0;
        strcpy(abstract,tempabst);
        free(tempabst);

        int length;
        for(int i=strlen(actual)-1;i>=0;i--)
        {
            if(actual[i]==47)
            {
                length = i;
                break;
            }
        }

        char* tempstring = (char*)calloc(length+2,sizeof(char));

        for(int i=0;i<length;i++)
        {
            tempstring[i] = actual[i];
        }
        tempstring[length] = 0;
        strcpy(actual,tempstring);
        free(tempstring);

        constructpath(abstract,actual,home);

    }
    else if(strcmp(abstract,"~")!=0 && abstract[0]==126)
    {
        int len = strlen(abstract);

        char* tempabst = (char*)calloc(len+2,sizeof(char));
        for(int i=0;i<len;i++)
        {
            tempabst[i]=abstract[i+2];
        }
        strcpy(abstract,tempabst);
        free(tempabst);

        strcpy(actual,home);
        constructpath(abstract,actual,home);
    }
    else if(strcmp(abstract,".")==0)
    {
        return actual;
    }
    else if(strcmp(abstract,"..")==0)
    {
        int length;
        for(int i=strlen(actual)-1;i>=0;i--)
        {
            if(actual[i]==47)
            {
                length = i;
                break;
            }
        }

        char* tempstring = (char*)calloc(length+2,sizeof(char));

        for(int i=0;i<length;i++)
        {
            tempstring[i] = actual[i];
        }
        tempstring[length] = 0;
        strcpy(actual,tempstring);
        free(tempstring);

        return actual;
    }
    else if(strcmp(abstract,"~")==0)
    {
        return home;
    }
    else
    {   
        strcat(actual,"/");
        int len = strlen(actual);
        for(int i=0;i<strlen(abstract);i++)
        {
            actual[len+i] = abstract[i];
        }
        actual[len+strlen(abstract)]=0;
        return actual;
    }
}

// int main()
// {
//     char abstract[200] = "test";
//     char actual[200] = "/home/keshava/mini-project-1-Keshavakishorananda";
//     char home[200] = "/home/keshava";

//     char* result = (char*)malloc(200);

//     result = constructpath(abstract,actual,home);

//     printf("%s\n",result);
//     return 0;
// }