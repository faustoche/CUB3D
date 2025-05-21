
#include "cub3d.h"

void	ft_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = mlx->addr + (y * mlx->size_line + x * (mlx->bpp / 8));
	*(unsigned int *)dst = color;
}

static void	draw_floor_ceiling(t_mlx *mlx, int ray, int t_pixel, int b_pixel)
{
	int	i;

	i = b_pixel;
	while (i < HEIGHT)
		ft_mlx_pixel_put(mlx, ray, i++, 0x6699CC);
	i = 0;
	while (i < t_pixel)
		ft_mlx_pixel_put(mlx, ray, i++, 0x99CCFF);
}

static int	get_color(t_mlx *mlx)
{
	double	angle;

	angle = mlx->ray->ray_angle;
	if (mlx->ray->hit_cell == 'D')
		return (0x0000FFFF);
	angle = angle_to_radians(angle);
	if (mlx->ray->flag == 1)
	{
		if (cos(angle) > 0)
			return (0xCCCC00);
		else
			return (0xFF6699);
	}
	else
	{
		if (sin(angle) > 0)
			return (0xFFCCFF);
		else
			return (0xFFFFCC);
	}
}

static void	draw_wall(t_mlx *mlx, int ray, int top_pixel, int bottom_pixel)
{
	int	color;

	color = get_color(mlx);
	while (top_pixel < bottom_pixel)
		ft_mlx_pixel_put(mlx, ray, top_pixel++, color);
}

void	render_wall(t_mlx *mlx, int ray)
{
	double	wall_height;
	double	bottom_pixel;
	double	top_pixel;

	wall_height = (TILE_SIZE / mlx->ray->distance) * ((WIDTH / 2)
			/ tan(mlx->player->fov_rd / 2));
	bottom_pixel = (HEIGHT / 2) + (wall_height / 2);
	top_pixel = (HEIGHT / 2) - (wall_height / 2);
	if (bottom_pixel > HEIGHT)
		bottom_pixel = HEIGHT;
	if (top_pixel < 0)
		top_pixel = 0;
	draw_floor_ceiling(mlx, ray, top_pixel, bottom_pixel);
	draw_wall(mlx, ray, top_pixel, bottom_pixel);
}
