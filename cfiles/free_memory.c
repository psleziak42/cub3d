/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psleziak <psleziak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 18:47:34 by psleziak          #+#    #+#             */
/*   Updated: 2021/12/15 20:59:26 by psleziak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/cub3d.h"

void	free_rgb(char **rgb)
{
	int	index;

	index = -1;
	while (rgb[++index])
	{
		free(rgb[index]);
		rgb[index] = NULL;
	}
	free(rgb);
	rgb = NULL;
}

void	ft_destroy_imgs(void)
{
	mlx_destroy_image(get_win(0)->mlx_p, get_img(0)[BG].img_inst);
	mlx_destroy_image(get_win(0)->mlx_p, get_img(0)[WL].img_inst);
	free(get_img(0));
}

void	ft_free_memory(void)
{
	int	index;

	index = -1;
	if (get_map(0)->map)
	{
		while (get_map(0)->map[++index])
		{
			free(get_map(0)->map[index]);
			get_map(0)->map[index] = NULL;
		}
		free(get_map(0)->map);
		get_map(0)->map = NULL;
	}
	index = -1;
	if (get_map(0)->args)
	{
		while (get_map(0)->args[++index])
		{
			free(get_map(0)->args[index]);
			get_map(0)->args[index] = NULL;
		}
		free(get_map(0)->args);
		get_map(0)->args = NULL;
	}
}
