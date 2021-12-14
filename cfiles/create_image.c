/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 19:44:16 by psleziak          #+#    #+#             */
/*   Updated: 2021/12/14 19:06:49 by rimartin         ###   ########.fr       */
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

	dst = img->img_address + (y * img->line_len + x * (img->bpp / 8));
	*(int*)dst = color;
}

 // IF ERROR SEARCH HERE FOR ++j - 1;
void	ft_update_bg(void)
{
	int i;
	int j;
	int color;

	j = -1;
	while (++j < get_map(0)->win_hei / 2)
	{
		i = -1;
		while (++i < get_map(0)->win_wid)
		{
			color = create_trgb(get_map(0)->c_f[C][2], 
				get_map(0)->c_f[C][1], get_map(0)->c_f[C][0], 0);
			my_mlx_pixel_put(&get_img(0)[BG], i, j, color);
		}
	}
	while (++j - 1 < get_map(0)->win_hei)
	{
		i = -1;
		while (++i < get_map(0)->win_wid)
		{
			color = create_trgb(get_map(0)->c_f[F][2], 
				get_map(0)->c_f[F][1], get_map(0)->c_f[F][0], 0);
			my_mlx_pixel_put(&get_img(0)[BG], i, j, color);
		}
	}
}

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
**/ 

void	ft_update_walls(int x, int dir, float ra)
{
	int	y;

	y = -1;
	while (++y < get_map(0)->win_hei)
	{
		if (y > get_trigo(0)->line_o_3d && y < (get_trigo(0)->line_o_3d + get_trigo(0)->line_h_3d))
		{
			if (dir == 1 && ra > 0 && ra < PI) // N
				my_mlx_pixel_put(&get_img(0)[WL], x, y, 0x00BF0000);
			else if (dir == 0 && (ra < PI/2 || ra > P3)) // E
				my_mlx_pixel_put(&get_img(0)[WL], x, y, 0x00FF0000);
			else if (dir == 1 && ra >= PI && ra < 2 * PI) // S
				my_mlx_pixel_put(&get_img(0)[WL], x, y, 0x00BF0000);
			else if (dir == 0 && ra > PI/2 && ra < P3) // W
				my_mlx_pixel_put(&get_img(0)[WL], x, y, 0x00FF0000);
		}
		else
			my_mlx_pixel_put(&get_img(0)[WL], x, y, 0xFF000000);
	}	
}

void    ft_3d_print_addr(int x, int dir, float ra)
{
	// ft_update_bg();
	// mlx_put_image_to_window(g_master.window.mlx_p, g_master.window.win_p, get_img(0)[BG].img_instance, 0, 0);
	ft_update_walls(x, dir, ra);
}
