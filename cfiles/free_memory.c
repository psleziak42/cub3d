/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 18:47:34 by psleziak          #+#    #+#             */
/*   Updated: 2021/12/15 22:59:56 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/cub3d.h"

void	malloc_guard(void **alloc_var, int size, int data_type_size)
{
	if (size <= 0 || data_type_size <= 0)
	{
		ft_error_handler("Error\n", "Incorrect map name. Must be *.cub\n", 2);
		exit(0);
	}
	*alloc_var = malloc(size * data_type_size);
	if (!(*alloc_var))
	{
		ft_error_handler("Error\n", "Incorrect map name. Must be *.cub\n", 2);
		exit(0);
	}
}

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

int	ft_free_memory_without_singleton(t_map *map)
{
	int	index;

	index = -1;
	if (map->map)
	{
		while (map->map[++index])
		{
			free(map->map[index]);
			map->map[index] = NULL;
		}
		free(map->map);
		map->map = NULL;
	}
	index = -1;
	if (map->args)
	{
		while (map->args[++index])
		{
			free(map->args[index]);
			map->args[index] = NULL;
		}
		free(map->args);
		map->args = NULL;
	}
	return (-1);
}
