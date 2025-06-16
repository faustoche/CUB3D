/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:55:21 by fcrocq            #+#    #+#             */
/*   Updated: 2025/06/16 14:21:34 by fcrocq           ###   ########.fr       */
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

	game = malloc(sizeof(t_game));
	player = malloc(sizeof(t_player));
	if (!player)
	{
		free(game);
		return (printf("Memory allocation failed\n"));
	}
	ft_memset(player, 0, sizeof(t_player));
	ray = malloc(sizeof(t_ray));
	if (!ray)
	{
		free(game);
		free(player);
		return (printf("Memory allocation failed\n"));
	}
	ft_memset(ray, 0, sizeof(t_ray));

	init_datas(game);
	if (open_map(av[1], game) != 0)
	{
		cleanup_game(game);
		free(game);
		free(player);
		free(ray);
		return (1);
	}
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
	{
		cleanup_game(game);
		free(game);
		free(player);
		free(ray);
		return (printf("Error\nMLX init failed\n"), 1);
	}
	game->win_ptr = mlx_new_window(game->mlx_ptr, WIDTH, HEIGHT, "Cub3D");
	if (!game->win_ptr)
	{
		cleanup_game(game);
		free(game);
		free(player);
		free(ray);	
		return (printf("Error\nWindow creation failed\n"), 1);
	}
	find_player(game);
	init_player(player, game);
	mlx.img = mlx_new_image(game->mlx_ptr, WIDTH, HEIGHT);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bpp, &mlx.size_line,
			&mlx.endian);
	mlx.game = game;
	mlx.player = player;
	mlx.ray = ray;
	if (!load_all_textures(&mlx))
    {
        mlx_destroy_image(game->mlx_ptr, mlx.img);
        mlx_destroy_window(game->mlx_ptr, game->win_ptr);
        mlx_destroy_display(game->mlx_ptr);
        free(game->mlx_ptr);
        cleanup_game(game);
        free(game);
        free(player);
        free(ray);
        return (1);
    }
	mlx_loop_hook(game->mlx_ptr, &main_loop, &mlx);
	mlx_key_hook(game->mlx_ptr, &key_input, &mlx);
	mlx_hook(game->win_ptr, KeyPress, KeyPressMask, key_input, &mlx);
	mlx_hook(game->win_ptr, KeyRelease, KeyReleaseMask, key_release, &mlx);
	mlx_hook(game->win_ptr, EVENT_MOUSE_CODE, (1L << 6), &mouse_handler, &mlx);
	mlx_hook(game->win_ptr, LeaveNotify, LeaveWindowMask, &mouse_leave, &mlx);
	mlx_hook(mlx.game->win_ptr, 17, 1L<<17, close_window, &mlx);
	mlx_loop(game->mlx_ptr);
	destroy_images(game, &mlx);
	cleanup_game(game);
	free(game);
	free(player);
	free(ray);
	return (0);
}
