/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <jleblond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 07:12:26 by jleblond          #+#    #+#             */
/*   Updated: 2020/02/25 16:24:28 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_bool		c_lst_new(t_cursor **new)
{
	*new = (t_cursor*)malloc(sizeof(t_cursor));
	if (*new == NULL)
	{
		ft_putendl_fd("ERROR: list new malloc failed", 2);
		return (FALSE);
	}
	ft_bzero(*new, sizeof(t_cursor));
	return (TRUE);
}

t_bool		c_lst_add_top(t_cursor **alst, t_cursor *new)
{
	if (new == NULL)
	{
		ft_putendl_fd("ERROR new cursor can't be NULL", 2);
		return (FALSE);
	}
	new->next = *alst;
	new->prev = NULL;
	*alst = new;
	if (new->next)
		new->next->prev = new;
	return (TRUE);
}

void		update_cursor(t_vm *vm, t_cursor *c)
{
	t_cursor	*keep_next;

	c = vm->cursor;
	while (c)
	{
		keep_next = c->next;
		if (c->live_counter == 0)
		{
			if (vm->flags & V_FLAG)
				ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
				c->c_id, c->no_live_cycle, vm->cycle_to_die);
			if (c == vm->cursor)
				vm->cursor = c->next;
			if (c->prev)
				c->prev->next = c->next;
			if (c->next)
				c->next->prev = c->prev;
			free(c);
			c = NULL;
			vm->cursor_nb--;
		}
		else
			c->live_counter = 0;
		c = keep_next;
	}
}

t_bool		init_cursor_lst(t_vm *vm)
{
	int			i;
	t_cursor	*new;

	i = 0;
	while (i < vm->player_nb)
	{
		if (c_lst_new(&new) == FALSE)
			return (FALSE);
		new->pc = (MEM_SIZE / vm->player_nb) * i;
		new->regs[1] = vm->players[i].player_id;
		if (c_lst_add_top(&(vm->cursor), new) == FALSE)
			return (FALSE);
		vm->cursor_nb++;
		new->c_id = vm->cursor_nb;
		i++;
	}
	return (TRUE);
}
