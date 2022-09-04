/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbally <lbally@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 12:23:26 by lbally            #+#    #+#             */
/*   Updated: 2022/08/05 09:50:11 by lbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*cut_arg(t_parse *parse, char *line, int i)
{
	int		start;
	char	*cmd;
	int		q;

	q = 0;
	cmd = NULL;
	(void)parse;
	start = i;
	while (line[i])
	{
		if (line[i] == '>' || line[i] == '|')
		{
			i = i - 1;
			break ;
		}
		else
			i++;
	}
	cmd = ft_substr(line, start, i);
	return (cmd);
}

char	*sub_arg(char *line, int i)
{
	char	*new_line;
	int		q;

	q = 0;
	new_line = NULL;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
			q++;
		if (line[i] == '>' || line[i] == '|')
		{
			i = i - 1;
			break ;
		}	
		i++;
	}
	i = i - q;
	new_line = ft_substr(line, i, ft_strlen(line));
	return (new_line);
}
