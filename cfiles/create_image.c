/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 19:44:16 by psleziak          #+#    #+#             */
/*   Updated: 2021/12/10 16:16:39 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/cub3d.h"

int	create_trgb(char t, char r, char g, char b)
{
	int color = 0;
	color = (t << 24 | r << 16 | g << 8 | b);
	// printf("t %d, r %d\n", t, r);
	// sleep(1);

	return (color);
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



/*
* new_y isnt %64 because we calculate how many pixels we put to cover all wall line
* we dont want to have more than one image at the same wall (vertically)
* this is why we calculate how man pixels must be printed to cover all lineH
*/

void	ft_update_walls(int x, int dir, float ra)
{
	int		y;
	static int		new_x;
	static int helper;
	static int	counter;
	static int	first_x;
	int			max_size = 64 * 64 * 4;
	int calc = 64;

	y = -1;
	calc = 64 * 4;
	while (++y < g_master.map.window_height)
	{
		// printf("x %d\n", x);
		// new_x = (x%4 + 4 - x%4) * x;
		// printf("new x %d\n", new_x);
		if (y > g_master.trigo.lineO_3d && y < (g_master.trigo.lineO_3d + g_master.trigo.lineH_3d))
		{

			//if (dir == 1 && ra > 0 && ra < PI) // N
				//my_mlx_pixel_put(&g_master.walls, x, y, 0x00FF0000); //g_master.textures[N].img_address[]); // y%64, x= heigth/64
			if (dir == 1 && ra > 0 && ra < PI) // N
			{
				// newx = 289 why??????????????????????????
				// printf("newx: %d\n", new_x);
				// sleep(2);
				if (helper == 0 && counter == 0)
				{
					counter = 0;
					new_x = counter * 4;
					first_x = x;
				}
				helper = 1;
				// new_index = -1;
				// 0-4 + 256   256-280 
				// while (++new_index < g_master.trigo.lineH_3d / TEXT)
				// {
					// printf("first x %d\n", first_x);
					// printf("new x %d\n", new_x);
					// printf("total %d\n", new_x);
					// printf("new index %d\n", new_index);
					// // sleep(2);
					if (new_x >= max_size)
					{
						first_x = x;
						new_x = counter * 4;
						// printf("counter: %d new_x: %d\n", counter, new_x);
						// sleep(3);
					}
					// sleep(3);
					my_mlx_pixel_put(&g_master.walls, x, y, create_trgb(
					0, g_master.textures[S].img_address[new_x + 2], 
						g_master.textures[S].img_address[new_x + 1], g_master.textures[S].img_address[new_x + 0]));
					// printf("color: %x\n", create_trgb(
					// 0, g_master.textures[N].img_address[new_x + 2], 
					// 	g_master.textures[N].img_address[new_x + 1], g_master.textures[N].img_address[new_x + 0]));
					// printf("index %d calc x %d\n", counter, new_x);
					
					// usleep(50000);
					new_x += calc;
					// printf("%d: af new_x: %d\n", counter, new_x);
					
					// new_x += 4;
					// y += 4;
				// }
				
				// printf("size_of image %zu\n", ft_strlen(g_master.textures[N].img_address));
				// sleep(10);
				// printf("%d\n", g_master.textures[N].bits_per_pixel / 8 * g_master.textures[N].line_length);

			}
			if (dir == 0 && (ra < PI/2 || ra > P3)) // E
				my_mlx_pixel_put(&g_master.walls, x, y, 0x0000FF00);
			if (dir == 1 && ra >= PI && ra < 2 * PI) // S
				my_mlx_pixel_put(&g_master.walls, x, y, 0x000000FF);
			else if (dir == 0 && ra > PI/2 && ra < P3) // W
				my_mlx_pixel_put(&g_master.walls, x, y, 0x00F000FF);
			//y -= 1;
			// if North : x % 64 (width), img_width_size / y -> gives us number of pixels we must print of the same color
			// 	color = create_trgb(0, g_master.textures[N].img_address[y * sth + x], g_master.textures[N].img_address[y * sth + x + 1], 
			// 		g_master.textures[N].img_address[y * sth + x + 2], g_master.textures[N].img_address[y * sth + x + 3]);
		}
		else
			my_mlx_pixel_put(&g_master.walls, x, y, 0xFF000000);
	}
	if (helper == 1)
	{
		counter++;
		// sleep(10);
	}

	helper = 0;
	// if (helper != 0)
	// {
	// 	printf("One row is done %d\n", y);
	// 	sleep(3);
	// }
	// if (new_x == 64*64)
	// 	new_x = 0;
}

void    ft_3d_print_addr(int x, int dir, float ra)
{
	// ft_update_bg();
	// mlx_put_image_to_window(g_master.window.mlx_p, g_master.window.win_p, g_master.bg.img_instance, 0, 0);
	ft_update_walls(x, dir, ra);
}
