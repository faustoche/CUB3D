/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:50:34 by faustoche         #+#    #+#             */
/*   Updated: 2025/06/19 10:34:34 by fcrocq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Check north/south/east/west direction for angle with PI */

int	check_angle_direction(float angle, char c)
{
	if (c == 'x')
	{
		if (angle > 0 && angle < M_PI)
			return (1);
	}
	else if (c == 'y')
	{
		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
			return (1);
	}
	return (0);
}

/* Check for collision, if there's a wall */

int	is_wall(float x, float y, t_mlx *mlx)
{
	int		map_x;
	int		map_y;
	char	tile;
	int		line_length;

	map_x = (int)(x / TILE_SIZE);
	map_y = (int)(y / TILE_SIZE);
	if (map_x < 0 || map_y < 0 || map_y >= mlx->game->height_map)
		return (1);
	line_length = ft_strlen(mlx->game->map[map_y]);
	if (map_x >= line_length)
		return (1);
	tile = mlx->game->map[map_y][map_x];
	if (tile == '1' || tile == 'D')
		return (1);
	return (0);
}

/* To keep angle between 0 and PI */

float	angle_to_radians(float angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

/* Calculate euclidian between 2 points using Pythagoras' theorem 
* Sqrt: calcule la racine carré de la valeur passée en paramètre
*/

float	cal_dist(float x1, float y1, float x2, float y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

/* Initiate structures with angle and calculate sin/cos value */

void	init_rays(t_ray *h_ray, t_ray *v_ray, t_mlx *mlx, float angle)
{
	h_ray->ray_angle = angle;
	v_ray->ray_angle = angle;
	h_ray->sin_a = sin(angle);
	h_ray->cos_a = cos(angle);
	v_ray->sin_a = h_ray->sin_a;
	v_ray->cos_a = h_ray->cos_a;
	h_ray->ray_x = mlx->player->player_x;
	h_ray->ray_y = mlx->player->player_y;
	v_ray->ray_x = mlx->player->player_x;
	v_ray->ray_y = mlx->player->player_y;
}
