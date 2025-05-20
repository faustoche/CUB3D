/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:52:49 by asaulnie          #+#    #+#             */
/*   Updated: 2025/05/20 19:05:03 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_row_length(char *line, int rows, int width)
{
	int	len;

	len = ft_strlen(line);
	if (width < 0)
		return (len);
	if (len != width)
	{
		free(line);
		printf("Error\nInconsistent row length at row %d\n", rows);
		return (-1);
	}
	return (width);
}

static int	append_row(t_game *g, char *line, int rows)
{
	char	**tmp;

	tmp = realloc(g->map, sizeof(char *) * (rows + 2));
	if (!tmp)
	{
		free(line);
		printf("Error\nMemory allocation\n");
		return (-1);
	}
	g->map = tmp;
	g->map[rows] = line;
	g->map[rows + 1] = NULL;
	g->height_map = rows + 1;
	return (0);
}

int	process_map_row(t_game *g, char *line, int rows, int width)
{
	int	new_width;

	new_width = check_row_length(line, rows, width);
	if (new_width < 0)
		return (-1);
	width = new_width;
	if (append_row(g, line, rows) < 0)
		return (-1);
	g->width_map = width;
	return (0);
}

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

int	validate_map(t_game *g)
{
	int		x;
	int		y;
	int		player_count;
	char	c;

	player_count = 0;
	y = 0;
	while (g->map[y])
	{
		x = 0;
		while (g->map[y][x])
		{
			c = g->map[y][x];
			if (ft_strchr("NSEW", c))
				player_count++;
			if ((c == '0' || ft_strchr("NSEW", c)) && out_of_bounds(g, x, y))
				return (printf("Error\nMap not closed at %d,%d\n", x, y), 1);
			x++;
		}
		y++;
	}
	if (player_count != 1)
		return (printf("Error\nExpected 1 player, found %d\n", player_count), 1);
	return (0);
}
