/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psleziak <psleziak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 16:28:32 by psleziak          #+#    #+#             */
/*   Updated: 2021/11/08 23:08:58 by psleziak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../extras/hfiles/cub3d.h"

/* TO DO:
 *-> 
 *
 *
 *
 *
 *
*/

void	ft_print_map(t_map *map)
{
	int y;

	y = -1;
	while (map->map[++y])
		printf("%s", map->map[y]);
}

int		ft_check_de_map(t_master *master) 
{
	int	x;
	int y;
	int	player;

	y = -1;
	player = 0;
	while (master->map.map[++y])
	{
		x = -1;
		while (master->map.map[y][++x])
		{
			if (y == 0 || y == master->map.last_line)
			{
				if (master->map.map[y][x] != '1' && master->map.map[y][x] != ' ' && master->map.map[y][x] != '\n')
					return (0);
			}
			else if (master->map.map[y][x] == 48 || master->map.map[y][x] == 'N' || master->map.map[y][x] == 'S' || master->map.map[y][x] == 'E' || master->map.map[y][x] == 'W') 
			{
				if (master->map.map[y][x+1] == 32 || master->map.map[y][x-1] == 32 || master->map.map[y+1][x] == 32 || master->map.map[y-1][x] == 32) 
					return (0);
				if (master->map.map[y][x] == 'N' || master->map.map[y][x] == 'S' || master->map.map[y][x] == 'E' || master->map.map[y][x] == 'W')
				{
					master->trigo.map2d_x = x;
					master->trigo.map2d_y = y;
					master->trigo.pixel_x = x * master->trigo.unit_x_size;
					master->trigo.pixel_y = y * master->trigo.unit_y_size;
					if (master->map.map[y][x] == 'N')
						master->trigo.current_angle = PI/2;
					else if (master->map.map[y][x] == 'S')
						master->trigo.current_angle = 3 * PI / 2;
					else if (master->map.map[y][x] == 'E')
						master->trigo.current_angle = 0;
					else if (master->map.map[y][x] == 'W')
						master->trigo.current_angle = PI; 
					player++;
				}	
			}
		}
	}
	if (player != 1)
		return (0);
	return (1);
}

void	ft_resize_map_to_square(t_map *map, int l)
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
			map->map[y] = realloc(map->map[y], sizeof(char) * (l + 1));
			while (x < l)
			{
				if (x == l)
					map->map[y][x] = '\0';
				if (x == l - 1)
					map->map[y][x] = '\n';
				map->map[y][x - 1] = ' '; // checked with 'x' it works, now we turn it back to spaces;
				x++;
			}
			map->map[y][x] = '\0';
		}
	}
}

int		ft_process_map(t_map *map, char *line, int counter) 
{
	int		size;
	
	if (counter == 0)
		map->map = malloc(sizeof(char *) * (counter + 2));
	else
		map->map = realloc(map->map, sizeof(char *) * (counter + 2));
	size = ft_strlen(line);
	map->map[counter] = ft_strdup(line);
	return (1);
}

int		ft_process_line(t_map *map)
{
	if (map->args[0][0] == 'R') // if wrong value, return atoi -1 i finish
	{
		map->window_width = ft_atoi(map->args[1]);  // less than 0 should throw error
		map->window_height = ft_atoi(map->args[2]); // less than 0 should throw error
		if (map->window_height <= 0 || map->window_width <= 0)
			return (0); 
	}
	else if (!(ft_strncmp(map->args[0], "NO", 2)))
		map->N = map->args[1];
	else if (!(ft_strncmp(map->args[0], "SO", 2)))
		map->S = map->args[1];
	else if (!(ft_strncmp(map->args[0], "WE", 2)))
		map->E = map->args[1];
	else if (!(ft_strncmp(map->args[0], "EA", 2)))
		map->W = map->args[1];
	else if (map->args[0][0] == 'F') // < 0 && > 255 error
	{
		map->RGB = ft_split(map->args[1], ',');
		map->FR = ft_atoi(map->RGB[0]); 
		map->FG = ft_atoi(map->RGB[1]);
		map->FB = ft_atoi(map->RGB[2]);
		/*if (wrong_color_range(map->FR, map->FG, map->FB))
			return (0);*/
	}	
	else if (map->args[0][0] == 'C') 
	{
		map->RGB = ft_split(map->args[1], ',');
		map->CR = ft_atoi(map->RGB[0]);
		map->CG = ft_atoi(map->RGB[1]);
		map->CB = ft_atoi(map->RGB[2]);
		/*if (wrong_color_range(map->FR, map->FG, map->FB))
			return (0);*/
	}
	return (1);
}

int		ft_get_next_line(t_map *map)
{
	char	*line;
	char	buf;
	int		i;
	int		counter;
	bool	next_is_map;

	i = 0;
	counter = -1;
	next_is_map = FALSE;
	line = malloc(8192);
	if (map->fd < 0 || !line)
		return (0);
	while (read(map->fd, &buf, 1))
	{
		if (buf == '\n')
		{
			line[i] = buf; 
			line[++i] = '\0';
			if (i != 0 && (line[0] >= 65 && line[0] <= 90) && next_is_map == FALSE) // to jest kod do informacji o teksturach i rozmiarze
			{
				map->args = ft_split(line, 32);
				if (map->args[0][0] == 'C')
					next_is_map = TRUE;
				if (!ft_process_line(map))
					return (0);
				i = 0;
				continue ;
			}
			else if (line[0] == '\n')
			{
				i = 0;
				continue ;
			}
			else if ((line[0] != 49 && line[0] != 32) || line[ft_strlen(line) - 2] != 49)
				return (0);
			else 
			{
				if(!ft_process_map(map, line, ++counter))
					break ;
				i = 0;
				continue ;
			}
		}
		line[i++] = buf;
	}
	map->last_line = counter;
	map->map[++counter] = NULL;
	return (1);
}
