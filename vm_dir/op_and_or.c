/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_and_or.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <jleblond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 21:55:43 by jleblond          #+#    #+#             */
/*   Updated: 2020/02/27 12:25:36 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
**		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
**
**  p1 & p2 -> p3, the parameter 3 is always a register. This operation
**  modifies the carry. and r2, %0,r3 stores r2 & 0 in r3.
*/

void			op_and(t_vm *vm, t_cursor *c)
{
	t_params	prm;
	uint32_t	value1;
	uint32_t	value2;
	uint32_t	value;

	fill_params(&prm, vm->arena, c);
	if (is_3_types(prm.p1_type, prm.p1) && is_3_types(prm.p2_type, prm.p2)
		&& is_reg_type(prm.p3_type, prm.p3))
	{
		value1 = get_reg_size_value(vm, c, prm.p1_type, prm.p1);
		value2 = get_reg_size_value(vm, c, prm.p2_type, prm.p2);
		value = value1 & value2;
		c->regs[prm.p3] = value;
		if (value == 0)
			c->carry = 1;
		else
			c->carry = 0;
		if (vm->flags & V_FLAG)
			ft_printf("P    %d | and %d & %d => r%d\n", c->c_id, value1,
					value2, prm.p3);
	}
	if (vm->flags & P_FLAG)
		print_pc_movement(vm, 8, c->pc, prm.newpc);
	c->pc = prm.newpc;
}

/*
** 	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
**		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
*/

void			op_or(t_vm *vm, t_cursor *c)
{
	t_params	prm;
	uint32_t	value1;
	uint32_t	value2;
	uint32_t	value;

	fill_params(&prm, vm->arena, c);
	if (is_3_types(prm.p1_type, prm.p1) && is_3_types(prm.p2_type, prm.p2)
		&& is_reg_type(prm.p3_type, prm.p3))
	{
		value1 = get_reg_size_value(vm, c, prm.p1_type, prm.p1);
		value2 = get_reg_size_value(vm, c, prm.p2_type, prm.p2);
		value = value1 | value2;
		c->regs[prm.p3] = value;
		if (value == 0)
			c->carry = 1;
		else
			c->carry = 0;
		if (vm->flags & V_FLAG)
			ft_printf("P    %d | or %d | %d => r%d\n", c->c_id, value1,
					value2, prm.p3);
	}
	if (vm->flags & P_FLAG)
		print_pc_movement(vm, 8, c->pc, prm.newpc);
	c->pc = prm.newpc;
}

/*
**	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
**	"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
*/

void			op_xor(t_vm *vm, t_cursor *c)
{
	t_params	prm;
	uint32_t	value1;
	uint32_t	value2;
	uint32_t	value;

	fill_params(&prm, vm->arena, c);
	if (is_3_types(prm.p1_type, prm.p1) && is_3_types(prm.p2_type, prm.p2)
		&& is_reg_type(prm.p3_type, prm.p3))
	{
		value1 = get_reg_size_value(vm, c, prm.p1_type, prm.p1);
		value2 = get_reg_size_value(vm, c, prm.p2_type, prm.p2);
		value = value1 ^ value2;
		c->regs[prm.p3] = value;
		if (value == 0)
			c->carry = 1;
		else
			c->carry = 0;
		if (vm->flags & V_FLAG)
			ft_printf("P    %d | xor %d ^ %d => r%d\n", c->c_id, value1,
					value2, prm.p3);
	}
	if (vm->flags & P_FLAG)
		print_pc_movement(vm, 8, c->pc, prm.newpc);
	c->pc = prm.newpc;
}
