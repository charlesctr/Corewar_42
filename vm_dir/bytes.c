/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bytes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <jleblond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 14:45:55 by jleblond          #+#    #+#             */
/*   Updated: 2020/02/27 13:34:46 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int32_t		read_bytes(uint8_t *s, int16_t addr, uint8_t nb_of_bytes)
{
	int32_t	ret;

	ret = 0;
	if (nb_of_bytes == 4)
		ret = s[pos(addr)] << 24 | s[pos(addr + 1)] << 16
	| s[pos(addr + 2)] << 8 | s[pos(addr + 3)];
	else if (nb_of_bytes == 2)
		ret = (int16_t)(s[pos(addr)] << 8 | s[pos(addr + 1)]);
	else if (nb_of_bytes == 1)
		ret = (int8_t)(s[pos(addr)]);
	else
	{
		ft_printf("nb_of_bytes [%d] wrong\n", nb_of_bytes);
	}
	return (ret);
}

void		write_4_bytes(uint8_t *arena, int16_t addr, uint32_t value)
{
	arena[pos(addr)] = (value & 0xff000000) >> 24;
	arena[pos(addr + 1)] = (value & 0x00ff0000) >> 16;
	arena[pos(addr + 2)] = (value & 0x0000ff00) >> 8;
	arena[pos(addr + 3)] = (value & 0x000000ff);
}

int32_t		read_four_bytes(uint8_t *s)
{
	int32_t	ret;

	ret = s[0] << 24 | s[1] << 16 | s[2] << 8 | s[3];
	return (ret);
}
