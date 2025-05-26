/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enclosure_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:42:13 by asaulnie          #+#    #+#             */
/*   Updated: 2025/05/26 11:41:38 by fcrocq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_edge_row(char *row, int y)
{
	int	x;

	x = 0;
	while (row[x])
	{
		if (row[x] != '1')
		{
			printf("Error\nMap not closed at %d,%d\n", x, y);
			return (1);
		}
		x++;
	}
	return (0);
}

static int out_of_bounds(t_game *g, int x, int y)
{
    int curr_len;
    
    // Vérifications de base
    if (y < 0 || y >= g->height_map || x < 0)
        return (1);
    
    curr_len = ft_strlen(g->map[y]);
    if (x >= curr_len)
        return (1);
    
    // Vérifier les lignes adjacentes
    if (y > 0) {
        int up_len = ft_strlen(g->map[y - 1]);
        if (x >= up_len)
            return (1);
    }
    
    if (y < g->height_map - 1) {
        int down_len = ft_strlen(g->map[y + 1]);
        if (x >= down_len)
            return (1);
    }
    
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
