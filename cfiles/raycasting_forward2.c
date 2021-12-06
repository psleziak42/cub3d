/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_forward2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 20:11:16 by psleziak          #+#    #+#             */
/*   Updated: 2021/12/06 22:46:50 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/cub3d.h"

void	ft_create_3d_world(float dist, float ra) // i ll need ofset lineO and lineH as return
{
	float	fish_eye;

	fish_eye = ra - g_master.trigo.current_angle; // Saber o angulo do angulo do jogador e o angulo atual (visto que incrementamos 30)
	if (fish_eye < 0)
		fish_eye += 2 * PI;
	if (fish_eye > 2 * PI)
		fish_eye -= 2 * PI;
	dist *= cos(fish_eye); // Vai dar a distancia para o novo angulo 
	// printf("dist: %f, i: %d\n", dist, i);
	(void)ra;
	g_master.trigo.lineH_3d = (g_master.trigo.cub_size * g_master.map.window_height) / dist; // Tamanho do cub size
	if (g_master.trigo.lineH_3d > g_master.map.window_height)
		g_master.trigo.lineH_3d = g_master.map.window_height;
	g_master.trigo.lineO_3d = (g_master.map.window_height - g_master.trigo.lineH_3d) / 2;
	// printf("g_master.trigo.lineH_3d: %f, i: %d\n", g_master.trigo.lineH_3d, i);
	// printf("g_master.trigo.lineO_3d: %f, i: %d\n", g_master.trigo.lineO_3d, i);
}

static float	ft_distance(float ry, float py, float rx, float px)
{
	return (sqrt((ry - py) * (ry - py) + (rx - px) * (rx - px)));
}

float	ft_horizontal_dist(float ra)
{
	float	ray_horizontal; // wall_x;
	float	ray_vertical; // wall_y;
	float	xo;
	float	yo;
	int		mx;
	int		my;
	
	if (!tan(ra))
	{
		ray_vertical = g_master.trigo.pixel_y;
		ray_horizontal = g_master.trigo.pixel_x;
		yo = 0;
		xo = g_master.trigo.unit_x_size;
	}
	else if (ra < PI)
	{
		ray_vertical = ((int)(g_master.trigo.pixel_y / g_master.trigo.unit_y_size) * g_master.trigo.unit_y_size) - 0.0001;
		ray_horizontal = ((g_master.trigo.pixel_y - ray_vertical) / tan(ra)) + g_master.trigo.pixel_x;
		yo = -g_master.trigo.unit_y_size;
		xo = -yo / tan(ra);
	}
	else
	{
		ray_vertical = ((int)(g_master.trigo.pixel_y / g_master.trigo.unit_y_size) * g_master.trigo.unit_y_size) + g_master.trigo.unit_y_size; //- 0.0001; // - 0.0001;//  + 0.0001;
		ray_horizontal = ((g_master.trigo.pixel_y - ray_vertical) / tan(ra)) + g_master.trigo.pixel_x;
		yo = g_master.trigo.unit_y_size;
		xo = -yo / tan(ra);
	}
	mx = (int)(ray_horizontal / g_master.trigo.unit_x_size);
	my = (int)(ray_vertical / g_master.trigo.unit_y_size);
	while (my < g_master.map.last_line && mx < g_master.map.longest_line && my > 0 && mx > 0 && g_master.map.map[my][mx] != '1')
	{
		ray_horizontal += xo;
		ray_vertical += yo;
		mx = (int)(ray_horizontal / g_master.trigo.unit_x_size);
		my = (int)(ray_vertical / g_master.trigo.unit_y_size);
	}
	g_master.trigo.ryh = ray_vertical;
	g_master.trigo.rxh = ray_horizontal;
	return(ft_distance(ray_vertical, g_master.trigo.pixel_y, ray_horizontal, g_master.trigo.pixel_x));
}

float	ft_vertical_dist(float ra)
{
	float	ry;
	float	rx;
	float	xo;
	float	yo;
	int		mx;
	int		my;
	
	if (!tan(ra))
	{
		ry = g_master.trigo.pixel_y;
		rx = g_master.trigo.pixel_x;
		yo = g_master.trigo.unit_x_size;
		xo = 0;
	}
	else if (ra >= P2 && ra <= P3)
	{
		rx =((int)(g_master.trigo.pixel_x / g_master.trigo.unit_x_size) * g_master.trigo.unit_x_size) - 0.0001;
		ry = ((g_master.trigo.pixel_x - rx) * tan(ra)) + g_master.trigo.pixel_y;
		xo = -g_master.trigo.unit_x_size;
		yo = -xo * tan(ra);
	}
	else
	{
		rx = ((int)(g_master.trigo.pixel_x / g_master.trigo.unit_x_size) * g_master.trigo.unit_x_size) + g_master.trigo.unit_x_size; //- 0.0001; // - 0.0001;//  + 0.0001;
		ry = ((g_master.trigo.pixel_x - rx) * tan(ra)) + g_master.trigo.pixel_y;
		xo = g_master.trigo.unit_x_size;
		yo = -xo * tan(ra);
	}
	mx = (int)(rx / g_master.trigo.unit_x_size);
	my = (int)(ry / g_master.trigo.unit_y_size);
	while (my < g_master.map.last_line && mx < g_master.map.longest_line && my > 0 && mx > 0 && g_master.map.map[my][mx] != '1')
	{
		rx += xo;
		ry += yo;
		mx = (int)(rx / g_master.trigo.unit_x_size);
		my = (int)(ry / g_master.trigo.unit_y_size);
	}
	g_master.trigo.ryv = ry;
	g_master.trigo.rxv = rx;
	return(ft_distance(ry, g_master.trigo.pixel_y, rx, g_master.trigo.pixel_x));
}

static void	ft_print_ray(float ry, float ra)
{
	float 	x;
	float	y;
	float	delta_x;
	float	step;
	int		inc;

	delta_x = fabs(ry - g_master.trigo.pixel_x);
	x = g_master.trigo.pixel_x;
	y = g_master.trigo.pixel_y;
	step = tan(ra);
	if (cos(ra) > 0)
	{
		step *= -1;
		inc = 1;
	}
	else
		inc = -1;
	while (--delta_x > 0)
	{
		// my_mlx_pixel_put(&g_master.bg, x, y, color);
		y += step;
		x += inc;
	}	
}

void	angle_protection(float *ra)
{
	if (*ra < 0)
		*ra += 2 * PI;
	else if (*ra > 2 * PI)
		*ra -= 2 * PI;
}

void	ft_raycasting(void)
{
	float	dist;
	int		i;
	float	ray_angle;
	float	rest;
	float	width_for_iteration; // Width to 
	float	dist_v;
	float	dist_h;
	bool	hit_the_vertical = false;
	bool	hit_the_horizontal = false;
	// int		half_of_rays = NUMBER_OF_RAYS/2;
	float	inc;
	int		more_rays;

	width_for_iteration = 0.0;
	rest = 0.0;
	ray_angle = g_master.trigo.current_angle + (30 * degree);
	angle_protection(&ray_angle);
	i = -1;
	g_master.temp = 0;
	inc = g_master.map.window_width/NUMBER_OF_RAYS;
	rest = (g_master.map.window_width%NUMBER_OF_RAYS) * 60;
	more_rays = rest/(int)inc;	
	while (++i < NUMBER_OF_RAYS + more_rays)
	{
		dist_v = ft_vertical_dist(ray_angle);
		dist_h = ft_horizontal_dist(ray_angle);
		if (dist_h < dist_v)
		{
			dist = dist_h;
			hit_the_horizontal = true;
			ft_print_ray(g_master.trigo.ryh, ray_angle);
		}
		else
		{
			dist = dist_v;
			hit_the_vertical = true;
			ft_print_ray(g_master.trigo.ryv, ray_angle);
		}
		ft_create_3d_world(dist, ray_angle);
		// width_for_iteration += ((float)g_master.map.window_width / (NUMBER_OF_RAYS + more_rays)); // 
		// if (i == 0) // rest = x_width + g_master.map.window_width % 60? 
		// 	g_master.trigo.x_width = (int)width_for_iteration;
		// printf("dist %f\n", dist);
		// sleep(1);
		ft_3d_print_addr(inc, dist);
		ray_angle -= degree/4;
		angle_protection(&ray_angle);
	}
	mlx_put_image_to_window(g_master.window.mlx_p, g_master.window.win_p, g_master.walls.img_instance, 0, 0);
}
