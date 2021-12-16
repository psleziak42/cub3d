/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psleziak <psleziak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 20:46:14 by psleziak          #+#    #+#             */
/*   Updated: 2021/12/15 23:20:04 by psleziak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/cub3d.h"

void	ft_create_color(t_color *color, int r, int g, int b)
{
	color->r = r % 255;
	color->g = g % 255;
	color->b = b % 255;
	color->t = 1;
}

void	ft_north_wall(t_trigo *tri, int x, int y)
{
	t_color	c;

	ft_create_color(&c, 85,
		tri->counter / 2, (x ^ y) * log(tri->line_h_3d) + tri->counter);
	my_mlx_pixel_put(&get_img(0)[WL], x, y, c.color);
}

void	ft_east_wall(t_trigo *tri, int x, int y)
{
	t_color	c;

	ft_create_color(&c, (x ^ y) * log(tri->line_h_3d) + tri->counter,
		tri->counter / 2, 100);
	my_mlx_pixel_put(&get_img(0)[WL], x, y, c.color);
}

void	ft_south_wall(t_trigo *tri, int x, int y)
{
	t_color	c;

	ft_create_color(&c, (x ^ y) + tri->counter,
		sqrt(y * x) + tri->counter, 100);
	my_mlx_pixel_put(&get_img(0)[WL], x, y, c.color);
}

void	ft_west_wall(t_trigo *tri, int x, int y)
{
	t_color	c;

	ft_create_color(&c, tri->counter / 2,
		(x ^ y) * log(tri->line_h_3d) + tri->counter, 250);
	my_mlx_pixel_put(&get_img(0)[WL], x, y, c.color);
}
