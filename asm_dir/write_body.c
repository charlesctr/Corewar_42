/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_body.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 03:50:49 by nabih             #+#    #+#             */
/*   Updated: 2020/02/14 18:54:12 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void			calc_size(uint32_t id, t_champ **c, int pos, t_champ *tmpc)
{
	int			flg;

	flg = (tmpc->id == (*c)->id) ? 1 : 0;
	while (tmpc->id != id)
	{
		if (flg == 0)
			(*c)->val[pos] -= tmpc->size;
		else
			(*c)->val[pos] += tmpc->size;
		tmpc = tmpc->next;
	}
	(*c)->val[pos] -= 1;
}

static void			convert_label(t_label **l, t_champ **c, int pos)
{
	t_label		*tmpl;
	t_champ		*tmpc;
	char		*lab;

	tmpc = NULL;
	lab = ((*c)->val[pos] == 1) ? (*c)->lab1 : (*c)->lab2;
	tmpl = lab_get(l, lab);
	if (tmpl->ptr && tmpl->ptr->id == (*c)->id)
		(*c)->val[pos] = 0;
	else if (tmpl->ptr && tmpl->ptr->id < (*c)->id)
		calc_size((*c)->id, c, pos, tmpl->ptr);
	else if (tmpl->ptr && tmpl->ptr->id > (*c)->id)
		calc_size(tmpl->ptr->id, c, pos, *c);
	else
	{
		tmpc = *c;
		while (tmpc)
		{
			(*c)->val[pos] += tmpc->size;
			tmpc = tmpc->next;
		}
		(*c)->val[pos] -= 1;
	}
}

static void			check_type_body(int fd, t_label **l, t_champ *tmp, int pos)
{
	if (tmp->type[pos] & T_LAB)
		convert_label(l, &tmp, pos);
	if (tmp->type[pos] & T_REG)
		write_int_one_byte(fd, tmp->val[pos]);
	else if (tmp->type[pos] & T_DIR)
	{
		if (g_op_tab[tmp->op].dir_type == false)
			write_int_four_bytes(fd, tmp->val[pos]);
		else
			write_int_two_bytes(fd, tmp->val[pos]);
	}
	else if (tmp->type[pos] & T_IND)
		write_int_two_bytes(fd, tmp->val[pos]);
}

void				write_body(int fd, t_label **l, t_champ **c)
{
	int			pos;
	t_champ		*tmp;
	char		op;

	if (c && *c)
	{
		tmp = *c;
		while (tmp != NULL)
		{
			pos = 0;
			op = ((char)(tmp->op + 1));
			write(fd, &op, 1);
			if (g_op_tab[tmp->op].ocp == true)
				write_ocp(fd, tmp);
			while (pos < tmp->nb_arg)
			{
				check_type_body(fd, l, tmp, pos);
				pos++;
			}
			tmp = tmp->next;
		}
	}
}
