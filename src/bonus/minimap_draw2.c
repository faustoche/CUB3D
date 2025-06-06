/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 09:25:46 by faustoche         #+#    #+#             */
/*   Updated: 2025/06/06 14:26:46 by fcrocq           ###   ########.fr       */
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
