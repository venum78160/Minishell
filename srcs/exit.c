/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbally <lbally@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 11:33:10 by lbally            #+#    #+#             */
/*   Updated: 2022/08/31 14:42:52 by lbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_num(char *lala)
{
	int	i;

	i = 0;
	while (lala[i])
	{
		if (lala[i] < '0' || lala[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char *lala)
{
	int	lolo;
	int	i;

	i = 0;
	printf("exit\n");
	if (lala)
	{
		if (!ft_num(lala))
			printf("exit: %s: numeric argument required\n", lala);
		else
		{
			lolo = ft_atoi(lala);
			i = lolo % 256;
			printf("IIII ====== %d\n", i);
			exit(EXIT_SUCCESS);
		}
	}
	exit(EXIT_SUCCESS);
}
