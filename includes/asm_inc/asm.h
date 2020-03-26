/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <jleblond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 11:01:54 by nabih             #+#    #+#             */
/*   Updated: 2020/03/02 16:32:09 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

/*
***-------------**
**|   Includes   |
***-------------**
*/
# include "../includes.h"

/*
***-----------**
**|   Return   |
***-----------**
*/
# define ASM_SUCCESS		0
# define ASM_ERROR			-1
# define ASM_IGNORE			1

/*
***------------**
**|   Boolean   |
***------------**
*/
# define ASM_TRUE			1
# define ASM_FALSE			0

/*
***---------------**
**|   Error Type   |
***---------------**
*/
# define ASM_ERROR_AC		-1
# define ASM_ERROR_FILE		-2
# define ASM_ERROR_MALLOC	-3
# define ASM_ERROR_CODE		-4
# define ASM_ERROR_OTHER	-404

/*
***------------------**
**|   Commande Type   |
***------------------**
*/
# define T_NAME				2
# define T_COMMENT			4

/*
***--------------**
**|   Caractere   |
***--------------**
*/
# define QUOTE				'\"'
# define COMMENT_CHAR2		';'

/*
***--------------**
**|   Structure   |
***--------------**
*/
typedef struct s_champion	t_champ;
typedef struct s_label		t_label;

typedef enum		e_boolean
{
	false = 0,
	true = 1
}					t_boolean;

typedef struct		s_op
{
	char		*name;
	int			nb_arg;
	int			bnry_args[3];
	int			id;
	int			cycle_count;
	char		*comment;
	t_boolean	ocp;
	t_boolean	dir_type;
}					t_op;

struct				s_champion
{
	uint32_t	id;
	int			op;
	int			size;
	t_boolean	ocp;
	int			nb_arg;
	int			type[3];
	int			val[3];
	char		*lab1;
	char		*lab2;
	t_champ		*next;
};

struct				s_label
{
	char		*label;
	t_champ		*ptr;
	t_label		*next;
};

typedef struct		s_asm
{
	int			fd;
	int			verbose;
	int			nl;
	uint32_t	size_name;
	uint32_t	size_comment;
	char		*file;
	char		*line;
	int			op_code;
	int			pos;
	int			type;
	uint32_t	line_nb;
	t_header	header;
	t_label		*lab;
	t_champ		*champ;
}					t_asm;

/*
***--------------**
**|     Error     |
***--------------**
*/
int8_t				print_main_error(t_asm *a, char *msg);
void				print_error(int error_type, char *str, int line);
void				error_arg_check(t_asm *a, int pos,
									char *args, t_champ **ret);

/*
***--------------**
**|     Check     |
***--------------**
*/
int8_t				check_arguments(int ac);
char				*check_file(t_asm *a, int ac, char **av);
t_champ				*arguments_analysis(t_asm *a);
uint8_t				is_valide_name(char *str, int end);

/*
***----------**
**|   Files   |
***----------**
*/
int					open_file(char *file);
int					create_new_file(t_asm *a, char *file);
int8_t				get_info(t_asm *a);
int8_t				get_name_comment(t_asm *a);
int8_t				check_end_cn(char **str, int i);
int8_t				get_name(t_asm *a, char **str, int *flg);
int8_t				get_comment(t_asm *a, char **str, int *flg);
int8_t				get_code(t_asm *a);

/*
***---------**
**|   Skip   |
***---------**
*/
void				skip_start(char *str);
uint8_t				is_empty(char *str);
void				skip_empty(t_asm *a);

/*
***--------------------**
**|   Label functions   |
***--------------------**
*/
t_label				*lab_new(char const *str);
void				lab_pushfront(t_label **lst, t_label *ptr);
t_label				*lab_pullfront(t_label **lst);
void				lab_add_ptr(t_label **lst_lab, t_champ **lst_champ);
t_label				*lab_get(t_label **lst, char *str);
uint8_t				is_valide_name(char *str, int end);
uint8_t				is_label(t_asm *a, char *str);
t_label				*sort_label(t_label **src);
char				*get_label_by_ptrid(t_label **la, unsigned int id);

/*
***--------------------**
**|   Champ functions   |
***--------------------**
*/
t_champ				*champ_new(int op);
void				champ_pushfront(t_champ **lst, t_champ *ptr);
t_champ				*champ_pullfront(t_champ **lst);
int8_t				set_register(t_champ *champ, char *arg, int size, int pos);
int8_t				set_direct(t_champ *champ, char *arg, int size, int pos);
int8_t				set_indirect(t_champ *champ, char *arg, int size, int pos);
int8_t				set_label(t_asm *a, t_champ *champ, char *label, int size);
t_champ				*sort_champ(t_asm *a, t_champ **src);
int					champ_size_calc(t_champ *c);
void				champion_clear(t_champ **lst);

/*
***-----------------**
**|   Print Memory   |
***-----------------**
*/
void				write_str_type(int fd, char *str, int size);
void				write_int_four_bytes(int fd, int nb);
void				write_int_two_bytes(int fd, int nb);
void				write_int_one_byte(int fd, int nb);
void				write_header(int fd, t_header *h);
void				write_body(int fd, t_label **l, t_champ **c);
void				write_ocp(int fd, t_champ *c);

/*
***------------**
**|   Verbose   |
***------------**
*/
void				print_champ(t_header *h, t_champ **ch, t_label **la);

/*
***-------------------**
**|   Release Memory   |
***-------------------**
*/
void				clear_all(t_asm *a);

/*
***---------------**
**|   Global Var   |
***---------------**
*/
extern t_op			g_op_tab[17];

#endif
