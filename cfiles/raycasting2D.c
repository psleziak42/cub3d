/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2D.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 22:03:44 by rimartin          #+#    #+#             */
/*   Updated: 2021/12/04 22:47:56 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/cub3d.h"

// static void	ft_print_rays(float dist, float ra, int color)
// {
// 	float 	x;
// 	float	y;
// 	float	i;
// 	//float	c;
// 	// float	delta_x;
// 	float	step_y;
// 	float	step_x;
//     // new_dist = (int)(dist / g_master.trigo.unit_x_size) * g_master.trigo.unit_x_size;
//     // new_dist /= 64;
// 	i = -1;

// 	dist = fabs(dist);
//     printf("dist %f g_master pixel x %f\n", dist, g_master.trigo.pixel_x);
//     // delta_x = fabs(pos - g_master.trigo.pixel_x); // chyba zle drukuje, trzeba popracoawc nad delta!!!, moze 2 rozne funkcje dac!!
// 	//printf("deltax: %f\n", delta_x);
// 	// if (sin(g_master.trigo.current_angle) != 0)
// 	// 	c = delta_x / sin(g_master.trigo.current_angle);
// 	step_y = tan(ra);
//     if (cos(ra) > 0)
//     {
//         step_y *= -1;
//         step_x = 1;
//     }
//     else
//         step_x = -1;
// 	x = g_master.trigo.pixel_x;
// 	y = g_master.trigo.pixel_y;
// 	while (++i < dist)
// 	{
// 		mlx_pixel_put(g_master.window.mlx_p, g_master.window.win_p, x, y, color);
// 		y += step_y;
// 		x += step_x;
// 	}	
// }

// #define NUMBER_OF_RAYS 60
// #define red_color 0x0000FF
// #define blue_color 0xFF0000

// void	ft_raycasting(void)
// {
// 	float	dist_H;
// 	float	dist_V;
// 	float	dist;
// 	int		i;
// 	float	ra;
// 	float	rest;
// 	float	width_x;

// 	width_x = 0.0;
// 	rest = 0.0;
// 	i = -1;
// 	ra = g_master.trigo.current_angle + 30 * degree;
// 	while (++i < NUMBER_OF_RAYS)
// 	{
// 		dist_H = ft_horizontal_line(ra);
// 		dist_V = ft_vertical_line(ra);
// 		if (dist_H < dist_V)
// 		{
// 			dist = dist_H;
// 			ft_print_rays(dist, ra, 0xFF0000);
// 		}
// 		else
// 		{
// 			dist = dist_V;
// 			ft_print_rays(dist, ra, 0x0000FF);
// 		}
// 		//static void	ft_print_one_ray_h(float rx, float ry, float ra, int color)
// 		// ft_create_3d_world(dist, ra, i);
// 		width_x += ((float)g_master.map.window_width / NUMBER_OF_RAYS); 
// 		if (i == 0) // rest = x_width + g_master.map.window_width % 60? 
// 			g_master.trigo.x_width = (int)width_x;
// 		// ft_3d_print_addr(i, (int)width_x);
// 		ra -= degree;
// 		// width_x += g_master.map.window_width / 60; - not sure if needed anymore;
// 		if (ra <= 0)
// 			ra += 2 * PI;
// 		if (ra >= 2*PI)
// 			ra -= 2 * PI;
// 	}
// 	// mlx_put_image_to_window(g_master.window.mlx_p, g_master.window.win_p, g_master.walls.img_instance, 0, 0);
// }

// int	main(int argc, char **argv)
// {
// 	ft_memset(&g_master, 0, sizeof(g_master));
// 	if (argc != 2)
// 		return (-1);
// 	if (!ft_map_parse(argv[1]))
// 	{
// 		printf("Error\n");
// 		ft_free_memory();
// 		return(-1);
// 	}
// 	g_master.window.mlx_p = mlx_init();
// 	g_master.window.win_p = mlx_new_window(g_master.window.mlx_p, g_master.map.window_width, g_master.map.window_height, "dujuivnDUBSTEPbro?");
// 	g_master.walls.img_instance = mlx_new_image(g_master.window.mlx_p, g_master.map.window_width, g_master.map.window_height);
// 	g_master.walls.img_address = mlx_get_data_addr(g_master.walls.img_instance, &g_master.walls.bits_per_pixel, &g_master.walls.line_length, &g_master.walls.endian);
// 	g_master.bg.img_instance = mlx_new_image(g_master.window.mlx_p, g_master.map.window_width, g_master.map.window_height);
// 	g_master.bg.img_address = mlx_get_data_addr(g_master.bg.img_instance, &g_master.bg.bits_per_pixel, &g_master.bg.line_length, &g_master.bg.endian);
// 	ft_printmap_to_window(); //THIS WILL BE FOR MINIMAP EVENTUALLY !!
// 	mlx_hook(g_master.window.win_p, 2, 1L << 0, key_press, NULL);
// 	//print_one_ray();
// 	mlx_loop(g_master.window.mlx_p);
// 	return (0);
// }
