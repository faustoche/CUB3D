/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faustoche <faustoche@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:50:44 by fcrocq            #+#    #+#             */
/*   Updated: 2025/04/29 19:55:21 by faustoche        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// tant que je n'atteind pas la taille voulu, je dessine un pixel correspondant
static void	draw_pixel(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;
	int	size;

	size = 20; // taille provisoire
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

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == '1')
				color = OxOOOOOO; // noir
			else if (game->map[y][x] == '0')
				color = 0xFFFFFF; // blanc
			else
			{
				x++;
				continue ;
			}
			draw_pixel(game, x * 20, y * 20, color);
			x++;
		}
		y++;
	}
}