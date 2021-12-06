/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 18:05:28 by psleziak          #+#    #+#             */
/*   Updated: 2021/12/06 23:14:39 by rimartin         ###   ########.fr       */
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
	int		py = (int)g_master.trigo.pixel_y/g_master.trigo.cub_size;
	int		px = (int)g_master.trigo.pixel_x/g_master.trigo.cub_size;
	
	if (key == k_W)
	{
		if_wall = py + SPEED * -sin(g_master.trigo.current_angle);
		printf("y: %d\n", (int)round(if_wall));
		printf("actual pos y: %d\n", py);
		if (g_master.map.map[(int)round(if_wall)][px] != '1')
			g_master.trigo.pixel_y += SPEED * -sin(g_master.trigo.current_angle);
		if_wall = px + SPEED * cos(g_master.trigo.current_angle);
		printf("x: %d\n", (int) round(if_wall));
		printf("acutal pos x: %d, cos %f angle %f\n", px, cos(g_master.trigo.current_angle), g_master.trigo.current_angle);
		if (g_master.map.map[py][(int)round(if_wall)] != '1')
			g_master.trigo.pixel_x += SPEED * cos(g_master.trigo.current_angle);
	}
	else if (key == k_S)
	{
		if_wall = g_master.trigo.pixel_y + SPEED * sin(g_master.trigo.current_angle);
		if (g_master.map.map[(int)if_wall/g_master.trigo.cub_size][(int)g_master.trigo.pixel_x/g_master.trigo.cub_size] != '1')
			g_master.trigo.pixel_y += SPEED * sin(g_master.trigo.current_angle);
		if_wall = g_master.trigo.pixel_x + SPEED * -cos(g_master.trigo.current_angle);
		if (g_master.map.map[(int)g_master.trigo.pixel_y/g_master.trigo.cub_size][(int)if_wall/g_master.trigo.cub_size] != '1')
			g_master.trigo.pixel_x += SPEED * -cos(g_master.trigo.current_angle);
	}
	else if (key == k_A)
	{
		g_master.trigo.current_angle += SPEED * degree;
		if (g_master.trigo.current_angle + degree >= 2 * PI)
			g_master.trigo.current_angle = 0 + degree;
	}
	else if (key == k_D)
	{
		g_master.trigo.current_angle -= SPEED *degree;
		if (g_master.trigo.current_angle - degree < 0)
			g_master.trigo.current_angle = 2 * PI - degree;
	}
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
