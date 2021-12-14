/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_forward2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psleziak <psleziak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 20:11:16 by psleziak          #+#    #+#             */
/*   Updated: 2021/12/14 00:54:22 by psleziak         ###   ########.fr       */
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
// 	delta_x = fabs(rx - get_trigo(0)->px_x); // chyba zle drukuje, trzeba popracoawc nad delta!!!, moze 2 rozne funkcje dac!!
// 	printf("deltax: %f\n", delta_x);
// 	// if (sin(get_trigo(0)->angle) != 0)
// 	// 	c = delta_x / sin(get_trigo(0)->angle);
// 	step = tan(ra);
// 	x = get_trigo(0)->px_x;
// 	y = get_trigo(0)->px_y;
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


void	ft_create_3d_world(float dist, float ra) // i ll need ofset lineO and lineH as return
{
	float	fish_eye;

	fish_eye = ra - get_trigo(0)->angle;
	if (fish_eye < 0)
		fish_eye += 2 * PI;
	if (fish_eye > 2*PI)
		fish_eye -= 2 * PI;
	dist = dist * cos(fish_eye);
	get_trigo(0)->lineH_3d = (TEXT * get_map(0)->win_hei) / dist;
	if (get_trigo(0)->lineH_3d > get_map(0)->win_hei)
		get_trigo(0)->lineH_3d = get_map(0)->win_hei;
	get_trigo(0)->lineO_3d = (get_map(0)->win_hei - get_trigo(0)->lineH_3d) / 2;
}

static float	ft_distance(float ry, float py, float rx, float px)
{
	return (sqrt((ry - py) * (ry - py) + (rx - px) * (rx - px)));
}

float	ft_hit_da_wall(float rx, float ry, float xo, float yo)
{
	int		mx;
	int		my;
	
	mx = (int)(rx / get_trigo(0)->unit_x_size);
	my = (int)(ry / get_trigo(0)->unit_y_size);
	while (my < get_map(0)->last_line && mx < get_map(0)->longest_line &&
		my > 0 && mx > 0 && get_map(0)->map[my][mx] != '1')
	{
		rx += xo;
		ry += yo;
		mx = (int)(rx / get_trigo(0)->unit_x_size);
		my = (int)(ry / get_trigo(0)->unit_y_size);
	}
	return(ft_distance(ry, get_trigo(0)->px_y, rx, get_trigo(0)->px_x));
}

/*** HORIZONTAL LINE ***/

float	ft_horizontal_line(float ra)
{
	float	rx; // wall_x; .
	float	ry; // wall_y; .
	float	xo;
	float	yo;
	
	if (!tan(ra))
	{
		ry = get_trigo(0)->px_y;
		rx = get_trigo(0)->px_x;
		yo = 0;
		xo = get_trigo(0)->unit_x_size;
	}
	else if (ra < PI)
	{
		ry = ((int)(get_trigo(0)->px_y / get_trigo(0)->unit_y_size) *
			get_trigo(0)->unit_y_size) - 0.0001;
		rx = ((get_trigo(0)->px_y - ry) / tan(ra)) + get_trigo(0)->px_x;
		yo = -get_trigo(0)->unit_y_size;
		xo = -yo / tan(ra);
	}
	else
	{
		ry = ((int)(get_trigo(0)->px_y / get_trigo(0)->unit_y_size) *
			get_trigo(0)->unit_y_size) + get_trigo(0)->unit_y_size; //- 0.0001; // - 0.0001;//  + 0.0001;
		rx = ((get_trigo(0)->px_y - ry) / tan(ra)) + get_trigo(0)->px_x;
		yo = get_trigo(0)->unit_y_size;
		xo = -yo / tan(ra);
	}
	return(ft_hit_da_wall(rx, ry, xo, yo));
}
	
	// int		mx;
	// int		my;
	
	// mx = (int)(rx / get_trigo(0)->unit_x_size);
	// my = (int)(ry / get_trigo(0)->unit_y_size);
	// while (my < get_map(0)->last_line && mx < get_map(0)->longest_line && my > 0 && mx > 0 && get_map(0)->map[my][mx] != '1')
	// {
	// 	rx += xo;
	// 	ry += yo;
	// 	mx = (int)(rx / get_trigo(0)->unit_x_size);
	// 	my = (int)(ry / get_trigo(0)->unit_y_size);
	// }
	// get_trigo(0)->ryh = ry;
	// get_trigo(0)->rxh = rx;
	// return(ft_distance(ry, get_trigo(0)->px_y, rx, get_trigo(0)->px_x));
	// //return(ft_hit_da_wall(rx, ry, xo, yo));

