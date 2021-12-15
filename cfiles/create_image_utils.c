/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_image_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psleziak <psleziak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 20:39:28 by psleziak          #+#    #+#             */
/*   Updated: 2021/12/15 20:57:58 by psleziak         ###   ########.fr       */
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
