/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_print_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 18:58:57 by jleblond          #+#    #+#             */
/*   Updated: 2019/07/23 18:59:01 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		p_sub_width(char *str_p, char *s, t_unit *unit, int width)
{
	int		len;

	len = ft_strlen(str_p) + 2;
	ft_memset(s, ' ', width);
	if (unit->val.p.flag_minus == TRUE)
	{
		ft_strncpy(s, "0x", 2);
		ft_strncpy(s + 2, str_p, len - 2);
	}
	else
	{
		ft_strncpy(s + width - len, "0x", 2);
		ft_strncpy(s + width - len + 2, str_p, len - 2);
	}
}

static void		p_precision_handler(char *str_p, int precision)
{
	char	s_keep[precision + 30];
	int		len;

	len = ft_strlen(str_p);
	if (precision > len)
	{
		ft_strcpy(s_keep, str_p);
		ft_memset(str_p, '0', precision);
		ft_strncpy(str_p + precision - len, s_keep, len);
		str_p[precision] = 0;
	}
}

static int		p_width_handler(char *str_p, char *s, t_unit *unit, int width)
{
	int		len;

	len = ft_strlen(str_p) + 2;
	if (width <= len)
	{
		ft_strncpy(s, "0x", 2);
		ft_strncpy(s + 2, str_p, len - 2);
		return (len);
	}
	if (unit->val.p.flag_zero == TRUE)
	{
		ft_memset(s, '0', width);
		ft_strncpy(s, "0x", 2);
		if (unit->val.p.flag_minus == TRUE)
			ft_strncpy(s + 2, str_p, len - 2);
		else
			ft_strncpy(s + width - len + 2, str_p, len - 2);
		return (width);
	}
	p_sub_width(str_p, s, unit, width);
	return (width);
}

int				print_p(int fd, t_unit *unit)
{
	char	s[unit->val.p.width + unit->val.p.precision + 30];
	char	str_p[unit->val.p.precision + 30];
	int		final_len;

	ft_memset(str_p, 0, unit->val.p.precision + 30);
	if (unit->val.p.precision == PRECISION_NULL && unit->val.p.pointer == 0)
		*str_p = 0;
	else
		pf_itoa_base(unit->val.p.pointer, 16, unit, str_p);
	p_precision_handler(str_p, unit->val.p.precision);
	final_len = p_width_handler(str_p, s, unit, unit->val.p.width);
	write(fd, s, final_len);
	return (final_len);
}
