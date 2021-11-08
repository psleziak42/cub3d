/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psleziak <psleziak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 20:02:42 by psleziak          #+#    #+#             */
/*   Updated: 2021/11/07 23:56:50 by psleziak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/cub3d.h"

static int ft_top_right(t_master *master)
{
    master->trigo.dist_x_to_grid = master->trigo.unit_x_size - master->trigo.offset_x;
    master->trigo.dist_y_to_grid =  master->trigo.offset_y;
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

static int    ft_direction(t_master *master, int ray_x_pixels, int ray_y_pixels)
{
    int     dir;
    float   angle;

    angle = master->trigo.current_angle;
    master->trigo.offset_x = ray_x_pixels % master->trigo.unit_x_size;
    master->trigo.offset_y = ray_y_pixels % master->trigo.unit_y_size;
    if (angle >= 0 && angle < PI/2)
        dir = ft_top_right(master);
    if (angle >= PI/2 && angle < PI)
        dir = ft_top_left(master);
    if (angle >= PI && angle < 3 * PI/2)
        dir = ft_bottom_left(master);
    if (angle >= 3 * PI/2 && angle < 2 * PI)
        dir = ft_bottom_right(master);
    return (dir);
}

void    ft_what_quarter_of_the_circle(t_master *master, int quarter_circle, int *x, int *y)
{
    static int      i;
    float           ray_x = 0.0;
    float           ray_y = 0.0; // -> 1st call we call both, other calls we call shorter!!!!
    
    if (i == 0)
    {
        ray_x = master->trigo.offset_x/sin(master->trigo.current_angle);
        ray_y = master->trigo.offset_y/cos(master->trigo.current_angle);
    }
    else if (i == 1)
        ray_x = master->trigo.offset_x/sin(master->trigo.current_angle);
    else if (i == 2)
        ray_y = master->trigo.offset_y/cos(master->trigo.current_angle);
    if (quarter_circle == 1)
    {
        if (ray_x < ray_y)
            (*x)--;
        else
            (*y)++;
    }
    if (quarter_circle == 2)
    {
        if (ray_x < ray_y)
            (*x)--;
        else
            (*y)--;
    }
    if (quarter_circle == 3)
    {
        if (ray_x < ray_y)
            (*x)++;
        else
            (*y)--;
    }
    if (quarter_circle == 4)
    {
        if (ray_x < ray_y)
            (*x)++;
        else
            (*y)++;
    }
    if (ray_x < ray_y)
        i = 1;
    else
        i = 2;
}

void    print_one_ray(t_master *master, int x, int y)
{
    int     quarter_circle;
    int     ray_x_pixels;
    int     ray_y_pixels;

    ray_x_pixels = x * master->trigo.unit_x_size; // pixel positon
    ray_y_pixels = y * master->trigo.unit_y_size;
    while (master->map.map[y][x] != '1')
    {
        quarter_circle = ft_direction(master, ray_x_pixels, ray_y_pixels);
        ft_what_quarter_of_the_circle(master, quarter_circle, &x, &y);
        //ft_print_ray;
    }
}