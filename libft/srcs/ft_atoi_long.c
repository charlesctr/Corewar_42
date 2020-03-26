/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <jleblond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 13:52:21 by naali             #+#    #+#             */
/*   Updated: 2020/03/02 09:16:14 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "./libft.h"

static void		init_var(int *i, long int *ret, long int *neg)
{
	*i = 0;
	*ret = 0;
	*neg = 1;
}

long int		ft_atoi_long(const char *str)
{
	int				i;
	long int		ret;
	long int		old;
	long int		neg;

	init_var(&i, &ret, &neg);
	while (((str[i] <= 13) && (str[i] >= 9)) || (str[i] == 32))
		i++;
	if ((str[i] == '+') || (str[i] == '-'))
	{
		if (str[i] == '-')
			neg = -neg;
		i++;
	}
	while ((str[i] != 0) && (str[i] >= '0') && (str[i] <= '9'))
	{
		old = ret;
		ret = ret * (long)10 + (long)(str[i] - '0');
		if (ret < old && neg == 1)
			return (LONG_MAX);
		else if (ret < old && neg == -1)
			return (LONG_MIN);
		i++;
	}
	return (ret * neg);
}
