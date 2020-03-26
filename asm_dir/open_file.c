/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <nabih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 13:46:52 by nabih             #+#    #+#             */
/*   Updated: 2020/02/28 16:20:30 by chcoutur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				open_file(char *file)
{
	int		fd;

	if ((fd = open(file, O_RDONLY)) < 3)
		return (ASM_ERROR);
	return (fd);
}

static int		open_n_free_file(t_asm *a, char **file)
{
	if ((a->fd = open(*file, O_CREAT | O_TRUNC | O_WRONLY, 0600)) < 3)
	{
		ft_memdel((void**)file);
		return (ASM_ERROR);
	}
	ft_putstr("creation .cor: ");
	ft_putstr(*file);
	ft_putchar('\n');
	ft_memdel((void**)file);
	return (a->fd);
}

int				create_new_file(t_asm *a, char *file)
{
	int			i;
	int			size;
	char		*nfile;

	i = 0;
	size = ft_strlen(file) + 2;
	if ((nfile = malloc(sizeof(char) * (size + 1))) == NULL)
		return (-1);
	while (i < (size - 3))
	{
		nfile[i] = file[i];
		i++;
	}
	nfile[i++] = 'c';
	nfile[i++] = 'o';
	nfile[i++] = 'r';
	nfile[i] = '\0';
	return (open_n_free_file(a, &nfile));
}
