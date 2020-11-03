# Minishell
42 project of writing own simple shell. 

</br>

## Requirements
* Every new line should begin with the prompt
* Search and launch the right executable (based on the PATH variable or by using relative or absolute path) like in bash
* Must implement the builtins like in bash:
	* **echo** with option ’-n’
	* **cd** with only a relative or absolute path
	* **pwd** without any options
	* **export** without any options
	* **unset** without any options
	* **env** without any options and any arguments
	* **exit** without any options
* **;** in the command should separate commands like in bash
* **’** and **"** should work like in bash except for multiline commands
* Redirections **< > “>>”** should work like in bash except for file descriptor aggregation
* Pipes **|** should work like in bash
* Environment variables (**$** followed by characters) should work like in bash
* **$?** should work like in bash
* **ctrl-C**, **ctrl-D** and **ctrl-\\** should have the same result as in bash

</br>

## Some external C-funcs

| Description | Function |
| --- | --- |
| Path of the current directory | dir = getcwd(NULL, 0) |
| Change current directory to "sd" | chdir("sd") |
| Copy file descriptor fd to STDOUT_FILENO and save to fd2 | fd2 = dup2(fd, STDOUT_FILENO) |
| Execute the program specified by the first parameter | execve("/sbin/ping", NULL, NULL) |
| Find out file info and write it to the struct stat buff | stat("includes/minishell.h", &buff) |
| Create tunnel to read fd[0] write fd[1] | pipe(fd) |
