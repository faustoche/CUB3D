/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:54:37 by fcrocq            #+#    #+#             */
/*   Updated: 2025/05/26 14:38:25 by fcrocq           ###   ########.fr       */
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

// static void move_player(t_mlx *mlx, double move_x, double move_y)
// {
//     int map_y;
//     int map_x;
//     int new_x;
//     int new_y;
//     int current_map_x;
//     int current_map_y;
    
//     new_x = roundf(mlx->player->player_x + move_x);
//     new_y = roundf(mlx->player->player_y + move_y);
//     map_x = (new_x / TILE_SIZE);
//     map_y = (new_y / TILE_SIZE);
    
//     current_map_x = mlx->player->player_x / TILE_SIZE;
//     current_map_y = mlx->player->player_y / TILE_SIZE;
    
//     // Vérifier les limites de la carte avant d'accéder aux indices
//     if (map_y < 0 || map_y >= mlx->game->height_map || 
//         map_x < 0 || map_x >= mlx->game->width_map)
//         return;
    
//     if (current_map_y < 0 || current_map_y >= mlx->game->height_map || 
//         current_map_x < 0 || current_map_x >= mlx->game->width_map)
//         return;
    
//     printf("Tentative de mouvement vers: (%d, %d) -> map[%d][%d]\n", new_x, new_y, map_y, map_x);
//     printf("Position actuelle: (%d, %d) -> map[%d][%d]\n", 
//            (int)mlx->player->player_x, (int)mlx->player->player_y, current_map_y, current_map_x);
//     if (mlx->game->map[map_y][map_x] == '1')
//         return;
//     int test_map_x = (new_x / TILE_SIZE);
//     if (test_map_x >= 0 && test_map_x < mlx->game->width_map && 
//         mlx->game->map[current_map_y][test_map_x] == '1')
//         return;
//     int test_map_y = (new_y / TILE_SIZE);
//     if (test_map_y >= 0 && test_map_y < mlx->game->height_map && 
//         mlx->game->map[test_map_y][current_map_x] == '1')
//         return;
//     mlx->player->player_x = new_x;
//     mlx->player->player_y = new_y;
    
//     printf("Mouvement effectué vers: (%d, %d)\n", 
//            (int)mlx->player->player_x, (int)mlx->player->player_y);
// }

static void	move_player(t_mlx *mlx, double move_x, double move_y)
{
	int	map_y;
	int	map_x;
	int	new_x;
	int	new_y;

	new_x = roundf(mlx->player->player_x + move_x);
	new_y = roundf(mlx->player->player_y + move_y);
	map_x = (new_x / TILE_SIZE);
	map_y = (new_y / TILE_SIZE);
	
	if ((mlx->game->map[map_y][map_x] != '1'
		&& (mlx->game->map[map_y][mlx->player->player_x / TILE_SIZE] != '1'
		&& mlx->game->map[mlx->player->player_y / TILE_SIZE][map_x] != '1')))
	{
		mlx->player->player_x = new_x;
		mlx->player->player_y = new_y;
	}
}

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
