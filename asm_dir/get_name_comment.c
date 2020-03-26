/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_name_comment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 12:52:03 by nabih             #+#    #+#             */
/*   Updated: 2020/02/29 16:40:58 by chcoutur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int8_t		choose_name_or_comment(t_asm *a, int *flg)
{
	int			size_name;
	int			size_comment;

	size_name = ft_strlen(NAME_CMD_STRING);
	size_comment = ft_strlen(COMMENT_CMD_STRING);
	if (ft_strncmp(a->line, NAME_CMD_STRING, size_name) == 0)
	{
		if (get_name(a, &(a->line), flg) == ASM_ERROR)
			return (ASM_ERROR);
	}
	else if (ft_strncmp(a->line, COMMENT_CMD_STRING, size_comment) == 0)
	{
		if (get_comment(a, &(a->line), flg) == ASM_ERROR)
			return (ASM_ERROR);
	}
	else
		return (ASM_ERROR);
	return (ASM_SUCCESS);
}

int8_t				check_end_cn(char **str, int i)
{
	char		c;

	while ((*str)[i] != '\"')
		i--;
	i++;
	while (((*str)[i] == ' ' || (*str)[i] == '\t')
			&& (*str)[i] != '\0' && (*str)[i] != COMMENT_CHAR
			&& (*str)[i] != COMMENT_CHAR2)
		i++;
	c = (*str)[i];
	ft_memdel((void**)str);
	return ((c == COMMENT_CHAR
			|| c == COMMENT_CHAR2
			|| c == '\0') ? ASM_SUCCESS : ASM_ERROR);
}

int8_t				get_name_comment(t_asm *a)
{
	int			i;
	int			flg;

	i = 1;
	flg = 0;
	while (a->line != NULL && i == 1 && !(flg & T_NAME && flg & T_COMMENT))
	{
		skip_empty(a);
		skip_start(a->line);
		if (choose_name_or_comment(a, &flg) == ASM_ERROR)
			return (ASM_ERROR);
		i = get_next_line_eof(a->fd, &(a->line), &(a->nl));
		a->line_nb += 1;
	}
	return ((flg & T_NAME && flg & T_COMMENT) ? ASM_SUCCESS : ASM_ERROR);
}
