/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psleziak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 16:24:13 by psleziak          #+#    #+#             */
/*   Updated: 2021/10/23 23:55:14 by psleziak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/cub3d.h"

int	ft_map_parse(t_map *map, char *argc)
{
	map->fd = open(argc, O_RDONLY);
	if (!ft_get_next_line(map))
		return (0);
	map->longest_line = ft_count_longest_line(map);
	ft_resize_map_to_square(map, map->longest_line);
	if (!ft_check_de_map(map))
		return (0);
	ft_print_map(map);
	return (1);
}

int	main(int argc, char **argv)
{
	t_master	master;
	
	ft_memset(&master, 0, sizeof(master));
	if (argc != 2)
		return (-1);
	if (!ft_map_parse(&master.map, argv[1]))
	{
		printf("Error\n");
		ft_free_memory(&master.map);
		return(-1);
	}
	master.window.mlx_p = mlx_init();
	master.window.win_p = mlx_new_window(master.window.mlx_p, master.map.window_width, master.map.window_height, "dujuivnDUBSTEPbro?");
	mlx_hook(master.window.win_p, 2, 1L << 0, key_press, &master);
	//mlx_hook(master.window.win_p, 2, 1L << 1, key_release, &master);
	ft_map_create(&master);
	//master.img.img_file = "cfiles/textures/player.xpm";
	//master.img.img_instance = mlx_xpm_file_to_image(master.window.mlx_p, master.img.img_file, &master.img.img_width, &master.img.img_heigth);
	//mlx_put_image_to_window(master.window.mlx_p, master.window.win_p, master.img.img_instance, 100, 100);
	//printf("w_heigh %d, w_width %d\n", map.window_height, map.window_width);
	//printf("N: %s\n, S %s\n, E %s\n, W %s\n", map.N, map.S, map.E, map.W);
	//printf("FR %d, FG %d, FB %d, CR %d, CG %d, CB %d\n", map.FR, map.FG, map.FB, map.CR, map.CG, map.CB);
	mlx_loop(master.window.mlx_p);
	return (0);
}
