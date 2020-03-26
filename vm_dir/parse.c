/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <jleblond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:19:28 by jleblond          #+#    #+#             */
/*   Updated: 2020/02/27 13:27:24 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_bool		is_valid_filename(char const *s)
{
	int		l;

	l = ft_strlen(s);
	if (s[l - 1] == 'r' && s[l - 2] == 'o' && s[l - 3] == 'c'
			&& s[l - 4] == '.')
		return (TRUE);
	return (FALSE);
}

void		fill_option_n_value(t_id_tab id_tab[MAX_PLAYERS],
				t_id_tab cp[MAX_PLAYERS], uint8_t player_nb)
{
	uint8_t	i;

	i = 0;
	while (i < player_nb)
	{
		if (cp[i].id != 0)
		{
			id_tab[cp[i].id - 1].id = cp[i].id;
			id_tab[cp[i].id - 1].argv = cp[i].argv;
		}
		i++;
	}
}

void		set_player_id(t_id_tab id_tab[MAX_PLAYERS], uint8_t player_nb)
{
	t_id_tab	cp[MAX_PLAYERS];
	uint8_t		i;
	uint8_t		j;

	ft_memcpy(cp, id_tab, sizeof(t_id_tab) * MAX_PLAYERS);
	ft_bzero(id_tab, sizeof(t_id_tab) * MAX_PLAYERS);
	fill_option_n_value(id_tab, cp, player_nb);
	i = 0;
	j = 0;
	while (i < player_nb)
	{
		if (cp[i].id == 0)
		{
			while (id_tab[j].id && j < player_nb)
				j++;
			id_tab[j].id = j + 1;
			id_tab[j].argv = cp[i].argv;
		}
		j = 0;
		i++;
	}
}

t_bool		duplicate_in_id_tab(t_id_tab id_tab[MAX_PLAYERS])
{
	size_t	i;
	size_t	j;

	i = 0;
	j = i + 1;
	while (i < MAX_PLAYERS)
	{
		while (j < MAX_PLAYERS)
		{
			if (id_tab[i].id && id_tab[j].id && id_tab[i].id == id_tab[j].id)
			{
				ft_putendl_fd("ERROR: Player id can't be identical.", 2);
				return (TRUE);
			}
			j++;
		}
		i++;
		j = i + 1;
	}
	return (FALSE);
}

/*
** Players are all initialised with temperaty id 1, 2, 3, 4.
** if option -n activated, replace them with this value
*/

t_bool		parse(t_vm *vm, int argc, char const **argv)
{
	t_id_tab		id_tab[MAX_PLAYERS];

	ft_bzero(id_tab, sizeof(t_id_tab) * MAX_PLAYERS);
	if (parse_argv(vm, argc, argv, id_tab) == FALSE
		|| duplicate_in_id_tab(id_tab))
	{
		ft_putendl_fd("ERROR: wrong parameter", 2);
		return (FALSE);
	}
	set_player_id(id_tab, vm->player_nb);
	if (init_players(id_tab, vm) == FALSE)
		return (FALSE);
	if (parse_file(vm) == FALSE)
		return (FALSE);
	return (TRUE);
}
