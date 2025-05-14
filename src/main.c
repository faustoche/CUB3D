/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faustoche <faustoche@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:31:59 by fcrocq            #+#    #+#             */
/*   Updated: 2025/05/14 16:01:14 by faustoche        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	main_loop(void	*param)
{
	t_mlx	*mlx;
	double	move_x;
	double	move_y;
	
	mlx = (t_mlx *)param;
	move_x = 0.0;
	move_y = 0.0;
	mlx_destroy_image(mlx->game->mlx_ptr, mlx->img); // efface l'image précédente (de chaque frame)
	mlx->img = mlx_new_image(mlx->game->mlx_ptr, WIDTH, HEIGHT); // crée une nouvelle image
	hook(mlx, move_x, move_y);
	cast_rays(mlx);
	draw_minimap(mlx);
	mlx_put_image_to_window(mlx->game->mlx_ptr, mlx->game->win_ptr, mlx->img, 0, 0);
	return (0);
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
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bpp, &mlx.size_line, &mlx.endian);
	mlx.game = game;
	mlx.player = player;
	mlx.ray = ray;
	mlx_loop_hook(game->mlx_ptr, &main_loop, &mlx);
	mlx_key_hook(game->mlx_ptr, &key_input, &mlx);
	mlx_hook(game->win_ptr, EVENT_MOUSE_CODE, 0, &mouse_handler, &mlx); // bonus pour la souris
	mlx_loop(game->mlx_ptr);
	if (game->map)
    {
        for (int i = 0; game->map[i]; i++)
            free(game->map[i]);
        free(game->map);
    }
    free(game);
    free(player);
    free(ray);
	return (0);
}
