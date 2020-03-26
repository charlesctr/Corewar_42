/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_champion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 02:44:05 by nabih             #+#    #+#             */
/*   Updated: 2020/02/14 18:50:50 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_champ				*champ_new(int op)
{
	static unsigned int	id = 0;
	t_champ				*ptr;

	ptr = NULL;
	if (op >= 0 && op < 16)
	{
		if ((ptr = malloc(sizeof(*ptr))) == NULL)
			return (NULL);
		ft_bzero(ptr, sizeof(*ptr));
		ptr->id = id++;
		ptr->op = op;
		ptr->ocp = g_op_tab[op].ocp;
		ptr->nb_arg = g_op_tab[op].nb_arg;
	}
	return (ptr);
}

void				champ_pushfront(t_champ **lst, t_champ *ptr)
{
	t_champ		*tmp;

	tmp = NULL;
	if (lst && *lst && ptr)
	{
		tmp = *lst;
		ptr->next = tmp;
		*lst = ptr;
	}
	else if (lst && *lst == NULL && ptr)
		*lst = ptr;
}

t_champ				*champ_pullfront(t_champ **lst)
{
	t_champ		*ptr;

	ptr = NULL;
	if (lst && *lst)
	{
		ptr = *lst;
		*lst = ptr->next;
		ptr->next = NULL;
	}
	return (ptr);
}

int					champ_size_calc(t_champ *c)
{
	int			i;
	int			size;

	i = 0;
	size = 1;
	if (c->ocp == true)
		size++;
	while (i < c->nb_arg)
	{
		if (c->type[i] & T_REG)
			size++;
		else if (c->type[i] & T_DIR)
		{
			if (g_op_tab[c->op].dir_type == false)
				size += 4;
			else
				size += 2;
		}
		else if (c->type[i] & T_IND)
			size += 2;
		i++;
	}
	c->size = size;
	return (size);
}
