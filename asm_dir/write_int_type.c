/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_int_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 03:15:03 by nabih             #+#    #+#             */
/*   Updated: 2020/02/01 07:16:31 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void				write_int_four_bytes(int fd, int nb)
{
	char	bytes[4];

	bytes[0] = (nb & 0xFF000000) >> 24;
	bytes[1] = (nb & 0xFF0000) >> 16;
	bytes[2] = (nb & 0xFF00) >> 8;
	bytes[3] = (nb & 0xFF);
	write(fd, bytes, 4);
}

void				write_int_two_bytes(int fd, int nb)
{
	char	bytes[2];

	bytes[0] = (nb & 0xFF00) >> 8;
	bytes[1] = (nb & 0xFF);
	write(fd, bytes, 2);
}

void				write_int_one_byte(int fd, int nb)
{
	char	byte;

	byte = (nb & 0xFF);
	write(fd, &byte, 1);
}
