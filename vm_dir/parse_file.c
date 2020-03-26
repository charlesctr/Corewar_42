/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <jleblond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 12:27:04 by jleblond          #+#    #+#             */
/*   Updated: 2020/02/27 13:34:54 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_bool		get_name(uint8_t *s, t_player *p)
{
	ft_memcpy(p->prog_name, s, PROG_NAME_LENGTH + 1);
	if (ft_strlen(p->prog_name) == 0)
	{
		ft_putendl_fd("ERROR: champion name can't be empty", 2);
		return (FALSE);
	}
	s += PROG_NAME_LENGTH;
	if (s[0] || s[1] || s[2] || s[3])
	{
		ft_putendl_fd("ERROR: name string shold be followed \
by 4 bytes of 0", 2);
		return (FALSE);
	}
	return (TRUE);
}

static t_bool		get_comment(uint8_t *s, t_player *p)
{
	ft_memcpy(p->comment, s, COMMENT_LENGTH + 1);
	s += COMMENT_LENGTH;
	if (s[0] || s[1] || s[2] || s[3])
	{
		ft_putendl_fd("ERROR: comment string shold be followed \
by 4 bytes of 0\n", 2);
		return (FALSE);
	}
	return (TRUE);
}

/*
** parcourir header dans .cor, stock "prog_name" et "comments",
** verifier "magic" et "prog_size".
**
** typedef struct		header_s
** {
**   unsigned int		magic;
**   char				prog_name[PROG_NAME_LENGTH + 1];
**   unsigned int		prog_size;
**   char				comment[COMMENT_LENGTH + 1];
** }					t_header;
*/

static t_bool		parse_one_player_header(t_player *p)
{
	uint8_t			*s;

	s = p->file;
	if (read_four_bytes(s) != COREWAR_EXEC_MAGIC)
	{
		ft_putendl_fd("ERROR: wrong magic nb in header", 2);
		return (FALSE);
	}
	s += sizeof(unsigned int);
	if (get_name(s, p) == FALSE)
		return (FALSE);
	s += PROG_NAME_LENGTH + 4;
	p->prog_size = read_four_bytes(s);
	if (p->prog_size != p->file_size - sizeof(t_header))
	{
		ft_putendl_fd("ERROR: wrong prog_size in header", 2);
		return (FALSE);
	}
	s += 4;
	if (get_comment(s, p) == FALSE)
		return (FALSE);
	return (TRUE);
}

static void			cp_prog_data(t_player *p)
{
	ft_memcpy(p->prog_data, p->file + sizeof(t_header), p->prog_size);
}

t_bool				parse_file(t_vm *vm)
{
	int		i;

	i = 0;
	while (i < vm->player_nb)
	{
		if (parse_one_player_header(&(vm->players[i])) == FALSE)
			return (FALSE);
		cp_prog_data(&(vm->players[i]));
		i++;
	}
	return (TRUE);
}
