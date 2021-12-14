/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 16:28:32 by psleziak          #+#    #+#             */
/*   Updated: 2021/12/14 18:43:57 by rimartin         ###   ########.fr       */
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
	while (get_map(0)->map[++y])
		printf("%s", get_map(0)->map[y]);
}

int		ft_check_de_map(void) 
{
	int	x;
	int y;
	int	player;

	y = -1;
	player = 0;
	while (get_map(0)->map[++y])
	{
		x = -1;
		while (get_map(0)->map[y][++x])
		{
			if (y == 0 || y == get_map(0)->last_line)
			{
				if (get_map(0)->map[y][x] != '1' && get_map(0)->map[y][x] != ' ' && get_map(0)->map[y][x] != '\n')
					return (0);
			}
			else if (get_map(0)->map[y][x] == 48 || get_map(0)->map[y][x] == 'N' || get_map(0)->map[y][x] == 'S' || get_map(0)->map[y][x] == 'E' || get_map(0)->map[y][x] == 'W') 
			{
				if (get_map(0)->map[y][x+1] == 32 || get_map(0)->map[y][x-1] == 32 || get_map(0)->map[y+1][x] == 32 || get_map(0)->map[y-1][x] == 32) 
					return (0);
				if (get_map(0)->map[y][x] == 'N' || get_map(0)->map[y][x] == 'S' || get_map(0)->map[y][x] == 'E' || get_map(0)->map[y][x] == 'W')
				{
					get_trigo(0)->px_x = x * get_trigo(0)->unit_x_size;
					get_trigo(0)->px_y = y * get_trigo(0)->unit_y_size;
					if (get_map(0)->map[y][x] == 'N')
						get_trigo(0)->angle = (PI/2);
					else if (get_map(0)->map[y][x] == 'S')
						get_trigo(0)->angle = 3 * PI / 2;
					else if (get_map(0)->map[y][x] == 'E')
						get_trigo(0)->angle = 0;
					else if (get_map(0)->map[y][x] == 'W')
						get_trigo(0)->angle = PI; 
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
	while (get_map(0)->map[++y])
	{
		x = -1;	
		while (get_map(0)->map[y][++x])
			;
		if (x < l)
		{
			get_map(0)->map[y] = realloc(get_map(0)->map[y], sizeof(char) * (l + 1));
			while (x < l)
			{
				if (x == l)
					get_map(0)->map[y][x] = '\0';
				if (x == l - 1)
					get_map(0)->map[y][x] = '\n';
				get_map(0)->map[y][x - 1] = ' '; // checked with 'x' it works, now we turn it back to spaces;
				x++;
			}
			get_map(0)->map[y][x] = '\0';
		}
	}
}

static int		ft_process_map(char *line, int counter) 
{
	if (counter == 0)
		get_map(0)->map = malloc(sizeof(char *) * (counter + 2));
	else
		get_map(0)->map = realloc(get_map(0)->map, sizeof(char *) * (counter + 2));
	get_map(0)->map[counter] = ft_strdup(line);
	return (1);
}

static int		ft_process_line(void)
{
	if (get_map(0)->args[0][0] == 'R') // if wrong value, return atoi -1 i finish
	{
		get_map(0)->win_wid = ft_atoi(get_map(0)->args[1]);  // less than 0 should throw error
		get_map(0)->win_hei = ft_atoi(get_map(0)->args[2]); // less than 0 should throw error
		if (get_map(0)->win_hei <= 0 || get_map(0)->win_wid <= 0)
			return (0); 
	}
	else if (!(ft_strncmp(get_map(0)->args[0], "NO", 2)))
		get_map(0)->nsew[N] = get_map(0)->args[1];
	else if (!(ft_strncmp(get_map(0)->args[0], "SO", 2)))
		get_map(0)->nsew[S] = get_map(0)->args[1];
	else if (!(ft_strncmp(get_map(0)->args[0], "WE", 2)))
		get_map(0)->nsew[E] = get_map(0)->args[1];
	else if (!(ft_strncmp(get_map(0)->args[0], "EA", 2)))
		get_map(0)->nsew[W] = get_map(0)->args[1];
	else if (get_map(0)->args[0][0] == 'F') // < 0 && > 255 error
	{
		get_map(0)->rgb = ft_split(get_map(0)->args[1], ',');
		get_map(0)->c_f[F][0] = ft_atoi(get_map(0)->rgb[0]); 
		get_map(0)->c_f[F][1] = ft_atoi(get_map(0)->rgb[1]);
		get_map(0)->c_f[F][2] = ft_atoi(get_map(0)->rgb[2]);
		/*if (wrong_color_range(map->FR, map->FG, map->FB))
			return (0);*/
	}	
	else if (get_map(0)->args[0][0] == 'C') 
	{
		get_map(0)->rgb = ft_split(get_map(0)->args[1], ',');
		get_map(0)->c_f[C][0] = ft_atoi(get_map(0)->rgb[0]);
		get_map(0)->c_f[C][1] = ft_atoi(get_map(0)->rgb[1]);
		get_map(0)->c_f[C][2] = ft_atoi(get_map(0)->rgb[2]);
		/*if (wrong_color_range(get_map(0)->FR, map->FG, map->FB))
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
	if (get_map(0)->fd < 0 || !line)
		return (0);
	while (read(get_map(0)->fd, &buf, 1))
	{
		if (buf == '\n')
		{
			line[i] = buf; 
			line[++i] = '\0';
			if (i != 0 && (line[0] >= 65 && line[0] <= 90) && next_is_map == FALSE)
			{
				get_map(0)->args = ft_split(line, 32);
				if (get_map(0)->args[0][0] == 'C')
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
	if (i != 0)
	{
		line[i] = '\0';
		get_map(0)->map[++counter] = ft_strdup(line);
		get_map(0)->map = realloc(get_map(0)->map, sizeof(char *) * (counter + 2));
	}		
	get_map(0)->last_line = counter;
	get_map(0)->map[++counter] = NULL;
	free(line);
	line = NULL;
	return (1);
}
