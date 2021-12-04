/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_forward2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 20:11:16 by psleziak          #+#    #+#             */
/*   Updated: 2021/12/03 22:35:14 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/cub3d.h"

// 	// jesli wiemy ze y jest dluzsze w tamtych obliczeniach to juz bez sensu tu spradzac // 

// 	// dy = fabs(g_master.trigo.wall_y_pixel - g_master.trigo.pixel_y);
// 	// dx = fabs(g_master.trigo.wall_x_pixel - g_master.trigo.pixel_x);
// 	// printf("\n\ng_master.trigo.wall_y_pixel: %f\n", g_master.trigo.wall_y_pixel);
// 	// printf("g_master.trigo.wall_x_pixel: %f\n", g_master.trigo.wall_x_pixel);
// 	// printf("dy: %f\n", fabs(g_master.trigo.wall_y_pixel - y));
// 	// printf("dx: %f\n\n\n", fabs(g_master.trigo.wall_x_pixel - x));
// 	// if (dy > dx)
// 	// 	step = dy;
// 	// else
// 	// 	step = dx;
// 	// dx = dx/step;
// 	// dy = dy/step;
// 	// i = -1;
// 	// while (++i <= step)
// 	// {
// 	// 	printf("y: %f, x: %f\n", y, x);
// 	// 	mlx_pixel_put(g_master.window.mlx_p, g_master.window.win_p, x, y, 0xFF0000);
// 	// 	y -= dy;
// 	// 	x += dx;
// 	// }

// static void	ft_print_one_ray(void)
// {
// 	float	i;
// 	// float	dx;
// 	// float	dy;
// 	// float	step;
// 	float	x;
// 	float	y;
// 	float	c; // length of the line
// 	float	step; // slope of the line, zmiana dla y.

// 	y = g_master.trigo.pixel_y; // player y
// 	printf("y: %f\n", y);
// 	x = g_master.trigo.pixel_x; // player x
// 	printf("x: %f\n", x);
// 	printf("g_master.trigo.wall_y_pixel: %f\n", g_master.trigo.wall_y_pixel);
// 	printf("g_master.trigo.wall_x_pixel: %f\n", g_master.trigo.wall_x_pixel);
// 	// g_master.trigo.wall_y_pixel = g_master.trigo.ray_dist_to_y; 
// 	// g_master.trigo.wall_x_pixel = g_master.trigo.ray_dist_to_x;
// 	//c = sqrt((g_master.trigo.wall_y_pixel - y) * (g_master.trigo.wall_y_pixel - y)
// 	//			+ (g_master.trigo.wall_x_pixel - x) * (g_master.trigo.wall_x_pixel));
// 	//printf("c: %f\n", c);
// 	//slope = (g_master.trigo.wall_y_pixel - y) / (g_master.trigo.wall_x_pixel - x);
	
// 	//printf("slope: %f\n", slope);
// 	i = 0;
// 	if (fabs(g_master.trigo.wall_y_pixel) > fabs(g_master.trigo.wall_x_pixel))
// 	//{
// 		c = cos(g_master.trigo.current_angle) * g_master.trigo.wall_x_pixel;
// 		//c = g_master.trigo.wall_x_pixel;
// 	else
// 		c = sin(g_master.trigo.current_angle) * g_master.trigo.wall_y_pixel;
// 	// if (g_master.trigo.wall_y_pixel > g_master.trigo.wall_x_pixel) - moze tu cos sie dzieje.
// 	// 	step = tan(g_master.trigo.current_angle) * 1;
// 	// printf("step: %f\n", step);
// 	while (i < c)
// 	{
// 		step = tan(g_master.trigo.current_angle);
// 		//printf("step: %f\n", step);
// 		if (cos(g_master.trigo.current_angle) > 0)
// 			y -= step;
// 		else
// 			y += step;
// 		mlx_pixel_put(g_master.window.mlx_p, g_master.window.win_p, x, y, 0xFF0000);
// 		if (cos(g_master.trigo.current_angle) < 0)
// 				x -= 1;
// 		else
// 			x += 1;
// 		i++;
// 	}
// 	printf("-----------------here------------------\n\n");
// }
// /***
//  * zle licze odleglosci. Odleglosc od pozycji do X badz Y na mapie moze byc wieksza niz 1 jednostka.
//  * jesli castuje po Y |/| to dla 0 - 90 y = y - 1, ale x = x + y(32)/tgalfa.
//  * To jest w pixelach podane wiec trzeba przeliczyc /32 i updatowac X w zaleznosci od tego gdzie sie kratka koczy/
//  * strona 1!!
//  * **/
// /*static void	ft_find_da_wall(void)
// {
// 	// int		imaginary_map2d_x;
// 	// int		imaginary_map2d_y;
// 	int 	ux;
// 	int		uy;

