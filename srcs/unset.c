/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbally <lbally@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 11:18:59 by lbally            #+#    #+#             */
/*   Updated: 2022/08/30 18:45:42 by lbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	destroy(t_parse *parse, t_list **alst, t_exp **atc)
{
	t_list	*head;
	t_list	*temp;
	t_parse	*elem;
	t_exp	*head2;
	t_exp	*temp2;

	head = *alst;
	head2 = *atc;
	elem = parse;
	if (elem->arg == NULL)
		perror("unset");
	while (*alst)
	{
		if ((*alst)->next && !ft_strcmp((*alst)->next->key, elem->arg))
		{
			free((*alst)->next->content);
			free((*alst)->next->key);
			temp = (*alst)->next;
			(*alst)->next = (*alst)->next->next;
			free(temp);
			*alst = head;
			break ;
		}
		(*alst) = (*alst)->next;
	}
	while (*atc)
	{
		if ((*atc)->next && !ft_strcmp((*atc)->next->name, elem->arg))
		{
			free((*atc)->next->mean);
			free((*atc)->next->name);
			temp2 = (*atc)->next;
			(*atc)->next = (*atc)->next->next;
			free(temp2);
			*atc = head2;
			break ;
		}
		(*atc) = (*atc)->next;
	}
}
