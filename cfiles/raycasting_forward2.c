/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_forward2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psleziak <psleziak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 20:11:16 by psleziak          #+#    #+#             */
/*   Updated: 2021/12/14 23:44:11 by psleziak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/cub3d.h"

//====================================================================
// static void	ft_print_one_ray_h(float rx, float ry, float ra, int color)
// {
// 	float 	x;
// 	float	y;
// 	float	i;
// 	//float	c;
// 	float	delta_x;
// 	float	step;

// 	ry = (float)ry;
// 	i = 0;
// 	delta_x = fabs(rx - trigo->px_x); // chyba zle drukuje, trzeba popracoawc nad delta!!!, moze 2 rozne funkcje dac!!
// 	printf("deltax: %f\n", delta_x);
// 	// if (sin(trigo->angle) != 0)
// 	// 	c = delta_x / sin(trigo->angle);
// 	step = tan(ra);
// 	x = trigo->px_x;
// 	y = trigo->px_y;
// 	while (i < delta_x)
// 	{
// 		mlx_pixel_put(get_win(0)->mlx_p, get_win(0)->win_p, x, y, color);
// 		if (cos(ra) > 0)
// 			y -= step;
// 		else
// 			y += step;
// 		if (cos(ra) < 0)
// 				x -= 1;
// 		else
// 			x += 1;
// 		i++;
// 	}	
// }
// ============================================================
// static void	ft_3d_printer(float lineH, float lineO, float width_x);


void	ft_create_3d_world(t_trigo *trigo, float dist, float ra)
{
	float	fish_eye;

	fish_eye = ra - trigo->angle;
	if (fish_eye < 0)
		fish_eye += 2 * PI;
	if (fish_eye > 2*PI)
		fish_eye -= 2 * PI;
	dist = dist * cos(fish_eye);
	trigo->line_h_3d = (TEXT * get_map(0)->win_hei) / dist;
	if (trigo->line_h_3d > get_map(0)->win_hei)
		trigo->line_h_3d = get_map(0)->win_hei;
	trigo->line_o_3d = (get_map(0)->win_hei - trigo->line_h_3d) / 2;
}

static float	ft_distance(float ry, float py, float rx, float px)
{
	return (sqrt((ry - py) * (ry - py) + (rx - px) * (rx - px)));
}

float	ft_hit_da_wall(t_trigo *trigo, float rx, float ry, float xo, float yo)
{
	int		mx;
	int		my;
	
	mx = (int)(rx / trigo->unit_x_size);
	my = (int)(ry / trigo->unit_y_size);
	while (my < get_map(0)->last_line && mx < get_map(0)->longest_line &&
		my > 0 && mx > 0 && get_map(0)->map[my][mx] != '1')
	{
		rx += xo;
		ry += yo;
		mx = (int)(rx / trigo->unit_x_size);
		my = (int)(ry / trigo->unit_y_size);
	}
	return(ft_distance(ry, trigo->px_y, rx, trigo->px_x));
}

/*** HORIZONTAL LINE ***/

float	ft_horizontal_line(t_trigo *trigo, float ra)
{
	float	rx;
	float	ry;
	float	xo;
	float	yo;
	
	if (!tan(ra))
	{
		ry = trigo->px_y;
		rx = trigo->px_x;
		yo = 0;
		xo = trigo->unit_x_size;
	}
	else if (ra < PI)
	{
		ry = ((int)(trigo->px_y / trigo->unit_y_size) *
			trigo->unit_y_size) - 0.0001;
		rx = ((trigo->px_y - ry) / tan(ra)) + trigo->px_x;
		yo = -trigo->unit_y_size;
		xo = -yo / tan(ra);
	}
	else
	{
		ry = ((int)(trigo->px_y / trigo->unit_y_size) *
			trigo->unit_y_size) + trigo->unit_y_size;
		rx = ((trigo->px_y - ry) / tan(ra)) + trigo->px_x;
		yo = trigo->unit_y_size;
		xo = -yo / tan(ra);
	}
	return(ft_hit_da_wall(trigo, rx, ry, xo, yo));
}
	
	// int		mx;
	// int		my;
	
	// mx = (int)(rx / trigo->unit_x_size);
	// my = (int)(ry / trigo->unit_y_size);
	// while (my < get_map(0)->last_line && mx < get_map(0)->longest_line && my > 0 && mx > 0 && get_map(0)->map[my][mx] != '1')
	// {
	// 	rx += xo;
	// 	ry += yo;
	// 	mx = (int)(rx / trigo->unit_x_size);
	// 	my = (int)(ry / trigo->unit_y_size);
	// }
	// trigo->ryh = ry;
	// trigo->rxh = rx;
	// return(ft_distance(ry, trigo->px_y, rx, trigo->px_x));
	// //return(ft_hit_da_wall(rx, ry, xo, yo));

/*** VERTICAL LINE ***/

float	ft_vertical_line(t_trigo *trigo, float ra)
{
	float	ry;
	float	rx;
	float	xo;
	float	yo;
	
	if (!tan(ra))
	{
		ry = trigo->px_y;
		rx = trigo->px_x;
		yo = trigo->unit_x_size;
		xo = 0;
	}
	else if (ra > P2 && ra < P3)
	{
		rx =((int)(trigo->px_x / trigo->unit_x_size) *
			trigo->unit_x_size) - 0.0001;
		ry = ((trigo->px_x - rx) * tan(ra)) + trigo->px_y;
		xo = -trigo->unit_x_size;
		yo = -xo * tan(ra);
	}
	else
	{
		rx = ((int)(trigo->px_x / trigo->unit_x_size) *
			trigo->unit_x_size) + trigo->unit_x_size;
		ry = ((trigo->px_x - rx) * tan(ra)) + trigo->px_y;
		xo = trigo->unit_x_size;
		yo = -xo * tan(ra);
	}
	return(ft_hit_da_wall(trigo, rx, ry, xo, yo));
}
	// int		mx;
	// int		my;
	
	// mx = (int)(rx / trigo->unit_x_size);
	// my = (int)(ry / trigo->unit_y_size);
	// while (my < get_map(0)->last_line && mx < get_map(0)->longest_line && my > 0 && mx > 0 && get_map(0)->map[my][mx] != '1')
	// {
	// 	rx += xo;
	// 	ry += yo;
	// 	mx = (int)(rx / trigo->unit_x_size);
	// 	my = (int)(ry / trigo->unit_y_size);
	// }
	// trigo->ryv = ry;
	// trigo->rxv = rx;
	// return(ft_distance(ry, trigo->px_y, rx, trigo->px_x));
	// //return(ft_hit_da_wall(rx, ry, xo, yo));

float ft_360(float ra)
{
	if (ra < 0)
		ra += 2 * PI;
	if (ra > 2*PI)
		ra -= 2 * PI;
	return (ra);
}

void	ft_raycasting(t_trigo *trigo)
{
	float	dist_H;
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
		dist_H = ft_horizontal_line(trigo, ra);
		dist = ft_vertical_line(trigo, ra);
		if (dist_H < dist)
		{
			printf("i: %d, distH: %f", i, dist_H);
			dist = dist_H;
			dir = 1;
		}
		ft_create_3d_world(trigo, dist, ra);
		ft_update_walls(trigo, i, dir, ra);
		ra -= DEGREE / (get_map(0)->win_wid / 60);
		ra = ft_360(ra);
	}
}
