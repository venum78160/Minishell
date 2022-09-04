/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 12:30:32 by lbally            #+#    #+#             */
/*   Updated: 2022/07/22 12:30:34 by lbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int			ft_itoa_size(int n)
{
	int				size;
	int				neg;

	size = 0;
	neg = 0;
	if (n < 0 && n > -2147483648)
	{
		neg = 1;
		size++;
		n = -n;
	}
	else if (n == 0)
		return (1);
	else if (n == -2147483648)
		return (11);
	while (n >= 1)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char				*ft_itoa(int n)
{
	char			*str;
	int				i;
	int				size;
	int				neg;
	unsigned int	tmp;

	size = ft_itoa_size(n);
	neg = (n < 0 ? 1 : 0);
	i = 1;
	if (!((str = (char *)malloc(sizeof(char) * size + 1))))
		return (NULL);
	tmp = (n < 0 ? -n : n);
	if (tmp == 0)
		str[tmp] = '0';
	while (tmp >= 1)
	{
		str[size - i] = (tmp % 10) + '0';
		tmp /= 10;
		i++;
	}
	if (neg)
		*str = '-';
	str[size] = '\0';
	return (str);
}
