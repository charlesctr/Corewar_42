/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <jleblond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 16:44:34 by jleblond          #+#    #+#             */
/*   Updated: 2020/03/02 10:27:04 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "../includes.h"

# define OPCODE_SIZE	1
# define OCP_SIZE		1

/*
** # define D_FLAG 1 << 0
** # define N_FLAG 1 << 1
** # define V_FLAG 1 << 2
** # define P_FLAG 1 << 3
*/

# define D_FLAG 1
# define N_FLAG 2
# define V_FLAG 4
# define P_FLAG 8

typedef struct		s_id_tab
{
	const char		*argv;
	uint8_t			id;
}					t_id_tab;

typedef enum		e_type
{
	TYPE_ABSENT = 0,
	TYPE_REG = 1,
	TYPE_DIR = 2,
	TYPE_IND = 3,
}					t_type;

typedef struct		s_player
{
	char			prog_name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	uint8_t			prog_data[CHAMP_MAX_SIZE];
	unsigned int	file_size;
	uint8_t			*file;
	int				prog_size;
	int				live_counter;
	int8_t			player_id;
}					t_player;

typedef struct		s_params
{
	uint8_t			ocp;
	int32_t			p1;
	int32_t			p2;
	int32_t			p3;
	t_type			p1_type;
	t_type			p2_type;
	t_type			p3_type;
	uint8_t			p1_len;
	uint8_t			p2_len;
	uint8_t			p3_len;
	int16_t			newpc;
}					t_params;

/*
** Cursor doesn't work for a certain player.
** It just executes the code it reads from the memory.
** During the battle after operations fork or lfork,
** the new cursor will get all it's values from the parent cursor
** and not from the player.
**
** regs[0] is not used, player_id is stored at regs[1].
*/
typedef	struct		s_cursor
{
	uint32_t		regs[REG_NUMBER + 1];
	unsigned int	live_counter;
	unsigned int	c_id;
	int				wait_cycle;
	int				no_live_cycle;
	int16_t			pc;
	uint8_t			op;
	t_bool			carry;
	struct s_cursor	*next;
	struct s_cursor	*prev;
}					t_cursor;

/*
** delta_cycle_counter :    count nb of cycle since last cycle check
** winner :					last player who reported alive in each round,
**							initialised with the highest player id
*/
typedef	struct		s_vm
{
	t_player		players[MAX_PLAYERS];
	uint8_t			arena[MEM_SIZE];
	int				dump;
	uint8_t			player_nb;
	int				cycle_total;
	int				cycle_to_die;
	int				max_check_counter;
	int				delta_cycle_counter;
	int				live_counter;
	t_cursor		*cursor;
	int				cursor_nb;
	int				winner;
	char			flags;
}					t_vm;

/*
** parser
*/
void				usage(void);
t_bool				parse(t_vm *vm, int argc, char const **argv);
t_bool				get_digital_value_succeed(char *s, int *value);
t_bool				parse_argv(t_vm *vm, int argc, char const **argv,
							t_id_tab id_tab[MAX_PLAYERS]);
t_bool				get_dump_value(int argc, char const **argv, int *i,
									t_vm *vm);
t_bool				get_n_value(char const **argv, int *i, t_vm *vm,
								t_id_tab id_tab[MAX_PLAYERS]);
t_bool				parse_file(t_vm *vm);
void				dump_mem(uint8_t *arena);
t_bool				is_valid_filename(char const *s);
t_bool				init_players(t_id_tab id_tab[MAX_PLAYERS], t_vm *vm);
int32_t				read_four_bytes(uint8_t *s);

/*
** vm
*/
void				run_vm(t_vm *vm);
t_bool				init_cursor_lst(t_vm *vm);
void				execute_instruction(t_vm *vm, t_cursor *c);
void				update_cursor(t_vm *vm, t_cursor *c);
t_bool				c_lst_new(t_cursor **new);
t_bool				c_lst_add_top(t_cursor **alst, t_cursor *new);
void				declare_winner(t_vm *vm);
void				free_vm(t_vm *vm);

/*
** 16 instructions
*/
void				op_zjmp(t_vm *vm, t_cursor *c);
void				op_live(t_vm *vm, t_cursor *c);
void				op_sti(t_vm *vm, t_cursor *c);
void				op_and(t_vm *vm, t_cursor *c);
void				op_ld(t_vm *vm, t_cursor *c);
void				op_lld(t_vm *vm, t_cursor *c);
void				op_ldi(t_vm *vm, t_cursor *c);
void				op_lldi(t_vm *vm, t_cursor *c);
void				op_st(t_vm *vm, t_cursor *c);
void				op_fork(t_vm *vm, t_cursor *c);
void				op_lfork(t_vm *vm, t_cursor *c);
void				op_aff(t_vm *vm, t_cursor *c);
void				op_add(t_vm *vm, t_cursor *c);
void				op_sub(t_vm *vm, t_cursor *c);
void				op_or(t_vm *vm, t_cursor *c);
void				op_xor(t_vm *vm, t_cursor *c);

/*
**	tools for instructions
*/
void				fill_params(t_params *prm, uint8_t *arena, t_cursor *c);
int32_t				read_bytes(uint8_t *s, int16_t addr, uint8_t nb_of_bytes);
void				write_4_bytes(uint8_t *arena, int16_t address,
									uint32_t value);
int16_t				pos(int16_t pc);
uint32_t			get_reg_size_value(t_vm *vm, t_cursor *c, t_type type,
										int32_t p);
uint16_t			get_ind_size_value(t_vm *vm, t_cursor *c, t_type type,
										int32_t p);
t_bool				op_code_valid(unsigned char op);
uint8_t				get_dir_len(uint8_t opcode);
t_bool				is_3_types(t_type type, uint32_t p_value);
t_bool				is_dir_or_ind(t_type type);
t_bool				is_dir_or_reg(t_type type, uint32_t p_value);
t_bool				is_reg_type(t_type type, uint32_t p_value);
void				print(unsigned int id, char *s, t_params *p);
char				*get_player_name(t_vm *vm, int id);
void				print_pc_movement(t_vm *vm, int nb_bytes, int pc,
										int newpc);

#endif
