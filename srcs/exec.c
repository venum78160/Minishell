/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msebbane <msebbane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 12:05:43 by msebbane          #+#    #+#             */
/*   Updated: 2022/09/02 14:57:20 by msebbane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	cmp_cmd(t_parse *parse, t_list *alst, t_exp *atc, int i)
{
	if (!ft_strcmp(parse->cmd, "unset"))
	{
		destroy(parse, &alst, &atc);
		i++;
	}
	else if (!ft_strcmp(parse->cmd, "export"))
	{
		port(parse, atc, alst);
		i++;
	}
	else if (!ft_strcmp(parse->cmd, "$?"))
	{
		dollar2(alst, parse->cmd + 2);
		i++;
	}
	else if (!ft_cmpchar(parse->cmd[0], '$'))
	{
		dollar(alst, parse->cmd + 1);
		i++;
	}
	else if (i == 0)
		printf("%s: command not found\n", parse->cmd);
}

void	check_elem(t_parse *parse, t_list *alst, char **lab)
{
	int	i;

	i = 0;
	while (i < parse->nbr_arg - 1)
	{
		if (parse->cmd != NULL)
		{
			lab[i] = check_path_access(alst, parse->cmd);
			i++;
		}
		if (parse->flag != NULL)
		{
			lab[i] = parse->flag;
			i++;
		}
		if (parse->arg != NULL)
		{
			lab[i] = parse->arg;
			i++;
		}
	}
	lab[i] = NULL;
	i = 0;
}

void	ft_execve(t_parse *parse, t_list *alst, char **lab, char **envp)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid == 0)
	{
		if (execve(check_path_access(alst, parse->cmd), lab, envp) == -1)
			perror("command not found\n");
		putenv_in_tab(alst);
	}
	else if (pid != 0)
	{
		if (!ft_strncmp(parse->cmd, "cd", 2))
			change_dir(parse->arg, alst, parse);
	}
}

void	my_exec(t_parse *parse, char **envp, t_list *alst, t_exp *atc)
{
	int			status;
	char		**lab;	
	t_parse		*elem;
	int			i;

	i = 0;
	elem = parse;
	lab = (char **)malloc(sizeof(char *) * parse->nbr_arg);
	check_elem(elem, alst, lab);
	while (elem)
	{
		if (parse->cmd)
		{
			if (!ft_strcmp(parse->cmd, "env"))
			{
				print_list(alst);
				i++;
			}
		}
		if (parse->cmd && check_path_access(alst, parse->cmd))
		{
			i++;
			ft_execve(elem, alst, lab, envp);
		}
		else
			cmp_cmd(parse, alst, atc, i);
		elem = elem->next;
	}
	wait(&status);
}

char	*check_path_access(t_list *alst, char *cmd)
{
	char	**tab_path;
	char	*path;
	int		i;

	i = -1;
	tab_path = NULL;
	while (alst != NULL)
	{
		if (!strcmp(alst->key, "PATH"))
		{
			tab_path = ft_split(alst->content, ':');
			break ;
		}
		alst = alst->next;
	}
	while (tab_path[++i])
	{
		if (!back_slash(tab_path[i]))
		{
			path = ft_strjoin(tab_path[i], "/");
			path = ft_strjoin(path, cmd);
		}
		if (!access(path, F_OK))
			return (path);
		else
			path = ft_strjoin(tab_path[i], cmd);
	}
	return (NULL);
}
