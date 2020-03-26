/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_print_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 13:42:42 by jleblond          #+#    #+#             */
/*   Updated: 2019/08/21 13:42:47 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned int		b_precision_handler(char *s, char *str_uint,
									int precision, t_unit *unit)
{
	int		dy_len;

	if (unit->val.b.un_int == 0 && precision == PRECISION_NULL)
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

static void				sub_b_width_handler(char *s, int dy_len,
										t_unit *unit, int width)
{
	char	s_keep[dy_len + 1];
	int		mark;

	mark = 0;
	ft_strcpy(s_keep, s);
	if (unit->val.b.flag_zero == TRUE && unit->val.b.precision == 0)
	{
		ft_memset(s, '0', width);
		if (s_keep[0] == '0' && s_keep[1] == 'b')
		{
			s[0] = s_keep[0];
			s[1] = s_keep[1];
			mark = 2;
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

static unsigned int		b_width_handler(char *s, int dy_len,
									t_unit *unit, int width)
{
	if (width <= dy_len)
		return (dy_len);
	if (unit->val.b.flag_minus == TRUE)
		ft_memset(s + dy_len, ' ', width - dy_len);
	else
		sub_b_width_handler(s, dy_len, unit, width);
	return (width);
}

static unsigned int		b_prefix_handler(char *s, int dy_len)
{
	char	s_keep[dy_len + 1];
	int		sign;

	sign = 0;
	ft_strcpy(s_keep, s);
	s[0] = '0';
	s[1] = 'b';
	sign = 2;
	ft_strncpy(s + sign, s_keep, dy_len);
	s[dy_len + sign] = '\0';
	return (dy_len + sign);
}

/*
** 		dy_len is initialted at the lenth of un_int,
**		it will change depending on precision, width, then flags
*/

int						print_b(int fd, t_unit *unit)
{
	char			str_uint[50];
	unsigned int	dy_len;
	char			s[unit->val.b.precision + unit->val.b.width + 50];

	ft_memset(s, 0, unit->val.b.precision + unit->val.b.width + 50);
	pf_itoa_base(unit->val.b.un_int, 2, unit, str_uint);
	dy_len = b_precision_handler(s, str_uint, unit->val.b.precision, unit);
	if (unit->val.b.flag_hash == TRUE && unit->val.b.un_int != 0)
		dy_len = b_prefix_handler(s, dy_len);
	dy_len = b_width_handler(s, dy_len, unit, unit->val.b.width);
	write(fd, s, dy_len);
	return (dy_len);
}
