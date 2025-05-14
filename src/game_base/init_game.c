/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faustoche <faustoche@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:47:39 by fcrocq            #+#    #+#             */
/*   Updated: 2025/05/14 16:01:18 by faustoche        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_datas(t_game *game)
{
	game->mlx_ptr = NULL;
	game->win_ptr = NULL;
	game->height_map = 0;
	game->width_map = 0;
}

void	find_player(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'Z')
			{
				game->player_x = x;
				game->player_y = y;
				game->map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}

/* 
* TILE_SIZE correspond à la taille en pixel d'une case sur la map (1/0)
* Game->player x/y * TILE_SIZE donne la position en pixels du coin 
	supérieur gauche de la case
* En ajoutant TILE_SIZE / 2, on place le joueur au centre de la case, ce qui
	pratique pour le raycasting (les rayons doivent partir du milieu de la case
	pour que ce soit visuellement correct)
* L'angle représente l'orientation du joueur dans l'espace 2D, mesuré en radians.
* On garde l'angle à 60 degré car c'est l'angle le plus équilibré visuellement
*/

void	init_player(t_player *player, t_game *game)
{
	player->player_x = game->player_x * TILE_SIZE + TILE_SIZE / 2;
	player->player_y = game->player_y * TILE_SIZE + TILE_SIZE / 2;
	player->angle = 3 * M_PI / 2;
	player->fov_rd = (60 * M_PI) / 180; // conversion de l'angle de 60 degres en radians
	player->rot = 0; // rotation de la vue, tourner à gauche ou à droite 
	player->left_right = 0;
	player->up_down = 0;
}

void	exit_game(t_mlx *mlx)
{
	mlx_destroy_window(mlx->game->mlx_ptr, mlx->game->win_ptr);
	exit (0);
}