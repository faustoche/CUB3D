/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:52:49 by asaulnie          #+#    #+#             */
/*   Updated: 2025/05/21 14:47:28 by asaulnie         ###   ########.fr       */
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
	if (rows == 0 && !valid_map_chars(line))
	{
		printf("Error\nBad char in map\n");
		return (-1);
	}
	if (new_width < 0)
		return (-1);
	width = new_width;
	if (append_row(g, line, rows) < 0)
		return (-1);
	g->width_map = width;
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

	if (find_closure_error(g, &err_x, &err_y))
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
