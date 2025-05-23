/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:53:23 by asaulnie          #+#    #+#             */
/*   Updated: 2025/05/23 15:15:09 by asaulnie         ###   ########.fr       */
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

static int	handle_texture(char *key, char *rest, t_meta *m)
{
	char	*parts[3];

	if (strcmp(key, "NO") == 0 || strcmp(key, "SO") == 0
		|| strcmp(key, "WE") == 0 || strcmp(key, "EA") == 0)
	{
		parts[0] = key;
		parts[1] = rest;
		parts[2] = NULL;
		if (!set_texture(parts, m))
		{
			printf("Error\nMissing or duplicate texture '%s'\n", key);
			return (-1);
		}
		return (1);
	}
	return (0);
}

static int	handle_color(char *key, char *rest, t_meta *m)
{
	char	*parts[3];

	if (key[0] == 'F' || key[0] == 'C')
	{
		parts[0] = key;
		parts[1] = rest;
		parts[2] = NULL;
		if (!set_color(parts, m))
		{
			printf("Error\nMissing or invalid color for '%s'\n", key);
			return (-1);
		}
		return (1);
	}
	return (0);
}

int	parse_header_line(char *line, t_meta *m)
{
	char	key[3];
	char	*rest;
	int		ret;

	while (*line == ' ' || *line == '\t')
		line++;
	if (*line == '1')
		return (printf("Error\nMissing header fields\n"), 0);
	if (sscanf(line, "%2s", key) != 1)
		return (0);
	rest = line + strlen(key);
	while (*rest == ' ' || *rest == '\t')
		rest++;
	ret = handle_texture(key, rest, m);
	if (ret > 0)
		return (1);
	if (ret < 0)
		return (0);
	ret = handle_color(key, rest, m);
	if (ret > 0)
		return (1);
	if (ret < 0)
		return (0);
	printf("Error\nInvalid or duplicate header '%s'\n", key);
	return (0);
}

int	read_header(int fd, t_meta *m)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		chomp_newline(line);
		if (is_blank_line(line))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (!parse_header_line(line, m))
		{
			free(line);
			return (1);
		}
		free(line);
		if (m->no && m->so && m->we && m->ea
			&& m->f_set && m->c_set)
			return (0);
		line = get_next_line(fd);
	}
	printf("Error\nMissing header fields\n");
	return (1);
}
