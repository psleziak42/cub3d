/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psleziak <psleziak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 16:28:32 by psleziak          #+#    #+#             */
/*   Updated: 2021/12/15 01:17:49 by psleziak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/cub3d.h"

int	ft_check_de_map(t_map *map, t_trigo *trigo)
{
	int	x;
	int	y;
	int	player;

	y = -1;
	player = 0;
	while (map->map[++y])
	{
		x = -1;
		while (map->map[y][++x])
		{
			if (y == 0 || y == map->last_line)
			{
				if (map->map[y][x] != '1' && map->map[y][x] != ' ' && map->map[y][x] != '\n')
					return (0);
			}
			else if (map->map[y][x] == 48 || map->map[y][x] == 'N' || map->map[y][x] == 'S' || map->map[y][x] == 'E' || map->map[y][x] == 'W') // "any char of ths string NSEW"?
			{
				if (map->map[y][x + 1] == 32 || map->map[y][x - 1] == 32 || map->map[y + 1][x] == 32 || map->map[y - 1][x] == 32)
					return (0);
				if (map->map[y][x] == 'N' || map->map[y][x] == 'S' || map->map[y][x] == 'E' || map->map[y][x] == 'W')
				{
					trigo->px_x = x * trigo->unit_x_size;
					trigo->px_y = y * trigo->unit_y_size;
					if (map->map[y][x] == 'N')
						trigo->angle = P2;
					else if (map->map[y][x] == 'S')
						trigo->angle = P3;
					else if (map->map[y][x] == 'E')
						trigo->angle = 0;
					else if (map->map[y][x] == 'W')
						trigo->angle = PI;
					player++;
				}	
			}
		}
	}
	if (player != 1)
		return (0);
	return (1);
}

void	ft_resize_map_to_square(int l, t_map *map)
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

static int	ft_process_map(char *line, int counter, t_map *map)
{
	int	i;

	if (counter == 0)
		map->map = malloc(sizeof(char *) * (counter + 2));
	else
		map->map = realloc(map->map, sizeof(char *) * (counter + 2));
	map->map[counter] = ft_strdup(line);
	i = 0;
	while (line[i])
	{
		if (!is_valid_char(line[i++],
				(char[9]){'0', '1', 'N', 'E', 'S', 'W', ' ', '\n', '\0'}))
			return (0);
	}
	map->map[counter] = ft_strdup(line);
	return (1);
}

static int	ft_process_line(t_map *map)
{
	if (map->args[0][0] == 'R' && map->win_hei == 0 && map->win_wid == 0)
	{
		map->win_wid = ft_atoi(map->args[1]);
		map->win_hei = ft_atoi(map->args[2]);
		if (map->win_hei <= 0 || map->win_wid <= 0)
			return (0);
	}
	else if (!(ft_strncmp(map->args[0], "NO", 2)) && !map->nsew[N])
		map->nsew[N] = map->args[1];
	else if (!(ft_strncmp(map->args[0], "SO", 2)) && !map->nsew[S])
		map->nsew[S] = map->args[1];
	else if (!(ft_strncmp(map->args[0], "WE", 2)) && !map->nsew[W])
		map->nsew[E] = map->args[1];
	else if (!(ft_strncmp(map->args[0], "EA", 2)) && !map->nsew[E])
		map->nsew[W] = map->args[1];
	else if (map->args[0][0] == 'F')
	{
		map->rgb = ft_split(map->args[1], ',');
		map->c_f[F][0] = ft_atoi(map->rgb[0]);
		map->c_f[F][1] = ft_atoi(map->rgb[1]);
		map->c_f[F][2] = ft_atoi(map->rgb[2]);
		if (is_wrong_color(map->c_f[F][0], map->c_f[F][1], map->c_f[F][2]))
			return (0);
	}	
	else if (map->args[0][0] == 'C')
	{
		map->rgb = ft_split(map->args[1], ',');
		map->c_f[C][0] = ft_atoi(map->rgb[0]);
		map->c_f[C][1] = ft_atoi(map->rgb[1]);
		map->c_f[C][2] = ft_atoi(map->rgb[2]);
		if (is_wrong_color(map->c_f[C][0], map->c_f[C][1], map->c_f[C][2]))
			return (0);
	}
	return (1);
}

int	parse_lines(char *line, int i, int *counter, t_map *map)
{
	static int		count_args;
	static bool		next_is_map;

	if (i != 0 && (line[0] >= 65 && line[0] <= 90) && next_is_map == FALSE)
	{
		map->args = ft_split(line, 32);
		if (count_args == 7)
			next_is_map = TRUE;
		if (!ft_process_line(map))
			return (0);
		count_args++;
	}
	else if (line[0] == '\0')
		;
	else if ((line[0] != 49 && line[0] != 32)
		|| line[ft_strlen(line) - 1] != 49)
		return (0);
	else
	{
		if(!ft_process_map(line, ++(*counter), map))
		{
			map->map[(*counter)] = NULL;
			return (0);
		}
	}
	return (1);
}

int	ft_get_next_line(t_map *map)
{
	char	*line;
	char	buf;
	int		i;
	int		counter;

	i = 0;
	counter = -1;
	line = malloc(8192);
	if (map->fd < 0 || !line)
		return (0);
	while (read(map->fd, &buf, 1))
	{
		if (buf == '\n')
		{
			line[i] = '\0';
			if (!parse_lines(line, i, &counter, map))
				return (0);
			i = 0;
		}
		else
			line[i++] = buf;
	}
	map->last_line = counter;
	map->map[++counter] = NULL;
	free(line);
	line = NULL;
	return (1);
}

// if (i != 0 && (line[0] >= 65 && line[0] <= 90) && next_is_map == FALSE)
// {
// 	map->args = ft_split(line, 32);
// 	if (map->args[0][0] == 'C')
// 		next_is_map = TRUE;
// 	if (!ft_process_line())
// 		return (0);
// 	i = 0;
// 	continue ;
// }
// else if (line[0] == '\n')
// {
// 	i = 0;
// 	continue ;
// }
// else if ((line[0] != 49 && line[0] != 32) || line[ft_strlen(line) - 2] != 49)
// 	return (0);
// else 
// {
// 	if(!ft_process_map(line, ++counter))
// 		break ;
// 	i = 0;

// 	continue ;
// }
