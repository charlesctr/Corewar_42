/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parse_type_b.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 14:36:46 by jleblond          #+#    #+#             */
/*   Updated: 2019/08/21 14:36:50 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*type_b_get_flags_and_width(char *buf, t_unit *unit,
										int buf_len, va_list args)
{
	int		digits;
	int		digits_len;
	char	flags[buf_len];
	int		flags_len;

	if ((flags_len = get_flags(flags, buf, "#-0+ ")))
	{
		(ft_strchr(flags, '#')) ? unit->val.b.flag_hash = TRUE : 0;
		(ft_strchr(flags, '-')) ? unit->val.b.flag_minus = TRUE : 0;
		(ft_strchr(flags, '0')) ? unit->val.b.flag_zero = TRUE : 0;
		buf += flags_len;
	}
	digits = 0;
	if ((digits_len = get_digits_or_star(&digits, buf, ft_strlen(buf), args)))
	{
		unit->val.b.width = digits;
		buf += digits_len;
	}
	return (buf);
}

static char		*type_b_get_precision(char *buf, t_unit *unit, va_list args)
{
	int		digits;
	int		digits_len;

	digits = 0;
	if (*buf == '.')
	{
		buf++;
		digits_len = get_digits_or_star(&digits, buf, ft_strlen(buf), args);
		if (digits_len == 0 || (digits_len != 0 && digits == 0))
			unit->val.b.precision = PRECISION_NULL;
		else
			unit->val.b.precision = digits;
		buf += digits_len;
	}
	return (buf);
}

static char		*type_b_get_modifier(char *buf, t_unit *unit)
{
	if (*buf == 'l' && buf[1] == 'l')
	{
		unit->val.b.modifier = MD_LL;
		buf += 2;
	}
	else if (*buf == 'h' && buf[1] == 'h')
	{
		unit->val.b.modifier = MD_HH;
		buf += 2;
	}
	else if (*buf == 'l')
	{
		unit->val.b.modifier = MD_L;
		buf++;
	}
	else if (*buf == 'h')
	{
		unit->val.b.modifier = MD_H;
		buf++;
	}
	return (buf);
}

void			d_get_valeur(va_list args, t_unit *unit)
{
	if (unit->val.b.modifier == MD_LL)
		unit->val.b.un_int = va_arg(args, unsigned long long);
	else if (unit->val.b.modifier == MD_L)
		unit->val.b.un_int = va_arg(args, unsigned long);
	else if (unit->val.b.modifier == MD_HH)
		unit->val.b.un_int = (unsigned char)va_arg(args, unsigned int);
	else if (unit->val.b.modifier == MD_H)
		unit->val.b.un_int = (unsigned short)va_arg(args, unsigned int);
	else
		unit->val.b.un_int = va_arg(args, unsigned int);
}

int				parse_b(t_list **alst, char *buf, va_list args)
{
	t_unit	unit;

	ft_bzero(&unit, sizeof(t_unit));
	buf = type_b_get_flags_and_width(buf, &unit, ft_strlen(buf), args);
	buf = type_b_get_precision(buf, &unit, args);
	buf = type_b_get_modifier(buf, &unit);
	if (*buf != 'b')
		return (ERROR);
	unit.type = TYPE_B;
	d_get_valeur(args, &unit);
	unit_lstadd_bot(alst, &unit);
	return (0);
}
