/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psleziak <psleziak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 16:24:13 by psleziak          #+#    #+#             */
/*   Updated: 2021/12/03 22:53:02 by psleziak         ###   ########.fr       */
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
	while (g_master.map.map[++y])
	{
		while(g_master.map.map[y][++x])
			;
		if (x > l)
			l = x;
		x = -1;
	}
	return (l);
}

int	ft_map_parse(char *argc)
{
	g_master.map.fd = open(argc, O_RDONLY);
	if (!ft_get_next_line())
		return (0);
	g_master.trigo.cub_size = 32;
	g_master.map.longest_line = ft_count_longest_line();
	g_master.trigo.unit_x_size = g_master.map.window_width/(g_master.map.longest_line - 1);
	g_master.trigo.unit_y_size =  g_master.map.window_height/(g_master.map.last_line + 1);
	ft_resize_map_to_square(g_master.map.longest_line);
	if (!ft_check_de_map())
		return (0);
	//ft_print_map();
	return (1);
}

int	main(int argc, char **argv)
{
	ft_memset(&g_master, 0, sizeof(g_master));
	if (argc != 2)
		return (-1);
	if (!ft_map_parse(argv[1]))
	{
		printf("Error\n");
		ft_free_memory();
		return(-1);
	}
	g_master.window.mlx_p = mlx_init();
	g_master.window.win_p = mlx_new_window(g_master.window.mlx_p, g_master.map.window_width, g_master.map.window_height, "dujuivnDUBSTEPbro?");
	g_master.walls.img_instance = mlx_new_image(g_master.window.mlx_p, g_master.map.window_width, g_master.map.window_height);
	g_master.walls.img_address = mlx_get_data_addr(g_master.walls.img_instance, &g_master.walls.bits_per_pixel, &g_master.walls.line_length, &g_master.walls.endian);
	g_master.bg.img_instance = mlx_new_image(g_master.window.mlx_p, g_master.map.window_width, g_master.map.window_height);
	g_master.bg.img_address = mlx_get_data_addr(g_master.bg.img_instance, &g_master.bg.bits_per_pixel, &g_master.bg.line_length, &g_master.bg.endian);
	ft_printmap_to_window(); //THIS WILL BE FOR MINIMAP EVENTUALLY !!
	mlx_hook(g_master.window.win_p, 2, 1L << 0, key_press, NULL);
	//print_one_ray();
	mlx_loop(g_master.window.mlx_p);
	return (0);
}
