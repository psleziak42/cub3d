#include "../extras/hfiles/cub3d.h"

void	free_dp(char **dp)
{
	int	x;

	x = -1;
	while (dp[++x])
	{
		free(dp[x]);
		dp[x] = NULL;
	}
	free(dp);
	dp = NULL;
}

void	destroy_imgs(t_img *img, void *mlx_ptr)
{
	if (img)
	{
		mlx_destroy_image(mlx_ptr, img[BG].img_address);
		mlx_destroy_image(mlx_ptr, img[WL].img_address);
		free(img);
		img = NULL;
	}
}

void	ft_free_memory(void)
{
	int	index;

	index = -1;
	if (get_map(0)->map)
	{
		while (get_map(0)->map[index++])
		{
			free(get_map(0)->map[index]);
			get_map(0)->map[index] = NULL;
		}
		free(get_map(0)->map);
	}
}