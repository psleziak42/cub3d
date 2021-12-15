/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psleziak <psleziak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 19:44:16 by psleziak          #+#    #+#             */
/*   Updated: 2021/12/15 00:18:25 by psleziak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/cub3d.h"

/**
 * Because on our image the colors are stored in bgrt, I have changed the order
 * to reflect it.
 * On the function "ft_update_walls" we are passing colors in the order bgrt
 * But here we must create it in trgb because computer reads it its way
 * We are adding +1 to transparency bit because it seems like without it 
 * computer does not see any value there 
 * and will move r in place of t g in place of r and b in place of g
 * 
 * That is the best way i can explain i guess.
 **/

int	create_trgb(int b, int g, int r, int t)
{
	return ((t << 24) + (r << 16) + (g << 8) + b);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->img_address + (y * img->line_len + x * (img->bpp / 8));
	*(int *)dst = color;
}

void	ft_update_bg(void)
{
	static int	j;
	int			i;
	int			color;

	while (j++ < get_map(0)->win_hei / 2)
	{
		i = -1;
		while (++i < get_map(0)->win_wid)
		{
			color = create_trgb(get_map(0)->c_f[C][2],
					get_map(0)->c_f[C][1], get_map(0)->c_f[C][0], 0);
			my_mlx_pixel_put(&get_img(0)[BG], i, j, color);
		}
	}
	while (j < get_map(0)->win_hei)
	{
		i = -1;
		while (++i < get_map(0)->win_wid)
		{
			color = create_trgb(get_map(0)->c_f[F][2],
					get_map(0)->c_f[F][1], get_map(0)->c_f[F][0], 0);
			my_mlx_pixel_put(&get_img(0)[BG], i, j, color);
		}
		j++;
	}
}

/** Endian 0 - means less significant byte goes first (int this case Blue)
* Color is given in hexa, 0x12345678, less significant byte is the last one. Y?
*
* Every pixel has 4 bytes, last byte max value is 256, 2nd last max is 65281etc.
* Hence "12" value will be the biggest among all.
*
* So: Endian 0 =  Pixels in the image with are stored in the manner of GBRT.
* From the lowest to the highest
*
* BUT: the screen's endian is 1 that means it displays in TRGB so we must 
* "reverse it".
* This is done with a functon "color" that puts Transparency as hights and Blue 
* as lowest.
* 
* If the image has the same endian as the screen then colors stored inside it
* corresponds to the image color set.
*
**/

void	ft_update_walls(t_trigo *trigo, int x, int dir, float ra)
{
	int	y;

	y = -1;
	while (++y < get_map(0)->win_hei)
	{
		if (y > trigo->line_o_3d && y < (trigo->line_o_3d + trigo->line_h_3d))
		{
			if (dir == 1 && ra > 0 && ra < PI)
				my_mlx_pixel_put(&get_img(0)[WL], x, y, 0x00BF0000);
			else if (dir == 0 && (ra < PI / 2 || ra > P3))
				my_mlx_pixel_put(&get_img(0)[WL], x, y, 0x00FF0000);
			else if (dir == 1 && ra >= PI && ra < 2 * PI)
				my_mlx_pixel_put(&get_img(0)[WL], x, y, 0x00BF0000);
			else if (dir == 0 && ra > PI / 2 && ra < P3)
				my_mlx_pixel_put(&get_img(0)[WL], x, y, 0x00FF0000);
		}
		else
			my_mlx_pixel_put(&get_img(0)[WL], x, y, 0xFF000000);
	}	
}
