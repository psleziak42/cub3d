/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singletones.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psleziak <psleziak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 00:54:44 by psleziak          #+#    #+#             */
/*   Updated: 2021/12/15 20:59:52 by psleziak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/cub3d.h"

t_map	*get_map(t_map *map)
{
	static t_map	*mapa = NULL;

	if (map)
		mapa = map;
	return (mapa);
}

t_win	*get_win(t_win *win)
{
	static t_win	*window = NULL;

	if (win)
		window = win;
	return (window);
}

t_img	*get_img(t_img *img)
{
	static t_img	*image = NULL;

	if (img)
		image = img;
	return (image);
}

t_trigo	*get_trigo(t_trigo *trigo)
{
	static t_trigo	*trigonometry = NULL;

	if (trigo)
		trigonometry = trigo;
	return (trigonometry);
}
