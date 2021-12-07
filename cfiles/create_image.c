/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psleziak <psleziak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 19:44:16 by psleziak          #+#    #+#             */
/*   Updated: 2021/12/07 22:32:56 by psleziak         ###   ########.fr       */
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
	//printf("RED: %d, GREEN: %d, BLUE: %d\n", g_master.map.CR, g_master.map.CG, g_master.map.CB);
	while (++j < y)
	{
		i = -1;
		while (++i < x)
		{
			color = create_trgb(0, g_master.map.c_f[C][0], g_master.map.c_f[C][1], g_master.map.c_f[C][2]);
			my_mlx_pixel_put(&g_master.bg, i, j, color);
		}
	}
	while (j < g_master.map.window_height)
	{
		i = -1;
		while (++i < x)
		{
			color = create_trgb(0, g_master.map.c_f[F][0], g_master.map.c_f[F][1], g_master.map.c_f[F][2]);
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

void	ft_update_walls(int x, int x_width, int dir, float ra)
{
	int		y;
	int		j;
// cos tu jest zle drukowane. pewnie musi byc drukowane po y caly czas. NIE MAM GLEBII!
	y = -1;
	//x_width = (int)x_width;
	x = -1;
	
	// printf("g_master.trigo.cub_size: %f\n", g_master.trigo.cub_size);
	// printf("g_master.trigo.lineO_3d: %f\n", g_master.trigo.lineO_3d);
	// printf("g_master.trigo.lineH_3d: %f\n", g_master.trigo.lineH_3d);
	while (++y < g_master.map.window_height)
	{
		while (++x < g_master.map.window_width)
			my_mlx_pixel_put(&g_master.walls, x, y, 0x00000000);
	}
	y = -1;
	while (++y < g_master.map.window_height)
	{
		j = x_width - g_master.trigo.x_width;
		while (j <= x_width && j < g_master.map.window_width)
		{
			//printf("j: %d\n", j);
			if (y > g_master.trigo.lineO_3d && y < (g_master.trigo.lineO_3d + g_master.trigo.lineH_3d))
			{
				if (dir == 1 && ra > 0 && ra < PI) // N
					my_mlx_pixel_put(&g_master.walls, j, y, 0x00FF0000); //g_master.textures[N].img_address[]); // y%64, x= heigth/64
				if (dir == 0 && (ra < PI/2 || ra > P3)) // E
					my_mlx_pixel_put(&g_master.walls, j, y, 0x0000FF00);
				if (dir == 1 && ra >= PI && ra < 2 * PI) // S
					my_mlx_pixel_put(&g_master.walls, j, y, 0x000000FF);
				else if (dir == 0 && ra > PI/2 && ra < P3) // W
					my_mlx_pixel_put(&g_master.walls, j, y, 0x00F000FF);
			}
			else
				my_mlx_pixel_put(&g_master.walls, j, y, 0xFF000000);
			j++;
		}
	}		
}

void    ft_3d_print_addr(int x, int width_x, int dir, float ra)
{
	// ft_update_bg();
	// mlx_put_image_to_window(g_master.window.mlx_p, g_master.window.win_p, g_master.bg.img_instance, 0, 0);
	ft_update_walls(x, width_x, dir, ra);
}
