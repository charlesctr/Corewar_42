/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aatoii.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 09:07:20 by jleblond          #+#    #+#             */
/*   Updated: 2020/02/25 13:54:50 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		*ft_aatoii(char **pptr)
{
	int		x;
	int		*tab;

	x = 0;
	while (pptr[x] != 0)
	{
		x++;
	}
	if (x == 0)
		return (0);
	tab = (int*)malloc(x * sizeof(int));
	if (tab == NULL)
		return (0);
	x = 0;
	while (pptr[x] != 0)
	{
		tab[x] = ft_atoi(pptr[x]);
		x++;
	}
	return (tab);
}
