/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vl-hotel <vl-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:09:48 by vl-hotel          #+#    #+#             */
/*   Updated: 2022/09/06 22:33:14 by vl-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *nextword(char *line,int *j)
{
	int i;
	int start;
	i = 0;
	while(line[i] && ft_isalnum(line[i]) == 0)
		i++;
	start = i;
	while(line[i] && ft_isalnum(line[i]) == 1)
	{
		i++;
	}
	*j += i;
	return (ft_strncpy(line + start, i - start));
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
	free ((void *)s1);
	return (str);
}

char	*ft_strncpy(char *s, int j)
{
	int		i;
	char	*str;

	i = 0;
	if (s == NULL || j == 0)
		return (NULL);
	str = malloc(sizeof(char) * j + 1);
	while (s[i] && i < j)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	print_global()
{
	int i;
	t_parse	*tete;
	int	count;
	
	i = 0;
	count = 0;
	printf("debut de print global\n");
	tete = g_global.parse;
	while (tete)
	{
		printf("\nParse numero %i\n", count);
		printf("cmd = %s, flag = %s\n", tete->cmd, tete->flag);
		printf("infile = %i, outfile = %i\n", tete->infile, tete->outfile);
		while (tete->arg && tete->arg[i])
		{
			printf("argument n: %i = %s\n", i, tete->arg[i]);
			i++;
		}
		tete = tete->next;
		count++;
	}
}