#include "headers.h"

int filter(const struct dirent* entry)
{
    if((entry->d_name)[0] == 46)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int alphasort(const struct dirent** entry1, const struct dirent** entry2)
{
    if(strcmp((*entry1)->d_name,(*entry2)->d_name)<0)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

void colorprint(char* buff,char* print,int indicator)
{
    if(indicator==0)
    {
        DIR* directory;
        directory = opendir(print);

        if(directory!=NULL)
        {
            printf(ANSI_COLOR_BLUE" %s\n" ANSI_COLOR_RESET,print);
        }
        else
        {
            if(access(print,X_OK)==0)
            {
                printf(ANSI_COLOR_GREEN "%s\n" ANSI_COLOR_RESET,print);
            }
            else
            {
                printf("%s\n",print);
            }
        }
        closedir(directory);
    }
    else
    {
        strcat(buff,"/");
        strcat(buff,print);
        struct stat info;

        int check = stat(buff, &info);

        if(check==0)
        {
            printf("%ld ",info.st_nlink);

            struct passwd* owner = getpwuid(info.st_uid); 
            printf("%s ",owner->pw_name);

            struct group* grp = getgrgid(info.st_gid);
            printf("%s ",grp->gr_name);
            printf("%ld ",info.st_size);

            struct tm *dt;
            time_t modification_time = info.st_mtime;
            dt = localtime(&modification_time);
            char time_buffer[80];
            strftime(time_buffer, sizeof(time_buffer), "%m-%d %H:%M", dt);
            
            printf("%s ", time_buffer);
        }
        else
        {
            printf("No file Exists\n");
        }

        DIR* directory;
        directory = opendir(print);

        if(directory!=NULL)
        {
            printf(ANSI_COLOR_BLUE" %s\n" ANSI_COLOR_RESET,print);
        }
        else
        {
            if(access(print,X_OK)==0)
            {
                printf(ANSI_COLOR_GREEN "%s\n" ANSI_COLOR_RESET,print);
            }
            else
            {
                printf("%s\n",print);
            }
        }
        closedir(directory);
    }
}

void peek(int count,char** flag,char* home,char* previous)
{
    if(count==1)
    {
        if(strcmp(flag[count-1],"-l")==0)
        {
            char* buffer;
            buffer = (char*)malloc(1000);

            char* dupli;
            dupli = (char*)malloc(1000);

            getcwd(buffer, 1000);
            getcwd(dupli, 1000);

            struct dirent** list;
            int n;

            n = scandir(buffer,&list,filter,alphasort);

            for(int i=0;i<n;i++)
            {
                int indicator = 1;
                colorprint(buffer,list[i]->d_name,indicator);
                strcpy(buffer,dupli);
            }
            free(dupli);
            free(buffer);
        }
        else if(strcmp(flag[count-1],"-a")==0)
        {
            char* buffer;
            buffer = (char*)malloc(1000);

            char* dupli;
            dupli = (char*)malloc(1000);

            getcwd(buffer, 1000);
            getcwd(buffer, 1000);

            struct dirent** list;
            int n;

            n = scandir(buffer,&list,NULL,alphasort);

            for(int i=0;i<n;i++)
            {
                int indicator = 0;
                colorprint(buffer,list[i]->d_name,indicator);
                strcpy(buffer,dupli);
            }
            free(buffer);
            free(dupli);
        }
        else if(strcmp(flag[count-1],".")==0)
        {
            char* buffer;
            buffer = (char*)malloc(1000);

            char* dupli;
            dupli = (char*)malloc(1000);

            getcwd(buffer, 1000);
            getcwd(dupli,1000);

            struct dirent** list;
            int n;

            n = scandir(buffer,&list,filter,alphasort);

            for(int i=0;i<n;i++)
            {
                int indicator = 0;
                colorprint(buffer,list[i]->d_name,indicator);
                strcpy(buffer, dupli);
            }
            free(buffer);
            free(dupli);
        }
        else if(strcmp(flag[count-1],"..")==0)
        {
            char* buffer;
            buffer = (char*)malloc(1000);

            char* dupli;
            dupli = (char*)malloc(1000);

            getcwd(buffer, 1000);
            getcwd(dupli,1000);

            int len;
            for(int i=strlen(buffer)-1;i>=0;i--)
            {
                if(buffer[i]==47)
                {
                    len = i;
                    break;
                }
            }


            struct dirent** list;
            int n;

            n = scandir(buffer,&list,filter,alphasort);

            for(int i=0;i<n;i++)
            {
                int indicator = 0;
                colorprint(buffer,list[i]->d_name,indicator);
                strcpy(buffer,dupli);
            }
            free(buffer);
            free(dupli);
        }
        else if(strcmp(flag[count-1],"-")==0)
        {
            char* buffer;
            buffer = (char*)malloc(1000);

            char* dupli;
            dupli = (char*)malloc(1000);

            strcpy(buffer,previous);
            strcpy(dupli,buffer);

            struct dirent** list;
            int n;

            n = scandir(buffer,&list,filter,alphasort);

            for(int i=0;i<n;i++)
            {
                int indicator = 0;
                colorprint(buffer,list[i]->d_name,indicator);
                strcpy(buffer,dupli);
            }
            free(dupli);
            free(buffer);
        }
        else if(strcmp(flag[count-1],"~")==0)
        {
            char* buffer;
            buffer = (char*)malloc(1000);

            char* dupli;
            dupli = (char*)malloc(1000);

            strcpy(buffer,home);
            strcpy(dupli, buffer);

            struct dirent** list;
            int n;

            n = scandir(buffer,&list,filter,alphasort);

            for(int i=0;i<n;i++)
            {
                int indicator = 0;
                colorprint(buffer,list[i]->d_name,indicator);
                strcpy(buffer,dupli);
            }
            free(buffer);
            free(dupli);
        }
        else
        {
            if(flag[0][0]!=126)
            {

                char* buffer;
                buffer = (char*)malloc(1000);

                char* dupli;
                dupli = (char*)malloc(1000);

                getcwd(buffer, 1000);
                strcat(buffer, "/");
                strcat(buffer, flag[0]);
                strcpy(dupli, buffer);

                struct dirent** list;
                int n;

                n = scandir(buffer,&list,filter,alphasort);

                for(int i=0;i<n;i++)
                {
                    int indicator = 0;
                    colorprint(buffer,list[i]->d_name,indicator);
                    strcpy(buffer,dupli);
                }
                free(dupli);
                free(buffer);
            }
            else
            {
                char* buffer;
                buffer = (char*)malloc(1000);

                char* dupli;
                dupli = (char*)malloc(1000);

                strcat(buffer, home);
                int len = strlen(buffer);
                for(int i=0;i<strlen(flag[0]);i++)
                {
                    buffer[len+i] = flag[0][i+1];
                }
                strcpy(dupli, buffer);

                struct dirent** list;
                int n;

                n = scandir(buffer,&list,filter,alphasort);

                for(int i=0;i<n;i++)
                {
                    int indicator = 0;
                    colorprint(buffer,list[i]->d_name,indicator);
                    strcpy(buffer,dupli);
                }
                free(dupli);
                free(buffer);
            }
        }
        
    }
    else if(count==2)
    {
        if(strcmp(flag[count-2],"-a")==0)
        {
            if(strcmp(flag[count-1],".")==0)
            {
                char* buffer;
                buffer = (char*)malloc(1000);

                char* dupli;
                dupli = (char*)malloc(1000);

                getcwd(buffer, 1000);
                strcpy(dupli, buffer);

                struct dirent** list;
                int n;

                n = scandir(buffer,&list,NULL,alphasort);

                for(int i=0;i<n;i++)
                {
                    int indicator = 0;
                    colorprint(buffer,list[i]->d_name,indicator);
                    strcpy(buffer,dupli);
                }
                free(dupli);
                free(buffer);
            }
            else if(strcmp(flag[count-1],"..")==0)
            {
                char* buffer;
                buffer = (char*)malloc(1000);

                char* dupli;
                dupli = (char*)malloc(1000);

                getcwd(buffer, 1000);

                int len;
                for(int i=strlen(buffer)-1;i>=0;i--)
                {
                    if(buffer[i]==47)
                    {
                        len = i;
                        break;
                    }
                }

                char* string;
                string = (char*)malloc(1000);

                for(int i=0;i<len;i++)
                {
                    string[i] = buffer[i];
                }
                string[len] = 0;
                strcpy(dupli, string);
                struct dirent** list;
                int n;

                n = scandir(string,&list,NULL,alphasort);

                for(int i=0;i<n;i++)
                {
                    int indicator = 0;
                    colorprint(string,list[i]->d_name,indicator);
                    strcpy(string,dupli);
                }
                free(dupli);
                free(buffer);
                free(string);
            }
            else if(strcmp(flag[count-1],"-")==0)
            {
                char* buffer;
                buffer = (char*)malloc(1000);

                char* dupli;
                dupli = (char*)malloc(1000);

                strcpy(buffer,previous);
                strcpy(dupli,buffer);

                struct dirent** list;
                int n;

                n = scandir(buffer,&list,NULL,alphasort);

                for(int i=0;i<n;i++)
                {
                    int indicator = 0;
                    colorprint(buffer,list[i]->d_name,indicator);
                    strcpy(buffer,dupli);
                }
                free(dupli);
                free(buffer);
            }
            else if(strcmp(flag[count-1],"~")==0)
            {
                char* buffer;
                buffer = (char*)malloc(1000);

                char* dupli;
                dupli = (char*)malloc(1000);

                strcpy(buffer,home);
                strcpy(dupli,buffer);

                struct dirent** list;
                int n;

                n = scandir(buffer,&list,NULL,alphasort);

                for(int i=0;i<n;i++)
                {
                    int indicator = 0;
                    colorprint(buffer,list[i]->d_name,indicator);
                    strcpy(buffer,dupli);
                }
                free(dupli);
                free(buffer);
            }
            else
            {
                if(flag[0][0]!=126)
                {

                    char* buffer;
                    buffer = (char*)malloc(1000);

                    char* dupli;
                    dupli = (char*)malloc(1000);

                    getcwd(buffer, 1000);
                    strcat(buffer, "/");
                    strcat(buffer, flag[0]);
                    strcpy(dupli,buffer);

                    struct dirent** list;
                    int n;

                    n = scandir(buffer,&list,NULL,alphasort);

                    for(int i=0;i<n;i++)
                    {
                        int indicator = 0;
                        colorprint(buffer,list[i]->d_name,indicator);;
                        strcpy(buffer,dupli);
                    }
                    free(dupli);
                    free(buffer);
                }
                else
                {
                    char* buffer;
                    buffer = (char*)malloc(1000);

                    char* dupli;
                    dupli = (char*)malloc(1000);

                    strcat(buffer, home);
                    int len = strlen(buffer);
                    for(int i=0;i<strlen(flag[0]);i++)
                    {
                        buffer[len+i] = flag[0][i+1];
                    }
                    strcpy(dupli,buffer);

                    struct dirent** list;
                    int n;

                    n = scandir(buffer,&list,NULL,alphasort);

                    for(int i=0;i<n;i++)
                    {
                        int indicator = 0;
                        colorprint(buffer,list[i]->d_name,indicator);
                        strcpy(buffer,dupli);
                    }
                    free(dupli);
                    free(buffer);
                }
            }
        }
        else if(strcmp(flag[count-2],"-l")==0)
        {
            if(strcmp(flag[count-1],".")==0)
            {
                char* buffer;
                buffer = (char*)malloc(1000);

                char* dupli;
                dupli = (char*)malloc(1000);

                getcwd(buffer, 1000);
                strcpy(dupli,buffer);

                struct dirent** list;
                int n;

                n = scandir(buffer,&list,filter,alphasort);

                for(int i=0;i<n;i++)
                {
                    int indicator = 1;
                    colorprint(buffer,list[i]->d_name,indicator);
                    strcpy(buffer,dupli);
                }
                free(buffer);
                free(dupli);
            }
            else if(strcmp(flag[count-1],"..")==0)
            {
                char* buffer;
                buffer = (char*)malloc(1000);

                char* dupli;
                dupli = (char*)malloc(1000);

                getcwd(buffer, 1000);

                int len;
                for(int i=strlen(buffer)-1;i>=0;i--)
                {
                    if(buffer[i]==47)
                    {
                        len = i;
                        break;
                    }
                }

                char* string;
                string = (char*)malloc(1000);

                for(int i=0;i<len;i++)
                {
                    string[i] = buffer[i];
                }
                string[len] = 0;

                strcpy(dupli,string);

                struct dirent** list;
                int n;

                n = scandir(string,&list,filter,alphasort);

                for(int i=0;i<n;i++)
                {
                    int indicator = 1;
                    colorprint(string,list[i]->d_name,indicator);
                    strcpy(string,dupli);
                }
                free(buffer);
                free(string);
                free(dupli);
            }
            else if(strcmp(flag[count-1],"-")==0)
            {
                char* buffer;
                buffer = (char*)malloc(1000);

                char* dupli;
                dupli = (char*)malloc(1000);

                strcpy(buffer,previous);
                strcpy(dupli,buffer);

                struct dirent** list;
                int n;

                n = scandir(buffer,&list,filter,alphasort);

                for(int i=0;i<n;i++)
                {
                    int indicator = 1;
                    colorprint(buffer,list[i]->d_name,indicator);
                    strcpy(buffer,dupli);
                }
                free(buffer);
                free(dupli);
            }
            else if(strcmp(flag[count-1],"~")==0)
            {
                char* buffer;
                buffer = (char*)malloc(1000);

                char* dupli;
                dupli = (char*)malloc(1000);

                strcpy(buffer,home);
                strcpy(dupli,buffer);

                struct dirent** list;
                int n;

                n = scandir(buffer,&list,filter,alphasort);

                for(int i=0;i<n;i++)
                {
                    int indicator = 1;
                    colorprint(buffer,list[i]->d_name,indicator);
                    strcpy(buffer,dupli);
                }
                free(dupli);
                free(buffer);
            }
            else
            {
                if(flag[0][0]!=126)
                {

                    char* buffer;
                    buffer = (char*)malloc(1000);

                    char* dupli;
                    dupli = (char*)malloc(1000);

                    getcwd(buffer, 1000);
                    strcat(buffer, "/");
                    strcat(buffer, flag[0]);

                    strcpy(dupli,buffer);

                    struct dirent** list;
                    int n;

                    n = scandir(buffer,&list,filter,alphasort);

                    for(int i=0;i<n;i++)
                    {
                        int indicator = 1;
                        colorprint(buffer,list[i]->d_name,indicator);;
                        strcpy(buffer,dupli);
                    }
                    free(dupli);
                    free(buffer);
                }
                else
                {
                    char* buffer;
                    buffer = (char*)malloc(1000);

                    char* dupli;
                    dupli = (char*)malloc(1000);

                    strcat(buffer, home);
                
                    int len = strlen(buffer);
                    for(int i=0;i<strlen(flag[0]);i++)
                    {
                        buffer[len+i] = flag[0][i+1];
                    }
                    strcpy(dupli,buffer);

                    struct dirent** list;
                    int n;

                    n = scandir(buffer,&list,filter,alphasort);

                    for(int i=0;i<n;i++)
                    {
                        int indicator = 1;
                        colorprint(buffer,list[i]->d_name,indicator);
                        strcpy(buffer,dupli);
                    }
                    free(dupli);
                    free(buffer);
                }
            }
        }
        else
        {
            if(strcmp(flag[count-1],".")==0)
            {
                char* buffer;
                buffer = (char*)malloc(1000);

                char* dupli;
                dupli = (char*)malloc(1000);

                getcwd(buffer, 1000);
                strcpy(dupli,buffer);

                struct dirent** list;
                int n;

                n = scandir(buffer,&list,NULL,alphasort);

                for(int i=0;i<n;i++)
                {
                    int indicator = 1;
                    colorprint(buffer,list[i]->d_name,indicator);
                    strcpy(buffer,dupli);
                }
                free(dupli);
                free(buffer);
            }
            else if(strcmp(flag[count-1],"..")==0)
            {
                char* buffer;
                buffer = (char*)malloc(1000);

                char* dupli;
                dupli = (char*)malloc(1000);

                getcwd(buffer, 1000);

                int len;
                for(int i=strlen(buffer)-1;i>=0;i--)
                {
                    if(buffer[i]==47)
                    {
                        len = i;
                        break;
                    }
                }

                char* string;
                string = (char*)malloc(1000);

                for(int i=0;i<len;i++)
                {
                    string[i] = buffer[i];
                }
                string[len] = 0;
                strcpy(dupli,string);

                struct dirent** list;
                int n;

                n = scandir(string,&list,NULL,alphasort);

                for(int i=0;i<n;i++)
                {
                    int indicator = 1;
                    colorprint(string,list[i]->d_name,indicator);
                    strcpy(buffer,dupli);
                }
                free(dupli);
                free(buffer);
                free(string);
            }
            else if(strcmp(flag[count-1],"-")==0)
            {
                char* buffer;
                buffer = (char*)malloc(1000);

                char* dupli;
                dupli = (char*)malloc(1000);

                strcpy(buffer,previous);
                strcpy(dupli,buffer);

                struct dirent** list;
                int n;

                n = scandir(buffer,&list,NULL,alphasort);

                for(int i=0;i<n;i++)
                {
                    int indicator = 1;
                    colorprint(buffer,list[i]->d_name,indicator);
                    strcpy(buffer,dupli);
                }
                free(dupli);
                free(buffer);
            }
            else if(strcmp(flag[count-1],"~")==0)
            {
                char* buffer;
                buffer = (char*)malloc(1000);

                char* dupli;
                dupli = (char*)malloc(1000);

                strcpy(buffer,home);
                strcpy(dupli,buffer);

                struct dirent** list;
                int n;

                n = scandir(buffer,&list,NULL,alphasort);

                for(int i=0;i<n;i++)
                {
                    int indicator = 1;
                    colorprint(buffer,list[i]->d_name,indicator);
                    strcpy(buffer,dupli);
                }
                free(dupli);
                free(buffer);
            }
            else
            {
                if(flag[0][0]!=126)
                {

                    char* buffer;
                    buffer = (char*)malloc(1000);

                    char* dupli;
                    dupli = (char*)malloc(1000);

                    getcwd(buffer, 1000);
                    strcat(buffer, "/");
                    strcat(buffer, flag[0]);

                    strcpy(dupli,buffer);

                    struct dirent** list;
                    int n;

                    n = scandir(buffer,&list,NULL,alphasort);

                    for(int i=0;i<n;i++)
                    {
                        int indicator = 1;
                        colorprint(buffer,list[i]->d_name,indicator);;
                        strcpy(buffer,dupli);
                    }
                    free(dupli);
                    free(buffer);
                }
                else
                {
                    char* buffer;
                    buffer = (char*)malloc(1000);

                    char* dupli;
                    dupli = (char*)malloc(1000);

                    strcat(buffer, home);
                    int len = strlen(buffer);
                    for(int i=0;i<strlen(flag[0]);i++)
                    {
                        buffer[len+i] = flag[0][i+1];
                    }
                    strcpy(dupli,buffer);

                    struct dirent** list;
                    int n;

                    n = scandir(buffer,&list,NULL,alphasort);

                    for(int i=0;i<n;i++)
                    {
                        int indicator = 1;
                        colorprint(buffer,list[i]->d_name,indicator);
                        strcpy(buffer,dupli);
                    }
                    free(dupli);
                    free(buffer);
                }
            }
        }
    }
    else
    {
        if(strcmp(flag[count-1],".")==0)
        {
            char* buffer;
            buffer = (char*)malloc(1000);

            char* dupli;
            dupli = (char*)malloc(1000);

            getcwd(buffer, 1000);
            strcpy(dupli,buffer);

            struct dirent** list;
            int n;

            n = scandir(buffer,&list,NULL,alphasort);

            for(int i=0;i<n;i++)
            {
                int indicator = 1;
                colorprint(buffer,list[i]->d_name,indicator);
                strcpy(buffer,dupli);
            }
            free(dupli);
            free(buffer);
        }
        else if(strcmp(flag[count-1],"..")==0)
        {
            char* buffer;
            buffer = (char*)malloc(1000);

            char* dupli;
            dupli = (char*)malloc(1000);

            getcwd(buffer, 1000);

            int len;
            for(int i=strlen(buffer)-1;i>=0;i--)
            {
                if(buffer[i]==47)
                {
                    len = i;
                    break;
                }
            }

            char* string;
            string = (char*)malloc(1000);

            for(int i=0;i<len;i++)
            {
                string[i] = buffer[i];
            }
            string[len] = 0;
            strcpy(dupli,string);

            struct dirent** list;
            int n;

            n = scandir(string,&list,NULL,alphasort);

            for(int i=0;i<n;i++)
            {
                int indicator = 1;
                colorprint(string,list[i]->d_name,indicator);
                strcpy(string,dupli);
            }
            free(dupli);
            free(buffer);
            free(string);
        }
        else if(strcmp(flag[count-1],"-")==0)
        {
            char* buffer;
            buffer = (char*)malloc(1000);

            char* dupli;
            dupli = (char*)malloc(1000);

            strcpy(buffer,previous);
            strcpy(dupli,buffer);

            struct dirent** list;
            int n;

            n = scandir(buffer,&list,NULL,alphasort);

            for(int i=0;i<n;i++)
            {
                int indicator = 1;
                colorprint(buffer,list[i]->d_name,indicator);
                strcpy(buffer,dupli);
            }
            free(dupli);
            free(buffer);
        }
        else if(strcmp(flag[count-1],"~")==0)
        {
            char* buffer;
            buffer = (char*)malloc(1000);

            char* dupli;
            dupli = (char*)malloc(1000);

            strcpy(buffer,home);
            strcpy(dupli,buffer);

            struct dirent** list;
            int n;

            n = scandir(buffer,&list,NULL,alphasort);

            for(int i=0;i<n;i++)
            {
                int indicator = 1;
                colorprint(buffer,list[i]->d_name,indicator);
                strcpy(buffer,dupli);
            }
            free(dupli);
            free(buffer);
        }
        else
        {
            if(flag[0][0]!=126)
            {

                char* buffer;
                buffer = (char*)malloc(1000);

                char* dupli;
                dupli = (char*)malloc(1000);

                getcwd(buffer, 1000);
                strcat(buffer, "/");
                strcat(buffer, flag[0]);

                strcpy(dupli,buffer);

                struct dirent** list;
                int n;

                n = scandir(buffer,&list,NULL,alphasort);

                for(int i=0;i<n;i++)
                {
                    int indicator = 1;
                    colorprint(buffer,list[i]->d_name,indicator);;
                    strcpy(buffer,dupli);
                }
                free(dupli);
                free(buffer);
            }
            else
            {
                char* buffer;
                buffer = (char*)malloc(1000);

                char* dupli;
                dupli = (char*)malloc(1000);

                strcat(buffer, home);
                int len = strlen(buffer);
                for(int i=0;i<strlen(flag[0]);i++)
                {
                    buffer[len+i] = flag[0][i+1];
                }
                strcpy(dupli,buffer);

                struct dirent** list;
                int n;

                n = scandir(buffer,&list,NULL,alphasort);

                for(int i=0;i<n;i++)
                {
                    int indicator = 1;
                    colorprint(buffer,list[i]->d_name,indicator);
                    strcpy(buffer,dupli);
                }
                free(dupli);
                free(buffer);
            }
        }
    }
}