/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_floor_ceiling.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psleziak <psleziak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 16:19:00 by psleziak          #+#    #+#             */
/*   Updated: 2021/12/15 18:55:16 by psleziak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/cub3d.h"

void	ft_floor(t_map *map)
{
	map->rgb = ft_split(map->args[1], ',');
	map->c_f[F][0] = ft_atoi(map->rgb[0]);
	map->c_f[F][1] = ft_atoi(map->rgb[1]);
	map->c_f[F][2] = ft_atoi(map->rgb[2]);
	free_rgb(map->rgb);
}

void	ft_ceiling(t_map *map)
{
	map->rgb = ft_split(map->args[1], ',');
	map->c_f[C][0] = ft_atoi(map->rgb[0]);
	map->c_f[C][1] = ft_atoi(map->rgb[1]);
	map->c_f[C][2] = ft_atoi(map->rgb[2]);
	free_rgb(map->rgb);
}

bool	is_wrong_color(int r, int g, int b)
{
	if ((r >= 0 && r <= 255) && (g >= 0 && g <= 255) && (b >= 0 && b <= 255))
		return (true);
	return (false);
}

int	ft_check_rgb_values(t_map *map)
{
	if (!is_wrong_color(map->c_f[F][0], map->c_f[F][1], map->c_f[F][2]))
		return (0);
	if (!is_wrong_color(map->c_f[C][0], map->c_f[C][1], map->c_f[C][2]))
		return (0);
	return (1);
}
