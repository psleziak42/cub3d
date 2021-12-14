/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psleziak <psleziak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 18:05:28 by psleziak          #+#    #+#             */
/*   Updated: 2021/12/14 00:23:26 by psleziak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/cub3d.h"

// static void	ft_move_player(int x, int y)
// {
// 	g_master.t_s_map.img_file = "extras/textures/player.xpm";
// 	g_master.t_s_map.img_instance = mlx_xpm_file_to_image(g_master.window.mlx_p, g_master.t_s_map.img_file, &g_master.t_s_map.img_width, &g_master.t_s_map.img_heigth);
// 	mlx_put_image_to_window(g_master.window.mlx_p, g_master.window.win_p, g_master.t_s_map.img_instance, x, y);
// }

void	ft_forward(void)
{
	float	if_wall;
	
	if_wall = get_trigo(0)->px_y + SPEED * -sin(get_trigo(0)->angle);
	if (get_map(0)->map[(int)(if_wall/get_trigo(0)->unit_y_size)][(int)(get_trigo(0)->px_x/get_trigo(0)->unit_x_size)] != '1') // tu x na y
		get_trigo(0)->px_y += SPEED * -sin(get_trigo(0)->angle);
	if_wall = get_trigo(0)->px_x + SPEED * cos(get_trigo(0)->angle);
	if (get_map(0)->map[(int)(get_trigo(0)->px_y/get_trigo(0)->unit_y_size)][(int)(if_wall/get_trigo(0)->unit_x_size)] != '1')
		get_trigo(0)->px_x += SPEED * cos(get_trigo(0)->angle);
}

void	ft_backward(void)
{
	float	if_wall;

	if_wall = get_trigo(0)->px_y + SPEED * sin(get_trigo(0)->angle);
	if (get_map(0)->map[(int)(if_wall/get_trigo(0)->unit_y_size)][(int)(get_trigo(0)->px_x/get_trigo(0)->unit_x_size)] != '1') // tu x na 
		get_trigo(0)->px_y += SPEED * sin(get_trigo(0)->angle);
	if_wall = get_trigo(0)->px_x + SPEED * -cos(get_trigo(0)->angle);
	if (get_map(0)->map[(int)(get_trigo(0)->px_y/get_trigo(0)->unit_y_size)][(int)(if_wall/get_trigo(0)->unit_x_size)] != '1')
		get_trigo(0)->px_x += SPEED * -cos(get_trigo(0)->angle);
}

void	ft_left(void)
{
	get_trigo(0)->angle += ROT * degree;
	if (get_trigo(0)->angle + degree >= 2 * PI)
		get_trigo(0)->angle = 0 + degree;
}

void	ft_right(void)
{
	get_trigo(0)->angle -= ROT *degree;
	if (get_trigo(0)->angle - degree < 0)
		get_trigo(0)->angle = 2 * PI - degree;
}

void	ft_update_position(int key)
{
	if (key == k_W)
		ft_forward();
	else if (key == k_S)
		ft_backward();
	else if (key == k_A || key == ARR_L)
		ft_left();
	else if (key == k_D || key == ARR_R)
		ft_right();
	if (key == ESC)
	{
		mlx_destroy_image(get_win(0)->mlx_p, get_win(0)->mlx_p);
		exit (1);
	}	
	
}


int	key_press(int key)
{
	ft_update_position(key);
	//ft_printmap_to_window(); //MINIMAP;
	//ft_move_player(get_trigo(0)->px_x, get_trigo(0)->px_y); //MINIMAP
	ft_raycasting();
	mlx_put_image_to_window(get_win(0)->mlx_p, get_win(0)->win_p, get_img(0)[BG].img_inst, 0, 0);
	mlx_put_image_to_window(get_win(0)->mlx_p, get_win(0)->win_p, get_img(0)[WL].img_inst, 0, 0);
	/*destroy image*/
	//ft_3d_print_addr();
	/*image to window*/
	return (0);
}
