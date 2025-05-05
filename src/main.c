/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:31:59 by fcrocq            #+#    #+#             */
/*   Updated: 2025/05/05 14:51:53 by fcrocq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

int	main_loop(void	*param)
{
	t_mlx	*mlx = (t_mlx *)param;

	mlx_destroy_image(mlx->game->mlx_ptr, mlx->img); // efface l'image précédente (de chaque frame)
	mlx->img = mlx_new_image(mlx->game->mlx_ptr, WIDTH, HEIGHT); // crée une nouvelle image
	update_player(mlx); // mise a jour de l'emplacement du joueur 
	//cast_rays(mlx); // fonction principale du raycasting
	mlx_put_image_to_window(mlx->game->mlx_ptr, mlx->game->win_ptr, mlx->img, 0, 0);
	return (0);
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
	player->angle = M_PI;
	player->fov_rd = (60 * M_PI) / 180; // conversion de l'angle de 60 degres en radians
	player->rot = 0; // rotation de la vue, tourner à gauche ou à droite 
	player->left_right = 0;
	player->up_down = 0;
}

int main(int ac, char **av)
{
	t_game		*game;
	t_player	*player;
	t_ray		*ray;
	t_mlx		mlx;

	if (ac != 2)
		return (printf("Error\nOnly one argument needed\n"), 1);
	game = malloc(sizeof(t_game));
	player = calloc(1, sizeof(t_player));
	ray = calloc(1, sizeof(t_ray));
	init_datas(game); // initialise les datas
	if (open_map(av, game) != 0) // ouvre la map
		return (1);
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (printf("Error\nMLX init failed\n"), 1);
	game->win_ptr = mlx_new_window(game->mlx_ptr, WIDTH, HEIGHT, "Cub3D");
	if (!game->win_ptr)
		return (printf("Error\nWindow creation failed\n"), 1);
	find_player(game); //initialise game->player x/y
	init_player(player, game);
	mlx.img = mlx_new_image(game->mlx_ptr, WIDTH, HEIGHT);
	mlx.game = game;
	mlx.player = player;
	mlx.ray = ray;
	mlx_loop_hook(game->mlx_ptr, &main_loop, &mlx);
	mlx_key_hook(game->mlx_ptr, &key_input, &mlx);
	mlx_loop(game->mlx_ptr);
	return (0);
}
