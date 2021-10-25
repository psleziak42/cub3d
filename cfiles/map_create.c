#include "../extras/hfiles/cub3d.h"

#define IMG_SIZE 64

void	ft_move_pixel(t_master *master, int next_x, int next_y)
{	
	master->map.next_x_position = next_x;
	while (master->map.current_y_position < next_y)
	{
		mlx_pixel_put(master->window.mlx_p, master->window.win_p, master->map.next_x_position, master->map.next_y_position, 0xFFFFFF);
		master->map.current_y_position++;
	}

}


void	ft_put_pixel(t_master *master, int x, int y)
{
	int		a;
	int		b;
	int		h;
	int		w;
	char	position;

	position = 0;
	a = x; // pozycja wyjscowa x
	b = y; // pozycja wyjsciowa y
	h = y/master->map.unit_y_size; // h = pozycja w pionie, 
	w = x/master->map.unit_x_size; // w = pozycja w poziomie;
	//printf("%c\n", master->map.map[h][w]);
	if (master->map.map[h][w] == 49)
		position = 49;
	else if (master->map.map[h][w] == 'N') 
		position = 'N';
	else
		position = 0;
	while (y <= b + master->map.unit_y_size)
	{
		while (x <= a + master->map.unit_x_size)
		{
			if (position == 49)
				mlx_pixel_put(master->window.mlx_p, master->window.win_p, x, y, 0xFFFFFF);
			else if (position == 'N')
			{
				if (y <= (b + b/10) && x <= (a + a/10))
				{
					if (y == b && x == a)
					{
						master->map.current_x_position = x;
						master->map.current_y_position = y;
					}
					mlx_pixel_put(master->window.mlx_p, master->window.win_p, x, y, 0xFFFFFF);
				}
				/*else
				{
					position = 48;
					break ;
				}*/
			}
			else
				break ;
			x++;
		}	
		if (position == 48)
			break ; 
		x = a;
		y++;
	}
}

void	ft_printmap_to_window(t_master *master)
{
	int	y;
	int x;

	y = 0;
	while (y < master->map.window_height)
	{
		x = 0;
		while (x < master->map.window_width)
		{
			ft_put_pixel(master, x, y); // tutaj jest 
			x += master->map.unit_x_size;
		}
		y += master->map.unit_y_size;
	}
}

int	key_hook(int key, t_master *master)
{
	//key press and key release
	if (key == k_W)
		ft_move_pixel(master, master->map.current_x_position, master->map.current_y_position + 10);
	return (1);
}


void	ft_map_create(t_master *master)
{

	master->window.mlx_p = mlx_init();
	master->window.win_p = mlx_new_window(master->window.mlx_p, master->map.window_width, master->map.window_height, "dujuivnDUBSTEPbro?");
	master->map.unit_x_size = master->map.window_width/(master->map.longest_line - 1);
	master->map.unit_y_size =  master->map.window_height/(master->map.last_line + 1);
	mlx_hook(master->window.mlx_p, 2, 1L << 0, key_hook, master);
	ft_printmap_to_window(master);
}
