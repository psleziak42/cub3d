/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psleziak <psleziak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 20:11:16 by psleziak          #+#    #+#             */
/*   Updated: 2021/11/21 01:08:46 by psleziak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/cub3d.h"

static void	ft_print_one_ray(void)
{
	int 	i;
	float	dx;
	float	dy;
	float	step;
	float	x;
	float	y;

	y = g_master.trigo.pixel_y;
	x = g_master.trigo.pixel_x;
	dy = fabs(g_master.trigo.wall_y_pixel - g_master.trigo.pixel_y);
	dx = fabs(g_master.trigo.wall_x_pixel - g_master.trigo.pixel_x);
	if (dy > dx)
		step = dy;
	else
		step = dx;
	dx = dx/step;
	dy = dy/step;
	i = -1;
	while (++i <= step)
	{
		mlx_pixel_put(g_master.window.mlx_p, g_master.window.win_p, x, y, 0xFF0000);
		y += dy;
		x += dx;
	}
}

/*
*	if angle is "on the bottom", 181 - 359 i say that alpha = 360 - angle,
*	otherwise it stay the way it is.
*
*	for 30 it goest o -30;
*	MAYBE SIN/COS COS JEST NIE TAK
*/
static void	ft_find_da_wall(void)
{
	int		imaginary_map2d_x;
	int		imaginary_map2d_y;

	imaginary_map2d_x = g_master.trigo.map2d_x;
	imaginary_map2d_y = g_master.trigo.map2d_y;
	while (g_master.map.map[imaginary_map2d_y][imaginary_map2d_x] != '1')
	{
		printf("tutaj\n");
		if (fabs(g_master.trigo.ray_dist_to_x) >= fabs(g_master.trigo.ray_dist_to_y)) // sin, cos can give - values
		{
			printf("imaginary_map2d_y: %d\n", imaginary_map2d_y);
			g_master.trigo.ray_dist_to_y = g_master.trigo.unit_y_size * cos(g_master.trigo.current_angle);
			imaginary_map2d_y += g_master.trigo.map2d_y_incrementor;
		}
		else
		{
			printf("imaginary_map2d_x: %d\n", imaginary_map2d_x);
			g_master.trigo.ray_dist_to_x = g_master.trigo.unit_x_size * sin(g_master.trigo.current_angle);
			imaginary_map2d_x += g_master.trigo.map2d_x_incrementor;
		}
	}
	g_master.trigo.wall_y_pixel = imaginary_map2d_y * g_master.trigo.unit_y_size;
	g_master.trigo.wall_x_pixel = imaginary_map2d_x * g_master.trigo.unit_x_size;
	printf("wall_y: %f, wall_x: %f\n", g_master.trigo.wall_y_pixel/32, g_master.trigo.wall_x_pixel/32);
}


static void	ft_calculate_X_and_Y_distance_to_grid(void)
{
	if (g_master.trigo.current_angle > PI && g_master.trigo.current_angle < 2 * PI)
		g_master.trigo.current_angle = 2 * PI - g_master.trigo.current_angle;
	printf("angle: %f\n", g_master.trigo.current_angle);
	g_master.trigo.ray_dist_to_y = g_master.trigo.dist_y_to_grid * cos(g_master.trigo.current_angle);
	g_master.trigo.ray_dist_to_x = g_master.trigo.dist_x_to_grid * sin(g_master.trigo.current_angle);
	printf("dist_y: %f, dist_x: %f\n", g_master.trigo.ray_dist_to_y, g_master.trigo.ray_dist_to_x);
}

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
static void	ft_set_map_incrementor(void)
{
	if (g_master.trigo.current_angle > PI/2 && g_master.trigo.current_angle < (3 * PI / 2))
		g_master.trigo.map2d_x_incrementor = -1;
	else
		g_master.trigo.map2d_x_incrementor = 1;
	if (g_master.trigo.current_angle > PI && g_master.trigo.current_angle < 2 * PI)
		g_master.trigo.map2d_y_incrementor = 1;
	else
		g_master.trigo.map2d_y_incrementor = -1;
	printf("sin: %f, cos: %f\n", g_master.trigo.current_angle, g_master.trigo.current_angle);
	printf("inc_y: %d, inc_x: %d\n", g_master.trigo.map2d_y_incrementor, g_master.trigo.map2d_x_incrementor);
}

/*
* missing to cover edge cases 0 90 180 270
*
*/

void	ft_calculate_offset_distans(void)
{
	g_master.trigo.offset_x = remainder(g_master.trigo.pixel_x, g_master.trigo.unit_x_size);
	g_master.trigo.offset_y = remainder(g_master.trigo.pixel_y, g_master.trigo.unit_x_size);
	if (g_master.trigo.current_angle > 0 && g_master.trigo.current_angle < PI)
		g_master.trigo.dist_y_to_grid = g_master.trigo.offset_y;
	else if (g_master.trigo.current_angle < 0 && g_master.trigo.current_angle > PI)
		g_master.trigo.dist_y_to_grid = g_master.trigo.unit_y_size - g_master.trigo.offset_x;
	if (g_master.trigo.current_angle > PI / 2 && g_master.trigo.current_angle < 3 * PI / 2)
		g_master.trigo.dist_x_to_grid = g_master.trigo.offset_x;
	else if (g_master.trigo.current_angle > 3 * PI / 2 && g_master.trigo.current_angle < PI / 2)
		g_master.trigo.dist_x_to_grid = g_master.trigo.unit_x_size - g_master.trigo.offset_x;
}

void	print_one_ray(void)
{
	ft_calculate_offset_distans();
	ft_set_map_incrementor();
	ft_calculate_X_and_Y_distance_to_grid();
	ft_find_da_wall();
	ft_print_one_ray();
}
