/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 13:12:40 by jleblond          #+#    #+#             */
/*   Updated: 2019/07/21 13:12:47 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		lenth(long long n, int base)
{
	int		len;

	len = 0;
	while (n > 0)
	{
		n = n / base;
		len++;
	}
	return (len);
}

static char		*convert(long long nbr, int len, char *ptr, int base)
{
	int			count;

	count = 1;
	while (1)
	{
		ptr[len - count] = nbr % base + (nbr % base > '9' ? 'A' - 10 : '0');
		nbr = nbr / base;
		count++;
		if (nbr == 0)
			break ;
	}
	ptr[len] = '\0';
	return (ptr);
}

char			*ft_itoa_base(int x, int base)
{
	int			len;
	char		*ptr;
	int			neg;
	long long	nbr;

	nbr = x;
	neg = 0;
	if (nbr < 0 && base == 10)
	{
		nbr = -nbr;
		neg = 1;
	}
	len = lenth(nbr, base);
	ptr = (char*)malloc(sizeof(char) * (len + 1));
	if (ptr == 0)
		return (NULL);
	ptr = convert(nbr, len, ptr, base);
	if (neg == 1)
		ptr[0] = '-';
	return (ptr);
}
