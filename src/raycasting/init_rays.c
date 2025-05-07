/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:50:34 by faustoche         #+#    #+#             */
/*   Updated: 2025/05/07 15:11:35 by fcrocq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_angle_direction(float angle, char c) // unit circle
{
	if (c == 'x')
	{
		if (angle > 0 && angle < M_PI) // droite ou gauche
			return (1);
	}
	else if (c == 'y')
	{
		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2) // haut ou bas
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

int	init_ray_direction(float angle, float *inter, float *step, int horizon) // inter check
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

int	is_wall(float x, float y, t_mlx *mlx) // wall hit
{
	int	x_map;
	int	y_map;

	if (x < 0 || y < 0)
		return (0);
	x_map = floor(x / TILE_SIZE); // recupere la position x
	y_map = floor(y / TILE_SIZE); // recupere la position y
	if (x < 0 || y < 0 || y_map >= mlx->game->height_map || x_map >= mlx->game->width_map)
		return (1);
	if (!mlx->game->map[y_map] || x_map >= (int)ft_strlen(mlx->game->map[y_map]))
		return (1);
	return (mlx->game->map[y_map][x_map] == '1');
}
