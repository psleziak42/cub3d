/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psleziak <psleziak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 23:47:04 by psleziak          #+#    #+#             */
/*   Updated: 2021/11/07 22:28:58 by psleziak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/cub3d.h"

void	ft_free_memory(t_master *master)
{
	int	y;

	y = -1;
	while (master->map.map[++y])
		free(master->map.map[y]);
	free(master->map.map);
	y = -1;
	while (master->map.args[++y])
		free(master->map.args[y]);
	free(master->map.args);
	y = -1;
	while (master->map.RGB[++y])
		free(master->map.RGB[y]);
	free(master->map.RGB);
}
