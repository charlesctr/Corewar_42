/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 04:01:17 by nabih             #+#    #+#             */
/*   Updated: 2020/03/02 16:31:54 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void				champion_clear(t_champ **lst)
{
	t_champ		*tmp;

	tmp = NULL;
	if (lst && *lst)
	{
		while (*lst != NULL)
		{
			tmp = *lst;
			*lst = (*lst)->next;
			ft_memdel((void**)&(tmp->lab1));
			ft_memdel((void**)&(tmp->lab2));
			ft_memdel((void**)&tmp);
		}
	}
}

static void			label_clear(t_label **lst)
{
	t_label		*tmp;

	tmp = NULL;
	if (lst && *lst)
	{
		while (*lst != NULL)
		{
			tmp = *lst;
			*lst = (*lst)->next;
			ft_memdel((void**)&(tmp->label));
			tmp->ptr = NULL;
			ft_memdel((void**)&tmp);
		}
	}
}

void				clear_all(t_asm *a)
{
	close(a->fd);
	champion_clear(&(a->champ));
	label_clear(&(a->lab));
	ft_memdel((void**)&(a->line));
}
