/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:54:37 by fcrocq            #+#    #+#             */
/*   Updated: 2025/06/06 14:38:30 by fcrocq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_player(t_mlx *mlx, int i)
{
	if (i == 1)
	{
		mlx->player->angle += ROTATION_SPEED;
		if (mlx->player->angle > 2 * M_PI)
			mlx->player->angle -= 2 * M_PI;
	}
	else
	{
		mlx->player->angle -= ROTATION_SPEED;
		if (mlx->player->angle < 0)
			mlx->player->angle += 2 * M_PI;
	}
}

int	is_valid_position(t_game *game, int map_x, int map_y)
{
	if (map_x < 0 || map_y < 0)
		return (0);
	if (map_y >= game->height_map || map_x >= game->width_map)
		return (0);
	if (!game->map[map_y])
		return (0);
	if (map_x >= (int)ft_strlen(game->map[map_y]))
		return (0);
	return (1);
}

static int	can_move_to(t_mlx *mlx, int new_x, int new_y)
{
	int	map_x_new;
	int	map_y_new;
	int	map_x_cur;
	int	map_y_cur;

	map_x_new = new_x / TILE_SIZE;
	map_y_new = new_y / TILE_SIZE;
	map_x_cur = mlx->player->player_x / TILE_SIZE;
	map_y_cur = mlx->player->player_y / TILE_SIZE;
	if (!is_valid_position(mlx->game, map_x_new, map_y_new)
		|| !is_valid_position(mlx->game, map_x_cur, map_y_cur))
		return (0);
	if (mlx->game->map[map_y_new][map_x_new] != '1'
		&& mlx->game->map[map_y_new][map_x_cur] != '1'
		&& mlx->game->map[map_y_cur][map_x_new] != '1')
		return (1);
	return (0);
}

void	move_player(t_mlx *mlx, double move_x, double move_y)
{
	int	new_x;
	int	new_y;

	new_x = roundf(mlx->player->player_x + move_x);
	new_y = roundf(mlx->player->player_y + move_y);
	if (can_move_to(mlx, new_x, new_y))
	{
		mlx->player->player_x = new_x;
		mlx->player->player_y = new_y;
	}
}

// static void	move_player(t_mlx *mlx, double move_x, double move_y)
// {
// 	int	map_y;
// 	int	map_x;
// 	int	new_x;
// 	int	new_y;
// 	int	current_map_x;
// 	int	current_map_y;

// 	new_x = roundf(mlx->player->player_x + move_x);
// 	new_y = roundf(mlx->player->player_y + move_y);
// 	map_x = (new_x / TILE_SIZE);
// 	map_y = (new_y / TILE_SIZE);
// 	current_map_x = mlx->player->player_x / TILE_SIZE;
// 	current_map_y = mlx->player->player_y / TILE_SIZE;
// 	if (!is_valid_position(mlx->game, map_x, map_y)
// 		|| !is_valid_position(mlx->game, current_map_x, current_map_y))
// 		return ;
// 	if ((mlx->game->map[map_y][map_x] != '1'
// 		&& (mlx->game->map[map_y][current_map_x] != '1'
// 		&& mlx->game->map[current_map_y][map_x] != '1')))
// 	{
// 		mlx->player->player_x = new_x;
// 		mlx->player->player_y = new_y;
// 	}
// }
