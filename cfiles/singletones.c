/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singletones.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 18:41:25 by rimartin          #+#    #+#             */
/*   Updated: 2021/12/14 18:41:49 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/cub3d.h"

t_map	*get_map(t_map *map)
{
	static t_map	*mapa;

	if (!map)
		mapa = map;
	return (mapa);
}

t_win	*get_win(t_win *win)
{
	static t_win	*window;

	if (!win)
		window = win;
	return (window);
}

t_img	*get_img(t_img *img)
{
	static t_img	*image;

	if (!img)
		image = img;
	return (image);
}

t_trigo	*get_trigo(t_trigo *trigo)
{
	static t_trigo	*trigonometry;

	if (!trigo)
		trigonometry = trigo;
	return (trigonometry);
}
