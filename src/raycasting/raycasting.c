/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:42:46 by faustoche         #+#    #+#             */
/*   Updated: 2025/06/05 12:13:42 by fcrocq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	walk_intersection(t_mlx *mlx, int is_horizontal)
{
	t_ray	*ray;
	int		cell_y;
	int		cell_x;

	ray = mlx->ray;
	if (is_horizontal && ray->sin_a < 0)
		ray->next_y -= 0.001;
	else if (!is_horizontal && ray->cos_a < 0)
		ray->next_x -= 0.001;
	while (ray->next_x >= 0 && ray->next_x < mlx->game->width_map * TILE_SIZE
		&& ray->next_y >= 0 && ray->next_y < mlx->game->height_map * TILE_SIZE)
	{
		cell_x = ray->next_x / TILE_SIZE;
		cell_y = ray->next_y / TILE_SIZE;
		if (cell_y >= 0 && cell_y < mlx->game->height_map
			&& cell_x >= 0 && cell_x < mlx->game->width_map
			&& mlx->game->map[cell_y][cell_x] != '0')
		{
			ray->hit_x = ray->next_x;
			ray->hit_y = ray->next_y;
			ray->hit_cell = mlx->game->map[cell_y][cell_x];
			return (cal_dist(ray->ray_x, ray->ray_y, ray->next_x, ray->next_y));
		}
		ray->next_x += ray->dx;
		ray->next_y += ray->dy;
	}
	return (INFINITY);
}

float	check_horizontal(t_mlx *mlx, float sin_a, float cos_a, int map_y)
{
	float	y_intercept;
	float	x_intercept;
	t_ray	*ray;

	ray = mlx->ray;
	if (sin_a == 0)
		return (INFINITY);
	ray->ray_x = mlx->player->player_x;
	ray->ray_y = mlx->player->player_y;
	if (sin_a > 0)
	{
		y_intercept = (map_y + 1) * TILE_SIZE;
		ray->dy = TILE_SIZE;
	}
	else
	{
		y_intercept = map_y * TILE_SIZE - 0.001;
		ray->dy = -TILE_SIZE;
	}
	x_intercept = ray->ray_x + (y_intercept - ray->ray_y) / sin_a * cos_a;
	ray->dx = ray->dy / sin_a * cos_a;
	ray->next_x = x_intercept;
	ray->next_y = y_intercept;
	return (walk_intersection(mlx, 1));
}

float	check_vertical(t_mlx *mlx, float sin_a, float cos_a, int map_x)
{
	float	y_intercept;
	float	x_intercept;
	t_ray	*ray;

	ray = mlx->ray;
	if (cos_a == 0)
		return (INFINITY);
	ray->ray_x = mlx->player->player_x;
	ray->ray_y = mlx->player->player_y;
	if (cos_a > 0)
	{
		x_intercept = (map_x + 1) * TILE_SIZE;
		ray->dx = TILE_SIZE;
	}
	else
	{
		x_intercept = map_x * TILE_SIZE - 0.001;
		ray->dx = -TILE_SIZE;
	}
	y_intercept = ray->ray_y + (x_intercept - ray->ray_x) / cos_a * sin_a;
	ray->dy = ray->dx / cos_a * sin_a;
	ray->next_x = x_intercept;
	ray->next_y = y_intercept;
	return (walk_intersection(mlx, 0));
}

static float	cast_ray(t_mlx *mlx, float angle)
{
	float	h_dist;
	float	v_dist;
	int		map_x;
	int		map_y;

	mlx->ray->sin_a = sin(angle);
	mlx->ray->cos_a = cos(angle);
	mlx->ray->ray_x = mlx->player->player_x;
	mlx->ray->ray_y = mlx->player->player_y;
	map_x = mlx->ray->ray_x / TILE_SIZE;
	map_y = mlx->ray->ray_y / TILE_SIZE;
	h_dist = check_horizontal(mlx, mlx->ray->sin_a, mlx->ray->cos_a, map_y);
	v_dist = check_vertical(mlx, mlx->ray->sin_a, mlx->ray->cos_a, map_x);
	if (v_dist < h_dist)
	{
		mlx->ray->flag = 1;
		mlx->ray->distance = v_dist;
		return (v_dist);
	}
	else
	{
		mlx->ray->flag = 0;
		mlx->ray->distance = h_dist;
		return (h_dist);
	}
}

void	cast_rays(t_mlx *mlx)
{
	float	angle;
	int		ray;
	float	ray_angle;

	angle = mlx->player->angle - (mlx->player->fov_rd / 2.0);
	ray = 0;
	while (ray < WIDTH)
	{
		ray_angle = angle_to_radians(angle);
		mlx->ray->ray_angle = ray_angle;
		mlx->ray->distance = cast_ray(mlx, ray_angle);
		mlx->ray->distance *= cos(ray_angle - mlx->player->angle);
		render_wall(mlx, ray);
		angle += mlx->player->fov_rd / (double)WIDTH;
		ray++;
	}
}
