/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 09:25:46 by faustoche         #+#    #+#             */
/*   Updated: 2025/05/20 17:08:51 by fcrocq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*get_direction_text(double angle)
{
	while (angle < 0)
		angle += 2 * M_PI;
	while (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	if (angle >= 7 * M_PI / 4 || angle < M_PI / 8)
		return ("EST");
	else if (angle >= M_PI / 8 && angle < 3 * M_PI / 8)
		return ("NORD-EST");
	else if (angle >= 3 * M_PI / 8 && angle < 5 * M_PI / 8)
		return ("NORD");
	else if (angle >= 5 * M_PI / 8 && angle < 7 * M_PI / 8)
		return ("NORD-OUEST");
	else if (angle >= 7 * M_PI / 8 && angle < 9 * M_PI / 8)
		return ("OUEST");
	else if (angle >= 9 * M_PI / 8 && angle < 11 * M_PI / 8)
		return ("SUD-OUEST");
	else if (angle >= 11 * M_PI / 8 && angle < 13 * M_PI / 8)
		return ("SUD");
	else
		return ("SUD-EST");
}

void	draw_direction_text(t_minimap *mini)
{
	char	*text;

	text = get_direction_text(mini->mlx->player->angle);
	mlx_string_put(mini->mlx->game->mlx_ptr, mini->mlx->game->win_ptr,
		mini->origin_x, mini->origin_y - 20, 0x330000, text);
}

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
