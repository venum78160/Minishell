/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vl-hotel <vl-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 12:23:58 by lbally            #+#    #+#             */
/*   Updated: 2022/09/05 18:28:35 by vl-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_exp(t_exp *atc)
{
	t_exp	*lala;

	lala = atc;
	while (lala)
	{
		if (!ft_strcmp(lala->mean, "(null)"))
			printf("declare -x %s \n", lala->name);
		else
			printf("declare -x %s=\"%s\" \n", lala->name, lala->mean);
		lala = lala->next;
	}
}

void	print_list(t_list *alst)
{
	while (alst)
	{
		printf("%s=%s \n", alst->key, alst->content);
		alst = alst->next;
	}
}

// void	print_arg(t_parse *parse)
// {
// 	t_parse	*tac;
// 	int		i;
// 	int		j;

// 	tac = parse;
// 	i = 0;
// 	j = -1;
// 	while (tac)
// 	{
// 		printf("cmd%d ===>%s\n", i, tac->cmd);
// 		if (tac->flag != NULL)
// 			printf("option%d ===>%s\n", i, tac->flag);
// 		if (tac->arg != NULL)
// 			printf("arg%d ===>[%s]\n", i, tac->arg);
// 		if (tac->dir != NULL)
// 		{
// 			while (tac->dir[++j])
// 				printf("command%d-> redirec:[%d] ==>%s\n", i, j, tac->dir[j]);
// 			j = -1;
// 		}
// 		if (tac->pipe)
// 			printf("pipe[%d] existant = [%d]\n", i, tac->pipe);
// 		i++;
// 		tac = tac->next;
// 	}
// }
