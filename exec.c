#include "minishell.h"

static  char    **temp_parse(char *line)
{
    return (ft_split(line, ' '));
}

void exec_line(char *line, char **envp)
{
    char    **args;
    pid_t   pid;
    int     status;

    args = temp_parse(line);
    if (args[0] == NULL)
    {
        free(args);
        return ;
    }
    pid = fork();
    if (pid == 0)
    {
        if (execve(args[0], args, envp) == -1)
        {
            perror("minishell: execve error");
            exit(EXIT_FAILURE);
        }
    }
    else if (pid < 0)
    {
        perror("minishell: fork error");
    }
    else
    {
        waitpid(pid, &status, 0);
    }
    free(args);
}

