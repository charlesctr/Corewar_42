/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_analysis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 17:09:05 by nabih             #+#    #+#             */
/*   Updated: 2020/03/02 16:01:21 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int8_t		check_between(char *bet, int *size, int pos, int nb_arg)
{
	int		i;
	int		nb_sep;

	i = 0;
	nb_sep = 0;
	while ((bet[i] == ' ' || bet[i] == '\t'
			|| bet[i] == SEPARATOR_CHAR) && bet[i] != '\0'
			&& bet[i] != COMMENT_CHAR && bet[i] != COMMENT_CHAR2)
	{
		if (bet[i] == SEPARATOR_CHAR)
			nb_sep++;
		i++;
	}
	*size += i;
	if (pos < nb_arg && (bet[i] == '\0' || bet[i] == COMMENT_CHAR
						|| bet[i] == COMMENT_CHAR2))
		return (ASM_ERROR);
	else if (pos == nb_arg && nb_sep == 0
			&& (bet[i] == '\0' || bet[i] == COMMENT_CHAR
			|| bet[i] == COMMENT_CHAR2))
		return (ASM_SUCCESS);
	return ((nb_sep == 1 && pos < nb_arg) ? ASM_SUCCESS : ASM_ERROR);
}

static int8_t		prepare_lab_type(t_asm *a, t_champ *c, char *arg, int size)
{
	int8_t		ret;
	int			pos;

	pos = a->pos;
	ret = ASM_ERROR;
	if (arg[0] == DIRECT_CHAR && arg[1] == LABEL_CHAR
			&& (g_op_tab[c->op].bnry_args[pos] & T_DIR))
	{
		a->type = T_DIR;
		ret = set_label(a, c, arg + 2, size - 2);
	}
	else if (arg[0] != DIRECT_CHAR && arg[0] == LABEL_CHAR
			&& (g_op_tab[c->op].bnry_args[pos] & T_IND))
	{
		a->type = T_IND;
		ret = set_label(a, c, arg + 1, size - 1);
	}
	return (ret);
}

static int8_t		set_argument(t_asm *a, t_champ *c, int size, int pos)
{
	int8_t		ret;
	char		*arg;

	arg = a->line;
	a->pos = pos;
	if (arg[0] == 'r' && (g_op_tab[c->op].bnry_args[pos] & T_REG))
		ret = set_register(c, arg, size, pos);
	else if (arg[0] == DIRECT_CHAR && arg[1] != LABEL_CHAR
			&& (g_op_tab[c->op].bnry_args[pos] & T_DIR))
		ret = set_direct(c, arg, size, pos);
	else if (arg[0] != DIRECT_CHAR && arg[0] != LABEL_CHAR
			&& (g_op_tab[c->op].bnry_args[pos] & T_IND))
		ret = set_indirect(c, arg, size, pos);
	else
		ret = prepare_lab_type(a, c, arg, size);
	return (ret);
}

static t_champ		*init_analysis(t_asm *a, char **args, int *pos)
{
	t_champ		*ret;

	*pos = 0;
	*args = a->line;
	if ((ret = champ_new(a->op_code)) == NULL)
		return (NULL);
	return (ret);
}

t_champ				*arguments_analysis(t_asm *a)
{
	int			size;
	int			pos;
	char		*args;
	t_champ		*ret;

	if ((ret = init_analysis(a, &args, &pos)) == NULL)
		return (NULL);
	while (pos >= 0 && pos < ret->nb_arg)
	{
		size = 0;
		while (args[size] != ' ' && args[size] != '\t'
			&& args[size] != SEPARATOR_CHAR && args[size] != '\0')
			size++;
		if (set_argument(a, ret, size, pos) == ASM_ERROR)
			pos = -1;
		if (pos != -1
			&& check_between(&(args[size]),
				&size, pos + 1, ret->nb_arg) == ASM_ERROR)
			pos = -1;
		if (pos != -1)
			ft_memmove(args, &(args[size]), ft_strlen(&(args[size])) + 1);
		pos = (pos >= 0) ? pos + 1 : -1;
	}
	error_arg_check(a, pos, args, &ret);
	return (ret);
}
