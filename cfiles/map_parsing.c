/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 16:28:32 by psleziak          #+#    #+#             */
/*   Updated: 2021/12/14 00:27:47 by rimartin         ###   ########.fr       */
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

void	free_dp(char **dp)
{
	int	x;

	x = -1;
	while (dp[++x])
	{
		free(dp[x]);
		dp[x] = NULL;
	}
	free(dp);
	dp = NULL;
}

bool	is_wrong_color(int r, int g, int b)
{
	if (r <= 255 && r >= 0)
		return (false);
	else if (g <= 255 && g >= 0)
		return (false);
	else if (b <= 255 && b >= 0)
		return (false);
	return (true);
}

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
		printf("g_master.map %s\n", g_master.map.map[y]);
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
				{
					// printf("inside if g_master.map %c y %d x %d\n", g_master.map.map[y + 1][x], y, x);	
					printf("inside if g_master.map %s y %d x %d\n", g_master.map.map[y + 1], y, x);	
					return (0);
				}
				if (g_master.map.map[y][x] == 'N' || g_master.map.map[y][x] == 'S' || g_master.map.map[y][x] == 'E' || g_master.map.map[y][x] == 'W')
				{
					g_master.trigo.pixel_x = x * g_master.trigo.unit_x_size;
					g_master.trigo.pixel_y = y * g_master.trigo.unit_y_size;
					if (g_master.map.map[y][x] == 'N')
						g_master.trigo.current_angle = (PI/2);
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
				g_master.map.map[y][x] = ' '; // checked with 'x' it works, now we turn it back to spaces;
				x++;
			}
			g_master.map.map[y][x] = '\0';
		}
	}
}

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

static int		ft_process_map(char *line, int counter) 
{
	int	i;

	if (counter == 0)
		g_master.map.map = malloc(sizeof(char *) * (counter + 2));
	else
		g_master.map.map = realloc(g_master.map.map, sizeof(char *) * (counter + 2));
	i = 0;
	while (line[i])
	{
		if (!is_valid_char(line[i++], (char[9]){'0', '1', 'N', 'E', 'S', 'W', ' ', '\n', '\0'}))
			return (0);
	}
	g_master.map.map[counter] = ft_strdup(line);
	printf("inside map %s\n", g_master.map.map[counter]);
	return (1);
}

static int		ft_process_line(void)
{
	// printf("%d %d\n", g_master.map.window_width, g_master.map.window_height);
	if (g_master.map.args[0][0] == 'R' && g_master.map.window_width == 0 && g_master.map.window_height == 0) // if wrong value, return atoi -1 i finish
	{
		g_master.map.window_width = ft_atoi(g_master.map.args[1]);  // less than 0 should throw error
		g_master.map.window_height = ft_atoi(g_master.map.args[2]); // less than 0 should throw error
		if (g_master.map.window_height <= 0 || g_master.map.window_width <= 0)
			return (0); 
	}
	else if (!(ft_strncmp(g_master.map.args[0], "NO", 3)) && g_master.map.NSEW[N] == NULL)
		g_master.map.NSEW[N] = ft_strtrim(g_master.map.args[1], "\n");
	else if (!(ft_strncmp(g_master.map.args[0], "SO", 3)) && g_master.map.NSEW[S] == NULL)
		g_master.map.NSEW[S] = ft_strtrim(g_master.map.args[1], "\n");
	else if (!(ft_strncmp(g_master.map.args[0], "WE", 3)) && g_master.map.NSEW[W] == NULL)
		g_master.map.NSEW[W] = ft_strtrim(g_master.map.args[1], "\n");
	else if (!(ft_strncmp(g_master.map.args[0], "EA", 3)) && g_master.map.NSEW[E] == NULL)
		g_master.map.NSEW[E] = ft_strtrim(g_master.map.args[1], "\n");
	else if (g_master.map.args[0][0] == 'F')
	{
		g_master.map.RGB = ft_split(g_master.map.args[1], ',');
		g_master.map.c_f[F][0] = ft_atoi(g_master.map.RGB[0]); 
		g_master.map.c_f[F][1] = ft_atoi(g_master.map.RGB[1]);
		g_master.map.c_f[F][2] = ft_atoi(g_master.map.RGB[2]);
		if (is_wrong_color(g_master.map.c_f[F][0], g_master.map.c_f[F][1], g_master.map.c_f[F][2]))
			return (0);
		free_dp(g_master.map.RGB);
	}	
	else if (g_master.map.args[0][0] == 'C') 
	{
		g_master.map.RGB = ft_split(g_master.map.args[1], ',');
		g_master.map.c_f[C][0] = ft_atoi(g_master.map.RGB[0]);
		g_master.map.c_f[C][1] = ft_atoi(g_master.map.RGB[1]);
		g_master.map.c_f[C][2]= ft_atoi(g_master.map.RGB[2]);
		if (is_wrong_color(g_master.map.c_f[C][0], g_master.map.c_f[C][1], g_master.map.c_f[C][2]))
			return (0);
		free_dp(g_master.map.RGB);
	}
	else
		return (0);
		
	return (1);
}

int	parse_lines(char *line, int i, int *counter)
{
	static int		count_args;
	static bool		next_is_map;

	if (i != 0 && (line[0] >= 65 && line[0] <= 90) && next_is_map == FALSE)
	{
		g_master.map.args = ft_split(line, 32);
		if (count_args == 7)
			next_is_map = TRUE;
		if (!ft_process_line())
			return (0);
		count_args++;
	}
	else if (line[0] == '\0')
		;
	else if ((line[0] != 49 && line[0] != 32) || line[ft_strlen(line) - 1] != 49)
		return (0);
	else 
	{
		if(!ft_process_map(line, ++(*counter)))
		{
			g_master.map.map[(*counter)] = NULL;
			return (0);
		}
	}
	return (1);
}

int		ft_get_next_line(void)
{
	char	*line;
	char	buf;
	int		i;
	int		count_args;
	int		counter;

	i = 0;
	counter = -1;
	count_args = 0;
	line = malloc(8192);
	if (g_master.map.fd < 0 || !line)
		return (0);
	while (read(g_master.map.fd, &buf, 1))
	{
		if (buf == '\n')
		{
			line[i] = '\0';
			if (!parse_lines(line, i, &counter))
				return (0);
			i = 0;
		}
		else
			line[i++] = buf;
	}
	g_master.map.last_line = counter;
	g_master.map.map[++counter] = NULL;
	return (1);
}
