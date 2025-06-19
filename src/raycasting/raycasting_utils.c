/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:42:38 by fcrocq            #+#    #+#             */
/*   Updated: 2025/06/19 09:56:53 by fcrocq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* 
** Check if a cell contains a wall. Check map limits.
** Calculate distance if there's a wall
*/

float	check_collision(t_mlx *mlx, t_ray *ray, int cell_x, int cell_y)
{
	int	line_length;

	if (cell_y < 0 || cell_y >= mlx->game->height_map)
		return (-1);
	line_length = ft_strlen(mlx->game->map[cell_y]);
	if (cell_x >= 0 && cell_x < line_length
		&& mlx->game->map[cell_y][cell_x] != '0')
	{
		ray->hit_x = ray->next_x;
		ray->hit_y = ray->next_y;
		ray->hit_cell = mlx->game->map[cell_y][cell_x];
		return (cal_dist(ray->ray_x, ray->ray_y, ray->next_x, ray->next_y));
	}
	if (cell_x >= line_length)
	{
		ray->hit_x = ray->next_x;
		ray->hit_y = ray->next_y;
		ray->hit_cell = '1';
		return (cal_dist(ray->ray_x, ray->ray_y, ray->next_x, ray->next_y));
	}
	return (-1);
}
