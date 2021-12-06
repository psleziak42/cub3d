/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 19:44:16 by psleziak          #+#    #+#             */
/*   Updated: 2021/12/06 21:47:24 by rimartin         ###   ########.fr       */
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

// X_width : Largura dos pixeis que vamos desenhar width da janela / Numero de raios

bool	is_inside_wall(int h, int j)
{
	(void)j;
	// printf("j %d lineO %f linO + lineH %f\n", j, g_master.trigo.lineO_3d, g_master.trigo.lineO_3d + g_master.trigo.lineH_3d);
	if (h > g_master.trigo.lineO_3d && h < (g_master.trigo.lineO_3d + g_master.trigo.lineH_3d))
	{
		// printf("j %d\n", j);
		// sleep(2);
		return (true);
	}
	return (false);
}


void	ft_update_walls(int width_for_iteration, float dist)
{
	int		h;
	int		j = 0;
	(void)dist;
	(void)width_for_iteration;
	
	h = -1;
	while (++h < g_master.map.window_height)
	{
		j = g_master.temp;
		// j = width_for_iteration - g_master.trigo.x_width;
		while (j <= (width_for_iteration +  g_master.temp) && j < g_master.map.window_width)
		{
			if (is_inside_wall(h, j))
				my_mlx_pixel_put(&g_master.walls, j, h, 0x00FF0000);
			else
				my_mlx_pixel_put(&g_master.walls, j, h, 0xFF000000);
			j++;
		}
		// printf("j %d\n", g_master.temp);
	}
	// sleep(1);
	g_master.temp += width_for_iteration;
}

void    ft_3d_print_addr(int width_for_iteration, float dist)
{
	ft_update_bg();
	ft_update_walls(width_for_iteration, dist);
	mlx_put_image_to_window(g_master.window.mlx_p, g_master.window.win_p, g_master.bg.img_instance, 0, 0);
}
