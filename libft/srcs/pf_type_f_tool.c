/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_type_f_tool.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 15:16:10 by jleblond          #+#    #+#             */
/*   Updated: 2019/08/21 15:16:13 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	References:
**	https://en.wikipedia.org/wiki/Double-precision_floating-point_format
**
**	https://www.doc.ic.ac.uk/~eedwards/compsys/float/nan.html
**
**	long double casting as double should preserve
**	exponent bits and chop off the mantissa
*/

int							pf_isinf(long double d)
{
	t_inf_check		check;

	check.d = (double)(d);
	if (check.l == 0x7FF0000000000000ll)
		return (1);
	else if (check.l == 0xFFF0000000000000ll)
		return (-1);
	else
		return (0);
}

int							pf_isnan(long double d)
{
	t_inf_check		check;

	check.d = (double)(d);
	return (check.l == 0x7FF8000000000000ll || check.l == 0xFFF8000000000000ll);
}
