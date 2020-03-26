/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 13:54:18 by nabih             #+#    #+#             */
/*   Updated: 2020/02/29 17:18:31 by chcoutur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void				skip_start(char *str)
{
	int			i;
	int			size;

	i = 0;
	if (str)
	{
		while (((str[i] > 7 && str[i] < 14) || str[i] == 32)
				&& str[i] != '\0')
			i++;
	}
	if (i > 0)
	{
		size = ft_strlen(&(str[i]));
		str[i - 1] = '\0';
		ft_memmove(str, &(str[i]), size + 1);
	}
}

uint8_t				is_empty(char *str)
{
	int		i;

	i = 0;
	while (str != NULL && ((str[i] == ' ' || str[i] == '\t')
			&& str[i] != '\0'))
		i++;
	return ((str == NULL || str[i] == '\0'
			|| str[i] == COMMENT_CHAR
			|| str[i] == COMMENT_CHAR2) ? ASM_TRUE : ASM_FALSE);
}

void				skip_empty(t_asm *a)
{
	int			flg;

	flg = 1;
	while (is_empty(a->line) == ASM_TRUE && flg != 0)
	{
		ft_memdel((void**)&(a->line));
		flg = get_next_line_eof(a->fd, &(a->line), &(a->nl));
		a->line_nb += 1;
	}
	if (flg == 0)
		ft_memdel((void**)&(a->line));
}
