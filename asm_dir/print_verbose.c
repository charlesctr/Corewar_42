/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_verbose.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 16:12:32 by nabih             #+#    #+#             */
/*   Updated: 2020/02/28 16:43:56 by chcoutur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void			print_header(t_header *h)
{
	ft_putstr(".name => ");
	ft_putstr(h->prog_name);
	ft_putchar('\n');
	ft_putstr(".comment => ");
	ft_putstr(h->comment);
	ft_putchar('\n');
	ft_putstr("Size => ");
	ft_putnbr(h->prog_size);
	ft_putstr("\n\n");
}

static void			print_type_arg(t_champ *tmp, int pos)
{
	if ((tmp->type[pos] & T_REG))
	{
		ft_putstr("T_REG[");
		ft_putchar('r');
		ft_putnbr(tmp->val[pos]);
		ft_putchar(']');
	}
	else if (((tmp->type[pos] & T_IND)
			|| (tmp->type[pos] & T_DIR))
			&& !(tmp->type[pos] & T_LAB))
	{
		if (tmp->type[pos] & T_IND)
			ft_putstr("T_IND[");
		else
			ft_putstr("T_DIR[");
		ft_putnbr(tmp->val[pos]);
		ft_putchar(']');
	}
	else if (tmp->type[pos] & T_LAB)
	{
		ft_putstr("T_LAB[");
		ft_putnbr(tmp->val[pos]);
		ft_putchar(']');
	}
}

static void			print_one_column(unsigned int address, t_champ *tmp)
{
	ft_putnbr(address);
	ft_putstr("\t\t");
	ft_putstr(g_op_tab[tmp->op].name);
	ft_putstr("\t\t");
	(tmp->type[0] > 0) ? print_type_arg(tmp, 0) : ft_putstr("-\t");
	ft_putstr("\t");
	(tmp->type[1] > 0) ? print_type_arg(tmp, 1) : ft_putstr("-\t");
	ft_putstr("\t");
	(tmp->type[2] > 0) ? print_type_arg(tmp, 2) : ft_putstr("-\t");
	ft_putstr("\t");
}

void				print_champ(t_header *h, t_champ **ch, t_label **la)
{
	unsigned int	address;
	t_champ			*tmp;
	char			*label;

	address = 0;
	tmp = NULL;
	label = NULL;
	print_header(h);
	if (ch && *ch)
	{
		tmp = *ch;
		ft_putstr("ADDR\t\tCMD\t\tARG1\t\tARG2\t\tARG3\t\tREF by LABEL\n");
		while (tmp != NULL)
		{
			print_one_column(address, tmp);
			if ((label = get_label_by_ptrid(la, tmp->id)) != NULL)
				ft_putstr(label);
			ft_putchar('\n');
			address += tmp->size;
			tmp = tmp->next;
		}
	}
}
