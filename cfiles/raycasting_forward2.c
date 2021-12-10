/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_forward2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psleziak <psleziak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 20:11:16 by psleziak          #+#    #+#             */
/*   Updated: 2021/12/09 18:02:30 by psleziak         ###   ########.fr       */
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
// 	delta_x = fabs(rx - g_master.trigo.pixel_x); // chyba zle drukuje, trzeba popracoawc nad delta!!!, moze 2 rozne funkcje dac!!
// 	printf("deltax: %f\n", delta_x);
// 	// if (sin(g_master.trigo.current_angle) != 0)
// 	// 	c = delta_x / sin(g_master.trigo.current_angle);
// 	step = tan(ra);
// 	x = g_master.trigo.pixel_x;
// 	y = g_master.trigo.pixel_y;
// 	while (i < delta_x)
// 	{
// 		mlx_pixel_put(g_master.window.mlx_p, g_master.window.win_p, x, y, color);
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


void	ft_create_3d_world(float dist, float ra, int i) // i ll need ofset lineO and lineH as return
{
	float	fish_eye;

	i = (int)i;
	fish_eye = ra - g_master.trigo.current_angle;
	if (fish_eye < 0)
		fish_eye += 2 * PI;
	if (fish_eye > 2*PI)
		fish_eye -= 2 * PI;
	dist = dist * cos(fish_eye);
	//printf("dist: %f, i: %d\n", dist, i);
	g_master.trigo.lineH_3d = (g_master.trigo.cub_size * g_master.map.window_height) / dist;
	if (g_master.trigo.lineH_3d > g_master.map.window_height)
		g_master.trigo.lineH_3d = g_master.map.window_height;
	// if (g_master.trigo.lineH_3d <= TEXT)
	// 	g_master.trigo.lineH_3d = TEXT;
	g_master.trigo.lineO_3d = (g_master.map.window_height - g_master.trigo.lineH_3d) / 2;
	// printf("g_master.trigo.lineH_3d: %f, i: %d\n", g_master.trigo.lineH_3d, i);
	// printf("g_master.trigo.lineO_3d: %f, i: %d\n", g_master.trigo.lineO_3d, i);
}

static float	ft_distance(float ry, float py, float rx, float px)
{
	return (sqrt((ry - py) * (ry - py) + (rx - px) * (rx - px)));
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
			ry = g_master.trigo.pixel_y;
			rx = g_master.trigo.pixel_x;
			yo = 0;
			xo = g_master.trigo.unit_x_size;
		}
		else if (ra < PI)
		{
			ry = ((int)(g_master.trigo.pixel_y / g_master.trigo.unit_y_size) * g_master.trigo.unit_y_size) - 0.0001;
			rx = ((g_master.trigo.pixel_y - ry) / tan(ra)) + g_master.trigo.pixel_x;
			yo = -g_master.trigo.unit_y_size;
			xo = -yo / tan(ra);
		}
		else
		{
			ry = ((int)(g_master.trigo.pixel_y / g_master.trigo.unit_y_size) * g_master.trigo.unit_y_size) + g_master.trigo.unit_y_size; //- 0.0001; // - 0.0001;//  + 0.0001;
			rx = ((g_master.trigo.pixel_y - ry) / tan(ra)) + g_master.trigo.pixel_x;
			yo = g_master.trigo.unit_y_size;
			xo = -yo / tan(ra);
		}
	int		mx;
	int		my;
	
	mx = (int)(rx / g_master.trigo.unit_x_size);
	my = (int)(ry / g_master.trigo.unit_y_size);
	while (my < g_master.map.last_line && mx < g_master.map.longest_line && my > 0 && mx > 0 && g_master.map.map[my][mx] != '1')
	{
		rx += xo;
		ry += yo;
		mx = (int)(rx / g_master.trigo.unit_x_size);
		my = (int)(ry / g_master.trigo.unit_y_size);
	}
	g_master.trigo.ryh = ry;
	g_master.trigo.rxh = rx;
	return(ft_distance(ry, g_master.trigo.pixel_y, rx, g_master.trigo.pixel_x));
	//return(ft_hit_da_wall(rx, ry, xo, yo));
}

/*** VERTICAL LINE ***/

