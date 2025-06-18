/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 09:25:46 by faustoche         #+#    #+#             */
/*   Updated: 2025/06/18 15:36:32 by fcrocq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap_player(t_minimap *mini)
{
	int	size;
	int	x;
	int	y;

	size = MINIMAP_TILE / 2;
	y = -size / 2;
	while (y <= size / 2)
	{
		x = -size / 2;
		while (x <= size / 2)
		{
			ft_mlx_pixel_put(mini->mlx, mini->center_x + x,
				mini->center_y + y, PLAYER_COLOR);
			x++;
		}
		y++;
	}
}

int	choose_color(char tile)
{
	if (tile == '1')
		return (WALL_COLOR);
	else if (tile == 'D')
		return (BORDER_COLOR);
	else if (tile == '0')
		return (FLOOR_COLOR);
	else
		return (WALL_COLOR);
}

int	get_tile_color(t_minimap *mini, int map_x, int map_y)
{
	char	tile;
	int		line_length;

	if (map_x < 0 || map_y < 0 || map_y >= mini->mlx->game->height_map)
		return (EMPTY_COLOR);
	line_length = ft_strlen(mini->mlx->game->map[map_y]);
	if (map_x >= line_length)
		return (EMPTY_COLOR);
	tile = mini->mlx->game->map[map_y][map_x];
	return (choose_color(tile));
}
