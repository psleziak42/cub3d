/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psleziak <psleziak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 19:44:16 by psleziak          #+#    #+#             */
/*   Updated: 2021/12/10 15:00:50 by psleziak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24| r << 16 | g << 8 | b);
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

void	ft_update_walls(int x, int dir, float ra)
{
	int		y;
	int		new_x;
	int		new_y;
	// int		new_index;

	y = -1;
	// new_y = -1;
	// printf("x: %d\n", x);
	new_x = (x%4 + 4 - x%4) * x;
	// printf("new_x: %d\n", new_x);
	// printf("new_x%%64: %d\n", new_x%64);
	// sleep(1);
	// int z = -1;
	// while (1)
	// {
	// 	printf("%d\n", g_master.textures[N].img_address[++z]);
	// 	printf("%d\n", z);
	// 	sleep(10);
	// }
	// printf("z: %d\n", z);
	// sleep(100);
	new_y = 0;
	// printf("%d\n", strlen(g_master.textures[N].img_address));
	int z;
	int ź;

	z = -1;
	ź = -1;
	// while (++z < 255)
	// {
	// 	sleep(5);
	// 	printf("-------------------------------------\n");
	// 	ź = -1;
	// 	while (++ź < g_master.textures[N].line_length)
	// 	printf("z: %d, g_master.textures[N].img_address: %s\n", z, g_master.textures[N].img_address);
	// }
	// sleep(100);
	while (++y < g_master.map.window_height)
	{
		if (y > g_master.trigo.lineO_3d && y < (g_master.trigo.lineO_3d + g_master.trigo.lineH_3d))
		{
			if (dir == 1 && ra > 0 && ra < PI) // N
			{
				//printf("line_length: %c\n", g_master.textures[N].img_address[y]);
				//printf("new_y%%64 * TEXT + new_x%%TEXT: %d\n", new_y%64 * TEXT + new_x%TEXT);
				//usleep(100);
				// sleep(2);
				// new_index = -1;
				//++new_y; // y is not 0 when gets here!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				// while (++new_index < g_master.trigo.lineH_3d / TEXT)
				// {
					//printf("hello\n");
					// printf("y: %d, x: %d, positon: %d\n", y, x, (y%64 * TEXT + new_x%TEXT));
					// //sleep(10);
					// printf("R? %d\n", g_master.textures[N].img_address[y%64 * TEXT + new_x%TEXT]);
					// printf("G? %d\n", g_master.textures[N].img_address[y%64 * TEXT + (new_x+1)%TEXT]);
					// printf("B? %d\n", g_master.textures[N].img_address[y%64 * TEXT + (new_x+2)%TEXT]);
					// printf("T? %d\n", g_master.textures[N].img_address[y%64 * TEXT + (new_x+3)%TEXT]);
					// usleep(10000);
					//prints upside down, only 16 pixels;
				//printf("g_master.textures[N].img_address[%d + %d]: %d\n", new_y%1024, x%1024, g_master.textures[N].img_address[new_y%1024 + x%1024]);
				// printf("g_master.textures[N].img_address[new_y + x * TEXT]: %lu\n", sizeof(g_master.textures[N].img_address));
				// sleep(10);
				// printf("pos %d\n", new_y%64 * TEXT * 4 + (new_x+0)%64 * 4);
				// sleep(1);
				// printf("new_x: %d\n, new_y: %d\n", new_x, new_y);
				my_mlx_pixel_put(&g_master.walls, x, y, 
								create_trgb(0, 0, 255, 0)); // to robi 64 / 64 - size of.
					// printf("color: %x\n", create_trgb(
					// 	0, g_master.textures[N].img_address[y%256 * TEXT + (new_x+0)%TEXT], 
					// 		g_master.textures[N].img_address[y%256 * TEXT + (new_x+1)%TEXT], 
					// 		g_master.textures[N].img_address[y%256 * TEXT + (new_x+2)%TEXT]));
					// y++;
				// }
				new_y++;
			}
			if (dir == 0 && (ra < PI/2 || ra > P3)) // E
				my_mlx_pixel_put(&g_master.walls, x, y, 0x00FF0000);
			if (dir == 1 && ra >= PI && ra < 2 * PI) // S
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
