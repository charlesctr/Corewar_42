/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_label.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 17:56:25 by nabih             #+#    #+#             */
/*   Updated: 2020/02/14 18:55:41 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_label				*lab_new(char const *str)
{
	t_label		*tmp;

	if ((tmp = malloc(sizeof(*tmp))) == NULL)
		return (NULL);
	if ((tmp->label = ft_strdup(str)) == NULL)
	{
		ft_memdel((void**)&tmp);
		return (NULL);
	}
	tmp->ptr = NULL;
	tmp->next = NULL;
	return (tmp);
}

void				lab_pushfront(t_label **lst, t_label *ptr)
{
	t_label		*tmp;

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

t_label				*lab_pullfront(t_label **lst)
{
	t_label		*ptr;

	ptr = NULL;
	if (lst && *lst)
	{
		ptr = *lst;
		*lst = (*lst)->next;
		ptr->next = NULL;
	}
	return (ptr);
}

void				lab_add_ptr(t_label **lst_lab, t_champ **lst_champ)
{
	t_label		*tmpl;

	tmpl = NULL;
	if (lst_lab && *lst_lab && lst_champ && *lst_champ)
	{
		tmpl = *lst_lab;
		while (tmpl && tmpl->ptr != NULL)
			tmpl = tmpl->next;
		while (tmpl && tmpl->ptr == NULL)
		{
			tmpl->ptr = *lst_champ;
			tmpl = tmpl->next;
		}
	}
}

t_label				*lab_get(t_label **lst, char *str)
{
	t_label		*ptr;

	ptr = NULL;
	if (lst && *lst && str)
	{
		ptr = *lst;
		while (ptr && (ptr->label != NULL
				&& ft_strcmp(ptr->label, str) != 0))
			ptr = ptr->next;
	}
	return (ptr);
}
