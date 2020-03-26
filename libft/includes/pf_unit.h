/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_unit.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 10:33:18 by jleblond          #+#    #+#             */
/*   Updated: 2019/07/09 10:33:56 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PF_UNIT_H
# define PF_UNIT_H

# include "libft.h"
# include <stdint.h>

# define PRECISION_NULL -1

typedef	enum			e_unit_type
{
	TYPE_LTR = 1,
	TYPE_C,
	TYPE_S,
	TYPE_D,
	TYPE_F,
	TYPE_P,
	TYPE_OXX,
	TYPE_O,
	TYPE_X,
	TYPE_X_MAJ,
	TYPE_U,
	TYPE_B,
}						t_unit_type;

typedef enum			e_modifier
{
	MD_H = 1,
	MD_HH,
	MD_L,
	MD_LL,
	MD_MAG_L,
}						t_modifier;

typedef struct			s_type_ltr
{
	const char			*literal;
	int					len;
}						t_type_ltr;

typedef struct			s_type_c
{
	t_bool				flag_minus;
	int					width;
	t_bool				modifier_l;
	wchar_t				character;
}						t_type_c;

typedef struct			s_type_s
{
	t_bool				flag_minus;
	int					width;
	unsigned int		precision;
	t_bool				modifier_l;
	const char			*string;
}						t_type_s;

typedef struct			s_type_d
{
	t_bool				flag_minus;
	t_bool				flag_plus;
	t_bool				flag_zero;
	t_bool				flag_blank;
	int					width;
	unsigned int		precision;
	int					modifier;
	intmax_t			integer;
}						t_type_d;

typedef struct			s_type_b
{
	t_bool				flag_minus;
	t_bool				flag_plus;
	t_bool				flag_zero;
	t_bool				flag_blank;
	t_bool				flag_hash;
	int					width;
	unsigned int		precision;
	int					modifier;
	intmax_t			un_int;
}						t_type_b;

typedef struct			s_type_oxx
{
	t_bool				flag_minus;
	t_bool				flag_hash;
	t_bool				flag_zero;
	int					width;
	int					precision;
	int					modifier;
	unsigned long long	un_int;
	t_unit_type			sub_type;
}						t_type_oxx;

typedef struct			s_type_u
{
	t_bool				flag_minus;
	t_bool				flag_zero;
	int					width;
	unsigned int		precision;
	int					modifier;
	unsigned long long	un_int;
}						t_type_u;

typedef struct			s_type_f
{
	t_bool				flag_minus;
	t_bool				flag_plus;
	t_bool				flag_zero;
	t_bool				flag_blank;
	t_bool				flag_hash;
	int					width;
	unsigned int		precision;
	int					modifier;
	long double			doub;
}						t_type_f;

typedef struct			s_type_p
{
	t_bool				flag_minus;
	t_bool				flag_zero;
	int					width;
	int					precision;
	uintmax_t			pointer;
}						t_type_p;

typedef	union			u_unit_union
{
	t_type_ltr			ltr;
	t_type_c			c;
	t_type_s			s;
	t_type_d			d;
	t_type_f			f;
	t_type_p			p;
	t_type_oxx			oxx;
	t_type_u			u;
	t_type_b			b;
}						t_unit_union;

typedef union			u_inf_check
{
	unsigned long long	l;
	double				d;
}						t_inf_check;

typedef struct			s_unit
{
	t_unit_union		val;
	t_unit_type			type;
}						t_unit;

t_unit					*unit_access(t_list *lst);
void					unit_lstadd_bot(t_list **alst, t_unit const *unit);
void					freelst(t_list *list);

#endif
