#include "headers.h"
extern void special2(char* string,char** commands,int* number);
extern void prompt(char* home,char* directory) ;
extern char* warp(char* home,char* folder,char* previous,char* string,const char* Path);
extern int filter(const struct dirent* entry);
extern int alphasort(const struct dirent** entry1, const struct dirent** entry2);
extern void colorprint(char* buff,char* print,int indicator);
extern void peek(int count,char** flag,char* home,char* previous);
extern void pastevents(FILE* backup);
extern void pasteventsflag(int count,int*number,int* pointstart,int* pointend,int* pointelem,char** commands,char* argu,char* home,char* previous,char* directory,int* pointsignal,char** commandstore,char* tempdirectory,FILE* backup);
extern void proclore(const char *pid_str);
extern void systemcommands(char* command,char** flag3);
extern char* constructpath(char* abstract,char* actual,char* home);
extern void seek(int count4,char** flag4,char* tempdirectory,char* home,char* directory);
extern void actualseek(char* current,char* target,char* tempcurr,int* num1);
extern int checkFileType(const char *path);
extern void actualseek_d(char* current,char* target,char* tempcurr,int* num2);
extern void actualseek_f(char* current,char* target,char* tempcurr,int* num3);
extern void actualseek_dfind(char* current,char* target,char* tempcurr,int* num2);
extern void actualseek_ffind(char* current,char* target,char* tempcurr,int* num2);
extern void actualseek_dchange(char* current,char* target,char* tempcurr,int* num2,char* directory);

void excute(char** commands,int* number,char* home,char* previous,char* directory,int* pointstart,int* pointend,int* pointelem,int* pointsignal,char** commandstore,char* tempdirectory,FILE* backup)
{
    for(int i=0;i<*(number);i++)
    {
            char* command = strtok(commands[i]," ");

            if(strcmp(command,"warp")==0)// For warp command
            {
                *pointsignal = 1;
                char* arg = strtok(NULL," ");
                if(arg[strlen(arg)-1]==10)
                {
                    arg[strlen(arg)-1] = 0;
                }

                char temp[200];
                char *s = warp(home,directory,previous,temp,arg);
                strcpy(directory,s);
                printf("%s\n", directory);
            }
            else if(strcmp(command,"warp\n")==0)
            {
                *pointsignal = 1;
                char* arg = strtok(NULL," ");

                char temp[200];
                strcpy(previous, directory);
                strcpy(directory, home);
                chdir(directory);
                
                printf("%s\n", directory);
            }
            else if(strcmp(command,"peek")==0)
            {
                char** flag;
                flag = (char**)malloc(sizeof(char*)*10);
                int count = 0;

                char* str = strtok(NULL, " ");
                while(str!=NULL)
                {
                    flag[count] = str;
                    count++;
                    str = strtok(NULL, " ");
                }
                flag[count-1][strlen(flag[count-1])-1] = 0;

                peek(count,flag,home,previous);
            }
            else if(strcmp(command,"peek\n")==0)
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
                    int indicator = 0;
                    colorprint(buffer,list[i]->d_name,indicator);
                    strcpy(buffer,dupli);
                }
                free(dupli);
                free(buffer);
            }
            else if(strcmp(command,"pastevents\n")==0)
            {
                pastevents(backup);
            }
            else if(strcmp(command,"pastevents")==0)
            {
                char** flag1;
                flag1 = (char**)malloc(sizeof(char*)*10);
                int count1 = 0;

                char* str1 = strtok(NULL, " ");
                while(str1!=NULL)
                {
                    flag1[count1] = str1;
                    count1++;
                    str1 = strtok(NULL, " ");
                }
                flag1[count1-1][strlen(flag1[count1-1])-1] = 0;

                pasteventsflag(count1,number,pointstart,pointend,pointelem,commands,flag1[count1-1],home,previous,directory,pointsignal,commandstore,tempdirectory,backup);
            }
            else if(strcmp(command,"proclore")==0)
            {
                char** flag2;
                flag2 = (char**)malloc(sizeof(char*)*10);
                int count2 = 0;

                char* str2 = strtok(NULL, " ");
                while(str2!=NULL)
                {
                    flag2[count2] = str2;
                    count2++;
                    str2 = strtok(NULL, " ");
                }
                flag2[count2-1][strlen(flag2[count2-1])-1] = 0;

                proclore(flag2[0]);
            }
            else if(strcmp(command,"proclore\n")==0)
            {
                int pid = getpid();

                char pidstr[20];
                snprintf(pidstr,sizeof(pidstr),"%d",pid);

                proclore(pidstr);
            }
            else if(strcmp(command,"seek")==0)
            {
                char** flag4;
                flag4 = (char**)malloc(sizeof(char*)*10);
                int count4 = 0;

                char* str4 = strtok(NULL, " ");
                while(str4!=NULL)
                {
                    flag4[count4] = str4;
                    count4++;
                    str4 = strtok(NULL, " ");
                }
                flag4[count4-1][strlen(flag4[count4-1])-1] = 0;

                seek(count4,flag4,tempdirectory,home,directory);
                strcpy(tempdirectory,directory);
            }
            else
            {
                char** flag3;
                flag3 = (char**)calloc(10,sizeof(char*));
                int count3 = 0;

                char* str3 = strtok(NULL, " ");
                while(str3!=NULL)
                {
                    flag3[count3] = str3;
                    count3++;
                    str3 = strtok(NULL, " ");
                }
                if(count3>=1 && flag3[count3-1][strlen(flag3[count3-1])-1]==10)
                {
                    flag3[count3-1][strlen(flag3[count3-1])-1] = 0;
                }
                flag3[count3] = NULL;

                if(command[strlen(command)-1]==10)
                {
                    command[strlen(command)-1] = 0;
                }
                
                char** flagstore;
                flagstore = (char**)calloc(count3+2,sizeof(char*));
                for(int i=0;i<count3+2;i++)
                {
                    flagstore[i] = (char*)malloc(30);
                }
                strcpy(flagstore[0],command);
                for(int i=1;i<count3+1;i++)
                {
                    strcpy(flagstore[i],flag3[i-1]); 
                }
                flagstore[count3+1] = NULL;

                systemcommands(command,flagstore);
            }
    }
}