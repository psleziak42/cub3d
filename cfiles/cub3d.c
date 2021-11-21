/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psleziak <psleziak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 16:24:13 by psleziak          #+#    #+#             */
/*   Updated: 2021/11/21 00:20:01 by psleziak         ###   ########.fr       */
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
	g_master.map.longest_line = ft_count_longest_line();
	g_master.trigo.unit_x_size = g_master.map.window_width/(g_master.map.longest_line - 1);
	g_master.trigo.unit_y_size =  g_master.map.window_height/(g_master.map.last_line + 1);
	ft_resize_map_to_square(g_master.map.longest_line);
	if (!ft_check_de_map())
		return (0);
	ft_print_map();
	return (1);
}

int	main(int argc, char **argv)
{
	//	master;
	
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
	mlx_hook(g_master.window.win_p, 2, 1L << 0, key_press, NULL);
	//mlx_hook(g_master.window.win_p, 2, 1L << 1, key_release, &g_master);
	ft_printmap_to_window(&g_master);
	print_one_ray();
	//master.img.img_file = "cfiles/textures/player.xpm";
	//master.img.img_instance = mlx_xpm_file_to_image(master.window.mlx_p, master.img.img_file, &master.img.img_width, &master.img.img_heigth);
	//mlx_put_image_to_window(master.window.mlx_p, master.window.win_p, master.img.img_instance, 100, 100);
	//printf("w_heigh %d, w_width %d\n", map.window_height, map.window_width);
	//printf("N: %s\n, S %s\n, E %s\n, W %s\n", map.N, map.S, map.E, map.W);
	//printf("FR %d, FG %d, FB %d, CR %d, CG %d, CB %d\n", map.FR, map.FG, map.FB, map.CR, map.CG, map.CB);
	mlx_loop(g_master.window.mlx_p);
	return (0);
}
