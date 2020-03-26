/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_label.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 05:16:13 by nabih             #+#    #+#             */
/*   Updated: 2020/02/11 21:05:18 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

uint8_t				is_valide_name(char *str, int end)
{
	int			i;

	i = 0;
	while (i < end)
	{
		if (ft_strchr(LABEL_CHARS, str[i]) == NULL)
			return (ASM_FALSE);
		i++;
	}
	return (ASM_TRUE);
}

uint8_t				is_label(t_asm *a, char *str)
{
	int			i;

	i = 0;
	while (str && str[i] != '\0')
	{
		if (str[i] == ':')
		{
			if (is_valide_name(str, i) == ASM_TRUE)
			{
				str[i] = '\0';
				lab_pushfront(&(a->lab), lab_new(str));
				ft_memmove(str, &(str[i + 1]), ft_strlen(&(str[i + 1])) + 1);
				skip_start(str);
				return (ASM_TRUE);
			}
		}
		i++;
	}
	return (ASM_FALSE);
}
