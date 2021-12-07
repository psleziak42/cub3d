/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psleziak <psleziak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 16:24:13 by psleziak          #+#    #+#             */
/*   Updated: 2021/12/07 22:52:24 by psleziak         ###   ########.fr       */
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
	g_master.trigo.cub_size = TEXT;
	g_master.map.longest_line = ft_count_longest_line();
	g_master.trigo.unit_x_size = g_master.map.window_width/(g_master.map.longest_line - 1);
	g_master.trigo.unit_y_size =  g_master.map.window_height/(g_master.map.last_line + 1);
	ft_resize_map_to_square(g_master.map.longest_line);
	if (!ft_check_de_map())
		return (0);
	//ft_print_map();
	return (1);
}

void	ft_load_textures(void)
{
	g_master.textures[N].img_instance = mlx_xpm_file_to_image(g_master.window.mlx_p, g_master.map.NSEW[0], &g_master.textures[0].img_width, &g_master.textures[0].img_heigth);
	g_master.textures[S].img_instance = mlx_xpm_file_to_image(g_master.window.mlx_p, g_master.map.NSEW[1], &g_master.textures[1].img_width, &g_master.textures[1].img_heigth);
	g_master.textures[E].img_instance = mlx_xpm_file_to_image(g_master.window.mlx_p, g_master.map.NSEW[2], &g_master.textures[2].img_width, &g_master.textures[2].img_heigth);
	g_master.textures[W].img_instance = mlx_xpm_file_to_image(g_master.window.mlx_p, g_master.map.NSEW[3], &g_master.textures[3].img_width, &g_master.textures[3].img_heigth);
	g_master.textures[N].img_address = mlx_get_data_addr(g_master.textures[N].img_instance, &g_master.textures[N].bits_per_pixel, &g_master.textures[N].line_length, &g_master.textures[N].endian);
	g_master.textures[S].img_address = mlx_get_data_addr(g_master.textures[S].img_instance, &g_master.textures[S].bits_per_pixel, &g_master.textures[S].line_length, &g_master.textures[S].endian);
	g_master.textures[E].img_address = mlx_get_data_addr(g_master.textures[E].img_instance, &g_master.textures[E].bits_per_pixel, &g_master.textures[E].line_length, &g_master.textures[E].endian);
	g_master.textures[W].img_address = mlx_get_data_addr(g_master.textures[W].img_instance, &g_master.textures[W].bits_per_pixel, &g_master.textures[W].line_length, &g_master.textures[W].endian);
	// printf("sizeof(line_length): %x\n", g_master.textures[N].img_address[1]);
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
	ft_load_textures();
	g_master.walls.img_instance = mlx_new_image(g_master.window.mlx_p, g_master.map.window_width, g_master.map.window_height);
	g_master.walls.img_address = mlx_get_data_addr(g_master.walls.img_instance, &g_master.walls.bits_per_pixel, &g_master.walls.line_length, &g_master.walls.endian);
	g_master.bg.img_instance = mlx_new_image(g_master.window.mlx_p, g_master.map.window_width, g_master.map.window_height);
	g_master.bg.img_address = mlx_get_data_addr(g_master.bg.img_instance, &g_master.bg.bits_per_pixel, &g_master.bg.line_length, &g_master.bg.endian);
	ft_update_bg();
	mlx_hook(g_master.window.win_p, 2, 1L << 0, key_press, NULL);
	//print_one_ray();
	mlx_loop(g_master.window.mlx_p);
	return (0);
}
