/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psleziak <psleziak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 16:24:13 by psleziak          #+#    #+#             */
/*   Updated: 2021/12/15 01:18:10 by psleziak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/cub3d.h"

int	ft_count_longest_line(t_map *map)
{
	int	x;
	int	y;
	int	l;

	x = -1;
	y = -1;
	l = 0;
	while (map->map[++y])
	{
		while (map->map[y][++x])
			;
		if (x > l)
			l = x;
		x = -1;
	}
	return (l);
}

void	ft_error_handler(char *error, char *msg, int fd)
{
	ft_putstr_fd(error, fd);
	ft_putstr_fd(msg, fd);
}

int	ft_map_parse(char *argc, t_map *map, t_trigo *trigo)
{
	map->fd = open(argc, O_RDONLY);
	if (!ft_get_next_line(map))
	{
		ft_error_handler("Error:\n", "File misconfiguraton\n", 2);
		return (0);
	}
	map->longest_line = ft_count_longest_line(map);
	ft_resize_map_to_square(map->longest_line, map);
	trigo->unit_x_size = map->win_wid / (map->longest_line - 1);
	trigo->unit_y_size = map->win_hei / (map->last_line + 1);
	if (!ft_check_de_map(map, trigo))
	{
		ft_error_handler("Error:\n", "Map misconfiguraton\n", 2);
		return (0);
	}
	return (1);
}

void	ft_create_singletones(t_map *map, t_win *win, t_img *img)
{
	get_map(map);
	get_win(win);
	get_img(img);
}

// void	ft_set_em_to_zero(t_map *map, t_win *win, t_img **img, t_trigo *trigo)
// {
// 	ft_memset(map, 0, sizeof(t_map));
// 	ft_memset(win, 0, sizeof(t_win));
// 	ft_memset(img, 0, sizeof(t_img));
// 	ft_memset(trigo, 0, sizeof(t_trigo));
// }

void	ft_fill_walls_and_background_struct(t_img *img, t_map *map, t_win *win)
{
	img[WL].img_inst = mlx_new_image(win->mlx_p, map->win_wid, map->win_hei);
	img[WL].img_address = mlx_get_data_addr(img[WL].img_inst, &img[WL].bpp,
			&img[WL].line_len, &img[WL].endian);
	img[BG].img_inst = mlx_new_image(win->mlx_p, map->win_wid, map->win_hei);
	img[BG].img_address = mlx_get_data_addr(img[BG].img_inst, &img[BG].bpp,
			&img[BG].line_len, &img[BG].endian);
}

int	ft_close_window(void)
{
	mlx_destroy_window(get_win(0)->mlx_p, get_win(0)->win_p);
	exit(1);
}

int	ft_render_image(t_trigo *trigo)
{
	ft_raycasting(trigo);
	mlx_put_image_to_window(get_win(0)->mlx_p, get_win(0)->win_p,
		get_img(0)[BG].img_inst, 0, 0);
	mlx_put_image_to_window(get_win(0)->mlx_p, get_win(0)->win_p,
		get_img(0)[WL].img_inst, 0, 0);
	return (0);
}

void	ft_init_loop(t_trigo *trigo)
{
	mlx_loop_hook(get_win(0)->mlx_p, ft_render_image, trigo);
	mlx_hook(get_win(0)->win_p, 2, 1L << 0, ft_update_position, trigo);
	mlx_hook(get_win(0)->win_p, 17, (1L << 16), ft_close_window, 0);
	mlx_loop(get_win(0)->mlx_p);
}

int	main(int argc, char **argv)
{
	t_map	map = {0};
	t_win	win = {0};
	t_img	*img = {0};
	t_trigo	trigo = {0};

	if (argc != 2 && ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 5))
	{
		ft_error_handler("Error\n", "Incorrect map name. Must be *.cub\n", 2);
		return (-1);
	}
	img = ft_calloc(sizeof(t_img), 2 + 1);
	//ft_set_em_to_zero(&map, &win, &img, &trigo);
	if (!ft_map_parse(argv[1], &map, &trigo))
	{
		//ft_free_memory();
		return (-1);
	}
	win.mlx_p = mlx_init();
	win.win_p = mlx_new_window(win.mlx_p, map.win_wid, map.win_hei, "cub3d");
	ft_fill_walls_and_background_struct(img, &map, &win);
	ft_create_singletones(&map, &win, img);
	ft_update_bg();
	ft_init_loop(&trigo);
	return (0);
}
