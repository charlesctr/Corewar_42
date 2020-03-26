/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <jleblond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 18:24:11 by flhember          #+#    #+#             */
/*   Updated: 2020/02/26 19:46:34 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_bool	is_digit_string(char const *s)
{
	while (*s)
	{
		if (ft_isdigit(*s))
			s += 1;
		else
			return (FALSE);
	}
	return (TRUE);
}

static t_bool	verif_size(const char *number)
{
	int		size;

	size = ft_strlen(number);
	if (size > 10)
		return (FALSE);
	if (size == 10)
	{
		if (ft_strcmp(number, "2147483647") > 0)
			return (FALSE);
	}
	return (TRUE);
}

t_bool			get_dump_value(int argc, char const **argv, int *i, t_vm *vm)
{
	int		dump;

	vm->flags = vm->flags | D_FLAG;
	if (*i + 1 < argc && is_digit_string(argv[*i + 1]))
	{
		if (verif_size(argv[*i + 1]) == FALSE)
		{
			ft_putendl_fd("ERROR: dump value must >= 0 and <= to INT_MAX", 2);
			return (FALSE);
		}
		dump = ft_atoi(argv[*i + 1]);
		if (dump < 0)
		{
			ft_putendl_fd("ERROR: dump value must >= 0\n", 2);
			return (FALSE);
		}
		vm->dump = dump;
		*i += 2;
		return (TRUE);
	}
	ft_putendl_fd("ERROR: wrong dump value\n", 2);
	return (FALSE);
}

t_bool			get_n_value(char const **argv, int *i, t_vm *vm,
					t_id_tab id_tab[MAX_PLAYERS])
{
	int		n_value;

	vm->flags = vm->flags | N_FLAG;
	if (is_digit_string(argv[*i + 1]) == FALSE
			|| is_valid_filename(argv[*i + 2]) == FALSE)
	{
		ft_putendl_fd("ERROR: wrong player id or wrong file name\n", 2);
		return (FALSE);
	}
	if (verif_size(argv[*i + 1]) == FALSE)
	{
		ft_putendl_fd("ERROR: player id must '> 0' and '<= nb of players'", 2);
		return (FALSE);
	}
	n_value = ft_atoi(argv[*i + 1]);
	if (n_value <= 0 || n_value > MAX_PLAYERS)
	{
		ft_putendl_fd("ERROR: player id must '> 0' and '<= nb of players'", 2);
		return (FALSE);
	}
	id_tab[vm->player_nb].id = n_value;
	id_tab[vm->player_nb].argv = argv[*i + 2];
	vm->player_nb++;
	*i += 3;
	return (TRUE);
}
