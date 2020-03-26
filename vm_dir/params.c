/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <jleblond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 22:14:14 by jleblond          #+#    #+#             */
/*   Updated: 2020/02/27 13:30:09 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_type		get_type(uint8_t ocp, uint8_t param_index)
{
	if (param_index == 1)
		return (ocp >> 6);
	else if (param_index == 2)
		return ((ocp & 0b00110000) >> 4);
	else if (param_index == 3)
		return ((ocp & 0b00001100) >> 2);
	else if (param_index == 4)
		return (ocp & 0b00000011);
	else
	{
		ft_putendl_fd("Wrong parameter index", 2);
		return (0);
	}
}

int			get_type_len(char type, char dir_size)
{
	if (type == TYPE_REG)
		return (1);
	if (type == TYPE_IND)
		return (IND_SIZE);
	if (type == TYPE_DIR)
		return (dir_size);
	if (type == TYPE_ABSENT)
		return (0);
	return (0);
}

/*
** Doesn't read p4, only need p4_len to calculate newpc in case ocp wrong.
*/

void		fill_params(t_params *prm, uint8_t *arena, t_cursor *c)
{
	uint8_t	dir_len;

	ft_bzero(prm, sizeof(t_params));
	dir_len = get_dir_len(c->op);
	prm->newpc = c->pc + OPCODE_SIZE;
	prm->ocp = arena[pos(prm->newpc)];
	prm->newpc += OCP_SIZE;
	prm->p1_type = get_type(prm->ocp, 1);
	prm->p1_len = get_type_len(prm->p1_type, dir_len);
	if (prm->p1_type != TYPE_ABSENT)
		prm->p1 = read_bytes(arena, prm->newpc, prm->p1_len);
	prm->newpc += prm->p1_len;
	prm->p2_type = get_type(prm->ocp, 2);
	prm->p2_len = get_type_len(prm->p2_type, dir_len);
	if (prm->p2_type != TYPE_ABSENT)
		prm->p2 = read_bytes(arena, prm->newpc, prm->p2_len);
	prm->newpc += prm->p2_len;
	prm->p3_type = get_type(prm->ocp, 3);
	prm->p3_len = get_type_len(prm->p3_type, dir_len);
	if (prm->p3_type != TYPE_ABSENT)
		prm->p3 = read_bytes(arena, prm->newpc, prm->p3_len);
	prm->newpc += prm->p3_len;
}
