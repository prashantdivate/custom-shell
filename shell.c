#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	char cmd[512];
	char *ptr;
	char *args[32];
	int i, pid, s, err;
	while(1)
	{
		// input command from user
		printf("cmd> ");
		gets(cmd);
		// convert command string into array of char* (cmd line args array)
		i = 0;
		ptr = strtok(cmd, " ");
		args[i++] = ptr;
		do {
			ptr = strtok(NULL, " ");
			args[i++] = ptr;
		} while(ptr != NULL);
		// check if command is internal and if so implement its logic.
		if(strcmp(args[0], "exit") == 0)
			break;
		else if(strcmp(args[0], "cd") == 0)
			chdir(args[1]);
		else
		{
			// execute the external command using fork() + exec()
			pid = fork();
			if(pid == 0)
			{
				err = execvp(args[0], args);
				if(err < 0)
				{
					perror("bad command");
					_exit(1);
				}
			}
			waitpid(-1, &s, 0);
		}
	}
	printf("bye!\n");
	return 0;
}
