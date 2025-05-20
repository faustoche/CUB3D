/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:53:23 by asaulnie          #+#    #+#             */
/*   Updated: 2025/05/20 20:26:14 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	set_texture(char **p, t_meta *m)
{
	if (ft_strcmp(p[0], "NO") == 0 && !m->no)
		m->no = ft_strdup(p[1]);
	else if (ft_strcmp(p[0], "SO") == 0 && !m->so)
		m->so = ft_strdup(p[1]);
	else if (ft_strcmp(p[0], "WE") == 0 && !m->we)
		m->we = ft_strdup(p[1]);
	else if (ft_strcmp(p[0], "EA") == 0 && !m->ea)
		m->ea = ft_strdup(p[1]);
	else
		return (0);
	return (1);
}

int	all_header_fields_set(t_meta *m)
{
	return (m->no && m->so && m->we && m->ea && m->f_set && m->c_set);
}

int	parse_header_line(char *line, t_meta *m)
{
	char	**p;
	int		res;

	p = ft_split(line, ' ');
	res = 0;
	if (!p[0] || !p[1])
	{
		if (p[0])
			printf("Error\nMissing value for header\n");
	}
	else if (set_texture(p, m))
		res = 1;
	else if (p[0][0] == 'F' || p[0][0] == 'C')
	{
		if ((p[0][0] == 'F' && !m->f_set) || (p[0][0] == 'C' && !m->c_set))
			res = set_color(p, m);
		else
			printf("Error\nInvalid or duplicate header '%s'\n", p[0]);
	}
	else if (ft_strchr("NSWEFC", p[0][0]))
		printf("Error\nInvalid or duplicate header '%s'\n", p[0]);
	else
		printf("Error\nInvalid header '%s'\n", p[0]);
	free_split(p);
	return (res);
}

int	read_header(int fd, t_meta *m)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		chomp_newline(line);
		if (is_blank_line(line))
			free(line);
		else
		{
			if (!parse_header_line(line, m))
			{
				free(line);
				return (1);
			}
			if (all_header_fields_set(m))
				return (0);
		}
	}
	printf("Error\nMissing header fields\n");
	return (1);
}

int	init_fd_and_header(const char *path, t_game *g, int *fd)
{
	*fd = open(path, O_RDONLY);
	if (*fd < 0)
	{
		printf("Error\nCannot open file\n");
		return (-1);
	}
	init_meta(&g->meta);
	if (read_header(*fd, &g->meta) != 0)
	{
		close(*fd);
		return (-1);
	}
	return (0);
}
