/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:36:51 by fcrocq            #+#    #+#             */
/*   Updated: 2025/06/06 14:37:40 by fcrocq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	hook(t_mlx *mlx, double move_x, double move_y)
{
	if (mlx->player->rot == 1)
		rotate_player(mlx, 1);
	if (mlx->player->rot == -1)
		rotate_player(mlx, 0);
	if (mlx->player->left_right == 1)
	{
		move_x = -sin(mlx->player->angle) * PLAYER_SPEED;
		move_y = cos(mlx->player->angle) * PLAYER_SPEED;
	}
	if (mlx->player->left_right == -1)
	{
		move_x = sin(mlx->player->angle) * PLAYER_SPEED;
		move_y = -cos(mlx->player->angle) * PLAYER_SPEED;
	}
	if (mlx->player->up_down == 1)
	{
		move_x = cos(mlx->player->angle) * PLAYER_SPEED;
		move_y = sin(mlx->player->angle) * PLAYER_SPEED;
	}
	if (mlx->player->up_down == -1)
	{
		move_x = -cos(mlx->player->angle) * PLAYER_SPEED;
		move_y = -sin(mlx->player->angle) * PLAYER_SPEED;
	}
	move_player(mlx, move_x, move_y);
}

int	key_input(int key, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	if (key == XK_W || key == XK_w || key == XK_Up)
		mlx->player->up_down = 1;
	else if (key == XK_S || key == XK_s || key == XK_Down)
		mlx->player->up_down = -1;
	else if (key == XK_A || key == XK_a)
		mlx->player->left_right = -1;
	else if (key == XK_D || key == XK_d)
		mlx->player->left_right = 1;
	else if (key == XK_Left)
		mlx->player->rot = -1;
	else if (key == XK_Right)
		mlx->player->rot = 1;
	else if (key == XK_Escape)
		exit_game(mlx);
	else
		return (0);
	return (0);
}
