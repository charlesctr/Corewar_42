/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parse_type_p.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 10:00:14 by jleblond          #+#    #+#             */
/*   Updated: 2019/07/23 10:00:28 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*type_p_get_flags(char *buf, int buf_len, t_unit *unit)
{
	char	flags[buf_len];
	int		flags_len;

	if ((flags_len = get_flags(flags, buf, "+- 0#")))
	{
		if (ft_strchr(flags, '-'))
			unit->val.p.flag_minus = TRUE;
		if (ft_strchr(flags, '0'))
			unit->val.p.flag_zero = TRUE;
		buf += flags_len;
	}
	return (buf);
}

static char		*type_p_get_width(char *buf, t_unit *unit, va_list args)
{
	int		digits;
	int		digits_len;

	digits = 0;
	digits_len = get_digits_or_star(&digits, buf, ft_strlen(buf), args);
	if (digits_len)
	{
		unit->val.p.width = digits;
		buf += digits_len;
	}
	return (buf);
}

static char		*type_p_get_precision(char *buf, t_unit *unit, va_list args)
{
	int		digits;
	int		digits_len;

	digits = 0;
	if (*buf == '.')
	{
		buf++;
		digits_len = get_digits_or_star(&digits, buf, ft_strlen(buf), args);
		if (digits_len == 0 || (digits_len != 0 && digits == 0))
			unit->val.p.precision = PRECISION_NULL;
		else
			unit->val.p.precision = digits;
		buf += digits_len;
	}
	return (buf);
}

static char		*type_p_modifier_check(char *buf)
{
	if (*buf == 'l' && buf[1] == 'l')
		buf += 2;
	else if (*buf == 'h' && buf[1] == 'h')
		buf += 2;
	else if (*buf == 'l')
		buf++;
	else if (*buf == 'h')
		buf++;
	return (buf);
}

int				parse_p(t_list **alst, char *buf, va_list args)
{
	t_unit	unit;

	ft_bzero(&unit, sizeof(t_unit));
	buf = type_p_get_flags(buf, ft_strlen(buf), &unit);
	buf = type_p_get_width(buf, &unit, args);
	buf = type_p_get_precision(buf, &unit, args);
	buf = type_p_modifier_check(buf);
	if (*buf != 'p')
		return (ERROR);
	unit.type = TYPE_P;
	unit.val.p.pointer = (uintmax_t)va_arg(args, void *);
	unit_lstadd_bot(alst, &unit);
	return (0);
}
