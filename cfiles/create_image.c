/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psleziak <psleziak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 19:44:16 by psleziak          #+#    #+#             */
/*   Updated: 2021/12/15 21:05:26 by psleziak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/cub3d.h"

void	ft_create_bg(void)
{
	int			j;
	int			i;

	j = -1;
	while (++j < get_map(0)->win_hei / 2)
	{
		i = -1;
		while (++i < get_map(0)->win_wid)
		{
			my_mlx_pixel_put(&get_img(0)[BG], i, j,
				create_trgb(get_map(0)->c_f[C][2],
					get_map(0)->c_f[C][1], get_map(0)->c_f[C][0], 0));
		}
	}
	while (j < get_map(0)->win_hei)
	{
		i = -1;
		while (++i < get_map(0)->win_wid)
		{
			my_mlx_pixel_put(&get_img(0)[BG], i, j,
				create_trgb(get_map(0)->c_f[F][2],
					get_map(0)->c_f[F][1], get_map(0)->c_f[F][0], 0));
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
				ft_north_wall(trigo, x, y);
			else if (dir == 0 && (ra < PI / 2 || ra > 3 * PI / 2))
				ft_east_wall(trigo, x, y);
			else if (dir == 1 && ra >= PI && ra < 2 * PI)
				ft_south_wall(trigo, x, y);
			else if (dir == 0 && ra > PI / 2 && ra < 3 * PI / 2)
				ft_west_wall(trigo, x, y);
		}
		else
			my_mlx_pixel_put(&get_img(0)[WL], x, y, 0xFF000000);
	}	
}
