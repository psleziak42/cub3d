/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psleziak <psleziak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 20:11:16 by psleziak          #+#    #+#             */
/*   Updated: 2021/11/24 23:47:26 by psleziak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/cub3d.h"

/*
*
* it searches for y but it does too big jumps
* i think it works now!
*/ 


static void	ft_print_one_ray(void)
{
	 float	i;
	// float	dx;
	// float	dy;
	float	step;
	float	x;
	float	y;

	y = g_master.trigo.pixel_y; // player y
	x = g_master.trigo.pixel_x; // player x
	g_master.trigo.wall_y_pixel = g_master.trigo.ray_dist_to_y; 
	g_master.trigo.wall_x_pixel = g_master.trigo.ray_dist_to_x;
	i = 0;
	// if (g_master.trigo.wall_y_pixel > g_master.trigo.wall_x_pixel) - moze tu cos sie dzieje.
		step = tan(g_master.trigo.current_angle) * 1;
	printf("step: %f\n", step);
	while (i < g_master.trigo.unit_x_size)
	{
		mlx_pixel_put(g_master.window.mlx_p, g_master.window.win_p, x, y, 0xFF0000);
		if (cos(g_master.trigo.current_angle) > 0)
			y -= step;
		else
			y += step;
		if (cos(g_master.trigo.current_angle) < 0)
				x -= 1;
		else
			x += 1;
		i++;
	}
	printf("here\n");
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
}

/*
*	if angle is "on the bottom", 181 - 359 i say that alpha = 360 - angle,
*	otherwise it stay the way it is.
*
*	for 30 it goest o -30;
*	MAYBE SIN/COS COS JEST NIE TAK
*/
// static void	ft_find_da_wall(void)
// {
// 	int		imaginary_map2d_x;
// 	int		imaginary_map2d_y;

// 	imaginary_map2d_x = g_master.trigo.map2d_x;
// 	imaginary_map2d_y = g_master.trigo.map2d_y;
// 	while (g_master.map.map[imaginary_map2d_y][imaginary_map2d_x] != '1')
// 	{
// 		//printf("tutaj\n");
// 		if (fabs(g_master.trigo.ray_dist_to_x) >= fabs(g_master.trigo.ray_dist_to_y)) // sin, cos can give - values
// 		{
// 			printf("imaginary_map2d_y: %d\n", imaginary_map2d_y);
// 			g_master.trigo.ray_dist_to_y = g_master.trigo.unit_y_size * cos(g_master.trigo.current_angle);
// 			imaginary_map2d_y += g_master.trigo.map2d_y_incrementor;
// 		}
// 		else
// 		{
// 			printf("imaginary_map2d_x: %d\n", imaginary_map2d_x);
// 			g_master.trigo.ray_dist_to_x = g_master.trigo.unit_x_size * sin(g_master.trigo.current_angle);
// 			imaginary_map2d_x += g_master.trigo.map2d_x_incrementor;
// 		}
// 	}
// 	g_master.trigo.wall_y_pixel = imaginary_map2d_y * g_master.trigo.unit_y_size;
// 	g_master.trigo.wall_x_pixel = imaginary_map2d_x * g_master.trigo.unit_x_size;
// 	printf("wall_y: %f, wall_x: %f\n", g_master.trigo.wall_y_pixel/32, g_master.trigo.wall_x_pixel/32);
// }

/*
*	SEARCHING FOR ERRORS:
*	it starts with 210* but later goes automatically to 0 - 180 and never croses 180. Y?
*
*	i was changing structure angle back to 2 PI - 180, now I use external variable.
*/
// static void	ft_calculate_X_and_Y_distance_to_grid(void)
// {
// 	if (g_master.trigo.dist_y_to_grid > g_master.trigo.dist_x_to_grid)
// 		g_master.trigo.ray_dist_to_x = fabs(g_master.trigo.unit_y_size / sin(g_master.trigo.current_angle));
// 	else
// 		g_master.trigo.ray_dist_to_y = fabs(g_master.trigo.unit_x_size / sin(g_master.trigo.current_angle));
// }

/*
* I am not sure if this is correct. Before I had:
* if (g_master.trigo.dist_y/x_to_grid > 0) but it is always bigger than zero
*
*
*	HERE MUST BE AN ERROR WITH FINDING PROPER WALL!!
*	it is: -x goest for 90 - 270
*	it is: +y goes for 180 - 0
*	!!!! MOST LIKELY IT IS FIXED NOW !!!!
*/
// static void	ft_set_map_incrementor(void)
// {
// 	if (cos(g_master.trigo.current_angle) > 0)
// 		g_master.trigo.map2d_x_incrementor = 1;
// 	else
// 		g_master.trigo.map2d_x_incrementor = -1;
// 	if (sin(g_master.trigo.current_angle) > 0)
// 		g_master.trigo.map2d_y_incrementor = -1;
// 	else
// 		g_master.trigo.map2d_y_incrementor = 1;
// 	printf("sin: %f, cos: %f\n", sin(g_master.trigo.current_angle), cos(g_master.trigo.current_angle));
// 	printf("inc_y: %d, inc_x: %d\n", g_master.trigo.map2d_y_incrementor, g_master.trigo.map2d_x_incrementor);
// }

/*
* missing to cover edge cases 0 90 180 270
* big y for cos > 0
* small x for sin > 0
*
* BEFORE CHANGE:
* g_master.trigo.current_angle > 0 && g_master.trigo.current_angle <= PI) // sin i cos
* g_master.trigo.dist_y_to_grid = g_master.trigo.offset_y;
*
* IT SEEMS VERY OK SOLUTION WITH COSINUS
*
*
*
* NEW UPDATE: we use value of y to calc distance to X and vaue of x to calc ditane to Y
*/

static void	ft_calculate_initial_offsets_and_distances(void)
{
	g_master.trigo.offset_y = fmod(g_master.trigo.pixel_y, g_master.trigo.unit_y_size);
	g_master.trigo.offset_x = fmod(g_master.trigo.pixel_x, g_master.trigo.unit_x_size);
	printf("g_master.trigo.offset_y: %f\n", g_master.trigo.offset_y);
	printf("g_master.trigo.offset_x: %f\n", g_master.trigo.offset_x);
	if (cos(g_master.trigo.current_angle) > 0)
		g_master.trigo.offset_x = g_master.trigo.unit_x_size - g_master.trigo.offset_x;
	if (sin(g_master.trigo.current_angle) < 0)
		g_master.trigo.offset_y = g_master.trigo.unit_y_size - g_master.trigo.offset_y;
	printf("off_y: %f, off_x: %f\n", g_master.trigo.offset_y, g_master.trigo.offset_x);
	printf("dist_y: %f, dist_x: %f\n", g_master.trigo.dist_y_to_grid, g_master.trigo.dist_x_to_grid);
	g_master.trigo.ray_dist_to_y = g_master.trigo.offset_x / cos(g_master.trigo.current_angle);
	g_master.trigo.ray_dist_to_x = g_master.trigo.offset_y / sin(g_master.trigo.current_angle);
	printf("g_master.trigo.ray_dist_to_y: %f\n", g_master.trigo.ray_dist_to_y);
	printf("g_master.trigo.ray_dist_to_x: %f\n", g_master.trigo.ray_dist_to_x);
	ft_print_one_ray();
}

void	print_one_ray(void)
{
	ft_calculate_initial_offsets_and_distances();
	// //ft_print_one_ray();
	// ft_set_map_incrementor();
	// ft_calculate_X_and_Y_distance_to_grid();
	// ft_find_da_wall();
	// ft_print_one_ray();
}
