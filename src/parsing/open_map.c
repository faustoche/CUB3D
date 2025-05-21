/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:31:53 by fcrocq            #+#    #+#             */
/*   Updated: 2025/05/21 14:14:36 by asaulnie         ###   ########.fr       */
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
		if (!ft_strchr("01NSEW", c))
			return (0);
	}
	return (1);
}

static int	handle_map_line(t_game *g, char *line, int rows, int width)
{
	if (is_blank_line(line))
		return (printf("Error\nBlank line inside map\n"), 0);
	if (!valid_map_chars(line))
		return (printf("Error\nBad char in map\n"), 0);
	if (process_map_row(g, line, rows, width) != 0)
		return (0);
	return (1);
}

int	process_map_lines(int fd, t_game *g, int rows, int width)
{
	char	*line;
	int		status;

	line = get_next_line(fd);
	while (line)
	{
		chomp_newline(line);
		status = handle_map_line(g, line, rows, width);
		free(line);
		if (status != 1)
			return (0);
		rows++;
		line = get_next_line(fd);
	}
	return (1);
}

void	init_game(t_game *g, int *rows, int *width)
{
	t_meta	*m;

	*rows = 0;
	*width = -1;
	g->map = NULL;
	m = &g->meta;
	m->no = NULL;
	m->so = NULL;
	m->we = NULL;
	m->ea = NULL;
	m->c_r = 0;
	m->c_g = 0;
	m->c_b = 0;
	m->f_r = 0;
	m->f_g = 0;
	m->f_b = 0;
	m->f_set = 0;
	m->c_set = 0;
}

int	open_map(const char *path, t_game *g)
{
	int		fd;
	int		rows;
	char	*first_line;

	init_game(g, &rows, &g->width_map);
	if (open_and_read_header(path, g, &fd) < 0)
		return (1);
	if (!read_first_map_line(fd, &first_line))
	{
		close(fd);
		return (1);
	}
	if (process_map_row(g, first_line, rows, g->width_map))
	{
		free(first_line);
		close(fd);
		return (1);
	}
	if (!process_map_lines(fd, g, rows + 1, g->width_map))
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (validate_map(g));
}
