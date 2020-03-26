/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   winner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <jleblond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 12:14:35 by jleblond          #+#    #+#             */
/*   Updated: 2020/02/26 15:54:14 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

char		*get_player_name(t_vm *vm, int id)
{
	int		i;

	i = 0;
	while (i < vm->player_nb)
	{
		if (id == vm->players[i].player_id)
			return (vm->players[i].prog_name);
		i++;
	}
	ft_printf("ERROR: Winner id(%d) doesn't exist\n", id);
	return (NULL);
}

void		declare_winner(t_vm *vm)
{
	char	*winner_name;

	winner_name = get_player_name(vm, vm->winner);
	if (winner_name)
		ft_printf("Contestant %d, \"%s\", has won !\n", -(vm->winner),
			winner_name);
}
