/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psleziak <psleziak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 14:52:05 by bcosters          #+#    #+#             */
/*   Updated: 2021/12/07 22:55:08 by psleziak         ###   ########.fr       */
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
# define F0V	PI / 3 / degree
# define degree	0.01745329251
# define ESC 	53
# define X		17
//# define F		3
# define k_A	0
# define k_S	1
# define k_W	13
# define k_D	2
# define TEXT	64
# define SPEED	5
# define ROT	3
# define N		0
# define S		1
# define E		2
# define W		3
# define F		1
# define C		0

typedef	struct s_map
{
	char	**map;
	char	**args;
	char	**RGB;
	int		fd;
	int		window_width;
	int		window_height;
	int		c_f[2][3];
	int		FR;
	int		FG;
	int		FB;
	int		CR;
	int		CG;
	int		CB;
	char	*NSEW[4];
	int		last_line;
	int		longest_line;
}				t_map;

typedef	struct	s_win
{
	void	*mlx_p;
	void	*win_p;
}
				t_window;

typedef struct	s_small_map
{
	char *img_file;
	void *img_instance;
	int	 img_width;
	int  img_heigth;

}				t_s_map;

typedef struct	s_img // to daje nam dane obrazka, line_length to jest dlugosc obrazka;
{
	void	*img_instance;
	char	*img_address;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int	 	img_width;
	int  	img_heigth;
}				t_img;

typedef struct s_trigonometry
{
	float	ryh;
	float	rxh;
	float	ryv;
	float	rxv;

	float	cub_size;
	float	pixel_y;
	float	pixel_x;
	float	current_angle;
	float	unit_y_size;
	float	unit_x_size;
	float	lineH_3d;
	float	lineO_3d;
	float	x_width;
}				t_trigo;

typedef struct s_master
{
	t_map		map;
	t_window	window;
	t_img		walls; // call it walls!
	t_img		bg; // init it and doesnt have to be updated anymore in the loop!
	t_img		textures[4];
	t_trigo		trigo;
	t_s_map		t_s_map;
} 				t_master;

t_master	g_master;

/****MAP****/
int		ft_get_next_line(void);
int		ft_count_longest_line(void);
void	ft_resize_map_to_square(int l);
int		ft_check_de_map(void);
void	ft_print_map(void);

/****WINDOW****/
void	ft_printmap_to_window(void);
void	ft_put_pixel(t_master *master, int x, int y);

/****KEY****/
int		key_press(int key);
int		key_release(int key, t_master *master);

/****RAYCASTING****/
void	ft_raycasting(void);

/****PRINTING****/
void    ft_3d_print_addr(int x, int dir, float ra);
void	ft_update_bg(void);

/****FREE and CLEAN****/
void	ft_free_memory(void);

#endif
