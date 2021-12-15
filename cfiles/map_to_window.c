#include "../extras/hfiles/cub3d.h"

void	ft_printmap_to_window(t_trigo *trigo)
{
	int a;
	int b;
	int	y;
	int x;
	int unit_size_x = (int)trigo->unit_x_size;
	int unit_size_y = (int)trigo->unit_y_size;;
	t_s_map	minimap;

	y = 0;
	b = 0;
	printf("get_map(0)->window_heigth: %d\n", get_map(0)->win_hei);
	printf("get_map(0).window_width: %d\n", get_map(0)->win_wid);
	printf("g_master.trigo->unit_y_size: %f\n", trigo->unit_y_size);
	printf("trigo->unit_x_size: %f\n", trigo->unit_x_size);
	while (y < get_map(0)->win_hei % 64)
	{
		x = 0;
		a = 0;
		while (x < get_map(0)->win_wid % 64)
		{
			if (get_map(0)->map[b][a] == '1')
				minimap.img_file = "extras/textures/wall.xpm";
			else if (get_map(0)->map[b][a] == 'N' || get_map(0)->map[b][a] == 'S' || get_map(0)->map[b][a] == 'E' || get_map(0)->map[b][a] == 'W')
				minimap.img_file = "extras/textures/walk.xpm";
			else
				minimap.img_file = "extras/textures/walk.xpm";
			minimap.img_instance = mlx_xpm_file_to_image(get_win(0)->mlx_p, minimap.img_file, &minimap.img_wid, &minimap.img_hei);
			if (!minimap.img_instance)
				printf("error\n");
			mlx_put_image_to_window(get_win(0)->mlx_p, get_win(0)->win_p, minimap.img_instance, x % 64, y % 64);
			x += unit_size_x % 64;
			a++;
		}
		y += unit_size_y % 64;
		b++;
	}
}
