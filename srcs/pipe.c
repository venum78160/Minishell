/*
	int         pipe_fd[2];
	int         pipe_fd1[2];
	char *argv[] = {check_path_access(alst, parse->cmd), parse->flag ,NULL};
 
   if (pipe(pipe_fd) == -1)
   perror("pipe");
   if ((pid = fork()) == -1)
   perror("fork");
   else if (pid == 0)
   {
   close(pipe_fd[0]);
   if (dup2(pipe_fd[1], 1) == -1)
   perror("dup2");
//argv = { check_path_access(alst, elem->cmd), parse->flag, NULL };
else if (if ((pid = fork()) == -1)
perror("fork");
else if (pid == 0)
{
if (execve(check_path_access(alst,parse->cmd ), argv, envp) == -1)
perror("execve");
}execve(check_path_access(alst,parse->cmd), argv, envp) == -1)
perror("execve");
}
else
{
char      buffer[1024];
int       ret;
close(pipe_fd[1]);
pipe(pipe_fd1);
pid = fork();

if (pid == 0)
{
elem = elem->next;
close(pipe_fd1[0]);
dup2(pipe_fd[0], 0);
close(pipe_fd[0]);

dup2(pipe_fd1[1], 1);
close(pipe_fd1[1]);
//argv = {check_path_access(alst, elem->cmd), parse->flag, NULL}; 
if (execve(check_path_access(alst,parse->cmd), argv, envp) == -1)
perror("execve:");
}
else
{
close(pipe_fd1[1]);
while ((ret = read(pipe_fd1[0], buffer, 1023)) != 0)
{
buffer[ret] = 0;
printf("buff = %s\n", buffer);
}

}
}
close(pipe_fd1[0]);
wait(&status);
*/
