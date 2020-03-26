/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_vm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <jleblond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 18:05:18 by jleblond          #+#    #+#             */
/*   Updated: 2020/02/27 13:25:49 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** op_wait[0] is not used.
*/

static int		get_wait_cycle(unsigned char op)
{
	static int op_wait[17] = {-1, 10, 5, 5, 10, 10, 6, 6, 6, 20, 25,
		25, 800, 10, 50, 1000, 2};

	return (op_wait[op]);
}

void			run_cursor(t_vm *vm)
{
	t_cursor	*c;

	c = vm->cursor;
	while (c)
	{
		if (vm->cycle_total == 1 || c->wait_cycle == -1)
		{
			c->op = vm->arena[pos(c->pc)];
			if (op_code_valid(c->op))
				c->wait_cycle = get_wait_cycle(c->op);
			else
				c->pc++;
		}
		if (c->wait_cycle > 0)
			c->wait_cycle--;
		if (c->wait_cycle == 0 && op_code_valid(c->op))
		{
			execute_instruction(vm, c);
			c->wait_cycle = -1;
		}
		c->no_live_cycle++;
		c = c->next;
	}
}

void			check(t_vm *vm)
{
	if (vm->max_check_counter == MAX_CHECKS - 1 || vm->live_counter >= NBR_LIVE)
	{
		vm->cycle_to_die -= CYCLE_DELTA;
		vm->max_check_counter = 0;
		if (vm->flags & V_FLAG)
			ft_printf("cycle_to_die is now[%d]\n", vm->cycle_to_die);
	}
	else
		vm->max_check_counter++;
	vm->live_counter = 0;
	vm->delta_cycle_counter = 0;
	update_cursor(vm, NULL);
}

t_bool			one_round(t_vm *vm)
{
	run_cursor(vm);
	if ((vm->flags & D_FLAG) && vm->cycle_total == vm->dump)
	{
		dump_mem(vm->arena);
		return (FALSE);
	}
	vm->delta_cycle_counter++;
	vm->cycle_total++;
	return (TRUE);
}

void			run_vm(t_vm *vm)
{
	while (vm->cursor_nb)
	{
		while (vm->delta_cycle_counter < vm->cycle_to_die)
		{
			if (one_round(vm) == FALSE)
				return ;
		}
		check(vm);
	}
	declare_winner(vm);
}
