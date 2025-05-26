/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:55:06 by fcrocq            #+#    #+#             */
/*   Updated: 2025/05/26 11:23:53 by fcrocq           ###   ########.fr       */
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

	if (!mlx || !mlx->meta || ray < 0 || ray >= WIDTH)
		return ;
	m = mlx->meta;
	i = b_pixel;
	while (i < HEIGHT)
		ft_mlx_pixel_put(mlx, ray, i++, m->f_color); // recuperation de la couleur
	i = 0;
	while (i < t_pixel)
		ft_mlx_pixel_put(mlx, ray, i++, m->c_color); // recuperation de la couleur
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


///// TO DELETE ?? ///////y

// static void	draw_wall(t_mlx *mlx, int ray, int top_pixel, int bottom_pixel)
// {
// 	int	color;

// 	color = get_color(mlx);
// 	while (top_pixel < bottom_pixel)
// 		ft_mlx_pixel_put(mlx, ray, top_pixel++, color);
// }

// static void draw_textured_wall(t_mlx *mlx, int ray, int top_pixel, int bottom_pixel)
// {
//     int			y;
//     int			tex_x;
//     int			tex_y;
//     double		step;
//     double		tex_pos;
//     int			wall_height;
//     t_texture	*texture;
// 	int			color;

//     if (mlx->ray->flag == 1) // Mur vertical
//     {
//         if (cos(mlx->ray->ray_angle) > 0)
//             texture = &mlx->game->west_texture;
//         else
//             texture = &mlx->game->east_texture;
//         tex_x = (int)(mlx->ray->next_y) % TILE_SIZE;
//     }
//     else // Mur horizontal
//     {
//         if (sin(mlx->ray->ray_angle) > 0)
//             texture = &mlx->game->north_texture;
//         else
//             texture = &mlx->game->south_texture;
//         tex_x = (int)(mlx->ray->next_x) % TILE_SIZE;
//     }
//     tex_x = (tex_x * texture->width) / TILE_SIZE;
//     wall_height = (int)((TILE_SIZE / mlx->ray->distance) * ((WIDTH / 2) / tan(mlx->player->fov_rd / 2)));
//     step = (double)texture->height / wall_height;
//     tex_pos = (top_pixel - HEIGHT / 2 + wall_height / 2) * step;
//     y = top_pixel;
//     while (y < bottom_pixel)
//     {
//         tex_y = (int)tex_pos & (texture->height - 1);
//         tex_pos += step;
// 		color = get_texture_pixel(texture, tex_x, tex_y);
//         ft_mlx_pixel_put(mlx, ray, y, color);
//         y++;
//     }
// }

