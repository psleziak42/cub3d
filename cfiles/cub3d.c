/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 16:24:13 by psleziak          #+#    #+#             */
/*   Updated: 2021/12/14 19:08:45 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/cub3d.h"

int		ft_count_longest_line(void)
{
	int	x;
	int	y;
	int	l;

	x = -1;
	y = -1;
	l = 0;
	while (get_map(0)->map[++y])
	{
		while(get_map(0)->map[y][++x])
			;
		if (x > l)
			l = x;
		x = -1;
	}
	return (l);
}

// void	ft_putstr_fd(int fd, char *str)
// {
// 	int i;

// 	i = -1;
// 	while (str[++i])
// 		write(fd, &str[i], 1);
// }

void	ft_error_handler(char *error, char *msg, int fd)
{
	ft_putstr_fd(error, fd);
	ft_putstr_fd(msg, fd);
}

int	ft_map_parse(char *argc)
{
	int	fd;
	fd = open(argc, O_RDONLY);
	if (!ft_get_next_line())
	{
		ft_error_handler("Error:\n", "File misconfiguraton\n", 2);
		return (0);
	}
	get_map(NULL)->longest_line = ft_count_longest_line();
	ft_resize_map_to_square(get_map(0)->longest_line);
	if (!ft_check_de_map())
	{
		ft_error_handler("Error:\n", "Map misconfiguraton\n", 2);
		return (0);
	}
	//get_trigo(NULL)->cub_size = TEXT; /* check if it is necesary!! */
	get_trigo(0)->unit_x_size = get_map(0)->win_wid/(get_map(0)->longest_line - 1);
	get_trigo(0)->unit_y_size =  get_map(0)->win_hei/(get_map(0)->last_line + 1);
	//ft_print_map();
	return (1);
}

void	ft_set_em_to_zero_and_create_singletones
	(t_map *map, t_win *win, t_img img[][6], t_trigo *trigo)
{
	ft_memset(map, 0, sizeof(map));
	ft_memset(win, 0, sizeof(win));
	ft_memset(*img, 0, sizeof(*img));
	ft_memset(trigo, 0, sizeof(trigo));
	get_map(map);
	get_win(win);
	get_img(*img);
	get_trigo(trigo);
}

void	ft_fill_walls_and_background_structs()
{
	get_img(0)[WL].img_inst = 
		mlx_new_image(get_win(0)->mlx_p, get_map(0)->win_wid, 
			get_map(0)->win_hei);
	get_img(0)[WL].img_address = 
		mlx_get_data_addr(get_img(0)[WL].img_inst, &get_img(0)[WL].bpp, 
			&get_img(0)[WL].line_len, &get_img(0)[WL].endian);
	get_img(0)[BG].img_inst = 
		mlx_new_image(get_win(0)->mlx_p, get_map(0)->win_wid, 
			get_map(0)->win_hei);
	get_img(0)[BG].img_address = 
		mlx_get_data_addr(get_img(0)[BG].img_inst, &get_img(0)[BG].bpp, 
			&get_img(0)[BG].line_len, &get_img(0)[BG].endian);
}

int	ft_close_window()
{
	mlx_destroy_window(get_win(0)->mlx_p, get_win(0)->win_p);
	exit(1);
}

int	main(int argc, char **argv)
{
	t_map	map;
	t_win	win;
	t_img	img[6];
	t_trigo	trigo;

	if (argc != 2 && ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 5))
	{
		ft_error_handler("Error\n", "Incorrect map name. Must be *.cub\n", 2);
		return (-1);
	}
	ft_set_em_to_zero_and_create_singletones(&map, &win, &img, &trigo);
	if (!ft_map_parse(argv[1]))
	{
		//ft_free_memory();
		return(-1);
	}
	get_win(0)->mlx_p = mlx_init();
	get_win(0)->win_p = mlx_new_window(get_win(0)->mlx_p, get_map(0)->win_wid, get_map(0)->win_hei, "dujuivnDUBSTEPbro?");
	ft_fill_walls_and_background_structs();
	//init_loop();
	mlx_hook(get_win(0)->win_p, 2, 1L << 0, key_press, 0);
	mlx_hook(get_win(0)->win_p, 17, (1L << 16), ft_close_window, 0);
	//print_one_ray();
	mlx_loop(get_win(0)->mlx_p);
	return (0);
}
