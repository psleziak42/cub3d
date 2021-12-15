/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_value_assignment.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psleziak <psleziak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 16:28:32 by psleziak          #+#    #+#             */
/*   Updated: 2021/12/15 18:55:08 by psleziak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/cub3d.h"

bool	is_valid_char(char c, char *compound)
{
	int	i;

	i = -1;
	while (compound[++i])
	{
		if (compound[i] == c)
			return (true);
	}	
	return (false);
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
				(char [9]){'0', '1', 'N', 'E', 'S', 'W', ' ', '\n', '\0' }))
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
		ft_floor(map);
	else if (map->args[0][0] == 'C')
		ft_ceiling(map);
	if (!ft_check_rgb_values(map))
		return (0);
	return (1);
}

/**
 * count_args++ == 7 // before: count_args ==7 and line 164 = count_args++;
 **/
int	parse_lines(char *line, int i, int *counter, t_map *map)
{
	static int		count_args;
	static bool		next_is_map;

	if (i != 0 && (line[0] >= 65 && line[0] <= 90) && next_is_map == FALSE)
	{
		map->args = ft_split(line, 32);
		if (count_args++ == 7)
			next_is_map = TRUE;
		if (!ft_process_line(map))
			return (0);
	}
	else if (line[0] == '\0')
		;
	else if ((line[0] != 49 && line[0] != 32)
		|| line[ft_strlen(line) - 1] != 49)
		return (0);
	else
	{
		if (!ft_process_map(line, ++(*counter), map))
		{
			map->map[(*counter)] = NULL;
			return (0);
		}
	}
	return (1);
}

/**
 * i was changed to static, in case of errors chekc here
 * 
 **/
int	ft_get_next_line(t_map *map)
{
	char		*line;
	char		buf;
	static int	i;
	int			counter;

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
	ft_memdel((void **)&line);
	return (1);
}
