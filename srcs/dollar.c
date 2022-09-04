/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msebbane <msebbane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 11:26:14 by lbally            #+#    #+#             */
/*   Updated: 2022/09/01 14:31:24 by msebbane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	dollar(t_list *alst, char *str)
{
	t_list	*list;

	list = alst;
	if (!str[1])
		printf(" $: command not found\n");
	while (list)
	{
		if (!ft_strcmp(str, list->key))
			printf("%s: is a directory\n", list->content);
		list = list->next;
	}
}
//$? == 0 command not found (command reussie)
// == 1 non reussie
// == 127 existe pas
void	dollar2(t_list *alst, char *str)
{
	t_list	*list;

	list = alst;
	if (!check_path_access(alst, str))
		printf(" 127: command not found\n");
	else if (check_path_access(alst, str))
		printf(" 0: command not found\n");
	//while (list)
	//{
		//if (!ft_strcmp(str, list->key))
			//printf("0: command not found");
		//list = list->next;
	//}
}
