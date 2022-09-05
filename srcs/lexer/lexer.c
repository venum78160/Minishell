/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vl-hotel <vl-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:17:43 by vl-hotel          #+#    #+#             */
/*   Updated: 2022/09/05 13:55:17 by vl-hotel         ###   ########.fr       */
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

char *nextword(char *line,int *j)
{
	int i;
	int start;
	i = 0;
	while(line[i] && ft_isalnum(line[i]) == 0)
		i++;
	start = i;
	while(line[i] && ft_isalnum(line[i]) == 1)
		i++;
	*j = i;
	return (ft_strncpy(line + start, i));
}

char	*ft_strncpy(char *s, int j)
{
	int		i;
	char	*str;

	i = 0;
	if (s == NULL || j == 0)
		return (NULL);
	str = malloc(sizeof(char) * j + 1);
	while (s[i] && i <= j)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
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

int	ft_flag(char *line, int i, t_parse *parse)
{
	// si un flag existe deja, je le rajoute.
	int	j;
	while(line[i] == '-')
		i++;
	j = i;
	if(parse->flag == NULL)
	{
		parse->flag = ft_strjoin_no_spc("-", nextword(line + i, j));
	}
	else
	{
		parse->flag = ft_strjoin_no_spc(parse->flag, nextword(line + i, j));
		// faire strjoin en oubliant pas de free.
	}
	return (j);
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

t_parse	*ft_lstnew_parse()
{
	t_parse	*newlist;

	newlist = malloc(sizeof(t_parse));
	if (!newlist)
		return (NULL);
	newlist->first = 0;
	newlist->i = 0;
	newlist->next = NULL;
	return (newlist);
}

char	*ft_strjoin_no_spc(const char *s1, char *s2)
{
	char	*str;
	int		slen;
	int		i;
	int		j;

	if (s1 == 0 || s2 == 0)
		return (NULL);
	slen = ft_strlen((char *)s1) + ft_strlen(s2);
	i = -1;
	j = -1;
	if (!(str = malloc(sizeof(char) * slen + 1)))
		return (NULL);
	while (s1[++i])
		str[i] = s1[i];
	while (s2[++j])
		str[i++] = s2[j];
	str[i] = '\0';
	free (s1);
	return (str);
}

void	lexer(char *line)
{
	int		i;
	t_parse	*tete;
	
	i = 0;
	tete = g_global.parse;
	while (line[i])
	{
		while ((line[i] && (line[i] == ' '|| line[i] == '\t')))
			i++;
		i = redirection_v(line, i, tete);
		// next_word();
		if (line[i] == '-')
		{
			i = ft_flag(line, i, tete);
		}
		if (line[i] == '|')
		{
			// pipe
		}
		else
		{
			// command et argument.
			// mettre dans un tableau.
			// voir realloc.
		}
		
	}
}