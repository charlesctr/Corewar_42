/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parse_type_f.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 10:32:20 by jleblond          #+#    #+#             */
/*   Updated: 2019/07/21 10:32:34 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*type_f_get_flags(char *buf, t_unit *unit, int buf_len)
{
	char	flags[buf_len];
	int		flags_len;

	if ((flags_len = get_flags(flags, buf, "+- 0#")))
	{
		if (ft_strchr(flags, '+'))
			unit->val.f.flag_plus = TRUE;
		if (ft_strchr(flags, '-'))
			unit->val.f.flag_minus = TRUE;
		if (ft_strchr(flags, ' '))
			unit->val.f.flag_blank = TRUE;
		if (ft_strchr(flags, '0'))
			unit->val.f.flag_zero = TRUE;
		if (ft_strchr(flags, '#'))
			unit->val.f.flag_hash = TRUE;
		buf += flags_len;
	}
	return (buf);
}

static char		*type_f_get_width(char *buf, t_unit *unit, va_list args)
{
	int		digits;
	int		digits_len;

	digits = 0;
	digits_len = get_digits_or_star(&digits, buf, ft_strlen(buf), args);
	if (digits_len)
	{
		unit->val.f.width = digits;
		buf += digits_len;
	}
	return (buf);
}

static char		*type_f_get_precision(char *buf, t_unit *unit, va_list args)
{
	int		digits;
	int		digits_len;

	digits = 0;
	if (*buf == '.')
	{
		buf++;
		digits_len = get_digits_or_star(&digits, buf, ft_strlen(buf), args);
		if (digits_len == 0 || (digits_len != 0 && digits == 0))
			unit->val.f.precision = PRECISION_NULL;
		else
			unit->val.f.precision = digits;
		buf += digits_len;
	}
	return (buf);
}

static char		*type_f_get_modifier(char *buf, t_unit *unit)
{
	if (*buf == 'l')
	{
		unit->val.f.modifier = MD_L;
		buf++;
	}
	else if (*buf == 'L')
	{
		unit->val.f.modifier = MD_MAG_L;
		buf++;
	}
	return (buf);
}

int				parse_f(t_list **alst, char *buf, va_list args)
{
	t_unit	unit;

	ft_bzero(&unit, sizeof(t_unit));
	buf = type_f_get_flags(buf, &unit, ft_strlen(buf));
	buf = type_f_get_width(buf, &unit, args);
	buf = type_f_get_precision(buf, &unit, args);
	buf = type_f_get_modifier(buf, &unit);
	if (*buf != 'f')
		return (ERROR);
	unit.type = TYPE_F;
	if (unit.val.f.modifier == MD_MAG_L)
		unit.val.f.doub = va_arg(args, long double);
	else
		unit.val.f.doub = (long double)va_arg(args, double);
	unit_lstadd_bot(alst, &unit);
	return (0);
}
