/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 18:05:28 by psleziak          #+#    #+#             */
/*   Updated: 2021/12/04 19:42:37 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/cub3d.h"

static void	ft_move_player(int x, int y)
{
	g_master.t_s_map.img_file = "extras/textures/player.xpm";
	g_master.t_s_map.img_instance = mlx_xpm_file_to_image(g_master.window.mlx_p, g_master.t_s_map.img_file, &g_master.t_s_map.img_width, &g_master.t_s_map.img_heigth);
	mlx_put_image_to_window(g_master.window.mlx_p, g_master.window.win_p, g_master.t_s_map.img_instance, x, y);
}

void	ft_update_position(int key)
{
	float	if_wall;
	if (key == k_W)
	{
		if_wall = g_master.trigo.pixel_y + 10 * -sin(g_master.trigo.current_angle);
		printf("(int)g_master.trigo.pixel_y: %d\n, (int)if_wall: %df\n", (int)g_master.trigo.pixel_y/32, (int)if_wall/32);
		printf("hello\n\n");
		if (g_master.map.map[(int)if_wall/32][(int)g_master.trigo.pixel_x/32] != '1')
			g_master.trigo.pixel_y += 10 * -sin(g_master.trigo.current_angle);
		if_wall = g_master.trigo.pixel_x + 10 * cos(g_master.trigo.current_angle);
		if (g_master.map.map[(int)g_master.trigo.pixel_y/32][(int)if_wall/32] != '1')
			g_master.trigo.pixel_x += 10 * cos(g_master.trigo.current_angle);
	}
	else if (key == k_S)
	{
		if_wall = g_master.trigo.pixel_y + 10 * sin(g_master.trigo.current_angle);
		if (g_master.map.map[(int)if_wall/32][(int)g_master.trigo.pixel_x/32] != '1')
			g_master.trigo.pixel_y += 10 * sin(g_master.trigo.current_angle);
		if_wall = g_master.trigo.pixel_x + 10 * -cos(g_master.trigo.current_angle);
		if (g_master.map.map[(int)g_master.trigo.pixel_y/32][(int)if_wall/32] != '1')
			g_master.trigo.pixel_x += 10 * -cos(g_master.trigo.current_angle);
	}
	else if (key == k_A)
	{
		g_master.trigo.current_angle += 10 * degree;
		if (g_master.trigo.current_angle + degree >= 2 * PI)
			g_master.trigo.current_angle = 0 + degree;
	}
	else if (key == k_D)
	{
		g_master.trigo.current_angle -= 10 *degree;
		if (g_master.trigo.current_angle - degree < 0)
			g_master.trigo.current_angle = 2 * PI - degree;
	}
	// printf("angle: %f\n", g_master.trigo.current_angle);
	// printf("x: %f, y: %f\n", g_master.trigo.pixel_x, g_master.trigo.pixel_y);
}


int	key_press(int key)
{
	ft_update_position(key);
	//ft_printmap_to_window(); //MINIMAP;
	ft_move_player(g_master.trigo.pixel_x, g_master.trigo.pixel_y); //MINIMAP
	ft_raycasting();
	/*destroy image*/
	//ft_3d_print_addr();
	/*image to window*/
	return (0);
}
