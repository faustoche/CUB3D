/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:05:30 by fcrocq            #+#    #+#             */
/*   Updated: 2025/06/19 14:00:16 by fcrocq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_bonus.h"

int	init_structures(t_game **game, t_player **player, t_ray **ray)
{
	*game = malloc(sizeof(t_game));
	if (!*game)
		return (printf("Error\nMemory allocation failed\n"), 1);
	*player = malloc(sizeof(t_player));
	if (!*player)
	{
		free(*game);
		return (printf("Error\nMemory allocation failed\n"), 1);
	}
	ft_memset(*player, 0, sizeof(t_player));
	*ray = malloc(sizeof(t_ray));
	if (!*ray)
	{
		free(*game);
		free(*player);
		return (printf("Error\nMemory allocation failed\n"), 1);
	}
	ft_memset(*ray, 0, sizeof(t_ray));
	init_datas(*game);
	return (0);
}

int	init_mlx(t_game *game, t_player *player, t_ray *ray)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
	{
		cleanup_mlx(game);
		return (printf("Error\nMLX init failed\n"), 1);
	}
	game->win_ptr = mlx_new_window(game->mlx_ptr, WIDTH, HEIGHT, "Cub3D");
	if (!game->win_ptr)
	{
		cleanup_all(game, player, ray);
		return (printf("Error\nWindow creation failed\n"), 1);
	}
	return (0);
}

int	setup_image(t_mlx *mlx, t_game *game, t_player *player, t_ray *ray)
{
	mlx->img = mlx_new_image(game->mlx_ptr, WIDTH, HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->size_line,
			&mlx->endian);
	mlx->game = game;
	mlx->player = player;
	mlx->ray = ray;
	if (!load_all_textures(mlx))
	{
		cleanup_mlx(game);
		return (1);
	}
	return (0);
}

void	setup_hooks(t_mlx *mlx)
{
	mlx_loop_hook(mlx->game->mlx_ptr, &main_loop, mlx);
	mlx_hook(mlx->game->win_ptr, KeyPress, KeyPressMask, key_input, mlx);
	mlx_hook(mlx->game->win_ptr, KeyRelease, KeyReleaseMask, key_release, mlx);
	mlx_hook(mlx->game->win_ptr, EVENT_MOUSE_CODE, (1L << 6),
		&mouse_handler, mlx);
	mlx_hook(mlx->game->win_ptr, LeaveNotify, LeaveWindowMask,
		&mouse_leave, mlx);
	mlx_hook(mlx->game->win_ptr, 17, 1L << 17, close_window, mlx);
}

void	clean_mlx_error(t_game *game, t_mlx *mlx)
{
	if (mlx->img)
		mlx_destroy_image(game->mlx_ptr, mlx->img);
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
}
