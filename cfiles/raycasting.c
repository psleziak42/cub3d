/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psleziak <psleziak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 20:02:42 by psleziak          #+#    #+#             */
/*   Updated: 2021/11/08 23:30:23 by psleziak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/cub3d.h"

static int ft_top_right(t_master *master)
{
    master->trigo.dist_x_to_grid = master->trigo.unit_x_size - master->trigo.offset_x;
    master->trigo.dist_y_to_grid = master->trigo.offset_y;
    return (1);
}

static int ft_top_left(t_master *master)
{
    master->trigo.dist_x_to_grid = master->trigo.offset_x;
    master->trigo.dist_y_to_grid = master->trigo.offset_y;
    return (2);
}

static int ft_bottom_left(t_master *master)
{
    master->trigo.dist_x_to_grid = master->trigo.offset_x;
    master->trigo.dist_y_to_grid = master->trigo.unit_y_size - master->trigo.offset_y;
    return (3);
}

static int ft_bottom_right(t_master *master)
{
    master->trigo.dist_x_to_grid = master->trigo.unit_x_size - master->trigo.offset_x;
    master->trigo.dist_y_to_grid = master->trigo.unit_y_size - master->trigo.offset_y;
    return (4);
}

static int    ft_direction(t_master *master, float pixel_x, float pixel_y)
{
    int     dir;
    float   angle;

    angle = master->trigo.current_angle;
	printf("pixel x: %f, pixel y: %f\n", pixel_x, pixel_y);
	printf("unit_x: %f, unit_y: %f\n", master->trigo.unit_x_size, master->trigo.unit_x_size);
    master->trigo.offset_x = remainder(pixel_x, master->trigo.unit_x_size);
    master->trigo.offset_y = remainder(pixel_y, master->trigo.unit_y_size);
	printf("offsetx: %f, offsety: %f\n", master->trigo.offset_x, master->trigo.offset_y);
    if (angle >= 0 && angle < PI/2)
	{
		printf("angle: %f\n", master->trigo.current_angle);
        dir = ft_top_right(master);
	}
    if (angle >= PI/2 && angle < PI)
        dir = ft_top_left(master);
    if (angle >= PI && angle < 3 * PI/2)
        dir = ft_bottom_left(master);
    if (angle >= 3 * PI/2 && angle < 2 * PI)
        dir = ft_bottom_right(master);
    return (dir);
}

void    ft_what_quarter_of_the_circle(t_master *master, int quarter_circle, int *imaginary_map2d_x, int *imaginary_map2d_y)
{
    static	int      i;
    static	float    ray_x;
    static 	float    ray_y; // -> 1st call we call both, other calls we call shorter!!!!
    
    if (i == 0)
    {
        //ray_x = master->trigo.offset_x/sin(master->trigo.current_angle);
        //ray_y = master->trigo.offset_y/cos(master->trigo.current_angle);
		ray_x = master->trigo.dist_x_to_grid/sin(master->trigo.current_angle);
		ray_y = master->trigo.dist_y_to_grid/cos(master->trigo.current_angle);
    }
    else if (i == 1)
        ray_x = fabs((master->trigo.dist_x_to_grid + master->trigo.unit_x_size)/sin(master->trigo.current_angle));
    else if (i == 2)
        ray_y = fabs((master->trigo.dist_y_to_grid + master->trigo.unit_y_size)/cos(master->trigo.current_angle)); // cos 0!!!
	printf("ray_x %f, ray_y %f, sin %f, cos %f\n", ray_x, ray_y, sin(master->trigo.current_angle), cos(master->trigo.current_angle));
    if (quarter_circle == 1)
    {
        if (ray_x > ray_y)
            (*imaginary_map2d_x)++;
        else
            (*imaginary_map2d_y)--;
    }
    if (quarter_circle == 2)
    {
        if (ray_y > ray_x) 
            (*imaginary_map2d_y)--;
        else
            (*imaginary_map2d_x)--;
    }
    if (quarter_circle == 3)
    {
        if (ray_x > ray_y) // this condition must be validated again. 
            (*imaginary_map2d_x)--;
        else
            (*imaginary_map2d_y)++;
    }
    if (quarter_circle == 4)
    {
        if (ray_x > ray_y)
            (*imaginary_map2d_x)++;
        else
            (*imaginary_map2d_y)++;
    }
    if (ray_x < ray_y)
        i = 1;
    else
        i = 2;
}

void    print_one_ray(t_master *master, float pixel_x, float pixel_y)
{
    int     quarter_circle; // trzeba przekazac 2dx i 2dy oraz pixel_x i pixel_y

    int     imaginary_map2d_x; // imaginary because we do not move a player to uptade his position
    int     imaginary_map2d_y; // we starting from players position and check where the ray should finish!

	imaginary_map2d_x = master->trigo.map2d_x;
	imaginary_map2d_y = master->trigo.map2d_y;
	printf("imaginary_map2d_x: %d, imaginary_map2d_y: %d\n", imaginary_map2d_x, imaginary_map2d_y);
    // ray_x_pixels = master->trigo.current_x_position; // pixel positon
    // ray_y_pixels = master->trigo.current_x_position;
    while (master->map.map[imaginary_map2d_y][imaginary_map2d_x] != '1')
    {
		printf("imaginary_map2d_x: %d, imaginary_map2d_y: %d\n", imaginary_map2d_x, imaginary_map2d_y);
        quarter_circle = ft_direction(master, pixel_x, pixel_y);
        ft_what_quarter_of_the_circle(master, quarter_circle, &imaginary_map2d_x, &imaginary_map2d_y);
        //ft_print_ray;
    }
	printf("imaginary_map2d_x: %d, imaginary_map2d_y: %d\n", imaginary_map2d_x, imaginary_map2d_y);
}
