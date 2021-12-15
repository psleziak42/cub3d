/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 18:05:28 by psleziak          #+#    #+#             */
/*   Updated: 2021/12/15 21:31:32 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/cub3d.h"

void	ft_forward(t_trigo *trigo)
{
	float	if_wall;

	if_wall = trigo->px_y + SPEED * -sin(trigo->angle);
	if (get_map(0)->map[(int)(if_wall / trigo->unit_y_size)]
			[(int)(trigo->px_x / trigo->unit_x_size)] != '1')
		trigo->px_y += SPEED * -sin(trigo->angle);
	if_wall = trigo->px_x + SPEED * cos(trigo->angle);
	if (get_map(0)->map[(int)(trigo->px_y / trigo->unit_y_size)]
			[(int)(if_wall / trigo->unit_x_size)] != '1')
		trigo->px_x += SPEED * cos(trigo->angle);
}

void	ft_backward(t_trigo *trigo)
{
	float	if_wall;

	if_wall = trigo->px_y + SPEED * sin(trigo->angle);
	if (get_map(0)->map[(int)(if_wall / trigo->unit_y_size)]
			[(int)(trigo->px_x / trigo->unit_x_size)] != '1')
		trigo->px_y += SPEED * sin(trigo->angle);
	if_wall = trigo->px_x + SPEED * -cos(trigo->angle);
	if (get_map(0)->map[(int)(trigo->px_y / trigo->unit_y_size)]
			[(int)(if_wall / trigo->unit_x_size)] != '1')
		trigo->px_x += SPEED * -cos(trigo->angle);
}

void	ft_left(t_trigo *trigo)
{
	trigo->angle += ROT * DEGREE;
	if (trigo->angle + DEGREE >= 2 * PI)
		trigo->angle = 0 + DEGREE;
}

void	ft_right(t_trigo *trigo)
{
	trigo->angle -= ROT * DEGREE;
	if (trigo->angle - DEGREE < 0)
		trigo->angle = 2 * PI - DEGREE;
}

int	ft_update_position(int key, t_trigo *trigo)
{
	if (key == K_W)
		ft_forward(trigo);
	else if (key == K_S)
		ft_backward(trigo);
	else if (key == K_A || key == ARR_L)
		ft_left(trigo);
	else if (key == K_D || key == ARR_R)
		ft_right(trigo);
	if (key == ESC)
	{
		ft_free_memory();
		ft_destroy_imgs();
		mlx_destroy_window(get_win(0)->mlx_p, get_win(0)->win_p);
		exit (1);
	}
	return (0);
}
