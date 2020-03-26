/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parse_type_d.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 17:30:01 by jleblond          #+#    #+#             */
/*   Updated: 2019/07/16 17:30:06 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*type_d_get_flags_and_width(char *buf, t_unit *unit,
														int buf_len)
{
	char	flags[buf_len];
	int		flags_len;

	if ((flags_len = get_flags(flags, buf, "+- 0")))
	{
		if (ft_strchr(flags, '+'))
			unit->val.d.flag_plus = TRUE;
		if (ft_strchr(flags, '-'))
			unit->val.d.flag_minus = TRUE;
		if (ft_strchr(flags, ' '))
			unit->val.d.flag_blank = TRUE;
		if (ft_strchr(flags, '0'))
			unit->val.d.flag_zero = TRUE;
		buf += flags_len;
	}
	return (buf);
}

static char		*type_d_get_width(char *buf, t_unit *unit, va_list args)
{
	int		digits;
	int		digits_len;

	digits = 0;
	digits_len = get_digits_or_star(&digits, buf, ft_strlen(buf), args);
	if (digits_len)
	{
		unit->val.d.width = digits;
		buf += digits_len;
	}
	return (buf);
}

static char		*type_d_get_precision(char *buf, t_unit *unit, va_list args)
{
	int		digits;
	int		digits_len;

	digits = 0;
	if (*buf == '.')
	{
		buf++;
		digits_len = get_digits_or_star(&digits, buf, ft_strlen(buf), args);
		if (digits_len == 0 || (digits_len != 0 && digits == 0))
			unit->val.d.precision = PRECISION_NULL;
		else
			unit->val.d.precision = digits;
		buf += digits_len;
	}
	return (buf);
}

static char		*type_d_get_modifier(char *buf, t_unit *unit)
{
	if (*buf == 'l' && buf[1] == 'l')
	{
		unit->val.d.modifier = MD_LL;
		buf += 2;
	}
	else if (*buf == 'h' && buf[1] == 'h')
	{
		unit->val.d.modifier = MD_HH;
		buf += 2;
	}
	else if (*buf == 'l')
	{
		unit->val.d.modifier = MD_L;
		buf++;
	}
	else if (*buf == 'h')
	{
		unit->val.d.modifier = MD_H;
		buf++;
	}
	return (buf);
}

int				parse_d(t_list **alst, char *buf, va_list args)
{
	t_unit	unit;

	ft_bzero(&unit, sizeof(t_unit));
	buf = type_d_get_flags_and_width(buf, &unit, ft_strlen(buf));
	buf = type_d_get_width(buf, &unit, args);
	buf = type_d_get_precision(buf, &unit, args);
	buf = type_d_get_modifier(buf, &unit);
	if (*buf != 'd' && *buf != 'i')
		return (ERROR);
	unit.type = TYPE_D;
	if (unit.val.d.modifier == MD_LL)
		unit.val.d.integer = (intmax_t)va_arg(args, long long);
	else if (unit.val.d.modifier == MD_L)
		unit.val.d.integer = (intmax_t)va_arg(args, long);
	else if (unit.val.d.modifier == MD_HH)
		unit.val.d.integer = (signed char)va_arg(args, int);
	else if (unit.val.d.modifier == MD_H)
		unit.val.d.integer = (short)va_arg(args, int);
	else
		unit.val.d.integer = va_arg(args, int);
	unit_lstadd_bot(alst, &unit);
	return (0);
}
