#include "../extras/hfiles/cub3d.h"

void	ft_printmap_to_window(void)
{
	int a;
	int b;
	int	y;
	int x;

	y = 0;
	b = 0;
	while (y < g_master.map.window_height)
	{
		x = 0;
		a = 0;
		while (x < g_master.map.window_width && g_master.map.map[b][a] != '\0')
		{
			if (g_master.map.map[b][a] == '1')
				g_master.t_s_map.img_file = "extras/textures/wall.xpm";
			else if (g_master.map.map[b][a] == 'N' || g_master.map.map[b][a] == 'S' || g_master.map.map[b][a] == 'E' || g_master.map.map[b][a] == 'W')
				g_master.t_s_map.img_file = "extras/textures/walk.xpm";
			else
				g_master.t_s_map.img_file = "extras/textures/walk.xpm";
			g_master.t_s_map.img_instance = mlx_xpm_file_to_image(g_master.window.mlx_p, g_master.t_s_map.img_file, &g_master.t_s_map.img_width, &g_master.t_s_map.img_heigth);
			if (!g_master.t_s_map.img_instance)
				printf("error\n");
			mlx_put_image_to_window(g_master.window.mlx_p, g_master.window.win_p, g_master.t_s_map.img_instance, x, y);
			x += g_master.trigo.unit_x_size;
			a++;
		}
		y += g_master.trigo.unit_y_size;
		b++;
	}
}
