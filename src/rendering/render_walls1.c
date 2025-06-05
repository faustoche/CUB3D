/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 22:50:11 by faustoche         #+#    #+#             */
/*   Updated: 2025/06/05 16:31:53 by fcrocq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_texture	*select_wall_texture(t_ray *ray, t_game *game)
{
	if (ray->flag == 1)
	{
		if (cos(ray->ray_angle) > 0)
			return (&game->east_texture);
		else
			return (&game->west_texture);
	}
	else
	{
		if (sin(ray->ray_angle) < 0)
			return (&game->south_texture);
		else
			return (&game->north_texture);
	}
}

static int	calculate_wall_height(t_ray *ray, t_player *player)
{
	return ((int)((TILE_SIZE / ray->distance)
		* ((WIDTH / 2) / tan(player->fov_rd / 2))));
}

static void	draw_wall_portion(t_mlx *mlx, int ray_num, int top, int bottom)
{
	t_texture	*texture;
	int			tex_x;
	int			tex_y;
	double		step;
	double		tex_pos;
	int			y;
	int			wall_height;
	double		wall_x;

	texture = select_wall_texture(mlx->ray, mlx->game);
	if (mlx->ray->flag == 1)
		wall_x = mlx->ray->hit_y;
	else
		wall_x = mlx->ray->hit_x;
	wall_x /= TILE_SIZE;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * texture->width);
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	if ((mlx->ray->flag == 0 && sin(mlx->ray->ray_angle) > 0)
		|| (mlx->ray->flag == 1 && cos(mlx->ray->ray_angle) < 0))
		tex_x = texture->width - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	wall_height = calculate_wall_height(mlx->ray, mlx->player);
	step = (double)texture->height / wall_height;
	tex_pos = (top - HEIGHT / 2 + wall_height / 2) * step;
	y = top;
	while (y < bottom)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		else if (tex_y >= texture->height)
			tex_y = texture->height - 1;
		tex_pos += step;
		ft_mlx_pixel_put(mlx, ray_num, y, get_texture_pixel(texture, tex_x, tex_y));
		y++;
	}
}

void	draw_textured_wall(t_mlx *mlx, int ray, int top_pixel, int bottom_pixel)
{
	draw_wall_portion(mlx, ray, top_pixel, bottom_pixel);
}
