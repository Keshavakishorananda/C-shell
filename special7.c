#include "headers.h"

#define LENGTH 1024

void proclore(const char *pid_str)
{
    char* proc_path = (char*)malloc(1024);
    snprintf(proc_path, sizeof(proc_path), "/proc/%s", pid_str);


    printf("Process ID: %s\n", pid_str);

    char* path2status = (char*)malloc(1024);
    snprintf(path2status, sizeof(path2status), "%s/status", proc_path);
    FILE *status_file = fopen(path2status, "r");
    if (status_file) 
    {
        char line[256];
        while (fgets(line, sizeof(line), status_file)) {
            if (strncmp(line, "State:", 6) == 0) {
                printf("Process Status: %s", line + 7);
                break;
            }
        }
        fclose(status_file);
    }
    free(path2status);

    printf("Process Group: ");
    char* path2cmd = (char*)malloc(1024);
    snprintf(path2cmd, sizeof(path2cmd), "%s/stat", proc_path);
    FILE *cmd_file = fopen(path2cmd, "r");
    if (cmd_file) 
    {
        int pid, ppid, pgrp, session, tty_nr;
        char comm[256];
        fscanf(cmd_file, "%d %s %s %d %d %d %d", &pid, comm, comm, &ppid, &pgrp, &session, &tty_nr);
        fclose(cmd_file);
        printf("%d\n", pgrp);
    }
    free(path2cmd);


    char* path2statm = (char*)malloc(1024);
    snprintf(path2statm, sizeof(path2statm), "%s/statm", proc_path);

    FILE *statm_file = fopen(path2statm, "r");
    if (statm_file) 
    {
        unsigned long vm_size, vm_resident, vm_share;
        fscanf(statm_file, "%lu %lu %lu", &vm_size, &vm_resident, &vm_share);
        fclose(statm_file);
        printf("Virtual Memory Size: %lu KB\n", vm_size);
    }
    free(path2statm);


    char* path2exe = (char*)malloc(1024);
    snprintf(path2exe, sizeof(path2exe), "%s/exe", proc_path);

    char executable[LENGTH];
    ssize_t length = readlink(path2exe, executable, sizeof(executable));
    if (length != -1) 
    {
        executable[length] = '\0';
        printf("Executable Path: a.out\n");
    } 
    else 
    {
        printf("Executable Path: Unknown\n");
    }
    free(path2exe);
}