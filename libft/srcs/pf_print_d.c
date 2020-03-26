/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_print_d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 18:13:40 by jleblond          #+#    #+#             */
/*   Updated: 2019/07/17 18:13:42 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned int		d_precision_handler(char *s, char *integer,
												int preci, t_unit *unit)
{
	int		neg;
	int		dy_len;

	if (unit->val.d.integer == 0 && preci == PRECISION_NULL)
		return (0);
	dy_len = ft_strlen(integer);
	if (dy_len > preci)
		ft_strcpy(s, integer);
	else
	{
		neg = ((*integer == '-') ? 1 : 0);
		s[preci + neg] = '\0';
		ft_memset(s, '0', preci + neg);
		if (neg == 1)
			s[0] = '-';
		ft_strncpy(s + preci + neg - dy_len + neg,
			integer + neg, dy_len - neg);
		dy_len = preci + neg;
	}
	return (dy_len);
}

static void				sub_d_width_handler(char *s, int dy_len,
										t_unit *unit, int width)
{
	char	s_keep[dy_len + 1];
	int		mark;

	ft_strcpy(s_keep, s);
	mark = 0;
	if (unit->val.d.flag_zero == TRUE && unit->val.d.precision == 0)
	{
		ft_memset(s, '0', width);
		if (*s_keep == '-' || *s_keep == '+' || *s_keep == ' ')
		{
			s[0] = s_keep[0];
			mark = 1;
		}
		ft_strncpy(s + width + mark - dy_len, s_keep + mark, dy_len - mark);
	}
	else
	{
		ft_memset(s, ' ', width);
		ft_strncpy(s + width - dy_len, s_keep, dy_len);
	}
}

/*
**		flag '0' is ignored when flag '-' or precision present"
*/

static unsigned int		d_width_handler(char *s, int dy_len,
									t_unit *unit, int width)
{
	if (width <= dy_len)
		return (dy_len);
	if (unit->val.d.flag_minus == TRUE)
		ft_memset(s + dy_len, ' ', width - dy_len);
	else
		sub_d_width_handler(s, dy_len, unit, width);
	return (width);
}

/*
** 		flag ' ' is ignored when flag '+' is present"
*/

static unsigned int		d_flag_plus_and_blank(char *s, int dy_len, t_unit *unit)
{
	unsigned int	i;

	if (unit->val.d.flag_plus == FALSE && unit->val.d.flag_blank == FALSE)
		return (dy_len);
	i = dy_len + 1;
	while (i > 0)
	{
		s[i] = s[i - 1];
		i--;
	}
	if (unit->val.d.flag_plus == TRUE)
		s[0] = '+';
	else if (unit->val.d.flag_blank == TRUE)
		s[0] = ' ';
	return (dy_len + 1);
}

/*
** 		dy_len is initialted at the lenth of integer,
**		it will change depending on precision, width, then flags
*/

int						print_d(int fd, t_unit *unit)
{
	char			*integer;
	unsigned int	dy_len;
	char			s[unit->val.d.precision + unit->val.d.width + 30];

	ft_memset(s, 0, unit->val.d.precision + unit->val.d.width + 30);
	integer = ft_itoa(unit->val.d.integer);
	dy_len = d_precision_handler(s, integer, unit->val.d.precision, unit);
	free(integer);
	integer = NULL;
	if (unit->val.d.integer >= 0)
		dy_len = d_flag_plus_and_blank(s, dy_len, unit);
	dy_len = d_width_handler(s, dy_len, unit, unit->val.d.width);
	write(fd, s, dy_len);
	return (dy_len);
}
