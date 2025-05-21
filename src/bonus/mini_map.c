/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 09:25:46 by faustoche         #+#    #+#             */
/*   Updated: 2025/05/20 15:24:11 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void draw_direction_ray(t_mlx *mlx, int minimap_center_x, int minimap_center_y, double angle)
{
	double	ray_x;
	double	ray_y;
	double	dx;
	double	dy;
	int		i;
	int		map_x;
	int		map_y;
	int		draw_x;
	int		draw_y;
	double	offset_x;
	double	offset_y;

	i = 0;
	ray_x = (double)(mlx->player->player_x);
	ray_y = (double)(mlx->player->player_y);
	dx = cos(angle) * 2.0;
	dy = sin(angle) * 2.0;
	while (i < 200) // 200 étapes = ~distance max du rayon
	{
		ray_x += dx;
		ray_y += dy;
		map_x = (int)(ray_x / TILE_SIZE);
		map_y = (int)(ray_y / TILE_SIZE);
		if (map_x < 0 || map_y < 0 || map_x >= mlx->game->width_map || map_y >= mlx->game->height_map)
			break;
		if (mlx->game->map[map_y][map_x] == '1')
			break;
		offset_x = (ray_x - mlx->player->player_x) / TILE_SIZE * MINIMAP_TILE;
		offset_y = (ray_y - mlx->player->player_y) / TILE_SIZE * MINIMAP_TILE;
		draw_x = minimap_center_x + (int)offset_x;
		draw_y = minimap_center_y - (int)offset_y;
		mlx_pixel_put(mlx, draw_x, draw_y, RAY_COLOR);
		i++;
	}
}

void draw_minimap(t_mlx *mlx)
{
	char	tile;
	int		color;
	int		px;
	int		py;
	int		minimap_height;
	int		minimap_origin_y;
	int		minimap_origin_x;
	int		dy;
	int		dx;
	int		map_x;
	int		map_y;
	int		screen_x;
	int		screen_y;
	int		x;
	int		y;
	int		player_size;
	int		center_x;
	int		center_y;

	minimap_height = (2 * MINIMAP_RADIUS + 1) * MINIMAP_TILE;
	minimap_origin_y = 880 - minimap_height / 2;
	minimap_origin_x = 10; // position fixe de la minimap en haut à gauche
	px = mlx->player->player_x / TILE_SIZE;
	py = mlx->player->player_y / TILE_SIZE;
	dy = -MINIMAP_RADIUS_Y;
	dx = -MINIMAP_RADIUS_X;
	while (dy <= MINIMAP_RADIUS_Y)
	{
		while (dx <= MINIMAP_RADIUS_X)
		{
			map_x = px + dx;
			map_y = py + dy;
			if (map_x < 0 || map_y < 0 || map_y >= mlx->game->height_map || map_x >= mlx->game->width_map)
				color = EMPTY_COLOR;
			else
			{
				tile = mlx->game->map[map_y][map_x];
				if (tile == 'E')  // Si c'est une porte
					color = 0x0000FFFF;  // Bleu pour la porte
				else
					color = (tile == '1') ? WALL_COLOR : FLOOR_COLOR;
			}
			screen_x = minimap_origin_x + (dx + MINIMAP_RADIUS) * MINIMAP_TILE;
			screen_y = minimap_origin_y + ( MINIMAP_RADIUS - dy) * MINIMAP_TILE;
			y = 0;
			while (y < MINIMAP_TILE)
			{
				x = 0;
				while (x < MINIMAP_TILE)
				{
					mlx_pixel_put(mlx, screen_x + x, screen_y + y, color);
					x++;
				}
				y++;
			}
			dx++;
		}
		dy++;
	}
	player_size = MINIMAP_TILE / 2;
	center_x = minimap_origin_x + MINIMAP_RADIUS * MINIMAP_TILE;
	center_y = minimap_origin_y + MINIMAP_RADIUS * MINIMAP_TILE;
	y = -player_size / 2;
	while (y <= player_size / 2)
	{
		x = -player_size / 2;
		while (x <= player_size / 2)
		{
			mlx_pixel_put(mlx, center_x + x, center_y + y, PLAYER_COLOR);
			x++;
		}
		y++;
	}
	draw_direction_ray(mlx, center_x, center_y, mlx->player->angle);
	//char *dir_text = get_direction_text(angle);
   //mlx_string_put(mlx->ptr, mlx->win, minimap_origin_x, minimap_origin_y - 20, 0xFFFFFF, (char *)dir_text);
}

// char *get_direction_text(double angle)
// {
//     while (angle < 0) angle += 2 * M_PI;
//     while (angle >= 2 * M_PI) angle -= 2 * M_PI;

//     if (angle >= 7 * M_PI / 4 || angle < M_PI / 8)
//         return "EST";
//     else if (angle >= M_PI / 8 && angle < 3 * M_PI / 8)
//         return "NORD-EST";
//     else if (angle >= 3 * M_PI / 8 && angle < 5 * M_PI / 8)
//         return "NORD";
//     else if (angle >= 5 * M_PI / 8 && angle < 7 * M_PI / 8)
//         return "NORD-OUEST";
//     else if (angle >= 7 * M_PI / 8 && angle < 9 * M_PI / 8)
//         return "OUEST";
//     else if (angle >= 9 * M_PI / 8 && angle < 11 * M_PI / 8)
//         return "SUD-OUEST";
//     else if (angle >= 11 * M_PI / 8 && angle < 13 * M_PI / 8)
//         return "SUD";
//     else
//         return "SUD-EST";
// }
