/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <jleblond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 14:05:14 by jleblond          #+#    #+#             */
/*   Updated: 2020/02/27 13:28:06 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**  {"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
*/

void		op_aff(t_vm *vm, t_cursor *c)
{
	t_params			prm;
	uint32_t			value;

	fill_params(&prm, vm->arena, c);
	if (is_reg_type(prm.p1_type, prm.p1))
	{
		value = c->regs[prm.p1] % 256;
		ft_printf("aff:%c\n", value);
		if (vm->flags & V_FLAG)
			ft_printf("P    %d |  aff r%d\n", c->c_id, prm.p1);
	}
	c->pc = prm.newpc;
}
