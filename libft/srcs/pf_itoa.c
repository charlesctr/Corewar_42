/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 14:35:03 by jleblond          #+#    #+#             */
/*   Updated: 2019/08/21 14:35:06 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		lenth(long long n)
{
	int		len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static char		*convert(long long n, int len, char *ptr)
{
	int			count;

	count = 1;
	ptr[len] = '\0';
	while (1)
	{
		ptr[len - count] = n % 10 + '0';
		n = n / 10;
		count++;
		if (n == 0)
			break ;
	}
	return (ptr);
}

char			*ft_itoa(long long x)
{
	int			len;
	char		*ptr;
	int			neg;

	if (x == (-9223372036854775807) - 1)
		return (ft_strdup("-9223372036854775808"));
	len = lenth(x);
	ptr = (char*)malloc(sizeof(char) * (len + 1));
	if (ptr == 0)
		return (NULL);
	neg = 0;
	if (x < 0)
	{
		x = -x;
		neg = 1;
	}
	ptr = convert(x, len, ptr);
	if (neg == 1)
		ptr[0] = '-';
	return (ptr);
}

void			pf_itoa_base(uintmax_t nbr, int base, t_unit *unit,
							char *str)
{
	int		posi;
	char	buf[50];

	posi = 49;
	buf[posi] = '\0';
	if (nbr == 0)
	{
		posi--;
		buf[posi] = '0';
	}
	while (nbr > 0)
	{
		posi--;
		if (base == 16 && unit->val.oxx.sub_type == TYPE_X_MAJ)
			buf[posi] = nbr % base + ((nbr % base < 10) ? '0' : 'A' - 10);
		else
			buf[posi] = nbr % base + ((nbr % base < 10) ? '0' : 'a' - 10);
		nbr = nbr / base;
	}
	ft_strcpy(str, buf + posi);
}
