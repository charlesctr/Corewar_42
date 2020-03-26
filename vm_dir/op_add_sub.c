/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_add_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <jleblond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 10:10:13 by jleblond          #+#    #+#             */
/*   Updated: 2020/02/27 12:27:29 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
*/

void		op_add(t_vm *vm, t_cursor *c)
{
	t_params	prm;
	int			value;

	fill_params(&prm, vm->arena, c);
	if (is_reg_type(prm.p1_type, prm.p1) && is_reg_type(prm.p2_type, prm.p2)
		&& is_reg_type(prm.p3_type, prm.p3))
	{
		value = c->regs[prm.p1] + c->regs[prm.p2];
		c->regs[prm.p3] = value;
		if (value == 0)
			c->carry = 1;
		else
			c->carry = 0;
		if (vm->flags & V_FLAG)
			ft_printf("P    %d | add r%d + r%d => r%d\n", c->c_id, prm.p1,
					prm.p2, prm.p3);
	}
	if (vm->flags & P_FLAG)
		print_pc_movement(vm, 5, c->pc, prm.newpc);
	c->pc = prm.newpc;
}

/*
**    {"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
*/

void		op_sub(t_vm *vm, t_cursor *c)
{
	t_params			prm;
	uint32_t			value;

	fill_params(&prm, vm->arena, c);
	if (is_reg_type(prm.p1_type, prm.p1) && is_reg_type(prm.p2_type, prm.p2)
		&& is_reg_type(prm.p3_type, prm.p3))
	{
		value = c->regs[prm.p1] - c->regs[prm.p2];
		c->regs[prm.p3] = value;
		if (value == 0)
			c->carry = 1;
		else
			c->carry = 0;
		if (vm->flags & V_FLAG)
			ft_printf("P    %d | sub r%d + r%d => r%d\n", c->c_id, prm.p1,
					prm.p2, prm.p3);
	}
	if (vm->flags & P_FLAG)
		print_pc_movement(vm, 5, c->pc, prm.newpc);
	c->pc = prm.newpc;
}
