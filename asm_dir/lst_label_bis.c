/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_label_bis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 19:51:25 by naali             #+#    #+#             */
/*   Updated: 2020/02/12 19:56:23 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char				*get_label_by_ptrid(t_label **la, unsigned int id)
{
	t_label		*tmp;

	tmp = *la;
	while (tmp != NULL && tmp->ptr != NULL)
	{
		if (tmp->ptr->id == id)
			return (tmp->label);
		tmp = tmp->next;
	}
	return (NULL);
}
