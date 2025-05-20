/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:31:59 by fcrocq            #+#    #+#             */
/*   Updated: 2025/05/20 16:58:36 by fcrocq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static int	main_loop(void	*param)
{
	t_mlx	*mlx;
	double	move_x;
	double	move_y;

	mlx = (t_mlx *)param;
	move_x = 0.0;
	move_y = 0.0;
	mlx_destroy_image(mlx->game->mlx_ptr, mlx->img);
	mlx->img = mlx_new_image(mlx->game->mlx_ptr, WIDTH, HEIGHT);
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
	int			i;

	if (ac != 2)
		return (printf("Error\nOnly one argument needed\n"), 1);
	game = malloc(sizeof(t_game));
	player = calloc(1, sizeof(t_player));
	ray = calloc(1, sizeof(t_ray));
	init_datas(game);
	if (open_map(av, game) != 0)
		return (1);
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (printf("Error\nMLX init failed\n"), 1);
	game->win_ptr = mlx_new_window(game->mlx_ptr, WIDTH, HEIGHT, "Cub3D");
	if (!game->win_ptr)
		return (printf("Error\nWindow creation failed\n"), 1);
	find_player(game);
	init_player(player, game);
	mlx.img = mlx_new_image(game->mlx_ptr, WIDTH, HEIGHT);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bpp, &mlx.size_line,
			&mlx.endian);
	mlx.game = game;
	mlx.player = player;
	mlx.ray = ray;
	mlx_loop_hook(game->mlx_ptr, &main_loop, &mlx);
	mlx_key_hook(game->mlx_ptr, &key_input, &mlx);
	mlx_hook(game->win_ptr, KeyPress, KeyPressMask, key_input, &mlx);
	mlx_hook(game->win_ptr, KeyRelease, KeyReleaseMask, key_release, &mlx);
	//mlx_hook(game->win_ptr, EVENT_MOUSE_CODE, 0, &mouse_handler, &mlx);
	mlx_loop(game->mlx_ptr);
	if (game->map)
	{
		i = 0;
		while (game->map[i])
		{
			free(game->map[i]);
			i++;
		}
		free(game->map);
	}
	free(game);
	free(player);
	free(ray);
	return (0);
}