// 	// imaginary_map2d_x = g_master.trigo.map2d_x; 
// 	// imaginary_map2d_y = g_master.trigo.map2d_y;
// 	printf("111 imaginary_map2d_x: %d\n", g_master.trigo.imaginary_map2d_x);
// 	printf("111 imaginary_map2d_y: %d\n", g_master.trigo.imaginary_map2d_y);
// 	printf("111111 g_master.map.map[imaginary_map2d_y][imaginary_map2d_x]: %c\n", 
// 		g_master.map.map[g_master.trigo.imaginary_map2d_y][g_master.trigo.imaginary_map2d_x]); // must stop here;
// 	if (g_master.map.map[g_master.trigo.imaginary_map2d_y][g_master.trigo.imaginary_map2d_x] != '1')
// 	{
// 		g_master.trigo.ray_dist_to_x = g_master.trigo.offset_y / sin(g_master.trigo.current_angle);
// 		printf("g_master.trigo.offset_y: %f\n", g_master.trigo.offset_y);
// 		printf("sin(g_master.trigo.current_angle: %f\n", sin(g_master.trigo.current_angle));
// 		printf("g_master.trigo.ray_dist_to_x: %f\n", g_master.trigo.ray_dist_to_x);
// 		/** tu mozna policzyc x2 i y2 i zsumowac z x1 i x2 i jesli zmienia pozycje to zmienic pozycje ray na mapie **/
// 		ux = g_master.trigo.ray_dist_to_x * cos(g_master.trigo.current_angle);
// 		uy = g_master.trigo.ray_dist_to_x * sin(g_master.trigo.current_angle); // x bo liczymy przyklad dla X.
// 			if (g_master.map.map[g_master.trigo.imaginary_map2d_y + uy][g_master.trigo.imaginary_map2d_x + ux] != 1)
// 			{
// 				g_master.trigo.imaginary_map2d_x += ux;
// 				g_master.trigo.imaginary_map2d_y += uy;
// 				//g_master.trigo.imaginary_map2d_x += (g_master.trigo.offset_y / tan(g_master.trigo.current_angle))/32;
// 				printf("g_master.trigo.offset_y: %f\n", g_master.trigo.offset_y);
// 				printf("tan(g_master.trigo.current_angle): %f\n", tan(g_master.trigo.current_angle));
// 				printf("333: imaginary_map2d_x: %d\n", g_master.trigo.imaginary_map2d_x);
// 			}
// 	}
// 	printf("222222 g_master.map.map[imaginary_map2d_y][imaginary_map2d_x]: %c\n", 
// 		g_master.map.map[g_master.trigo.imaginary_map2d_y][g_master.trigo.imaginary_map2d_x]);
// 	if (g_master.map.map[g_master.trigo.imaginary_map2d_y][g_master.trigo.imaginary_map2d_x] != '1')
// 	{
// 		g_master.trigo.ray_dist_to_y = g_master.trigo.offset_x / cos(g_master.trigo.current_angle);
// 		printf("g_master.trigo.ray_dist_to_y: %f\n", g_master.trigo.ray_dist_to_y);
// 			if (fabs(g_master.trigo.ray_dist_to_y / 32) > g_master.trigo.imaginary_map2d_y)
// 			{
// 				g_master.trigo.imaginary_map2d_y += (g_master.trigo.offset_x * tan(g_master.trigo.current_angle)) / 32;
// 				printf("222: imaginary_map2d_y: %d\n", g_master.trigo.imaginary_map2d_y);
// 			}
// 	}
// 	/** dlugosc lini x i y **/
// 	if (g_master.map.map[g_master.trigo.imaginary_map2d_y][g_master.trigo.imaginary_map2d_x] != '1')
// 	{
// 		g_master.trigo.wall_y_pixel = g_master.trigo.unit_y_size / sin(g_master.trigo.current_angle);//imaginary_map2d_y * g_master.trigo.unit_y_size;
// 		g_master.trigo.wall_x_pixel = g_master.trigo.unit_x_size / cos(g_master.trigo.current_angle);//imaginary_map2d_x * g_master.trigo.unit_x_size;
// 		printf("wall_y: %f, wall_x: %f\n", g_master.trigo.wall_y_pixel, g_master.trigo.wall_x_pixel);
// 	}




