/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faustoche <faustoche@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:42:46 by faustoche         #+#    #+#             */
/*   Updated: 2025/05/13 20:34:29 by faustoche        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float calculate_distance(float x1, float y1, float x2, float y2)
{
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

float check_horizontal_intersection(t_mlx *mlx, float ray_x, float ray_y, float sinA, float cosA)
{
	if (sinA == 0) return INFINITY;

	int map_y = ray_y / TILE_SIZE;
	float y_intercept = (sinA > 0) ? (map_y + 1) * TILE_SIZE : map_y * TILE_SIZE;
	float dy = (sinA > 0) ? TILE_SIZE : -TILE_SIZE;
	float x_intercept = ray_x + (y_intercept - ray_y) / sinA * cosA;
	float dx = dy / sinA * cosA;
	float next_x = x_intercept;
	float next_y = y_intercept;
	if (sinA < 0) next_y -= 0.001;
	while (next_x >= 0 && next_x < mlx->game->width_map * TILE_SIZE &&
		   next_y >= 0 && next_y < mlx->game->height_map * TILE_SIZE) {
		int cell_x = next_x / TILE_SIZE;
		int cell_y = next_y / TILE_SIZE;
		if (cell_y >= 0 && cell_y < mlx->game->height_map &&
			cell_x >= 0 && cell_x < mlx->game->width_map &&
			mlx->game->map[cell_y][cell_x] == '1') {
			return calculate_distance(ray_x, ray_y, next_x, next_y);
		}
		next_x += dx;
		next_y += dy;
	}
	return INFINITY;
}

float check_vertical_intersection(t_mlx *mlx, float ray_x, float ray_y, float sinA, float cosA) {
	if (cosA == 0) return INFINITY;

	int map_x = ray_x / TILE_SIZE;
	float x_intercept = (cosA > 0) ? (map_x + 1) * TILE_SIZE : map_x * TILE_SIZE;
	float dx = (cosA > 0) ? TILE_SIZE : -TILE_SIZE;
	float y_intercept = ray_y + (x_intercept - ray_x) / cosA * sinA;
	float dy = dx / cosA * sinA;

	float next_x = x_intercept;
	float next_y = y_intercept;

	if (cosA < 0) next_x -= 0.001;

	while (next_x >= 0 && next_x < mlx->game->width_map * TILE_SIZE &&
		   next_y >= 0 && next_y < mlx->game->height_map * TILE_SIZE) {
		int cell_x = next_x / TILE_SIZE;
		int cell_y = next_y / TILE_SIZE;

		if (cell_y >= 0 && cell_y < mlx->game->height_map &&
			cell_x >= 0 && cell_x < mlx->game->width_map &&
			mlx->game->map[cell_y][cell_x] == '1') {
			return calculate_distance(ray_x, ray_y, next_x, next_y);
		}

		next_x += dx;
		next_y += dy;
	}

	return INFINITY;
}

float cast_ray(t_mlx *mlx, float angle) {
	float sinA = sin(angle);
	float cosA = cos(angle);

	float ray_x = mlx->player->player_x;
	float ray_y = mlx->player->player_y;

	float h_dist = check_horizontal_intersection(mlx, ray_x, ray_y, sinA, cosA);
	float v_dist = check_vertical_intersection(mlx, ray_x, ray_y, sinA, cosA);

	if (v_dist < h_dist) {
		mlx->ray->flag = 1; // Vertical wall
		return v_dist;
	} else {
		mlx->ray->flag = 0; // Horizontal wall
		return h_dist;
	}
}

/* Cette fonction affiche les rayons en ligne droite donc pas de murs */


void cast_rays(t_mlx *mlx)
{
	float angle;
	int ray;
	
	angle = mlx->player->angle - (mlx->player->fov_rd / 2.0);
	ray = 0;
	while (ray < WIDTH)
	{
		float ray_angle = angle_to_radians(angle);
		mlx->ray->ray_angle = ray_angle;
		
		// Obtenir la distance avec le rayon
		mlx->ray->distance = cast_ray(mlx, ray_angle);
		
		// Corriger l'effet fisheye
		mlx->ray->distance *= cos(ray_angle - mlx->player->angle);
		
		printf("Ray %d: angle=%.2f, distance=%.2f, flag=%d\n", 
		ray, mlx->ray->ray_angle * 180 / M_PI, mlx->ray->distance, mlx->ray->flag);
		render_wall(mlx, ray);
		
		angle += mlx->player->fov_rd / (double)WIDTH;
		ray++;
	}
}
