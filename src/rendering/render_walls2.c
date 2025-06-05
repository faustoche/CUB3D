/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:55:06 by fcrocq            #+#    #+#             */
/*   Updated: 2025/06/05 16:29:17 by fcrocq           ###   ########.fr       */
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

static void	draw_floor_ceiling(t_mlx *mlx, int ray, int t_pixel, int b_pixel)
{
	int		i;
	t_meta	*m;

	if (!mlx || ray < 0 || ray >= WIDTH)
		return ;
	m = &mlx->game->meta;
	i = b_pixel;
	while (i < HEIGHT)
		ft_mlx_pixel_put(mlx, ray, i++, m->f_color);
	i = 0;
	while (i < t_pixel)
		ft_mlx_pixel_put(mlx, ray, i++, m->c_color);
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
	draw_textured_wall(mlx, ray, top_pixel, bottom_pixel);
}
