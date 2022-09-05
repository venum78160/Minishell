/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vl-hotel <vl-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:11:15 by vl-hotel          #+#    #+#             */
/*   Updated: 2022/09/05 15:15:08 by vl-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_file(int fd, int i, t_parse *parse)
{
	if (i = 2)
	{
		if (parse->infile == NULL)
			parse->infile = fd;
		else
		{
			close(parse->infile);
			parse->infile = fd;
		}
	}
	else
	{
		if (parse->outfile == NULL)
			parse->outfile = fd;
		else
		{
			close(parse->outfile);
			parse->outfile = fd;
		}
	}
}

void	open_file(char *str, int i, t_parse *parse)
{
	int	file;
	file = 0;
	
	file = open(str, O_DIRECTORY, O_RDONLY);
	if (file != -1)
	{
		ft_putstr_fd("it's a folder and not a file\n", 1);
		exit(1);
	}
	close(file);
	if (i == 0)
	{
		file = open(str, O_WRONLY | O_CREAT | O_APPEND, 0777);
	}
	else if (i == 1)
		file = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
	{
		file = open(str, O_RDONLY, 0777);
		if (file == -1)
		msg_error("ce fichier n'existe pas");
	}
	if (file == -1)
		msg_error("ouverture file");
	free(str);
	init_file(file, i, parse);
}

int	redirection_v(char *line, int i, t_parse *parse)
{
	int j;
	
	j = i;
	if (line[i] == '>' && line[i + 1] == '>')
	{
		// append
		open_file(nextword(line + i, &j), 0, parse);
	}
	else if (line[i] == '>' && line[i + 1] != '>')
	{
		// trunc
		open_file(nextword(line + i, &j), 1, parse);
	}
	else if (line[i] == '<' && line[i + 1] == '<')
	{
		// heredoc
	}
	else if (line[i] == '<' && line[i + 1] != '<')
	{
		// infile
		open_file(nextword(line + i, &j), 2, parse);
	}
	return (j);
}