// }*/
// 	// while (g_master.map.map[imaginary_map2d_y][imaginary_map2d_x] != '1')
// 	// {
// 	// 	//printf("tutaj\n");
// 	// 	if (fabs(g_master.trigo.ray_dist_to_x) >= fabs(g_master.trigo.ray_dist_to_y)) // sin, cos can give - values
// 	// 	{
// 	// 		printf("imaginary_map2d_y: %d\n", imaginary_map2d_y);
// 	// 		g_master.trigo.ray_dist_to_y = g_master.trigo.unit_x_size / cos(g_master.trigo.current_angle); // not sure if it updates the value of the ray or always shoots the same.
// 	// 		imaginary_map2d_y += g_master.trigo.map2d_y_incrementor;
// 	// 	}
// 	// 	else
// 	// 	{
// 	// 		printf("imaginary_map2d_x: %d\n", imaginary_map2d_x);
// 	// 		g_master.trigo.ray_dist_to_x = g_master.trigo.unit_y_size / sin(g_master.trigo.current_angle);
// 	// 		imaginary_map2d_x += g_master.trigo.map2d_x_incrementor;
// 	// 	}
// 	// }

// // static void	ft_calculate_X_and_Y_distance_to_grid(void)
// // {
// // 	if (g_master.trigo.dist_y_to_grid > g_master.trigo.dist_x_to_grid)
// // 		g_master.trigo.ray_dist_to_x = fabs(g_master.trigo.unit_y_size / sin(g_master.trigo.current_angle));
// // 	else
// // 		g_master.trigo.ray_dist_to_y = fabs(g_master.trigo.unit_x_size / sin(g_master.trigo.current_angle));
// // }

// static void	ft_set_map_incrementor(void)
// {
// 	if (cos(g_master.trigo.current_angle) > 0)
// 		g_master.trigo.map2d_x_incrementor = 1;
// 	else
// 		g_master.trigo.map2d_x_incrementor = -1;
// 	if (sin(g_master.trigo.current_angle) > 0)
// 		g_master.trigo.map2d_y_incrementor = -1;
// 	else
// 		g_master.trigo.map2d_y_incrementor = 1;
// 	printf("sin: %f, cos: %f\n", sin(g_master.trigo.current_angle), cos(g_master.trigo.current_angle));
// 	printf("inc_y: %d, inc_x: %d\n", g_master.trigo.map2d_y_incrementor, g_master.trigo.map2d_x_incrementor);
// }

// static void	ft_calculate_initial_offsets_and_distances(void) // every next move instead offset x/y we take unit size x/y 
// {
	// int		imaginary_map2d_x;
	// int		imaginary_map2d_y;
	
	// imaginary_map2d_x = g_master.trigo.map2d_x;
	// imaginary_map2d_y = g_master.trigo.map2d_y;
	// g_master.trigo.offset_y = fmod(g_master.trigo.pixel_y, g_master.trigo.unit_y_size);
	// g_master.trigo.offset_x = fmod(g_master.trigo.pixel_x, g_master.trigo.unit_x_size);
	// if (cos(g_master.trigo.current_angle) > 0)
	// 	g_master.trigo.offset_x = g_master.trigo.unit_x_size - g_master.trigo.offset_x;
	// if (sin(g_master.trigo.current_angle) < 0)
	// 	g_master.trigo.offset_y = g_master.trigo.unit_y_size - g_master.trigo.offset_y;
	
	/* Shooting ray to first X and Y grid */
	
	// if (g_master.map.map[imaginary_map2d_y][imaginary_map2d_x] != '1')
	// {
	// 	g_master.trigo.ray_dist_to_x = g_master.trigo.offset_y / sin(g_master.trigo.current_angle);
	// 	if (g_master.trigo.ray_dist_to_x)
	// 		imaginary_map2d_x += g_master.trigo.map2d_y_incrementor;
	// 	g_master.trigo.ray_dist_to_y = g_master.trigo.offset_x / cos(g_master.trigo.current_angle);
	// 	if (g_master.trigo.ray_dist_to_y)
	// 		imaginary_map2d_x += g_master.trigo.map2d_y_incrementor;
	// }
	// printf("g_master.trigo.ray_dist_to_y: %f\n", g_master.trigo.ray_dist_to_y);
	// printf("g_master.trigo.ray_dist_to_x: %f\n", g_master.trigo.ray_dist_to_x);
	//ft_print_one_ray();
