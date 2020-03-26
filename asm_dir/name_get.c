/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 19:57:17 by naali             #+#    #+#             */
/*   Updated: 2020/02/29 16:40:29 by chcoutur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int8_t		copy_quote_name(t_asm *a, char **str, int32_t i)
{
	while (*str && (*str)[i] != '\"' && a->size_name < PROG_NAME_LENGTH)
	{
		if ((*str)[i] != '\0')
		{
			a->header.prog_name[a->size_name] = (*str)[i++];
			a->size_name += 1;
		}
		else if ((*str)[i] == '\0')
		{
			i = 0;
			ft_memdel((void**)str);
			get_next_line_eof(a->fd, str, &(a->nl));
			a->line_nb += 1;
			a->header.prog_name[(a->size_name)++] = '\n';
		}
	}
	if (*str && (*str)[i++] == '\"' && (a->size_name < PROG_NAME_LENGTH))
		a->header.prog_name[a->size_name] = '\0';
	else
		return (ASM_ERROR);
	return (check_end_cn(str, ft_strlen(*str) - 1));
}

int8_t				get_name(t_asm *a, char **str, int *flg)
{
	int32_t		i;

	i = ft_strlen(NAME_CMD_STRING);
	if (*flg & T_NAME)
		return (ASM_ERROR);
	*flg |= T_NAME;
	while ((*str)[i] != '\"' && (*str)[i] != '\0')
	{
		if ((*str)[i] != ' ' && (*str)[i] != '\t')
			return (ASM_ERROR);
		i++;
	}
	if ((*str)[i] == '\0')
		return (ASM_ERROR);
	i++;
	return (copy_quote_name(a, str, i));
}
