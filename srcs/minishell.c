/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vl-hotel <vl-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 12:26:07 by lbally            #+#    #+#             */
/*   Updated: 2022/09/05 23:59:39 by vl-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

struct s_global	g_global;

char	*rl_gets(void)
{
	static char	*line_read;

	if (line_read)
	{
		free (line_read);
		line_read = (char *) NULL;
	}
	line_read = readline ("minishell>> ");
	if (line_read && *line_read)
		add_history (line_read);
	return (line_read);
}

void	line_prompt(char *line, char **argv)
{
	if (!line)
		signal_exit();
	line = ft_strtrim(line, " ");
	argv = ft_split(line, ' ');
}

void	init_global(void)
{
	g_global.parse = malloc(sizeof(t_parse));
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_exp	*atc;
	t_list	*alst;

	alst = NULL;
	(void) ac;
	(void) av;
	insert_env(envp, &alst);
	insert_exp(envp, &atc);
	signals();
	while (1)
	{
		line = rl_gets();
		line_prompt(line, av);
		g_global.parse = malloc(sizeof(t_parse));
		// init_global;
		lexer(line);
		printf("end lexer\n");
		exit(0);
		print_global();
		// if (parse->cmd)
		// {
		// 	if (!ft_strcmp(parse->cmd, "exit"))
		// 		ft_exit(parse->arg);
		// 	my_exec(parse, envp, alst, atc);
		// }
		// print_arg(parse);
		// free(parse);
		exit(0);
	}
}

/*
A FIX :
-simple quote et double quote + avec echo (a faire)
	bash-3.2$ echo 'PATH'
	PATH
	bash-3.2$ echo '$PATH'
	$PATH
	bash-3.2$ echo "$PATH"
	/Users/msebbane/.brew/bin:/Users/msebbane/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki
- $?
- bash-3.2$ cat + ctrl \ doit afficher = ^\Quit: 3
- Mettre un int pour reperer tous les $ status (127, 0, 1)
*/