//}
static float	ft_distance(float ry, float py, float rx, float px)
{
	return (sqrt((ry - py) * (ry - py) + (rx - px) * (rx - px)));
}

/* WYSTARCZY JEDNA DRUKARKA, BO Y LICZYMY PO X ANYWAY */

// static void	ft_print_one_ray_v(float rx, float ry, int color)
// {
// 	float 	x;
// 	float	y;
// 	float	i;
// 	//float	c;
// 	float	delta_x;
// 	float	step;

// 	ry = (float)ry;
// 	i = 0;
// 	delta_x = fabs(rx - g_master.trigo.pixel_x); // chyba zle drukuje, trzeba popracoawc nad delta!!!, moze 2 rozne funkcje dac!!
// 	printf("deltax: %f\n", delta_x);
// 	// if (sin(g_master.trigo.current_angle) != 0)
// 	// 	c = delta_x / sin(g_master.trigo.current_angle);
// 	step = tan(g_master.trigo.current_angle);
// 	x = g_master.trigo.pixel_x;
// 	y = g_master.trigo.pixel_y;
// 	while (i < delta_x)
// 	{
// 		mlx_pixel_put(g_master.window.mlx_p, g_master.window.win_p, x, y, color);
// 		if (cos(g_master.trigo.current_angle) > 0)
// 			y -= step;
// 		else
// 			y += step;
// 		if (cos(g_master.trigo.current_angle) < 0)
// 				x -= 1;
// 		else
// 			x += 1;
// 		i++;
// 	}	
// }

/* nie wiem dlaczego nie drukuje 60 promieni*/
//====================================================================
static void	ft_print_one_ray_h(float rx, float ry, float ra, int color)
{
	float 	x;
	float	y;
	float	i;
	//float	c;
	float	delta_x;
	float	step;

	ry = (float)ry;
	i = 0;
	delta_x = fabs(rx - g_master.trigo.pixel_x); // chyba zle drukuje, trzeba popracoawc nad delta!!!, moze 2 rozne funkcje dac!!
	printf("deltax: %f\n", delta_x);
	// if (sin(g_master.trigo.current_angle) != 0)
	// 	c = delta_x / sin(g_master.trigo.current_angle);
	step = tan(ra);
	x = g_master.trigo.pixel_x;
	y = g_master.trigo.pixel_y;
	while (i < delta_x)
	{
		mlx_pixel_put(g_master.window.mlx_p, g_master.window.win_p, x, y, color);
		if (cos(ra) > 0)
			y -= step;
		else
			y += step;
		if (cos(ra) < 0)
			x -= 1;
		else
			x += 1;
		i++;
	}	
}
// ============================================================
// static void	ft_3d_printer(float lineH, float lineO, float width_x);

