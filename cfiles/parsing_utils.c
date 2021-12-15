/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psleziak <psleziak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 19:36:33 by rimartin          #+#    #+#             */
/*   Updated: 2021/12/14 20:26:57 by psleziak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/cub3d.h"

bool	is_wrong_color(int r, int g, int b)
{
	if (r <= 255 && r >= 0)
		return (false);
	else if (g <= 255 && g >= 0)
		return (false);
	else if (b <= 255 && b >= 0)
		return (false);
	return (true);
}

bool	is_valid_char(char c, char *compound)
{
	int	i;

	i = -1;
	while (compound[++i])
	{
		if (compound[i] == c)
			return (true);
	}	
	return (false);
}
