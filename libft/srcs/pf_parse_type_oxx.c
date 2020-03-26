/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parse_type_oxx.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 13:43:35 by jleblond          #+#    #+#             */
/*   Updated: 2019/07/27 13:43:39 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*type_oxx_get_flags_and_width(char *buf, t_unit *unit,
										int buf_len, va_list args)
{
	int		digits;
	int		digits_len;
	char	flags[buf_len];
	int		flags_len;

	if ((flags_len = get_flags(flags, buf, "#-0+ ")))
	{
		(ft_strchr(flags, '#')) ? unit->val.oxx.flag_hash = TRUE : 0;
		(ft_strchr(flags, '-')) ? unit->val.oxx.flag_minus = TRUE : 0;
		(ft_strchr(flags, '0')) ? unit->val.oxx.flag_zero = TRUE : 0;
		buf += flags_len;
	}
	digits = 0;
	if ((digits_len = get_digits_or_star(&digits, buf, ft_strlen(buf), args)))
	{
		unit->val.oxx.width = digits;
		buf += digits_len;
	}
	return (buf);
}

static char		*type_oxx_get_precision(char *buf, t_unit *unit, va_list args)
{
	int		digits;
	int		digits_len;

	digits = 0;
	if (*buf == '.')
	{
		buf++;
		digits_len = get_digits_or_star(&digits, buf, ft_strlen(buf), args);
		if (digits_len == 0 || (digits_len != 0 && digits == 0))
			unit->val.oxx.precision = PRECISION_NULL;
		else
			unit->val.oxx.precision = digits;
		buf += digits_len;
	}
	return (buf);
}

static char		*type_oxx_get_modifier(char *buf, t_unit *unit)
{
	if (*buf == 'l' && buf[1] == 'l')
	{
		unit->val.oxx.modifier = MD_LL;
		buf += 2;
	}
	else if (*buf == 'h' && buf[1] == 'h')
	{
		unit->val.oxx.modifier = MD_HH;
		buf += 2;
	}
	else if (*buf == 'l')
	{
		unit->val.oxx.modifier = MD_L;
		buf++;
	}
	else if (*buf == 'h')
	{
		unit->val.oxx.modifier = MD_H;
		buf++;
	}
	return (buf);
}

void			get_valeur(char *buf, va_list args, t_unit *unit)
{
	if (*buf == 'X')
		unit->val.oxx.sub_type = TYPE_X_MAJ;
	if (*buf == 'x')
		unit->val.oxx.sub_type = TYPE_X;
	if (*buf == 'o')
		unit->val.oxx.sub_type = TYPE_O;
	if (unit->val.oxx.modifier == MD_LL)
		unit->val.oxx.un_int = va_arg(args, unsigned long long);
	else if (unit->val.oxx.modifier == MD_L)
		unit->val.oxx.un_int = va_arg(args, unsigned long);
	else if (unit->val.oxx.modifier == MD_HH)
		unit->val.oxx.un_int = (unsigned char)va_arg(args, unsigned int);
	else if (unit->val.oxx.modifier == MD_H)
		unit->val.oxx.un_int = (unsigned short)va_arg(args, unsigned int);
	else
		unit->val.oxx.un_int = va_arg(args, unsigned int);
}

int				parse_oxx(t_list **alst, char *buf, va_list args)
{
	t_unit	unit;

	ft_bzero(&unit, sizeof(t_unit));
	buf = type_oxx_get_flags_and_width(buf, &unit, ft_strlen(buf), args);
	buf = type_oxx_get_precision(buf, &unit, args);
	buf = type_oxx_get_modifier(buf, &unit);
	if (*buf != 'o' && *buf != 'x' && *buf != 'X')
		return (ERROR);
	unit.type = TYPE_OXX;
	get_valeur(buf, args, &unit);
	unit_lstadd_bot(alst, &unit);
	return (0);
}
