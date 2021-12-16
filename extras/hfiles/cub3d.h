/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psleziak <psleziak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 14:52:05 by psleziak          #+#    #+#             */
/*   Updated: 2021/12/15 23:54:58 by psleziak         ###   ########.fr       */
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
// # define P2		PI/2
// # define P3		3 * PI / 2
//# define F0V	PI / 3 / DEGREE
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

typedef struct s_img
{
	void	*img_inst;
	char	*img_address;
	int		bpp;
	int		line_len;
	int		endian;
	int		img_wid;
	int		img_hei;	
}				t_img;

typedef struct s_trigonometry
{
	float	counter;
	float	ry;
	float	rx;
	float	xo;
	float	yo;
	float	px_y;
	float	px_x;
	float	angle;
	float	unit_y_size;
	float	unit_x_size;
	float	line_h_3d;
	float	line_o_3d;
	bool	key_a;
	bool	key_w;
	bool	key_s;
	bool	key_d;
}				t_trigo;

typedef union u_color
{
	int	color;
	struct
	{
		uint8_t	b;
		uint8_t	g;
		uint8_t	r;
		uint8_t	t;
	};
}				t_color;

/****CUB3D_UTILS****/
int		ft_close_window(void);
void	ft_error_handler(char *error, char *msg, int fd);
void	ft_fill_walls_and_background_struct(t_img *img, t_map *map, t_win *win);
void	ft_create_singletones(t_map *map, t_win *win, t_img *img);
void	ft_set_em_to_zero(t_map *map, t_win *win, t_img *img, t_trigo *trigo);

/****MAP****/
int		ft_get_next_line(t_map *map);
int		ft_map_parse(char *argc, t_map *map, t_trigo *trigo);

/****RGB****/
int		ft_floor(t_map *map);
int		ft_ceiling(t_map *map);
bool	is_wrong_color(int r, int g, int b);
bool	is_valid_char(char c, char *compound);
int		ft_check_rgb_values(t_map *map);
int		create_trgb(int b, int g, int r, int t);
/****CREATE_MAP_UTILS****/
void	ft_north_wall(t_trigo *trigo, int x, int y);
void	ft_east_wall(t_trigo *trigo, int x, int y);
void	ft_south_wall(t_trigo *trigo, int x, int y);
void	ft_west_wall(t_trigo *trigo, int x, int y);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

/****WINDOW****/
void	ft_printmap_to_window(void);

/****KEY****/
int		key_release(int key);
int		ft_update_position(int key, t_trigo *trigo);

/****RAYCASTING****/
void	ft_raycasting(t_trigo *trigo);

/*****RAYCASTING_UTILS****/
float	ft_distance(float ry, float py, float rx, float px);
float	ft_360(float ra);

/****PRINTING****/
void	ft_update_walls(t_trigo *trigo, int x, int dir, float ra);
void	ft_create_bg(void);

/****FREE and CLEAN****/
void	ft_error_handler(char *error, char *msg, int fd);
void	ft_free_memory(void);
void	free_rgb(char **rgb);
void	ft_destroy_imgs(void);
int		ft_free_memory_without_singleton(t_map *map);
void	malloc_guard(void **alloc_var, int size, int data_type_size);
int		check_files(char **nsew);

/****SINGLETONES****/
t_map	*get_map(t_map *map);
t_win	*get_win(t_win *win);
t_img	*get_img(t_img *img);

#endif
