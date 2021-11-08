/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psleziak <psleziak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 18:05:28 by psleziak          #+#    #+#             */
/*   Updated: 2021/11/07 22:27:51 by psleziak         ###   ########.fr       */
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
		master->trigo.current_y_position += 2 * -sin(master->trigo.current_angle);
		master->trigo.current_x_position += 2 * cos(master->trigo.current_angle);
	}
	else if (key == k_S)
	{
		master->trigo.current_y_position += 2 * sin(master->trigo.current_angle);
		master->trigo.current_x_position += 2 * -cos(master->trigo.current_angle);
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
	ft_move_image(master, master->trigo.current_x_position, master->trigo.current_y_position);
	return (0);
}