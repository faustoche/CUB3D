/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:54:37 by fcrocq            #+#    #+#             */
/*   Updated: 2025/06/16 14:21:54 by fcrocq           ###   ########.fr       */
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

static int	is_valid_position(t_game *game, int map_x, int map_y)
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

int	key_release(int key, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	if (key == XK_W || key == XK_w || key == XK_Up || key == XK_S
		|| key == XK_s || key == XK_Down)
		mlx->player->up_down = 0;
	if (key == XK_A || key == XK_a || key == XK_D || key == XK_d)
		mlx->player->left_right = 0;
	if (key == XK_Left || key == XK_Right)
		mlx->player->rot = 0;
	return (0);
}
