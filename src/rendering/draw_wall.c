/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:57:52 by fcrocq            #+#    #+#             */
/*   Updated: 2025/06/16 10:12:46 by fcrocq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	calculate_tex_x(t_ray *ray, t_texture *texture)
{
	double	wall_x;
	int		tex_x;

	if (ray->flag == 1)
		wall_x = ray->hit_y;
	else
		wall_x = ray->hit_x;
	wall_x /= TILE_SIZE;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * texture->width);
	return (tex_x);
}

static int	apply_tex_x_corrections(int tex_x, t_ray *ray, t_texture *texture)
{
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	if ((ray->flag == 0 && sin(ray->ray_angle) > 0)
		|| (ray->flag == 1 && cos(ray->ray_angle) < 0))
		tex_x = texture->width - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	return (tex_x);
}

static void	init_texture_data(t_tex_data *data, t_mlx *mlx, int top)
{
	int	wall_height;

	data->texture = select_wall_texture(mlx->ray, mlx->game);
	data->tex_x = calculate_tex_x(mlx->ray, data->texture);
	data->tex_x = apply_tex_x_corrections(data->tex_x, mlx->ray, data->texture);
	wall_height = calculate_wall_height(mlx->ray, mlx->player);
	data->step = (double)data->texture->height / wall_height;
	data->tex_pos = (top - HEIGHT / 2 + wall_height / 2) * data->step;
}

static void	draw_texture_line(t_mlx *mlx, t_tex_data *data, int ray_num, int y)
{
	int	tex_y;

	tex_y = (int)data->tex_pos;
	if (tex_y < 0)
		tex_y = 0;
	else if (tex_y >= data->texture->height)
		tex_y = data->texture->height - 1;
	data->tex_pos += data->step;
	ft_mlx_pixel_put(mlx, ray_num, y,
		get_tex_pix(data->texture, data->tex_x, tex_y));
}

void	draw_wall_portion(t_mlx *mlx, int ray_num, int top, int bottom)
{
	t_tex_data	tex_data;
	int			y;

	init_texture_data(&tex_data, mlx, top);
	y = top;
	while (y < bottom)
	{
		draw_texture_line(mlx, &tex_data, ray_num, y);
		y++;
	}
}
