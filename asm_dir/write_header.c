/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 03:04:12 by nabih             #+#    #+#             */
/*   Updated: 2020/02/01 03:46:00 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void				write_header(int fd, t_header *h)
{
	write_int_four_bytes(fd, h->magic);
	write_str_type(fd, h->prog_name, PROG_NAME_LENGTH);
	write_int_four_bytes(fd, h->prog_size);
	write_str_type(fd, h->comment, COMMENT_LENGTH);
}
