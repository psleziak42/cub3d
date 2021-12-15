/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:51:21 by psleziak          #+#    #+#             */
/*   Updated: 2021/12/15 21:31:50 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/cub3d.h"

static int	ft_count_longest_line(t_map *map)
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

static void	ft_resize_map_to_square(int l, t_map *map)
{
	int	x;
	int	y;

	y = -1;
	while (map->map[++y])
	{
		x = -1;
		while (map->map[y][++x])
			;
		if (x < l)
		{
			map->map[y] = realloc(map->map[y], l + 1);
			while (x < l)
			{
				if (x == l)
					map->map[y][x] = '\0';
				if (x == l - 1)
					map->map[y][x] = '\n';
				map->map[y][x] = ' ';
				x++;
			}
			map->map[y][x] = '\0';
		}
	}
}

static int	ft_place_a_player(t_trigo *trigo, t_map *map, int x, int y)
{
	static int	player;

	trigo->px_x = x * trigo->unit_x_size;
	trigo->px_y = y * trigo->unit_y_size;
	if (map->map[y][x] == 'N')
		trigo->angle = PI / 2;
	else if (map->map[y][x] == 'S')
		trigo->angle = 3 * PI / 2;
	else if (map->map[y][x] == 'E')
		trigo->angle = 0;
	else if (map->map[y][x] == 'W')
		trigo->angle = PI;
	player++;
	if (player != 1)
		return (0);
	return (1);
}

static int	ft_check_de_map(t_map *map, t_trigo *trigo)
{
	int	x;
	int	y;

	y = -1;
	while (map->map[++y])
	{
		x = -1;
		while (map->map[y][++x])
		{
			if ((y == 0 || y == map->last_line)
				&& !ft_strchr("1 \n", map->map[y][x]))
				return (0);
			else if (ft_strchr(" NSEW", map->map[y][x]))
			{
				if (map->map[y][x + 1] == 32 || map->map[y][x - 1] == 32
					|| map->map[y + 1][x] == 32 || map->map[y - 1][x] == 32)
					return (0);
				if (ft_strchr("NSEW", map->map[y][x]))
					if (!ft_place_a_player(trigo, map, x, y))
						return (0);
			}
		}
	}
	return (1);
}

int	ft_map_parse(char *argc, t_map *map, t_trigo *trigo)
{
	map->fd = open(argc, O_RDONLY);
	if (!ft_get_next_line(map))
	{
		ft_error_handler("Error:\n", "File/Map misconfiguraton\n", 2);
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
