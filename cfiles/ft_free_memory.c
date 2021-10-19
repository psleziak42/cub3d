/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psleziak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 23:47:04 by psleziak          #+#    #+#             */
/*   Updated: 2021/10/19 23:59:39 by psleziak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/files/cub3d.h"

void	ft_free_memory(t_map *map)
{
	int	x;
	int	y;

	y = -1;
	while (map->map[++y])
		free(map[y]);
	free(map->map);
	y = -1;
	while (map->args[++y])
		free(map->args[y]);
	free(map->args);
	y = -1;
	while (map->RGB[++y])
		free(map->RGB[y]);
	free(map->RGB);
}
