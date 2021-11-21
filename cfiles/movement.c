/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psleziak <psleziak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 18:05:28 by psleziak          #+#    #+#             */
/*   Updated: 2021/11/21 00:19:47 by psleziak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/cub3d.h"

static void	ft_move_image(int x, int y)
{
	g_master.img.img_file = "extras/textures/player.xpm";
	g_master.img.img_instance = mlx_xpm_file_to_image(g_master.window.mlx_p, g_master.img.img_file, &g_master.img.img_width, &g_master.img.img_heigth);
	mlx_put_image_to_window(g_master.window.mlx_p, g_master.window.win_p, g_master.img.img_instance, x, y);
}

int	key_press(int key)
{
	if (key == k_W)
	{
		g_master.trigo.pixel_y += 2 * -sin(g_master.trigo.current_angle);
		g_master.trigo.pixel_x += 2 * cos(g_master.trigo.current_angle);
	}
	else if (key == k_S)
	{
		g_master.trigo.pixel_y += 2 * sin(g_master.trigo.current_angle);
		g_master.trigo.pixel_x += 2 * -cos(g_master.trigo.current_angle);
	}
	else if (key == k_A)
	{
		g_master.trigo.current_angle += degree;
		if (g_master.trigo.current_angle + degree >= 2 * PI)
			g_master.trigo.current_angle = 0;
	}
	else if (key == k_D)
	{
		g_master.trigo.current_angle -= degree;
		if (g_master.trigo.current_angle - degree <= 0)
			g_master.trigo.current_angle = 2 * PI;
	}
	printf("angle: %f\n", g_master.trigo.current_angle);
	printf("x: %f, y: %f\n", g_master.trigo.pixel_x, g_master.trigo.pixel_y);
	ft_move_image(g_master.trigo.pixel_x, g_master.trigo.pixel_y);
	print_one_ray();
	return (0);
}
