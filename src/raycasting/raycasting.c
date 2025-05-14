/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faustoche <faustoche@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:42:46 by faustoche         #+#    #+#             */
/*   Updated: 2025/05/14 15:59:55 by faustoche        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static float calculate_distance(float x1, float y1, float x2, float y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

static float check_horizontal_intersection(t_mlx *mlx, float ray_x, float ray_y, float sinA, float cosA)
{
	int		map_y;
	float	y_intercept;
	float	dy;
	float	x_intercept;
	float	dx;
	float	next_x;
	float	next_y;
	int		cell_y;
	int		cell_x;

	if (sinA == 0)
		return (INFINITY);
	map_y = ray_y / TILE_SIZE;
	y_intercept = (sinA > 0) ? (map_y + 1) * TILE_SIZE : map_y * TILE_SIZE;
	dy = (sinA > 0) ? TILE_SIZE : -TILE_SIZE;
	x_intercept = ray_x + (y_intercept - ray_y) / sinA * cosA;
	dx = dy / sinA * cosA;
	next_x = x_intercept;
	next_y = y_intercept;
	if (sinA < 0)
		next_y -= 0.001;
	while (next_x >= 0 && next_x < mlx->game->width_map * TILE_SIZE &&
		   next_y >= 0 && next_y < mlx->game->height_map * TILE_SIZE)
	{
		cell_x = next_x / TILE_SIZE;
		cell_y = next_y / TILE_SIZE;
		if (cell_y >= 0 && cell_y < mlx->game->height_map &&
			cell_x >= 0 && cell_x < mlx->game->width_map &&
			mlx->game->map[cell_y][cell_x] != '0')
		{
			mlx->ray->hit_cell = mlx->game->map[cell_y][cell_x];
			return (calculate_distance(ray_x, ray_y, next_x, next_y));
		}
		next_x += dx;
		next_y += dy;
	}
	return (INFINITY);
}


static float check_vertical_intersection(t_mlx *mlx, float ray_x, float ray_y, float sinA, float cosA)
{
	int		map_x;
	float	y_intercept;
	float	dy;
	float	x_intercept;
	float	dx;
	float	next_x;
	float	next_y;
	int		cell_y;
	int		cell_x;
	
	if (cosA == 0)
		return (INFINITY);
	map_x = ray_x / TILE_SIZE;
	x_intercept = (cosA > 0) ? (map_x + 1) * TILE_SIZE : map_x * TILE_SIZE;
	dx = (cosA > 0) ? TILE_SIZE : -TILE_SIZE;
	y_intercept = ray_y + (x_intercept - ray_x) / cosA * sinA;
	dy = dx / cosA * sinA;
	next_x = x_intercept;
	next_y = y_intercept;
	if (cosA < 0)
		next_x -= 0.001;
	while (next_x >= 0 && next_x < mlx->game->width_map * TILE_SIZE
			&& next_y >= 0 && next_y < mlx->game->height_map * TILE_SIZE)
	{
		cell_x = next_x / TILE_SIZE;
		cell_y = next_y / TILE_SIZE;
		if (cell_y >= 0 && cell_y < mlx->game->height_map
			&& cell_x >= 0 && cell_x < mlx->game->width_map
			&& mlx->game->map[cell_y][cell_x] != '0')
		{
			mlx->ray->hit_cell = mlx->game->map[cell_y][cell_x];
			return (calculate_distance(ray_x, ray_y, next_x, next_y));
		}
		next_x += dx;
		next_y += dy;
	}
	return (INFINITY);
}

static float cast_ray(t_mlx *mlx, float angle)
{
	float	sinA;
	float	cosA;
	float	ray_x;
	float	ray_y;
	float	h_dist;
	float	v_dist;
	
	sinA = sin(angle);
	cosA = cos(angle);
	ray_x = mlx->player->player_x;
	ray_y = mlx->player->player_y;
	h_dist = check_horizontal_intersection(mlx, ray_x, ray_y, sinA, cosA);
	v_dist = check_vertical_intersection(mlx, ray_x, ray_y, sinA, cosA);
	if (v_dist < h_dist)
	{
		mlx->ray->flag = 1; // Vertical wall
		return (v_dist);
	}
	else
	{
		mlx->ray->flag = 0; // Horizontal wall
		return (h_dist);
	}
}

void cast_rays(t_mlx *mlx)
{
	float   angle;
	int     ray;
	float	ray_angle;

	angle = mlx->player->angle - (mlx->player->fov_rd / 2.0);
	ray = 0;
	while (ray < WIDTH)
	{
		ray_angle = angle_to_radians(angle);
		mlx->ray->ray_angle = ray_angle;
		mlx->ray->distance = cast_ray(mlx, ray_angle); // distance avec le rayon
		mlx->ray->distance *= cos(ray_angle - mlx->player->angle); // correction fisheye
		render_wall(mlx, ray);
		angle += mlx->player->fov_rd / (double)WIDTH;
		ray++;
	}
}