float	ft_vertical_line(float ra)
{
	float	ry;
	float	rx;
	float	xo;
	float	yo;
	
	if (!tan(ra))
	{
		ry = g_master.trigo.pixel_y;
		rx = g_master.trigo.pixel_x;
		yo = g_master.trigo.unit_x_size;
		xo = 0;
	}
	else if (ra > P2 && ra < P3)
	{
		rx =((int)(g_master.trigo.pixel_x / g_master.trigo.unit_x_size) * g_master.trigo.unit_x_size) - 0.0001;
		//printf("RXVertical 90 - 270: %f\n", rxv);
		ry = ((g_master.trigo.pixel_x - rx) * tan(ra)) + g_master.trigo.pixel_y;
		//printf("RYVertical 90 - 270: %f\n", ryv);
		xo = -g_master.trigo.unit_x_size;
		yo = -xo * tan(ra);
	}
	else
	{
		rx = ((int)(g_master.trigo.pixel_x / g_master.trigo.unit_x_size) * g_master.trigo.unit_x_size) + g_master.trigo.unit_x_size; //- 0.0001; // - 0.0001;//  + 0.0001;
		ry = ((g_master.trigo.pixel_x - rx) * tan(ra)) + g_master.trigo.pixel_y;
		xo = g_master.trigo.unit_x_size;
		yo = -xo * tan(ra);
	}
	int		mx;
	int		my;
	
	mx = (int)(rx / g_master.trigo.unit_x_size);
	my = (int)(ry / g_master.trigo.unit_y_size);
	// printf("g_master.map.last_line: %d\n", g_master.map.last_line);
	// printf("g_master.map.longest_line: %d\n", g_master.map.longest_line);
	while (my < g_master.map.last_line && mx < g_master.map.longest_line && my > 0 && mx > 0 && g_master.map.map[my][mx] != '1')
	{
		rx += xo;
		ry += yo;
		mx = (int)(rx / g_master.trigo.unit_x_size);
		my = (int)(ry / g_master.trigo.unit_y_size);
	}
	g_master.trigo.ryv = ry;
	g_master.trigo.rxv = rx;
	return(ft_distance(ry, g_master.trigo.pixel_y, rx, g_master.trigo.pixel_x));
	//return(ft_hit_da_wall(rx, ry, xo, yo));
}

/******** NIE MA POTRZEBNYCH DANYCH DO WYDRUKOWANIA TEGO!!! **************/
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
// 	delta_x = fabs(rx - g_master.trigo.pixel_x); // chyba zle drukuje, trzeba popracoawc nad delta!!!, moze 2 rozne funkcje dac!!
// 	//printf("deltax: %f\n", delta_x);
// 	// if (sin(g_master.trigo.current_angle) != 0)
// 	// 	c = delta_x / sin(g_master.trigo.current_angle);
// 	step = tan(ra);
// 	x = g_master.trigo.pixel_x;
// 	y = g_master.trigo.pixel_y;
// 	while (i < delta_x)
// 	{
// 		mlx_pixel_put(g_master.window.mlx_p, g_master.window.win_p, x, y, color);
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


void	ft_raycasting(void)
{
	float	dist_H;
	float	dist_V;
	float	dist;
	int		i;
	float	ra;
	float	rest;
	float	width_x;
	int		dir;
	//int		x;

	width_x = 0.0;
	rest = 0.0;
	i = -1;
	ra = g_master.trigo.current_angle + 30 * degree;
	if (ra < 0)
		ra += 2 * PI;
	if (ra > 2*PI)
		ra -= 2 * PI;
	while (++i < g_master.map.window_width)
	{
		dist_H = ft_horizontal_line(ra);
		dist_V = ft_vertical_line(ra);
		if (dist_H < dist_V)
		{
			dist = dist_H;
			dir = 1;
			//ft_print_one_ray_h(g_master.trigo.rxh, g_master.trigo.ryh, ra, 0xFF0000);
		}
		else
		{
			dist = dist_V;
			dir = 0;
			//ft_print_one_ray_h(g_master.trigo.rxv, g_master.trigo.ryv, ra, 0x0000FF);
		}
		ft_create_3d_world(dist, ra, i);
		//printf("i: %d\n", i);
		ft_3d_print_addr(i, dir, ra);
		ra -= degree / (g_master.map.window_width / 60);
		// width_x += g_master.map.window_width / 60; - not sure if needed anymore;
		if (ra < 0)
		ra += 2 * PI;
		if (ra > 2*PI)
		ra -= 2 * PI;
	}
	mlx_put_image_to_window(g_master.window.mlx_p, g_master.window.win_p, g_master.bg.img_instance, 0, 0);
	mlx_put_image_to_window(g_master.window.mlx_p, g_master.window.win_p, g_master.walls.img_instance, 0, 0);
// 	if (g_master.walls.img_instance)
// 	{
// 		printf("hello\n");
		
// 		g_master.walls.img_instance = mlx_new_image(g_master.window.mlx_p, g_master.map.window_width, g_master.map.window_height);
// 		g_master.walls.img_address = mlx_get_data_addr(g_master.walls.img_instance, &g_master.walls.bits_per_pixel, &g_master.walls.line_length, &g_master.walls.endian);
// 	}
}



// float	ft_hit_da_wall(float rx, float ry, float xo, float yo)
// {
// 	int		mx;
// 	int		my;
	
// 	mx = rx / g_master.trigo.unit_x_size;
// 	my = ry / g_master.trigo.unit_y_size;
// 	printf("g_master.map.last_line: %d\n", g_master.map.last_line);
// 	printf("g_master.map.longest_line: %d\n", g_master.map.longest_line);
// 	while (my < g_master.map.last_line && mx < g_master.map.longest_line && my > 0 && mx > 0 && g_master.map.map[my][mx] != '1')
// 	{
// 		rx += xo;
// 		ry += yo;
// 		mx = rx / g_master.trigo.unit_x_size;
// 		my = ry / g_master.trigo.unit_y_size;
// 	}
// 	return(ft_distance(ry, g_master.trigo.pixel_y, rx, g_master.trigo.pixel_x));
// }
