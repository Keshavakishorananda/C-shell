# Description
1. Prompt will display what is User/Systemname and indicate in which user will have control.
2. ";" will execute the commands in a foreground continously. "&" will execute one command in background.
3. ‘warp’ command changes the directory that the shell is currently in. It should also print the full path of working directory after changing. The directory path/name can be provided as argument to this command.
4. ‘peek’ command lists all the files and directories in the specified directories in lexicographic order (default peek does not show hidden files). 
5. ‘pastevents’ command which is similar to the actual history command in bash. Your implementation should store (and output) the 15 most recent command statements given as input to the shell based on some constraints.
6. Shell will be able to execute the other system commands present in Bash as well like emacs, gedit etc. This should be possible in both foreground and background processes.
7. proclore is used to obtain information regarding a process. If an argument is missing, print the information of your shell.
8. 'seek’ command looks for a file/directory in the specified target directory (or current if no directory is specified). It returns a list of relative paths (from target directory) of all matching files/directories (files in green and directories in blue) separated with a newline character.

# Assumptions

1. When we execute peek -l or something related to -l in peek then file permissions will not be   printed as same in actual terminal.
2. Multiple commands seperated with "&"(background process) can't be executed but execute as in case of ";".
3. When I execute pastevents then commands with ";" can't be executed.