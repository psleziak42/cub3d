/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 23:47:04 by psleziak          #+#    #+#             */
/*   Updated: 2021/12/13 23:38:44 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/cub3d.h"

void	ft_free_memory(void)
{
	int	y;

	y = -1;
	if (g_master.map.map)
	{
		if (g_master.map.map[y + 1])
			while (g_master.map.map[++y])
				free(g_master.map.map[y]);
		free(g_master.map.map);
	}
	y = -1;
	if (g_master.map.args != NULL)
	{
		while (g_master.map.args[++y])
			free(g_master.map.args[y]);
		free(g_master.map.args);
	}
	y = -1;
}
