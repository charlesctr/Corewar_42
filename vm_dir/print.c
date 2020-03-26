/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <jleblond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 11:39:09 by jleblond          #+#    #+#             */
/*   Updated: 2020/02/27 13:30:49 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_pc_movement(t_vm *vm, int nb_bytes, int pc, int newpc)
{
	int		i;
	uint8_t	p;

	if (nb_bytes < 1 || nb_bytes > 10)
		return ;
	i = 0;
	ft_printf("ADV  %d (%#06x -> %#06x)", newpc - pc, pc,
			newpc);
	while (i < nb_bytes)
	{
		p = vm->arena[pos(pc + i)];
		i++;
		ft_printf(" %02x", p);
	}
	ft_printf("\n");
}