void	ft_draw_3d(void)
{
	float	distHorizontal;
	float	distVertical;
	float	rx; // wall_x;
	float	ry; // wall_y;
	float	xo;
	float	yo;
	int		mx;
	int		my;
	float	cot;
	int		i;
	float	ra;
	float	width_x;

	i = -1;
	// ra = g_master.trigo.current_angle - degree * 30;
	// if (ra < 0)
	// 	ra += 2 * PI;
	// if (ra > 2*PI)
	// 	ra -= 2 * PI;
	ra = g_master.trigo.current_angle + 30 * degree; //-> jak zmieniam pozycje z x albo y to linie sie wydluzaja.
	//printf("\n\n 1_RA: %f \n\n", ra);
	//ra = g_master.trigo.current_angle + degree;
	width_x = 0;
	//printf("\n\n 2_RA: %f \n\n", ra);
	while (++i < 60)
	{	
	/*** TANGENS IS CHANGING SIGNT AND FUCKING UP ALL THE MATH. WE SHOULD PROBABLY USE SINUS AND COSINUS INSTEAD TO HAVE CONTROL OVER THIS SHIT ***/
		cot = 1/(tan(ra));
		//printf("\n\ng_master.trigo.pixel_y: %f, g_master.trigo.pixel_x: %f\n\n", g_master.trigo.pixel_y, g_master.trigo.pixel_x);
		/**** HORIZONTAL LINES ****/
		if (!tan(ra))
		{
			ry = g_master.trigo.pixel_y;
			rx = g_master.trigo.pixel_x;
			yo = 0;
			xo = g_master.trigo.unit_x_size;
		}
		else if (ra < PI)
		{
			ry = ((int)(g_master.trigo.pixel_y / g_master.trigo.unit_y_size) * g_master.trigo.unit_y_size) - 0.0001;
			printf("\nra < PI ry: %f\n", ry);
			rx = ((g_master.trigo.pixel_y - ry) * cot) + g_master.trigo.pixel_x;
			printf("\nra < PI rx: %f\n", rx);
			yo = -g_master.trigo.unit_y_size;
			xo = -yo * cot;
		}
		else
		{
			ry = ((int)(g_master.trigo.pixel_y / g_master.trigo.unit_y_size) * g_master.trigo.unit_y_size) + g_master.trigo.unit_y_size; //- 0.0001; // - 0.0001;//  + 0.0001;
			rx = ((g_master.trigo.pixel_y - ry) * cot) + g_master.trigo.pixel_x;
			yo = g_master.trigo.unit_y_size;
			xo = -yo * cot;
		}
		mx = (int)(rx / g_master.trigo.unit_x_size);
		my = (int)(ry / g_master.trigo.unit_y_size);
		while (my < 8 && mx < 8 && my > 0 && mx > 0 && g_master.map.map[my][mx] != '1')
		{
			ry += yo;
			rx += xo;
			// printf("tan(ra): %f\n", cot);
			// printf("2___:g_master.map.map[y:%d][x:%d]: %c\n", my, mx, g_master.map.map[my][mx]);
			my = (int)(ry / g_master.trigo.unit_y_size);
			mx = (int)(rx / g_master.trigo.unit_x_size);
			
		}
		// printf("\n\ng_master.trigo.pixel_y: %f, g_master.trigo.pixel_x: %f\n", g_master.trigo.pixel_y, g_master.trigo.pixel_x);
		// printf("ry: %f, rx: %f\n",ry, rx);

		distHorizontal = ft_distance(ry, g_master.trigo.pixel_y, rx, g_master.trigo.pixel_x);
		// printf("distHorizontal: %f\n\n", distHorizontal);
		//ft_print_one_ray(rx, ry, 0xFF0000, 0);
		/*********** CHECK VERTICAL LINE *************/
		float ryv;
		float rxv;
		float	distT;

		float nTan = tan(ra);
		if (!tan(ra))
		{
			ryv = g_master.trigo.pixel_y;
			rxv = g_master.trigo.pixel_x;
			yo = g_master.trigo.unit_x_size;
			xo = 0;
		}
		else if (ra > P2 && ra < P3)
		{
			rxv =((int)(g_master.trigo.pixel_x / g_master.trigo.unit_x_size) * g_master.trigo.unit_x_size) - 0.0001;
			//printf("RXVertical 90 - 270: %f\n", rxv);
			ryv = ((g_master.trigo.pixel_x - rxv) * nTan) + g_master.trigo.pixel_y;
			//printf("RYVertical 90 - 270: %f\n", ryv);
			xo = -g_master.trigo.unit_x_size;
			yo = -xo * nTan;
		}
		else
		{
			rxv = ((int)(g_master.trigo.pixel_x / g_master.trigo.unit_x_size) * g_master.trigo.unit_x_size) + g_master.trigo.unit_x_size; //- 0.0001; // - 0.0001;//  + 0.0001;
			ryv = ((g_master.trigo.pixel_x - rxv) * nTan) + g_master.trigo.pixel_y;
			xo = g_master.trigo.unit_x_size;
			yo = -xo * nTan;
		}
		my = (int)(ryv / g_master.trigo.unit_y_size);
		mx = (int)(rxv / g_master.trigo.unit_x_size);
		printf("start mx %d my %d longest line %d last line %d\n", mx, my, g_master.map.longest_line, g_master.map.last_line);
		while (my < g_master.map.last_line && mx < g_master.map.longest_line - 1 && my > 0 && mx > 0 && g_master.map.map[my][mx] != '1')
		{
			rxv += xo;
			ryv += yo;
			mx = (int)(rxv / g_master.trigo.unit_x_size);
			my = (int)(ryv / g_master.trigo.unit_y_size);
			printf("mx %d e my %d\n", mx, my);
		}
		distVertical = ft_distance(ryv, g_master.trigo.pixel_y, rxv, g_master.trigo.pixel_x); // rxv ryvt musi byc dla horizontal i vertial osobne;
		if (distVertical < distHorizontal)
		{
			distT = distVertical;
			ft_print_one_ray_h(rxv, ryv, ra, 0x0000FF);
		}
		else
		{
			distT = distHorizontal;
			ft_print_one_ray_h(rx, ry, ra, 0xFF0000);
		}
		ra -= degree;
		width_x += g_master.map.window_width / 60;
		if (ra < 0)
			ra += 2 * PI;
		if (ra > 2*PI)
			ra -= 2 * PI;
	// /*********** 3d part ************/
	// 	float	lineH;
	// 	float	lineO;
	// 	float	cubS;
	// 	float	fish_eye;

	// 	cubS = 16;
	// 	fish_eye = g_master.trigo.current_angle - ra;
	// 	if (fish_eye < 0)
	// 		fish_eye += 2 * PI;
	// 	if (fish_eye > 2*PI)
	// 		fish_eye -= 2 * PI;
	// 	distT = distT * cos(fish_eye);
	// 	lineH = (cubS * g_master.map.window_height) / distT;
	// 	lineO = (g_master.map.window_height - lineH) / 2;
	// 	if (lineH > g_master.map.window_height)
	// 		lineH = g_master.map.window_height;
	// 	//ft_3d_printer(lineH, lineO, width_x); // y musi byc 0 i musi byc y + width window / no of rays.
	// 	ra -= degree;
	// 	width_x += g_master.map.window_width / 60;
	// 	if (ra < 0)
	// 		ra += 2 * PI;
	// 	if (ra > 2*PI)
	// 		ra -= 2 * PI;
	}
}

