/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:55:21 by fcrocq            #+#    #+#             */
/*   Updated: 2025/06/18 13:49:46 by fcrocq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main_loop(void	*param)
{
	t_mlx	*mlx;
	double	move_x;
	double	move_y;

	mlx = (t_mlx *)param;
	move_x = 0.0;
	move_y = 0.0;
	hook(mlx, move_x, move_y);
	cast_rays(mlx);
	draw_minimap(mlx);
	mlx_put_image_to_window(mlx->game->mlx_ptr, mlx->game->win_ptr,
		mlx->img, 0, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_game		*game;
	t_player	*player;
	t_ray		*ray;
	t_mlx		mlx;

	if (ac != 2)
		return (printf("Error\nOnly one argument needed\n"), 1);
	if (check_extension(av[1]) != 0)
		return (1);
	if (init_structures(&game, &player, &ray) != 0)
		return (1);
	if (open_map(av[1], game) != 0)
		return (cleanup_all(game, player, ray), 1);
	if (init_mlx(game, player, ray) != 0)
		return (cleanup_all(game, player, ray), 1);
	(find_player(game), init_player(player, game));
	if (setup_image(&mlx, game, player, ray) != 0)
	{
		(clean_mlx_error(game, &mlx), cleanup_all(game, player, ray));
		return (1);
	}
	(setup_hooks(&mlx), mlx_loop(game->mlx_ptr), destroy_images(game, &mlx));
	(cleanup_mlx(game), cleanup_game(game));
	(free(game), free(player), free(ray));
	return (0);
}
