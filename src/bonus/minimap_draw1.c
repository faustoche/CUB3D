/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 09:25:46 by faustoche         #+#    #+#             */
/*   Updated: 2025/05/20 17:20:43 by fcrocq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_tile_square(t_minimap *mini, int sx, int sy, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < MINIMAP_TILE)
	{
		x = 0;
		while (x < MINIMAP_TILE)
		{
			ft_mlx_pixel_put(mini->mlx, sx + x, sy + y, color);
			x++;
		}
		y++;
	}
}

void	draw_tiles(t_minimap *mini, int dx, int dy)
{
	int		map_x;
	int		map_y;
	int		screen_x;
	int		screen_y;
	char	tile;

	screen_y = mini->origin_y + (MINIMAP_RADIUS - dy) * MINIMAP_TILE;
	screen_x = mini->origin_x + (dx + MINIMAP_RADIUS) * MINIMAP_TILE;
	map_x = mini->player_tile_x + dx;
	map_y = mini->player_tile_y + dy;
	if (map_x < 0 || map_y < 0 || map_y >= mini->mlx->game->height_map
		|| map_x >= mini->mlx->game->width_map)
		mini->color = EMPTY_COLOR;
	else
	{
		tile = mini->mlx->game->map[map_y][map_x];
		if (tile == '1')
			mini->color = WALL_COLOR;
		else
			mini->color = FLOOR_COLOR;
	}
	draw_tile_square(mini, screen_x, screen_y, mini->color);
}

static void	draw_minimap_rows(t_minimap *mini, int dy)
{
	int	dx;

	dx = -MINIMAP_RADIUS_X;
	while (dx <= MINIMAP_RADIUS_X)
	{
		draw_tiles(mini, dx, dy);
		dx++;
	}
}

static void	draw_minimap_tiles(t_minimap *mini)
{
	int	dy;

	dy = -MINIMAP_RADIUS_Y;
	while (dy <= MINIMAP_RADIUS_Y)
	{
		draw_minimap_rows(mini, dy);
		dy++;
	}
}

void	draw_minimap(t_mlx *mlx)
{
	t_minimap	mini;

	mini.mlx = mlx;
	mini.origin_x = 10;
	mini.origin_y = 10;
	mini.player_tile_x = mlx->player->player_x / TILE_SIZE;
	mini.player_tile_y = mlx->player->player_y / TILE_SIZE;
	mini.center_x = mini.origin_x + MINIMAP_RADIUS * MINIMAP_TILE;
	mini.center_y = mini.origin_y + MINIMAP_RADIUS * MINIMAP_TILE;
	draw_minimap_tiles(&mini);
	draw_minimap_player(&mini);
	draw_direction_ray(&mini, mlx->player->angle);
	draw_direction_text(&mini);
}