/*** VERTICAL LINE ***/

float	ft_vertical_line(float ra)
{
	float	ry;
	float	rx;
	float	xo;
	float	yo;
	
	if (!tan(ra))
	{
		ry = get_trigo(0)->px_y;
		rx = get_trigo(0)->px_x;
		yo = get_trigo(0)->unit_x_size;
		xo = 0;
	}
	else if (ra > P2 && ra < P3)
	{
		rx =((int)(get_trigo(0)->px_x / get_trigo(0)->unit_x_size) *
			get_trigo(0)->unit_x_size) - 0.0001;
		ry = ((get_trigo(0)->px_x - rx) * tan(ra)) + get_trigo(0)->px_y;
		xo = -get_trigo(0)->unit_x_size;
		yo = -xo * tan(ra);
	}
	else
	{
		rx = ((int)(get_trigo(0)->px_x / get_trigo(0)->unit_x_size) *
			get_trigo(0)->unit_x_size) + get_trigo(0)->unit_x_size; //- 0.0001; // - 0.0001;//  + 0.0001;
		ry = ((get_trigo(0)->px_x - rx) * tan(ra)) + get_trigo(0)->px_y;
		xo = get_trigo(0)->unit_x_size;
		yo = -xo * tan(ra);
	}
	return(ft_hit_da_wall(rx, ry, xo, yo));
}
	// int		mx;
	// int		my;
	
	// mx = (int)(rx / get_trigo(0)->unit_x_size);
	// my = (int)(ry / get_trigo(0)->unit_y_size);
	// while (my < get_map(0)->last_line && mx < get_map(0)->longest_line && my > 0 && mx > 0 && get_map(0)->map[my][mx] != '1')
	// {
	// 	rx += xo;
	// 	ry += yo;
	// 	mx = (int)(rx / get_trigo(0)->unit_x_size);
	// 	my = (int)(ry / get_trigo(0)->unit_y_size);
	// }
	// get_trigo(0)->ryv = ry;
	// get_trigo(0)->rxv = rx;
	// return(ft_distance(ry, get_trigo(0)->px_y, rx, get_trigo(0)->px_x));
	// //return(ft_hit_da_wall(rx, ry, xo, yo));

float ft_360(float ra)
{
	if (ra < 0)
		ra += 2 * PI;
	if (ra > 2*PI)
		ra -= 2 * PI;
	return (ra);
}

void	ft_raycasting(void)
{
	float	dist_H;
	float	dist;
	float	ra;
	int		dir;
	int		i;

	ra = get_trigo(0)->angle + 30 * degree;
	ft_360(ra);
	i = -1;
	while (++i < get_map(0)->win_wid)
	{
		dir = 0;
		dist_H = ft_horizontal_line(ra);
		dist = ft_vertical_line(ra);
		if (dist_H < dist)
		{
			dist = dist_H;
			dir = 1;
			//ft_print_one_ray_h(get_trigo(0)->rxh, get_trigo(0)->ryh, ra, 0xFF0000);
		}
		//ft_print_one_ray_h(get_trigo(0)->rxv, get_trigo(0)->ryv, ra, 0x0000FF);
		ft_create_3d_world(dist, ra);
		ft_3d_print_addr(i, dir, ra);
		ra -= degree / (get_map(0)->win_wid / 60);
		ft_360(ra);
	}
}
