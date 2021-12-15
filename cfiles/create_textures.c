/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psleziak <psleziak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 20:46:14 by psleziak          #+#    #+#             */
/*   Updated: 2021/12/15 21:28:30 by psleziak         ###   ########.fr       */
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

void	ft_north_wall(t_trigo *trigo, int x, int y)
{
	t_color	color;

	ft_create_color(&color, x, y - x, trigo->px_y);
	my_mlx_pixel_put(&get_img(0)[WL], x, y, color.color);
}

void	ft_east_wall(t_trigo *trigo, int x, int y)
{
	t_color	color;

	ft_create_color(&color, x ^ y, y * x, 1 / (y * x) + trigo->px_x);
	my_mlx_pixel_put(&get_img(0)[WL], x, y, color.color);
}

void	ft_south_wall(t_trigo *trigo, int x, int y)
{
	t_color	color;

	(void)trigo;
	ft_create_color(&color, x ^ y, sqrt(y * x), y * x);
	my_mlx_pixel_put(&get_img(0)[WL], x, y, color.color);
}

void	ft_west_wall(t_trigo *trigo, int x, int y)
{
	t_color	color;

	ft_create_color(&color, x + y, x - y, trigo->px_y);
	my_mlx_pixel_put(&get_img(0)[WL], x, y, color.color);
}
