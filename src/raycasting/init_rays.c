/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:50:34 by faustoche         #+#    #+#             */
/*   Updated: 2025/05/26 11:49:09 by fcrocq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

/*
* Savoir si le rayon va vers le bas ou le haut (horizon)
* Ou vers la gauche ou la droite (si horizon = 0)
* On peut donc placer correctement le premier point d'intersection
* Le rayon avance dans la bonne direction
* Inter = point d'intersection de la premiere ligne
*/

int	init_ray_direction(float angle, float *inter, float *step, int horizon)
{
	if (horizon)
	{
		if (angle > 0 && angle < M_PI)
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2))
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

/*
* Est-ce que le point x y est dans la carte, sur une case mur
* Renvois 1 s'il n'y a pas de mur et que le rayon peut continuer
*/

int	is_wall(float x, float y, t_mlx *mlx)
{
	int		map_x;
	int		map_y;
	char	tile;

	map_x = (int)(x / TILE_SIZE);
	map_y = (int)(y / TILE_SIZE);
	if (map_x < 0 || map_y < 0 || map_y >= mlx->game->height_map
		|| map_x >= mlx->game->width_map)
		return (1);
	tile = mlx->game->map[map_y][map_x];
	if (tile == '1' || tile == 'D')
	{
		printf("mur :%d\n", tile);
		return (1);
	}
	return (0);
}
