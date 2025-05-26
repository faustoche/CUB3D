/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:55:21 by fcrocq            #+#    #+#             */
/*   Updated: 2025/05/26 12:27:48 by fcrocq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Imprimer la carte simplement
void print_map(t_mlx *mlx)
{
    int y = 0;
    
    printf("\n=== MAP ===\n");
    printf("Player: (%.1d, %.1d)\n", mlx->player->player_x, mlx->player->player_y);
    
    while (y < mlx->game->height_map && mlx->game->map[y])
    {
        printf("%2d: %s\n", y, mlx->game->map[y]);
        y++;
    }
    printf("===========\n");
}

// Test simple de détection de mur
void test_wall(t_mlx *mlx, float x, float y)
{
    int map_x = (int)(x / TILE_SIZE);
    int map_y = (int)(y / TILE_SIZE);
    
    printf("Test (%.1f, %.1f) -> [%d][%d] = ", x, y, map_y, map_x);
    
    if (map_y < 0 || map_y >= mlx->game->height_map) {
        printf("OUT OF BOUNDS Y\n");
        return;
    }
    
    if (!mlx->game->map[map_y]) {
        printf("NULL LINE\n");
        return;
    }
    
    if (map_x < 0 || map_x >= (int)ft_strlen(mlx->game->map[map_y])) {
        printf("OUT OF BOUNDS X\n");
        return;
    }
    
    char tile = mlx->game->map[map_y][map_x];
    printf("'%c' -> %s\n", tile, (tile == '1' || tile == 'D') ? "WALL" : "FLOOR");
}

// Tester autour du joueur
void test_around_player(t_mlx *mlx)
{
    float px = mlx->player->player_x;
    float py = mlx->player->player_y;
    
    printf("\n=== TESTS AROUND PLAYER ===\n");
    test_wall(mlx, px, py);                    // Position actuelle
    test_wall(mlx, px, py - TILE_SIZE);        // Nord
    test_wall(mlx, px, py + TILE_SIZE);        // Sud  
    test_wall(mlx, px - TILE_SIZE, py);        // Ouest
    test_wall(mlx, px + TILE_SIZE, py);        // Est
    printf("============================\n");
}

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
	if (open_map(av[1], game) != 0)
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
	load_all_textures(&mlx);
	print_map(&mlx);
	test_around_player(&mlx);
	mlx_loop_hook(game->mlx_ptr, &main_loop, &mlx);
	mlx_key_hook(game->mlx_ptr, &key_input, &mlx);
	mlx_hook(game->win_ptr, KeyPress, KeyPressMask, key_input, &mlx);
	mlx_hook(game->win_ptr, KeyRelease, KeyReleaseMask, key_release, &mlx);
	mlx_hook(game->win_ptr, EVENT_MOUSE_CODE, 0, &mouse_handler, &mlx);
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
