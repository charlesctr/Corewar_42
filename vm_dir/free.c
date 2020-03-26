/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <jleblond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 11:13:06 by jleblond          #+#    #+#             */
/*   Updated: 2020/02/25 14:06:35 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		free_vm(t_vm *vm)
{
	t_cursor	*keep;

	while (vm->player_nb)
	{
		free(vm->players[vm->player_nb - 1].file);
		vm->players[vm->player_nb - 1].file = NULL;
		vm->player_nb--;
	}
	while (vm->cursor)
	{
		keep = vm->cursor->next;
		free(vm->cursor);
		vm->cursor = keep;
	}
}
