/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:50:44 by fcrocq            #+#    #+#             */
/*   Updated: 2025/04/30 14:34:52 by fcrocq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// tant que je n'atteind pas la taille voulu, je dessine un pixel correspondant
static void	draw_pixel(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;
	int	size;

	size = 50; // taille provisoire
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			mlx_pixel_put(game->mlx_ptr, game->win_ptr, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

// si c'est un 1 noir, sinon blanc, sinon j'itere et je continue,
// je dessine un pixel correspond
void	display_map(t_game *game)
{
	int	x;
	int	y;
	int	color;

	//mlx_clear_window(game->mlx_ptr, game->win_ptr);
	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->player_x == x && game->player_y == y)
				color = 0x00FF0033;
			else if (game->map[y][x] == '1')
				color =  0xFFFFFF;
			else if (game->map[y][x] == '0')
				color = 0x000000;
			else
			{
				x++;
				continue ;
			}
			draw_pixel(game, x * 50, y * 50, color);
			x++;
		}
		y++;
	}
}