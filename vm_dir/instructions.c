/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <jleblond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 20:48:09 by jleblond          #+#    #+#             */
/*   Updated: 2020/02/25 14:10:40 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	none(t_vm *vm, t_cursor *c)
{
	(void)vm;
	(void)c;
}

/*
** if opcode invalid, go to next byte.
**
** Given opcode starts at 0x01, to get the right function directly with
** op_dispatch[op_code], I put none() in op_dispatch[0] to occupy the place,
** it will not be used.
**
** Tous les adressages sont relatifs au PC et à IDX_MOD sauf pour lld, lldi et
**lfork.
*/

void		execute_instruction(t_vm *vm, t_cursor *c)
{
	static void (*op_dispatch[17])() = {none,
		op_live, op_ld, op_st, op_add, op_sub, op_and, op_or, op_xor, op_zjmp,
		op_ldi, op_sti, op_fork, op_lld, op_lldi, op_lfork, op_aff};

	op_dispatch[c->op](vm, c);
}
