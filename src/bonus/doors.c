/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 09:20:34 by faustoche         #+#    #+#             */
/*   Updated: 2025/06/19 10:44:02 by fcrocq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	init_directions(int dx[4], int dy[4])
{
	dx[0] = 0;
	dx[1] = 2;
	dx[2] = 0;
	dx[3] = -2;
	dy[0] = -2;
	dy[1] = 0;
	dy[2] = 2;
	dy[3] = 0;
}

/* Check if there's a door on the map */

static int	door_position(t_mlx *mlx, int nx, int ny)
{
	int	width;
	int	height;

	width = mlx->game->width_map;
	height = mlx->game->height_map;
	return (nx >= 0 && ny >= 0 && ny < height && nx < width
		&& mlx->game->map[ny][nx] == 'D');
}
