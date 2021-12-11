/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psleziak <psleziak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 19:44:16 by psleziak          #+#    #+#             */
/*   Updated: 2021/12/11 15:09:49 by psleziak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/cub3d.h"

/**
 * Because on our image the colors are stored in bgrt, I have changed the order here to reflect it.
 * On the function "ft_update_walls" we are passing colors in the order bgrt
 * But here we must create it in trgb because computer reads it its way
 * We are adding +1 to transparency bit because it seems like without it computer 
 * does not see any value there and will move r in place of t g in place of r and b in place of g
 * 
 * That is the best way i can explain i guess.
 **/

int	create_trgb(int b, int g, int r, int t)
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
			color = create_trgb(g_master.map.c_f[C][2], g_master.map.c_f[C][1], g_master.map.c_f[C][0], 0);
			my_mlx_pixel_put(&g_master.bg, i, j, color);
		}
	}
	while (j < g_master.map.window_height)
	{
		i = -1;
		while (++i < x)
		{
			color = create_trgb(g_master.map.c_f[F][2], g_master.map.c_f[F][1], g_master.map.c_f[F][0], 0);
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



/** Endian 0 - means less significant byte goes first (int this case Blue)
* Color is given in hexa, 0x12345678, less significant byte is the last one. Y?
*
* Every pixel has 4 bytes, last byte max value is 256, 2nd last max is 65281, etc.
* Hence "12" value will be the biggest among all.
*
* So: Endian 0 =  Pixels in the image with are stored in the manner of GBRT.
* From the lowest to the highest
*
* BUT: the screen's endian is 1 that means it displays in TRGB so we must "reverse it".
* This is done with a functon "color" that puts Transparency as hights and Blue as lowest.
* 
* If the image has the same endian as the screen then colors stored inside it
* corresponds to the image color set.
*
*/ 


void	ft_update_walls(int x, int dir, float ra)
{
	int				y;
	int				new_x;
	int				new_y;
	int				pixel_index;
	float			pixel_offset;
	float			pixel_minus_offset;

	y = -1;
	pixel_index = -1;
	new_y = 0;
	new_x = (x%4 + 4 - x%4) * x;
	pixel_offset = 0; //g_master.trigo.lineH_3d / TEXT;
	pixel_minus_offset = 0;
	while (++y < g_master.map.window_height)
	{
		pixel_offset += g_master.trigo.lineH_3d / TEXT;
		pixel_index = -1;
		if (y > g_master.trigo.lineO_3d && y < (g_master.trigo.lineO_3d + g_master.trigo.lineH_3d))
		{
			if (dir == 1 && ra > 0 && ra < PI) // N
			{
				// new_x = (new_x%4 + 4 - new_x%4) * new_x;
				//printf("pixel_offset - pixel_minus offset: %d", (int)(pixel_offset - pixel_minus_offset));
				//sleep(3);
				while (++pixel_index < (int)(pixel_offset - pixel_minus_offset))
				{
					my_mlx_pixel_put(&g_master.walls, x, y,
						create_trgb(g_master.textures[N].img_address[new_y%64 * TEXT * 4 + (new_x+0)%256], 
										g_master.textures[N].img_address[new_y%64 * TEXT * 4 + (new_x+1)%256], 
											g_master.textures[N].img_address[new_y%64 * TEXT * 4 + (new_x+2)%256], 
												g_master.textures[N].img_address[new_y%64 * TEXT * 4 + (new_x+3)%256] + 1));
					y++;
				}
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
		pixel_minus_offset += (g_master.trigo.lineH_3d / TEXT);
		// printf("pixel_minus_offset: %f\n", pixel_minus_offset);
		// sleep(10);
	}	
	// if (new_x > 265)
	// 	new_x = 0;
	// else	
		// new_x++;
}

void    ft_3d_print_addr(int x, int dir, float ra)
{
	// ft_update_bg();
	// mlx_put_image_to_window(g_master.window.mlx_p, g_master.window.win_p, g_master.bg.img_instance, 0, 0);
	ft_update_walls(x, dir, ra);
}
