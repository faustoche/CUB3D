/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 09:20:34 by faustoche         #+#    #+#             */
/*   Updated: 2025/06/06 14:54:45 by fcrocq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static int	door_position(t_mlx *mlx, int nx, int ny)
{
	int	width;
	int	height;

	width = mlx->game->width_map;
	height = mlx->game->height_map;
	return (nx >= 0 && ny >= 0 && ny < height && nx < width
		&& mlx->game->map[ny][nx] == 'D');
}

static void	open_door(t_mlx *mlx, int nx, int ny)
{
	mlx->game->map[ny][nx] = '0';
}

void	open_door_near_player(t_mlx *mlx)
{
	int	px;
	int	py;
	int	dx[4];
	int	dy[4];
	int	i;

	init_directions(dx, dy);
	px = (int)(mlx->player->player_x / TILE_SIZE);
	py = (int)(mlx->player->player_y / TILE_SIZE);
	i = 0;
	while (i < 4)
	{
		if (door_position(mlx, px + dx[i], py + dy[i]))
		{
			open_door(mlx, px + dx[i], py + dy[i]);
			break ;
		}
		i++;
	}
}
