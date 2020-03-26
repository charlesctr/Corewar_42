/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_print_c_s_ltr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 16:45:57 by jleblond          #+#    #+#             */
/*   Updated: 2019/07/16 16:46:00 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_ltr(int fd, t_unit *unit)
{
	write(fd, unit->val.ltr.literal, (unit->val.ltr.len));
	return (unit->val.ltr.len);
}

int		print_c(int fd, t_unit *unit)
{
	char	s[unit->val.c.width];
	int		width;

	width = unit->val.c.width;
	if (width)
	{
		ft_memset(s, ' ', width);
		if (unit->val.c.flag_minus == FALSE)
			s[width - 1] = unit->val.c.character;
		else
			s[0] = unit->val.c.character;
		write(fd, s, width);
		return (width);
	}
	write(fd, &(unit->val.c.character), 1);
	return (1);
}

int		print_s(int fd, t_unit *unit)
{
	int		width;
	int		precision;
	int		print_len;
	char	s[unit->val.s.width];

	print_len = ft_strlen(unit->val.s.string);
	precision = unit->val.s.precision;
	width = unit->val.s.width;
	if (precision == PRECISION_NULL)
		print_len = 0;
	else if (precision != 0 && precision < print_len)
		print_len = precision;
	if (width > print_len)
	{
		ft_memset(s, ' ', width);
		if (unit->val.s.flag_minus == FALSE)
			ft_strncpy((s + width - print_len), unit->val.s.string, print_len);
		else
			ft_strncpy(s, unit->val.s.string, print_len);
		write(fd, s, width);
		return (width);
	}
	write(fd, unit->val.s.string, print_len);
	return (print_len);
}
