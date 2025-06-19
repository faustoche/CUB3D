/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:52:49 by asaulnie          #+#    #+#             */
/*   Updated: 2025/06/19 10:32:55 by fcrocq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	valid_map_chars(char *line)
{
	int		i;
	char	c;

	i = 0;
	while (line[i])
	{
		c = line[i++];
		if (!ft_strchr("01NSEWD ", c))
			return (0);
	}
	return (1);
}

static int	append_row(t_game *g, char *line, int rows)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = realloc(g->map, sizeof(char *) * (rows + 2));
	if (!tmp)
	{
		free(line);
		if (g->map)
		{
			while (i < rows && g->map[i])
			{
				free(g->map[i]);
				i++;
			}
			free(g->map);
		}
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
	int		len;
	char	*normalized_line;

	(void)width;
	normalized_line = normalize_map_line(line);
	if (!normalized_line)
	{
		free(line);
		return (printf("Error\nMemory allocation failed\n"), -1);
	}
	len = ft_strlen(normalized_line);
	if (rows == 0 && !valid_map_chars(normalized_line))
	{
		(free(line), free(normalized_line));
		return (printf("Error\nBad char in map\n"), -1);
	}
	free(line);
	if (append_row(g, normalized_line, rows) < 0)
	{
		free(normalized_line);
		return (-1);
	}
	if (len > g->width_map)
		g->width_map = len;
	return (0);
}

static void	count_players(t_game *g, int *player_count)
{
	int	y;
	int	x;

	*player_count = 0;
	y = 0;
	while (g->map[y])
	{
		x = 0;
		while (g->map[y][x])
		{
			if (ft_strchr("NSEW", g->map[y][x]))
				(*player_count)++;
			x++;
		}
		y++;
	}
}

int	validate_map(t_game *g)
{
	int	player_count;
	int	err_x;
	int	err_y;

	if (check_edge_row(g->map[0], 0))
		return (1);
	if (check_edge_row(g->map[g->height_map - 1], g->height_map - 1))
		return (1);
	if (find_closure_error(g, &err_x, &err_y) == 1)
	{
		printf("Error\nMap not closed at %d,%d\n", err_x, err_y);
		return (1);
	}
	count_players(g, &player_count);
	if (player_count != 1)
	{
		printf("Error\nExpected 1 player, found %d\n", player_count);
		return (1);
	}
	return (0);
}
