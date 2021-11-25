/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_forward.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psleziak <psleziak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 20:11:16 by psleziak          #+#    #+#             */
/*   Updated: 2021/11/25 01:04:05 by psleziak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/cub3d.h"

	// jesli wiemy ze y jest dluzsze w tamtych obliczeniach to juz bez sensu tu spradzac // 

	// dy = fabs(g_master.trigo.wall_y_pixel - g_master.trigo.pixel_y);
	// dx = fabs(g_master.trigo.wall_x_pixel - g_master.trigo.pixel_x);
	// printf("\n\ng_master.trigo.wall_y_pixel: %f\n", g_master.trigo.wall_y_pixel);
	// printf("g_master.trigo.wall_x_pixel: %f\n", g_master.trigo.wall_x_pixel);
	// printf("dy: %f\n", fabs(g_master.trigo.wall_y_pixel - y));
	// printf("dx: %f\n\n\n", fabs(g_master.trigo.wall_x_pixel - x));
	// if (dy > dx)
	// 	step = dy;
	// else
	// 	step = dx;
	// dx = dx/step;
	// dy = dy/step;
	// i = -1;
	// while (++i <= step)
	// {
	// 	printf("y: %f, x: %f\n", y, x);
	// 	mlx_pixel_put(g_master.window.mlx_p, g_master.window.win_p, x, y, 0xFF0000);
	// 	y -= dy;
	// 	x += dx;
	// }

static void	ft_print_one_ray(void)
{
	float	i;
	// float	dx;
	// float	dy;
	// float	step;
	float	x;
	float	y;
	float	c; // length of the line
	float	slope; // slope of the line, zmiana dla y.

	y = g_master.trigo.pixel_y; // player y
	printf("y: %f\n", y);
	x = g_master.trigo.pixel_x; // player x
	printf("x: %f\n", x);
	printf("g_master.trigo.wall_y_pixel: %f\n", g_master.trigo.wall_y_pixel);
	printf("g_master.trigo.wall_x_pixel: %f\n", g_master.trigo.wall_x_pixel);
	// g_master.trigo.wall_y_pixel = g_master.trigo.ray_dist_to_y; 
	// g_master.trigo.wall_x_pixel = g_master.trigo.ray_dist_to_x;
	c = sqrt((g_master.trigo.wall_y_pixel - y) * (g_master.trigo.wall_y_pixel - y)
				+ (g_master.trigo.wall_x_pixel - x) * (g_master.trigo.wall_x_pixel));
	printf("c: %f\n", c);
	slope = (g_master.trigo.wall_y_pixel - y) / (g_master.trigo.wall_x_pixel - x);
	printf("slope: %f\n", slope);
	i = 0;
	// if (g_master.trigo.wall_y_pixel > g_master.trigo.wall_x_pixel) - moze tu cos sie dzieje.
	// 	step = tan(g_master.trigo.current_angle) * 1;
	// printf("step: %f\n", step);
	while (i < c)
	{
		mlx_pixel_put(g_master.window.mlx_p, g_master.window.win_p, x, y, 0xFF0000);
		y += slope;
		if (cos(g_master.trigo.current_angle) < 0)
				x -= 1;
		else
			x += 1;
		i++;
	}
	printf("here\n");
}
/***
 * zle licze odleglosci. Odleglosc od pozycji do X badz Y na mapie moze byc wieksza niz 1 jednostka.
 * jesli castuje po Y |/| to dla 0 - 90 y = y - 1, ale x = x + y(32)/tgalfa.
 * To jest w pixelach podane wiec trzeba przeliczyc /32 i updatowac X w zaleznosci od tego gdzie sie kratka koczy/
 * strona 1!!
 * **/
