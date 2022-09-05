/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vl-hotel <vl-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:17:43 by vl-hotel          #+#    #+#             */
/*   Updated: 2022/09/05 17:17:08 by vl-hotel         ###   ########.fr       */
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

int	ft_flag(char *line, int i, t_parse *parse)
{
	// si un flag existe deja, je le rajoute.
	int	j;
	while(line[i] == '-')
		i++;
	j = i;
	parse->flag = ft_strjoin_no_spc(parse->flag, nextword(line + i, &j));
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
	newlist->flag = ft_strncpy("-", 1);
	newlist->arg = malloc(sizeof(char *));
	newlist->arg = NULL;
	return (newlist);
}

char *ft_realloc2char(char **src, int size)
{
	char **dest;
	int		i;
	
	i = 0;
	if (src == NULL)
		return (NULL);
	dest = ft_calloc(sizeof(char *), size + 1);
	while (i < size)
	{
		ft_memcpy(dest[i], src[i], ft_strlen(src[i]));
		i++;
	}
	free_tab(src);
	free(src);
	return (dest);
}

int	ft_cmd_arg(char *line, int i, t_parse *tete)
{
	int j;
	
	j = i;
	if (tete->first == 0)
	{
		tete->cmd = ft_strdup(nextword(line + i, &j));
		tete->first++;
	}
	else
	{
		tete->arg = ft_realloc2char(tete->arg, len_envp(tete->arg) + 1);
		ft_memcpy(tete->arg[len_envp(tete->arg) - 1], nextword(line + i, &j), ft_strlen(nextword(line + i, &j)));
	}
	return (j);
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
			i++;
			//  pipe
		}
		else
		{
			i = ft_cmd_arg(line, i, tete);
		}
	}
}