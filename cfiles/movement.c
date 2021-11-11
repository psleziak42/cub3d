/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psleziak <psleziak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 18:05:28 by psleziak          #+#    #+#             */
/*   Updated: 2021/11/10 23:48:16 by psleziak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/cub3d.h"

void	ft_move_image(t_master *master, int x, int y)
{
	master->img.img_file = "extras/textures/player.xpm";
	master->img.img_instance = mlx_xpm_file_to_image(master->window.mlx_p, master->img.img_file, &master->img.img_width, &master->img.img_heigth);
	mlx_put_image_to_window(master->window.mlx_p, master->window.win_p, master->img.img_instance, x, y);
}

int	key_press(int key, t_master *master)
{
	if (key == k_W)
	{
		master->trigo.pixel_y += 2 * -sin(master->trigo.current_angle);
		master->trigo.pixel_x += 2 * cos(master->trigo.current_angle);
	}
	else if (key == k_S)
	{
		master->trigo.pixel_y += 2 * sin(master->trigo.current_angle);
		master->trigo.pixel_x += 2 * -cos(master->trigo.current_angle);
	}
	else if (key == k_A)
	{
		master->trigo.current_angle += degree;
		if (master->trigo.current_angle + degree >= 2 * PI)
			master->trigo.current_angle = 0;
	}
	else if (key == k_D)
	{
		master->trigo.current_angle -= degree;
		if (master->trigo.current_angle - degree <= 0)
			master->trigo.current_angle = 2 * PI;
	}
	printf("angle: %f\n", master->trigo.current_angle);
	printf("x: %f, y: %f\n", master->trigo.pixel_x, master->trigo.pixel_y);
	ft_move_image(master, master->trigo.pixel_x, master->trigo.pixel_y);
	print_one_ray(master, master->trigo.pixel_x, master->trigo.pixel_y);
	return (0);
}
