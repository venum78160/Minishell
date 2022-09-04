/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vl-hotel <vl-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:17:43 by vl-hotel          #+#    #+#             */
/*   Updated: 2022/09/02 18:38:48 by vl-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	msg_error(char *err)
{
	perror(err);
	exit (1);
}

int	count_pipe_v(char *line)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (line[i] )
	{
		if (line[i] == '|')
			size++;
		i++;
	}
	return (size);
}

void	init_file(int fd, int i, t_parse *parse)
{
	if (i = 2)
	{
		if (t_parse.infile == NULL)
			t_parse.infile = fd;
		else
		{
			close(t_parse.infile);
			t_parse.infile = fd;
		}
	}
	else
	{
		if (t_parse.outfile == NULL)
			t_parse.outfile = fd;
		else
		{
			close(t_parse.outfile);
			t_parse.outfile = fd;
		}
	}
}

int	open_file(char *str, int i, t_parse *parse)
{
	int	file;
	// proteger les directory
	file = 0;
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
	return (file);
}

char *nextword(char *line)
{
	int i;
	int start;
	i = 0;
	while(line[i] || ft_isalnum(line[i]) == 0)
		i++;
	start = i;
	while(line[i] ft_isalnum(line[i]) == 1))
		i++;
	return (ft_strncpy(line + start, i));
}

char	*ft_strncpy(char *s, int j)
{
	int	i;

	i = 0;
	if (s == NULL || j == 0)
		return ();
	str = malloc(sizeof(char) * j + 1);
	while (s[i] && i <= j)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char *redirection_v(char *line, int i, t_parse *parse)
{
	if (line[i] == '>' && line[i + 1] == '>')
	{
		// append
		open_file(nextword(line + i), 0);
	}
	else if (line[i] == '>' && line[i + 1] != '>')
	{
		// trunc
		open_file(nextword(line + i), 1);
	}
	else if (line[i] == '<' && line[i + 1] == '<')
	{
		// heredoc
	}
	else if (line[i] == '<' && line[i + 1] != '<')
	{
		// infile
		open_file(nextword(line + i), 2);
	}
}

int	ft_flag(char *line,int i);
{
	// si un flag existe deja, je le rajoute.
	while(line[i] == '-')
		i++;
	if(parse->flag == NULL)
	{
		parse->flag = nextword(line);
	}
	else
		parse->flag = nextword(line) 
		// faire strjoin en oubliant pas de free.

}

t_parse	*ft_lstmove(t_parse *lst, int indice)
{
	int	s;

	if (lst)
	{
		s = 1;
		while (s < indice)
		{
			lst = lst->next;
			s++;
		}
	}
	return (lst);
}

void	lexer(char *line)
{
	int	i;
	g_global.parse
	while (line[i])
	{
		if (line[i] == ' '|| line[i] == '\t')
			i++;
		i = redirection_v(line, i);
		if (line[i] == '-')
		{
			ft_flag();
		}
		if (line[i] == '|')
		{
			// pipe
		}
		
	}
}