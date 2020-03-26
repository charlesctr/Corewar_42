/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_code.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 15:01:11 by nabih             #+#    #+#             */
/*   Updated: 2020/03/02 16:03:24 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void			check_op_bis(char *str, size_t size)
{
	if (str[size] == DIRECT_CHAR)
		str[size - 1] = '\0';
	else
		str[size] = '\0';
	if (str[size] == DIRECT_CHAR)
		ft_memmove(str, &(str[size]), ft_strlen(&(str[size])) + 1);
	else
		ft_memmove(str, &(str[size + 1]),
					ft_strlen(&(str[size + 1])) + 1);
}

int8_t				check_op(char *str, size_t size)
{
	int			op_code;

	op_code = 0;
	while (g_op_tab[op_code].name != NULL && str && size > 0)
	{
		if (ft_strncmp(g_op_tab[op_code].name, str, size) == 0)
		{
			if (str[size] == ' ' || str[size] == '\t'
				|| str[size] == DIRECT_CHAR)
			{
				check_op_bis(str, size);
				skip_start(str);
				return (op_code);
			}
			else
			{
				ft_putstr_fd("Command not well formated\n", 2);
				return (ASM_ERROR);
			}
		}
		op_code++;
	}
	ft_putstr_fd("Error 404 command not found\n", 2);
	return (ASM_ERROR);
}

int8_t				check_line(t_asm *a, int *lab)
{
	int			size;
	t_champ		*tmp;

	tmp = NULL;
	if (a->line != NULL && *(a->line) != '\0')
	{
		size = 0;
		while ((a->line)[size] != ' ' && (a->line)[size] != '\t'
				&& (a->line)[size] != DIRECT_CHAR && (a->line)[size] != '\0')
			size++;
		if ((a->op_code = check_op(a->line, size)) == ASM_ERROR)
			return (ASM_ERROR);
		else
		{
			if ((tmp = arguments_analysis(a)) == NULL)
				return (ASM_ERROR);
			champ_pushfront(&(a->champ), tmp);
			if (*lab == 1 && a->champ)
			{
				*lab = 0;
				lab_add_ptr(&(a->lab), &(a->champ));
			}
		}
	}
	return (ASM_SUCCESS);
}

int8_t				get_code(t_asm *a)
{
	int			flg;
	int			lab;

	flg = 1;
	lab = 0;
	while (a->line != NULL && flg == 1 && a->nl == 0)
	{
		skip_empty(a);
		if (a->nl == 0)
		{
			skip_start(a->line);
			if (is_label(a, a->line) == ASM_TRUE)
				lab = 1;
			if (is_empty(a->line) == ASM_FALSE
				&& check_line(a, &lab) == ASM_ERROR)
				return (ASM_ERROR);
			ft_memdel((void**)&(a->line));
			flg = get_next_line_eof(a->fd, &(a->line), &(a->nl));
			a->line_nb += 1;
		}
	}
	if (is_empty(a->line) == ASM_FALSE && a->nl == 1)
		return (ASM_ERROR);
	ft_memdel((void**)&(a->line));
	return (ASM_SUCCESS);
}
