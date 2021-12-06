/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 19:44:16 by psleziak          #+#    #+#             */
/*   Updated: 2021/12/04 23:18:49 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color) // znajdz ta funkcje, czemu nie drukuje?
{
	char	*dst;

	dst = img->img_address + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	ft_update_bg(void)
{
	int y;
	int x;
	int i;
	int j;
	int color;

	y = g_master.map.window_height / 2;
	x = g_master.map.window_width;
	j = -1;
	// printf("RED: %d, GREEN: %d, BLUE: %d\n", g_master.map.CR, g_master.map.CG, g_master.map.CB);
	while (++j < y)
	{
		i = -1;
		while (++i < x)
		{
			color = create_trgb(0, g_master.map.CR, g_master.map.CG, g_master.map.CB);
			my_mlx_pixel_put(&g_master.bg, i, j, color);
		}
	}
	while (j < g_master.map.window_height)
	{
		i = -1;
		while (++i < x)
		{
			color = create_trgb(0, g_master.map.FR, g_master.map.FG, g_master.map.FB);
			my_mlx_pixel_put(&g_master.bg, i, j, color);
		}
		j++;
	}
}

	//j = width_x - g_master.map.window_width / 60;
// 	while (++i < g_master.map.window_height)
// 	{
// 		printf("j: %d\n", j);
// 		while (j < width_x)
// 		{
// 			printf("j: %d\n", j);
// 			if (i > lineO && i < lineO + lineH)
// 				mlx_pixel_put(g_master.window.mlx_p, g_master.window.win_p, j, i, 0xFF0000);
// 			else
// 				mlx_pixel_put(g_master.window.mlx_p, g_master.window.win_p, j, i, 0x00FF00);
// 			j++;
// 		}
// 		j = width_x - g_master.map.window_width / 60;

void	ft_update_walls(int x_width)
{
	int		y;
	int		j;
// cos tu jest zle drukowane. pewnie musi byc drukowane po y caly czas. NIE MAM GLEBII!
	//x_width = (int)x_width;
	// printf("g_master.trigo.cub_size: %f\n", g_master.trigo.cub_size);
	// printf("g_master.trigo.lineO_3d: %f\n", g_master.trigo.lineO_3d);
	// printf("g_master.trigo.lineH_3d: %f\n", g_master.trigo.lineH_3d);
	y = -1;
	while (++y < g_master.map.window_height)
	{
		j = x_width - g_master.trigo.x_width;
		while (j <= x_width && j < 256)
		{
			//printf("j: %d\n", j);
			if (y > g_master.trigo.lineO_3d && y < (g_master.trigo.lineO_3d + g_master.trigo.lineH_3d))
				my_mlx_pixel_put(&g_master.walls, j, y, 0x00FF0000);
			else
				my_mlx_pixel_put(&g_master.walls, j, y, 0xFF000000);
			j++;
		}
	}		
}

void    ft_3d_print_addr(int width_x)
{
	ft_update_bg();
	ft_update_walls(width_x);
	mlx_put_image_to_window(g_master.window.mlx_p, g_master.window.win_p, g_master.bg.img_instance, 0, 0);
}
