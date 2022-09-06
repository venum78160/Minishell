/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vl-hotel <vl-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:17:43 by vl-hotel          #+#    #+#             */
/*   Updated: 2022/09/06 22:58:09 by vl-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	int		j;
	char	*nextw;
	
	while(line[i] == '-')
		i++;
	j = i;
	nextw = nextword(line + i, &j);
	printf("[flag] valeur nextw |%s|\n", nextw);
	parse->flag = ft_strjoin_no_spc(parse->flag, nextw);
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
	newlist->infile = 0;
	newlist->outfile = 1;
	newlist->fd_kill = 0;
	newlist->next = NULL;
	newlist->flag = ft_strncpy("-", 1);
	newlist->arg = malloc(sizeof(char *));
	newlist->arg[0] = NULL;
	newlist->cmd = NULL;
	return (newlist);
}

char **ft_realloc2char(char **src, int size)
{
	char **dest;
	int		i;
	
	i = 0;
	if (src == NULL)
		return (NULL);
	dest = ft_calloc(sizeof(char *), size + 1);
	printf("dans le realloc, size = %i\n", size);
	while (i < size)
	{
		printf("realloc %i et size = %i\n", i, size);
		dest[i] = ft_calloc(sizeof(char), (ft_strlen(src[i]) + 1));
		ft_memcpy(dest[i], src[i], ft_strlen(src[i]));
		i++;
	}
	free_tab(src);
	free(src);
	printf("end realloc\n");
	return (dest);
}

int	ft_cmd_arg(char *line, int i, t_parse *tete)
{
	int j;
	char *nextw;
	
	j = i;
	nextw = nextword(line + i, &j);
	printf("resultat nextword = %s\n", nextw);
	if (tete->first == 0)
	{
		printf("command\n");
		// printf("resultat nextword = %s\n", nextword(line + i, &j));
		// tete->cmd = nextword(line + i, &j);
		tete->cmd = nextw;
		printf("cmd = %s\n", tete->cmd);
		tete->first++;
	}
	else
	{
		printf("argument\n");
		tete->arg = ft_realloc2char(tete->arg, len_envp(tete->arg) + 1);
		printf("apres le realloc, \n");
		// printf("resultat nextword = %s\n", nextw);
		ft_memcpy(tete->arg[len_envp(tete->arg) - 1], nextw, ft_strlen(nextw));
	}
	return (j);
}

void	ft_lstadd_back_parse(t_parse **alst, t_parse *new)
{
	t_parse	*tmp;

	if (!*alst)
		*alst = new;
	else
	{
		tmp = (t_parse *)ft_lstlast((t_list *)*alst);
		tmp->next = new;
	}
}

void	lexer(char *line)
{
	int		i;
	t_parse	*tete;
	
	i = 0;
	g_global.parse = ft_lstnew_parse();
	tete = g_global.parse;
	while (line[i])
	{
		printf("valeur de i = %i, = %c\n", i, line[i]);
		while ((line[i] && (line[i] == ' '|| line[i] == '\t')))
			i++;
		if (ft_strchr("><", line[i]) != NULL)
			i = redirection_v(line, i, tete);
		// next_word();
		else if (line[i] == '-')
		{
			printf("debut des flags\n");
			i = ft_flag(line, i, tete);
		}
		else if (line[i] == '|')
		{
			printf("debut des pipes\n");
			i++;
			ft_lstadd_back_parse(&g_global.parse, ft_lstnew_parse());
			tete = (t_parse *)ft_lstlast((t_list *)g_global.parse);
			//  pipe
		}
		else
		{
			printf("debut des cmd et arguments\n");
			i = ft_cmd_arg(line, i, tete);
		}
	}
}