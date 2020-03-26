/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_print_oxx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 10:34:25 by jleblond          #+#    #+#             */
/*   Updated: 2019/07/27 10:34:29 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned int		oxx_precision_handler(char *s, char *str_uint,
									int precision, t_unit *unit)
{
	int		dy_len;

	if (unit->val.oxx.un_int == 0 && precision == PRECISION_NULL)
	{
		if (unit->val.oxx.sub_type != TYPE_O
			|| (unit->val.oxx.sub_type == TYPE_O
				&& unit->val.oxx.flag_hash != TRUE))
			return (0);
	}
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

static void				sub_oxx_width_handler(char *s, int dy_len,
										t_unit *unit, int width)
{
	char	s_keep[dy_len + 1];
	int		mark;

	mark = 0;
	ft_strcpy(s_keep, s);
	if (unit->val.oxx.flag_zero == TRUE && unit->val.oxx.precision == 0)
	{
		ft_memset(s, '0', width);
		if (s_keep[0] == '0' && (s_keep[1] == 'x' || s_keep[1] == 'X'))
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

static unsigned int		oxx_width_handler(char *s, int dy_len,
									t_unit *unit, int width)
{
	if (width <= dy_len)
		return (dy_len);
	if (unit->val.oxx.flag_minus == TRUE)
		ft_memset(s + dy_len, ' ', width - dy_len);
	else
		sub_oxx_width_handler(s, dy_len, unit, width);
	return (width);
}

static unsigned int		oxx_prefix_handler(char *s, int dy_len,
	t_unit_type sub_type)
{
	char	s_keep[dy_len + 1];
	int		sign;

	sign = 0;
	ft_strcpy(s_keep, s);
	if (sub_type == TYPE_O && s_keep[0] != '0')
	{
		s[0] = '0';
		sign = 1;
	}
	if (sub_type == TYPE_X)
	{
		s[0] = '0';
		s[1] = 'x';
		sign = 2;
	}
	if (sub_type == TYPE_X_MAJ)
	{
		s[0] = '0';
		s[1] = 'X';
		sign = 2;
	}
	ft_strncpy(s + sign, s_keep, dy_len);
	s[dy_len + sign] = '\0';
	return (dy_len + sign);
}

/*
** 		dy_len is initialted at the lenth of un_int,
**		it will change depending on precision, width, then flags
*/

int						print_oxx(int fd, t_unit *unit)
{
	char			str_uint[30];
	unsigned int	dy_len;
	char			s[unit->val.oxx.precision + unit->val.oxx.width + 50];

	ft_memset(s, 0, unit->val.oxx.precision + unit->val.oxx.width + 50);
	if (unit->val.oxx.sub_type == TYPE_O)
		pf_itoa_base(unit->val.oxx.un_int, 8, unit, str_uint);
	else
		pf_itoa_base(unit->val.oxx.un_int, 16, unit, str_uint);
	dy_len = oxx_precision_handler(s, str_uint, unit->val.oxx.precision, unit);
	if (unit->val.oxx.flag_hash == TRUE && unit->val.oxx.un_int != 0)
		dy_len = oxx_prefix_handler(s, dy_len, unit->val.oxx.sub_type);
	dy_len = oxx_width_handler(s, dy_len, unit, unit->val.oxx.width);
	write(fd, s, dy_len);
	return (dy_len);
}
