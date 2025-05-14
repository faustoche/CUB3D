/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faustoche <faustoche@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:31:14 by faustoche         #+#    #+#             */
/*   Updated: 2025/05/14 16:00:49 by faustoche        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = mlx->addr + (y * mlx->size_line + x * (mlx->bpp / 8));
	*(unsigned int *)dst = color;
}

static void draw_floor_ceiling(t_mlx *mlx, int ray, int top_pixel, int bottom_pixel)
{
	int i;

	i = bottom_pixel;
	while (i < HEIGHT)
		ft_pixel_put(mlx, ray, i++, 0x615E5EFF);
	i = 0;
	while (i < top_pixel)
		ft_pixel_put(mlx, ray, i++, 0x333D2EFF);
}

static int get_color(t_mlx *mlx)
{
	double	angle;

	angle = mlx->ray->ray_angle;
	if (mlx->ray->hit_cell == 'D')
		return 0x0000FFFF; // bleu
	angle = angle_to_radians(angle);
	if (mlx->ray->flag == 1)
	{
		if (cos(angle) > 0)
			return (0xB41248FF);
		else
			return (0xCC6699FF);
	}
	else
	{
		if (sin(angle) > 0)
			return (0x812D53FF);
		else
			return (0x35487BFF);
	}
}


static void draw_wall(t_mlx *mlx, int ray, int top_pixel, int bottom_pixel)
{
	int color;

	color = get_color(mlx);
	while (top_pixel < bottom_pixel)
		ft_pixel_put(mlx, ray, top_pixel++, color);
}

void render_wall(t_mlx *mlx, int ray)
{
	double	wall_height;
	double	bottom_pixel;
	double	top_pixel;

	wall_height = (TILE_SIZE / mlx->ray->distance) * ((WIDTH / 2) / tan(mlx->player->fov_rd / 2));
	bottom_pixel = (HEIGHT / 2) + (wall_height / 2);
	top_pixel = (HEIGHT / 2) - (wall_height / 2);
	if (bottom_pixel > HEIGHT)
		bottom_pixel = HEIGHT;
	if (top_pixel < 0)
		top_pixel = 0;
	draw_floor_ceiling(mlx, ray, top_pixel, bottom_pixel);
	draw_wall(mlx, ray, top_pixel, bottom_pixel);
}
