/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psleziak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 00:16:06 by psleziak          #+#    #+#             */
/*   Updated: 2021/10/22 00:28:46 by psleziak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/cub3d.h"

void	ft_map_create(t_window *window, t_map *map)
{
	window->mlx_p = mlx_init();
	window->win_p = mlx_new_window(window->mlx_p, map->windo_width, map->window_height, "cub3d_beaches");
	mlx_loop(window->mlx_p);
}
