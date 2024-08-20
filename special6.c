#include "headers.h"

void systemcommands(char* command,char** flag3)
{

    int child = fork();

    if (child < 0) 
    {
        perror("fork");
    } 
    else if (child == 0) 
    {
        execvp(command, flag3);
        perror("execvp");
        exit(EXIT_FAILURE);
    } 
    else 
    {
        wait(NULL);
    }
}

// int main() {
//     char *command = "ls"; // Replace with the command you want to run
//     char *args[] = {"ls","-l",NULL}; // Command and its arguments

//     systemcommands(command, args);

//     return 0;
// }