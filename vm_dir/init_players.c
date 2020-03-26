/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <jleblond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 11:08:35 by jleblond          #+#    #+#             */
/*   Updated: 2020/02/25 14:11:18 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_bool		read_one_file(int fd, uint8_t **file, int *file_size)
{
	*file_size = lseek(fd, 0, SEEK_END);
	if (*file_size < 0)
	{
		ft_putendl_fd("ERROR : lseek failed", 2);
		return (FALSE);
	}
	if ((unsigned int)*file_size < sizeof(t_header)
		|| *file_size - sizeof(t_header) > CHAMP_MAX_SIZE)
	{
		ft_putendl_fd("ERROR : file size wrong", 2);
		return (FALSE);
	}
	*file = (uint8_t*)malloc(sizeof(uint8_t) * (*file_size));
	if (*file == NULL)
		return (FALSE);
	if (lseek(fd, 0, SEEK_SET) != -1 && read(fd, *file, *file_size) > 0)
		return (TRUE);
	else
	{
		free(*file);
		*file = NULL;
		return (FALSE);
	}
}

t_bool				init_one_player(char const *argv, t_vm *vm, uint8_t id)
{
	int				fd;
	int				file_size;
	uint8_t			*file;
	t_bool			ret;

	file = NULL;
	file_size = 0;
	fd = open(argv, O_RDONLY);
	if (fd < 0)
	{
		ft_putendl_fd("ERROR: Can not open player file", 2);
		return (FALSE);
	}
	if (read_one_file(fd, &file, &file_size))
	{
		vm->players[id - 1].file = file;
		vm->players[id - 1].file_size = file_size;
		vm->players[id - 1].player_id = -id;
		ret = TRUE;
	}
	else
		ret = FALSE;
	if (close(fd) == -1)
		ret = FALSE;
	return (ret);
}

t_bool				init_players(t_id_tab id_tab[MAX_PLAYERS], t_vm *vm)
{
	uint8_t i;

	i = 0;
	while (i < vm->player_nb)
	{
		if (init_one_player(id_tab[i].argv, vm, id_tab[i].id) == FALSE)
		{
			ft_putendl_fd("ERROR: Players initialization failed", 2);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}
