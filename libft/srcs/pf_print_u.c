/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_print_u.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 13:36:35 by jleblond          #+#    #+#             */
/*   Updated: 2019/07/27 13:36:39 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned int		u_precision_handler(char *s, char *str_uint,
									int precision, t_unit *unit)
{
	int		dy_len;

	if (unit->val.u.un_int == 0 && precision == PRECISION_NULL)
		return (0);
	dy_len = ft_strlen(str_uint);
	if (dy_len > precision)
		ft_strcpy(s, str_uint);
	else
	{
		s[precision] = '\0';
		ft_memset(s, '0', precision);
		ft_strncpy(s + precision - dy_len, str_uint, dy_len);
		dy_len = precision;
	}
	return (dy_len);
}

static void				sub_u_width_handler(char *s, int dy_len,
										t_unit *unit, int width)
{
	char	s_keep[dy_len + 1];

	ft_strcpy(s_keep, s);
	if (unit->val.u.flag_zero == TRUE && unit->val.u.precision == 0)
	{
		ft_memset(s, '0', width);
		ft_strncpy(s + width - dy_len, s_keep, dy_len);
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

static unsigned int		u_width_handler(char *s, int dy_len, t_unit *unit,
										int width)
{
	if (width <= dy_len)
		return (dy_len);
	if (unit->val.u.flag_minus == TRUE)
		ft_memset(s + dy_len, ' ', width - dy_len);
	else
		sub_u_width_handler(s, dy_len, unit, width);
	return (width);
}

/*
** 		dy_len is initialted at the lenth of un_int,
**		it will change depending on precision, width, then flags
*/

int						print_u(int fd, t_unit *unit)
{
	char			str_uint[30];
	unsigned int	dy_len;
	char			s[unit->val.u.precision + unit->val.u.width + 50];

	ft_memset(s, 0, unit->val.u.precision + unit->val.u.width + 50);
	pf_itoa_base(unit->val.u.un_int, 10, unit, str_uint);
	dy_len = u_precision_handler(s, str_uint, unit->val.u.precision, unit);
	dy_len = u_width_handler(s, dy_len, unit, unit->val.u.width);
	write(fd, s, dy_len);
	return (dy_len);
}
