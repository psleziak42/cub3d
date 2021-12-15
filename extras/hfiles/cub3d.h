/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 14:52:05 by bcosters          #+#    #+#             */
/*   Updated: 2021/12/15 18:17:19 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "../libft/libft.h"
# include <math.h>
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
# include <limits.h>

# define PI		3.14159265359
# define P2		PI/2
# define P3		3 * PI / 2
# define F0V	PI / 3 / DEGREE
# define DEGREE	0.01745329251
# define X		17
# define ESC 	53
# define K_W	13
# define K_S	1
# define K_A	0
# define ARR_L	123
# define K_D	2
# define ARR_R	124
# define TEXT	64
# define SPEED	5
# define ROT	3
# define N		0
# define S		1
# define E		2
# define W		3
# define WL		0
# define BG		1
# define F		1
# define C		0

typedef struct s_map
{
	char	**map;
	char	**args;
	char	**rgb;
	int		fd;
	int		win_wid;
	int		win_hei;
	int		c_f[2][3];
	char	*nsew[4];
	int		last_line;
	int		longest_line;
}	t_map;

typedef struct s_win
{
	void	*mlx_p;
	void	*win_p;
}				t_win;

typedef struct s_s_map
{
	void	*img_instance;
	char	*img_file;
	int		img_wid;
	int		img_hei;
}	t_s_map;

typedef struct	s_img
{
	void	*img_inst;
	char	*img_address;
	int		bpp;
	int		line_len;
	int		endian;
	int		img_wid;
	int		img_hei;
}	t_img;

typedef struct s_trigonometry
{
	float	px_y;
	float	px_x;
	float	angle;
	float	unit_y_size;
	float	unit_x_size;
	float	line_h_3d;
	float	line_o_3d;
}				t_trigo;

/****MAP****/
int		ft_get_next_line(t_map *map);
int		ft_count_longest_line(t_map *map);
void	ft_resize_map_to_square(int l, t_map *map);
int		ft_check_de_map(t_map *map, t_trigo *trigo);
void	ft_print_map(void);

/****MAP_UTILS****/
bool	is_wrong_color(int r, int g, int b);
bool	is_valid_char(char c, char *compound);

/****WINDOW****/
void	ft_printmap_to_window(t_trigo *trigo);
//void	ft_put_pixel(t_master *master, int x, int y);

/****KEY****/
int		key_release(int key);
int		ft_update_position(int key, t_trigo *trigo);

/****RAYCASTING****/
void	ft_raycasting(t_trigo *trigo);

/****PRINTING****/
void	ft_update_walls(t_trigo *trigo, int x, int dir, float ra);
void	ft_update_bg(void);

/****FREE and CLEAN****/
void	ft_free_memory(void);
void	free_dp(char **dp);
int		ft_close_window();

/****SINGLETONES****/
t_map	*get_map(t_map *map);
t_win	*get_win(t_win *win);
t_img	*get_img(t_img *img);

#endif
