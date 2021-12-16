/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psleziak <psleziak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 17:16:58 by psleziak          #+#    #+#             */
/*   Updated: 2021/12/15 21:01:06 by psleziak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/cub3d.h"

float	ft_distance(float ry, float py, float rx, float px)
{
	return (sqrt((ry - py) * (ry - py) + (rx - px) * (rx - px)));
}

float	ft_360(float ra)
{
	if (ra < 0)
		ra += 2 * PI;
	if (ra > 2 * PI)
		ra -= 2 * PI;
	return (ra);
}
