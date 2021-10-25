/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 14:52:05 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/23 23:42:50 by psleziak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "mlx.h"
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/errno.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <sys/errno.h>
# include <termios.h>
# include <curses.h>
# include <term.h>

# define ESC 	53
# define X		17
# define F		3
# define k_A	0
# define k_S	1
# define k_W	13
# define k_D	2

typedef	struct s_map
{
	char	**map;
	char	**args;
	char	**RGB;
	int		fd;
	int		current_x_position;
	int		current_y_position;
	int		next_x_position;
	int		next_y_position;
	char	player_facing_dir;
	int		window_width;
	int		window_height;
	int		FR;
	int		FG;
	int		FB;
	int		CR;
	int		CG;
	int		CB;
	char	*N;
	char	*S;
	char	*E;
	char	*W;
	int		last_line;
	int		longest_line;
	float	unit_x_size;
	float	unit_y_size;
}				t_map;

typedef	struct	s_window
{
	void	*mlx_p;
	void	*win_p;
	void	*xpm_image;
}
				t_window;

typedef struct s_img
{
	int		bpp;
	int		endian;
	int		size_line;
	void	*img_ptr;
} t_img;

typedef struct s_master
{
	t_map		map;
	t_window	window;
} t_master;

/****MAP****/
int		ft_map_parse(t_map *map, char *argc);
int		ft_get_next_line(t_map *map);
int		ft_count_longest_line(t_map *map);
int		ft_check_de_map(t_map *map);
void	ft_resize_map_to_square(t_map *map, int l);
void	ft_print_map(t_map *map);

/****WINDOW****/
void	ft_map_create(t_master *master);
void	ft_put_pixel(t_master *master, int x, int y);

/****FREE and CLEAN****/
void	ft_free_memory(t_map *map);

/*
typedef struct s_minishell
{
	char			*input;
	t_list			*env;
	char			**path;
	char			**argv;
	struct termios	term;
	char			*prompt;
	char			*cwd;
	int				fd;
	unsigned char	exit_code;
}				t_minishell;

t_minishell	g_mini;

void	ft_echon(void);
void	ft_echo(void);
void	ft_cd(void);
void	ft_pwd(void);
void	ft_export(void);
void	ft_unset(void);
void	ft_env(void);
void	ft_exit(void);
void	ft_path(void);

void	ft_handler(int signal);*/

/* ERROS AND CLEAN */

int		ft_clear_data(char c);
void	ft_error_exit(const char *errmessage);
int		ft_error_handler(const char *errmessage);

/* DOLLAR */

void	ft_dollar_sign(char *argv);
void	ft_expand_var(char *argv);

/* LINKED LIST EXTRAS */

#endif
