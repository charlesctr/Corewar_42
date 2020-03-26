/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_unit_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 10:51:15 by jleblond          #+#    #+#             */
/*   Updated: 2019/07/09 10:51:19 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		freelst(t_list *lst)
{
	t_unit		*unit;
	t_list		*keep;

	while (lst != NULL)
	{
		keep = lst->next;
		unit = unit_access(lst);
		free(lst->content);
		lst->content = NULL;
		free(lst);
		lst = keep;
	}
}

t_list		*unit_list_new(t_unit const *unit)
{
	t_list *lst;

	lst = ft_lstnew((void const *)unit, sizeof(t_unit));
	return (lst);
}

void		unit_lstadd_bot(t_list **alst, t_unit const *unit)
{
	ft_lstadd_bot(alst, unit_list_new(unit));
}

t_unit		*unit_access(t_list *lst)
{
	return ((t_unit*)lst->content);
}
