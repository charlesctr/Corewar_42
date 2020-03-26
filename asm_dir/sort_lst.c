/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 01:55:13 by nabih             #+#    #+#             */
/*   Updated: 2020/03/02 16:32:52 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_label				*sort_label(t_label **src)
{
	t_label		*dst;
	t_label		*tmp;

	dst = NULL;
	if (src && *src)
	{
		while (*src)
		{
			tmp = lab_pullfront(src);
			lab_pushfront(&dst, tmp);
		}
		tmp = NULL;
	}
	return (dst);
}

static int8_t		label_recheck(t_asm *a, t_champ **cmp, char *lab)
{
	t_champ		*tmp;

	tmp = NULL;
	if (lab_get(&(a->lab), lab) == NULL)
	{
		tmp = *cmp;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = a->champ;
		a->champ = *cmp;
		clear_all(a);
		return (ASM_ERROR);
	}
	return (ASM_SUCCESS);
}

static int8_t		check_label_exist(t_asm *a, t_champ **cmp)
{
	int8_t		flg;

	flg = ASM_SUCCESS;
	if ((*cmp)->lab1 != NULL)
		flg = label_recheck(a, cmp, (*cmp)->lab1);
	if (flg != ASM_ERROR && (*cmp)->lab2 != NULL)
		flg = label_recheck(a, cmp, (*cmp)->lab2);
	return (flg);
}

t_champ				*sort_champ(t_asm *a, t_champ **src)
{
	t_champ		*dst;
	t_champ		*tmp;

	dst = NULL;
	if (src && *src)
	{
		while (*src)
		{
			tmp = champ_pullfront(src);
			if (check_label_exist(a, &tmp) == ASM_ERROR)
			{
				champion_clear(src);
				champion_clear(&dst);
				return (NULL);
			}
			a->header.prog_size += champ_size_calc(tmp);
			champ_pushfront(&dst, tmp);
		}
		tmp = NULL;
	}
	return (dst);
}
