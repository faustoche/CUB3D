/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:47:39 by fcrocq            #+#    #+#             */
/*   Updated: 2025/06/18 10:48:58 by fcrocq           ###   ########.fr       */
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
			if (ft_strchr("NSEW", game->map[y][x]))
			{
				game->player_x = x;
				game->player_y = y;
				game->player_dir = game->map[y][x];
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
* En ajoutant TILE_SIZE / 2, on place le joueur au centre de la case, 
ce qui
	pratique pour le raycasting (les rayons doivent partir du milieu de 
	la case
	pour que ce soit visuellement correct)
* L'angle représente l'orientation du joueur dans l'espace 2D, mesuré en 
radians.
* On garde l'angle à 60 degré car c'est l'angle le plus équilibré 
visuellement
* player->fov_rd = (60 * M_PI) / 180; // conversion de l'angle de 60 degres 
en radians
	player->rot = 0; // rotation de la vue, tourner à gauche ou à droite 
*/

void	init_player(t_player *player, t_game *game)
{
	player->player_x = game->player_x * TILE_SIZE + TILE_SIZE / 2;
	player->player_y = game->player_y * TILE_SIZE + TILE_SIZE / 2;
	if (game->player_dir == 'N')
		player->angle = 3 * M_PI / 2;
	else if (game->player_dir == 'S')
		player->angle = M_PI / 2;
	else if (game->player_dir == 'E')
		player->angle = 0;
	else if (game->player_dir == 'W')
		player->angle = M_PI;
	player->fov_rd = (60 * M_PI) / 180;
	player->rot = 0;
	player->left_right = 0;
	player->up_down = 0;
}

int	close_window(void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	if (!mlx || !mlx->game)
		return (0);
	destroy_images(mlx->game, mlx);
	if (mlx->game->mlx_ptr)
		mlx_loop_end(mlx->game->mlx_ptr);
	cleanup_mlx(mlx->game);
	cleanup_game(mlx->game);
	free(mlx->game);
	free(mlx->player);
	free(mlx->ray);
	exit(EXIT_SUCCESS);
	return (0);
}

int	check_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4)
	{
		printf("Error\nInvalid file name\n");
		return (-1);
	}
	if (ft_strcmp(filename + len - 4, ".cub") != 0)
	{
		printf("Error\nFile extension must be .cub\n");
		return (-1);
	}
	return (0);
}
