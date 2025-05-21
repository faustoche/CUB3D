/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enclosure_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:42:13 by asaulnie          #+#    #+#             */
/*   Updated: 2025/05/21 14:47:02 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	out_of_bounds(t_game *g, int x, int y)
{
	if (y == 0 || y == g->height_map - 1 || x == 0 || x == g->width_map - 1)
		return (1);
	if (g->map[y - 1][x] == '\0' || g->map[y + 1][x] == '\0')
		return (1);
	if (g->map[y][x - 1] == '\0' || g->map[y][x + 1] == '\0')
		return (1);
	return (0);
}

int	find_closure_error(t_game *g, int *ex, int *ey)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (g->map[y])
	{
		x = 0;
		while (g->map[y][x])
		{
			c = g->map[y][x];
			if ((c == '0' || ft_strchr("NSEW", c))
				&& out_of_bounds(g, x, y))
			{
				*ex = x;
				*ey = y;
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}
