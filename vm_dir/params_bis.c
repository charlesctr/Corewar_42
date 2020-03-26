/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <jleblond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 14:48:39 by jleblond          #+#    #+#             */
/*   Updated: 2020/02/27 13:30:20 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_bool		is_reg_type(t_type type, uint32_t p_value)
{
	return (type == TYPE_REG && p_value > 0 && p_value < 17);
}

t_bool		is_3_types(t_type type, uint32_t p_value)
{
	return (is_reg_type(type, p_value) || type == TYPE_DIR
		|| type == TYPE_IND);
}

t_bool		is_dir_or_ind(t_type type)
{
	return (type == TYPE_DIR || type == TYPE_IND);
}

t_bool		is_dir_or_reg(t_type type, uint32_t p_value)
{
	return (type == TYPE_DIR || is_reg_type(type, p_value));
}
