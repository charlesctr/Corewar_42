/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parse_type_c.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 12:02:43 by jleblond          #+#    #+#             */
/*   Updated: 2020/02/25 13:50:08 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*type_c_get_flags(char *buf, t_unit *unit, int buf_len)
{
	char	flags[buf_len];
	int		flags_len;

	flags_len = get_flags(flags, buf, "-0+ #");
	if (flags_len)
	{
		(ft_strchr(flags, '-')) ? unit->val.c.flag_minus = TRUE : 0;
		buf += flags_len;
	}
	return (buf);
}

static char		*type_c_width_precision(char *buf, t_unit *unit, va_list args)
{
	int		digits;
	int		digits_len;

	digits = 0;
	digits_len = get_digits_or_star(&digits, buf, ft_strlen(buf), args);
	if (digits_len)
	{
		unit->val.c.width = digits;
		buf += digits_len;
	}
	if (*buf == '.')
	{
		buf++;
		while (ft_isdigit(*buf))
			buf++;
	}
	return (buf);
}

static char		*type_c_get_modifier(char *buf, t_unit *unit)
{
	if (*buf == 'l')
	{
		unit->val.c.modifier_l = TRUE;
		buf++;
	}
	return (buf);
}

int				parse_c(t_list **alst, char *buf, va_list args)
{
	t_unit	unit;

	ft_bzero(&unit, sizeof(t_unit));
	buf = type_c_get_flags(buf, &unit, ft_strlen(buf));
	buf = type_c_width_precision(buf, &unit, args);
	buf = type_c_get_modifier(buf, &unit);
	if (*buf != 'c')
		return (ERROR);
	unit.type = TYPE_C;
	if (unit.val.c.modifier_l == TRUE)
		unit.val.c.character = (wchar_t)va_arg(args, wint_t);
	else
		unit.val.c.character = (char)va_arg(args, int);
	unit_lstadd_bot(alst, &unit);
	return (0);
}

int				parse_percent(t_list **alst, char *buf, va_list args)
{
	t_unit	unit;

	ft_bzero(&unit, sizeof(t_unit));
	buf = type_c_get_flags(buf, &unit, ft_strlen(buf));
	buf = type_c_width_precision(buf, &unit, args);
	buf = type_c_get_modifier(buf, &unit);
	unit.type = TYPE_C;
	unit.val.c.character = '%';
	unit_lstadd_bot(alst, &unit);
	return (0);
}
