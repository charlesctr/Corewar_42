/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 11:25:51 by jleblond          #+#    #+#             */
/*   Updated: 2019/08/21 11:25:55 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static uintmax_t		pow_ten(int preci)
{
	int			i;
	uintmax_t	pw;

	i = 0;
	pw = 1;
	while (i < preci + 1)
	{
		pw = pw * 10;
		i++;
	}
	return (pw);
}

static void				write_frac_on_buf(char *buf, uintmax_t pw,
									uintmax_t frac_to_int, int len)
{
	buf[len] = '.';
	buf += len + 1;
	while (pw > 10)
	{
		pw = pw / 10;
		*buf = frac_to_int / pw + '0';
		buf++;
		frac_to_int = frac_to_int % pw;
	}
	*buf = 0;
}

static void				round_then_write(long double nbr, int preci,
							char *buf, t_bool flag_hash)
{
	uintmax_t	frac_to_int;
	uintmax_t	pw;
	uintmax_t	int_part;
	int			len;

	pw = pow_ten(preci);
	int_part = (uintmax_t)nbr;
	frac_to_int = (uintmax_t)((nbr - int_part) * pw);
	if (frac_to_int % 10 >= 5)
		frac_to_int = frac_to_int + 10;
	int_part = int_part + frac_to_int / pw;
	frac_to_int = frac_to_int % pw;
	pf_itoa_base(int_part, 10, NULL, buf);
	len = ft_strlen(buf);
	if (preci == 0 && flag_hash == FALSE)
		return ;
	else if (preci == 0 && flag_hash == TRUE)
	{
		buf[len] = '.';
		buf[len + 1] = 0;
		return ;
	}
	write_frac_on_buf(buf, pw, frac_to_int, len);
}

int						is_inf_or_nan(long double nbr, char *buf)
{
	if (pf_isinf(nbr))
	{
		ft_strcpy(buf, "inf");
		return (TRUE);
	}
	if (pf_isnan(nbr))
	{
		ft_strcpy(buf, "nan");
		return (TRUE);
	}
	return (FALSE);
}

void					pf_dtoa(long double nbr, int precision,
							char *buf, t_bool flag_hash)
{
	if (is_inf_or_nan(nbr, buf))
		return ;
	precision = (precision == 0 ? 6 : precision);
	if (precision == PRECISION_NULL)
		round_then_write(nbr, 0, buf, flag_hash);
	else
		round_then_write(nbr, precision, buf, flag_hash);
}