static void	ft_find_da_wall(void)
{
	int		imaginary_map2d_x;
	int		imaginary_map2d_y;

	imaginary_map2d_x = g_master.trigo.map2d_x;
	imaginary_map2d_y = g_master.trigo.map2d_y;
	printf("imaginary_map2d_x: %d\n", imaginary_map2d_x);
	printf("imaginary_map2d_y: %d\n", imaginary_map2d_y);
	if (g_master.map.map[imaginary_map2d_y][imaginary_map2d_x] != '1')
	{
		g_master.trigo.ray_dist_to_x = g_master.trigo.offset_y / sin(g_master.trigo.current_angle);
		printf("g_master.trigo.ray_dist_to_x: %f\n", g_master.trigo.ray_dist_to_x);
			if (g_master.trigo.ray_dist_to_x)
				imaginary_map2d_x += g_master.trigo.map2d_x_incrementor;
	}
	if (g_master.map.map[imaginary_map2d_y][imaginary_map2d_x] != '1')
	{
		g_master.trigo.ray_dist_to_y = g_master.trigo.offset_x / cos(g_master.trigo.current_angle);
		printf("g_master.trigo.ray_dist_to_y: %f\n", g_master.trigo.ray_dist_to_y);
			if (g_master.trigo.ray_dist_to_y)
				imaginary_map2d_y += g_master.trigo.map2d_y_incrementor;
	}
	g_master.trigo.wall_y_pixel = imaginary_map2d_y * g_master.trigo.unit_y_size;
	g_master.trigo.wall_x_pixel = imaginary_map2d_x * g_master.trigo.unit_x_size;
	printf("wall_y: %f, wall_x: %f\n", g_master.trigo.wall_y_pixel/32, g_master.trigo.wall_x_pixel/32);
}
	// while (g_master.map.map[imaginary_map2d_y][imaginary_map2d_x] != '1')
	// {
	// 	//printf("tutaj\n");
	// 	if (fabs(g_master.trigo.ray_dist_to_x) >= fabs(g_master.trigo.ray_dist_to_y)) // sin, cos can give - values
	// 	{
	// 		printf("imaginary_map2d_y: %d\n", imaginary_map2d_y);
	// 		g_master.trigo.ray_dist_to_y = g_master.trigo.unit_x_size / cos(g_master.trigo.current_angle); // not sure if it updates the value of the ray or always shoots the same.
	// 		imaginary_map2d_y += g_master.trigo.map2d_y_incrementor;
	// 	}
	// 	else
	// 	{
	// 		printf("imaginary_map2d_x: %d\n", imaginary_map2d_x);
	// 		g_master.trigo.ray_dist_to_x = g_master.trigo.unit_y_size / sin(g_master.trigo.current_angle);
	// 		imaginary_map2d_x += g_master.trigo.map2d_x_incrementor;
	// 	}
	// }

// static void	ft_calculate_X_and_Y_distance_to_grid(void)
// {
// 	if (g_master.trigo.dist_y_to_grid > g_master.trigo.dist_x_to_grid)
// 		g_master.trigo.ray_dist_to_x = fabs(g_master.trigo.unit_y_size / sin(g_master.trigo.current_angle));
// 	else
// 		g_master.trigo.ray_dist_to_y = fabs(g_master.trigo.unit_x_size / sin(g_master.trigo.current_angle));
// }

static void	ft_set_map_incrementor(void)
{
	if (cos(g_master.trigo.current_angle) > 0)
		g_master.trigo.map2d_x_incrementor = 1;
	else
		g_master.trigo.map2d_x_incrementor = -1;
	if (sin(g_master.trigo.current_angle) > 0)
		g_master.trigo.map2d_y_incrementor = -1;
	else
		g_master.trigo.map2d_y_incrementor = 1;
	printf("sin: %f, cos: %f\n", sin(g_master.trigo.current_angle), cos(g_master.trigo.current_angle));
	printf("inc_y: %d, inc_x: %d\n", g_master.trigo.map2d_y_incrementor, g_master.trigo.map2d_x_incrementor);
}

static void	ft_calculate_initial_offsets_and_distances(void) // every next move instead offset x/y we take unit size x/y 
{
	int		imaginary_map2d_x;
	int		imaginary_map2d_y;
	
	imaginary_map2d_x = g_master.trigo.map2d_x;
	imaginary_map2d_y = g_master.trigo.map2d_y;
	g_master.trigo.offset_y = fmod(g_master.trigo.pixel_y, g_master.trigo.unit_y_size);
	g_master.trigo.offset_x = fmod(g_master.trigo.pixel_x, g_master.trigo.unit_x_size);
	if (cos(g_master.trigo.current_angle) > 0)
		g_master.trigo.offset_x = g_master.trigo.unit_x_size - g_master.trigo.offset_x;
	if (sin(g_master.trigo.current_angle) < 0)
		g_master.trigo.offset_y = g_master.trigo.unit_y_size - g_master.trigo.offset_y;
	
	/* Shooting ray to first X and Y grid */
	
	// if (g_master.map.map[imaginary_map2d_y][imaginary_map2d_x] != '1')
	// {
	// 	g_master.trigo.ray_dist_to_x = g_master.trigo.offset_y / sin(g_master.trigo.current_angle);
	// 	if (g_master.trigo.ray_dist_to_x)
	// 		imaginary_map2d_x += g_master.trigo.map2d_y_incrementor;
	// 	g_master.trigo.ray_dist_to_y = g_master.trigo.offset_x / cos(g_master.trigo.current_angle);
	// 	if (g_master.trigo.ray_dist_to_y)
	// 		imaginary_map2d_x += g_master.trigo.map2d_y_incrementor;
	// }
	// printf("g_master.trigo.ray_dist_to_y: %f\n", g_master.trigo.ray_dist_to_y);
	// printf("g_master.trigo.ray_dist_to_x: %f\n", g_master.trigo.ray_dist_to_x);
	//ft_print_one_ray();
}

void	print_one_ray(void)
{
	ft_calculate_initial_offsets_and_distances();
	ft_set_map_incrementor();
	ft_find_da_wall();
	ft_print_one_ray();
	// ft_check_first_square();
	// //ft_print_one_ray();
	// ft_calculate_X_and_Y_distance_to_grid();
}
