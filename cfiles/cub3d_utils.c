/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psleziak <psleziak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 19:52:49 by psleziak          #+#    #+#             */
/*   Updated: 2021/12/15 20:59:58 by psleziak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/cub3d.h"

void	ft_error_handler(char *error, char *msg, int fd)
{
	ft_putstr_fd(error, fd);
	ft_putstr_fd(msg, fd);
}

int	ft_close_window(void)
{
	ft_free_memory();
	ft_destroy_imgs();
	mlx_destroy_window(get_win(0)->mlx_p, get_win(0)->win_p);
	exit(1);
}

void	ft_fill_walls_and_background_struct(t_img *img, t_map *map, t_win *win)
{
	img[WL].img_inst = mlx_new_image(win->mlx_p, map->win_wid, map->win_hei);
	img[WL].img_address = mlx_get_data_addr(img[WL].img_inst, &img[WL].bpp,
			&img[WL].line_len, &img[WL].endian);
	img[BG].img_inst = mlx_new_image(win->mlx_p, map->win_wid, map->win_hei);
	img[BG].img_address = mlx_get_data_addr(img[BG].img_inst, &img[BG].bpp,
			&img[BG].line_len, &img[BG].endian);
}

void	ft_set_em_to_zero(t_map *map, t_win *win, t_img *img, t_trigo *trigo)
{
	ft_memset(map, 0, sizeof(t_map));
	ft_memset(win, 0, sizeof(t_win));
	ft_memset(img, 0, sizeof(t_img));
	ft_memset(trigo, 0, sizeof(t_trigo));
}

void	ft_create_singletones(t_map *map, t_win *win, t_img *img)
{
	get_map(map);
	get_win(win);
	get_img(img);
}
