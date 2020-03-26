/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parse_type_s.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 11:58:55 by jleblond          #+#    #+#             */
/*   Updated: 2019/08/21 11:58:59 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*type_s_get_flags_and_width(char *buf,
	t_unit *unit, int buf_len, va_list args)
{
	int		digits;
	int		digits_len;
	char	flags[buf_len];
	int		flags_len;

	flags_len = get_flags(flags, buf, "-");
	if (flags_len)
	{
		unit->val.s.flag_minus = TRUE;
		buf += flags_len;
	}
	digits = 0;
	digits_len = get_digits_or_star(&digits, buf, ft_strlen(buf), args);
	if (digits_len)
	{
		unit->val.s.width = digits;
		buf += digits_len;
	}
	return (buf);
}

static char		*type_s_get_precision_and_modifier(char *buf,
									t_unit *unit, va_list args)
{
	int		digits;
	int		digits_len;

	digits = 0;
	if (*buf == '.')
	{
		buf++;
		digits_len = get_digits_or_star(&digits, buf, ft_strlen(buf), args);
		if (digits_len == 0 || (digits_len != 0 && digits == 0))
			unit->val.s.precision = PRECISION_NULL;
		else
			unit->val.s.precision = digits;
		buf += digits_len;
	}
	if (*buf == 'l')
	{
		unit->val.s.modifier_l = TRUE;
		buf++;
	}
	return (buf);
}

int				parse_s(t_list **alst, char *buf, va_list args)
{
	t_unit	unit;

	ft_bzero(&unit, sizeof(t_unit));
	buf = type_s_get_flags_and_width(buf, &unit, ft_strlen(buf), args);
	buf = type_s_get_precision_and_modifier(buf, &unit, args);
	if (*buf != 's')
		return (ERROR);
	unit.type = TYPE_S;
	if ((unit.val.s.string = va_arg(args, char *)) == NULL)
		unit.val.s.string = "(null)";
	unit_lstadd_bot(alst, &unit);
	return (0);
}
