/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:57:52 by fcrocq            #+#    #+#             */
/*   Updated: 2025/06/06 16:14:40 by fcrocq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static int	get_base_text(t_ray *ray, t_texture *texture)
// {
// 	double	wall_x;
// 	int		tex_x;

// 	if (ray->flag == 1)
// 		wall_x = ray->hit_y;
// 	else
// 		wall_x = ray->hit_x;
// 	wall_x /= TILE_SIZE;
// 	wall_x -= floor(wall_x);
// 	tex_x = (int)(wall_x * texture->width);
// 	return (tex_x);
// }

// static int	tex_x_bounds(int tex_x, int width)
// {
// 	if (tex_x < 0)
// 		tex_x = 0;
// 	if (tex_x >= width)
// 		tex_x = width - 1;
// 	return (tex_x);
// }

// static int	fix_tex_side(t_ray *ray, int tex_x, int width)
// {
// 	int	flip;

// 	flip = ((ray->flag == 0 && sin(ray->ray_angle) > 0)
// 			|| (ray->flag == 1 && cos(ray->ray_angle) < 0));
// 	if (flip)
// 		tex_x = width - tex_x - 1;
// 	return (tex_x);
// }

// void	draw_wall_slice(t_mlx *mlx, int ray_num, int tex_x, t_wall *wall)
// {
// 	while (wall->y < wall->bottom)
// 	{
// 		wall->tex_y = (int)(wall->tex_pos);
// 		if (wall->tex_y < 0)
// 			wall->tex_y = 0;
// 		else if (wall->tex_y >= wall->texture->height)
// 			wall->tex_y = wall->texture->height - 1;
// 		ft_mlx_pixel_put(mlx, ray_num, wall->y, get_tex_pix(wall->texture, tex_x, wall->tex_y));
// 		wall->tex_pos += wall->step;
// 		wall->y++;
// 	}
// }

// void	render_wall_column(t_mlx *mlx, int ray_num, int tex_x, int top)
// {
// 	t_wall	wall;
// 	int			wall_height;

// 	wall.top = top;
// 	wall.bottom = HEIGHT;
// 	wall.texture = select_wall_texture(mlx->ray, mlx->game);
// 	wall_height = calculate_wall_height(mlx->ray, mlx->player);
// 	wall.step = (double)wall.texture->height / wall_height;
// 	wall.tex_pos = (wall.top - HEIGHT / 2 + wall_height / 2) * wall.step;
// 	wall.y = wall.top;
// 	draw_wall_slice(mlx, ray_num, tex_x, &wall);
// }

// void	draw_wall_portion(t_mlx *mlx, int ray_num, int top)
// {
// 	t_texture	*texture;
// 	int			tex_x;

// 	texture = select_wall_texture(mlx->ray, mlx->game);
// 	tex_x = get_base_text(mlx->ray, texture);
// 	tex_x = fix_tex_side(mlx->ray, tex_x, texture->width);
// 	tex_x = tex_x_bounds(tex_x, texture->width);
// 	render_wall_column(mlx, ray_num, tex_x, top);
// }
