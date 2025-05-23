/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:05:58 by fcrocq            #+#    #+#             */
/*   Updated: 2025/05/20 17:05:34 by fcrocq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ray_line(t_minimap *mini)
{
	int		draw_x;
	int		draw_y;
	double	offset_x;
	double	offset_y;

	offset_x = (mini->ray_x - mini->mlx->player->player_x)
		/ TILE_SIZE * MINIMAP_TILE;
	offset_y = (mini->ray_y - mini->mlx->player->player_y)
		/ TILE_SIZE * MINIMAP_TILE;
	draw_x = mini->center_x + (int)offset_x;
	draw_y = mini->center_y - (int)offset_y;
	ft_mlx_pixel_put(mini->mlx, draw_x, draw_y, RAY_COLOR);
}

void	trace_ray(t_minimap *mini)
{
	int		i;
	int		map_x;
	int		map_y;

	i = 0;
	while (i < 200)
	{
		mini->ray_x += mini->dx;
		mini->ray_y += mini->dy;
		map_x = (int)(mini->ray_x / TILE_SIZE);
		map_y = (int)(mini->ray_y / TILE_SIZE);
		if (map_x < 0 || map_y < 0
			|| map_x >= mini->mlx->game->width_map
			|| map_y >= mini->mlx->game->height_map)
			break ;
		if (mini->mlx->game->map[map_y][map_x] == '1')
			break ;
		draw_ray_line(mini);
		i++;
	}
}

void	draw_direction_ray(t_minimap *mini, double angle)
{
	mini->ray_x = (double)(mini->mlx->player->player_x);
	mini->ray_y = (double)(mini->mlx->player->player_y);
	mini->dx = cos(angle) * 2.0;
	mini->dy = sin(angle) * 2.0;
	trace_ray(mini);
}
