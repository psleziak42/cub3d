/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psleziak <psleziak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 16:28:32 by psleziak          #+#    #+#             */
/*   Updated: 2021/11/29 19:21:08 by psleziak         ###   ########.fr       */
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

void	ft_print_map(void)
{
	int y;

	y = -1;
	while (g_master.map.map[++y])
		printf("%s", g_master.map.map[y]);
}

int		ft_check_de_map(void) 
{
	int	x;
	int y;
	int	player;

	y = -1;
	player = 0;
	while (g_master.map.map[++y])
	{
		x = -1;
		while (g_master.map.map[y][++x])
		{
			if (y == 0 || y == g_master.map.last_line)
			{
				if (g_master.map.map[y][x] != '1' && g_master.map.map[y][x] != ' ' && g_master.map.map[y][x] != '\n')
					return (0);
			}
			else if (g_master.map.map[y][x] == 48 || g_master.map.map[y][x] == 'N' || g_master.map.map[y][x] == 'S' || g_master.map.map[y][x] == 'E' || g_master.map.map[y][x] == 'W') 
			{
				if (g_master.map.map[y][x+1] == 32 || g_master.map.map[y][x-1] == 32 || g_master.map.map[y+1][x] == 32 || g_master.map.map[y-1][x] == 32) 
					return (0);
				if (g_master.map.map[y][x] == 'N' || g_master.map.map[y][x] == 'S' || g_master.map.map[y][x] == 'E' || g_master.map.map[y][x] == 'W')
				{
					g_master.trigo.map2d_x = x;
					g_master.trigo.map2d_y = y;
					g_master.trigo.imaginary_map2d_x = g_master.trigo.map2d_x;
					g_master.trigo.imaginary_map2d_y = g_master.trigo.map2d_y;
					g_master.trigo.pixel_x = x * g_master.trigo.unit_x_size;
					g_master.trigo.pixel_y = y * g_master.trigo.unit_y_size;
					if (g_master.map.map[y][x] == 'N')
						g_master.trigo.current_angle = (2*PI - PI/6);
					else if (g_master.map.map[y][x] == 'S')
						g_master.trigo.current_angle = 3 * PI / 2;
					else if (g_master.map.map[y][x] == 'E')
						g_master.trigo.current_angle = 0;
					else if (g_master.map.map[y][x] == 'W')
						g_master.trigo.current_angle = PI; 
					player++;
				}	
			}
		}
	}
	if (player != 1)
		return (0);
	return (1);
}

void	ft_resize_map_to_square(int l)
{
	int	x;
	int	y;

	y = -1;
	while (g_master.map.map[++y])
	{
		x = -1;	
		while (g_master.map.map[y][++x])
			;
		if (x < l)
		{
			g_master.map.map[y] = realloc(g_master.map.map[y], sizeof(char) * (l + 1));
			while (x < l)
			{
				if (x == l)
					g_master.map.map[y][x] = '\0';
				if (x == l - 1)
					g_master.map.map[y][x] = '\n';
				g_master.map.map[y][x - 1] = ' '; // checked with 'x' it works, now we turn it back to spaces;
				x++;
			}
			g_master.map.map[y][x] = '\0';
		}
	}
}

static int		ft_process_map(char *line, int counter) 
{
	int		size;
	
	if (counter == 0)
		g_master.map.map = malloc(sizeof(char *) * (counter + 2));
	else
		g_master.map.map = realloc(g_master.map.map, sizeof(char *) * (counter + 2));
	size = ft_strlen(line);
	g_master.map.map[counter] = ft_strdup(line);
	return (1);
}

static int		ft_process_line(void)
{
	if (g_master.map.args[0][0] == 'R') // if wrong value, return atoi -1 i finish
	{
		g_master.map.window_width = ft_atoi(g_master.map.args[1]);  // less than 0 should throw error
		g_master.map.window_height = ft_atoi(g_master.map.args[2]); // less than 0 should throw error
		if (g_master.map.window_height <= 0 || g_master.map.window_width <= 0)
			return (0); 
	}
	else if (!(ft_strncmp(g_master.map.args[0], "NO", 2)))
		g_master.map.N = g_master.map.args[1];
	else if (!(ft_strncmp(g_master.map.args[0], "SO", 2)))
		g_master.map.S = g_master.map.args[1];
	else if (!(ft_strncmp(g_master.map.args[0], "WE", 2)))
		g_master.map.E = g_master.map.args[1];
	else if (!(ft_strncmp(g_master.map.args[0], "EA", 2)))
		g_master.map.W = g_master.map.args[1];
	else if (g_master.map.args[0][0] == 'F') // < 0 && > 255 error
	{
		g_master.map.RGB = ft_split(g_master.map.args[1], ',');
		g_master.map.FR = ft_atoi(g_master.map.RGB[0]); 
		g_master.map.FG = ft_atoi(g_master.map.RGB[1]);
		g_master.map.FB = ft_atoi(g_master.map.RGB[2]);
		/*if (wrong_color_range(map->FR, map->FG, map->FB))
			return (0);*/
	}	
	else if (g_master.map.args[0][0] == 'C') 
	{
		g_master.map.RGB = ft_split(g_master.map.args[1], ',');
		g_master.map.CR = ft_atoi(g_master.map.RGB[0]);
		g_master.map.CG = ft_atoi(g_master.map.RGB[1]);
		g_master.map.CB = ft_atoi(g_master.map.RGB[2]);
		/*if (wrong_color_range(g_master.map.FR, map->FG, map->FB))
			return (0);*/
	}
	return (1);
}

int		ft_get_next_line(void)
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
	if (g_master.map.fd < 0 || !line)
		return (0);
	while (read(g_master.map.fd, &buf, 1))
	{
		if (buf == '\n')
		{
			line[i] = buf; 
			line[++i] = '\0';
			if (i != 0 && (line[0] >= 65 && line[0] <= 90) && next_is_map == FALSE) // to jest kod do informacji o teksturach i rozmiarze
			{
				g_master.map.args = ft_split(line, 32);
				if (g_master.map.args[0][0] == 'C')
					next_is_map = TRUE;
				if (!ft_process_line())
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
				if(!ft_process_map(line, ++counter))
					break ;
				i = 0;
				continue ;
			}
		}
		line[i++] = buf;
	}
	g_master.map.last_line = counter;
	g_master.map.map[++counter] = NULL;
	return (1);
}
