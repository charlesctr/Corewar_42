/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_print_f.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 14:36:10 by jleblond          #+#    #+#             */
/*   Updated: 2019/07/27 14:36:13 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void				sub_f_width_handler(char *s, int dy_len,
							t_unit *unit, int width)
{
	char	s_keep[dy_len + 1];
	int		mark;

	ft_strcpy(s_keep, s);
	mark = 0;
	if (unit->val.f.flag_zero == TRUE)
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

static unsigned int		f_width_handler(char *s, int dy_len, t_unit *unit,
										int width)
{
	if (width <= dy_len)
		return (dy_len);
	if (unit->val.f.flag_minus == TRUE)
		ft_memset(s + dy_len, ' ', width - dy_len);
	else
		sub_f_width_handler(s, dy_len, unit, width);
	return (width);
}

/*
** 		flag ' ' is ignored when flag '+' is present"
*/

static unsigned int		f_flag_plus_and_blank(char *s, int dy_len, t_unit *unit)
{
	unsigned int	i;

	if (unit->val.f.flag_plus == FALSE && unit->val.f.flag_blank == FALSE)
		return (dy_len);
	i = dy_len + 1;
	while (i > 0)
	{
		s[i] = s[i - 1];
		i--;
	}
	if (unit->val.f.flag_plus == TRUE)
		s[0] = '+';
	else if (unit->val.f.flag_blank == TRUE)
		s[0] = ' ';
	return (dy_len + 1);
}

/*
** 		dy_len is initialted at the lenth of integer,
**		it will change depending on precision, width, then flags
*/

int						print_f(int fd, t_unit *unit)
{
	unsigned int	dy_len;
	char			s[unit->val.f.precision + unit->val.f.width + 60];
	int				neg_sign;
	long double		abs_doub;

	neg_sign = 0;
	ft_memset(s, 0, unit->val.f.precision + unit->val.f.width + 60);
	if (1.0 / unit->val.f.doub < 0 || pf_isinf(unit->val.f.doub) == -1)
	{
		*s = '-';
		abs_doub = -(unit->val.f.doub);
		neg_sign = 1;
	}
	else
		abs_doub = (unit->val.f.doub);
	pf_dtoa(abs_doub, unit->val.f.precision, s + neg_sign,
									unit->val.f.flag_hash);
	dy_len = ft_strlen(s);
	if (neg_sign == 0)
		dy_len = f_flag_plus_and_blank(s, dy_len, unit);
	dy_len = f_width_handler(s, dy_len, unit, unit->val.f.width);
	write(fd, s, dy_len);
	return (dy_len);
}
