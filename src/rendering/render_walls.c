/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faustoche <faustoche@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:31:14 by faustoche         #+#    #+#             */
/*   Updated: 2025/05/06 18:36:25 by faustoche        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_mlx_pixel_put(t_mlx *mlx, int x, int y, int color) // le pixel put de la mlx ?
{
	if (x < 0)
		return ;
	else if (x >= WIDTH)
		return ;
	if (y < 0)
		return ;
	else if (y >= HEIGHT)
		return ;
	ft_mlx_pixel_put(mlx->img, x, y, color);
}

void	draw_floor_ceiling(t_mlx *mlx, int ray, int top_pixel, int bottom_pixel)
{
	int	i;
	int	c;

	i = bottom_pixel;
	while (i < HEIGHT)
		ft_mlx_pixel_put(mlx, ray, i++, 0xB99470FF);
	i = 0;
	while (i < top_pixel)
		ft_mlx_pixel_put(mlx, ray, i++, 0x89CFF3FF);
}

int	get_color(t_mlx *mlx, int flag)
{
	mlx->ray->ray_angle = angle_to_radians(mlx->ray->ray_angle);
	if (flag == 0)
	{
		if (mlx->ray->ray_angle > M_PI / 2 && mlx->ray->ray_angle < 3 * (M_PI / 2))
			return (0xB5B5B5FF);
		else
			return (0xB5B5B5FF);
	}
	else
	{
		if (mlx->ray->ray_angle > 0 && mlx->ray->ray_angle < M_PI)
			return (0xF5F5F5FF);
		else
			return (0xF5F5F5FF);
	}
}

void	draw_wall(t_mlx *mlx, int ray, int top_pixel, int bottom_pixel)
{
	int	color;

	color = get_color(mlx, mlx->ray->flag);
	while (top_pixel < bottom_pixel)
		ft_mlx_pixel_put(mlx, ray, top_pixel++, color);
}

void	render_wall(t_mlx *mlx, int ray)
{
	double	wall_height;
	double	bottom_pixel;
	double	top_pixel;

	mlx->ray->distance *= cos(angle_to_radians(mlx->ray->ray_angle - mlx->player->angle)); // fix l'effet fish eye
	wall_height = (TILE_SIZE / mlx->ray->distance) * ((WIDTH / 2) / tan(mlx->player->fov_rd / 2));
	bottom_pixel = (HEIGHT / 2) + (wall_height / 2);
	top_pixel = (HEIGHT / 2) - (wall_height / 2);
	if (bottom_pixel > HEIGHT)
		bottom_pixel = HEIGHT;
	if (top_pixel < 0)
		top_pixel = 0;
	draw_wall(mlx, ray, top_pixel, bottom_pixel);
	draw_floor_ceiling(mlx, ray, top_pixel, bottom_pixel);
}
