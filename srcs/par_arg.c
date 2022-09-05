/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vl-hotel <vl-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:51:51 by lbally            #+#    #+#             */
/*   Updated: 2022/09/05 18:31:19 by vl-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// t_parse	*parser_arg(t_parse *parse, char *line)
// {
// 	int		i;
// 	int		start;
// 	int		len;
// 	char	*cmd;
// 	int		nbr_redi;

// 	i = 0;
// 	start = 0;
// 	len = 0;
// 	nbr_redi = count_pipe(line);
// 	while (line[i])
// 	{
// 		if (line[i] != ' ')
// 		{
// 			if (line[i] == '$')
// 			{
// 				i++;
// 				if (ft_isalnum(line[i]))
// 				{
// 					i++;
// 					if (!ft_isprint(line[i]))
// 						i++;
// 				}
// 			}
// 			else if (line[i] == '>')
// 			{
// 				cmd = get_path_redirection(line, start + 1);
// 				parse = add_redirection(parse, cmd, nbr_redi);
// 				line = sub_path_direction(line, start + 1);
// 				free(cmd);
// 				cmd = NULL;
// 				i = 0;
// 				start = 0;
// 			}
// 			else if (line[i] == '-')
// 			{
// 				len = count_letter(line, start);
// 				cmd = ft_substr(line, start, len);
// 				parse = insert_arg(parse, cmd);
// 			}
// 			else if (line[i] == '|')
// 			{
// 				nbr_redi = count_pipe(line);
// 				last_elem(parse)->pipe = 1;
// 			}
// 			else
// 			{
// 				printf("III ==== %c\n", line[i]);
// 				if (last_elem(parse)->pipe == 1
// 					|| last_elem(parse)-> cmd == NULL)
// 				{
// 					len = count_letter(line, start);
// 					cmd = ft_substr(line, start, len);
// 					i++;
// 				}
// 				else
// 				{
// 					printf("III ==== %c\n", line[i]);
// 					cmd = cut_arg(last_elem(parse), line, i);
// 					line = sub_arg(cmd, start);
// 					i = 0;
// 					start = 0;
// 				}
// 				parse = insert_arg(parse, cmd);
// 			}
// 			while (line[i] && line[i] != ' ')
// 				i++;
// 		}
// 		else
// 		{
// 			i++;
// 			start = i;
// 		}
// 	}
// 	return (parse);
// }
