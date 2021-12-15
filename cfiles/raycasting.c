/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psleziak <psleziak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 20:11:16 by psleziak          #+#    #+#             */
/*   Updated: 2021/12/15 21:00:54 by psleziak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/cub3d.h"

void	ft_create_3d_world(t_trigo *trigo, float dist, float ra)
{
	float	fish_eye;

	fish_eye = ra - trigo->angle;
	ra = ft_360(ra);
	dist = dist * cos(fish_eye);
	trigo->line_h_3d = (TEXT * get_map(0)->win_hei) / dist;
	if (trigo->line_h_3d > get_map(0)->win_hei)
		trigo->line_h_3d = get_map(0)->win_hei;
	trigo->line_o_3d = (get_map(0)->win_hei - trigo->line_h_3d) / 2;
}

float	ft_hit_da_wall(t_trigo *trigo)
{
	int		mx;
	int		my;

	mx = (int)(trigo->rx / trigo->unit_x_size);
	my = (int)(trigo->ry / trigo->unit_y_size);
	while (my < get_map(0)->last_line && mx < get_map(0)->longest_line
		&& my > 0 && mx > 0 && get_map(0)->map[my][mx] != '1')
	{
		trigo->rx += trigo->xo;
		trigo->ry += trigo->yo;
		mx = (int)(trigo->rx / trigo->unit_x_size);
		my = (int)(trigo->ry / trigo->unit_y_size);
	}
	return (ft_distance(trigo->ry, trigo->px_y, trigo->rx, trigo->px_x));
}

/*** HORIZONTAL LINE ***/

float	ft_horizontal_line(t_trigo *trigo, float ra)
{
	if (!tan(ra))
	{
		trigo->ry = trigo->px_y;
		trigo->rx = trigo->px_x;
		trigo->yo = 0;
		trigo->xo = trigo->unit_x_size;
	}
	else if (ra < PI)
	{
		trigo->ry = ((int)(trigo->px_y / trigo->unit_y_size)
				* trigo->unit_y_size) - 0.0001;
		trigo->rx = ((trigo->px_y - trigo->ry) / tan(ra)) + trigo->px_x;
		trigo->yo = -trigo->unit_y_size;
		trigo->xo = -trigo->yo / tan(ra);
	}
	else
	{
		trigo->ry = ((int)(trigo->px_y / trigo->unit_y_size)
				* trigo->unit_y_size) + trigo->unit_y_size;
		trigo->rx = ((trigo->px_y - trigo->ry) / tan(ra)) + trigo->px_x;
		trigo->yo = trigo->unit_y_size;
		trigo->xo = -trigo->yo / tan(ra);
	}
	return (ft_hit_da_wall(trigo));
}

/*** VERTICAL LINE ***/

float	ft_vertical_line(t_trigo *trigo, float ra)
{
	if (!tan(ra))
	{
		trigo->ry = trigo->px_y;
		trigo->rx = trigo->px_x;
		trigo->yo = trigo->unit_x_size;
		trigo->xo = 0;
	}
	else if (ra > PI / 2 && ra < 3 * PI / 2)
	{
		trigo->rx = ((int)(trigo->px_x / trigo->unit_x_size)
				* trigo->unit_x_size) - 0.0001;
		trigo->ry = ((trigo->px_x - trigo->rx) * tan(ra)) + trigo->px_y;
		trigo->xo = -trigo->unit_x_size;
		trigo->yo = -trigo->xo * tan(ra);
	}
	else
	{
		trigo->rx = ((int)(trigo->px_x / trigo->unit_x_size)
				* trigo->unit_x_size) + trigo->unit_x_size;
		trigo->ry = ((trigo->px_x - trigo->rx) * tan(ra)) + trigo->px_y;
		trigo->xo = trigo->unit_x_size;
		trigo->yo = -trigo->xo * tan(ra);
	}
	return (ft_hit_da_wall(trigo));
}

void	ft_raycasting(t_trigo *trigo)
{
	float	dist_h;
	float	dist;
	float	ra;
	int		dir;
	int		i;

	ra = trigo->angle + 30 * DEGREE;
	ra = ft_360(ra);
	i = -1;
	while (++i < get_map(0)->win_wid)
	{
		dir = 0;
		dist_h = ft_horizontal_line(trigo, ra);
		dist = ft_vertical_line(trigo, ra);
		if (dist_h < dist)
		{
			dist = dist_h;
			dir = 1;
		}
		ft_create_3d_world(trigo, dist, ra);
		ft_update_walls(trigo, i, dir, ra);
		ra -= DEGREE / (get_map(0)->win_wid / 60);
		ra = ft_360(ra);
	}
}
