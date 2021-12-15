/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psleziak <psleziak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 16:24:13 by psleziak          #+#    #+#             */
/*   Updated: 2021/12/15 18:58:43 by psleziak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/cub3d.h"

int	ft_render_image(t_trigo *trigo)
{
	ft_raycasting(trigo);
	mlx_put_image_to_window(get_win(0)->mlx_p, get_win(0)->win_p,
		get_img(0)[BG].img_inst, 0, 0);
	mlx_put_image_to_window(get_win(0)->mlx_p, get_win(0)->win_p,
		get_img(0)[WL].img_inst, 0, 0);
	return (0);
}

void	ft_init_loop(t_trigo *trigo)
{
	mlx_loop_hook(get_win(0)->mlx_p, ft_render_image, trigo);
	mlx_hook(get_win(0)->win_p, 2, 1L << 0, ft_update_position, trigo);
	mlx_hook(get_win(0)->win_p, 17, (1L << 16), ft_close_window, 0);
	mlx_loop(get_win(0)->mlx_p);
}

int	main(int argc, char **argv)
{
	t_map	map;
	t_win	win;
	t_img	*img;
	t_trigo	trigo;

	if (argc != 2 && ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 5))
	{
		ft_error_handler("Error\n", "Incorrect map name. Must be *.cub\n", 2);
		return (-1);
	}
	img = ft_calloc(sizeof(t_img), 2 + 1);
	ft_set_em_to_zero(&map, &win, img, &trigo);
	if (!ft_map_parse(argv[1], &map, &trigo))
	{
		ft_free_memory();
		return (-1);
	}
	win.mlx_p = mlx_init();
	win.win_p = mlx_new_window(win.mlx_p, map.win_wid, map.win_hei, "cub3d");
	ft_fill_walls_and_background_struct(img, &map, &win);
	ft_create_singletones(&map, &win, img);
	ft_create_bg();
	ft_init_loop(&trigo);
	return (0);
}
