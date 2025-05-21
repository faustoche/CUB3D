/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faustoche <faustoche@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 22:50:11 by faustoche         #+#    #+#             */
/*   Updated: 2025/05/21 22:51:27 by faustoche        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_texture *select_wall_texture(t_ray *ray, t_game *game)
{
    if (ray->flag == 1) // Mur vertical
    {
        if (cos(ray->ray_angle) > 0)
            return &game->west_texture;
        else
            return &game->east_texture;
    }
    else // Mur horizontal
    {
        if (sin(ray->ray_angle) > 0)
            return &game->north_texture;
        else
            return &game->south_texture;
    }
}

static int calculate_wall_height(t_ray *ray, t_player *player)
{
    return (int)((TILE_SIZE / ray->distance) * 
            ((WIDTH / 2) / tan(player->fov_rd / 2)));
}

static void draw_wall_portion(t_mlx *mlx, int ray_num, int top, int bottom)
{
    t_texture	*texture;
    int		tex_x;
    int		tex_y;
    double	step;
    double	tex_pos;
	int		y;
	int		wall_height;

    texture = select_wall_texture(mlx->ray, mlx->game);
    if (mlx->ray->flag == 1)
        tex_x = (int)(mlx->ray->next_y) % TILE_SIZE;
    else
        tex_x = (int)(mlx->ray->next_x) % TILE_SIZE;
    tex_x = (tex_x * texture->width) / TILE_SIZE;
    wall_height = calculate_wall_height(mlx->ray, mlx->player);
    step = (double)texture->height / wall_height;
    tex_pos = (top - HEIGHT / 2 + wall_height / 2) * step;
    y = top;
    while (y < bottom)
    {
        tex_y = (int)tex_pos & (texture->height - 1);
        tex_pos += step;
        ft_mlx_pixel_put(mlx, ray_num, y, get_texture_pixel(texture, tex_x, tex_y));
        y++;
    }
}

static void draw_textured_wall(t_mlx *mlx, int ray, int top_pixel, int bottom_pixel)
{
    draw_wall_portion(mlx, ray, top_pixel, bottom_pixel);
}