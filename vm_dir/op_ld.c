/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <jleblond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 14:41:19 by jleblond          #+#    #+#             */
/*   Updated: 2020/02/27 13:29:22 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**  {"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
*/

void			op_ld(t_vm *vm, t_cursor *c)
{
	t_params	prm;

	fill_params(&prm, vm->arena, c);
	if (is_dir_or_ind(prm.p1_type) && is_reg_type(prm.p2_type, prm.p2))
	{
		prm.p1 = get_reg_size_value(vm, c, prm.p1_type, prm.p1);
		c->regs[prm.p2] = prm.p1;
		if (prm.p1 == 0)
			c->carry = 1;
		else
			c->carry = 0;
		if (vm->flags & V_FLAG)
			ft_printf("P    %d | ld %d => r%d\n", c->c_id, prm.p1, prm.p2);
	}
	if (vm->flags & P_FLAG)
		print_pc_movement(vm, 7, c->pc, prm.newpc);
	c->pc = prm.newpc;
}

/*
**	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
*/

void			op_lld(t_vm *vm, t_cursor *c)
{
	t_params	prm;
	int			address;

	fill_params(&prm, vm->arena, c);
	if (is_dir_or_ind(prm.p1_type) && is_reg_type(prm.p2_type, prm.p2))
	{
		if (prm.p1_type == TYPE_IND)
		{
			address = c->pc + ((uint16_t)prm.p1);
			prm.p1 = read_bytes(vm->arena, address, 4);
		}
		c->regs[prm.p2] = prm.p1;
		if (prm.p1 == 0)
			c->carry = 1;
		else
			c->carry = 0;
		if (vm->flags & V_FLAG)
			ft_printf("P    %d | lld %d => r%d\n", c->c_id, prm.p1, prm.p2);
	}
	if (vm->flags & P_FLAG)
		print_pc_movement(vm, 7, c->pc, prm.newpc);
	c->pc = prm.newpc;
}

/*
**     {"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
**       "long load index", 1, 1},
**
** ca prend 2 index et 1 registre, additionne les 2 premiers,
** traite ca comme une adresse, y lit une valeur de la taille
** d’un registre et la met dans le 3eme.
*/

void			op_ldi(t_vm *vm, t_cursor *c)
{
	t_params	prm;
	int16_t		address;
	int16_t		value1;
	int16_t		value2;

	fill_params(&prm, vm->arena, c);
	if (is_3_types(prm.p1_type, prm.p1) && is_dir_or_reg(prm.p2_type, prm.p2)
		&& is_reg_type(prm.p3_type, prm.p3))
	{
		value1 = get_ind_size_value(vm, c, prm.p1_type, prm.p1);
		value2 = get_ind_size_value(vm, c, prm.p2_type, prm.p2);
		address = c->pc + (value1 + value2) % IDX_MOD;
		c->regs[prm.p3] = read_bytes(vm->arena, address, REG_SIZE);
		if (c->regs[prm.p3] == 0)
			c->carry = 1;
		else
			c->carry = 0;
		if (vm->flags & V_FLAG)
			ft_printf("P    %d | ldi %d(%d) %d(%d) => r%d\n", c->c_id, prm.p1,
					value1, prm.p2, value2, prm.p3);
	}
	if (vm->flags & P_FLAG)
		print_pc_movement(vm, 6, c->pc, prm.newpc);
	c->pc = prm.newpc;
}

/*
** {"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
**    "long load index", 1, 1},
*/

void			op_lldi(t_vm *vm, t_cursor *c)
{
	t_params	prm;
	int16_t		address;
	int16_t		value1;
	int16_t		value2;

	fill_params(&prm, vm->arena, c);
	if (is_3_types(prm.p1_type, prm.p1) && is_dir_or_reg(prm.p2_type, prm.p2)
		&& is_reg_type(prm.p3_type, prm.p3))
	{
		value1 = get_ind_size_value(vm, c, prm.p1_type, prm.p1);
		value2 = get_ind_size_value(vm, c, prm.p2_type, prm.p2);
		address = c->pc + value1 + value2;
		c->regs[prm.p3] = read_bytes(vm->arena, address, REG_SIZE);
		if (c->regs[prm.p3] == 0)
			c->carry = 1;
		else
			c->carry = 0;
		if (vm->flags & V_FLAG)
			ft_printf("P    %d | lldi %d(%d) %d(%d) => r%d\n", c->c_id, prm.p1,
					value1, prm.p2, value2, prm.p3);
	}
	if (vm->flags & P_FLAG)
		print_pc_movement(vm, 7, c->pc, prm.newpc);
	c->pc = prm.newpc;
}
