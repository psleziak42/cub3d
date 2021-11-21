/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psleziak <psleziak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 23:47:04 by psleziak          #+#    #+#             */
/*   Updated: 2021/11/20 23:54:04 by psleziak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/cub3d.h"

void	ft_free_memory(void)
{
	int	y;

	y = -1;
	while (g_master.map.map[++y])
		free(g_master.map.map[y]);
	free(g_master.map.map);
	y = -1;
	while (g_master.map.args[++y])
		free(g_master.map.args[y]);
	free(g_master.map.args);
	y = -1;
	while (g_master.map.RGB[++y])
		free(g_master.map.RGB[y]);
	free(g_master.map.RGB);
}
