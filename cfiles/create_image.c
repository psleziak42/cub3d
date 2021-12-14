/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 19:44:16 by psleziak          #+#    #+#             */
/*   Updated: 2021/12/13 16:09:53 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/cub3d.h"

int	create_trgb(char t, char r, char g, char b)
{
	return ((t << 24) + (r << 16) + (g << 8) + b);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color) // znajdz ta funkcje, czemu nie drukuje?
{
	char	*dst;

	dst = img->img_address + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(int*)dst = color;
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
			color = create_trgb(1, g_master.map.c_f[C][0], g_master.map.c_f[C][1], g_master.map.c_f[C][2]);
			my_mlx_pixel_put(&g_master.bg, i, j, color);
		}
	}
	while (j < g_master.map.window_height)
	{
		i = -1;
		while (++i < x)
		{
			color = create_trgb(1, g_master.map.c_f[F][0], g_master.map.c_f[F][1], g_master.map.c_f[F][2]);
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



/*
* new_y isnt %64 because we calculate how many pixels we put to cover all wall line
* we dont want to have more than one image at the same wall (vertically)
* this is why we calculate how man pixels must be printed to cover all lineH
*/

void	do_texture(t_img img, int *x, int *y, int new_x, int *new_y)
{
	static int	helper;
	int	size_per_pixel = g_master.trigo.lineH_3d/TEXT;
	
	if (helper <= 64 * size_per_pixel + 1)
	{
		helper = 0;
	}
	new_x = (helper%4 + 4 - helper%4) * helper / size_per_pixel;
	int	i = 0;
	while (i < size_per_pixel && (*y) < (g_master.trigo.lineO_3d + g_master.trigo.lineH_3d) 
		&& *x < g_master.map.window_width - 5)
	{
		my_mlx_pixel_put(&g_master.walls, *x, *y,
			create_trgb(img.img_address[(*new_y)%64 * TEXT * 4 + (new_x+3)%256] + 1,
				img.img_address[(*new_y)%64 * TEXT * 4 + (new_x+2)%256], 
					img.img_address[(*new_y)%64 * TEXT * 4 + (new_x+1)%256], 
						img.img_address[(*new_y)%64 * TEXT * 4 + (new_x+0)%256]));
		i++;
		(*y)++;
	}
	(*new_y)++;
	if ((*y) <= (g_master.trigo.lineO_3d + g_master.trigo.lineH_3d))
		helper++;
}

void	ft_update_walls(int x, int dir, float ra)
{
	int		y;
	int		new_x;
	int		new_y = 0;
	int		size_per_pixel = g_master.trigo.lineH_3d/TEXT;

	new_x = (x%4 + 4 - x%4) * x / size_per_pixel;
	y = -1;
	while (++y < g_master.map.window_height)
	{
		if (y > g_master.trigo.lineO_3d && y < (g_master.trigo.lineO_3d + g_master.trigo.lineH_3d))
		{
			if (dir == 1 && ra > 0 && ra < PI) // N
				do_texture(g_master.textures[N], &x, &y, new_x, &new_y);
			else if (dir == 0 && (ra < PI/2 || ra > P3)) // E
				my_mlx_pixel_put(&g_master.walls, x, y, 0x00FF0000);
			else if (dir == 1 && ra >= PI && ra < 2 * PI) // S
				my_mlx_pixel_put(&g_master.walls, x, y, 0x0000FF00);
			else if (dir == 0 && ra > PI/2 && ra < P3) // W
				my_mlx_pixel_put(&g_master.walls, x, y, 0x000000FF);
		}
		else
			my_mlx_pixel_put(&g_master.walls, x, y, 0xFF000000);
	}
}

void    ft_3d_print_addr(int x, int dir, float ra)
{
	// ft_update_bg();
	// mlx_put_image_to_window(g_master.window.mlx_p, g_master.window.win_p, g_master.bg.img_instance, 0, 0);
	ft_update_walls(x, dir, ra);
}
