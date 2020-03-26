/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live_zjmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <jleblond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 10:09:02 by jleblond          #+#    #+#             */
/*   Updated: 2020/02/27 13:27:01 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_bool		player_id_valid(t_vm *vm, int id, int *index)
{
	int		i;

	i = 0;
	while (i < vm->player_nb)
	{
		if (id == vm->players[i].player_id)
		{
			*index = i;
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

/*
**	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
*/

void		op_live(t_vm *vm, t_cursor *c)
{
	int		player_id;
	int		player_index;
	int		new_pc;

	new_pc = c->pc + OPCODE_SIZE;
	player_id = read_bytes(vm->arena, new_pc, 4);
	new_pc += 4;
	if (player_id_valid(vm, player_id, &player_index))
	{
		vm->players[player_index].live_counter++;
		vm->winner = player_id;
		ft_printf("Player %d (%s) is alive\n", -player_id,
				get_player_name(vm, player_id));
	}
	c->no_live_cycle = 0;
	c->live_counter++;
	vm->live_counter++;
	if (vm->flags & V_FLAG)
		ft_printf("P    %d | live %d\n", c->c_id, player_id);
	if (vm->flags & P_FLAG)
		print_pc_movement(vm, 5, c->pc, new_pc);
	c->pc = new_pc;
}

/*
**  {"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
*/

void		op_zjmp(t_vm *vm, t_cursor *c)
{
	int16_t		jump;
	int16_t		new_pc;

	jump = read_bytes(vm->arena, c->pc + OPCODE_SIZE, IND_SIZE);
	if (c->carry == 1)
		new_pc = pos(c->pc + (jump % IDX_MOD));
	else
		new_pc = pos(c->pc + OPCODE_SIZE + IND_SIZE);
	if (vm->flags & V_FLAG)
		ft_printf("P    %d | zjmp %d %s\n", c->c_id, jump,
				(c->carry == 1) ? "OK" : "FAILED");
	if (vm->flags & P_FLAG)
		ft_printf("ADV  %d (%#06x -> %#06x)\n", new_pc - c->pc, c->pc, new_pc);
	c->pc = new_pc;
}
