/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comment_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 19:58:40 by naali             #+#    #+#             */
/*   Updated: 2020/03/02 09:56:08 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int8_t		copy_quote_comment(t_asm *a, char **str, int32_t i)
{
	while (*str && (*str)[i] != '\"' && a->size_comment < COMMENT_LENGTH)
	{
		if ((*str)[i] != '\0')
		{
			a->header.comment[a->size_comment] = (*str)[i];
			a->size_comment += 1;
			i++;
		}
		else if ((*str)[i] == '\0')
		{
			i = 0;
			ft_memdel((void**)str);
			get_next_line_eof(a->fd, str, &(a->nl));
			a->line_nb += 1;
			a->header.comment[(a->size_comment)++] = '\n';
		}
	}
	if (*str && (*str)[i] == '\"' && (a->size_comment < COMMENT_LENGTH))
		a->header.comment[a->size_comment] = '\0';
	else
		return (ASM_ERROR);
	return (check_end_cn(str, ft_strlen(*str) - 1));
}

int8_t				get_comment(t_asm *a, char **str, int *flg)
{
	int32_t		i;

	i = ft_strlen(COMMENT_CMD_STRING);
	if (*flg & T_COMMENT)
		return (ASM_ERROR);
	*flg |= T_COMMENT;
	while ((*str)[i] != '\"' && (*str)[i] != '\0')
	{
		if ((*str)[i] != ' ' && (*str)[i] != '\t')
			return (ASM_ERROR);
		i++;
	}
	if ((*str)[i] == '\0')
		return (ASM_ERROR);
	i++;
	return (copy_quote_comment(a, str, i));
}
