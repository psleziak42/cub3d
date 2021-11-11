#include "../extras/hfiles/cub3d.h"

#define IMG_SIZE 64

void	ft_printmap_to_window(t_master *master)
{
	int a;
	int b;
	int	y;
	int x;

	y = 0;
	b = 0;
	while (y < master->map.window_height)
	{
		x = 0;
		a = 0;
		while (x < master->map.window_width)
		{
			if (master->map.map[b][a] == '1')
				master->img.img_file = "extras/textures/wall.xpm";
			else if (master->map.map[b][a] == 'N' || master->map.map[b][a] == 'S' || master->map.map[b][a] == 'E' || master->map.map[b][a] == 'W')
				master->img.img_file = "extras/textures/player.xpm";
			else
				master->img.img_file = "extras/textures/walk.xpm";
			master->img.img_instance = mlx_xpm_file_to_image(master->window.mlx_p, master->img.img_file, &master->img.img_width, &master->img.img_heigth);
			if (!master->img.img_instance)
				printf("error\n");
			mlx_put_image_to_window(master->window.mlx_p, master->window.win_p, master->img.img_instance, x, y);
			x += master->trigo.unit_x_size;
			a++;
		}
		y += master->trigo.unit_y_size;
		b++;
	}
}
