/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psleziak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 16:24:13 by psleziak          #+#    #+#             */
/*   Updated: 2021/10/19 23:55:17 by psleziak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/cub3d.h"

int	ft_map_parse(t_map *map, char *argc)
{
	int l;

	map->fd = open(argc, O_RDONLY);
	if (!ft_get_next_line(map))
		return (0);
	l = ft_count_longest_line(map);
	ft_resize_map_to_square(map, l);
	if (!ft_check_de_map(map))
		return (0);
	ft_print_map(map);
	return (1);
}

int	main(int argc, char **argv)
{
	t_map	map;
	(void)argc;
	if (!ft_map_parse(&map, argv[1]))
	{
		printf("Error\n");
		ft_free_memory(map);
		return(-1);
	}		
	printf("w_heigh %d, w_width %d\n", map.window_height, map.window_width);
	printf("N: %s\n, S %s\n, E %s\n, W %s\n", map.N, map.S, map.E, map.W);
	printf("FR %d, FG %d, FB %d, CR %d, CG %d, CB %d\n", map.FR, map.FG, map.FB, map.CR, map.CG, map.CB);
	return (0);
}
