/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <nabih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 11:31:28 by nabih             #+#    #+#             */
/*   Updated: 2020/03/02 16:16:45 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void			print_asm_usage(void)
{
	ft_putstr_fd("Usage: ./asm [-v=verbose] [champion.s]\n", 2);
}

int8_t				print_main_error(t_asm *a, char *msg)
{
	clear_all(a);
	if (msg != NULL)
		print_error(ASM_ERROR_OTHER, msg, 0);
	return (ASM_ERROR);
}

void				print_error(int error_type, char *str, int line)
{
	if (error_type == ASM_ERROR_AC)
		print_asm_usage();
	else if (error_type == ASM_ERROR_FILE)
		ft_putstr_fd("File error\n", 2);
	else if (error_type == ASM_ERROR_MALLOC)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(":\nAllocation error\n", 2);
	}
	else if (error_type == ASM_ERROR_CODE)
	{
		ft_putstr_fd("Error line: ", 2);
		ft_putnbr_fd(line, 2);
		ft_putchar_fd('\n', 2);
	}
	else
	{
		ft_putstr_fd("ERROR from: \"", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\"\n", 2);
	}
}

void				error_arg_check(t_asm *a, int pos,
									char *args, t_champ **ret)
{
	if (pos == -1)
	{
		ft_putstr_fd("Arguments not well formated -> |", 2);
		(args != NULL) ? ft_putstr_fd(args, 2) : ft_putstr_fd("(null)", 2);
		ft_putstr_fd("|\n", 2);
		clear_all(a);
		ft_memdel((void**)&((*ret)->lab1));
		ft_memdel((void**)&((*ret)->lab2));
		ft_memdel((void**)ret);
	}
}
