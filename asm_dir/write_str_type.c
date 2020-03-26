/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_str_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 03:10:58 by nabih             #+#    #+#             */
/*   Updated: 2020/02/01 06:44:24 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void				write_str_type(int fd, char *str, int size)
{
	int			i;

	i = ft_strlen(str);
	ft_putstr_fd(str, fd);
	while (i < size)
	{
		ft_putchar_fd(0, fd);
		i++;
	}
	write_int_four_bytes(fd, 0);
}
