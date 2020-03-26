/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 11:57:04 by jleblond          #+#    #+#             */
/*   Updated: 2019/07/06 11:57:19 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	a capsule is defined as :
** 	[flags][width][precision][modifier][conversion][literal]
**	excepte the first capsule which may contains only literal
*/

static int		find_end_of_capsule(const char *format)
{
	int i;

	i = 0;
	while (format[i] != '\0')
	{
		if (is_conversion(format[i]))
			break ;
		i++;
	}
	return (i);
}

static int		parse_capsule(t_list **alst, const char *capsule,
								int end, va_list args)
{
	int					index;
	char				buf[ft_strlen(capsule)];
	static t_parse_funs	funs[PARSE_FUNS_NB] = {
		{'c', parse_c}, {'s', parse_s}, {'d', parse_d}, {'i', parse_d},
		{'f', parse_f}, {'p', parse_p}, {'o', parse_oxx}, {'x', parse_oxx},
		{'X', parse_oxx}, {'u', parse_u}, {'%', parse_percent}, {'b', parse_b}
	};

	index = 0;
	if (capsule[end] == '\0')
		return (ERROR);
	while (index < PARSE_FUNS_NB)
	{
		if (capsule[end] == funs[index].type)
		{
			ft_strncpy(buf, capsule, end + 1);
			buf[end + 1] = '\0';
			if (funs[index].f(alst, buf, args) == ERROR)
				return (ERROR);
			break ;
		}
		index++;
	}
	return (0);
}

static int		parse_percent_substring(const char *capsule, t_list **alst,
											va_list args, int *r_capsule_ok)
{
	int end;
	int ret;

	*r_capsule_ok = TRUE;
	end = find_end_of_capsule(capsule);
	ret = parse_capsule(alst, capsule, end, args);
	if (ret == ERROR)
		*r_capsule_ok = FALSE;
	return (end + 1);
}

static int		parse_literal_substring(const char *capsule, t_list **alst,
										int *r_capsule_ok)
{
	int			i;
	t_unit		unit;

	*r_capsule_ok = TRUE;
	i = 0;
	while (capsule[i] != '\0' && capsule[i] != '%')
		i++;
	ft_bzero(&unit, sizeof(t_unit));
	unit.type = TYPE_LTR;
	unit.val.ltr.len = i;
	unit.val.ltr.literal = capsule;
	unit_lstadd_bot(alst, &unit);
	return (i);
}

t_list			*parse_string(const char *format, va_list args,
												int *r_format_ok)
{
	size_t		i;
	int			substr_format_ok;
	t_list		*lst;

	*r_format_ok = TRUE;
	lst = NULL;
	i = 0;
	while (i < ft_strlen(format))
	{
		if (format[i] == '%')
		{
			i++;
			i += parse_percent_substring(format + i, &lst,
									args, &substr_format_ok);
		}
		else
			i += parse_literal_substring(format + i, &lst, &substr_format_ok);
		if (!substr_format_ok)
			*r_format_ok = FALSE;
	}
	return (lst);
}