// static void	ft_3d_printer(float lineH, float lineO, float width_x)
// {
// 	int		i;
// 	int		j;

// 	i = -1;
// 	j = width_x - g_master.map.window_width / 60;
// 	while (++i < g_master.map.window_height)
// 	{
// 		printf("j: %d\n", j);
// 		while (j < width_x)
// 		{
// 			printf("j: %d\n", j);
// 			if (i > lineO && i < lineO + lineH)
// 				mlx_pixel_put(g_master.window.mlx_p, g_master.window.win_p, j, i, 0xFF0000);
// 			else
// 				mlx_pixel_put(g_master.window.mlx_p, g_master.window.win_p, j, i, 0x00FF00);
// 			j++;
// 		}
// 		j = width_x - g_master.map.window_width / 60;
// 	}		
// }
/* trzeba zrobic ze ray przechodi przez cala szerokosc. Dlaczego?
* bo plansza musi byc na szerokosc calego okna. wiec jak mam 60 rays po pixelu to bd to tylko 60 px	
* a musi wypelnic cale okno!
*
*/

// static void	ft_print_one_ray(void)
// {
// 	float	i;
// 	// float	dx;
// 	// float	dy;
// 	float	step;
// 	float	x;
// 	float	y;

// 	i = 0;
// 	// if (g_master.trigo.wall_y_pixel > g_master.trigo.wall_x_pixel) - moze tu cos sie dzieje.
// 		step = tan(g_master.trigo.current_angle) * 1;
// 	printf("step: %f\n", step);
// 	while (i < g_master.trigo.unit_x_size)
// 	{
// 		mlx_pixel_put(g_master.window.mlx_p, g_master.window.win_p, x, y, 0xFF0000);
// 		if (cos(g_master.trigo.current_angle) > 0)
// 			y -= step;
// 		else
// 			y += step;
// 		if (cos(g_master.trigo.current_angle) < 0)
// 				x -= 1;
// 		else
// 			x += 1;
// 		i++;
// 	}
// 	printf("here\n");


void	print_one_ray(void)
{
	ft_draw_3d();
	//ft_calculate_initial_offsets_and_distances();
	//ft_set_map_incrementor();
	//ft_find_da_wall();
	//ft_print_one_ray();
	// ft_check_first_square();
	// //ft_print_one_ray();
	// ft_calculate_X_and_Y_distance_to_grid();
}
