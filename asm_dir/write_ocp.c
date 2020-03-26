/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_ocp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 19:54:26 by naali             #+#    #+#             */
/*   Updated: 2020/02/12 19:54:50 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void			compare_type(char *ocp, int type, int *i)
{
	if (type & T_REG)
	{
		(*ocp) |= 1 << (--(*i));
		--(*i);
	}
	else if (type & T_DIR)
	{
		(*ocp) |= 1 << (*i);
		(*i) -= 2;
	}
	else if (type & T_IND)
	{
		(*ocp) |= 1 << ((*i)--);
		(*ocp) |= 1 << ((*i)--);
	}
}

void				write_ocp(int fd, t_champ *c)
{
	int		i;
	int		pos;
	char	ocp;

	i = 7;
	pos = 0;
	ocp = 0;
	while (pos < c->nb_arg)
	{
		compare_type(&ocp, c->type[pos], &i);
		pos++;
	}
	write(fd, &ocp, 1);
}
