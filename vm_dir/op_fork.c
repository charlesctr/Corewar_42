/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <jleblond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 10:06:08 by jleblond          #+#    #+#             */
/*   Updated: 2020/02/27 12:30:46 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
*/

void		op_fork(t_vm *vm, t_cursor *c)
{
	t_cursor	*new;
	int16_t		p1;

	if (c_lst_new(&new) == FALSE)
		return ;
	ft_memcpy(new, c, sizeof(t_cursor));
	p1 = read_bytes(vm->arena, c->pc + 1, 2);
	new->pc = pos(c->pc + p1 % IDX_MOD);
	new->wait_cycle = -1;
	new->next = NULL;
	new->prev = NULL;
	if (c_lst_add_top(&(vm->cursor), new) == FALSE)
		return ;
	vm->cursor_nb++;
	new->c_id = vm->cursor_nb;
	if (vm->flags & V_FLAG)
		ft_printf("P    %d | fork  %d(%d)\n", c->c_id, p1, new->pc);
	if (vm->flags & P_FLAG)
		print_pc_movement(vm, 3, c->pc, c->pc + 3);
	c->pc += 3;
}

void		op_lfork(t_vm *vm, t_cursor *c)
{
	t_cursor	*new;
	int16_t		p1;

	p1 = read_bytes(vm->arena, c->pc + 1, 2);
	if (c_lst_new(&new) == FALSE)
		return ;
	ft_memcpy(new, c, sizeof(t_cursor));
	new->pc = c->pc + p1;
	new->wait_cycle = -1;
	new->next = NULL;
	new->prev = NULL;
	if (c_lst_add_top(&(vm->cursor), new) == FALSE)
		return ;
	vm->cursor_nb++;
	new->c_id = vm->cursor_nb;
	if (vm->flags & V_FLAG)
		ft_printf("P    %d | lfork %d(%d)\n", c->c_id, p1, new->pc);
	if (vm->flags & P_FLAG)
		print_pc_movement(vm, 3, c->pc, c->pc + 3);
	c->pc += 3;
}
