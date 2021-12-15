/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_floor_ceiling.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 16:19:00 by psleziak          #+#    #+#             */
/*   Updated: 2021/12/15 22:54:22 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/cub3d.h"

int	ft_floor(t_map *map)
{
	int	index;

	map->rgb = ft_split(map->args[1], ',');
	map->c_f[F][0] = ft_atoi(map->rgb[0]);
	map->c_f[F][1] = ft_atoi(map->rgb[1]);
	map->c_f[F][2] = ft_atoi(map->rgb[2]);
	index = -1;
	while (map->rgb[++index])
		;
	free_rgb(map->rgb);
	if (index > 3)
		return (0);
	return (1);
}

int	ft_ceiling(t_map *map)
{
	int	index;

	map->rgb = ft_split(map->args[1], ',');
	map->c_f[C][0] = ft_atoi(map->rgb[0]);
	map->c_f[C][1] = ft_atoi(map->rgb[1]);
	map->c_f[C][2] = ft_atoi(map->rgb[2]);
	index = -1;
	while (map->rgb[++index])
		;
	free_rgb(map->rgb);
	if (index > 3)
		return (0);
	return (1);
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
