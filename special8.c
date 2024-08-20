#include "headers.h"

extern char* constructpath(char* abstract,char* actual,char* home);

int checkFileType(const char *path) 
{
    struct stat st;
    
    if (stat(path, &st) == 0) 
    {
        if (S_ISDIR(st.st_mode)) 
        {
            return 1; // Path points to a directory
        } 
        else if (S_ISREG(st.st_mode)) 
        {
            return 2; // Path points to a regular file
        } 
        else 
        {
            return 0; // Path points to neither a directory nor a file
        }
    } 
    else 
    {
        perror("stat");
        return -1; // Error occurred while checking the type
    }
}

void actualseek(char* current,char* target,char* tempcurr,int* num1)
{
    char targtxt[20];
    strcpy(targtxt,target);
    strcat(targtxt,".txt");

    DIR *dir = opendir(current);
    if(!dir) 
    {
        // printf("directory is not opened\n");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) 
    {

        if((strcmp(entry->d_name, target) != 0 && strcmp(entry->d_name,targtxt)!=0) && entry->d_name[0]!=46) 
        {
            char path[1000];
            snprintf(path, sizeof(path), "%s/%s", current, entry->d_name);
            actualseek(path,target,tempcurr,num1);
        }
        else if(strcmp(entry->d_name, target) == 0 || strcmp(entry->d_name,targtxt)==0)
        {
            char path[1000];
            snprintf(path, sizeof(path), "%s/%s", current, entry->d_name);
            int last;
            for(int i=0;i<strlen(path);i++)
            {
                if(tempcurr[i]!=path[i])
                {
                    last = i;
                    break;
                }
            }
            char tempath[1000];
            strcpy(tempath,"./");
            for(int i=last+2;i<=strlen(path);i++)
            {
                tempath[i-last] = path[i-1];
            }
            tempath[strlen(path)-last+1] = 0;
            printf("%s\n",tempath);
            (*num1)++;
            actualseek(path,target,tempcurr,num1);
        }
    }
    closedir(dir);
}

void actualseek_d(char* current,char* target,char* tempcurr,int* num2)
{
    char targtxt[20];
    strcpy(targtxt,target);
    strcat(targtxt,".txt");

    DIR *dir = opendir(current);
    if(!dir) 
    {
        // printf("directory is not opened\n");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) 
    {

        if((strcmp(entry->d_name, target) != 0 && strcmp(entry->d_name,targtxt)!=0) && entry->d_name[0]!=46) 
        {
            char path[1000];
            snprintf(path, sizeof(path), "%s/%s", current, entry->d_name);
            actualseek_d(path,target,tempcurr,num2);
        }
        else if(strcmp(entry->d_name, target) == 0 || strcmp(entry->d_name,targtxt)==0)
        {
            char path[1000];
            snprintf(path, sizeof(path), "%s/%s", current, entry->d_name);

            int filetype = checkFileType(path);

            if(filetype==1)
            {
                int last;
                for(int i=0;i<strlen(path);i++)
                {
                    if(tempcurr[i]!=path[i])
                    {
                        last = i;
                        break;
                    }
                }
                char tempath[1000];
                strcpy(tempath,"./");
                for(int i=last+2;i<=strlen(path);i++)
                {
                    tempath[i-last] = path[i-1];
                }
                tempath[strlen(path)-last+1] = 0;
                printf("%s\n",tempath);
                (*num2)++;
            }
            actualseek_d(path,target,tempcurr,num2);
        }
    }
    closedir(dir);
}

void actualseek_f(char* current,char* target,char* tempcurr,int* num3)
{
    char targtxt[20];
    strcpy(targtxt,target);
    strcat(targtxt,".txt");

    DIR *dir = opendir(current);
    if(!dir) 
    {
        // printf("directory is not opened\n");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) 
    {

        if((strcmp(entry->d_name, target) != 0 && strcmp(entry->d_name,targtxt)!=0) && entry->d_name[0]!=46) 
        {
            char path[1000];
            snprintf(path, sizeof(path), "%s/%s", current, entry->d_name);
            actualseek_f(path,target,tempcurr,num3);
        }
        else if(strcmp(entry->d_name, target) == 0 || strcmp(entry->d_name,targtxt)==0)
        {
            char path[1000];
            snprintf(path, sizeof(path), "%s/%s", current, entry->d_name);

            int filetype = checkFileType(path);

            if(filetype==2)
            {
                int last;
                for(int i=0;i<strlen(path);i++)
                {
                    if(tempcurr[i]!=path[i])
                    {
                        last = i;
                        break;
                    }
                }
                char tempath[1000];
                strcpy(tempath,"./");
                for(int i=last+2;i<=strlen(path);i++)
                {
                    tempath[i-last] = path[i-1];
                }
                tempath[strlen(path)-last+1] = 0;
                printf("%s\n",tempath);

                (*num3)++;
            }
            actualseek_f(path,target,tempcurr,num3);
        }
    }
    closedir(dir);
}

void actualseek_dfind(char* current,char* target,char* tempcurr,int* num4)
{
    char targtxt[20];
    strcpy(targtxt,target);
    strcat(targtxt,".txt");

    DIR *dir = opendir(current);
    if(!dir) 
    {
        // printf("directory is not opened\n");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) 
    {

        if((strcmp(entry->d_name, target) != 0 && strcmp(entry->d_name,targtxt)!=0) && entry->d_name[0]!=46) 
        {
            char path[1000];
            snprintf(path, sizeof(path), "%s/%s", current, entry->d_name);
            actualseek_dfind(path,target,tempcurr,num4);
        }
        else if(strcmp(entry->d_name, target) == 0 || strcmp(entry->d_name,targtxt)==0)
        {
            char path[1000];
            snprintf(path, sizeof(path), "%s/%s", current, entry->d_name);

            int filetype = checkFileType(path);

            if(filetype==1)
            {
                (*num4)++;   
            }
            actualseek_dfind(path,target,tempcurr,num4);
        }
    }
    closedir(dir);
}

void actualseek_ffind(char* current,char* target,char* tempcurr,int* num6)
{
    char targtxt[20];
    strcpy(targtxt,target);
    strcat(targtxt,".txt");

    DIR *dir = opendir(current);
    if(!dir) 
    {
        // printf("directory is not opened\n");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) 
    {

        if((strcmp(entry->d_name, target) != 0 && strcmp(entry->d_name,targtxt)!=0) && entry->d_name[0]!=46) 
        {
            char path[1000];
            snprintf(path, sizeof(path), "%s/%s", current, entry->d_name);
            actualseek_ffind(path,target,tempcurr,num6);
        }
        else if(strcmp(entry->d_name, target) == 0 || strcmp(entry->d_name,targtxt)==0)
        {
            char path[1000];
            snprintf(path, sizeof(path), "%s/%s", current, entry->d_name);

            int filetype = checkFileType(path);

            if(filetype==2)
            {
                (*num6)++;   
            }
            actualseek_ffind(path,target,tempcurr,num6);
        }
    }
    closedir(dir);
}

void actualseek_dchange(char* current,char* target,char* tempcurr,int* num2,char* directory)
{
    char targtxt[20];
    strcpy(targtxt,target);
    strcat(targtxt,".txt");

    DIR *dir = opendir(current);
    if(!dir) 
    {
        // printf("directory is not opened\n");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) 
    {

        if((strcmp(entry->d_name, target) != 0 && strcmp(entry->d_name,targtxt)!=0) && entry->d_name[0]!=46) 
        {
            char path[1000];
            snprintf(path, sizeof(path), "%s/%s", current, entry->d_name);
            actualseek_dchange(path,target,tempcurr,num2,directory);
        }
        else if(strcmp(entry->d_name, target) == 0 || strcmp(entry->d_name,targtxt)==0)
        {
            char path[1000];
            snprintf(path, sizeof(path), "%s/%s", current, entry->d_name);

            int filetype = checkFileType(path);

            if(filetype==1)
            {
                int last;
                for(int i=0;i<strlen(path);i++)
                {
                    if(tempcurr[i]!=path[i])
                    {
                        last = i;
                        break;
                    }
                }
                char tempath[1000];
                strcpy(tempath,"./");
                for(int i=last+2;i<=strlen(path);i++)
                {
                    tempath[i-last] = path[i-1];
                }
                tempath[strlen(path)-last+1] = 0;
                printf("%s\n",tempath);
                (*num2)++;

                chdir(path);
                strcpy(directory,path);
                break;
            }
        }
    }
    closedir(dir);
}

void seek(int count4,char** flag4,char* tempdirectory,char* home,char* directory)
{
    if(count4==1)
    {
        char* random0 = (char*)calloc(1024,sizeof(char));
        strcpy(random0,tempdirectory);

        if (access(random0, F_OK) != 0)
        {
            printf("Invalid path\n");
        }
    }
    else if(count4==2)
    {
        char* random = (char*)calloc(1024,sizeof(char));
        random = constructpath(flag4[1],tempdirectory,home);

        if (access(random, F_OK) != 0)
        {
            printf("Invalid path\n");
        }

        int init = 0;
        int* num1;
        num1 = &init;
        actualseek(random,flag4[0],random,num1);

        if(init=0)
        {
            printf("Invalid\n");
        }
    }
    else if(count4==3)
    {
        char* random1 = (char*)calloc(1024,sizeof(char));
        random1 = constructpath(flag4[2],tempdirectory,home);
        if (access(random1, F_OK) != 0)
        {
            printf("Invalid path\n");
        }

        if(strcmp(flag4[0],"-d")==0)
        {
            int init1 = 0;
            int* num2;
            num2 = &init1;
            actualseek_d(random1,flag4[1],random1,num2);

            if(*num2==0)
            {
                printf("Invalid\n");
            }
        }
        else if(strcmp(flag4[0],"-f")==0)
        {
            int init2 = 0;
            int* num3;
            num3 = &init2;
            actualseek_f(random1,flag4[1],random1,num3);

            if(init2==0)
            {
                printf("Invalid\n");
            }
        }
    }
    else if(count4==4)
    {
        char* random2 = (char*)calloc(1024,sizeof(char));
        random2 = constructpath(flag4[3],tempdirectory,home);
        if(strcmp(flag4[0],"-e")==0 || strcmp(flag4[1],"-e")==0)
        {
            if(strcmp(flag4[0],"-e")==0 && strcmp(flag4[1],"-d")==0)
            {
                int init3 = 0;
                int* num4;
                num4 = &init3;
                actualseek_dfind(random2,flag4[2],random2,num4);

                if(init3==1)
                {
                    actualseek_dchange(random2,flag4[2],random2,num4,directory);
                }
            }
            else if(strcmp(flag4[0],"-d")==0 && strcmp(flag4[1],"-e")==0)
            {
                int init4 = 0;
                int* num5;
                num5 = &init4;
                actualseek_dfind(random2,flag4[2],random2,num5);

                if(init4==1)
                {
                    actualseek_dchange(random2,flag4[2],random2,num5,directory);
                }
            }
            else if(strcmp(flag4[0],"-f")==0 && strcmp(flag4[1],"-e")==0)
            {
                int init5 = 0;
                int* num6;
                num6 = &init5;
                actualseek_ffind(random2,flag4[2],random2,num6);

                if(init5==1)
                {
                    actualseek_f(random2,flag4[2],random2,num6);
                }
            }
            else if(strcmp(flag4[0],"-e")==0 && strcmp(flag4[1],"-f")==0)
            {
                int init6 = 0;
                int* num7;
                num7 = &init6;
                actualseek_ffind(random2,flag4[2],random2,num7);

                if(init6==1)
                {
                    actualseek_f(random2,flag4[2],random2,num7);
                }
            }
        }
    }
}

// int main()
// {
//     char* current = "/home/keshava/mini-project-1-Keshavakishorananda";
//     char* target = "test";
//     char* tempcurr = (char*)malloc(1024);
//     strcpy(tempcurr,current);

//     actualseek_f(current,target,tempcurr);

//     free(tempcurr);

//     return 0;
// }